@[toc]


# next_permutation

cplusplus：
[next_permutation](https://cplusplus.com/reference/algorithm/next_permutation/)

作用：**得到所有的全排列**

例题：
[P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)

```cpp
void test1()
{
    int n;
    cin >> n;
    int* arr = new int[n];

    _rep(i, 0, n)
    {
        arr[i] = i + 1;
    }
    do {
        _rep(i, 0, n)
        {
            printf("%5d", arr[i]);
        }
        cout << endl;
    } while (next_permutation(arr, arr + n));
    delete[] arr;
}
```
当然这样类似的题目也可以使用**回溯法**实现，回溯法是实现这类问题的主要方法。


-----

# lower_bound 与 upper_bound
lower_bound：**得到大于等于这个数字的第一个元素。** 否则（没有找到）返回**尾后迭代器**
upper_bound：**得到大于这个数字的第一个元素**。否则，返回**尾后迭代器**。

这两个算法的实现就是运用了二分查找的思想，STL用于二分查找的函数：**binary_search**。

这两个函数在查找**找到元素第一个与最后一个元素**的下标位置的题目中有**奇效**。

例题：[力扣 34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/)

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        auto it1=lower_bound(nums.begin(),nums.end(),target);
        if (it1==nums.end() || *it1!=target) return {-1,-1};
        auto it2=lower_bound(nums.begin(),nums.end(),target+1)-1;
        return {int(it1-nums.begin()),int(it2-nums.begin())};
    }
};
```
这道题目也可以我们自己来实现二分查找的功能，具体实现可细节可以看我这篇博客：
[二分查找的多种实现方式及本质解析（c++实现 + 例题）](https://blog.csdn.net/jj6666djdbbd/article/details/127951585?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167143957016782428633135%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fblog.%2522%257D&request_id=167143957016782428633135&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-1-127951585-null-null.nonecase&utm_term=%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE&spm=1018.2226.3001.4450)


----

# partial_sum

>partial_sum位于头文件numeric中。


作用： **用于求原数组的前缀和，并且保存于一个新的目标数组中。**

前缀和是我们的一个重要的算法思想，使用这个函数，可以快速求某一个序列的前缀和。

函数接受一个**原序列的头和尾**，接受**一个目标序列**，最终目标序列的某一位存储的就是原序列到某一位为止的前缀和。

如下：

>y0 = x0
y1 = x0 + x1
y2 = x0 + x1 + x2
y3 = x0 + x1 + x2 + x3
y4 = x0 + x1 + x2 + x3 + x4

实现：

```cpp
//前缀和
void test2()
{
    vector<int> src{ 1,2,3,4,5 };
    vector<int> dst;
    partial_sum(src.begin(), src.end(), back_inserter(dst));
    _rep(i, 0, dst.size())
    {
        cout << dst[i] << " ";
    }
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/f548484891bb45b080bc054a8b5d9144.png)


----


# sort 与 unique

sort：给一个序列排序
unique：对序列去重，注意这里的去重是指把重复多余的数字放在不重复的序列的后面而已，并不是真正的删除，使用erase来删除后面。返回排序后第一个多余的元素的位置。

例题：[P1138 第 k 小整数](https://www.luogu.com.cn/problem/P1138#submit)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n,k;
    cin>>n>>k;
    vector<int> arr(n);
    for (int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    //排序
    sort(arr.begin(),arr.end());
    //去重,返回去重后的迭代器
    auto it=unique(arr.begin(),arr.end());
    int len=int(it-arr.begin());
    if (len<k) cout<<"NO RESULT";
    else cout<<arr[k-1];
    return 0;
}

```

