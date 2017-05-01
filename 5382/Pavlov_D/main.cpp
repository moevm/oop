#include <iostream>
//#include "lr2.h"
#include "shape.h"
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{

   Point array;
   int size =4;
   int x;
   int y;

   for (int i=0;i<size-1;i++)
   {       cin>>x;
       cin>> y;
       array.xs.push_back(x);
       array.ys.push_back(y);
   }

   array.size=3;

  RightTriangle s(array);
cout<<s;
Point array1;
for (int i=0;i<size;i++)
{   cin>>x;
    cin>> y;
    array1.xs.push_back(x);
    array1.ys.push_back(y);
}

array1.size=4;
Square q(array1);
cout<<q;
//cout<<"S "<<q.area();
Point array2;
for (int i=0;i<size-1;i++)
{   cin>>x;
    cin>> y;
    array2.xs.push_back(x);
    array2.ys.push_back(y);
}



array2.size=3;
RightTriangle z(array2);
cout<<z;
std::cout<<"BEGIIIIN"<<std::endl;
cout<<s;
cout<<q;
cout<<z;


cout<<"Similar or not "<<s.similar(q,z)<<endl;;

    cout << "Hello World!!!!!!" << endl;

    return 0;

}
