//
// Created by 施天逸 on 2023/3/25.
//
#include "templateFunc.h"
#include "gtest/gtest.h"

using std::cout;
using std::endl;

template<typename T>
void swap2(T &a, T &b) {
    cout << "using template swap" << endl;
    T temp = a;
    a = b;
    b = temp;
}

