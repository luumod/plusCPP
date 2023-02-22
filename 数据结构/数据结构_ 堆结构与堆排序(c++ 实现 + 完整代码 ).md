# 堆结构与堆排序
@[toc]
## 引入堆

* 二叉树
具有左孩子与右孩子的最普通的二叉树。

* 满二叉树
  **特殊的二叉树：每个节点如果有孩子则一定同时具有左孩子与右孩子。**

满二叉树的条件：

  1. 要么有两个孩子，要么没有孩子
  2. 叶子节点在同一层

> 
>满二叉树有如下规律：
​如果层数为n
第n层节点数  一定为  2^(n-1)
整颗树节点数  为   2^n - 1


----
* 完全二叉树
能够使得满二叉树 从 **下边和右边**开始删节点的 二叉树 , 满足从右往左  从下往上删除 （和 阅读顺序 相反）

  1. 满二叉树一定是完全二叉树

  2. 完全二叉树不一定是满二叉树

* 堆

  ​	堆是有序的完全二叉树。 

  ​	父子之间必须有序，父大于子或者子大于父，同层兄弟之间不用管

  1. 父大于子：最大堆（大顶堆）
  2. 子大于父：最小堆（小顶堆）



## 堆结构所满足的数学特性
![在这里插入图片描述](https://img-blog.csdnimg.cn/ce60571321d2468c9c0e8083779df2e1.png)

下标关系： 

* 150 的 下标为 0 ，260 的下标为1，290的下标为3，400的下标为7。共同点：都是父节点的**左孩子**，父节点的下标*2+1=左孩子的下标

* 150的下标为0，300的下标为2，400的下标为6；260的下标为1，320的下标为4，500的下标为10。共同点：都是父节点的**右孩子**，父节点的下标*2+2=右孩子的下标

* 相反，已知400的下标为7，则290的下标为3，260的下标为1。共同点：已知左孩子的下标，（左孩子下标-1）/2得到父节点的下标

* 已知500的下标为10，320的下标为4，260 的下标为1。共同点：已知右孩子的下标，（右孩子下标-2）/2得到父节点的下标

  > 总结： 
  >
  > **父亲推孩子：**
  >
  > 已知父节点下标为N
  > 左孩子下标为：2*N + 1
  >
  > 右孩子下标为：2*N + 2
  >
  > **孩子反推父亲：**
  >
  > 已知左孩子下标为M 父节点下标为： (M-1)/2
  > 已知右孩子下标为M 父节点下标为： (M-2)/2
  >
  > 已知**孩子下标**为M 父节点下标为： (M-1)/2

## 准备代码

```cpp
template <class T>
class My_Heap
{
private:
	T* pRoot;	//指向堆的指针，实际上是一个动态数组
	int len;	//元素个数
	int MaxLen;	//容量
public:
	My_Heap()
	{
		pRoot = nullptr;
		len = MaxLen = 0;
	}
	~My_Heap()
	{
		delete[] pRoot;
		pRoot = nullptr;
		len = MaxLen = 0;
	}

	//往堆中插入元素
	void insert(const T& data);
	//遍历
	void travel()const;
	//删除堆顶
	T pop();
};
```

## 往堆中插入元素 (upd)

我们采用 **小顶堆**的方式，即保证孩子节点要比父亲节点大。
采用动态内存分配的方法，插入一个节点到数组中。
从**堆底**开始，根据**下标关系**找到对应的父节点.

插入步骤：（小顶堆）

1. 比较插入节点与当前父节点的关系
2. **如果比父节点小，则当前节点需要上提，交换当前节点与父节点的值**
3. **如果比父节点大，则说明不冲突，则直接退出即可，因为经过以前的处理此情况一定是合法的。**
4. 继续比较，直到不冲突或者到达了根节点为止。

**注意：我们使用自底向上的方式，每次比较当前节点与父节点的关系，然后需要将当前节点往上提，继续比较和上一层的关系**


图例：
![在这里插入图片描述](https://img-blog.csdnimg.cn/9f86c70c9842417087321d7691db69f3.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/79bc45086e594b1686fee94ebdac84b7.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/aa39420e701a4f5f89d82d064eea334e.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/d6473c28cb174d578216d5de64d9c4a4.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/ce6c1fa9159a472b880bc88be18f22cd.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/e183bf2ae05d4ad8931960db67918dc8.png)

要点：**从下往上**遍历，交换不合适的节点。

```cpp
template<class T>
inline void My_Heap<T>::insert(const T& data)
{
	//动态数组
	//1 像动态数组一样进来
	if (MaxLen <= len) {//需要申请
		//计算需要申请的内存大小   //>>1 右移一位 等同于除以2
		MaxLen = MaxLen + (((MaxLen >> 1) > 1) ? (MaxLen >> 1) : 1);
		//1 开内存
		T* pNew = new T[MaxLen];
		if (pRoot) {
			//2 pArr指向内存段中数据拷贝到pNew指向内存段
			memcpy(pNew, pRoot, sizeof(T) * len);
			//3 释放pArr指向内存段
			delete[] pRoot;
		}
		//4 pArr指向新开内存
		pRoot = pNew;
	}
	pRoot[len++] = data;

	//循环和父节点比较，如果冲突交换，不冲突，覆盖
	if (len == 1)
	{
		return;
	}
	int CurrentIdx= len - 1;				//孩子节点
	int ParentIdx = (CurrentIdx - 1) / 2;	//父节点
	T temp;
	while (1)
	{
		if (CurrentIdx <= 0)
			break;		//没有父节点，循环结束
		ParentIdx = (CurrentIdx - 1) / 2;
		if (pRoot[ParentIdx] < pRoot[CurrentIdx])
			break;	//不冲突，孩子父亲大，则停止
		//否则，交换元素
		temp = pRoot[ParentIdx];
		pRoot[ParentIdx] = pRoot[CurrentIdx];
		pRoot[CurrentIdx] = temp;
		//遍历完一次后，接着往上移动，开始重新一次比较
		CurrentIdx = ParentIdx;
	}
}
```
不使用动态内存分配：

```cpp
void InsertData(int val)
	{
		arr[++this->size] = val;
		if (this->size == 1) return;
		int curLen = this->size;//当前节点
		int parentLen = curLen >> 1;//父节点
		while (true)
		{
			if (curLen <= 1) break;//到达根节点，退出
			//比较和父节点的关系，比父节点小则交换
			parentLen = curLen >> 1;
			if (arr[curLen] > arr[parentLen])
			{
				break;
			}
			swap(arr[curLen], arr[parentLen]);
			curLen = parentLen;
		}
	}
```



## 删除堆顶 (upd)

从堆顶开始，把**最后一个元素覆盖堆顶元素**，接着根据下标关系，找到堆顶的孩子节点，比较两个孩子谁是最小孩子，如果堆顶比最小孩子节点小，则退出（小顶堆）。否则，交换两个节点，要保证父小于子。然后顶堆往下移动，移动到下一层的父节点，比较父子关系。确保在覆盖了原堆顶（即删除了原堆顶）后，整个堆结构仍然是以小堆顶的结构，因此要进行重排，直到数组下标越界为止。

步骤：

1. 最后一个元素覆盖堆顶元素
2. 当前节点寻找两个孩子节点的最小的那个，并且把那个最小的与当前节点的值作交换
3. 当前节点下移，继续寻找最小的元素并且作交换
4. 直到超过了下界之后停止。


**注意：如果堆顶元素比左右孩子最小的元素都小，则不冲突，因此直接结束循环**

图例：

![在这里插入图片描述](https://img-blog.csdnimg.cn/c00aa7450b0e4ecebc6f0d75cc911edb.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/351886f002b746d48d3a9091be8f9417.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/551e50a7cd49464a96ca8c94a671c87f.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/eeb4c251b69e4e2a99a237feba061fcc.png)

要点：**从上往下**遍历，重排堆结构的父子关系。

```cpp
template <class T>
//删除堆顶
T MyHeap<T>::pop(){
	if (0 == len){
		cout << "堆为空，删除失败!" << endl;
		return (T)0;
	}//没法删
	if (1 == len){//只有一个
		len--;
		return pRoot[0];
	}
	//1 临时保存堆顶元素
	T temp = pRoot[0];
	//2 最后一个覆盖堆顶元素
	pRoot[0] = pRoot[len - 1];
	//3 循环  
	int currentIdx = 0;//从堆顶开始
	int minChildIdx;
	while (1){
		//数组结束 
		if ((currentIdx * 2 + 1) > (len - 1) ||
			(currentIdx * 2 + 2) > (len - 1)){
			break;
		}
		// 找到最小的孩子 
		minChildIdx = currentIdx * 2 + 1;//假定左孩子比较小
		//如果左孩子比右孩子大，右孩子最小
		if (pRoot[minChildIdx] > pRoot[minChildIdx + 1]) 
			minChildIdx++;
		//比最小孩子还小 循环结束
		if (pRoot[len-1] < pRoot[minChildIdx]) break;
		//当前位置和最小孩子交换 //子覆盖父
        //简单交换方式
        temp1 = pRoot[CurrentIdx];
		pRoot[CurrentIdx] = pRoot[MinChildIdx];
		pRoot[MinChildIdx] = temp1;
		//往下移动
		currentIdx = minChildIdx;
	}

	//4 返回
	len--;
	return temp;
}
```
不使用动态内存分配

```cpp
int pop()
	{
		/*
		删除堆顶元素
		*/
		if (this->size == 1)
		{
			this->size = 0;
			return arr[1];
		}
		//1. 最后一个元素覆盖堆顶元素
		int temp = arr[1];
		arr[1] = arr[this->size];
		int curLen = 1;//当前节点
		int childLen = curLen << 1;//孩子节点
		while (true)
		{
			//下移超过了边界则退出
			if (((curLen << 1) > this->size) || (curLen << 1 | 1) > this->size)
			{
				break;
			}
			//找到两个孩子中最小的一个
			childLen = curLen << 1;//默认最小的是左孩子
			if (arr[childLen] > arr[childLen + 1])
			{
				childLen += 1;//最小的为右孩子
			}
			//堆顶比最小的孩子还小，则无需交换
			if (arr[this->size] < arr[childLen]) break;
			//交换当前节点与孩子节点的值
			swap(arr[childLen], arr[curLen]);
			curLen = childLen;//下移到孩子
		}
		this->size--;//最后总的个数要减一个
		return temp;
	}
```

## 堆排序构建

```cpp
template <class T>
//直接用数组方式来构建堆
void MyHeap<T>::initHeap(T* pArr, int size){
	//开内存
	maxLen = size;
	len = 0;
	pRoot = new T[size];
	//数据进来
	pRoot[len++] = pArr[0];//第一个
	int currentIdx;
	int parentIdx;
	for (int i = 1; i < size; i++){
		currentIdx = len;
		parentIdx = (currentIdx - 1) / 2;


		//数据先放进来
		pRoot[currentIdx] = pArr[i];

		while (1){
			if (currentIdx <= 0) break;//没有父节点 循环结束
			parentIdx = (currentIdx - 1) / 2;
			if (pRoot[parentIdx] < pRoot[currentIdx]) break;

			//冲突 父节点覆盖子节点
			pRoot[currentIdx] = pRoot[parentIdx];
			//往上移
			currentIdx = parentIdx;
		}
		//新数据覆盖回来
		pRoot[currentIdx] = pArr[i];
		//个数增加
		len++;
	}
}
```

## 完整代码及测试
![在这里插入图片描述](https://img-blog.csdnimg.cn/af5550584a1249ef8d339e2d78af31b4.png)

```cpp
#pragma once
#include <iostream>
using namespace std;
template <class T>
class My_Heap
{
private:
	T* pRoot;	//指向堆的指针，实际上是一个动态数组
	int len;	//元素个数
	int MaxLen;	//容量
public:
	My_Heap()
	{
		pRoot = nullptr;
		len = MaxLen = 0;
	}
	~My_Heap()
	{
		delete[] pRoot;
		pRoot = nullptr;
		len = MaxLen = 0;
	}

	//往堆中插入元素
	void insert(const T& data);
	//遍历
	void travel()const;
	//删除堆顶
	T pop();
	void initHeap(T* pArr, int size);
};

template<class T>
inline void My_Heap<T>::insert(const T& data)
{
	//动态数组
	//1 像动态数组一样进来
	if (MaxLen <= len) {//需要申请
		//计算需要申请的内存大小   //>>1 右移一位 等同于除以2
		MaxLen = MaxLen + (((MaxLen >> 1) > 1) ? (MaxLen >> 1) : 1);
		//1 开内存
		T* pNew = new T[MaxLen];
		if (pRoot) {
			//2 pArr指向内存段中数据拷贝到pNew指向内存段
			memcpy(pNew, pRoot, sizeof(T) * len);
			//3 释放pArr指向内存段
			delete[] pRoot;
		}
		//4 pArr指向新开内存
		pRoot = pNew;
	}
	pRoot[len++] = data;

	//循环和父节点比较，如果冲突交换，不冲突，覆盖
	if (len == 1)
	{
		return;
	}
	int CurrentIdx= len - 1;				//孩子节点
	int ParentIdx = (CurrentIdx - 1) / 2;	//父节点
	T temp;
	while (1)
	{
		if (CurrentIdx <= 0)
			break;		//没有父节点，循环结束
		ParentIdx = (CurrentIdx - 1) / 2;
		if (pRoot[ParentIdx] < pRoot[CurrentIdx])
			break;	//不冲突，循环继续
		//效率较低
		temp = pRoot[ParentIdx];
		pRoot[ParentIdx] = pRoot[CurrentIdx];
		pRoot[CurrentIdx] = temp;
		//往上移动
		CurrentIdx = ParentIdx;
	}
}

template<class T>
inline void My_Heap<T>::travel() const
{
	for (int i = 0; i < len; i++)
	{
		cout << pRoot[i] << " ";
	}
	cout << endl;
}

template<class T>
inline T My_Heap<T>::pop()
{
	if (len == 0)
	{
		cout << "堆为空!\n";
		return (T)0;
	}
	if (len == 1)
	{
		len--;	//只有一个元素
		return pRoot[0];
	}

	//1. 临时保存堆顶元素
	T temp = pRoot[0];
	T temp1;
	//2. 最后一个元素覆盖堆顶元素
	pRoot[0] = pRoot[len - 1];

	//从堆顶开始
	int CurrentIdx = 0;
	int MinChildIdx;
	while (1)
	{
		//越界
		if ((CurrentIdx * 2 + 1) > (len - 1) ||
			(CurrentIdx * 2 + 2) > (len - 1))
		{
			break;
		}
		//找到最小孩子
		//先假设左孩子比较小
		MinChildIdx = CurrentIdx * 2 + 1;
		if (pRoot[MinChildIdx] > pRoot[MinChildIdx + 1])
		{
			MinChildIdx++;	//右孩子比较小
		}
		//如果比最小孩子还小
		if (pRoot[len-1] < pRoot[MinChildIdx])
			break;
		//需要交换，采用简单交换, 子覆盖父
		temp1 = pRoot[CurrentIdx];
		pRoot[CurrentIdx] = pRoot[MinChildIdx];
		pRoot[MinChildIdx] = temp1;
		//父节点往下移动
		CurrentIdx = MinChildIdx;
	}

	len--;
	return temp;
}

template <class T>
//直接用数组方式来构建堆
void My_Heap<T>::initHeap(T* pArr, int size) {
	//开内存
	MaxLen = size;
	len = 0;
	pRoot = new T[size];
	//数据进来
	pRoot[len++] = pArr[0];//第一个
	int currentIdx;
	int parentIdx;
	for (int i = 1; i < size; i++) {
		currentIdx = len;
		parentIdx = (currentIdx - 1) / 2;


		//数据先放进来
		pRoot[currentIdx] = pArr[i];

		while (1) {
			if (currentIdx <= 0) break;//没有父节点 循环结束
			parentIdx = (currentIdx - 1) / 2;
			if (pRoot[parentIdx] < pRoot[currentIdx]) break;

			//冲突 父节点覆盖子节点
			pRoot[currentIdx] = pRoot[parentIdx];
			//往上移
			currentIdx = parentIdx;
		}
		//新数据覆盖回来
		pRoot[currentIdx] = pArr[i];
		//个数增加
		len++;
	}
}
```

```cpp
#include "MyHeap.h"

#define NUM 11
int main()
{
	int arr[NUM] = { 150,260,300,290,320,350,500,400,450,490,500 };
	My_Heap<int> a;

	/*for (int i = 0; i < NUM; i++)
	{
		a.insert(arr[i]);
		a.travel();
	}*/
	a.initHeap(arr, NUM);
	a.travel();
	return 0;
}

```

# 完整代码及测试 (upd)


[P1177 【模板】快速排序 ----排序测试](https://www.luogu.com.cn/problem/P1177)


Ac code
```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
#define int long long
const int N = 1e5 + 10;
const int CurSize = 1e5 + 10;
struct Tree
{
	int arr[N];
	int size;
	Tree() { memset(arr, 0, sizeof(arr)); size = 0; }
	void InsertData(int val)
	{
		arr[++this->size] = val;
		if (this->size == 1) return;
		int curLen = this->size;//当前节点
		int parentLen = curLen >> 1;//父节点
		while (true)
		{
			if (curLen <= 1) break;//到达根节点，退出
			//比较和父节点的关系，比父节点小则交换
			parentLen = curLen >> 1;
			if (arr[curLen] > arr[parentLen])
			{
				break;
			}
			swap(arr[curLen], arr[parentLen]);
			curLen = parentLen;
		}
	}
	int pop()
	{
		/*
		删除堆顶元素
		*/
		if (this->size == 1)
		{
			this->size = 0;
			return arr[1];
		}
		//1. 最后一个元素覆盖堆顶元素
		int temp = arr[1];
		arr[1] = arr[this->size];
		int curLen = 1;//当前节点
		int childLen = curLen << 1;//孩子节点
		while (true)
		{
			//下移超过了边界则退出
			if (((curLen << 1) > this->size) || (curLen << 1 | 1) > this->size)
			{
				break;
			}
			//找到两个孩子中最小的一个
			childLen = curLen << 1;//默认最小的是左孩子
			if (arr[childLen] > arr[childLen + 1])
			{
				childLen += 1;//最小的为右孩子
			}
			//堆顶比最小的孩子还小，则无需交换
			if (arr[this->size] < arr[childLen]) break;
			//交换当前节点与孩子节点的值
			swap(arr[childLen], arr[curLen]);
			curLen = childLen;//下移到孩子
		}
		this->size--;//最后总的个数要减一个
		return temp;
	}
};
signed main()
{
	Tree t;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int p;
		cin >> p;
		t.InsertData(p);
	}
	while (t.size != 0)
	{
		cout << t.pop() << " ";
	}
	return 0;
}
```

