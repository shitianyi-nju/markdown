//
// Created by 施天逸 on 2023/3/25.
//

#ifndef TEMPLATESHOW_TEMPLATEFUNC_H
#define TEMPLATESHOW_TEMPLATEFUNC_H

void swap(int &a, int &b);
void swap(double &a, double &b);

template<typename T> void swap(T &a, T &b);

template<typename T1, typename T2 = int> void add(const T1 &a, const T2 &b);

#endif //TEMPLATESHOW_TEMPLATEFUNC_H
