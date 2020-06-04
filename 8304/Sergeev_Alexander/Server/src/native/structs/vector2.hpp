#ifndef LOGIC_VECTORS_H
#define LOGIC_VECTORS_H

#include "../base/interfaces.hpp"

namespace stts {
    // JSON
    namespace j_vector2 {
        const std::string x = TOSTRING(x); // : T where T : new()
        const std::string y = TOSTRING(y); // : T where T : new()
    }

    /// https://docs.unity3d.com/ScriptReference/Vector2.html
    /// \tparam T : value number
    template<typename T>
    class vector2 : public iserializable {
    public:
        T x;
        T y;

    public:
        explicit vector2 (T nx = 0, T ny = 0);
        explicit vector2 (json& package);
        vector2 (const vector2& other);
        vector2& operator= (const vector2& other);
        ~vector2 () override = default;
        void serialize (json& package) const override;
        void deserialize (json& package) override;

        vector2 operator- () const { return vector2(-x, -y); }

        vector2 operator+ (const vector2& other) const { return vector2(x + other.x, y + other.y); }

        vector2 operator- (const vector2& other) const { return vector2(x - other.x, y - other.y); }

        T operator* (const vector2& other) const { return x * other.x + y * other.y; }

        bool operator== (const vector2& other) const { return x == other.x && y == other.y; }

        bool operator!= (const vector2& other) const { return !(*this == other); }

        bool is_set ();

        /// \return squared length of the vector
        T sqr_magnitude () { return x * x + y * y; }

        /// \return length of the vector
        T magnitude () { return sqrtf(sqr_magnitude()); }
    };

    template<typename T>
    vector2<T>::vector2 (T nx, T ny) : x(nx), y(ny) { }

    template<typename T>
    vector2<T>::vector2 (json& package) {
        vector2::deserialize(package);
    }

    template<typename T>
    vector2<T>::vector2 (const vector2& other) : x(other.x), y(other.y) { }

    template<typename T>
    vector2<T>& stts::vector2<T>::operator= (const vector2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    template<typename T>
    void vector2<T>::serialize (json& package) const {
        package[j_vector2::x] = x;
        package[j_vector2::y] = y;
    }

    template<typename T>
    void vector2<T>::deserialize (json& package) {
        x = package[j_vector2::x].get<T>();
        y = package[j_vector2::y].get<T>();
    }

    template<typename T>
    bool vector2<T>::is_set () {
        return (x != -1) && (y != -1);
    }

}

#endif //LOGIC_VECTORS_H