#include <iostream>
#include <string>
using namespace std;

#define PI 3.14159 //#define 预处理

#define MIN(a,b) (((a)<(b)) ? a : b) // 参数宏

#define DEBUG // 条件编译

#define MKSTR( x ) #x  //# 运算符会把参数，也就是x转换为用引号引起来的字符串

#define concat(a, b) a ## b //## 运算符用于连接两个参数

int main ()
{
    int i, j;
    i = 100;
    j = 30;

#ifdef DEBUG
    cerr <<"Trace: Inside main function" << endl;
#endif

    cout <<"The minimum is " << MIN(i, j) << endl;

    cout << MKSTR(HELLO C++) << endl;

    int xy = 100;
    cout <<  concat(x, y) << endl;

    //预定义的宏
    cout << "Value of __LINE__ : " << __LINE__ << endl; //当前行号 33
    cout << "Value of __FILE__ : " << __FILE__ << endl; //当前文件名main.cpp
    cout << "Value of __DATE__ : " << __DATE__ << endl; //转换为目标代码的日期
    cout << "Value of __TIME__ : " << __TIME__ << endl; //程序被编译日期时间


    return 0;
}
