#include <iostream>
#include <ctime>
using namespace std;


void getSeconds(unsigned long *par); // 在写函数时应习惯性的先声明函数，然后在定义函数
int * getRandom();

int main ()
{
   // 指针声明和赋值
   int  var = 20;   // 实际变量
   int  *ip;        // 指针变量ip 引用：int& a = b；
   float  *fp = NULL; // float 指针 fp 的声明 未使用的指针一般初始化为NULL，避免野指针

   ip = &var;       // 在指针变量 ip 中存储 var 的地址


   cout << "Value of var variable: " << var << endl;    //变量值
   cout << "Address of var variable: " << &var << endl; //变量地址


   cout << "Address stored in ip (int pointer) variable: " << ip << endl;  //指针值 （相当于一个地址）
   cout << "Value of *ip variable: " << *ip << endl;    // 指针值对应内存的存储值

   cout << "Value of fp variable:" << fp << "\n" << endl;  //
//   cout << "Value of *fp variable: " << *fp << endl; //内存地址为0处不可访问

// 指针运算 概念说明：指针常量：本质是常量但是指针类型的 = 指针不能改变（int * const p）const修饰p；常量指针：本质是指针但是指向的是个常量 = 指针指向的值不能改变（const int *p|int const* p） const修饰int
//  其他（const int * const b = &a） //指向常量的指针常量

   const int MAX = 3; //MAX的值不可变 MAX是常量整数
   int  array[MAX] = {10, 100, 200}; // array 是一个指针常量，不可改变，但是指向的值可以改变

   *array = 5;
   *(array+1) = 50;
   *(array+2) = 500; //指针常量作为索引，访问或者修改其指向的内存值
//   array++; //不可以加减，指针常量不能变化

   int  *ptr; //ptr = Pointer 指针变量代替数组，因为变量指针可以递增，而数组不能递增
   ptr = array;// 数组名=第一个元素的地址，相当于 ptr = &array[0]，是一个指针常量（指针类常量）
   int i = 0;
   while ( ptr <= &array[MAX - 1] ) // 具体到哪个数组元素就需要取地址符&  比如&array[2] 第三个元素
   {
       cout << "Address of array[" << i << "] = " << ptr << "  Value of array[" << i << "] = " << *ptr << endl;

       ptr++;// 移动到下一个位置，相比于数组的好处
       i++;

       if(i == MAX)
          cout << "\n "<< endl;
   }

   //传递指针给函数 :能接受指针作为参数的函数，也能接受数组作为参数，方法：把数组名赋值给一个指针当参数传进去，然后把size也当参数传进去
   unsigned long sec;
   getSeconds( &sec ); // 将sec地址传给par指针变量，在函数中直接存入秒数，不用返回值就直接修改了sec的值
   cout << "sec(Number of seconds) :" << sec << endl;
   cout << "&sec = par"<< "\n"<< endl;

   //函数返回指针
   int *p;
   p = getRandom(); // 返回函数中静态修饰的数组的数组名（指针常量）
   for ( int i = 0; i < 10; i++ )
   {
       cout << "*(p + " << i << ") : " << *(p + i) << endl;
   }


   return 0;
}


