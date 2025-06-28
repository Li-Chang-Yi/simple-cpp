#include <iostream>
using namespace std;
// 函数重载 同名函数的形式参数（指参数的个数、类型或者顺序）不同
class printData
{
   public:
      void print(int i) {
        cout << "int: " << i << endl;
      }

      void print(double  f) {
        cout << "float: " << f << endl;
      }

      void print(char c[]) {
        cout << "string: " << c << endl;
      }
};

// 运算符重载（重定义运算符） 对象运算 = overload 运算符  对象赋值 = 拷贝构造
class Box
{
   public:

      double getVolume(void)
      {
         return length * breadth * height;
      }
      void setLength( double len )
      {
          length = len;
      }

      void setBreadth( double bre )
      {
          breadth = bre;
      }

      void setHeight( double hei )
      {
          height = hei;
      }
      // 重载 + 运算符，是带有特殊名称的函数，函数名是由“ operator ”和“ + ”构成的，重载运算符有一个返回类型和一个参数列表。
      // 第一个操作数是通过this指针隐式传递的
      Box operator+(const Box& b)
      {
         Box box;

         box.length = this->length + b.length;
         box.breadth = this->breadth + b.breadth;
         box.height = this->height + b.height;

         return box;
      }
   private:
      double length;      // 长度
      double breadth;     // 宽度
      double height;      // 高度
};
// 运算符重载 分为一元运算符重载、二元运算符重载、关系运算符重载、	输入/输出运算符重载、++ 和 -- 运算符重载、赋值运算符重载、函数调用运算符 () 重载、	下标运算符 [] 重载、类成员访问运算符 -> 重载


int main(void)
{
   printData pd;

   // 输出整数
   pd.print(5);
   // 输出浮点数
   pd.print(500.263);
   // 输出字符串
   char c[] = "Hello C++";
   pd.print(c);

   Box Box1;                // 声明 Box1，类型为 Box
   Box Box2;                // 声明 Box2，类型为 Box
   Box Box3;                // 声明 Box3，类型为 Box
   double volume = 0.0;     // 把体积存储在该变量中

   Box1.setLength(6.0);
   Box1.setBreadth(7.0);
   Box1.setHeight(5.0);

   Box2.setLength(12.0);
   Box2.setBreadth(13.0);
   Box2.setHeight(10.0);

   // Box1 的体积
   volume = Box1.getVolume();
   cout << "Volume of Box1 : " << volume <<endl;

   // Box2 的体积
   volume = Box2.getVolume();
   cout << "Volume of Box2 : " << volume <<endl;

   // 把两个对象相加，得到 Box3
   Box3 = Box1 + Box2;

   // Box3 的体积
   volume = Box3.getVolume();
   cout << "Volume of Box3 : " << volume <<endl;

   return 0;
}
