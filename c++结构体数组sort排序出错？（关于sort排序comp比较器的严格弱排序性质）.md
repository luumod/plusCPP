@[toc]

# sort的严格弱排序的性质
我在给结构体数组排序的时候，自定义了sort函数的排序法则，我的结构体如下定义：

```cpp
struct score
{
	int a, b, c;//语数英
	int sum;	//总分
	int num;	//学号
};
```
排序标准：

* 首先按照总分排序
* 总分相同的情况下按照语文成绩a排序
* 再相同的情况下，按照学号的大小排序，因此经过这三重检测，最后得到的一定是已经排序好的。


----



**无效的比较器！**
![在这里插入图片描述](https://img-blog.csdnimg.cn/e52cf781dfdf45288716044a37127810.png)

-----

原因：参考cplusplus中对于comp比较规则的解析。
>comp
Binary function that accepts two elements in the range as arguments, and returns a value convertible to bool. The value returned indicates whether the element passed as first argument is considered to go before the second in the specific strict weak ordering it defines.
The function shall not modify any of its arguments.
This can either be a function pointer or a function object.

即comp必须是一个**严格弱排序**的性质的比较器。

严格弱排序：（a=50,b=60） a < b

1. 对于a < b，满足  a < b
2. 若交换两数： a=60，b=50,此时应该返回false， 60 < 50（不满足，返回false）

----

比如说我有这样一个例子：

```cpp
struct A
{
	int num;
};
bool comp(A a, A b)
{
	return a.num >= b.num;
}
A a[2];
a[0].num = 11;	//两个值相等！！！！！
a[1].num = 11;	//会出现比较错误！！！
sort(a, a + 2, comp);
```
==**在sort函数比较的时候，它会严格弱排序，比较 a是否 >= b，然后两个对象会进行交换，重新比较一遍，相当于这次比较的是 b是否>= a**==

1. **a >= b ？ 满足： true**
2. **b <= a  ?  满足： true** 
3. 这样就出现了一个冲突，不管是a >= b还是b >= a都会返回true的情况，我们都知道sort中只要comp返回true，两个元素就会交换一次，因此comp返回两次true，会对两个元素交换两次，**相当于没有交换**，因此就会出现无效的比较器的情况。
4. **正确的交换方式： 当 == 的时候，他们不用交换就可以了，此时如果两个元素相等，则都返回false，因此两次false，在sort中就不用交换，因此达到了等于时不交换的目标。**

```cpp
bool comp(A a, A b)
{
	return a.num > b.num;	//去除=的判断，
}

```

----

再回到本题：

## 无效的比较器（Invalid comparator）
我们自定义的排序法则如下定义：
* 首先按照总分排序
* 总分相同的情况下按照语文成绩a排序
* 再相同的情况下，按照学号的大小排序，因此经过这三重检测，最后得到的一定是已经排序好的。

```cpp
bool comp2(struct score sc1, struct score sc2)
{
	//总分高的在前面
	if (sc1.sum > sc2.sum)
	{
		return true;
	}
	//如果总分相同，则a表示语文成绩，语文成绩高的在前面
	if (sc1.a > sc2.a)
	{
		return true;
	}
	//总分和语文成绩都相等，则num学号小的在前面
	if (sc1.num < sc2.num)
	{
		return true;
	}
	return false;
}
```

然后在我创建变量，并且输入进行排序后

```cpp
sort(sc + 1, sc + 1 + n, comp2);
```

严格弱排序，检查两个数分别互换位置的比较情况：

假设我比较的两个数字：
*  sc1 ： 2 244（a=84）  
* sc2： 1 237（a=90）

1. sc1 与 sc2 的检查：首先检查总分： **244>237 ，第一个if满足，返回true。**
2. sc2 与 sc1 的检查（sc1=sc2，sc2=sc1）**然后交换两个对象（进行弱排序比较）**：237 < 244，第一个if不满足，**90 > 84，第二个if满足，返回true。**
3. 此时返回了两次true，表明这两个对象要交换两次，但实际上就像等于没交换，但是sort一定要进行一次交换，因此出现 **无效的比较器！！**


如何解决这个问题呢？

----

## 正确的比较器

```cpp
bool comp1( struct score sc1,   struct score sc2)
{
	//分数高的在前面
	if (sc1.sum > sc2.sum)
	{
		return true;
	}
	//如果总分一样，则语文成绩大的在前面
	if (sc1.sum == sc2.sum && sc1.a > sc2.a)
	{
		return true;
	}
	///如果前两项都一样，则学号小的在前面
	if (sc1.sum == sc2.sum && sc1.a == sc2.a && sc1.num < sc2.num)
	{
		return true;
	}
	//如果都不满足，返回false
	return false;
}
```

再来比较这两个对象： （我们可以猜测出来，**排序后位序（总分）： sc2, sc1**）
* sc1： 1 237（a=90）
* sc2 ： 2 244（a=84）  

1. sc1 比较 sc2：首先244>237 ，返回true
2. **sc1=sc2 比较 sc2=sc1，交换后比较**：237 < 244，第一个if不满足，同时他们的总分不同，无法进入第二个if，也不满足，同理第三个if也不满足，最终返回false。
3. 一个返回true，一个返回false，满足comp的比较准则，因此sc1与sc2交换，不会产生无效的比较准则，**因为在if语句的前面都加上了必须首先不满足前一项的要求，然后才能进行优先级第二的比较准则。**


---

两个比较条件的比较:

```cpp
//错误的排序比较器
bool compOk(struct score sc1, struct score sc2)
{
	if (sc1.sum > sc2.sum)
	{
		return true;
	}
	if (sc1.a > sc2.a)
	{
		return true;
	}
	if (sc1.num < sc2.num)
	{
		return true;
	}
	return false;
}
//正确的比较器
bool compError( struct score sc1,   struct score sc2)
{
	if (sc1.sum > sc2.sum)
	{
		return true;
	}
	if (sc1.sum == sc2.sum && sc1.a > sc2.a)
	{
		return true;
	}
	if (sc1.sum == sc2.sum && sc1.a == sc2.a && sc1.num < sc2.num)
	{
		return true;
	}
	return false;
}
```

