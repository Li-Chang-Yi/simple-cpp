#include <iostream>
#ifndef CLASS_H
#define CLASS_H

//类访问修饰符
class Box
{
    //公有成员在程序中类的外部是可访问的,可以不使用任何成员函数来改变和获取
public:
    double get(void);
    void set( double len, double bre, double hei );
    int volume;

    //protected（受保护）成员变量或函数与私有成员十分相似，但protected（受保护）成员在派生类（即子类）中是可访问的
protected:

    //私有成员变量和成员函数只能 类内部的成员函数 访问和修改，无论这些成员函数是公有的还是私有的
    //没有使用任何访问修饰符，类的成员将被假定为私有成员：
private:
    double length;   // 长度
    double breadth;  // 宽度
    double height;   // 高度

};


//继承方式：指的是基类的非私有成员在子类的访问属性变化（公有继承就属性不变，保护继承就全变保护，私有继承就全变私有）
class Base {
public:
    void funcPublic() {}
protected:
    void funcProtected() {}
private:
    void funcPrivate() {}
};

class Derived1 : Base { // 私有继承(默认)
    // Base中的funcPublic()和funcProtected()在Derived1中变为私有成员
    // Base中的这三个函数均不能通过子类Derived1的对象（类外部）直接访问
    // funcPublic()、funcProtected()-private性质的不能通过子类的对象在类外部直接访问，但是在子类的成员函数内部访问，如下
public: //声明为public意味着可以通过子类Derived1对象外部访问，这行若声明为private，只能子类的内部成员函数调用访问，子类的对象也不能调用
    void callProtectedAndPublic()
    {
        funcPublic();    // 从Base继承的public成员，在Derived1中为private
        funcProtected(); // 从Base继承的protected成员，在Derived1中为private
    }
    //无论是通过什么类型的继承（私有继承、保护继承、公开继承）。私有成员仅在基类Base的内部可见，不能在任何子类中访问，即使是在派生类的成员函数内部也不行
};

class Derived2 : public Base {   // 继承方式被显式指定为公有继承
    // Base的funcPublic()和funcProtected()在Derived2中访问属性不变
    // Base中的funcPrivate()在Derived2中不可访问
};


//调用私有成员函数，私有成员变量和函数，只能通过类内部的成员函数访问和修改
class DemoClass {

public:
    DemoClass(int value) : privateVariable(value) {} // 构造函数，初始化私有成员变量

    void publicFunction() const {

        privateFunction();   // 公有函数调用私有函数
    }
private:

    void privateFunction() const {
        std::cout << "私有函数被调用私有变量" << privateVariable << std::endl;
    }

    int privateVariable;
};

//构造函数 & 析构函数
//创建类的对象时执行；构造函数名与类名相同；构造函数带参数初始化成员变量


class Line
{
   public:
       Line();   // 这是构造函数声明
      ~Line();  // 这是析构函数声明

};

class Line1
{
   public:
      Line1(double len) { // 这是带参数的构造函数
          length = len;
      }
   private:
      double length;
};


// 使用初始化列表来初始化字段(即私有变量)
class Rectangle {
public:
    Rectangle    (int w, int h) : width(w), height(h)     {}  // 使用初始化列表来初始化width和height     Rectangle rect(10, 5);
    void display() {std::cout << "Width: " << width << ", Height: " << height << std::endl;}
private:
        int width, height;


};

// 拷贝构造（对象各部分对应赋值）函数 & 深拷贝和浅拷贝 & 显示拷贝和隐式拷贝
class Book {
public:
    // 普通构造函数
    Book(std::string t, int p) : title(t), pages(p) {} // 使用普通构造函数创建一个Book对象  Book book1("C++ Primer", 1000);


    // 拷贝构造函数
    Book(const Book& b) : title(b.title), pages(b.pages) {  // 使用拷贝构造函数创建book2，它是book1的副本 Book book2 = book1;（显式拷贝） // 或者 Book book2(book1); （隐式拷贝）
        std::cout << "拷贝构造函数被调用" << std::endl;
    }
private:
    std::string title;
    int pages;
};

//友元函数	友元函数可以访问类的 private 和 protected 成员
//内联函数	通过内联函数，编译器试图在调用函数的地方扩展函数体中的代码，减少函数调用的开销，提高程序的执行效率。

class Point {
public:
    Point(double x, double y) : x(x), y(y) {}
    // 声明友元函数，允许这个函数访问Point的私有成员
    friend inline double distance(const Point& p1, const Point& p2); //声明内联函数
private:
    double x, y;
};

//this 指针	每个对象都有一个特殊的指针 this，它指向对象本身
//类指针     MyClass obj; MyClass *ptr = &obj;


// 类的静态成员  声明类的成员为静态时，这意味着无论创建多少个类的对象，静态成员都只有一个副本
// 类的静态成员函数：1.静态成员函数即使在类对象不存在的情况下也能被调用 2.静态函数只要使用类名加范围解析运算符 :: 就可以访问

//静态成员函数与普通成员函数的区别：
//静态成员函数没有 this 指针，只能访问静态成员（包括静态成员变量和静态成员函数）。
//普通成员函数有 this 指针，可以访问类中的任意成员；而静态成员函数没有 this 指针。

#endif // CLASS_H





