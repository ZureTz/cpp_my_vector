# `my::vector` documentation

## 简介

这是一个由**我自己**编写的`C++ vector`模版类，是模仿`std::vector`类设计的，与`std::vector`有着相像的功能，包括`vector`长度的动态分配、自由插入或更改相同类型的元素、迭代器、`range-based loop`、使用`initializer_list`进行初始化和赋值等功能。

- 在此文档中，有自定义的输出[运算符重载](#appendix_output_using_ostream)，以及有关的[类型重定义](#appendix_typename_redifinition)，请参见附录。

- 在此文档中，所有包含头文件和定义`main()`函数入口的行为均省略，在使用该类时，需要手动添加头文件，定义`main()`函数。

## 构造函数

### `vector()`

这是默认的构造函数。当未指定大小时，该`vector`为空。（即vector内的首地址与末地址(`begin()`和`end()`)相等。）

Example Code:

```c++
my::vector<int> vect;
std::cout << vect;
```

> 在`my::vector`类中并没有有关`ostream`的运算符重载，如需要使用`ostream`输出一个`vector`，需要手动重载相关的运算符。在本文档中的相关实现可见[附录](#appendix_output_using_ostream)。

Output:

```
[]
```

### `vector(const int length)`

构造指定长度为`length`的`vector`。

Example Code:

```c++
my::vector<int> vect(5);
std::cout << vect1;
```

Output:

```
[0, 0, 0, 0, 0]
```

### `vector(const self_type &source)/vector(self_type &&source)`

这两个构造函数分别为`Copy Constructor `和`Move Constructor`。创建一个和`Source`所含内容相同的另一个`vector`。

> 需要注意的是，两个`vector`内部所含有的首末指针所含地址不同，二者是互异的，仅仅只是内容相同

Example Code:

```c++
// using default constructor
my::vector<int> vect1(5);
vect1.at(0) = 1;
std::cout << vect1;

// using copy constructor (also using overloaded "=" operator)
my::vector<int> vect2(vect1);
vect2.at(1) = 3;
vect2.at(2) = 5;
std::cout << vect2;
```

Output:

```
[1, 0, 0, 0, 0]
[1, 3, 5, 0, 0]
```

### `vector(const std::initializer_list<element_type> init_list)`

使用`initializer_list`构造一个`vector`，`initializer_list`为在`C++11`中引入的概念，该概念允许使用初始化列表的方式初始化一个对象，拓展了`C`中只能使用初始化列表初始化一个固定内存区域的语法。

Example Code:

```c++
my::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8};
std::cout << vec1;
```

Output:

```
[1, 2, 3, 4, 5, 6, 7, 8]
```

### `vector(const_iterator first, const_iterator last)`

通过`vector`的两个`iterator`，进行初始化，初始化的vector包含两个迭代器之间包含的内容，不允许`first > last`。

Example Code:

```c++
my::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8};
my::vector<int> vec2(vec1.begin(), vec1.end() - 2);
std::cout << vec1 << vec2;
```

Output:

```
[1, 2, 3, 4, 5, 6, 7, 8]
[1, 2, 3, 4, 5, 6]
```

## 析构函数

### `~vector()`

该析构函数不需要直接使用。其作用是在析构时，释放掉当前`vector`所分配的内存。

## 获取整体状态

获取当前`vector`的整体状态。

### `bool empty() const`

获取当前`vector`是否为空（长度/大小是否为`0`）。

Example Code:

```c++
my::vector<int> vect1;
std::cout << vect1.empty() << std::endl;
my::vector<int> vect2{1, 2, 3, 4, 5};
std::cout << vect2.empty() << std::endl;
```

Output:

```
1
0
```

### `size_type size() const/size_type length() const`

取得当前`vector`的大小/长度

> 注意：此方法的复杂度为O(1)。

Example Code:

```c++
my::vector<int> vect1;
std::cout << vect1.size() << std::endl;
std::cout << vect1.length() << std::endl;

my::vector<int> vect2(15);
std::cout << vect2.size() << std::endl;
std::cout << vect2.length() << std::endl;
```

Output:

```
0
0
15
15
```

### `size_type capacity() const`

获取当前`vector`在内存中所占的实际容量。

Example Code:

```c++
my::vector<int> vect1;
std::cout << vect1.capacity() << std::endl;

my::vector<int> vect2(15);
std::cout << vect2.capacity() << std::endl;
```

Output:

```
2
16
```

## 获取特定元素（的引用）

### `element_reference operator[](const int index)`

按照地址偏移量，给出特定位置元素的引用。（为提高性能，没有范围检查）

Example Code：

```c++
my::vector<int> vect{0, 1, 2, 3, 4, 5};
std::cout << vect[2] << std::endl;
// wrong, but no rumtime error
// do not do this, has potential risk
std::cout << vect[-1] << std::endl;
```

Output:

```
2
0 (maybe...)
```

### `element_reference at(const int index)`

按照地址偏移量，给出特定位置元素的引用。

Example Code:

```c++
my::vector<int> vect{0, 1, 2, 3, 4, 5};
std::cout << vect.at(2) << std::endl;
// has runtime error
// std::cout << vect.at(-1) << std::endl;
```

Output:

```
2
```

### `element_reference front()/const_element_reference front() const`

给出该`vector`第一个元素的引用。

Example Code:

```c++
my::vector<int> vect{0, 1, 2, 3, 4, 5};
std::cout << vect.front() << std::endl;
```

Output:

```
0
```

### `element_reference back()/const_element_reference back() const`

给出该`vector`最后一个元素的引用。

Example Code:

```c++
my::vector<int> vect{0, 1, 2, 3, 4, 5};
std::cout << vect.back() << std::endl;
```

Output:

```
5
```

### `iterator begin() const`

给出第一个元素的迭代器。

Example Code:

```c++
my::vector<int> vect{0, 1, 2, 3, 4, 5};
std::cout << *vect.begin() << std::endl;
```

Output:

```
0
```

### `iterator end() const`

给出一个迭代器，指向最后一个元素之后的一个位置。

Example Code:

```c++
my::vector<int> vect{0, 1, 2, 3, 4, 5};
std::cout << *(vect.end() - 1) << std::endl;
```

Output:

```
5
```

## 比较运算符

### `bool operator==(const self_type &rhs) const/bool operator!=(const self_type &rhs) const`

比较两个`vector`在长度和每个元素上是否都相等。

Example Code:

```c++
my::vector<int> vect1{0, 1, 2, 3, 4, 5};
my::vector<int> vect2{0, 1, 2, 3, 4};
my::vector<int> vect3{0, 1, 2, 3, 4, 5};
std::cout << (vect1 == vect2) << " " << (vect1 == vect3) << std::endl;
std::cout << (vect1 != vect2) << " " << (vect1 != vect3) << std::endl;
```

Output:

```
0 1
1 0
```



## Range-Based Loop

使用C++11提供的新语法，进行for循环。

> 具体实现方式可以参考[链接](https://stackoverflow.com/questions/8164567/how-to-make-my-custom-type-to-work-with-range-based-for-loops)，简单来说，需要在容器内实现一个`iterator`，支持解引用，自增，自减，以及比较运算符，在容器内实现`begin()`和`end()`类方法，返回首个元素的`iterator`以及末尾的`iterator`。

Example Code:

```c++
my::vector<int> vect1{0, 1, 2, 3, 4, 5};
for (const auto it : vect1) {
  std::cout << it << " ";
}
```

Output:

```
0 1 2 3 4 5 
```

## 改变元素/状态

### `self_type &resize(const int size)`

重置当前`vector`到给定的大小。

> 使用了在g++和MSVC等编译器在实现vector容器中引入的[vector增长因子](https://www.zhihu.com/question/36538542)。在这个类的实现中，增长因子为`2`，即当`vector`空间已满时，会重新分配大小为原`vector`的`2`倍大小的空间。这也是`allocator`的基本实现。
>
> - 如果给定的大小小于当前的`size()`，那么将会忽略给定大小之后的元素。
> - 如果给定的大小大于或等于当前的`size()`但是小于当前的`capacity()`，则会在不重新申请新的空间下，将vector末尾的指针移到指定的大小处。
> - 如果给定的大小大于当前的`capacity()`，那么会重新申请并分配大小为当前`capacity()`两倍的空间，并将原来的内容按顺序拷贝到新的空间中。

Example Code:

```c++
my::vector<int> vect1{0, 1, 2, 3, 4, 5};
std::cout << vect1;
std::cout << vect1.size() << " " << vect1.capacity() << std::endl;
vect1.resize(15);
std::cout << vect1;
std::cout << vect1.size() << " " << vect1.capacity() << std::endl;
vect1.resize(4);
std::cout << vect1;
std::cout << vect1.size() << " " << vect1.capacity() << std::endl;
```

Output:

```
[0, 1, 2, 3, 4, 5]
6 8
[0, 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0]
15 16
[0, 1, 2, 3]
4 16
```

## 其他

- `self_type &push_front(element_right_reference argument)/self_type &push_front(const_element_reference argument)`

- `self_type &push_back(element_right_reference argument)/self_type &push_back(const_element_reference argument)`

- `self_type &pop_front()`

- `self_type &pop_back()`

- `element_type pop_back(element_reference out_param)`

- `self_type &insert(const_iterator position, const_element_reference val)`

- `self_type &insert(const_iterator position, size_type num, const_element_reference val)`

- `self_type &insert(const_iterator position, InputIterator first, InputIterator last)`

- `self_type &insert(const_iterator position, element_right_reference val)`

- `self_type &insert(const_iterator position, std::initializer_list<element_type> object)`

- `self_type &erase(const_iterator position)`

- `self_type &erase(const_iterator first, const_iterator end)`

- `self_type &clear()`

- `self_type &reverse()`

- `self_type slice(const_iterator begin, const_iterator end)`

- `void swap(self_type &object)`

- `self_type &operator=(const self_type &object)`

- `self_type &operator=(self_type &&object)`

- `self_type &operator=(const std::initializer_list<element_type> init_list)`

Example Code:

```c++
my::vector<int> vect1{0, 1, 2, 3, 4, 5};
my::vector<int> vect2{1, 2, 3};
vect1.insert(vect1.begin() + 3, vect2.begin(), vect2.end());
std::cout << vect1;
vect1.insert(vect1.begin(), static_cast<size_t>(3), 3);
std::cout << vect1;
vect1.insert(vect1.begin() + 2, {2, 0, 4, 2, 5, 4});
std::cout << vect1;
vect1.insert(vect1.end(), 1145);
std::cout << vect1;
vect1.erase(vect1.begin() + 3);
std::cout << vect1;
vect1.erase(vect1.begin() + 2, vect1.end() - 7);
std::cout << vect1;
vect1.push_back(3).push_front(6).push_back(9);
std::cout << vect1;
vect1.reverse();
std::cout << vect1;
```

Output:

```
[0, 1, 2, 1, 2, 3, 3, 4, 5]
[3, 3, 3, 0, 1, 2, 1, 2, 3, 3, 4, 5]
[3, 3, 2, 0, 4, 2, 5, 4, 3, 0, 1, 2, 1, 2, 3, 3, 4, 5]
[3, 3, 2, 0, 4, 2, 5, 4, 3, 0, 1, 2, 1, 2, 3, 3, 4, 5, 1145]
[3, 3, 2, 4, 2, 5, 4, 3, 0, 1, 2, 1, 2, 3, 3, 4, 5, 1145]
[3, 3, 1, 2, 3, 3, 4, 5, 1145]
[6, 3, 3, 1, 2, 3, 3, 4, 5, 1145, 3, 9]
[9, 3, 1145, 5, 4, 3, 3, 2, 1, 3, 3, 6]
```

> 更多的示例代码，可以参见`test.cpp`。

## 迭代器

实现方法与C++ STL的方法类似，用法基本相同，具体用法参见[C++参考手册](https://zh.cppreference.com/mwiki/index.php?title=首页&variant=zh-cn)。



## 附录

### 类型重定义

<span id="appendix_typename_redifinition">Code, written in header:</span>

```c++
// header files...

template <typename T>
class vector{
// ......
// ......

// in class vector<T>:
/* Type definitions */
  typedef T element_type;
  typedef T *element_pointer;
  typedef T &element_reference;
  typedef T &&element_right_reference;
  typedef const T *const_element_pointer;
  typedef const T &const_element_reference;
  typedef size_t size_type;
  typedef vector<T> self_type;
  
// ......
// ......

  class const_iterator{
  // in class vector<T>::const_iterator:
  public:
  /* Type definitions */
    typedef const_iterator self_type;

  // ......
  // ......
  };

  class iterator: public const_iterator{
  // in class vector<T>::iterator:
  public:
  /* Type definitions */
    typedef iterator self_type;

  // ......
  // ......
  }
    
};
```

### 有关使用`ostream`进行输出`vector`的运算符重载

此处借鉴了`Python`对`list`进行输出的格式。

<span id="appendix_output_using_ostream">Example Code:</span>

```c++
// output the vector using operator "<<"
template <typename T>
std::ostream &operator<<(std::ostream &os, const my::vector<T> &vect) {
  if (vect.empty()) {
    os << "[]" << std::endl;
    return os;
  }

  os << '[';
  for (typename my::vector<T>::iterator it = vect.begin(); it != vect.end() - 1;
       it++) {
    os << *it << ", ";
  }
  os << vect.back() << ']' << std::endl;

  return os;
}
```