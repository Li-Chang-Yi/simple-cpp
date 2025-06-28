#include <iostream>
#include <ctime> //时间头文件

using namespace std;

//struct tm {
//  int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
//  int tm_min;   // 分，范围从 0 到 59
//  int tm_hour;  // 小时，范围从 0 到 23
//  int tm_mday;  // 一月中的第几天，范围从 1 到 31
//  int tm_mon;   // 月，范围从 0 到 11
//  int tm_year;  // 自 1900 年起的年数
//  int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
//  int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
//  int tm_isdst; // 夏令时
//};

int main( )
{
    // 返回当前秒数 第一种写法
   time_t now = time(NULL); // _t 代表数据是int类型的 返回当前秒数
   cout << "From 1970 till now all second : " << now << "\n" << endl;

   // 第二种写法
   time_t second; // 获得一个地址
   time_t *sec = &second;
   time(sec);
   cout << "Now seconds from 1970: " << *sec << "\n" << endl;

   // 秒数 -> 字符串
   char* dt = ctime(&now);

   cout << "Local time(UTC+8) : " << dt <<endl; //格式->Wdy Mon dd hh:mm:ss yyyy\n\0 本地时间 =  UTC+8

   // 秒数 -> tm结构体
   tm *gmtm = gmtime(&now); //gm 在这里就是指 "Greenwich Mean" 的缩写 = GMT = UTC

   //tm结构体 -> 字符串
   dt = asctime(gmtm);

   cout << "UTC(GMT) time : "<< dt << endl;

   // 返回当前时间的tm结构体而不是秒数
   tm *ltm = localtime(&now);


   cout << "year : "<< 1900 + ltm->tm_year << endl; // 自 1900 年起的年数
   cout << "month : "<< 1 + ltm->tm_mon<< endl; // 月，范围从 0 到 11
   cout << "day : "<<  ltm->tm_mday << endl;
   cout << "time : "<< ltm->tm_hour << ":"<< ltm->tm_min << ":" << ltm->tm_sec << endl;
    cout << "Weekday(Wdy) : "<<  ltm->tm_wday << endl;
}
