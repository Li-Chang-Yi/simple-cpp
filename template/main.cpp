#include <iostream>
#include <string> // 包含string头文件

#include <vector> //用到向量
#include <stdexcept> //用到标准错误
//#include <cstdlib>

template <typename T>
// 定义一个模板函数max，接收两个T类型的输入参数，T是一个模板参数，可以在函数被调用时根据传入的参数类型自动推断
T max(T x, T y) {
    return (x > y) ? x : y;
}

// 定义一个泛型的Pair类
template <typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair(T1 a, T2 b) : first(a), second(b) {}

    void print() {
        std::cout << "(" << first << ", " << second << ")" << std::endl;
    }
};

// 类模板
// 声明一个类模板，T是一个占位符类型，代替将来要填充的值或类型的标识符
template <typename T>
class Box {
private:
    T value; // Box类中存储的值的类型为T

public:
    // 构造函数，用于初始化value
    Box(T newValue) : value(newValue) {}

    // 成员函数，用于获取value的值
    T getValue() const {
        return value;
    }
};
// 栈的类模板例子
template <class T>
class Stack {
public:
    void push(T const&);  // 入栈
    void pop();               // 出栈
    T top() const;            // 返回栈顶元素
    bool empty() const{       // 如果为空则返回真。
        return elems.empty();
    }
private:
    std::vector<T> elems;     // 元素
};
//push操作
template <class T>
void Stack<T>::push (T const& elem)
{
    // 追加传入元素的副本
    elems.push_back(elem);
}
//pop操作
template <class T>
void Stack<T>::pop ()
{
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    // 删除最后一个元素
    elems.pop_back();
}
//top操作
template <class T>
T Stack<T>::top () const
{
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    // 返回最后一个元素的副本
    return elems.back();
}


int main() {

    std::cout << "Max of 3 and 5 is " << max<int>(3, 5) << std::endl;    // 使用模板函数max比较两个整数
    std::cout << "Max of 2.3 and 3.2 is " << max<double>(2.3, 3.2) << std::endl;    // 使用模板函数max比较两个浮点数
    std::cout << "Max of 'a' and 'z' is " << max<char>('a', 'z') << std::endl;    // 使用模板函数max比较两个字符


    Pair<int, double> p1(6, 7.8);    // 创建一个Pair对象，其中包含一个整数和一个浮点数
    p1.print();
    Pair<std::string, std::string> p2("hello", "world");    // 创建一个Pair对象，其中包含两个字符串
    p2.print();
    Pair<char, int> p3('A', 65);     // 创建一个Pair对象，其中包含一个字符和一个整数
    p3.print();

    Box<int> intBox(123); // 使用int类型实例化Box类
    std::cout << "Box<int> value: " << intBox.getValue() << std::endl;

    Box<std::string> stringBox("Hello World");  // 使用string类型实例化Box类,string前面加std
    std::cout << "Box<string> value: " << stringBox.getValue() << std::endl;

    try {
        Stack<int>         intStack;  // int 类型的栈
        Stack<std::string> stringStack;    // string 类型的栈

        intStack.push(7); // 操作 int 类型的栈
        std::cout << intStack.top() <<std::endl;

        stringStack.push("hello"); // 操作 string 类型的栈
        std::cout << stringStack.top() << std::endl;
        stringStack.pop();
        stringStack.pop(); //不能再pop了，就一个元素
    }
    catch (std::exception const& ex) {
        std::cerr << "Exception: " << ex.what() <<std::endl;
        return -1;
    }
    return 0;
}
