@[toc]
# 合并两个有序链表
传送门：
[https://leetcode.cn/problems/merge-two-sorted-lists/description/](https://leetcode.cn/problems/merge-two-sorted-lists/description/)


题目要求；
给你两个有序的链表，将这两个链表按照从小到大的关系，合并两个链表为一个新的链表。

![在这里插入图片描述](https://img-blog.csdnimg.cn/92e4433dbe5548ab8f02c3d04228209e.png)

解： 
看到两个合成一个的，我们就可以利用二路归并的思想来解决，这道题也是如此。
关于顺序表和链表的二路归并可以看我之前发表的一篇博客：
[顺序表和单链表的二路归并问题](https://blog.csdn.net/jj6666djdbbd/article/details/127037612?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166954981116782388053513%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fblog.%2522%257D&request_id=166954981116782388053513&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-1-127037612-null-null.nonecase&utm_term=%E4%BA%8C%E8%B7%AF&spm=1018.2226.3001.4450)

---

我们本节主要讨论如何**利用递归**来求解合并两个单链表的问题？

设计递归：

* 递归的终止：当递归到**单链表1 == nullptr**，或者**单链表2 == nullptr** 的时候，则终止递归，并且我们可以得知，**当一个链表为空时，另一个链表一定还没有遍历完，所以我们返回其对应的另一个链表。**
* 递归如何进行：我们每次比较list1与list2的节点值得大小，**让较小的链表的next进入递归，并且存储递归返回的结果。**

过程：以1 2 4 --- 1 3 4两个链表为例子。

1. 首先list1的值与list2的值相同，但是当list1的值大于等于list2的时候，我们都操纵list2，list2的next进入递归，此时list2指向 节点3.
2. 比较节点1 与 节点3，list1的节点值小，所以操纵list1的next，进入递归.
3.  一直往下递归，直到最后，list2指向了空，图中 **蓝色圈5** 所示。
4. 此时，我们递归已经完成，接下来该回溯了。
5. 节点依次回溯到上一个节点的next，例如图中的 橙色圆圈就是回溯的过程，与之对应的是蓝色圆圈的递归的过程。
6. 一直回溯到起点，节点指针依次连接，我们就得到了一条新的链表，这个链表就是我们合并后的新链表。
![在这里插入图片描述](https://img-blog.csdnimg.cn/ee193f5279c24b789cc190f46db2fcec.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/8f9ec41362a34b6abd62550c0b0705c6.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/8ef436ccbf4441749bf4fff1493b4cb9.png)
代码示例：

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1==nullptr)
        {
            return list2;
        }
        if (list2==nullptr)
        {
            return list1;
        }
        //每一次找到节点值小的链表进入递归
        if (list1->val>=list2->val)
        {
            list2->next=mergeTwoLists(list1,list2->next);
            return list2;
        }
        list1->next=mergeTwoLists(list1->next,list2);
        return list1;
    }
};
```


-----

# 翻转链表
传送门：
[https://leetcode.cn/problems/reverse-linked-list/description/](https://leetcode.cn/problems/reverse-linked-list/description/)

题目要求：把一个单链表的所有节点原地翻转。

我们可以利用迭代来求解这个问题：

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pTemp=nullptr;
        ListNode* pCur=head;
        //前一个节点置空，可以在第一步就断开链表
        ListNode* pPre=nullptr;
        while (pCur)
        {
        	//1. 保存下一个节点位置
            pTemp=pCur->next;
            //2. 当前节点指向前一个节点
            pCur->next=pPre;
            //3. 前一个节点指向当前节点
            pPre=pCur;
            //4. 继续遍历下一个节点
            pCur=pTemp;
        }
        return pPre;
    }
};
```
迭代的方式很简单，自己画图就可以理解，重点要理解**第二步与第三步**。

---

接下来我们看**递归：**

设定一个pNew节点为我们的结果，最后返回pNew即可。

**递去**： 当节点为空或者next为空时，返回此节点，

1. **回溯第一步**：pNew节点指向5，此时已经回溯==一==次了，所以head指向4，head的next的next等于head，即让pNew的节点5连接节点4；head->next为空，即让前一个head节点4断开，后一个head节点4指向空。形成了 **5 -> 4 -> NULL**
![在这里插入图片描述](https://img-blog.csdnimg.cn/65b5a3f558064bd5862c600cc6e321f3.png)

---

2. **回溯第二步**：pNew节点还是指向5，此时是回溯的第==二==次，所以**head指向3**，注意head的位置，==相当于**head**和**第一步逆转的节点5**同时指向节点4==，head的next的next等于head，即让pNew的节点4连接节点3；head->next为空，即让前一个head节点3断开，后一个head节点3指向空。形成了 **5 -> 4 -> 3 ->  NULL**
![在这里插入图片描述](https://img-blog.csdnimg.cn/0dcd398942d343e89c2df96c10a9bc51.png)
---

3. **回溯第三步**：pNew节点还是指向5，此时是回溯的第==三==次，所以**head指向2**，注意head的位置，==相当于**head**和**第二步逆转的节点4**同时指向节点3==，head的next的next等于head，即让pNew的节点3连接节点2；head->next为空，即让前一个head节点2断开，后一个head节点2指向空。形成了 **5 -> 4 -> 3 -> 2 -> NULL**

![在这里插入图片描述](https://img-blog.csdnimg.cn/7cf49f0d16934fd988385a749974b106.png)

4. 最后一步也是如此，把节点一连接到按同样的操作连接到链表的末尾。


代码如下：

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head==nullptr || head->next==nullptr)
        {
            return head;
        }
        ListNode* pNew=reverseList(head->next);
        head->next->next=head;
        head->next=nullptr;
        return pNew;
    }
};
```


----

# 链表中移除节点
传送门：
[https://leetcode.cn/problems/remove-nodes-from-linked-list/](https://leetcode.cn/problems/remove-nodes-from-linked-list/)


题目要求：
> 给你一个链表的头节点 head 。
对于列表中的每个节点 node ，如果其右侧存在一个具有 严格更大 值的节点，则移除 node 。
返回修改后链表的头节点 head 。

![在这里插入图片描述](https://img-blog.csdnimg.cn/682e5529655a4e48836b60176cf75267.png)

**这道题利用非递归可以更加有效，非递归的空间复杂度是O(1)，利用非递归可以首先将链表逆转，然后依次遍历每个节点，删除，最后再翻转回来。这里不再多说。**

---

递归过程：

![在这里插入图片描述](https://img-blog.csdnimg.cn/9c6354167dbb4d08a37b975acaeb35ad.png)


----

```cpp
class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        if (head==nullptr || head->next==nullptr)
        {
            return head;
        }
        ListNode* pNew=removeNodes(head->next);
        if (pNew->val>head->val)
        {
            return pNew;
        }
        head->next=pNew;
        return head;
    }
};
```

