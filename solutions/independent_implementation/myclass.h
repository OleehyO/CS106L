#ifndef MYCLASS_H
#define MYCLASS_H

template <typename T>
class MyClass {
public:
    MyClass(T value) : value_(value) {}
    
    // 强制类型转换运算符声明
    operator int() const noexcept;

private:
    T value_;
};

#include "MyClass.hpp" // 包含定义

#endif // MYCLASS_H
