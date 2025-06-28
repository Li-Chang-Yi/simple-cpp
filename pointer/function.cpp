#include <iostream>
#include <ctime>

#include <cstdlib>
void getSeconds(unsigned long *par)
{
   *par = time( NULL );    // 获取当前的秒数 par是指针变量 把秒数存进去
   std::cout << "*par(Number of seconds) :" << *par << std::endl;
}
int * getRandom( )
{
  static int  r[10];//静态局部变量  没有 static 返回的时候r就被释放掉了无法赋值给p 将变成悬空指针

  // 设置种子
  srand( (unsigned)time( NULL ) );
  for (int i = 0; i < 10; ++i)
  {
    r[i] = rand();
    std::cout <<"r[" << i << "] value : " << r[i] << " ---return r to p " << std::endl; // 没有using namespace，std::表示这些标识符属于标准命名空间
  }

  return r; //返回数组头部地址，作为索引
}
