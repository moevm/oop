#include <QCoreApplication>
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>

using namespace std;

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
      cout << "Constructor " << this << endl;
  }

  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }

    //////////////
    ~Array(){
      cout << "Destructor " << this << endl;
            delete [] m_array;
    }

    Array(const Array &other){
        cout << "Copy constructor " << this << endl;
            this->m_size = other.m_size;
            m_array = new T[this->m_size];

            for(size_t i = 0; i<this->m_size; i++)
                this->m_array[i] = other.m_array[i];
    }

    Array & operator = (const Array &other){
        cout << "Operator = " << endl;
        size_t saveSize = this->m_size;
        T saveArr[saveSize];
        std::copy(this->m_array, this->m_array+saveSize, saveArr);

        if(this != &other){
            try {
                delete [] m_array;
                m_size = other.m_size;
                m_array = new T[other.m_size];
                std::copy(other.m_array, other.m_array + other.m_size, m_array);
            }
            catch(...) {
                printf("Catch\n");
                if(this->m_array != nullptr)
                    delete [] this->m_array;
                this->m_size = saveSize;
                this->m_array = new T[saveSize];
                std::copy(saveArr, saveArr+saveSize, this->m_array);
            }
        }
        return *this;
    }

    Array & operator = (Array &&other){
        if(this != &other){
            delete [] m_array;
            m_size = other.m_size;
//            m_array = new T[m_size];
            m_array = other.m_array;
//            std::copy(other.m_array, other.m_array + m_size, m_size);

            other.m_size = 0;
            delete [] other.m_array;
            other.m_array = nullptr;// a = move(a);
        }
        return *this;
    }

    Array(Array &&other){
        cout << "Move constructor " << this << endl;
        this->m_size = other.m_size;
        this->m_array = other.m_array;
        other.m_size = 0;
        other.m_array = nullptr;
    }
    //////////////

    void printArr(){
        for(size_t i=0; i<m_size; i++)
            cout << m_array[i] << " " << endl;
    }

private:
  size_t m_size;
  T* m_array;
};

void foo(Array<int> arr2){
    arr2.printArr();
    Array<int> arr1(5);
    for(int i=0; i<5; i++)
        arr1[i] = i*2;

    arr1.printArr();

    arr1 = arr2;

    arr1.printArr();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
/*
    Array<int> arr2(10);
    for(int i=0; i<10; i++)
        arr2[i] = i;
    foo(arr2);
*/

    Array<int> A(10);
    A = move(A);

    return a.exec();
}

