#include <iostream>
using namespace std;
// 多态 分为静态多态（静态链接）和动态多态（动态链接）
// 静态多态是在编译时实现的多态性。它主要通过两种方式实现：函数重载和运算符重载。
// 静态多态适用于重载和简单的运算符重载场景，动态多态适用于需要利用继承和派生机制
class Shape {
public:
    Shape( int a=0, int b=0)
    {
        width = a;
        height = b;
    }
//    int area() // 1. 静态多态--在程序编译时期就已经设置好了
    virtual int area() // 2. 动态多态（虚函数）--在基类中声明的虚函数，可以在派生类中被重写（即告诉编译器不要静态链接到基类的area函数）（override），
                       // 2.1 为了允许通过基类的指针来调用子类的重写的area函数
                       // 2.2 类中存在未定义的虚函数也就是纯虚函数，则不能创建该对象，其类是抽象类，无法实例化
//    virtual int area() = 0; // 3. 纯虚函数：在基类中没实现（定义）的虚函数是纯虚函数，起到规范作用，继承这个类的子类必须实现这个函数

    {
        cout << "Parent class area :" <<endl;
        return 0;
    }

protected:
    int width, height;
};
class Rectangle: public Shape{
   public:
      Rectangle( int a=0, int b=0):Shape(a, b) { } //调用基类的构造函数，初始化列表形式 ClassName(Type1 arg1, Type2 arg2, ...) : member1(arg1), member2(arg2), ... {函数体 }

      int area ()
      {
         cout << "Rectangle class area" <<endl;
         return (width * height);
      }
};
class Triangle: public Shape{
   public:
      Triangle( int a=0, int b=0):Shape(a, b) { }
      int area ()
      {
         cout << "Triangle class area" <<endl;
         return (width * height / 2);
      }
};
// 抽象类: 无法实例化
// 可用于实例化对象的类被称为具体类
// 虚函数表（vtable）
class Box
{
   public:
//      virtual double getVolume() = 0; // 纯虚函数
      virtual double getVolume(); // 虚函数未定义
   private:
      double length;      // 长度
      double breadth;     // 宽度
      double height;      // 高度
};






// 程序的主函数
int main( )
{
   Shape *shape; // 基类指针
   Rectangle rec(10,7);
   Triangle  tri(10,5);

// 通过基类指针实现动态多态也叫动态链接 area()函数在基类中需要被声明为虚函数，并在子类中重写
   shape = &rec;
   shape->area();
   shape = &tri;
   shape->area();


// 通过创建子类对象来调用方法，也是静态多态
//   rec.area();
//   tri.area();

//   Box Box1; 不可用


   return 0;
}

