#include <iostream>

extern int extern_value; //外部文件定义的变量

void write_extern(void)
{
   std::cout << "extern_value is " << extern_value << std::endl;
}
