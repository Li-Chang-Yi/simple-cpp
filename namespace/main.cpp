#include <iostream>
using namespace std;

// 第一个命名空间
namespace first_space{
   void func(){
      std::cout << "Inside first_space" << std::endl;
   }
}
// 第二个命名空间
namespace second_space{
   void func(){
      std::cout << "Inside second_space" << std::endl;
   }
}
int main ()
{

   // 调用第一个命名空间中的函数
   first_space::func();

   // 调用第二个命名空间中的函数
   second_space::func();

   using namespace first_space;
   func();
//   using namespace second_space;
//   func();

//   using namespace first_space::second_space; // 命名空间可嵌套
   return 0;
}
