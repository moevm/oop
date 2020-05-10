#ifndef OOP_OBJECTFACTORY_H
#define OOP_OBJECTFACTORY_H

#include <map>
#include <string>
#include <memory>
#include <sstream>

// Based on Andrei Alexandrescu "Modern C ++ Design"

namespace cds
{
    // Proxy classes for generating code for creating objects

    /**
     * In this case, the templates will act as macros,
     * allowing to generate code for a specific creator
     * based on the template parameter
     * @tparam Base
     */
    template <class Base>
    class AbstractCreator
    {
    public:
        AbstractCreator()
        = default;

        virtual ~AbstractCreator()
        = default;

        virtual std::shared_ptr<Base> create() const = 0;

        // Implementation of non-copyable idiom
        AbstractCreator(const AbstractCreator&) = delete;
        AbstractCreator& operator= (const AbstractCreator&) = delete;
    };


    /**
     * The class in which the code will be generated
     * to create an object of a particular class
     * @tparam C
     * @tparam Base
     */
    template <class C, class Base>
    class Creator : public AbstractCreator<Base>
    {
    public:
        Creator()
        = default;

        virtual ~Creator()
        = default;

        virtual std::shared_ptr<Base> create() const { return std::make_shared<C>(); }
    };

    // FACTORY POLICIES

    class ObjectFactoryException : public std::exception
    {
        std::string	msg;
    public:
        explicit ObjectFactoryException(const std::string& msg) throw() : msg(msg) { }
        virtual ~ObjectFactoryException() throw() { }

        virtual const char *what() const throw() { return msg.c_str(); }
    };

    template <class Base, class Type>
    class ObjectFactoryIgnoreErrorPolicy
    {
    public:
        std::shared_ptr<Base> onCreateFailed([[maybe_unused]] const Type& type) const { return 0; }
        void onRemoveFailed([[maybe_unused]] const Type& type) { }
        void onDuplicateRegistered([[maybe_unused]] const Type& type) { }
    };

    template <class Base, class Type>
    class ObjectFactoryThrowExceptionErrorPolicy
    {
    public:
        std::string generateMessage(const char *msg, const Type& type) const
        {
            std::stringstream strm;
            strm << msg << ", requested type id : " << type;
            return strm.str();
        }

        std::shared_ptr<Base> onCreateFailed(const Type& type) const
        {
            throw ObjectFactoryException(generateMessage(
                    "ObjectFactory - can't create object (not registered)", type));
        }

        void onRemoveFailed(const Type& type)
        {
            throw ObjectFactoryException(generateMessage(
                    "ObjectFactory - can't remove class (not registered)", type));
        }

        void onDuplicateRegistered(const Type& type)
        {
            throw ObjectFactoryException(generateMessage(
                    "ObjectFactory - class already registered", type));
        }
    };

    // FACTORY

    /**
     * When declaring a factory class,
     * we indicate that we want to pass
     * not just some class as a parameter,
     * but a template class
     * @tparam Base
     * Abstract class for implementation classes
     * @tparam IdType
     * Type of values for identifying implementation classes
     * @tparam ObjectFactoryErrorPolicy
     */
    template < class Base, class IdType = int,
            template <class, class> class ObjectFactoryErrorPolicy = ObjectFactoryIgnoreErrorPolicy >
    class ObjectFactory : public ObjectFactoryErrorPolicy<Base, IdType>
    {
    protected:
        typedef AbstractCreator<Base> AbstractFactory;
        typedef std::map<IdType, AbstractFactory*> FactoryMap;

    public:
        ObjectFactory()
        = default;

        virtual ~ObjectFactory()
        {
            for (typename FactoryMap::iterator it = map.begin(), endIt = map.end(); it != endIt; ++it)
                delete it->second;
        }

        /**
         * A method that returns a reference to this object by the name
         * of the object of the implementation class
         * @param id
         * @return
         */
        std::shared_ptr<Base> create(const IdType& id) const
        {
            typename FactoryMap::const_iterator it = map.find(id);
            if (it != map.end())
                return it->second->create();
            return this->onCreateFailed(id);
        }

        /**
         * Registering an implementation class object -
         * or just adding it to an associative array
         * @tparam C
         * @param id
         */
        template <class C>
        void add(const IdType& id)
        {
            registerClass(id, new Creator<C, Base>);
        }

        /**
         * Removing an implementation class object
         * from an associative array
         * @param id
         */
        void remove(const IdType& id)
        {
            typename FactoryMap::iterator it = map.find(id);
            if (it != map.end())
            {
                delete it->second;
                map.erase(it);
            }
            else
                onRemoveFailed(id);
        }

        bool isRegistered(const IdType& id) const
        {
            return map.find(id) != map.end();
        }

        [[nodiscard]] size_t size() const { return map.size(); }

        ObjectFactory(const ObjectFactory&) = delete;
        ObjectFactory& operator= (const ObjectFactory&) = delete;

    protected:
        /**
         * Creating objects of the class, which we send
         * as template parameter to "add" method
         * @param id
         * @param pAbstractFactory
         */
        void registerClass(const IdType& id, AbstractFactory *pAbstractFactory) {
            std::unique_ptr<AbstractFactory> ptr(pAbstractFactory);
            typename FactoryMap::iterator it = map.find(id);
            if (it == map.end())
                map[id] = ptr.release();
            else
                this->onDuplicateRegistered(id);
        }

        FactoryMap map;
    };

}

#endif //OOP_OBJECTFACTORY_H
