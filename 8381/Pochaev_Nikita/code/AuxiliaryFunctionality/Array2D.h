#ifndef OOP_ARRAY2D_H
#define OOP_ARRAY2D_H

#include "Vector.h"
#include "GameField/Cell.h"
#include <cstdio>

namespace cds
{
    /**
     * The main advantage: memory allocation as a single block,
     * as in a static C array
     * @tparam T
     */
    template<typename T>
    class Array2D
    {
    public:
        Array2D(size_t w, size_t h) : width(w), height(h), data(w * h)
        {
            for(size_t i = 0; i < data.capacity(); i++)
            {
                data.push_back(std::make_shared<Cell>());
            }
        }
        Array2D(const Array2D& arr) : data(arr.data), width(arr.width), height(arr.height)
        {
        }
        Array2D(Array2D&& arr) noexcept : width(arr.width), height(arr.height), data(std::move(arr.data))
        {
        }

        ~Array2D() = default;

            class Row2D
            {
                friend class Array2D;

            public:
                T& operator[] (size_t col)
                {
                    // return parent.data() + col * parent.getHeight() + row;
                    return parent->data[col * parent->getHeight() + row];
                }

                const T& operator[] (size_t col) const
                {
                    // return parent.data() + col * parent.getHeight() + row;
                    return parent->data[col * parent->getHeight() + row];
                }

            private:
                Row2D(const Array2D<T>* parent_, size_t row_) :
                    row(row_)
                {
                    parent = parent_;
                }

                const Array2D<T> *parent;
                size_t row;
            };

        Row2D operator[] (size_t row)
        {
            return Row2D(this, row);
        }

        Row2D operator[] (size_t row) const
        {
            return Row2D(this, row);
        }

        // T *operator[](size_t i) { return data.data() + i * height; }
        // const T *operator[](size_t i) const { return data.data() + i * height; }

        Array2D& operator= (const Array2D& arr)
        {
            data = arr.data;
            width = arr.width;
            height = arr.height;

            return *this;
        }

        Array2D& operator= (Array2D&& arr) noexcept
        {
            data = arr.data;
            width = arr.width;
            height = arr.height;

            return *this;
        }

        [[nodiscard]] size_t getWidth() const { return width; }
        [[nodiscard]] size_t getHeight() const { return height; }

    private:
        cds::Vector<T> data;
        size_t width;
        size_t height;
    };
}

#endif //OOP_ARRAY2D_H
