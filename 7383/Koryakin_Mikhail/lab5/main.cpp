#include <iostream>


  template <typename T>
  class shared_ptr{
      template <typename D>
      friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr=0){
         s_ptr = ptr;
         if (s_ptr != nullptr)
            counter = new int(1);
         else
            counter  = nullptr;

      }

    ~shared_ptr(){
      del();
    }


    shared_ptr(const shared_ptr & other) : s_ptr(other.s_ptr), counter(other.counter){
      ++(*counter);
    }

    template <typename D>
    shared_ptr(const shared_ptr<D> & other) : s_ptr(other.s_ptr), counter(other.counter){
         ++(*counter);
    }


     shared_ptr& operator=(const shared_ptr & other){
         if(other.s_ptr != s_ptr){
             del();
             s_ptr = other.s_ptr;
             counter = other.counter;
             ++(*counter);
         }
         return *this;
     }


     template <typename D>
     shared_ptr& operator=(const shared_ptr<D> & other){
         if(other.s_ptr != s_ptr){
            del();
            s_ptr = other.s_ptr;
            counter = other.counter;
            ++(*counter);
          }
          return *this;
        }

    template <typename D>
    bool operator == (const shared_ptr<D> & other) const{
         return s_ptr == other.s_ptr;
    }


    template <typename D>
    bool operator != (const shared_ptr<D> & other) const{
         return !(s_ptr == other.s_ptr);
    }


    explicit operator bool() const{
      return s_ptr != nullptr;
    }

    T* get() const{
      return s_ptr;
    }


    long use_count() const{
      return s_ptr == nullptr ? 0 : *counter;
    }

    T& operator*() const{
      return *s_ptr;
    }


    T* operator->() const{
      return s_ptr;
    }

    void swap(shared_ptr& x) noexcept{
        T* tmp = s_ptr;
        int* tmp_c = counter;
        s_ptr = x.s_ptr;
        counter = x.counter;
        x.s_ptr = tmp;
        x.counter = tmp_c;
    }

    void reset(T *ptr = 0){
      del();
      this->s_ptr = ptr;
      this->counter = new int(1);
    }

  private:

      T* s_ptr;
      int* counter;
      void del(){
          if(s_ptr != nullptr){
              if(*counter == 1){
                  delete counter;
                  delete s_ptr;
                  s_ptr = nullptr;
              }
              else
                  --(*counter);
          }
      }
  };

class Figure {
    int a;
    int b;
public:
    Figure(int a, int b): a(a), b(b) {}
    void print() {std::cout << a << " " <<b <<std::endl;}
    void set(int v) {a = v; b = v+1;}
};

int main(){
        Figure *a = new Figure(1,2);
{
        shared_ptr<Figure> ptr(a);

     /*   ptr->print();
        ptr->set(5);
        ptr->print();*/
        shared_ptr<int> ptr2(ptr);

        //shared_ptr<Figure> ptr2(a);
       // ptr2->print();
        std::cout << ptr.use_count() << " " << ptr2.use_count() <<std::endl;
}
    return 0;
}


