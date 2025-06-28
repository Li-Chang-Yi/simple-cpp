#include <iostream>

#include <fstream>

#include <string>

#include <thread>

#include <chrono>

using namespace std;

int main( )
{
   char name[50];

   cout << "please input your name: "; // 流插入运算符 <<

   cin >> name; // cin 是与流提取运算符 >>

   cout << "your name is :" << name << endl; // endl 用于在行末添加一个换行符

   char str[] = "Unable to read....";

   cout << "Error message : " << str << endl;  //使用了缓冲区，在下一个“换行符”被打印后出现在屏幕上，但是如果程序立即崩溃或被杀死，这条消息可能不会被看到
   cerr << "Error message : " << str << endl;  // 无缓冲的，这条消息会立即出现在屏幕上，与缓存区无关
   clog << "Error message : " << str << endl;  // 也是缓冲的，所以这条消息将在缓冲区满或者流被刷新时打印



}
