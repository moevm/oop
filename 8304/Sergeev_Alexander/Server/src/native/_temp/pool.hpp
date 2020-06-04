#ifndef LOGIC_POOL_H
#define LOGIC_POOL_H

#include <stack>
#include <memory>
#include "../base/errors.hpp"

template<typename T> // Where T : new(), idisposable (?)
class pool {
private:
    std::stack<std::shared_ptr<T>> items;

public:
    explicit pool ();
    std::shared_ptr<T> get ();
    void recycle (std::shared_ptr<T> item);
    ~pool ();
};

template<typename T> pool<T>::pool () {
    items = std::stack<std::shared_ptr<T>>();
}

template<typename T> std::shared_ptr<T> pool<T>::get () {
    if (items.size() > 0)
    {
        std::shared_ptr ptr = items.top();
        items.pop();
        return ptr;
    }
    else
    {
        return std::make_shared<T>();
    }

}

template<typename T> void pool<T>::recycle (std::shared_ptr<T> item) {
    // Recycle only items without other references
    if (static_cast<int>(item.use_count) > 1)
        throw ;//shared_pointer_exception("pool error");
    // TODO maybe item.dispose()
    items.push(item);
}

template<typename T> pool<T>::~pool () {
    // TODO
}

#endif //LOGIC_POOL_H