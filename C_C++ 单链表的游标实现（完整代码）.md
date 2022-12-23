# 单链表的游标实现（数组）

不使用任何指针类型，利用游标实现单链表的基本操作
```cpp
#include <iostream>
using namespace std;

using PtrToNode = int;
using List = PtrToNode;
using Position = PtrToNode;

constexpr int SpaceSize = 10;

struct Node
{
	PtrToNode data;
	Position next;
};

//使用全局的数组
Node CursorSpace[SpaceSize];

//初始化链表
void InitializeCursorSpace();
//为游标链表分配内存
static Position CursorAlloc();
//释放内存
static void CursorFree(const Position& p);
//插入数据
void insert(const PtrToNode& data, Position P);
//测试一个链表是否为空
bool empty(List L);
//P是否是链表的末尾
bool Last(Position P);
//返回表L中data的位置
Position Find(PtrToNode data, List L);
//返回表中data的前一个位置
Position FindPrevNode(PtrToNode data, List L);
//删除链表节点
void DeleteNode(PtrToNode data, List L);
//删除链表
void DeleteList(List L);
//遍历链表
void Travel(List L);

int main()
{
	InitializeCursorSpace();
	Position L = CursorAlloc();
	insert(1, L);
	insert(3, L);
	insert(5, L);
	Position L1 = CursorAlloc();
	insert(2, L1);
	insert(4, L1);
	insert(6, L1);
	cout << empty(L1) << endl;

	Position pL = Find(5, L);
	Position pPrevL = FindPrevNode(5, L);
	//DeleteNode(4,L1);
	Travel(L);
	DeleteList(L1);
	return 0;
}

void InitializeCursorSpace()
{
	for (int i = 0; i < SpaceSize; i++)
	{
		CursorSpace[i].data = 0;
		CursorSpace[i].next = (i + 1) % SpaceSize;
	}
}

static Position CursorAlloc()
{
	Position p;
	p = CursorSpace[0].next;
	CursorSpace[0].next = CursorSpace[p].next;	
	CursorSpace[p].next = 0;
	return p;
}

void insert(const PtrToNode& data, Position P)
{
	Position tempCell;

	tempCell = CursorAlloc();
	if (tempCell == 0)
	{
		cout << "Out of Space!\n";
	}

	CursorSpace[tempCell].data = data;
	CursorSpace[tempCell].next = CursorSpace[P].next;
	CursorSpace[P].next = tempCell;
}

bool empty(List L)
{
	return CursorSpace[L].next == 0;
}

bool Last(Position P)
{
	return CursorSpace[P].next == 0;
}

Position Find(PtrToNode data, List L)
{
	Position p;

	p = CursorSpace[L].next;
	while (p && CursorSpace[p].data != data)
	{
		p = CursorSpace[p].next;
	}
	return p;
}

Position FindPrevNode(PtrToNode data, List L)
{
	Position p = L;
	Position tempCell = CursorSpace[p].next;
	while (CursorSpace[tempCell].data!=data && tempCell)
	{
		tempCell = CursorSpace[tempCell].next;
		p = CursorSpace[p].next;
	}
	return p;
}

void DeleteNode(PtrToNode data, List L)
{
	Position p, tempCell;

	p = FindPrevNode(data, L);

	if (!Last(p))
	{
		tempCell = CursorSpace[p].next;
		CursorSpace[p].next = CursorSpace[tempCell].next;
		//CursorFree(tempCell);
	}
}

void DeleteList(List L)
{
	Position p = CursorSpace[L].next;
	Position tempCell = p;
	while (tempCell)
	{
		p = CursorSpace[p].next;
		CursorFree(tempCell);
		if (p == 0)
		{
			break;
		}
		tempCell = p;
	}
	CursorSpace[L].next = 0;
}

void Travel(List L)
{
	Position p = CursorSpace[L].next;
	while (p)
	{
		cout << CursorSpace[p].data << " ";
		p = CursorSpace[p].next;
	}
}

static void CursorFree(const Position& p)
{
	CursorSpace[p].next = CursorSpace[0].next;
	CursorSpace[p].data = 0;
	CursorSpace[0].next = p;
}

```

