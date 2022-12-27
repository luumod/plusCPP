
# 82. 删除排序链表的重复元素
力扣传送：
[https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/description/](https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/description/)

> 给一个排好序的链表，删除把链表中出现的所有的重复的项：
> 1 2 2 3 3 3 4 5   ----->  1  4 5

这道题有很多种解法，我第一眼看到这题的时候，想到了 哈希表。
利用哈希表来记录出现的重复的节点元素，接着在遍历链表，等到这个节点出现在了哈希表中，则while 循环一直跳过这个节点，直到跳到下一个不同的元素为止。

![在这里插入图片描述](https://img-blog.csdnimg.cn/4a07189649d549e39951cfad870811ba.png)

---


哈希表的做法:

1. 首先遍历一边链表，记录下哈希表的数据
2. 然后再遍历一遍链表，当哈希表记录的此节点处的值出现的次数大于一次时，一直while找到直到下一个等于一次的节点位置，然后连接前一个节点位置，这样就做到了**跳过了出现次数大于二的节点的中间节点。**
3. 双指针分别连接链表节点。
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        unordered_map<int,int> m;
        ListNode* temp=head;
        while (temp)
        {
  			//首先初始化哈希表，记录下每个节点的值出现的次数
            m[temp->val]++;
            temp=temp->next;
        }
        ListNode* pDummy=new ListNode{-101,head};
        ListNode* slow=pDummy;
        ListNode* fast=head;
        while (fast && fast->next)
        {
            if (m[fast->val]>1)
            {
                ListNode* pTemp=fast->next;
                while (fast && m[fast->val]>1)
                {
                    fast=fast->next;
                }
                slow->next=fast;
            }
            else
            {
                slow=slow->next;
                fast=fast->next;
            }
        }
        return pDummy->next;
    }
};
```

哈希表的缺点：
我们的哈希表的空间随着链表的增大而增大，空间复杂度达到了O（N）。

**但其实我们没必要使用哈希表。**
我们知道用哈希表来记录出现次数大于一次的节点，那我们能不能直接用**双指针的快指针**来记录呢？ **只需要合适的边界检测，就可以记录下其快指针的 当前节点元素和 下一个节点元素的值，判断他们是否相等即可。**

实现：

1. 哑节点方便返回链表（pDummy）
2. 慢指针在前，快指针在后，快指针移动一步，每次快指针都判断它当前的值和后面的值想不想等，如果相等，则快指针进入while循环，一直跳过。
3. 等到处理完毕后， 慢指针前进一步，等于快指针；快指针再前进一步，等于next

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* pDummy=new ListNode{-101,head};
        ListNode* slow=pDummy;
        ListNode* fast=head;
        while (fast && fast->next)
        {
            int val=fast->val;
            if (val==fast->next->val)
            {
                while (fast && fast->val==val)
                {
                    fast=fast->next;
                }
                slow->next=fast;
            }
            else
            {
                slow=fast;
                fast=fast->next;
            }
        }
        return pDummy->next;
    }
};
```

时间复杂度：O（N）只遍历链表一遍，空间复杂度：O（1）

-----



# 15. 三数之和
力扣传送门：
[https://leetcode.cn/problems/3sum/description/?envType=study-plan&id=suan-fa-ji-chu&plan=algorithms&plan_progress=y00ve32](https://leetcode.cn/problems/3sum/description/?envType=study-plan&id=suan-fa-ji-chu&plan=algorithms&plan_progress=y00ve32)


>找到数组中是否包含三个元素使得 nums[i]+nums[j]+nums[z] =0 

这道题目一看看出就可以使用暴力搜索的做法：首先给数组排序，然后创建一个三重循环，每重循环遍历每一个元素；注意，我们的元素可能会出现重复项，因此我们要跳过两重循环中可能遍历到的重复的项：

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int n=nums.size();
        sort(nums.begin(),nums.end());
        for (int i=0;i<n;i++)
        {
            if (i==0 || nums[i]!=nums[i-1])
            {
                for (int j=i+1;j<n;j++)
                {
                    if (j==i+1 || nums[j]!=nums[j-1])
                    {
                        for (int z=j+1;z<n;z++)
                        {
                            if (z==j+1 || nums[z]!=nums[z-1])
                            {
                                 if (nums[i]+nums[j]+nums[z]==0)
                                {
                                    res.push_back({nums[i],nums[j],nums[z]});
                                }
                            }
                        }
                    }
                }
            }
        }
        return res;
    }
};
```

我们的时间复杂度达到了O（N^3） 这对于最长数据量3000来说是很容易超时的，因为 3000 * 3000 * 3000 相乘后达到了27,000,000,000，即这就是三重循环的最坏的情况，因此暴力搜索的方法无法通过。

-----

我们引入一个新方法：

**利用双指针降低维数： 利用双指针把三重循环降低为二重循环。**

1. 当我们确定第一个数字之后，**如果第二个数字增大，则第三个数字必定减小。**
2. 令第二个数字和第三个数字**同时寻找。**
3. 第二个数字起始位于第二重循环的开头，第三个数字起始位于第二重循环的末尾。

我们就可以保持第二重循环不变，==**而将第三重循环变成一个从数组最右端开始向左移动的指针**==
![在这里插入图片描述](https://img-blog.csdnimg.cn/d4c816a85a1447288b9471fcda9abe61.png#pic_center)



```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n=nums.size();
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        for (int i=0;i<n;i++)
        {
            //当前项和前一项相同，则当前数字已经被刚才用过了，则直接跳过这个数字
            if (i>0 && nums[i]==nums[i-1])
            {
                continue;
            }
            //第二重循环同时遍历 j 和 z
            int z=n-1;  //初始化z的位置，z从后往前
            for (int j=i+1;j<n;j++)   //j从前往后
            {
                //同理，跳过重复的数字
                if (j>i+1 && nums[j]==nums[j-1])
                {
                    continue;
                }
                //同时需要保证j<z：因为j作为左指针一定要在z右指针的左边
                while (j<z && nums[i]+nums[j]+nums[z]>0)
                {
                    //因为序列从小到大排序，当前的结果大于0，则减小z,寻找合适的位置
                    --z;
                }
                //如果j 和 z相遇，则表示无论j再往后，z再往前，他们都不可能再有结果了（和为0），因为j再往后遍历的数字一定和z之前的一个数字相同; z也是，一定和j之前的一个数字相同，我们已经遍历过了，所以这种情况直接退出 
                if (j==z)
                {
                    break;
                }
                if (nums[i]+nums[j]+nums[z]==0)
                {
                    res.push_back({nums[i],nums[j],nums[z]});
                }
            }
        }
        return res;
    }
};
```

总结：

当我们需要**枚举数组中的两个元素**时，如果我们发现随着**第一个元素的递增，第二个元素是递减的**，那么就可以使用**双指针**的方法，将枚举的时间复杂度从 **O(N^2)减少至 O(N)**
