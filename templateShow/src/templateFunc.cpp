//
// Created by 施天逸 on 2023/3/25.
//

#include "templateFunc.h"
#include <iostream>
#include "gtest/gtest.h"

using std::cout;
using std::endl;

void swap(int &a, int &b) {
    cout << "using int swap" << endl;
    int temp = a;
    a = b;
    b = temp;
}

//函数重载方式
void swap(double &a, double &b) {
    cout << "using double swap" << endl;
    double temp = a;
    a = b;
    b = temp;
}

template<typename T>
void swap(T &a, T &b) {
    cout << "using template swap" << endl;
    T temp = a;
    a = b;
    b = temp;
}

template<typename T1, typename T2> void add(const T1 &a, const T2 &b) {
    std::cout << a + b << endl;
}

TEST(NonTemplateFunc, swapInt) {
    int a = 5;
    int b = 10;
    swap(a, b);
    cout << "a :" << a << " b: " << b << endl;
}

TEST(NonTemplateFunc, swapDouble) {
    double c = 4.2;
    double d = 5.3;
    swap(c, d);
    cout << "c :" << c << " d: " << d << endl;
}

TEST(NonTemplateFunc, swapTemplate) {
    long a = 100l;
    long b = 200l;
    swap(a, b);
    cout << "a :" << a << " b: " << b << endl;

    double c = 5.2;
    double d = 4.2;
    swap(c, d);
    cout << "c :" << c << " d: " << d << endl;

    add(2.5, 3);
}