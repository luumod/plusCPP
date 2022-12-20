
@[toc]

# allocator
标准库allocator类定义在头文件memory中，他帮助我们把内存分配和对象的构造分离开来，提供一种类型感知的内存分配的方法。

>#include < memory >


* 指明使用allocator可以分配的对象的类型：

```cpp
allocator<string> alloc;	//表明alloc可以分配string的allocator对象
```

---

* 分配内存空间

```cpp
constexpr auto n=3;	//可以接受常量或者变量
auto p = alloc.allocate(n);		//分配了三个string内存空间给了p 
```
分配之后，p是string* 类型。相当于new string[ 3 ]，但是使用alloc分配的内存是未构造的。

---

* 在内存中构造对象

由于 由alloc分配的内存是未构造的，我们无法使用普通的赋值来给它赋予初始值，例如：

```cpp
string* str = new string[n];
for (int i = 0; i < n; i++)
{
	*str++ = "abc";	//可以赋值
}
for (int i = 0; i < 3; i++)
{
	*p++ = "abc";	//ERROR： 未构造的，无法进行赋值操作
}
```
因此，在使用alloc分配的内存我们需要使用**construct进行构造对象**，来完成初始化或者赋值。

正确方式：这样我们就可以完成对分配的内存构造成对象，并且进行赋值。

```cpp
q=p;	//使用q来记录它的位置，p始终保存着分配的内存的起始位置
for (int i = 0; i < n; i++)
{
	string s;
	cin >> s;
	alloc.construct(q, s);	//构造对象
}
```
注意：我们的**construct第一个参数必须是指向未构造的内存空间**，后面的参数为可变参数，表示接受一个**构造函数**，在这里我们指定它接受默认的string的构造函数。

> 警告： 使用allocator分配的内存一定要使用construct来进行构造对象，使用未构造的内存其行为是未定义的。

---


* 销毁对象

destroy可以销毁每一个构造的对象，相当于对这个对象执行它自己的析构函数。

```cpp
//销毁构造的对象：q指向的是当前的对象，p指向的是我们的内存的起始位置
while (q != p)
{
	//释放每一个string对象:对string*执行析构操作
	alloc.destroy(--q);
}
```
从后往前，依次进行string对象的销毁。但是请注意，**我们只是析构这个对象，我们开辟的这段空间并未释放。**


----

* 释放内存空间

使用deallocate来释放开辟的内存空间。

```cpp
//最后再释放内存块:  deallocate一定要在destroy执行之后再执行
alloc.deallocate(p, n);
```


----

## 一个完整的allocator分配内存的过程

```cpp
#include <iostream>
#include <memory>
#include <vld.h>
#include <vector>
using namespace std;

int main()
{
	//使用allocator
	constexpr auto n = 3;
	allocator<string> alloc;	//可以分配string的allocator对象
	auto p = alloc.allocate(n);		//分配了三个string内存空间给了p
	string s;
	auto q = p;
	while (q != p + n && cin >> s)
	{
		/*
		在alloc分配的内存是未构造的，必须使用construct来构造对象，使用原始内存
		*/
		alloc.construct(q++, s);
	}
	//打印输出构造的对象:保存原始位置，使用一个临时的beg指针
	auto beg = p;
	while (beg != q)
	{
		cout << *beg++ << " ";
	}
	//销毁构造的对象
	while (q != p)
	{
		//释放每一个string对象:对string*执行析构操作
		alloc.destroy(--q);
	}
	//最后再释放内存块:  deallocate一定要在destroy执行之后再执行
	alloc.deallocate(p, n);
	return 0;
}
```

使用allocator开辟的内存比使用new开辟的内存空间更加安全。

---

## allocator算法

allocator类具有两个伴随算法， 方便进行空间的使用与创建，它们分别是
* uninitialized_copy：拷贝指定范围的元素到新创建的未构造的内存空间中。
* uninitialized_fill_n：填充元素到新创建的未构造的内存空间中。

---
举例： 将一个vector数组扩大一倍，并且把序列中的内从拷贝到我们开辟的动态内存中，多余的未构造的空间进行默认初始化。

```cpp
/*
拷贝与填充未初始化的内存
*/
vector<int> vec{ 1,2,3,4,5 };
allocator<int> allocInt;
//分配比原始的vector内存空间大两倍的空间
auto vecP =  allocInt.allocate(vec.size() * 2);
//原始的内容拷贝到新的内存空间中
auto vecq =  uninitialized_copy(vec.begin(), vec.end(), vecP);
//剩下的一半内存空间填充
uninitialized_fill_n(vecq++, vec.size(), 6);
//释放内存
allocInt.deallocate(vecP, vec.size() * 2);
```

uninitialized_copy： 返回值==是拷贝完成后剩余未构造的内存空间的起始位置。==
uninitialized_fill_n：把前一个函数返回值当作第一个参数，表示从这里开始，填充指定数量的值往剩余的空间中。

----
