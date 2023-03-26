//
// Created by 施天逸 on 2023/3/25.
//

#include "templateClass.h"
#include "gtest/gtest.h"

bool Stack::isEmpty() const {
    return top == 0;
}

bool Stack::isFull() const {
    return top == SIZE;
}
void Stack::push(const int &a) {
    item[top++] = a;
}

template<typename T>
bool Stack2<T>::isEmpty() const {
    return top == 0;
}

template<typename T>
bool Stack2<T>::isFull() const {
    return top == size;
}

template<typename T>
void Stack2<T>::push(const T &a) {
    item[top++] = a;
}

TEST(templateClass, NonExpressionArg) {
    ArrayTp<int, 10> intArr;
    ArrayTp<double, 20> doubleArr;

    Pair<double, int> pair(3.5, 3);
    Pair<double> pair2(7.1, 4);
    std::cout << pair.add() << std::endl;
}

TEST(templateClass, hasFriends) {
    HasFriends<int> a;
    HasFriends<double> b;
    HasFriends<std::string> c;
    reports(a);
    reports(b);
    //reports(c);
    HasFriends2<std::string> f2;
    reports(f2);
}