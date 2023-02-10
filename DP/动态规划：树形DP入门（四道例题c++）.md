
@[toc]

# 树形背包




* **选择节点类**： dp[i] [0/1]表示 第i个节点 1选择，0不选所能得到的最大价值。

1. dp[i] [0]：i不选，则j节点可以选择，也可以不选，取一个最优的
2. dp[i] [1]：i选择，则j节点一定不能选。

$$
\begin{cases}
 dp[i][0]=max/min(dp[j][1],dp[j][0] \\	
 dp[i][1]=dp[j][0]
 \end{cases}
$$

* 树形背包

$$
dp[i][j]=max(dp[i][j],dp[son][k]+dp[i][j-k])
$$




# 生命之树

[题目传送门](https://www.luogu.com.cn/problem/P8625)

> 在 X 森林里，上帝创建了生命之树。
>
> 他给每棵树的每个节点（叶子也称为一个节点）上，都标了一个整数，代表这个点的和谐值。
>
> 上帝要在这棵树内选出一个节点集合 �*S*（允许为空集），使得对于 �*S* 中的任意两个点 �,�*a*,*b*，都存在一个点列 �,�1,�2,⋯ ,��,�*a*,*v*1,*v*2,⋯,*v**k*,*b* 使得这个点列中的每个点都是 �*S* 里面的元素，且序列中相邻两个点间有一条边相连。
>
> 在这个前提下，上帝要使得 �*S* 中的点所对应的整数的和尽量大。
>
> 这个最大的和就是上帝给生命之树的评分。
>
> 经过 atm 的努力，他已经知道了上帝给每棵树上每个节点上的整数。但是由于 atm 不擅长计算，他不知道怎样有效的求评分。他需要你为他写一个程序来计算一棵树的分数。

-----

给我们一颗树，并且每个节点都有一个权值，并且要使得S中的点的整数的和要尽可能大。



首先存图，把这个树结构存储起来，这是个无向双向连通图，可以使用vector容器，也可以使用链式前向星存图，在下面我们给出这两种形式的写法。

我们可以使用dfs来遍历这棵树，也可以使用dp来动态转移每个值，同样列出了这两种方法：



---

思路：

1. 对于每一个根节点，递归他的所有孩子节点，然后每一次递归解算出当前节点所具有的分数，然后到达叶子节点之后就回溯。
2. 回溯之后，我们会获得他的孩子节点的值，我们再赋值给根节点的值，这样来统计每一个最大值。



----

dp形式的状态转移方程： dp[i] 表示以i为根节点的所具有的最大值，则：
$$
dp[i]+=max(0,dp[son])
$$

---



第一种写法：dfs 形式

```cpp
//TODO: Write code here
int n,m;
const int N=1e5+10;
v<int> vec[N];
int nums[N];    	//每个节点的权值
int wsum[N];       //每个节点及其所在子树的权值之和
int ans=0;
void dfs(int root,int fa)   //树形DP的套路dfs
{   
    wsum[root]=nums[root];//每个节点的默认权值
    for (int i=0;i<vec[root].size();i++)
    {
        int son=vec[root][i]; //当前root的一个孩子
        if (son!=fa)    //孩子不为父亲
        {
            dfs(son,root);  //孩子成为新的root,root成为孩子的father
            //一直递归到叶子节点或者从子树返回到根节点
            if (wsum[son]>0) wsum[root]+=wsum[son];//当前root的权值加上它的孩子所具有的最大权值
        }
    }
    if (wsum[root]>ans) ans=wsum[root];
}
signed main()
{
	cin>>n;
    for (int i=1;i<=n;i++) cin>>nums[i];
    for (int i=1;i<=n-1;i++) 
    {
        int u,v;
        cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);    //两个点相互连接
    }
    dfs(1,0);   //根节点从1开始，父亲节点默认为0
    cout<<ans;
#define one 1
	return 0;
}
```



另一种写法：dp 形式



```cpp
//TODO: Write code here
int n,m;
const int N=1e5+10;
int nums[N],dp[N];
struct Edge
{
	int to,next;
}edge[N];
int head[N],cnt,w[N],ans,top[N];
void add_edge(int u,int v)
{
	edge[++cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
void dfs(int root,int fa)
{
	for (int i=head[root];i!=-1;i=edge[i].next)
	{
		int son=edge[i].to;
		if (son!=fa)
		{
			dfs(son,root);
			//if (w[sum]>0) w[root]+=w[sum]
			dp[root]+=max(0LL,dp[son]);
		}
	}
}
signed main()
{
	cin>>n;
	memset(head,-1,sizeof(head));
	for (int i=1;i<=n;i++)
	{
		cin>>dp[i];
	}
	for (int i=1;i<=n-1;i++)
	{
		int u,v;
		cin>>u>>v;
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);

	for (int i=1;i<=n;i++) ans=max(ans,dp[i]);
	cout<<ans;
#define one 1
	return 0;
}
```







# 没有上司的舞会

[题目传送门](https://www.luogu.com.cn/problem/P1352)



> 某大学有 �*n* 个职员，编号为 1…�1…*n*。
>
> 他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树，父结点就是子结点的直接上司。
>
> 现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数 ��*r**i*，但是呢，如果某个职员的直接上司来参加舞会了，那么这个职员就无论如何也不肯来参加舞会了。
>
> 所以，请你编程计算，邀请哪些职员可以使快乐指数最大，求最大的快乐指数。



-----



树形DP的入门题目。



我们首先根据从属关系建立图，以每一个上司所拥有的员工建立树形结构的图。

每一个上司的如果不能参加，则它的直接下属可以选择参加，也可以选择不参加，因为如果直接下属参加了，则以此为根节点的子树又是相同的情况，我们需要考类得到整个**树结构的最优解**，因此如果上司参加，**那么他的直接下属不一定参加**；反之，**如果上司参加，则他的直接下属一定不能参加**



我们便可以使用dp[i] [0/1] 来表示 i号节点1参加或者0不参加 能够组成的最大快乐值 

----

状态转移方程如下：
$$
dp[i][0]+=max(dp[j][0],dp[j][1])\\
dp[i][1]+=dp[j][0]
$$
i 表示当前的 根节点， j 节点表示i所代表的子树的孩子节点。



```cpp
//TODO: Write code here
int n, m;
const int N = 6e3 + 10;
int nums[N],dp[N][2], ans;
v<int> vec[N];
bool top[N];
void dfs(int x)
{
    dp[x][0]=0; //x不参加
    dp[x][1]=nums[x];//x参加
    for (int i=0;i<vec[x].size();i++)
    {
        int son=vec[x][i];
        dfs(son);
        dp[x][0]+=max(dp[son][0],dp[son][1]);
        dp[x][1]+=dp[son][0];
    }
    ans=max(dp[x][0],dp[x][1]);
}
signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> nums[i];
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        vec[v].push_back(u);
        top[u] = true;    //v是u的上司
    }
    for (int i=1;i<=n;i++)
    {
        if (!top[i]) {dfs(i); break;}
    }
    cout << ans;
#define one 1
    return 0;
}
```



另一种写法：

```cpp
//TODO: Write code here
int n,m;
const int N=1e4+10;
int nums[N],dp[N][2],ans;
v<int> vec[N];
bool top[N];
void dfs(int root)
{
    for (int i=0;i<vec[root].size();i++)
    {
        int son=vec[root][i];
        dfs(son);
        dp[root][0]=max(max(dp[root][0],dp[root][0]+dp[son][1]),max(dp[son][0],dp[son][1]));
        dp[root][1]=max(max(dp[root][1],dp[root][1]+dp[son][0]),dp[son][0]);//不选子节点，或者max(当前值，当前值+不选子节点的值)
    }
    ans=max(dp[root][0],dp[root][1]);
}
signed main()
{
	cin>>n;
    for (int i=1;i<=n;i++)
    {
        cin>>dp[i][1];
    }
    //建立不带权双向连通图
    for (int i=1;i<=n-1;i++)
    {
        int l,k;
        cin>>l>>k;
        vec[k].push_back(l);
        top[l]=true;    //已经有了父节点，则表示
    }
    for (int i=1;i<=n;i++)
    {
        if (!top[i])
        {
            dfs(i);
            break;
        } 
    }
    cout<<ans;
#define one 1
	return 0;
}
```

---



# 二叉苹果树

[题目传送门](https://www.luogu.com.cn/problem/P2015)



> 有一棵苹果树，如果树枝有分叉，一定是分二叉（就是说没有只有一个儿子的结点）
>
> 这棵树共有 �*N* 个结点（叶子点或者树枝分叉点），编号为 1∼�1∼*N*，树根编号一定是 11。
>
> 我们用一根树枝两端连接的结点的编号来描述一根树枝的位置。下面是一颗有 44 个树枝的树：
>
> ```
> 2   5
>  \ / 
>   3   4
>    \ /
>     1
> ```
>
> 现在这颗树枝条太多了，需要剪枝。但是一些树枝上长有苹果。
>
> 给定需要保留的树枝数量，求出最多能留住多少苹果。



-----



这是一道**树形01背包的好题目！**



我们规定**可以保留的树枝的数量当作背包**，则物品就是苹果树的每个节点，我们就可以**求得装满背包的物品的最大价值**，只不过这个01背包是在树上的！



----

我们规定dp[i] [j]：把编号为 i 的物品（节点）放进容量为 j 的背包（最大树枝数量），可以获得的最大价值（最多留住的苹果数量），通俗来讲，**dp[i] [j] 的含义是： 以 i 为根节点，保留 j 个树枝的苹果数量最大值。**

我们设置：

* ls[i] 为 i 的左孩子 节点
* rs[i] 为 i 的右孩子节点
* la[i] 为 连接左孩子的树枝所具有的苹果个数
* ra[i] 为 连接右孩子的树枝所具有的苹果个数



则可以归纳出以下的情形：

1. 把编号为 i 的物品放入背包，保留 m 个树枝，则 i 的孩子节点也可以放进背包， 因此假设ls[i] 存在，则把ls[i]看作一颗新的子树，他可以保留 k 个树枝，那么对于 i 的右孩子 rs[i] 来说，我们还可以保留 m - k个树枝，则我们可以获得 i 连接左右孩子节点的树枝的苹果数量的最大值，从而更新 以 i 的根节点dp的最大值。



则状态转移方程为 ： **j 表示我们所枚举的背包的容量，即此时可以保留 j 个背包 (0<=j<=m)**
$$
dp[i][j]=max(dp[i][j],dp[ls[i][k-1]+dp[rs[i]][j-k-1]+la[i]+ra[i])
$$
其中 i ，ls ，rs， la，ra的含义与上面的描述一致。



* **为什么 k和 j-k 需要减一呢？？** 
  * 因为我们此时他位于左子树上，而根节点到左子树默认也有一条树枝相连，所以我们应该让 k -1，同理 我们也应该让 j-k-1
* 两种特殊情况：
  * k==0，则 k - 1就成 -1了，这是不可能的，所以需要单独考虑右子树；**因为 k==0，所以意味着左子树保留0根树枝，右子树保留 j-1 根**
  * k==j，则 j -  k - 1就成 -1了，这是不可能的，所以需要单独考虑左子树；**因为 k==j，所以意味着左子树保留 j - 1  根树枝，右子树保留 0 根**



----



综上：最终的状态转移方程：
$$
dp[i][j]=max(dp[i][j],dp[ls[i][k-1]+dp[rs[i]][j-k-1]+la[i]+ra[i])
\\
dp[i][j]+=dp[ls[i]][j-1]+la[i] -> ( k==0 )
\\
dp[i][j]+=dp[rs[i]][j-1]+ra[i] -> (k==j)
$$




----

解题过程

* 我们首先需要根据**输入转换为图的存储形式**
* 通过build函数递归来初始化ls rs la ra数组
* 核心：树形DP的进行。



```cpp
//TODO: Write code here
int n,m;
const int N=1e4+10;
int nums[N],ls[N],rs[N],la[N],ra[N],dp[N][N];
struct Edge
{
    int to,w,next;//终点,边权,这个起点的上一条边
}edge[N];
int head[N],cnt;//head[i]表示以i为起点的最后一条边的编号
void init()
{
    for (int i=1;i<=n;i++)
    {
        head[i]=-1;
    }
    cnt=0;
}
void add_edge(int u,int v,int w)
{
    edge[cnt].to=v; //u->v
    edge[cnt].w=w;  //u->v的权值是w
    edge[cnt].next=head[u];//以u为起点的上一条边是head[u]
    head[u]=cnt++; //更新以u为起点的最后一条边的编号
}
void build(int root,int fa)
{
    int g=0;
    for (int i=head[root];i!=-1;i=edge[i].next)
    {
        int son=edge[i].to;
        if (son!=fa)
        {
            g++;
            if (g==1)
            {
                //左子树
                ls[root]=son;
                la[root]=edge[i].w;
            }
            else if (g==2)
            {
                rs[root]=son;
                ra[root]=edge[i].w;
            }
            build(son,root);
        }
    }
}
int dfs(int i,int j)   //dp[i][j]: 以i为根，保留j个树枝的最大值
{
    if (ls[i]==0 || rs[i]==0) return 0; //叶子节点往后没有树枝
    if (j==0) return 0; //一个树枝都不分配，没有苹果
    if (dp[i][j]) return dp[i][j];//记忆化
    for (int k=0;k<=j;k++)
    {
        /*
        dp[i][j]=max(dp[i][j],dp[ls[i]][k]+dp[rs[i]][j-k]+la[i]+ra[i])
        从根节点往最近的左右孩子走也是一条根,因此需要k-1
        */
       if (k==0) dp[i][j]=max(dp[i][j],dfs(rs[i],j-1)+ra[i]);//全给右孩子
       else if (k==j) dp[i][j]=max(dp[i][j],dfs(ls[i],j-1)+la[i]);//全给左孩子
       else dp[i][j]=max(dp[i][j],dfs(ls[i],k-1)+dfs(rs[i],j-k-1)+la[i]+ra[i]);//k个给左孩子，j-k个给右孩子
       //由于走到儿子结点都需要经过一条树枝，所以实际上分配数都要-1。 
    }
    return dp[i][j];
}

signed main()
{
	cin>>n>>m;
    init();
    for (int i=1;i<=n-1;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);
        add_edge(v,u,w);//双向带权图
    }
    build(1,0);

    cout<<dfs(1,m);
#define one 1
	return 0;
}
```



树形01背包的另一种做法，与 《选课》有一点像



```cpp
#include<bits/stdc++.h>
using namespace std;
int son[105][105],f[105][105];
int n,m,w[105][105],cnt[105],vis[105];

void dfs(int k)
{
	vis[k]=1;// 每次循环时，给父结点一个标记，防止无限循环 
	for(int i=1;i<=cnt[k];i++)
	{
		int ny=son[k][i];// 给 ny 赋上 k 结点的第 i 个 子结点 
		if(vis[ny]==1)continue;// 如果 ny 是 k 的 父结点，直接跳过循环 
		vis[ny]=1;
		dfs(ny);// 以  ny 为 父结点 进行搜索 
		for(int j=m;j>=1;j--) //逆序枚举当前可以选的树枝根数 
			for(int g=j-1;g>=0;g--) //逆序枚举留给 子结点 的树枝根数 
			{
				f[k][j]=max(f[k][j],f[ny][g]+f[k][j-g-1]+w[k][ny]);
				// f[ny][g] 表示以 ny 为 子结点 可以选 g 条边
				// f[k][j-g-1] 表示剩余给 k 结点的 兄弟结点 j-g-1 条边
				// w[k][ny] 表示 k 结点和 ny 结点之间的苹果数  
			}
	}
	return;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		w[x][y]=w[y][x]=z;//因为不知道 父结点 和 子结点分别是谁，所以同时存值 
		son[x][++cnt[x]]=y;// 每输入一次 当前结点，该节点的儿子数就 + 1 
		son[y][++cnt[y]]=x;
	}
	dfs(1);
	cout<<f[1][m]<<endl;//输出一 1 为根，选了 m 条边的树 
}
```



----



# 选课

[题目传送门](https://www.luogu.com.cn/problem/P2014)

> 在大学里每个学生，为了达到一定的学分，必须从很多课程里选择一些课程来学习，在课程里有些课程必须在某些课程之前学习，如高等数学总是在其它课程之前学习。现在有 �*N* 门功课，每门课有个学分，每门课有一门或没有直接先修课（若课程 a 是课程 b 的先修课即只有学完了课程 a，才能学习课程 b）。一个学生要从这些课程里选择 �*M* 门课程学习，问他能获得的最大学分是多少？



----

这道题目也是树形DP01背包问题。**并且与 二叉苹果树相似。**



这个课程体系就是一个树型结构，我们在这个树中选择 M 个节点，使得所选节点的数值和最大。

我们可以注意到，如果我们选择了 某一个非根节点，那么他的**父节点也一定会被选择**，需要满足直接先修课这个条件。

并且一个课程可能会影响多门课程，**所有他的结构是一颗多叉树，不止有两个孩子节点**

---

设dp [i] [j] 表示以 i 为根，选择 j 个节点的最大分数。
$$
dp[i][j]=max(dp[i][j],dp[son][k]+dp[i][j-k])
$$
其中 j 表示我们枚举的背包的容量（倒序枚举，01背包），son表示我们 以 i 为根节点的其中一个孩子节点，k表示我们往左右子树中分别选择的节点的个数，有点类似于 **区间dp的枚举区间分割点**，但是这个地方与那里不同。



```cpp
//TODO: Write code here
int n,m;
const int N=310;
int nums[N],w[N],ans,dp[N][N];
struct edge
{
    int to,w,next;
}Edge[N];
int head[N],cnt; 
void add_edge(int u,int v)
{
    Edge[++cnt].to=v; //u->v
    Edge[cnt].next=head[u];//以u为起点的前一个节点的编号为head[u]
    head[u]=cnt;  //更新以u为起点的最后一个节点的编号
}
void dfs(int root)
{
    //选择他的所有子节点的前提是一定要选择这个root节点
    dp[root][1]=nums[root];//root本身所具有的值,表示以root为根选择一个就是选择它本身
    for (int i=head[root];i!=-1;i=Edge[i].next)
    {
        int son=Edge[i].to;
        dfs(son);
        /*
        dp[i][j]: 表示以i为根，选择j个节点的获得的最大的学分
        */
        for (int j=m;j>=1;j--)
        {
            for (int k=j-1;k>=1;k--)
            {
                /*
                k表示root的其中一个孩子节点所选择的它的子节点的数量，因此dp[son][k]代表了root的其中一个孩子节点son所具有的一个最大学分
                则root的其中一个son选择了k个，那么root的其他son选择的就是j-k的，则其他孩子节点所具有的最大学分是dp[root][j-k]，包括root本身
                同时如果其中一个孩子节点选择了k=j=m个，那么root就不能选择了，所以k至多为j-1个，使得root本身可以被选择，如果root都不被选，则son们一定不会被选择
                */
                dp[root][j]=max(dp[root][j],dp[son][k]+dp[root][j-k]);
            }
        }
    }
}
signed main()
{
	cin>>n>>m;
    memset(head,-1,sizeof(head));
    for (int i=1;i<=n;i++)
    {
        int k,s;
        cin>>k>>s;
        nums[i]=s;
        add_edge(k,i);   
    }
    m++;
    dfs(0);
    cout<<dp[0][m];
#define one 1
	return 0;
}
```

