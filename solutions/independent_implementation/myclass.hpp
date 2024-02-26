#ifndef MYCLASS_HPP
#define MYCLASS_HPP

#include "myclass.h"
// 强制类型转换运算符定义
template <typename T>
MyClass<T>::operator int() const noexcept{
    return static_cast<int>(value_);
}

#endif // MYCLASS_HPP
