#include <iostream>
#include <string>
#include <cmath>


class Shape {
public:
    void draw() {
        std::cout << "Drawing a shape." << std::endl;
    }
    void setWidth(int w)
    {
       width = w;
    }
    void setHeight(int h)
    {
       height = h;
    }
protected:
   int width;
   int height;
};

class PaintCost
{
   public:
      int getCost(int area)
      {
         return area * 70;
      }
};


class Rectangle: public Shape, public PaintCost // 派生类继承于多个类 可以访问基类中所有的非私有成员；基类成员如果不想被派生类的成员函数访问，则应在基类中声明为 private
{
   public:
      int getArea()
      {
         return (width * height);
      }
};
class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}

    double area() {
        return M_PI * std::pow(radius, 2);
    }
    void draw() {
        std::cout << "Drawing a circle." << std::endl;
    }
private:
    double radius;

};






int main() {

    Shape shape;
    shape.draw();  // 输出: Drawing a shape.

    Circle circle(5); // 创建一个半径为5的圆
    circle.draw();    // 输出: Drawing a circle. 继承自Shape
    std::cout << "Circle area: " << circle.area() << std::endl; // 计算并输出圆的面积

    Rectangle Rect;
    int area,cost;

    Rect.setWidth(5);
    Rect.setHeight(7);

    area = Rect.getArea();
    cost = Rect.getCost(area);


    return 0;
}


