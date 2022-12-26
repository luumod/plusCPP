#include <bits/stdc++.h>
using namespace std;

using Type = int;

struct TreeNode
{
	Type data;
	TreeNode* left;
	TreeNode* right;
	int height = 0;
	TreeNode(const Type& data, TreeNode* left = nullptr, TreeNode* right = nullptr, const int& height = 0)
		:data(data), left(left), right(right),height(height) {}
};

class AVLTree
{
public:
	AVLTree();
	~AVLTree();
	//计算AVL树的节点高度
	static int Height(TreeNode* node);
	void insert(const Type& data);
private:
	void SingleRotateWithLeft(TreeNode*& root);
	void SingleRotateWithRight(TreeNode*& root);
	void DoubleRotateWithLeft(TreeNode*& root);
	void DoubleRotateWithRight(TreeNode*& root);
	void _insert(const Type& data, TreeNode*& root);
private:
	TreeNode* root;
};

int main()
{
	AVLTree t1, t2, t3, t4;

	//右右型
	t1.insert(1);
	t1.insert(2);
	t1.insert(3);

	//左左型
	t2.insert(3);
	t2.insert(2);
	t2.insert(1);

	//左右型
	t3.insert(3);
	t3.insert(1);
	t3.insert(2);

	//右左型
	t4.insert(1);
	t4.insert(3);
	t4.insert(2);

	AVLTree t;
	vector<int> vec{ 4,2,6,1,3,5,7,16,15,14,13,12,11,10,8,9 };
	for (int i = 0; i < vec.size(); i++)
	{
		t.insert(vec[i]);
	}
	return 0;
}

AVLTree::AVLTree()
{
	root = nullptr;
}

AVLTree::~AVLTree()
{
	//销毁整棵树
}

int AVLTree::Height(TreeNode* node)
{
	if (node == nullptr)
	{
		return -1;
	}
	else
	{
		return node->height;
	}
}

void AVLTree::insert(const Type& data)
{
	_insert(data, root);
}

void AVLTree::SingleRotateWithLeft(TreeNode*& root)
{
	//左左型
	TreeNode* K2 = root;

	TreeNode* K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	//K1经过旋转后成为了新的根节点，K2是其右孩子

	K2->height = max(Height(K2->left), Height(K2->right)) + 1;
	K1->height = max(Height(K1->left), K2->height) + 1;

	root = K1;
}

void AVLTree::SingleRotateWithRight(TreeNode*& root)
{
	//右右型
	TreeNode* K1 = root;

	TreeNode* K2 = K1->right;
	K1->right = K2->left;
	K2->left = K1;
	//K1经过旋转后成为了新的根节点，K2是其左孩子

	K1->height = max(Height(K1->left), Height(K1->right)) + 1;
	K2->height = max(K1->height, Height(K2->right)) + 1;

	root = K2;
}

void AVLTree::DoubleRotateWithLeft(TreeNode*& root)
{
	//左右型
	TreeNode* K3 = root;
	//1. 先右旋
	SingleRotateWithRight(K3->left);
	//2. 后左旋
	SingleRotateWithLeft(K3);

	root = K3;
}

void AVLTree::DoubleRotateWithRight(TreeNode*& root)
{
	//右左型
	TreeNode* K3 = root;
	//1. 先左旋
	SingleRotateWithLeft(K3->right);
	//2. 再右旋
	SingleRotateWithRight(K3);

	root = K3;
}

void AVLTree::_insert(const Type& data, TreeNode*& root)
{
	if (root == nullptr)
	{
		root = new TreeNode{ data };
		return;
	}
	if (data < root->data)
	{
		//左子树插入
		_insert(data, root->left);
		if (Height(root->left) - Height(root->right) == 2)
		{
			if (data < root->left->data)
			{
				SingleRotateWithLeft(root);	//单旋转：左左型
			}
			else
			{
				DoubleRotateWithLeft(root);	//双旋转：左右型
			}
		}
	}
	else if (data > root->data)
	{
		//右子树插入
		_insert(data, root->right);
		if (Height(root->right) - Height(root->left) == 2)
		{
			if (data > root->right->data)
			{
				SingleRotateWithRight(root);	//单旋转：右右型
			}
			else
			{
				DoubleRotateWithRight(root);	//双旋转：右左型
			}
		}
	}
	//否则树已经在节点中了，我们什么也不做

	//update树节点的高度
	root->height = max(Height(root->left), Height(root->right)) + 1;
}
