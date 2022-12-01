
@[TOC]

> 关于二分查找的概念，再次不过多描述，本篇我们主要讲解二分查找的几个关键因素，便于随时以后复习与查阅，避免二分查找的死循环问题！！！

# 三种方式的二分查找

## 1. 闭区间二分查找
* 在数组中查找第一次大于等于元素target 的位置：
> [1 2 3 4 5 6 7 ]    target = 5

![在这里插入图片描述](https://img-blog.csdnimg.cn/edef343cfbf94300ad501c83cc2f3809.png)

1. 图中蓝色区域代表 left 走过的距离。黄色代表 right 走过的距离
2. 在左右闭区间的情况下，二分查找的结束： right在left的左边，即left的位置指向目标位置，right指向目标位置的前一个位置。
3. 双闭区间下，返回 left的指向。

```cpp
int lower_bound(vector<int>& nums,int target)
    {
        int left=0,right=nums.size()-1;
        while (left<=right)//闭区间：[left,right]
        {
            int mid=left+(right-left)/2; //确定中间位置
            if (nums[mid]>=target)
            {
                right=mid-1; //target位于： [left,mid-1]
            }
            else
            {
                left=mid+1;  //target位于： [mid+1,right]
            }
        }
        return left;    //结束时，left指向的是目标位置，right指向目标的前一个位置
    }
```


## 2. 左闭右开二分查找
左闭右开的情况下：

1. right初始等于数组的长度，即一开始right位于数组的右外面
2. 循环时条件： left < right   当left = right时结束循环
3. right位置更新时，应为 right = mid 
4.  right最终会指向与left相同的位置，所以结束循环，此时left和right都指向目标位置

```cpp
 int lower_bound2(vector<int>& nums,int target)
    {
        int left=0,right=nums.size();
        while (left<right)  //左闭右开：[left,right)
        {
            int mid=left+(right-left)/2; //确定中间位置
            if (nums[mid]>=target)
            {
                right=mid; //target位于： [left,mid)
            }
            else
            {
                left=mid+1;  //target位于： [mid+1,right)
            }
        }
        return left;  // return right 都可以
    }
```

## 3. 开区间二分查找
双端开区间的情况下：

1. left初始等于-1，位于左外面；right初始等于数组的长度，right位于数组的右外面
2. 循环时条件： left + 1  < right   当left +1 = right时结束循环
3. left位置更新：left = mid；  right位置更新时，应为 right = mid  
4.  结束循环：此时right指向目标位置，left指向目标位置的前一个位置

```cpp
int lower_bound3(vector<int>& nums,int target)
    {
        int left=-1,right=nums.size();
        while (left+1<right)  //开区间：(left,right)
        {
            int mid=left+(right-left)/2; //确定中间位置
            if (nums[mid]>=target)
            {
                right=mid; //target位于： (left,mid)
            }
            else
            {
                left=mid;  //target位于： (mid,right)
            }
        }
        return right;  // right指向目标位置
    }
```

# 重要：二分查找中 >  >=   <=   < 等关系如何确定？

**本质：  二分查找的循环不变量！！**

我们设 target= x 数组： 【1，2，3，4，5，6，7，8】


* \>= x ：  返回大于等于x的第一个元素
*  \>  x 	 ：  相当于 ` >= （x + 1）`
*  \<  x：  相当于 `（>=x）- 1`
*  \<= x：相当于 ` （> x） - 1 `

![在这里插入图片描述](https://img-blog.csdnimg.cn/40b145f115e64dbcb14fca28da220c61.png)



# 例题：在排序数组中查找元素的第一个和最后一个位置

**leetcode 原题链接：**
[https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/)


> 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]。
你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

示例 1：

输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]
示例 2：

输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]
示例 3：

输入：nums = [], target = 0
输出：[-1,-1]

注意：你可以使用以上三种方式进行二分查找：闭区间，左闭右开，开区间

* 目标值的**开始位置**： `大于等于target的第一个元素位置` ---->  `>=x`
* 目标值的**结束位置**： `小于等于target的最后一个元素位置` -----> < x  ----> ` (>= x+1) -1`
```cpp
class Solution {
public:
    int lower_bound(vector<int>& nums,int target)
    {
        int left=0,right=nums.size()-1;
        while (left<=right) //闭区间：[left,right]
        {
            int mid=left+(right-left)/2; //确定中间位置
            if (nums[mid]>=target)
            {
                right=mid-1; //target位于： [left,mid-1]
            }
            else
            {
                left=mid+1;  //target位于： [mid+1,right]
            }
        }
        return left;    //结束时，left指向的是目标位置，right指向前一个位置
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        //1. 大于等于target的第一个元素位置
        // >=x
        int leftIdx=lower_bound3(nums,target);
        if (leftIdx>=nums.size() || nums[leftIdx]!=target)
        {
            return {-1,-1};
        }
        //2. 小于等于target的第一个元素位置
        // <=x  --->   (>4+1)-1
        int rightIdx=lower_bound3(nums,target+1)-1;
        return {leftIdx,rightIdx};
    }
};
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/8256ef50824447c1b540510b43fbe220.png)

