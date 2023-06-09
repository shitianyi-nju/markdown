# c++泛型和STL

## 泛型编程

C++面向对象编程（OOP）关注点在于编程的数据，而泛型编程关注的是算法。泛型编程和面向对象编程的共同点都是创建和抽象可重用代码，但其理念则完全不同，c++泛型编程旨在编写**独立于数据类型**的代码，实现工具就是**模板（templates)**。模板可以按照泛型定义函数和类，分别称为模板函数和模板类。

模板是整个C++泛型编程以及STL的基础。

## 模板函数

示例：

~~~c++
// 定义一个交换两个int的函数swap
void swap(int &a, int &b) {
  	int &temp = a;
  	a = b;
  	b = temp;
}
  
// 如果想添加两个double互换的函数
// 通过函数重载的方式
void swap(double &a, double &b) {
  	double &temp = a;
  	a = b;
    b = temp;
}

// 两个long、两个char、....
~~~

采用模板函数的方式：

~~~c++
template<typename T>
void swap2(T &a, T &b) {
    cout << "using template swap" << endl;
    T temp = a;
    a = b;
    b = temp;
}
~~~

如果需要将同一种算法应用于不同数据类型，那采取模板方式开发可节省大量代码。

模板函数声明方式：

`template<typename T> return-type func(T ...)或者template<class T> return-type func(T..)`  其中，`typename`和`class`在模板声明中是等价的。`<>`内存储的为模板参数，包括**类型参数**和**非类型参数**，`typename T`指定的就是类型参数。

当然，并非所有的数据类型都可以通过同一种算法完全覆盖，如：交换两个数组中的元素。但**函数模板也支持重载**。

交换基础类型参数`(T &, T &)`，交换两个数组的函数参数应当为`(T *, T*, int)`或者`(T[], T[], int)`

~~~c++
template<typename T>
void swap2(T* array1, T* array2, int n) {
	for(int i = 0; i < n; i++) {
		T temp = array1[i];
		array1[i] = array2[i];
		array2[i] = temp;
	}
}
~~~

但模板函数并不是万能的，考虑以下场景：

~~~c++
// 如果T传入数组，则比较的则是数组指针地址的大小，和预期不符。或者传入的T是一个类，但是类并没有重载>符号，则会出现异常。
template<typename T>
void f(T &a, T &b) { a > b }
~~~

模板显式实例化和显示具体化：

~~~c++
//显式实例化，仍然使用模板函数的方法
double m = 2.0;
double n = 3.5;
template void swap2<double>(double &a, double &b)

struct Job {
	string name;
	int id;
}
//具象到某个具体的结构(显式具体化，不使用模板函数定义，而是自定义实现)
template<> void swap2<Job>(Job &a, Job &b) { //或者template<> void swap2(Job &a, Job &b)
		int temp = a.id;
		a.id = b.id;
		b.id = temp;
}
~~~

**优先级：非模板函数 > 模板具体化函数 > 模板函数**。

模板函数支持定义多个参数，也支持定义非模板参数

~~~c++
// 多个模板参数
template<typename T1, typename T2>
void add(T1 &t1, T2 & t2) {
  	// t1 + t2类型表示
  	//?(t1+t2)? = t1 + t2;
  	decltype(t1+t2) = t1 + t2; // c++11支持
}

template<typename T1, typename T2>
auto add(T1 &t1, T2 & t2) -> decltype(t1 + t2) { return t1 + t2; }

// 非模板参数
// 非模板的参数除了简单的数值计算， 还可针对数组，类中重载+、*等操作符处理
template<typename T1, int VAL>
auto multi(T1 & t1) => decltype(t1 * VAL) {
  return t1 * VAL;
}
~~~

## 模板类

模板类的核心理念同模板函数类似，使用通用的数据类型来表示成员对象或者成员函数参数，返回值。

声明：`template<typename T ...> class ClassName {}`

~~~c++
//非模板类
//int类型stack
class Stack {
private:
    const static int size = 10;
    int item[size];
    int top;
public:
    Stack();
    bool isEmpty() const;
    bool isFull() const;
    bool pop(int & a);
    void push(const int & a);
};

//模板类
template<typename T> //T称为类型参数，只能给他们赋值类型
class Stack2 {
private:
    const static int size = 10;
    T item[size];
    int top;
public:
    Stack2();
    bool isEmpty() const;
    bool isFull() const;
  	// 内联场景可不需要声明template
    bool pop(T & a) { a = item[--top]; };
    void push(const T & a);
};
~~~

成员函数实现：

~~~c++
bool Stack::isEmpty() const {
    return top == 0;
}

void Stack::push(const int &a) {
    item[top++] = a;
}

//实现模板函数的方式实现
template<typename T> 
bool Stack2<T>::isEmpty() const {
    return top == 0;
}

template<typename T>
void Stack2<T>::push(const T &a) {
    item[top++] = a;
}

int main() {
  //和模板函数不同，必须通过显示的方式提供类型参数的类型
  Stack2<int> intStack;
  Stack2<std::string> stringStack;
}
~~~

也需要注意，该种场景下生成的模板类可能也只符合部分场景，如果传入的类型参数为指针类型，则相关成员函数实现可能都需要更改。

template模板参数中，除了包含类型参数，也可包含非类型参数

~~~c++
// T和n均为模板参数，T为类型参数, n为非类型参数(表达式参数）
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

int main() {
	//类名为ArrayTp<int,10>
  ArrayTp<int,10> intArr;
  	//类名为ArrayTp<double,20>
  ArrayTp<double, 20> doubleArr;
  
  //嵌套,多维数组
  ArrayTp<ArrayTp<int,10>, 20> arrayArr;
}
~~~

注意：表达式参数只能是**整型，枚举，引用或者指针**，所以`double n`是不合法的，但是`double *pn`却是合法的。

模板代码不能修改表达式参数的值，也不能获取他的地址，所以`n++`或者`&n`都是不允许的。

![image-20230325231610046](https://raw.githubusercontent.com/shitianyi-nju/markdownImg/main/img/image-20230325231610046.png?token=GHSAT0AAAAAACASH2JZFM6ARNEEEADWFIQ4ZA75F7Q)

![image-20230325232309343](https://raw.githubusercontent.com/shitianyi-nju/markdownImg/main/img/image-20230325232309343.png?token=GHSAT0AAAAAACASH2JZ5F5HQR5XEUBR7GZEZA75GNQ)

类的其他特性也支持模板类（继承，包含）

~~~c++
template <typename T>
class SuperStack : public Stack2<T> {
  //...
}

template <typename V>
class SuperStack2 {
private:
  Stack<V> stack;
}
~~~



类模板也同样支持多个模板参数，也可以为类模板的模板参数提供默认值（从右往左）

~~~c++
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

int main() {
  Pair<double, int> pair(3.5, 2);
  //也是Pair<double, int>
  Pair<double> pair(7.1, 3);
}
~~~

STL中会大量使用默认类型。

和函数模板一样，类模板也支持隐式实例化，显式实例化和显示具体化。

~~~c++
// 隐式实例化，通过声明对象的方式，指出所需要的类型，编译器通过模板定义生成具体的类定义
// 仅在生成对象时生成类定义
Pair<double, int> pair(3.5, 2);

// 显式实例化，通过template关键字声明类
// 即使此时还未生成类对象，编译器也会生成类声明
template class Pair<double, double>;

//显式具体化，特定类型的定义，可能需要重新修改原有的类模板
template <> class Pair<Stack, Stack> {
  private:
  	Stack a;
  	Stack b;
  //...
  auto add() -> Stack {
    Stack result;
    for(int i = 0; i < a.size; i++) {
       int tempA = a.pop();
       int tempB = b.pop();
       result.push(tempA + tempB);
    }
  }
}

//部分具体化， <>内声明未具体化的参数
template <typename T1> class Pair<T1, int> {
  //...
}

main() {
  // 通用模板
  Pair<double, double> p0;
  //显示具体化
  Pair<Stack, Stack> p1;
  //部分具体化
  Pair<double, int> p2;
  // init;
  p1.add(); //调用显式具体化类的add
}
~~~

模板参数还支持将其他模板当做模板参数。也支持和其他模板参数，非模板参数任意组合

~~~c++
//该模板包含一个 template<typename T> class类型的V
template <template <typename T> class V> class Top{
private:
  V<int> a;
}
  
template<typename T> class Middle {...}

int main {
	Top<Middle> t;
}
~~~

### 模板类友元

- 非模板友元（普通友元函数）
- 约束模板友元，友元的类型取决于模板类被实例化的类型
- 非约束模板友元，友元的所有具体化都是类的每一个具体化的友元

~~~c++
// 申明一个函数模板
template<typename T> void report(T &);

template<typename T>
class Hasfriend {
private:
  T val;
public:
  // 非模板友元，函数本身是非模板函数，实现上必须传入具体类
  friend void report(Hasfriend<T> &);
  // 约束模板友元，它只能处理Hasfriend的某种特定类场景
  friend void report<<Hasfriend<T>>(Hasfriend<T> &) //省略<>内的声明也可以 friend void report<>(Hasfriend<T> &)
  // 非约束模板友元
  template<typename C, typename D> friend void report(C &c, D &d);
}

//非模板友元模板化参数实现
void report(Hasfriend<int> &a) {...}
void report(Hasfriend<double> &b) {...}
//非约束友元模板
template<typename C, typename D> friend void report(C &c, D &d) {...}


//约束模板友元实现
template<typename T> void report(T &a);

int main() {
  	Hasfriend<int> a;
  	report(a); //pass
 		Hasfriend<double> b;
  	report(b); //pass
  	Hasfriend<string> c;
  	report(c); // 非模板友元将报error,约束模板友元可pass
 		
  	//非约束友元，友元可同时处理Hasfriend<int>和Hasfriend<double>
  	report(a, b);
}
~~~

### 模板别名(c++ 11以后)

c++11以前，只能通过typedef来申明别名，但typedef无法申明template

~~~c++
typedef std::array<int, 12> ArrayTypeInt;
typedef std::array<double, 12> ArrayTypeDouble;
template <typename T> typedef std::array<T, 12> arrayTemplate; // error
~~~

![image-20230326140404645](https://raw.githubusercontent.com/shitianyi-nju/markdownImg/main/img/image-20230326140404645.png?token=AFCLAE24QESR3WWYMJGG67TED7U24)

在C++11后，可以通过using的方式声明模板别名。

~~~c++
template <typename T> using arrayType = std::array<T, 12>

arrayType<int> a
arrayType<double> b
~~~



## STL

**STL**: standard templates library，标准模板库，提供了一组表示**容器、迭代器、函数对象和算法**的**模板**。STL也属于泛型编程的范畴。

算法通过使用模板，从而独立于所存储的对象的类型；通过使用迭代器接口，从而独立于容器的类型

- **容器**：容器是一个和数组类似的单元，可以存储一组值，STL容器是同质的，这一组值的类型必须相同。（数组，队列，链表等）
- **迭代器**：能够用于遍历STL容器的对象，是一种广义上的指针（可类比：数组的指针可以遍历整个数组）
- **函数对象**：类似于函数的对象，可以是某个函数指针，也可以是一个类对象（重载()）
- **算法**：完成特定任务的方法。(搜索，排序，转换等)

### 迭代器

理解了迭代器才理解了STL的关键。

模板可以使用户编写独立于数据类型的代码，而迭代器使得算法可以独立于使用的容器。

~~~c++
//在array数组找到值 = val
double * find_dr(double *arr, int n, const double & val) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == val) {
            return &arr[i];
        }
    }

    return nullptr;
}

struct Node {
    double ele;
    Node *next;
};

//在node数组中找到val
Node* find_nd(Node *head, const double &val) {
    Node *start;
    for (start = head; start != nullptr; start = start->next) {
        if (start->ele == val) {
            return start;
        }
    }

    return nullptr;
}
~~~

两个算法的本质都是遍历容器，查找和容器内值相等的数据，但实现上存在很大的差异。

能否找到一个通用的`find`方法，同时支持数组和链表或者其他容器类型，可以遍历容器内的数据，并且将遍历的值进行通用表示。

迭代器就是这样一个遍历对象（有点像java的iterator)

满足上述查找算法的迭代器特征：

- 通过迭代器访问数值（类比指针，如果p是指针，可通过*p访问指针数据）
- 迭代器之间能够相互赋值，且支持比较操作（p = q，p == q, p != q)
- 能够遍历容器元素，支持p++或者++p的行为来使得迭代器在元素间移动。

~~~c++
//在array数组找到值 = val
using iterator = double *
iterator find_dr(iterator begin, iterator end, const double & val) {
    for (int i = begin; i < end; i++) {
        if (*i == val) {
            return i;
        }
    }

    return end;
}

struct Node {
    double ele;
    Node *next;
};

class Node1 {
private:
    double ele;
    Node1 *next;
    Node1 *current;
public:
    Node1():ele(0.0), next(nullptr), current(this){};
    Node1(double &val) : ele(val), next(nullptr), current(this){}
    double operator*()  {return ele;}
    Node1 &operator++()  {
        if (current->next != nullptr) {
            current = current->next;
            return *current;
        }
      
      	return nullptr;
    }

    bool operator==(Node1 *n) {
        return current == n;
    }
  
  	bool operator!=(Node1 *n) {
      	return !operator==(n);
    }
};

using iterator1 = Node1 *;
iterator1 find_nd(iterator1 head, const double &val) {
  	iterator1 start;
  	for (start = head; start != nullptr; start++) {
      	if (*start == val) {
          return start;
        }
    }
}
~~~

​	每个容器分别为自己的数据定义了不用的迭代器类型，某个容器的迭代器可能是指针，某个容器的迭代器可能是类对象。但是他们都实现了*，++，获取头元素(begin())，获取超尾元素(end())的方法，每个容器再操作对应的迭代器从头指向超尾，实现容器的遍历。

​	我们在使用容器时，无需知道迭代器是如何实现的，只需要知道它有迭代器，且能通过容器的通用方法（`::iterator`，`begin`, `end`)来获取。

~~~c++
vector<double> v1;

vector<double>::iterator iter;
for (iter = v1.begin(); iter != v1.end(); iter++) {
	//...
}
~~~



### 容器

STL具有容器概念和容器类型。概念是具有名称（如容器、序列容器、关联容器等）的通用类别；容器类型是可用于创建具体容器对象的模板。C++11以前的容器类型分别是`deque`、`list`、`queue`、`priority_queue`、`stack`、`vector`、`map`、`multimap`、`set`、`multiset`和`bitset`；C++11新增了`forward_list`、`unordered_map`、`unordered_multimap`、`unordered_set`和`unordered_multiset`

| 容器类型       | 实现     | 容器概念 |
| -------------- | -------- | -------- |
| deque          | 双端队列 |          |
| list           | 双向链表 |          |
| priproty_queue | 双向链表 |          |
| stack          | 栈       |          |
| vector         |          |          |
| map            |          |          |
| multimap       |          |          |
| set            |          |          |
| multiset       |          |          |

#### 容器概念

容器概念描述了所有容器都通用的元素，是一个概念化的抽象类，指定了所有STL容器类必须满足的一系列要求。

容器概念的必要要求：容器内存储的对象必须是同一类型的，可以存储内置对象，也可存储OOP对象，容器过期则数据过期（指针除外）;存储进容器的对象，必须支持可赋值和可拷贝构造（基本类型，未将拷贝构造和赋值设置为私有的OOP类型）

所有的容器都必须提供某些特征和操作。

容器通用特征总结：（“X表示容器类型，如vector；T表示存储在容器中的对象类型；a和b表示类型为X的值；r表示类型为X&的值；u表示类型为X的标识符（即如果X表示`vector<int>`，则u是一个`vector<int>`对象，rv代表X的非常量右值）” 

| 表达式        | 返回类型                  | 说明                                             | 时间复杂度   |
| ------------- | ------------------------- | ------------------------------------------------ | ------------ |
| X::iterator   | 返回指向X元素的迭代器类型 | 满足正向迭代器要求                               | O(1)         |
| X::value_type | T                         | T的类型                                          | O(1)         |
| X u           | X                         | 创建一个空的容器                                 | O(1)         |
| X()           | X                         | 创建一个匿名空容器                               | O(1)         |
| X u(a)        | X                         | 调用容器的拷贝构造函数创建新的容器               | O(n)         |
| X u = a       | X                         | 同X u(a)                                         | O(n)         |
| r = a         | X &                       | 调用容器的赋值重载符                             | O(n)         |
| a.begin()     | 返回指向X元素的迭代器类型 | 返回指向容器第一个元素的迭代器                   | O(1)         |
| a.end()       | 返回指向X元素的迭代器类型 | 返回指向容器最后一个元素下一个（超尾值）的迭代器 | O(1)         |
| a.size()      | int                       | 返回容器内元素的个数                             | O(1)         |
| a.swap(b)     | void                      | 交换a和b的内容                                   | O(1) or O(n) |
| a == b        | bool                      | a和b长度相同且每个元素都相等，返回true           | O(n)         |
| a != b        | bool                      | !(a == b)                                        | O(n)         |
| X u(rv)       | X                         | 移动构造（ C++11）                               | O(n)         |
| X u = rv      | X                         | 移动构造（ C++11)                                | O(n)         |
| a = rv        | X                         | 移动复制（ C++11）                               | O(n)         |
| a.cbegin()    | const_interator           | 返回指向第一个元素的const迭代器                  | O(1)         |
| a.cend()      | const_interator           | 返回指向超尾的const迭代器                        | O(1)         |

注：容器迭代器必须满足正向迭代器，容器必须是序列容器。

##### 序列容器

序列概念增加了迭代器至少是正向迭代器这样的要求，这保证了元素将按特定顺序排列，不会在两次迭代之间发生变化。array也被归类到序列容器，虽然它并不满足序列的所有要求。

deque、forward_list、list、queue、priority_queue、stack和vector都是序列容器。
