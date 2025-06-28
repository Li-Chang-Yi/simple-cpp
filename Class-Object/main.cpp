#include <iostream>
#include <class.h>

using namespace std;


int main( )
{
    Box Box1;        // 对象 Box1
//    Box1.height = 5.0; // private and protected 变量不能使用直接成员访问运算符 (.) 来直接访问，只能通过类的内部函数使用
    Box1.volume = 100;  //public 变量可以用

    Box Box3;
    double volume = 0.0;     // 用于存储体积

    Box3.set(16.0, 8.0, 12.0); // 调用成员函数 set
    volume = Box3.get();
    cout << "Box3 volume: " << volume <<endl;

    Rectangle rect(10, 5);
    rect.display(); // 输出：Width: 10, Height: 5

    Derived1 A;

//    A.funcPublic();  // 在子类中都是Private不可通过对象（类外部）访问
//    A.funcProtected();// 不可访问
//    A.funcPrivate(); // 不可访问
    A.callProtectedAndPublic();// 由于在子类中是public，所以可通过对象访问(子类public成员函数调用基类成员函数)
}
