// C++ STL（标准模板库）提供了通用的模板类和函数，这些模板类和函数可以实现多种流行和常用的算法和数据结构，如向量、链表、队列、栈
// 核心组件：容器（Containers）、算法（Algorithms）、迭代器（iterators）
// 容器 是用来管理某一类对象的集合，比如 deque、list、vector、map 等
// 算法 作用于容器。它们提供了执行各种操作的方式，包括对容器内容执行初始化、排序、搜索和转换等操作
// 迭代器 用于遍历对象集合的元素。这些集合可能是容器，也可能是容器的子集
#include <iostream>  // std::cout

#include <vector>    // std::vector
#include <algorithm> // std::sort
#include <iterator>  // std::ostream_iterator
#include <list>
#include <map>
#include <numeric>  // 包含对 std::accumulate 的定义
int main()
{
    std::vector<int> numbers = {7, 3, 5, 2, 8, 6};    // 容器: vector

    // 算法: sort，对容器中的元素升序排列
    std::sort(numbers.begin(), numbers.end()); //std::sort接受两个迭代器作为参数，表示排序操作的起始和结束位置
    //降序排列
//    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    // 迭代器: 遍历容器
    for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';


    std::vector<int> ages = {22, 45, 17, 53, 28, 39};   // 容器: vector
    // 使用算法 count_if 和 lambda 表达式来统计年龄超过30的人数
    int count_over_30 = std::count_if(ages.begin(), ages.end(), [](int age) //一个 lambda 表达式？？？？，为每个元素返回一个布尔值，表示该元素是否应该被计数
    {
        return age > 30;
    });
    std::cout << "Number of people over 30: " << count_over_30 << '\n';
    // 算法: 使用 sort 和 greater<int>() 对年龄进行降序排列 std::greater<int>()
    std::sort(ages.begin(), ages.end(), std::greater<int>());
    // 迭代器
    std::cout << "Ages in descending order: ";
    // std::ostream_iterator，这是一种特殊的迭代器，它在每次迭代时将元素输出到一个流（在这个例子中是标准输出流 std::cout）
    std::copy(ages.begin(), ages.end(), std::ostream_iterator<int>(std::cout, " ")); //将排序后的容器元素复制到 std::ostream_iterator
    std::cout << '\n';


    std::vector<int> vec;   // 创建一个int向量
    int i;
    std::cout << "vector size = " << vec.size() << std::endl;   // 向量初始大小
    for(i = 0; i < 5; i++){
       vec.push_back(i);  //push_back( ) 成员函数在向量的末尾插入5个值
    }
    std::cout << "extended vector size = " << vec.size() << std::endl; // vec 扩展后的大小
    for(i = 0; i < 5; i++){
       std::cout << "value of vec [" << i << "] = " << vec[i] << std::endl;  // 访问向量中的5个值
    }
    std::vector<int>::iterator v = vec.begin(); //定义一个迭代器
    while( v != vec.end())      // 使用迭代器 iterator v 访问每个向量值
    {
       std::cout << "value of v = " << *v << std::endl;
       v++;
    }


    std::list<int> myList = {7, 5, 16, 8}; // list 双向链表，它允许从两端快速插入和删除元素，但不支持随机访问
    myList.push_front(25); // 添加元素到list的前面
    myList.push_back(13);  // 添加元素到list的后面
    myList.remove(16);     // 删除所有值为16的元素
    for (int n : myList)   // 使用迭代器遍历并打印list
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';


    std::map<std::string, int> ageMap; //std::map<KeyType, ValueType>是基于键值对的容器（平衡二叉树），每个元素都是一个键和一个值
    ageMap["Alice"] = 30;     // 添加元素
    ageMap["Bob"] = 25;
    ageMap["Charlie"] = 17;
    std::cout << "Alice is " << ageMap["Alice"] << " years old.\n";    // 访问元素

    for (const auto& pair : ageMap)  // 基于范围的 for 循环的语法
    // const 表示我们不打算修改遍历到的元素，这保证了循环体内元素的不可变性
    // auto ：让编译器自动推断元素的类型，
    // & 表示我们通过引用来访问元素，以避免不必要的复制，不是副本
    // pair 是对每个键值对的引用
    // : ageMap：这是被遍历的容器
    {
        std::cout << pair.first << " is " << pair.second << " years old.\n";  // 迭代器遍历map
    }

     //find算法
    std::vector<int> vec1 = {4, 1, 2, 8, 5, 7};
    auto it = std::find(vec1.begin(), vec1.end(), 5);

    if (it != vec1.end()) {
        std::cout << "Found: " << *it << '\n';
    } else {
        std::cout << "Not found\n";
    }
    //  accumulate算法
    std::vector<int> numbers1 = {1, 2, 3, 4, 5};
    int sum = std::accumulate(numbers1.begin(), numbers1.end(), 0);

    std::cout << "The sum is: " << sum << '\n';

    return 0;
}
