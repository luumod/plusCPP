@[toc]

# 图论：三种最短路及模板

注意：在这三种算法 中我均使用的 **链式前向星存图**，具体方式请看我这篇博客：[链式前向星存图详解](https://blog.csdn.net/jj6666djdbbd/article/details/128923459?spm=1001.2014.3001.5502)

## 模板
### SPFA算法

spfa是优化后的Bellmax-ford算法，采用了 **队列进行优化**

SPFA可以用来处理负权边的情况，通常用于求带**负边权的单源最短路径问题**

```cpp
//TODO: Write code here
int n,m,s;
const int N=1e5+10;
int nums[N];
struct Edge
{
    int to,w,next;
}edge[N];
int dis[N];
bool vis[N];
int head[N],cnt;
void add_edge(int u,int v,int w)
{
    edge[++cnt].next=head[u];
    edge[cnt].to=v;
    edge[cnt].w=w;
    head[u]=cnt;
}
void spfa()
{
    for (int i=1;i<=n;i++)
    {
        dis[i]=INF;   //起点到i点的距离为一个极大值
        vis[i]=false;
    }
    queue<int> q;
    //起点入队，标记起点，起点距离为0
    q.push(s);
    vis[s]=true;
    dis[s]=0;
    while (!q.empty())
    {
        auto p=q.front();   //取出这个待优化的点
        q.pop();
        vis[p]=false;
        for (int i=head[p];i;i=edge[i].next)
        {//寻找与p队头元素相连的边
            int v=edge[i].to;
            if (dis[v]>dis[p]+edge[i].w)//对 p->v 的每条边寻找一个最短路径的边
            {
                //松弛操作
                dis[v]=dis[p]+edge[i].w;
                if (!vis[v])
                {
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
}
signed main()
{
	cin>>n>>m>>s;
    for (int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);
    }  
    spfa();
    for (int i=1;i<=n;i++)
    {
        cout<<dis[i]<<" ";
    }
#define one 1
	return 0;
}
```



----



### Floyd算法

弗洛伊德算法使用三重循环，时间复杂度较高

```cpp
//TODO: Write code here
int n,m,s;
const int N=1e4+10;
int dis[N];
int G[N][N];
signed main()
{
	cin>>n>>m>>s;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            G[i][j]=INF;
        }
    }
    for (int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        G[u][v]=min(G[u][v],w);
    }
    for (int k=1;k<=n;k++)
    {
        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=n;j++)
            {
                G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
            }
        }
    }
    G[s][s]=0;
    for (int i=1;i<=n;i++)
    {
        cout<<G[s][i]<<" ";
    }
#define one 1
	return 0;
}
```



----

### Dijkstra算法

迪杰斯特拉算法采用**堆优化**的方法，是求最短路三种方法中的**较优的方法**



获取每一个点的顶点编号，然后对这个顶点**相连的所有边进行遍历求最短路径**，并且处理完成之后把每个点入队，然后接下来继续对队列中的点弹出并且最短路径，直到队列为空。

另外，如果我们的**起点到 一个点有多条路径**，则dis会记录当前一条路径的最短路径，而 pair的first记录的则不一定是最短路径，则如果 **我们发现  dis[u] < p.first 则直接跳转下一个点即可**，表示的是当前到该点的路径已经是最短的了，无需再次进行松弛操作。

```cpp
//TODO: Write code here
int n,m,s;
const int N=1e6+10;
struct Edge
{
    int to,val,next;
}edge[N];
int head[N],cnt,dis[N];
void add_edge(int u,int v,int w)
{
    edge[++cnt].next=head[u];
    edge[cnt].to=v;
    edge[cnt].val=w;
    head[u]=cnt;
}
void dijsktra()
{   
    for (int i=1;i<=n;i++)
    {
        dis[i]=INF;
    }
    priority_queue<PI,v<PI>,greater<PI>> q;
    dis[s]=0;
    q.push({0,s});  //起点入堆
    while (!q.empty())
    {
        PI p=q.top();
        q.pop();
        int u=p.second;//获取以u为起点的顶点编号
        if (dis[u]<p.first) continue;
        for (int i=head[u];i;i=edge[i].next)//遍历与u相连的所有点，寻找最短路径
        {
            int v=edge[i].to;
            if (dis[v]>dis[u]+edge[i].val)
            {
                dis[v]=dis[u]+edge[i].val;
                q.push({dis[v],v});
            }
        }
    }
}
signed main()
{
	cin>>n>>m>>s;
    for (int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);    //单向边
    }
    dijsktra();
    for (int i=1;i<=n;i++)
    {
        cout<<dis[i]<<' ';
    }
#define one 1
	return 0;
}
```

---

## 应用

### 反向建边

例题：[邮递员送信](https://www.luogu.com.cn/problem/P1629)

> 有一个邮递员要送东西，邮局在节点 11。他总共要送 �−1*n*−1 样东西，其目的地分别是节点 22 到节点 �*n*。由于这个城市的交通比较繁忙，因此所有的道路都是单行的，共有 �*m* 条道路。这个邮递员每次只能带一样东西，并且**运送每件物品过后必须返回邮局**。求送完这 �−1*n*−1 样东西并且**最终回到邮局**最少需要的时间。

----

从起始点出发到每个点的最短距离： 直接使用一次 dijktra算法计算单源最短路径即可。

但是我们发现还需要求从**每个点再回到起点**的最短路径。

我们能否求出起点到终点的**距离乘2** ？？这不就是往返两趟的路程吗？？？

请注意： **道路是单向边**，过去有道路可走，回来不一定有路！



因此，本题核心：**反向建边，再进行一次反向的 disktra** 

起点到每个点：**一对多的关系**；每个点到起点：**多对一的关系，我们要把它转换为一对多的关系**

----



如何反向建边？？

1. 使用邻接矩阵：邻接矩阵存边，是采用数组的形式，记录的 u 到 v 的边用 edge[u] [v]表示，正向的时候，我开门直接用即可；**反向的时候：我们采用 swap，交换每一个 u 与 v ，这就成了反向的图了**

2. 使用链式前向星存图： add_edge添加 u 到 v，权值为 w的边，则**我们把 u 加上 n，v 加上 n，确保点之间不会出现冲突，然后 add_edge添加 v+n 到 u+n，权值为 w 的边**，这样既不会产生冲突，我们也建了**n条反向的边**



然后分别进行 dijkstra算法即可，我们传入每个的起点，**分别为  1 和 1+n，同时注意dis 的清除**

```cpp
//TODO: Write code here
int n,m;
const int N=5e6+10;
int nums[N];
struct Edge
{
    int to,w,next;
}edge[N];
int head[N],cnt,dis[N];
void add_edge(int u,int v,int w)
{
    edge[++cnt].next=head[u];
    edge[cnt].to=v;
    edge[cnt].w=w;
    head[u]=cnt;
}
void dijktra(int s)
{
    memset(dis,0x3F,sizeof(dis));
    dis[s]=0;
    priority_queue<PI,v<PI>,greater<PI>> q;
    q.push({0,s});
    while (!q.empty())
    {
        auto p=q.top();
        q.pop();
        int u=p.second;
        if (dis[u]!=p.first) continue;
        for (int i=head[u];i;i=edge[i].next)
        {
            int v=edge[i].to;
            if (dis[v]>dis[u]+edge[i].w)
            {
                dis[v]=dis[u]+edge[i].w;
                q.push({dis[v],v});
            }
        }
    }
}
signed main()
{
	cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);
        add_edge(v+n,u+n,w);
    }
    int ans=0;
    dijktra(1);
    for (int i=2;i<=n;i++)
    {
        ans+=dis[i];    
    }
    dijktra(1+n);
    for (int i=2+n;i<=(n<<1);i++)
    {
        ans+=dis[i];    
    }
    cout<<ans;
#define one 1
	return 0;
}
```



---

### 最短路计数

[题目传送门](https://www.luogu.com.cn/problem/P1144)



> 给出一个 �*N* 个顶点 �*M* 条边的无向无权图，顶点编号为 1∼�1∼*N*。问从顶点 11 开始，到其他每个点的最短路有几条。



题目让我们对最短路径条数进行**计数**

并且这个图是一个**无向无权图**，因此我们假设每一条边的**权值为 1**，进行**正常的求最短路径的过程**

只不过我们需要一个ans数组，**ans[i] 表示从 1 到 i 点的最短路径的条数**。

**我们在利用dijsktra求出 从 u到 v 点的路径长度的时候，需要初始化 ans[v] 为 ans[u]条路径  ；当有多条路径的时候，则此条路径的最短路径长度应该和我们之前记录的最短的长度是相等的，因此直接加上之前的最短路径的条数即 ans[v]+=ans[u]。**

注意ans[1] 初始化为1，1到1默认有一条路径



过程如下：

1.  点1到点2有一条路径，ans[2] =1
2.  点1到点3有一条路径，ans[3] =1
3.  点1到点4有**两条**路径，1->2->4 和 1-> 3->4 ，ans[4] =2
4.  点1到点5有**四条**路径，1->2->4->5（两条）,1->3->4->5（两条）ans[5] =4



```cpp
//TODO: Write code here
int n,m;
const int N=5e6+10,mod=100003;
int nums[N],ans[N];
struct Edge
{
    int to,next;
}edge[N];
int head[N],cnt,dis[N];
void add_edge(int u,int v)
{
    edge[++cnt].next=head[u];
    edge[cnt].to=v;
    head[u]=cnt;
}
void dijktra()
{
    memset(dis,INF,sizeof(dis));
    priority_queue<PI,v<PI>,greater<PI>> q;
    dis[1]=0;
    ans[1]=1;
    q.push({0,1});
    while (!q.empty())
    {
        auto p=q.top();
        q.pop();
        int u=p.second;
        if (dis[u]<p.first) continue;
        for (int i=head[u];i;i=edge[i].next)
        {
            int v=edge[i].to;
            if (dis[v]>dis[u]+1)
            {
                dis[v]=dis[u]+1;
                ans[v]=ans[u];
                q.push({dis[v],v});
            }
            else if (dis[v]==dis[u]+1)
            {
                ans[v]+=ans[u];
                ans[v]%=mod;
            }
        }
    }
}
signed main()
{
	cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        add_edge(u,v);
        add_edge(v,u);
    }
    dijktra();
    for (int i=1;i<=n;i++)
    {
        cout<<ans[i]<<endl;
    }
#define one 1
	return 0;
}
```

