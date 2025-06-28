#include <QCoreApplication>
#include <iostream>
class Example {
public:
    int get_value() const {
        return value_; // const 关键字表示该成员函数不会修改对象中的数据成员
    }
    void set_value(int value) const {
        value_ = value;
    }
private:
    mutable int value_; // mutable 关键字允许在 const 成员函数中修改成员变量
//    int value_; // 不用mutable set_value就不能给value_赋值
};

void func( void );
static int count = 10; /* 全局变量 */

int extern_value = 5000;
extern void write_extern(); // 外部文件内的函数

int main(int argc, char *argv[])
{
    //修饰符
    const int NUM = 10; // 定义常量 NUM，其值不可修改
    const int* ptr = &NUM; // 定义指向常量的指针 =常量指针
    const int *ptr1 = &NUM; // 写法1
    const int * ptr2 = &NUM; // 写法2
    int const* ptr3 = &NUM; // // 写法3

    volatile int num = 20; // 定义变量 num，其值可能会在未知的时间被改变

    Example a;
    a.set_value(1);

    //存储类
    auto f=3.14;      //double
    auto s("hello");  //const char*
    auto z = new auto(9); // int*

    while(count--)
    {
       func();
    }


    //extern
//    extern_value ;
    write_extern();


   return 0;


}

void example_function(register int num) {
    // register 关键字建议编译器将变量 num 存储在寄存器中以提高程序执行速度
    // 但是实际上是否会存储在寄存器中由编译器决定
    // 寄存器是CPU内部的小容量存储单元
    // 现代编译器的优化技术已经足够先进，能够自动决定最有效的变量存储方式，所以register关键字在C++17标准中已被废弃，不再对程序的性能产生影响
}

void func( void )
{
    //静态存储区、堆、栈 都在RAM中
    //静态存储区：存放全局变量和静态变量。这部分空间在程序编译的时候就已经分配好了，存储生命周期贯穿程序始终
    //堆（Heap）：malloc和free，C++中的new和delete
    //栈（Stack）：用于存储局部变量和函数调用的上下文，后进先出
    static int i = 5; // 局部变量：static 关键字使变量 count 存储在 程序生命周期内 都存在
    i++;
    std::cout << " i = " << i ;
    std::cout << " count = " << count << std::endl;
}
