#include <iostream>
#include <vector>
#include <stdexcept> // 包含标准异常类

double division(int a, int b)
{
   if( b == 0 )
   {
      throw "Division by zero condition!";
   }
   return (a/b);
}


int main() {
    std::vector<int> myVector = {1, 2, 3, 4, 5};

    try {
        // 尝试访问一个不存在的元素
        int myValue = myVector.at(10); // 这将抛出一个std::out_of_range异常
    }
    catch (const std::exception& e) {
        std::cout << "Caught an exception: " << e.what() << std::endl;
    }

    int x = 50;
    int y = 0;
    double z = 0;

    try {
      z = division(x, y);
      std::cout << z << std::endl;
    }catch (const char* msg) {
      std::cerr << msg << std::endl;
    }

    return 0;
}

