#include <iostream>

int main() {
    int a = 10;
    {
        int a = 20;  // 块作用域变量
        std::cout << "Block{} Scope Variable: " << a << std::endl;
        std::cout << "Block{} Free " <<  std::endl;

    }
    std::cout << "Block extern Variable: " << a << std::endl;
    return 0;
}
