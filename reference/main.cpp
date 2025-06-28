#include <iostream>

using namespace std;

class LargeObject {
public:
    void modify() {
        // 修改对象的状态
    }
};

// 使用一个函数 封装 类的一些方法
void modifyObject(LargeObject& obj) { //传递引用 作为参数
    obj.modify(); //调用对象的方法
}

class Counter {
public:
    Counter() : value(0) {} // 构造函数初始化计数器为 0

    int& getValue() {       // 返回当前计数器的私有成员变量的引用 （int& 声明返回的是引用）
        return value;
    }

    void print() {
        cout << "Current value: " << value << endl;
    }

private:
    int value;
};

class IntArray {
private:
    int arr[10];
public:
    IntArray() {
        // 初始化数组
        for(int i = 0; i < 10; ++i) {
            arr[i] = i;
        }
    }

    // 返回数组元素的引用，重载运算符 "[]"用于提供类或对象的下标访问能力
    int& operator[](int index) {
        return arr[index];
    }

    void print() const {
        for(int i = 0; i < 10; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

//引用与指针的区别：
//不存在空引用。引用必须连接到一块合法的内存。
//一旦引用被初始化为一个对象，就不能被指向到另一个对象。指针可以在任何时候指向到另一个对象。
//引用必须在创建时被初始化。指针可以在任何时间被初始化
int main ()
{
   // 声明简单的变量
   int    i;
   double d;

   // 引用 创建时被初始化 就是给变量取一个别名
   int&    r = i;
   double& s = d;

   i = 5;
   cout << "Value of i : " << i << endl;
   cout << "Value of i reference : " << r  << endl;

   d = 10;
   cout << "Value of d : " << d << endl;
   cout << "Value of d reference : " << s  << endl;

   //引用作为参数传递：
   //安全性: 由于引用必须被初始化，并且一旦被初始化后就不能改变指向另一个对象
   //效率: 引用传递不需要进行任何拷贝操作
   //不足：函数内部对引用所做的修改会影响到原始数据
   //场景：特别是在处理大型对象或希望在函数内部修改调用者提供的对象时
   LargeObject myObj; //创建对象 myObj
   modifyObject(myObj); // 传递引用，不会发生拷贝

   //把引用作为返回值
   Counter myCounter;
   myCounter.print(); // 打印当前值：Current value: 0

   myCounter.getValue() = 5; // 直接通过返回的引用修改计数器的值
   myCounter.print(); // 打印修改后的值：Current value: 5

   int& val = myCounter.getValue(); // 再次修改计数器的值
   val = 10;
   myCounter.print(); // 打印再次修改后的值：Current value: 10

   IntArray myArray;
   myArray.print(); // 打印初始数组

   // 通过返回的引用修改数组元素
   myArray[2] = 20;
   myArray.print(); // 打印修改后的数组

   return 0;
}
