#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
///////////////////////
/// Фигуры
/// Квадрат
/// Прямоугольный треугольник
/// Равнобедренный треуг.
///
///
/// Структура точек.
/////////////////

struct Point {
    std::vector<float> xs;
    std::vector<float> ys;
    int size;
    Point () :size(0) {}
};

struct line {
    std::vector<float> xl1;
    std::vector<float> yl1;
    std::vector<float> xl2;
    std::vector<float> yl2;
    std::vector<float> k;
    std::vector<float> b;
    std::vector<float> d;
    //std::vector<float> side;
    int size;
    line () :size(0) {}
    line (Point Array,std::vector<float> inputsize) :size(Array.size)
    {

        std::cout<<"CONST SIZE"<<size<<std::endl;
        for (int k=0;k<size;k++) {
            std::cout << "x= "<<Array.xs[k]<<" "<< "y= "<<Array.ys[k]<<std::endl;
        }
        for (int k=0;k<size;k++) {
            std::cout<<inputsize[k]<<" ";
        }
        std::cout<<std::endl;
        bool notSide=false;
        int c=0;
        for (int q=0;q<size;++q)
        {
            for(int j=1;j<(size-q);++j)
            {
                std::cout<<q<<" "<<j<<std::endl;
                float buffer=SizeSide(Array,q,q+j);
                std::cout<<"SIDE "<<buffer<<std::endl;
                for (int n=0 ;n<size;n++) {
                    if (buffer==inputsize[n])
                        break;
                    if ((buffer!=inputsize[n])&& (n==size-1) )
                        notSide=true;
                }
                if (!notSide) {
                    std::cout <<"!"<<std::endl;
                    std::cout << "xs1= "<<Array.xs[q]<<" "<< "ys1= "<<Array.ys[q]<<std::endl;
                    std::cout << "xs2= "<<Array.xs[q+j]<<" "<< "ys2= "<<Array.ys[q+j]<<std::endl;
                    float count1=(Array.ys[q]-Array.ys[q+j]);
                    std::cout << "count1= "<<count1<<std::endl;

                    float count2=(Array.xs[q]-Array.xs[q+j]);
                    std::cout << "count2= "<<count2<<std::endl;
                    // float buffer=((Array.ys[q]-Array.ys[q+j])/(Array.xs[q]-Array.xs[q+j]));
                    //   float buffer=((Array.ys[q]-Array.ys[q+j])/(Array.xs[q]-Array.xs[q+j]));
                    if (count1==0) {
                        k.push_back(0);
                        b.push_back(Array.xs[q]);
                        d.push_back(1);
                        xl1.push_back(Array.xs[q]);
                        yl1.push_back(Array.ys[q]);
                        xl2.push_back(Array.xs[q+j]);
                        yl2.push_back(Array.ys[q+j]);
                        c++;
                    }
                    if (count2==0) {
                        k.push_back(-1);
                        b.push_back(Array.xs[q]);
                        d.push_back(0);
                        xl1.push_back(Array.xs[q]);
                        yl1.push_back(Array.ys[q]);
                        xl2.push_back(Array.xs[q+j]);
                        yl2.push_back(Array.ys[q+j]);
                        c++;

                    }
                    if ((count1!=0)&& (count2!=0))
                    {
                        float buffer=(float) count1/count2;
                        //   std::cout << "K= "<<buffer<<std::endl;
                        k.push_back(buffer);
                        d.push_back(1);
                        buffer=Array.ys[q]-k[c]*Array.xs[q];
                        //  std::cout << "b= "<<buffer<<std::endl;
                        b.push_back(buffer);
                        xl1.push_back(Array.xs[q]);
                        yl1.push_back(Array.ys[q]);
                        xl2.push_back(Array.xs[q+j]);
                        yl2.push_back(Array.ys[q+j]);
                        c++;
                    }

                }
                notSide=false;

            }

        }
        //  for (int k=0;k<size;k++);


    }
private:
    float SizeSide(Point array, int pos1 , int pos2)
    {
        return sqrt(pow(array.xs[pos1]-array.xs[pos2],2.0)+pow(array.ys[pos1]-array.ys[pos2],2.0));

    }

};
////////////////
class Shape
{
public:
    Shape () :colour_(0), pointCount_(0),ID_(0) {}
    Shape(Point array)
    {

        if (array.xs.size()!=array.ys.size())
            throw std::invalid_argument("Not enought information ");
        if (!checkSame(array))
            throw std::invalid_argument("Shape have Equal points ");
        //std::vector<float> side;
        //countSides(side,array);
    }

    virtual  ~Shape() {

    }

    unsigned int getColour() const ;//взять цвет
    void setColour(unsigned int colour) ; //поставить цвет
    void turn(float angle);  //повернуть
    void expand(int size); //расширить
    void replaceShape (float mx, float my);//переставить
    virtual void showShape (std::ostream& os) const =0;  //показать фигуру
    int getPointCount() const;  //количество точек
    int getID() const; //ВЗЯТЬ ID ФИГУРЫ
    int setNextID();//ПОСТАВИТЬ id НОВОЙ
    friend std::ostream& operator<< (std::ostream& os, Shape& p); //ФУНКЦИЯ ДЛЯ ВЫВОДА ИНФОРМАЦИИ ЧЕРЕЗ ПОТОК (НЕ БЫЛО В ОРИГИНАЛЕ)
    virtual void countSides(std::vector<float> &side, Point array)=0;
    bool similar(const Shape &sh1, const Shape &sh2);
    bool sameShape(const Shape &sh1) const;
    bool sameShape( Point &array) const ;
    bool sameShape(Point &array, const Shape &sh1, const Shape &sh2) const ;
    virtual  float area()=0;
    bool itSide (float tside)
    {
        for (int count=0;count<pointCount_;++count) {
            if (tside==side[count])
                return true;
        }
        return false ;
    }

    void findCenter(std::vector<float> center);
protected:
    int  colour_; //ЦВЕТ
    int pointCount_; //кОЛИЧЕСТВО ТОЧЕК
    int ID_; //ID ФИГУРЫ
    static int nextID_; //ПЕРЕМЕННАЯ , КОТОРАЯ СТАВИТ id (СМОТРИ , ЧТО ТАКОЕ STATIC)

    Point point_;

    std::vector<float> side;
    float area_;
    bool checkSame(Point array);
    void makePoint(Point array) ;
    bool insidePoint (float ix, float iy, const  Shape &shape) const;
    void cross(line lin1,int pos1 , line lin2,int pos2,Point &pointer,const Shape &sh);

    //  bool similar();


};
int Shape::nextID_=0; //ИНИЦИАЛИЗАЦИЯ ID
class Triangle: public Shape
{

public:
    Triangle () //:Shape()
    {

        colour_=0;
        pointCount_=3;
        ID_=0;
    }
    Triangle (Point array):Shape(array)
    {


        pointCount_=3;
        if (array.size!=pointCount_)
            throw std::invalid_argument("Not enought/Too much points ");
        // std::vector<float> side;
        countSides(side,array);
        area_=area();
        makePoint(array);
    }

    void showShape(std::ostream &os) const override
    {
        os<<"I'm Triangle"<<std::endl;
        for (int i=0;i<pointCount_;++i) {
            os<<"POINT "<<i+1<<"("<<point_.xs[i]<<";"<<point_.ys[i]<<")"<<std::endl;
        }
    }
    float area() override {
        float per=0;
        for (int count=0;count<pointCount_;++count)
            per+=side[count];
        per=per/2;
        return sqrt(per*(per-side[0])*(per-side[1])*(per-side[2]));


    }
    void countSides(std::vector<float> & side, Point array) override
    {
        side.push_back(sqrt(pow(array.xs[0]-array.xs[1],2.0)+pow(array.ys[0]-array.ys[1],2.0))) ;//

        side.push_back(sqrt(pow(array.xs[0]-array.xs[2],2.0)+pow(array.ys[0]-array.ys[2],2.0)));//

        side.push_back(sqrt(pow(array.xs[1]-array.xs[2],2.0)+pow(array.ys[1]-array.ys[2],2.0)));//

    }

protected:


};
//int Triangle::pointCount_=3;

std::ostream& operator<< (std::ostream& os, Shape& p)
{
    p.showShape(os);
    return os;
}
///////////////////////////////////////

unsigned int Shape::getColour() const
{
    return colour_;
}
////////////////////////////////////

int Shape::getPointCount() const
{
    return pointCount_;
}
////////////////////////////////////
void Shape::setColour(unsigned int colour)
{
    colour_=colour;
}
///////////////////////////////////
void Shape::findCenter(std::vector<float>center)
{

    //Используется матрица переворота .
    for (int i=0;i<pointCount_;++i) {
        center[0]+=point_.xs[i];
        center[1]+=point_.ys[i];
    }
    center[0]/=pointCount_;
    center[1]/=pointCount_;
}
bool Shape::checkSame(Point array) {

    for (int q=0 ;q<array.size-1;++q) {
        for (int k=1;k<array.size-q;++k) {
          //  std::cout<<array.xs[q]<<" "<<array.ys[q]<< " and " <<array.xs[q+k]<< " "<<array.ys[q+k]<<std::endl;
            if ((array.xs[q]==array.xs[q+k])&& (array.ys[q]==array.ys[q+k])) {

                return false;
            }

        }
    }

    return true;
}

////////////////////////////////////
void Shape::turn(float angle)
{
    std::vector<float> center= {0,0};
    findCenter(center);
    for (int i=0;i<pointCount_;++i) {
        point_.xs[i]=(point_.xs[i]-center[0])*cos(angle)-(point_.ys[i]-center[1])*sin(angle);
        point_.ys[i]=(point_.xs[i]-center[0])*sin(angle)+(point_.ys[i]-center[1])*cos(angle);
    }
}
////////////////////////////////////
void Shape::expand(int size)
{
    std::vector<float> center= {0,0}; //x,y
    findCenter(center);
    for (int i=0;i<pointCount_;++i) {
        point_.xs[i]= (point_.xs[i]-center[0])*size+center[0];
        point_.ys[i]=(point_.ys[i]-center[1])*size+center[1];
    }
    for (int count=0;count<pointCount_;++count)
        side[count]=side[count]*size;
    area_=area();
}

////////////////////////////////////
void Shape::replaceShape (float mx, float my )
{
    for (int i=0;i<pointCount_;++i) {
        point_.xs[i]=point_.xs[i]+mx;
        point_.ys[i]=point_.ys[i]+my;
    }
}
////////////////////////////////////
void Shape::makePoint(Point array)
{

    int count=array.size;
    if ((!point_.xs.empty())&&(!point_.ys.empty()))
    {

        point_.xs.clear();
        point_.ys.clear();
    }
    while (count!=0) {
        point_.xs.push_back(array.xs[count-1]);
        point_.ys.push_back(array.ys[count-1]);
        count--;
    }
    point_.size=array.size;


}
////////////////////////////////////
int Shape::getID() const
{
    return ID_;
}
////////////////////////////////////
int Shape::setNextID()
{
    nextID_++;
    return nextID_;
}
////////////////////////////////////

class Square:public Shape
{
public:
    Square () :Shape()
    {

        //colour_=0;
        pointCount_=4;
        // ID_=0;
    }
    Square(Point array) :Shape(array) {


        pointCount_=4;

        if (array.size!=pointCount_)
            throw std::invalid_argument("Not enought/Too much points ");
        //std::vector<float> side;
        countSides(side,array);
        for (int i=0 ;i<pointCount_;i++) {
            if (side[0]!=side[i])
                throw std::invalid_argument("Sides not equal ");
        }

        colour_=0;

        makePoint(array);
        area_=area();

        ID_=setNextID();
    }
    ~Square() {

    }

    void showShape(std::ostream &os) const override
    {
        os<<"I'm Square"<<std::endl;
        for (int i=0;i<pointCount_;++i) {
            os<<"POINT "<<i+1<<"("<<point_.xs[i]<<";"<<point_.ys[i]<<")"<<std::endl;
        }
    }
    float area() override
    {
        return side[0]*side[0];
    }
    virtual void countSides(std::vector<float> &side, Point array) override
    {   side.push_back(sqrt(pow(array.xs[0]-array.xs[1],2.0)+pow(array.ys[0]-array.ys[1],2.0))) ;//
        side.push_back(sqrt(pow(array.xs[0]-array.xs[2],2.0)+pow(array.ys[0]-array.ys[2],2.0)));//
        side.push_back(sqrt(pow(array.xs[0]-array.xs[3],2.0)+pow(array.ys[0]-array.ys[3],2.0)));//
        side.push_back(sqrt(pow(array.xs[2]-array.xs[3],2.0)+pow(array.ys[2]-array.ys[3],2.0))) ;//
        side.push_back(sqrt(pow(array.xs[1]-array.xs[3],2.0)+pow(array.ys[1]-array.ys[3],2.0)));//
        side.push_back(sqrt(pow(array.xs[1]-array.xs[2],2.0)+pow(array.ys[1]-array.ys[2],2.0)));//
        float maxSide=side[0];
        // std::for_each(side.begin(),side.end(),[](float &n) {maxSide=max(n,maxSide)});
        int count=2;
        while (count!=0) {
            for (auto i=0 ;i<array.size;i++) {
                maxSide=std::max(maxSide,side[i]);
            }

            for (auto i=0 ;i<array.size;i++) {
                if (maxSide==side[i])
                    std:: swap(side[i],side[side.size()-1]);
                //  side[i].swap(side[3]) ;
            }
            side.pop_back();
            count--;
        }


    }


};

class RightTriangle: public Triangle
{
public:

    RightTriangle () :Triangle()
    {

        // colour_=0;
        // pointCount_3;
        //  ID_=0;
    }
    RightTriangle(Point array) :Triangle(array) {
        /*
        if (array.size!=3)
            throw std::invalid_argument("Not enought/Too much points");
        pointCount_=3;
        if (!checkSame(array))
            throw std::invalid_argument("Shape have Equal points ");


        // std::vector <float> side;
        countSides(side,array);
*/

        float maxSide=side[0];
        //проверка на свойства прямоугольного треугольника
        //Поиск гипотинузы .Далее проверка Т Пифагора

        if ((side[0]==side[1])&&(side[0]==side[2])&&(side[2]==side[1]))
            throw std::invalid_argument ("sides are same");
        for (int i=1;i<pointCount_;++i)
        {
            maxSide=std::max(maxSide,side[i]);

        }


        if (maxSide!=side[0])
        {
            if (maxSide!=side[2])
                std::swap(side[0],side[1]);
            else
                std::swap(side[0],side[2]);

        }

        float hyp=sqrt(pow(side[1],2.0)+pow(side[2],2.0));
        if (side[0]!=hyp)
            throw std::invalid_argument ("T.Pifagor wrong");

        /* else {
            if ((side[0]>side[1])&&  (side[0]>side[2])) {
                buffer=sqrt(pow(side[1],2.0)+pow(side[2],2.0));
                if (side[0]!=buffer)
                    throw std::invalid_argument ("T.Pishagor wrong");
            }
            if ((side[1]>side[0])&&  (side[1]>side[2])) {
                buffer=sqrt(pow(side[2],2.0)+pow(side[0],2.0));
                if (side[1]!=buffer)
                    throw std::invalid_argument("T.Pishagor wrong");
            }
            if ((side[2]>side[1])&&(side[2]>side[0])) {
                buffer=sqrt((pow(side[1],2.0)+pow(side[0],2.0)));
                if (side[2]!=buffer)
                    throw std::invalid_argument ("T.Pishagor wrong");
            }

        }
        */
        colour_=0;
        makePoint(array);
        ID_=setNextID();

    }
    ~RightTriangle() {


    }

    void showShape(std::ostream &os) const  override
    {
        os<<"I'm Right Triangle"<<std::endl;
        for (int i=0;i<pointCount_;++i) {
            os<<"POINT "<<i+1<<"("<<point_.xs[i]<<";"<<point_.ys[i]<<")"<<std::endl;
        }

    }

};
////////////////////////////////////

class IsoscelesTriangle:public Triangle
{
public:
    IsoscelesTriangle () :Triangle()
    {

        //   colour_=0;
        //pointCount_=3;
        //  ID_=0;
    }
    IsoscelesTriangle(Point array) : Triangle(array) {
        /*
        if (array.size!=3)
            throw std::invalid_argument("Not enought/Too much points");
        pointCount_=3;
        //Проверка на сопадение точек

        if (!checkSame(array))
            throw std::invalid_argument("Shape have Equal points ");

        countSides(side,array);
        */
        //Проверка на свойства Равнобндренного тр-ка

        if  ((side[0]!=side[1]) && (side[1]!=side[2]) &&(side[0]!=side[2]))
            throw std::invalid_argument("Not Isoscellence");

        colour_=0;
        makePoint(array);

        ID_=setNextID();
    }
    ~IsoscelesTriangle() {


    }

    void showShape(std::ostream &os) const override
    {
        os<<"I'm IsoscelesTriangle"<<std::endl;
        for (int i=0;i<pointCount_;++i) {
            os<<"POINT "<<i+1<<"("<<point_.xs[i]<<";"<<point_.ys[i]<<")"<<std::endl;
        }
    }


};
bool Shape::similar(const Shape &sh1, const Shape &sh2)
{
  //  std::cout<<"STEP1"<<std::endl;
    if (sameShape(sh1))
        return true;
   // std::cout<<"STEP2"<<std::endl;
    Point NewPoint;
    line lin1(sh1.point_,sh1.side);
    line lin2(sh2.point_,sh2.side);
    for (int test=0;test<sh1.pointCount_;test++)
    {
        std::cout<<"lin1 d "<<lin1.d[test]<<" k "<<lin1.k[test]<<" b "<<lin1.b[test]<<std::endl;
    }
    for (int test=0;test<sh2.pointCount_;test++)
    {
        std::cout<<"lin2 d "<<lin2.d[test]<<" k "<<lin2.k[test]<<" b "<<lin2.b[test]<<std::endl;
    }
    // Point NewPoint();
  //  std::cout<<"STEP3"<<lin1.size<<lin2.size<<std::endl;
    for (int count=0;count<sh1.pointCount_;count++) {

        if (!insidePoint(sh1.point_.xs[count],sh1.point_.ys[count],sh2)) {
         //   std::cout<<"notInside"<<std::endl;
            NewPoint.xs.push_back(sh1.point_.xs[count]);
            NewPoint.ys.push_back(sh1.point_.ys[count]);
            NewPoint.size++;
        }
    }
    std::cout<<"STEP4 "<<NewPoint.size<<std::endl;
    for (int l=0; l<NewPoint.size;l++)
        std::cout<<NewPoint.xs[l]<<" "<< NewPoint.ys[l]<<std::endl;
    if ((NewPoint.size>pointCount_) || (NewPoint.size==0))
        return false;
    std::cout<<"STEP5"<<std::endl;

    for (int count1=0;count1<lin1.size;count1++) {
        for (int count2=0;count2<lin2.size;count2++) {
            cross(lin1,count1,lin2,count2,NewPoint,sh1);

        }

    }

    std::cout<<"STEP6"<<NewPoint.size<<std::endl;
    for (int p=0;p<NewPoint.size;p++)
      //  std::cout<<"NP "<< NewPoint.xs[p]<<" " << NewPoint.ys[p] << std::endl;
    if (NewPoint.size>pointCount_) {
        if (sameShape(NewPoint,sh1,sh2))
            return true ;
        else return false ;
    }

   // std::cout<<"STEP7"<<std::endl;
    if (sameShape(NewPoint))
        return true;
    else
        return false;
}
bool Shape:: insidePoint (float ix, float iy,  const Shape &shape) const
{

    for (int i=0;i<pointCount_;++i) {
        if ((shape.point_.xs[i]==ix) && (shape.point_.ys[i]==iy))
            return true ;
    }

    float S=0;
    Point buffer;
    buffer.size=1;
    buffer.xs.push_back(ix);
    buffer.ys.push_back(iy);
    bool test=false;
    for (int count1=0;count1<shape.pointCount_;++count1) {
        for (int count2=1;count2+count1<shape.pointCount_;++count2) {
            float tside=(sqrt(pow(shape.point_.xs[count1]-shape.point_.xs[count1+count2],2.0)+pow(shape.point_.ys[count1]-shape.point_.ys[count2+count1],2.0)));
           // std::cout<<"SIDE "<<tside<<std::endl;
            for (int count=0;count<shape.pointCount_;++count) {
                if (tside==shape.side[count])
                    test= true;
            }

            if (test) {
            //    std::cout<<"WAS FOUND TRIANGLE"<<std::endl;
                buffer.xs.push_back(shape.point_.xs[count1]);
                buffer.ys.push_back(shape.point_.ys[count1]);
                buffer.size++;
                buffer.xs.push_back(shape.point_.xs[count1+count2]);
                buffer.ys.push_back(shape.point_.ys[count1+count2]);
                buffer.size++;

               // for (int p=0;p<buffer.size;++p)
              //      std::cout<<"TRIANGLE STUFF X "<<buffer.xs[p]<< " Y "<<buffer.ys[p]<<std::endl;
           //     std::cout<<"buffer size"<<buffer.size<<std::endl;
                Triangle triangle (buffer);

                S=S+triangle.area_;
                test=false;
                //Triangle.~Shape();
                for (int i=buffer.size;i!=1;--i) {
                    buffer.xs.pop_back();
                    buffer.ys.pop_back();
                    buffer.size--;
                }
            //    std::cout<<"AFTER"<<buffer.size<<std::endl;




            }
        }

    }

    if (S==shape.area_)
        return true;
    else
        return false;

}
bool Shape::sameShape(const Shape &sh1) const
{
    if (pointCount_!=sh1.pointCount_)
        return false;
    else
    {
        int count=0;
        for (int i=0;i<pointCount_;++i) {
            for (int q=1;q<pointCount_-i;++q) {
                if ((sh1.point_.xs[i]==point_.xs[i+q]) &&  (sh1.point_.ys[i]==point_.ys[i+q]))
                    ++count;
            }
        }
        if (count==pointCount_)
            return true;
        else
            return false;
    }
}
bool Shape::sameShape(Point &array) const
{
    if (pointCount_!=array.size)
        return false;
    else {
        int count=0;
        for (int i=0;i<pointCount_;++i) {
            for (int q=1;q<pointCount_-i;++q) {
                if ((array.xs[i]==point_.xs[i+q]) &&  (array.ys[i]==point_.ys[i+q]))
                    ++count;
            }
        }
        if (count==pointCount_)
            return true;
        else
            return false;

    }
}

bool Shape::sameShape(Point &array, const Shape &sh1, const Shape &sh2) const
{
    Point TroublePoint;
    int truecount=0;
    for (int i=0 ; i<array.size;i++)
    {  bool check=false;
        for (int q=0;q<pointCount_;q++) {
            if ((array.xs[i]==point_.xs[q]) &&(array.ys[i]==point_.ys[q]))
            {
                check=true;
                truecount++;
            }
        }
        if (!check)
        {
            TroublePoint.size++;
            TroublePoint.xs.push_back(array.xs[i]);
            TroublePoint.ys.push_back(array.ys[i]);

        }
        check=false;


    }
    if (truecount!=pointCount_)
        return false ;
    int count=0;
    for (int i=0; i<TroublePoint.size;i++)
    {
        for (int q=0 ;q<sh1.pointCount_;q++)
            if ((TroublePoint.xs[i]==sh1.point_.xs[q]) &&(TroublePoint.ys[i]==sh1.point_.ys[q]))
                count++;


        for (int q=0 ;q<sh2.pointCount_;q++)
            if ((TroublePoint.xs[i]==sh2.point_.xs[q]) &&(TroublePoint.ys[i]==sh2.point_.ys[q]))
                count++;
        if (count==0)
            return false ;
        count=0;

    }
    return true;


}

////////////////////////
void Shape ::cross(line lin1,int pos1 , line lin2,int pos2,Point &pointer,const Shape &sh)
{   // std::cout<<"LINE 1: d "<<lin1.d[pos1]<<" k "<<lin1.k[pos1] <<" b "<<lin1.b[pos1]<<std::endl;
   //  std::cout<<"LINE 2: d "<<lin2.d[pos2]<<" k "<<lin2.k[pos2] <<" b "<<lin2.b[pos2]<<std::endl;
      if ((lin1.d[pos1]==lin2.d[pos2])&&(lin1.b[pos1]!=lin2.b[pos2]) && (lin1.k[pos1]==lin2.k[pos2]))
          // | | -no cross
          return;


      if ((lin1.d[pos1]==lin2.d[pos2])&&(lin1.k[pos1]==lin2.k[pos2]) && (lin1.b[pos1]==lin2.b[pos2])) {
          // same. no cross,but....
          //   bool pointinside1=insidePoint(lin1.xl1[pos1],lin1.yl1[pos1],lin2);
          //   bool pointinside2=insidePoint(lin1.xl2[pos1],lin1.yl2[pos1],lin2);
          //  if ( (pointinside1)&& (pointinside2)) {
          //      pointer.xs.push_back(crossX);
          //      pointer.ys.push_back(crossY);
          //      pointer.size++;
          return;
          //   }



      }
      float crossX;
       float crossY;
        //  if ((lin1.k[pos1]!=lin2.k[pos2]) && (lin1.b[pos1]!=lin2.b[pos2])) {
        if (lin2.d[pos2]==0)
        {

            crossX=-lin2.b[pos2]/lin2.k[pos2];
            crossY=(lin1.k[pos1]*crossX+lin1.b[pos1]);



        }
        else {
            if ((lin2.d[pos2]*lin1.k[pos1]-lin2.k[pos2]*lin1.d[pos1])==0) {
                if (lin2.k[pos2]==0) {
                    crossY=lin2.b[pos2];
                    crossX=(lin1.d[pos1]*crossY-lin1.b[pos1])/lin1.k[pos1];
                }

                else {
                    crossY=lin2.b[pos2]/lin2.d[pos2];
                    crossX=(lin1.d[pos1]*crossY-lin1.b[pos1])/lin1.k[pos1];
                }
            }
            else {

                // crossX=(-in1.b[pos1]+lin2.b[pos2])/(lin1.k[pos1]-lin2.k[pos2]);
                // crossY=(lin1.k[pos1]*crossX+lin1.b[pos1]);
                crossX=(lin2.b[pos2]*lin1.d[pos1]-lin2.d[pos2]*lin1.b[pos1])/(lin2.d[pos2]*lin1.k[pos1]-lin2.k[pos2]*lin1.d[pos1]);
                crossY=(lin2.k[pos2]*crossX+lin2.b[pos2])/lin2.d[pos2];

            }
        }
         std::cout<<"JOB  X "<<crossX<<" Y " <<crossY<< std::endl;
          bool check=false;
           for (int q=0;q<pointer.size;q++)
           {
               if ((crossX==pointer.xs[q]) && (crossY==pointer.ys[q]))
                   check=true;
           }
            if (!check)
            {
                bool step=false;
                for (int i=0;i<sh.pointCount_;i++) {
                    if((sh.point_.xs[i]==crossX) && (sh.point_.ys[i]==crossY)) {
                        pointer.xs.push_back(crossX);
                        pointer.ys.push_back(crossY);
                        pointer.size++;
                    }
                    step=true;
                }
                if (!step) {
                    if (insidePoint(crossX,crossY,sh)) {
                        pointer.xs.push_back(crossX);
                        pointer.ys.push_back(crossY);
                        pointer.size++;
                    }
                }


            }
            return;
             //  }
}


#endif // SHAPE_H
