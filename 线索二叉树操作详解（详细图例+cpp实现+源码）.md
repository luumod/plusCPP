@[toc]

# 线索二叉树

线索二叉树又称为二叉树的线索化。

**在一个具有n个节点的二叉树中，它含有n+1个空指针链域，如果我们把这些空指针链域利用起来，用它来记录当前节点的前驱节点与后继节点，这些指针被称为线索。 加上线索的二叉树成为==线索二叉树==。**

线索二叉树：

* 先序线索二叉树
* 中序线索二叉树
* 后序线索二叉树

==我们在本节主要讨论中序线索二叉树。==

----

线索二叉树的优势：

1. 利用线索二叉树进行中序遍历时，不必采用**堆栈处理**，速度**较一般二叉树的遍历速度快，且节约存储空间**。
2. **任意一个结点都能直接找到它的前驱和后继结点**。

-----

## 中序线索二叉树

解析： 中序线索二叉树

这颗二叉树的中序遍历结果： ==1 1 2 4 5 9==  注意：我们使用了一个头节点（值为0）作为**特殊的线索**，在二叉树中本身并不包含这个头节点。


**黑色指针链**： 代表节点之间的正常的左右孩子关系。
**红色指针链**： 代表线索，即指针此节点的前驱与后继节点

==注意：我们所讨论的**前驱与后继**都是根据这个二叉树的中序遍历的序列的位置关系。== 

1. 根节点的左子树 1： 它是一个叶子节点，所以具有线索，**左线索指向前驱节点**，但是注意由于**其前驱为空**，所以规定他指向**头节点**；**右线索指向其后继**，在中序遍历中指向根节点1。
2. 节点2：它的左为子树为空，所以它应该**具有左线索，指向其前驱，应该为根节点1.**
3. 节点4：同第一步的节点1一致，**具有左线索与右线索，分别指向前驱与后继节点，即节点2和节点5.**
4. 节点9：它是中序遍历的末尾节点，也是叶子节点，**左线索指向前驱，即它的中序遍历前一个节点5；右线索指向后继，它没有后继，因此指向头节点。**
5. ==注意：头节点也应该具有线索，左线索指向根节点，右线索指向这颗树的中序遍历的最后一个节点，即最右节点。==

![在这里插入图片描述](https://img-blog.csdnimg.cn/b0a38405bef7405cbcbcbd808acb9cf5.png)


-----

# 构造线索二叉树
我们经过上面的图分析后，可以得知：线索二叉树其实就是普通的二叉树，然后又加了指向其前驱与后继的线索。
那么如何表示左右指针链与线索呢？

存储结构：
```cpp
template <typename T>
struct TreeNode
{
	T data;		//节点的值
	TreeNode* pleft, * pright;	//左右指针
	int ltag, rtag;		//表示有没有左右线索
};
```
* ltag：是否具有左线索

	* 值为0： 直接用作**普通的指针链即可**，pelft指向其左孩子节点
	* 值为1： 它具有线索：==此时pleft指向其当前节点的前驱节点。==
* rtag：是否具有右线索

	* 值为0： 直接用作**普通的指针链即可**，pright指向其右孩子节点
	* 值为1： 它具有线索：==此时pright指向其当前节点的后继节点。==



## 节点的线索化
当我们明确了二叉树节点的存储结构之后，我们便可以按照我们的思路来完成==线索化==了。

主要思路：
==中序遍历一颗树，在中序遍历的过程中，检查当前节点的左右指针是否为空，为空则指向当前节点的前驱节点与后继节点。==

请注意：既然需要前驱节点与后继节点，那么我们**显然需要一个 pre节点**，即**指向当前节点的前驱节点的指针**，用它来连接。

过程：
1. 首先创建一个头节点pHead，用它来确保中序遍历的序列的首元节点和尾节点能够被线索化。
2. 首先遍历**左子树**。
3. 如果当前遍历的节点 p->pleft 不为空，则 p->ltag 置为0； p->pright 不为空，则 p->rtag 置为0，表示左右指针==不需要线索化==。
4.  如果当前遍历的节点 **p->pleft 为空，则 p->ltag 置为1，p->pleft指向其前驱节点 pre** ； **p->pright 为空，则 pre ->rtag 置为1，pre->pright指向其后继节点 p**，表示左右指针==需要线索化==。（注意这个右线索化时，我们当前节点是p，前驱节点是pre，我们既然要让 p 连接后继节点，不如反过来让pre连接p。）
5. 然后遍历**右子树**，==递归==，执行相同的操作。

----

代码示例：

```cpp
template<typename T>
TreeNode<T>* Tree<T>::_createThread_Tree(TreeNode<T>* bt)
{
	//增加一个头节点
	TreeNode<T>* pHead = new TreeNode<T>{ 0,nullptr,bt,0,1 };
	//1. 判断这颗树是否是空的。
	if (bt == nullptr)
	{
		pHead->ltag = 0;
		pHead->pleft = pHead;
		pHead->rtag = 1;
		pHead->pright = nullptr;
	}
	else
	{
		//2. bt不为空树，则开始线索化。
		pHead->pleft = bt;	//（1）首先头节点的左指针线索化树根节点
		pre = pHead;		//（2）前驱节点首先设置为头节点
		_Thread(bt);		//（3）开始树中各个节点的线索连接
		//结束后，pre指向根节点  进行头节点根节点的连接
		pHead->pright = pre;	
		pre->rtag = 1;				
		pre->pright = pHead;
	}
	//返回头节点
	return pHead;
}
template<typename T>
void Tree<T>::_Thread(TreeNode<T>*& bt)
{	
	if (bt != nullptr)
	{
		//递归进入右子树，开始线索化
		_Thread(bt->pleft);	
		//直到其左指针为空，则需要将左指针线索化。
		//左指针指向其前驱节点，ltag标记为1
		if (bt->pleft == nullptr)
		{
			bt->pleft = pre;
			bt->ltag = 1;
		}
		else
		{
			//左指针不为空，则不需要线索化，ltag设置为0
			bt->ltag = 0;
		}
		//如果节点右指针为空，则需要将右指针线索化。
		//右指针指向其后继节点，rtag标记为1
		//注意： 当前节点与后继节点的连接可以转换为 ---> 前驱节点与当前节点(当作后继节点)的连接
		if (pre->pright == nullptr)
		{
			pre->pright = bt;
			pre->rtag = 1;
		}
		else
		{
			pre->rtag = 0;
		}
		//每次完成一个节点的操作后，前驱节点记得要更新为当前节点，然后当前节点接着往下遍历
		pre = bt;
		_Thread(bt->pright);	//递归进入右子树，开始线索化
	}
}
```
如果你对 _Thread线索化函数感到难以理解，我们来一步步图解这个过程：


1. 首先p一路递归到其**左指针等于空**的时候，开始线索化：左指针指向其前驱节点，此时**pre默认为头节点**（我们自定义的），==左指针指向头节点，ltag标记为1==；pre的右指针为空，==pre的右指针指向当前节点==，rtag标记为1，接着递归进入节点4的右子树。
![在这里插入图片描述](https://img-blog.csdnimg.cn/7f2d69ac36e741af866a023a4035a66e.png)


2. 节点4右指针为空，因此递归返回一层，返回到节点3。pre指向其前驱节点4。可以发现**节点3的左指针不为空，因此ltag标记为0，无需对左指针进行线索化。pre的右指针为空，进行pre右指针的线索化**，连接其后继节点。==pre的pright连接当前节点p==，标记ltag为1，**此时就完成了节点4的线索化**。
![在这里插入图片描述](https://img-blog.csdnimg.cn/a7543bab9e254022a14f18e7c535d76a.png)
3. 接着递归进入节点3的右子树中，**到达节点5，它的左指针为空，因此进行左线索化**，连接其**前驱节点pre**，标记节点5的ltag为1。此时 **节点3的线索化就完成了！** 然后递归进入节点5的右子树。
![在这里插入图片描述](https://img-blog.csdnimg.cn/15f367fa6719468d80598fc2704c2ba1.png)
4. **节点5的右指针为空，因此返回递归**，到达了节点2，pre指向节点5。节点2的左指针不为空，因此ltag标记0。==pre的右指针为空，pre的右指针指向p，rtag标记为1==，接着递归进入节点2的右子树，为空，则返回上一层。**对于节点5的线索化也完成了！**
![在这里插入图片描述](https://img-blog.csdnimg.cn/8c6a5caf8a134525bf5cfdfed85cce01.png)
5. p到达节点1，pre到达节点2，p的左指针不为空，无需线索化，ltag标记为0。==pre的右指针为空，需要线索化，pre的右指针指向p，rtag标记为1==，**节点2的线索化就完成了！**

![在这里插入图片描述](https://img-blog.csdnimg.cn/2d358b944caa40cc807f9f92c2eecaae.png)
6. 接下来进入节点1的右子树的递归，为空，所以返回上一层，**递归结束**，返回到函数中。==头节点的右指针连接到pre上，rtag标记为1，根节点的右指针也连接到头节点上，rtag标记为1==，**此时整棵树的线索化就完成了！**

![在这里插入图片描述](https://img-blog.csdnimg.cn/0698291f044542cf8630498f1de62f57.png)

---------

如何来检测结果的正确性？
中序遍历序列：

4   ----    3    -----   5  -----  2 ------ 1 
4的前驱为头节点，后继为节点3。（线索化）
3的前驱为节点4，后继是节点5。（无需线索化）
5的前驱是节点3，后继是节点2。（线索化）
2的前驱是节点5，后继是节点1。（右线索化）
1的前驱是节点2，后继是根节点。（右线索化）
==根节点始终与中序遍历的最后一个节点的右指针互相连接。==



-----

# 其他操作
## 销毁二叉搜索树

如果 ltag和rtag都等于0，表示节点具有左右子树；如果都不等于1，则相当于上面的叶子节点4一样，递归到了树底层，则删除此节点。

```cpp
template<typename T>
void Tree<T>::_destroyTH(TreeNode<T>*& bt)
{
	//左子树不为空，递归到最后一个左子树叶子节点
	if (bt->ltag == 0)
	{
		_destroyTH(bt->pleft);
	}
	//右子树不为空，递归到最后一个右子树叶子节点
	if (bt->rtag == 0)
	{
		_destroyTH(bt->pright);
	}
	delete bt;
	bt = nullptr;
}
```

## 获取中序遍历的第一个节点

当最后一个节点的ltag为1时，则表示到达了最后。
```cpp
template<typename T>
TreeNode<T>* Tree<T>::FindMidFirst()
{
	TreeNode<T>* begnode = root->pleft;
	while (begnode->ltag == 0)
	{
		begnode = begnode->pleft;
	}
	return begnode;
}
```
## 获取中序遍历的最后一个节点
头节点与中序遍历的最后一个节点相互连接，因此它的右指针就是中序遍历的最后一个节点。

```cpp
template<typename T>
TreeNode<T>* Tree<T>::FindMidLast()
{
	return root->pright;
}
```

## 输出中序遍历序列

```cpp
template<typename T>
TreeNode<T>* Tree<T>::PreNode(TreeNode<T>* p)
{
	auto find = p->pleft;
	if (p->ltag != 1)
	{
		while (find->rtag == 0)
		{
			find = find->pright;
		}
	}
	return find;
}
```
```cpp
template<typename T>
void Tree<T>::_midtavel()
{
	TreeNode<T>* node;
	node = FindMidFirst();
	while (node != root)
	{
		cout << node->data << " ";
		node = NextNode(node);
	}
	cout << endl;
}
```
## 逆序输出中序遍历序列

```cpp
template<typename T>
TreeNode<T>* Tree<T>::NextNode(TreeNode<T>* p)
{
	auto find = p->pright;
	if (p->rtag != 1)
	{
		while (find->ltag == 0)
		{
			find = find->pleft;
		}
	}
	return find;
}
```

```cpp
template<typename T>
void Tree<T>::_rmidtravel()
{
	auto node = FindMidLast();
	while (node != root)
	{
		cout << node->data << " ";
		node = PreNode(node);
	}
	cout << endl;
}

```

## 源码

```cpp
#include <iostream>
#include <algorithm>
#include <vld.h>
#include <vector>
#include <stack>
#include <list>
using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode* pleft, * pright;
	int ltag, rtag;
	TreeNode(const T& data = 0) 
		:data(data), pleft(nullptr), pright(nullptr),rtag(0),ltag(0) {}
	TreeNode(const T& data, TreeNode* pleft, TreeNode* pright, int ltag, int rtag)
		:data(data), pleft(pleft), pright(pright), ltag(ltag), rtag(rtag) {}
};

template <typename T = int>
class Tree
{
public:
	Tree();
	~Tree();
	void CreateTree(const T& val);
	//中序遍历序列
	void MidTravel();
	//逆中序遍历序列
	void rMidTravel();
	void CreateThreadTree();
	void destroyThreadTree();
	void destroyTree();

	//查找中序遍历的第一个节点
	TreeNode<T>* FindMidFirst();
	//得到中序遍历的最后一个节点
	TreeNode<T>* FindMidLast();
private:
	//找P节点的中序前驱节点
	TreeNode<T>* PreNode(TreeNode<T>* p);
	//找P节点的中序后继节点
	TreeNode<T>* NextNode(TreeNode<T>* p);
	void _destroyTree(TreeNode<T>*& bt);
	void _midtavel();
	void _rmidtravel();
	void _createTree(TreeNode<T>*& root,const T& val);
	TreeNode<T>* _createThread_Tree(TreeNode<T>* bt);
	void _Thread(TreeNode<T>*& bt);
	void _destroyTH(TreeNode<T>*& bt);
private:
	TreeNode<T>* root;
	TreeNode<T>* pre;
};

int main()
{
	Tree<> a;
	int arr[]{ 1,2,5,4,1,9 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		a.CreateTree(arr[i]);
	}
	a.CreateThreadTree();
	auto beg =  a.FindMidFirst();
	auto end = a.FindMidLast();
	a.MidTravel();
	a.rMidTravel();
	return 0;
}

template<typename T>
Tree<T>::Tree()
{
	root = nullptr;
	pre = nullptr;
}

template<typename T>
Tree<T>::~Tree()
{
	if (pre == nullptr)
	{
		destroyTree();
	}
	else
	{
		destroyThreadTree();
	}
}

template<typename T>
void Tree<T>::CreateTree(const T&val)
{
	_createTree(root, val);
}

template<typename T>
void Tree<T>::MidTravel() 
{
	_midtavel();
}

template<typename T>
void Tree<T>::rMidTravel()
{
	_rmidtravel();
}

template<typename T>
void Tree<T>::CreateThreadTree()
{
	root = _createThread_Tree(root);
}

template<typename T>
void Tree<T>::destroyThreadTree()
{
	auto pNode = root->pleft;		//保存下一个节点的位置
	delete root;	//删除头节点的内存
	root = nullptr;
	_destroyTH(pNode);
	pre = nullptr;
}

template<typename T>
void Tree<T>::destroyTree()
{
	_destroyTree(root);
	root = nullptr;
}

template<typename T>
TreeNode<T>* Tree<T>::FindMidFirst()
{
	TreeNode<T>* begnode = root->pleft;
	while (begnode->ltag == 0)
	{
		begnode = begnode->pleft;
	}
	return begnode;
}

template<typename T>
TreeNode<T>* Tree<T>::FindMidLast()
{
	return root->pright;
}

template<typename T>
TreeNode<T>* Tree<T>::PreNode(TreeNode<T>* p)
{
	auto find = p->pleft;
	if (p->ltag != 1)
	{
		while (find->rtag == 0)
		{
			find = find->pright;
		}
	}
	return find;
}

template<typename T>
TreeNode<T>* Tree<T>::NextNode(TreeNode<T>* p)
{
	auto find = p->pright;
	if (p->rtag != 1)
	{
		while (find->ltag == 0)
		{
			find = find->pleft;
		}
	}
	return find;
}

template<typename T>
void Tree<T>::_destroyTree(TreeNode<T>*& bt)
{
	if (bt != nullptr)
	{
		_destroyTree(bt->pleft);
		_destroyTree(bt->pright);
		delete bt;
	}
}

template<typename T>
void Tree<T>::_midtavel()
{
	TreeNode<T>* node;
	node = FindMidFirst();
	while (node != root)
	{
		cout << node->data << " ";
		node = NextNode(node);
	}
	cout << endl;
}

template<typename T>
void Tree<T>::_rmidtravel()
{
	auto node = FindMidLast();
	while (node != root)
	{
		cout << node->data << " ";
		node = PreNode(node);
	}
	cout << endl;
}

template<typename T>
void Tree<T>::_createTree(TreeNode<T>*& root, const T& val)
{
	if (root == nullptr)
	{
		root = new TreeNode<T>{ val };
		return;
	}
	if (val <= root->data)
	{
		_createTree(root->pleft, val);
	}
	else
	{
		_createTree(root->pright, val);
	}
}

template<typename T>
TreeNode<T>* Tree<T>::_createThread_Tree(TreeNode<T>* bt)
{
	//增加一个头节点
	TreeNode<T>* pHead = new TreeNode<T>{ 0,nullptr,bt,0,1 };
	if (bt == nullptr)
	{
		pHead->ltag = 0;
		pHead->pleft = pHead;
		pHead->rtag = 1;
		pHead->pright = nullptr;
	}
	else
	{
		//bt不为空树
		pHead->pleft = bt;
		pre = pHead;			//前驱节点默认为头节点
		_Thread(bt);	//线索连接
		//结束后，pre指向根节点  进行头节点根节点的连接
		pHead->pright = pre;	
		pre->pright = pHead;
		pre->rtag = 1;				
	}
	//返回头节点
	return pHead;
}

template<typename T>
void Tree<T>::_Thread(TreeNode<T>*& bt)
{	
	if (bt != nullptr)
	{
		_Thread(bt->pleft);	//递归进入右子树，开始线索化
		//线索化
		if (bt->pleft == nullptr)
		{
			bt->pleft = pre;
			bt->ltag = 1;
		}
		else
		{
			bt->ltag = 0;
		}
		if (pre->pright == nullptr)
		{
			pre->pright = bt;
			pre->rtag = 1;
		}
		else
		{
			pre->rtag = 0;
		}
		//node.emplace_back(bt);
		pre = bt;
		_Thread(bt->pright);	//递归进入右子树，开始线索化
	}
}

template<typename T>
void Tree<T>::_destroyTH(TreeNode<T>*& bt)
{
	//左子树不为空，递归到最后一个左子树叶子节点
	if (bt->ltag == 0)
	{
		_destroyTH(bt->pleft);
	}
	//右子树不为空，递归到最后一个右子树叶子节点
	if (bt->rtag == 0)
	{
		_destroyTH(bt->pright);
	}
	delete bt;
	bt = nullptr;
}


```

