#ifndef OOP_GAMEFIELDITERATOR_H
#define OOP_GAMEFIELDITERATOR_H

/**
 * IT WOULDN'T WORK WITH SHARED_PTR!!!
 */

#include <iterator>
#include <memory>

template<typename ValueType>
/**
 * @tparam std::input_iterator_tag
 *
 * An empty class: it has no member functions,
 * member variables, or nested types.
 * It is used solely as a "tag": a representation of
 * the Input Iterator concept within the C++ type system
 * @tparam ValueType
 *
 * The type of value that is stored and returned by operators: * and ->
 */
class GameFieldIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
    friend class GameField;
private:
    explicit GameFieldIterator(ValueType &p) : p(p) { };
public:
    /**
     * @param it
     * Pointer to an array element
     * stored in GameField
     */
    GameFieldIterator(const GameFieldIterator &it) : p(it.p) { };

    bool operator!= (GameFieldIterator const& other) const
    {
        return p != other.p;
    }

    // need for BOOST_FOREACH
    bool operator== (GameFieldIterator const& other) const
    {
        return p == other.p;
    }

    typename GameFieldIterator::reference operator* () const
    {
        return *p;
    }
    typename GameFieldIterator::pointer operator-> () const
    {
        return &p;
    }
    GameFieldIterator& operator++ ()
    {
        ++p;
        return *this;
    }
private:
    ValueType p;
};

#endif //OOP_GAMEFIELDITERATOR_H
