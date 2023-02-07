@[toc]

# 石子合并

[题目传送门](https://www.luogu.com.cn/problem/P1880)



>在一个圆形操场的四周摆放 �*N* 堆石子，现要将石子有次序地合并成一堆，规定每次只能选相邻的 22 堆合并成新的一堆，并将新的一堆的石子数，记为该次合并的得分。试设计出一个算法,计算出将 �*N* 堆石子合并成 11 堆的最小得分和最大得分。



**设dp[i] [j]表示 将i堆合并到j堆的最小得分**（最大得分同理）

sum[i] [j]表示 i堆到 j堆的石子的和

我们可以将石子堆从小堆逐渐推导：

1. 合并一堆：dp[i] [j]=sum[i] [j]，其中 i==j
2. 合并两堆：dp[i] [j]=dp[i] [i]+dp[j] [j] 
3. 合并三堆：
   1. 前两堆合并后与第三堆合并：dp[i] [j]=dp[i] [j-1] +dp[j] [j]
   2. 后两堆合并后与第一堆合并：dp[i] [j]=dp[i+1] [j]+dp[i] [i]
   3. 两者取一个**最小值**
4. 合并四堆：
   1. 前三堆合并后与第四堆合并：dp[i] [j]=dp[i] [j-1] +dp[j] [j]
   2. 后三堆合并后与第一堆合并：dp[i] [j]=dp[i+1] [j]+dp[i] [i]
   3. 两者取一个**最小值**



----



综上： 状态转移方程： 
$$
dp[i][j]=min(dp[i][k]+dp[k+1][j]+sum[i][j],dp[i][j])
$$
其中 k表示两堆之间的分割，再最后合并成两堆后，别忘了**合并成最后一堆**，加上sum[i] [j]

 

本题需要注意点：

* 这是一个**环形**，而我们上述所讨论的情况是**一条链**，因此我们把这个**环形拉长变成一条链**
* 环形拉长后形成的链长应为**初始的长度的二倍**

* 最后：在这条长链中的任意起点和终点位置寻找一个最小值和最大值，得到的即是N堆石子合并后的最小值和最大值



AC code：

```cpp
//TODO: Write code here
int n,m;
const int N=2e3+10;
int nums[N],dpmax[N][N],dpmin[N][N],sum[N][N];
signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>nums[i];
		nums[i+n]=nums[i];
		sum[i][i]=nums[i],sum[i+n][i+n]=nums[i+n];
	}

	for (int len=2;len<=n;len++)
	{
		for (int i=1;i+len<=(n<<1)+1;i++)	//寻找起点
		{
			int j=i+len-1;//对应的终点
			dpmax[i][j]=0,dpmin[i][j]=INF;
			for (int k=i;k<j;k++)	//分割成两堆，
			{
				sum[i][j]=sum[i][k]+sum[k+1][j];//首先计算[i,j]的和
				dpmin[i][j]=min(dpmin[i][k]+dpmin[k+1][j]+sum[i][j],dpmin[i][j]);
				dpmax[i][j]=max(dpmax[i][k]+dpmax[k+1][j]+sum[i][j],dpmax[i][j]);
			}
		}
	}
	int ansMax=0,ansMin=INF;
	for (int i=1;i<=n;i++)
	{
        //寻找一条链中能够形成的最大和最小的值
		ansMin=min(ansMin,dpmin[i][i+n-1]);
		ansMax=max(ansMax,dpmax[i][i+n-1]);
	}
	cout<<ansMin<<endl<<ansMax;
#define one 0
	return 0;
}
```





-----

# Cheapest Palindrome G

[题目传送门](https://www.luogu.com.cn/problem/P2890)

> 字串S长M，由N个小写字母构成。欲通过增删字母将其变为回文串，增删特定字母花费不同，求最小花费。



我们可以得到一个性质： **当我们把一个字符串通过添加a字符或者删除a字符变为回文串的时候，我们可以发现我们只需要进行a字符的最小花费的操作即可。**



例如 ： abcb    删除a：1200  添加a：1000

1. 删除头a，则bcb是回文串，总花费为1200
2. 添加尾a，则abcba是回文串，总花费为1000
3. **所以我们只需要统计一下每个字符花费的最小的操作即可**

----



定义dp[i] [j]表示将字符串的[i,j] 修改为回文串的最小花费

1. 当a[i] =a[j]的时候，意味着首尾字符相等，则[i,j]的最小花费就等于 [i+1,j-1]的最小花费，即**此时无需操作。**
2. 否则，首尾字符不相等，我们需要对字符串进行操作。
   1. 把[i,j-1]改为回文串，然后再单独操作一个a[j]
   2. 把[i+1,j]改为回文串，然后再单独操作一个a[i]
   3. **求两种操作的最小值**





----

状态转移方程如下：
$$
dp[i][j]=min(dp[i+1][j]+cost[a[i]],dp[i][j-1]+cost[s[j]])
$$


AC code

```cpp
//TODO: Write code here
int n,m;
const int N=5e3+10;
char s[N];
int dp[N][N];
umap<char,int> me;
signed main()
{
	cin>>n>>m;
    scanf("%s",s+1);
    //memset(dp,INF,sizeof(dp));
    for (int i=1;i<=n;i++)
    {
        char ch;
        int a,b;
        cin>>ch>>a>>b;
        me[ch]=min(a,b);    //只需要记录最小代价即可
        //dp[i][i]=0;
    }
    //dbgumap(me);
    /*
    dp[i][j]: 表示以i,j为字符串左右构成的回文串的最小代价
    */
    for (int len=2;len<=m;len++)    //区间长度
    {
        for (int i=1;i<=m-len+1;i++)    //区间起始点
        {
            int j=i+len-1;  //区间终点
            if (s[i]==s[j]) dp[i][j]=dp[i+1][j-1];
            else dp[i][j]=min(dp[i+1][j]+me[s[i]],dp[i][j-1]+me[s[j]]);
        }
    }

#define one 0
    //dbg(dp,m,m);
    cout<<dp[1][m];
	return 0;
}
```



-----

# 最少操作数（粉刷字符串）

[题目传送门](https://www.lanqiao.cn/problems/1548/learning/)



> 给定两个长度相等的字符串 �*A*、�*B*，由小写字母组成。
>
> 现有一种操作，可以把 �*A* 中的一个连续子串（区间）都转换为某个字符（就像用刷子刷成一样的字符）。
>
> 问要把 �*A* 转换为 �*B*，最少的操作数是多少?



定义dp[i] [j]表示字符串A从[i,j] 范围的转换的最少操作数



首先用一个空串模拟转换为B串的过程，然后用A串转换为B串



首先模拟用空串转换为B：

1. b[i]=b[j]，如果B两端字符相同，则会产生这种情况：空串： a***a， B串：abbba
   1. 粉刷[i,j-1]，则变为 aaaaa，然后再对 [i+1,j-1]粉刷：则变为 abbba，粉刷次数为2
   2. 粉刷[i+1,j]，则变为 aaaaa，然后再对 [i+1,j-1]粉刷：则变为 abbba，粉刷次数也为2
   3. 因此，当两端字符相同时，对dp[i] [j] 的操作次数就为dp[i] [j-1] 或者dp[i+1] [j]，两者的操作次数是一致的
2. 当两端字符不一致时，使用” 石子合并“ 的方法，分割区间，逐步取得区间的最小值



**然后我们再根据空串转换为B串的DP方程所得到的结果来处理A串转换为B串的形式，注意此时我们只对终点进行操作，因为我们要固定a的起点，得到从a[1]转换为a[j]的最少操作数**



----



状态转移方程如下：


$$
dp[i][j]=dp[i][j-1] || (dp[i+1][j])  , b[i]==b[j] \\
dp[i][j]=min(dp[i][k]+dp[k+1][j],dp[i][j])
$$


AC code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005,INF=0x3F3F3F3F;
char a[N], b[N];
int dp[N][N];
int main()
{
    scanf("%s%s", a + 1, b + 1);
    int n = strlen(a + 1);
    for (int i = 1; i <= n; i++) dp[i][i] = 1;    //单个字符转换次数为1
    /*
    dp[i][j]: 表示[i,j]内转换的最少操作数
    */

    //将一个空串转换为b串：预处理
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i <= n - len + 1; i++)//起点
        {
            int j = i + len - 1;    //终点
            dp[i][j] = INF;
            if (b[i] == b[j])
            {
                dp[i][j] = dp[i][j - 1];  //dp[i][j]=dp[i+1][j]
            }
            else
            {
                /*
                "合并石子": abbbc
                */
                for (int k = i; k < j; k++) //区间分割
                {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }   
            }
        }
    }
    //将a串转换为b串: dp[1][j]: 从1转换到j的最少操作数
    for (int j = 1; j <= n; j++)
    {
        if (a[j] == b[j])
        {
            dp[1][j] = dp[1][j - 1];//当前字符相同不用转，[1,j]的操作数就等于上一次的操作数
        }
        else
        {
            for (int k = 1; k < j; k++)    //分割[1,j]的区间
            {
                dp[1][j] = min(dp[1][j], dp[1][k] + dp[k + 1][j]);
            }
        }
    }
    cout << dp[1][n];
    return 0;
}
```



-----



# 相亲的男孩们

[题目传送门](https://www.lanqiao.cn/problems/1549/learning/)



> *n* 个男孩去相亲，排成一队上场。大家都不想等，排队越靠后越愤怒。每人的耐心不同，用 �*D* 表示火气，设男孩 �*i* 的火气是 ��*D**i*，他排在第 �*k* 个时，愤怒值是 (�−1)∗��(*k*−1)∗*D**i*。
>
> 主持人不想看到会场气氛紧张。他安排了一个黑屋，可以调整这排男孩上场的顺序，屋子很狭长，先进去的男孩最后出来（黑屋就是一个**堆栈**）。
>
> 例如，当男孩 �*A* 排到时，如果他后面的男孩 �*B* 火气更大，就把 �*A* 送进黑屋，让 �*B* 先上场。一般情况下，那些火气小的男孩要多等等，让火气大的占便宜。不过，零脾气的你也不一定吃亏，如果你原本排在倒数第二个，而最后一个男孩脾气最坏，主持人为了让这个坏家伙第一个上场，把其他人全赶进了黑屋，结果你就排在了黑屋的第 11 名，第二个上场相亲了（注意，每个男孩都要进出黑屋）。
>
> 对所有男孩的愤怒值求和，求所有可能情况的最小和。





定义dp[i] [j]表示[i,j]个人的最小愤怒值之和



---





我们假设第 i 个人第 k个出场，男孩们的火气值分别为 1,2,3,4,5

如果 i =1 ， k = 3，则我们应该让 第一个人第三个出场，根据**栈的含义**，我们应该这样安排：

1入栈，2入栈，3入栈 ，3出栈，2出栈，1出栈 ，后面的4，5不变

则男孩们的出场顺序为：  3  2  1  4  5



我们可以分三段对他进行分析

1.  k-1 之前的人全部往左移动，即往前移动，表示为dp[i+1] [k] 
2. 第 i 个人往后移动 k-i个位置，因此它的火气值应该为： D[i]*(k-i)
3. 剩余的k后面的人，全部不动，离他们上场最少还有 k-i+1 个位置，并且他们也有火气值：dp[k+1] [j]+ (k-i+1)* (sum[j]-sum[k])



-----

![在这里插入图片描述](https://img-blog.csdnimg.cn/a64544d6a2ca4484b6f9d8b29410fcf2.png)


状态转移方程为：
$$
dp[i][j]=min(dp[i][j],\\
dp[i+1][k]+D[i]*(k-i)+dp[k+1][j]+(k-i+1)*(sum[j]-sum[k]))
$$
其中，k表示**分割的区间的位置**，即第i个男孩移动到的位置，sum表示区间和





AC code 

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005,INF=0x3F3F3F3F;
char a[N], b[N];
int dp[N][N];
int t, n;
int D[N];
int sum[N];
void solve2()
{
    cin >> t;
    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        cin >> n;
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> D[i];
            sum[i] = sum[i - 1] + D[i];
        }
        /*
        dp[i][j]：表示 [i,j]的最小愤怒值之和
        */
        for (int len = 2; len <= n; len++)
        {
            for (int i = 1; i <= n - len + 1; i++)
            {
                int j = i + len - 1;
                dp[i][j] = INF;
                for (int k = i; k <= j; k++)
                {
                    dp[i][j] = min(dp[i][j],
                        dp[i + 1][k] +    //1. i+1到k的人往前挪
                        D[i] * (k - i) +    //2. 第i个人往后移动k-i个位置
                        dp[k + 1][j] + (k - i + 1) * (sum[j] - sum[k]));//3. k后面的人往前移动k-i+1个位置 
                }
            }
        }
        cout << dp[1][n]<<endl;
    }
}
int main()
{
    solve2();
    return 0;
}
```









