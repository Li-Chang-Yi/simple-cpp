#include <iostream>
#include <cstring>

using namespace std;

int main ()
{
   // C风格
   char str1[13] = "runoob";
   char str2[13] = "google";
   char str3[13]; //str3 指针常量
   int  len ;

   // 复制 str1 到 str3
   strcpy( str3, str1); //将str1数组中的内容复制到str3数组中，这是完全合法的。这个过程并没有改变str3这个指针的值
   cout << "str1 : " << str1 << endl;
   cout << "strcpy(str3, str1)  str3: " << str3 << endl;

   // 连接 str1 和 str2
   cout << "str2 : " << str2 << endl;
   strcat( str1, str2);
   cout << "strcat(str1, str2)  str1:" << str1 << endl;

   // 连接后，str1 的总长度
   len = strlen(str1);
   cout << "strlen(str1) : " << len << "\n" << endl;


   //C++风格
   string str4 = "runoob";
   string str5 = "google";
   string str6;
   int  length ;

   // 复制 str4 到 str5
   cout << "str4 : " << str4 << endl;
   str6 = str4;
   cout << "str6 = str4  str6 : " << str6 << endl;

   // 连接 str4 和 str5
   cout << "str5 : " << str5 << endl;
   str6 = str4 + str5;
   cout << "str6 = str4 + str5   str6: " << str6 << endl;

   // 连接后，str6 的总长度
   length = str6.size();
   cout << "str6.size() :  " << length  << endl;

   return 0;
}
