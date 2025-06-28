#include <QCoreApplication>
#include "SimpleIni.h"

#include <QDebug>
#include <errno.h>  // 引入 errno
#include <cstdio>   // 引入 perror
#include <iostream>
#define FILE_NAME    "myini.ini"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // 获取应用程序的路径
    QString appPath = QCoreApplication::applicationDirPath();
    // 打印应用程序的路径
//    qDebug() << "Application Path:" << appPath;

    // 定义ini文档对象
    CSimpleIniA ini;
    // 设置INI数据的存储格式，参数为true时保存为UTF-8格式，否则为本地编码格式
    ini.SetUnicode(true);
    // 是否允许一个关键字对应多个值，默认为允许；若不允许，则将最后一个值作为此关键字关联的值
    ini.SetMultiKey(false);

    SI_Error rc;


    // 加载ini文件
    rc = ini.LoadFile(FILE_NAME);	// 另一种方式：SI_Error LoadFile(FILE * a_fpFile);
    if (rc < 0) {
        perror("Error loading INI file"); // 使用 perror 打印错误详细信息
        qDebug() << QString("加载 %1 文件失败, 错误码: %2").arg(FILE_NAME).arg(rc);
        return -1;
    }

    // 添加一个新的 section
    rc = ini.SetValue("section1", nullptr, nullptr);
    if (rc < 0) {
        qDebug() << QString("添加section1失败！\n");
        return -1;
    }

    // 添加一个新的 key和value
    rc = ini.SetValue("section1", "name", "张三");
    if (rc < 0) {
        qDebug() << QString("添加name失败");
        return -1;
    }
    ini.SetValue("section1", "age", "24");
    ini.SetValue("section1", "sex", "男");

    ini.SetLongValue("server", "length", 173);
    ini.SetDoubleValue("server", "weight", 53.5);
    ini.SetBoolValue("server", "vip", true);

    // 修改value，如果键(name)不存在则添加该 key和value
    rc = ini.SetValue("section1", "name", "李四");
    if (rc < 0) {
        printf("修改name失败！\n");
        return -1;
    }

    ini.SetLongValue("server", "length", 1000);
    ini.SetDoubleValue("server", "weight", 66.66);
    ini.SetBoolValue("server", "vip", false);


    // 删除 key
    bool done = false;
    done = ini.Delete("section1", "name");
    if (false == done) {
        printf("删除 section1 - name 失败！\n");
        return -1;
    }

    // 如果最后一个key也被删除了，那么section也会被一起删除掉
    bool deleteSectionIfEmpty = true;
    done = ini.Delete("section1", "age", deleteSectionIfEmpty);
    if (false == done) {
        printf("删除 section1 - age 失败！\n");
        return -1;
    }

    ini.Delete("section1", "sex", false); //不删除section1节点

    // 删除整个section和其中的所有键
    done = ini.Delete("section1", nullptr);
    if (false == done) {
        printf("删除整个section和其中的所有键 失败 ！\n");
        return -1;
    }

    //获取值
    int _int = std::stoi(ini.GetValue("section", "_int", "-1"));
    printf("_int = %d\n", _int);

    long long _long = std::stoll(ini.GetValue("section", "_long", "-1"));
    printf("_long = %lld\n", _long);

    double _double = std::stod(ini.GetValue("section", "_double", "0.0"));
    printf("_double = %lf\n", _double);

    float _float = std::stof(ini.GetValue("section", "_float", "0.0"));
    printf("_float = %f\n", _float);

    bool _bool = ini.GetBoolValue("section", "_bool", false);
    printf("_bool = %s\n", _bool ? "true" : "false");

    std::string _string = ini.GetValue("section", "_string", "");
    printf("_string = %s\n", _string.c_str());

    std::string _string2 = ini.GetValue("section", "_string2", "");
    printf("_string2 = %s\n", _string2.c_str());

    char _char = ini.GetValue("section", "_char", "")[0];
    printf("_char = %c\n", _char);

    std::string ip = ini.GetValue("server", "ip", "0.0.0.0");
    printf("ip = %s\n", ip.c_str());

    int port = std::stoi(ini.GetValue("server", "port", "-1"));
    printf("port = %d\n", port);

    std::string name1 = ini.GetValue("server", "name", "");
    printf("name = %s\n", name1.c_str());

    int lenght = ini.GetLongValue("server", "length", -1);
    double weight = ini.GetDoubleValue("server", "weight", -1);
    bool vip = ini.GetBoolValue("server", "vip", false);

    //遍历
    CSimpleIniA::TNamesDepend sections;
    // get all sections
    ini.GetAllSections(sections);
    // 遍历所有 section 的 key 和 value
    for (const auto &it : sections) {
        const CSimpleIniA::TKeyVal *pKeyVal = ini.GetSection(it.pItem);
        if (nullptr != pKeyVal) {
            for (const auto& it : *pKeyVal) {
                std::cout << it.first.pItem << " = " << it.second << std::endl;
            }
        }
    }

    CSimpleIniA::TNamesDepend sections1;
    // 获取所有section
    ini.GetAllSections(sections1);
    // 遍历所有 sections
    for (const auto &it : sections1) {
        std::cout << it.pItem << std::endl;
    }

    CSimpleIniA::TNamesDepend keys;
    // get all keys in a section
    ini.GetAllKeys("section", keys);
    // 遍历 section 指定的所有 key
    for (const auto &it : keys) {
        std::cout << it.pItem << std::endl;
    }

    CSimpleIniA::TNamesDepend values;
    // 获取 key 所对应的多个 value；ini.SetMultiKey(true);一定要设置为true，
    // 否则就只会获取到最后一个，其他删除
    ini.GetAllValues("server", "name", values);
    // 遍历一个 key 对应多个 value；
    for (const auto &it : values) {
        printf("name = %s\n", it.pItem);
    }

    // 获取section里有多少值
    int size = ini.GetSectionSize("section");
    printf("section 的 key 个数：%d\n", size);


    // 保存
    rc = ini.SaveFile(FILE_NAME);
    if (rc < 0) {
        perror("Error saving INI file");
        qDebug() << QString("保存 %1 文件失败, 错误码: %2").arg(FILE_NAME).arg(rc);
        return -1;
    }

    return a.exec();
}
