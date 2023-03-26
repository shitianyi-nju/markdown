//
// Created by 施天逸 on 2023/3/25.
//

#ifndef TEMPLATESHOW_TEMPLATECLASS_H
#define TEMPLATESHOW_TEMPLATECLASS_H

#include <iostream>

//非模板类
class Stack {
private:
    const static int SIZE = 10;
    int item[SIZE];
    int top;
public:
    Stack() {};
    bool isEmpty() const;
    bool isFull() const;
    bool pop(int & a) { a = item[--top]; };
    void push(const int & a);
};

//模板类
template<typename T>
class Stack2 {
private:
    const static int size = 10;
    T item[size];
    int top;
public:
    Stack2() {};
    bool isEmpty() const;
    bool isFull() const;
    bool pop(T & a) { a = item[--top]; };
    void push(const T & a);
};


template<typename T, int n>
class ArrayTp {
private:
    T item[n];
public:
    ArrayTp() {};
    explicit ArrayTp(const T &v);
    virtual T &operator[](int i);
    virtual T operator[](int i) const;
};

template<typename T, int n>
T ArrayTp<T, n>::operator[](int i) const {
    return item[i];
}

template<typename T, int n>
T &ArrayTp<T, n>::operator[](int i) {
    return item[i];
}

template<typename T, int n>
ArrayTp<T, n>::ArrayTp(const T &v) {
    for(int i = 0; i < n; i++) {
        item[i] = v;
    }
}


template<typename T1, typename T2 = int>
class Pair {
private:
        T1 a;
        T2 b;
public:
        Pair() {};
        Pair(const T1 & t1, const T2 & t2) : a(t1), b(t2) {}
        T1 & first() {return a;}
        T2 & second() {return b;}
        auto add() -> decltype(a + b);
    };

template<typename T1, typename T2>
auto Pair<T1, T2>::add() -> decltype(a + b) {
    return a + b;
}

template <> class Pair<Stack, Stack> {
private:
    Stack a;
    Stack b;
public:
    Pair() {};
    Pair(const Stack &t1, const Stack &t2) : a(t1), b(t2) {};
    Stack& first() {return a;}
    Stack& second() {return b;}
    auto add() -> Stack {
        //...
        return Stack();
    }
};

template <typename T>
class HasFriends {
private:
    T friends;
public:
    friend void reports(HasFriends<T> & a);
    //friend void reports<>(HasFriends<T> &a);
};


void reports(HasFriends<int> & a) {
    std::cout << "int friends" << std::endl;
}

void reports(HasFriends<double> & a) {
    std::cout << "double friends" << std::endl;
}


template <typename T> void reports(T &a);
template <typename T>
class HasFriends2 {
private:
    T friends;
public:
    friend void reports<>(HasFriends2<T> & a);
    //friend void reports<>(HasFriends<T> &a);
    template<typename C, typename D> friend void report(C &c, D &d);
};

template <typename T> void reports(T &a) {
    std::cout << "in template" << std::endl;
}

template<typename C, typename D> void report(C &c, D &d) {
    std::cout << "in other tempalte" << std::endl;
}

typedef std::array<int,10> arrayInt;
template <typename T> using arrayType = std::array<T, 12>;
template <typename T>  typedef std::array<T, 12> arrayTemplate;

#endif //TEMPLATESHOW_TEMPLATECLASS_H
