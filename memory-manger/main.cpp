#include <iostream>
using namespace std;
const int m = 10;
const int n = 10;

class Box
{
   public:
      Box() {
         cout << "creat object" <<endl;
      }
      ~Box() {
         cout << "free object" <<endl;
      }
};

int main ()
{
   double*    pVar  = new double; // 为变量请求内存
   *pVar = 29494.99;     // 在分配的地址存储值
   cout << "Value of pvalue : " << *pVar << endl;
   delete pVar;         // 释放内存

   char* pArray  = new char[20];   // 为变量请求内存
   delete [] pArray;        // 删除 pvalue 所指向的数组

   int *array=new int [m];   // 动态分配,数组长度为 m
   delete [] array;   //释放内存


   Box* myBoxArray = new Box[4];
   delete [] myBoxArray; // 删除对象
   return 0;
}
