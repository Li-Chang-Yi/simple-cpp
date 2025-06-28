#include<class.h>
// 成员函数定义 类的外部使用范围解析运算符::  简单的函数实现也可以写在类的内部
double Box::get(void)
{
    return length * breadth * height;
}

void Box::set( double len, double bre, double hei)
{
    length = len;
    breadth = bre;
    height = hei;
}



