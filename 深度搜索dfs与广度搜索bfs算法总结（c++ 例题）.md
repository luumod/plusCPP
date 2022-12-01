@[toc]

深度优先搜索的本质：**递归**
广度优先搜索的本质：利用**队列**先进先出的特性
# 图像渲染
传送门：

[图像渲染](https://leetcode.cn/problems/flood-fill/description/)
## dfs
dfs求解：递归到达每一个格子，判断这个格子的颜色是不是我们需要更改的颜色curcolor，如果是，则把他更改为目标颜色color，并且借助它再次递归，遍历它周围的四个方向的格子，重复进行判断与更新。

直到所有的格子都遍历之后，需要更改的格子都已经递归到了并且更改了，不需要更改颜色的颜色则根本不会递归到这个格子。
```cpp
class Solution {
private:
    const int dirX[4]{0,0,-1,1};
    const int dirY[4]{-1,1,0,0};
public:
    void dfs(vector<vector<int>>& image,int sr,int sc,int curcolor,int color)
    {
        //判断是否是需要更改的颜色
        if (image[sr][sc]==curcolor)
        {
            //首先更改此颜色
            image[sr][sc]=color;
            //接着递归遍历其周围的四个方向，递归下去
            for (int i=0;i<4;i++)
            {
                int mx=sr+dirX[i];
                int my=sc+dirY[i];
                if (mx>=0 && mx<image.size() && my>=0 && my<image[0].size())
                {
                    dfs(image,mx,my,curcolor,color);
                }
            }
        }   
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int curcolor=image[sr][sc];
        if (curcolor==color)
        {
            return image;
        }
        dfs(image,sr,sc,curcolor,color);
        return image;
    }
};
```

## bfs 
bfs求解：当我们遍历到某一个格子的时候，把这个格子存储进队列中，当队列不为空的时候，我们重复取得队列 的第一个元素，然后pop一次。**再对这个元素进行四个方向的判断**，并且把需要更改的格子入队，等待下次取得该元素。别忘了队列的特性：先进先出，所以我们下一次取得的元素是之前的，接着再重复进行循环，直到队列为空。

```cpp
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        const int dirX[4]{0,0,-1,1};
        const int dirY[4]{-1,1,0,0};
        int curcolor=image[sr][sc];
        if (curcolor==color)
        {
            return image;
        }
        queue<pair<int,int>> q;
        q.push(make_pair(sr,sc));
        image[sr][sc]=color;
        while (!q.empty())
        {
            pair<int,int> num=q.front();  //获取队列顶部元素
            q.pop();    //弹出队列顶部元素
            for (int i=0;i<4;i++)
            {
                int mx=num.first+dirX[i];
                int my=num.second+dirY[i];
                if (mx>=0 && mx<image.size() && my>=0 && my<image[0].size() &&
                    image[mx][my]==curcolor)
                {
                    q.push(make_pair(mx,my));
                    image[mx][my]=color;
                }
            }
        }
        return image;
    }
};
```

----

# 岛屿的最大面积
## dfs
思路
* 得到每个网格中**每个连通形状然后取最大值**。

* 在 **每一块土地的周围四个方向**探索与之相连的每一个土地那么探索过的土地总数将是该连通形状的面积。

* 确保每个土地访问不超过一次，我们每次经过一块土地时，将这块土地的值置为 0。这样我们就不会多次访问同一土地。


```cpp
class Solution {
private:
    const int dirX[4]{0,0,-1,1};
    const int dirY[4]{-1,1,0,0};
public:
    void dfs(vector<vector<int>>& nums,int sr,int sc,int& len)
    {
    	//当前统计的面积递增
        len++;
        nums[sr][sc]=0; //标识为已经走过
        //接着遍历某一块土地的周围四个方向，递归到达每一个地方
        for (int i=0;i<4;i++)
        {
            int mx=sr+dirX[i];
            int my=sc+dirY[i];
            //到达的地方必须是有效的，而且必须是一块土地 (1)
            if (mx>=0 && mx<nums.size() && my>=0 && my<nums[0].size() &&
                 nums[mx][my]==1)
            {
           		//递归到达每一个地方
                dfs(nums,mx,my,len);
            }
        }
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res=0;
        for (int i=0;i<grid.size();i++)
        {
            for (int j=0;j<grid[0].size();j++)
            {
                if (grid[i][j]==1)
                {
                	//遇到了土地，则进入递归。
                    int len=0;
                    bfs(grid,i,j,len);
                    res=max(res,len);
                }
            }
        }
        return res;
    }
};
```

## bfs 
思路
* 把每一块土地放入队列中，利用队列先进先出的特性，得到每一个队列头部
* 只要队列不为空，就表示还有没有遍历到的土地，继续入队，出队
* 直到队列为空，表示所有的连通区域都已经遍历到。

```cpp
class Solution {
private:
    const int dirX[4]{0,0,-1,1};
    const int dirY[4]{-1,1,0,0};
public:
    void bfs(vector<vector<int>>& nums,int sr,int sc,int& len)
    {
        queue<pair<int,int>> q;
        q.emplace(sr,sc);
        nums[sr][sc]=0;
        while (!q.empty())
        {
            len++;
            //队列中取出每一个土地
            pair<int,int> p=q.front();
            q.pop();
            //遍历周围的四个方向，如果是土地则放入队列中，此后再继续得到队列中的每一个元素，再重新循环
            for (int i=0;i<4;i++)
            {
                int mx=p.first+dirX[i];
                int my=p.second+dirY[i];
                if (mx>=0 && mx<nums.size() && my>=0 && my<nums[0].size() &&
                    nums[mx][my]==1)
                {
                    q.emplace(mx,my);
                    nums[mx][my]=0;
                }
            }
        }
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res=0;
        for (int i=0;i<grid.size();i++)
        {
            for (int j=0;j<grid[0].size();j++)
            {
                if (grid[i][j]==1)
                {
                    int len=0;
                    bfs(grid,i,j,len);
                    res=max(res,len);
                }
            }
        }
        return res;
    }
};
```

# 合并二叉树结点
传送门
[https://leetcode.cn/problems/merge-two-binary-trees/description/](https://leetcode.cn/problems/merge-two-binary-trees/description/)
## dfs
思路：

* 利用递归**依次遍历到两颗树的每一个节点**
* 判断这两棵树的节点**都是空**，还是**都不为空**，还是**有一个为空**
* 把不为空的节点合并成一个新节点，或者获得单独一个节点

```cpp
class Solution {
public:
    TreeNode* dfs(TreeNode* p1,TreeNode* p2)
    {
        if (p1==nullptr)
        {   
            return p2;
        }
        if (p2==nullptr)
        {
            return p1;
        }
        TreeNode* pNew=new TreeNode{p1->val+p2->val};
        pNew->left=dfs(p1->left,p2->left);
        pNew->right=dfs(p1->right,p2->right);
        return pNew;
    }    
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        return bfs(root1,root2);
    }
};
```
---

## bfs
思路：

* 三个队列分别维护两个原始树和一个生成后的结果树
* 遍历到每一个子树的左右节点，根据他们的非空情况，依次放入队列中。
* 结果树队列出队得到每一棵子树，再对每一个子树填充节点

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:   
    TreeNode* bfs(TreeNode* p1,TreeNode* p2)
    {
        if (p1==nullptr)
        {
            return p2;
        }
        if (p2==nullptr)
        {
            return p1;
        }
        TreeNode* pNew=new TreeNode{p1->val+p2->val};
        //三个队列维护
        queue<TreeNode*> q1;
        queue<TreeNode*> q2;
        queue<TreeNode*> res;
        q1.emplace(p1);
        q2.emplace(p2);
        res.emplace(pNew);
        while (!res.empty())
        {
            TreeNode* node1=q1.front();
            TreeNode* node2=q2.front();
            TreeNode* pRes=res.front();
            q1.pop();
            q2.pop();
            res.pop();
            //两棵左子树存在不为空
            if (node1->left!=nullptr || node2->left!=nullptr)
            {
            	//两个左边都不为空，进行合并填充，保存下一个节点
                if (node1->left!=nullptr && node2->left!=nullptr)
                {
                    TreeNode* pnode=new TreeNode{node1->left->val+node2->left->val};
                    pRes->left=pnode;
                    q1.emplace(node1->left);
                    q2.emplace(node2->left);
                    res.emplace(pnode);
                }
                //两棵树存在某一边为空，则连接不为空一边的节点
                else if (node1->left==nullptr)
                {
                    pRes->left=node2->left;
                }
                else if (node2->left==nullptr)
                {
                    pRes->left=node1->left;
                }
            }
            //进行右侧的遍历
            if (node1->right!=nullptr || node2->right!=nullptr)
            {
                if (node1->right!=nullptr && node2->right!=nullptr)
                {
                    TreeNode* pnode=new TreeNode{node1->right->val+node2->right->val};                   pRes->right=pnode;
                    q1.emplace(node1->right);
                    q2.emplace(node2->right);
                    res.emplace(pnode);
                }
                else if (node1->right==nullptr)
                {
                    pRes->right=node2->right;
                }
                else if (node2->right==nullptr)
                {
                    pRes->right=node1->right;
                }
            }   
        }
        return pNew;
    }
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        return bfs(root1,root2);
    }
};
```
