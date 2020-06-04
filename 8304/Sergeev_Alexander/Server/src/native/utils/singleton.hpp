#ifndef LOGIC_SINGLETON_HPP
#define LOGIC_SINGLETON_HPP

namespace utils {
    template<class Derived>
    class singleton {
    protected:
        singleton () { }

    public:
        // For sum kind o safety.
        singleton (const singleton<Derived>&) = delete;
        singleton<Derived>& operator= (const singleton<Derived>&) = delete;

        static Derived& get () {
            static Derived theInstance;
            return theInstance;
        }
    };
}


#endif //LOGIC_SINGLETON_HPP
