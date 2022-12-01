
@[toc]

> 本篇主要总结关于滑动窗口的相关做题技巧与注意事项，有关滑动窗口是什么请参阅其他文章，本篇主要用于在了解滑动窗口的构造后，快速掌握滑动窗口的做题技巧与做题模板，便于以后复习参阅。
# 滑动窗口模板
1. `定义变量`：确定需要**维护的变量**：**数之和，最大最小长度，哈希表等**
2. `滑动窗口`：确定滑动窗口的左右边界，开始滑动窗口
3. `合法更新`：**在滑动窗口有效的情况下，合法的更新需要维护的变量**
4. `非法更新`（二次更新）：**在滑动窗口无效或者即将无效的情况下，更新维护的变量，并且收缩滑动窗口的左边界**，非法更新的两种情况：
* 滑动窗口的长度是`固定`的！！！  使用 `if条件`来更新
* 滑动窗口的长度是`可变`的！！！  使用 `while条件`来更新
5. `返回与得到答案`
----

```cpp
int func(vector<int>& nums,int k)
{
	//Step1. 定义维护变量：
	1. unordered_map<char,int> m;	//在需要统计字符或者数字出现的次数的时候，使用哈希表
	2. int sum=0,res=0;			//在需要记录整数数组中的子序列和或者其他求和时，使用sum记录每一次滑动窗口的子和，再利用res得到最大的或者最小的结果	
	3. int len=0,start=0;		//得到字符串的字串，len记录字串长度，start标识字串开始位置

	//Step2. 确定滑动窗口的边界，开始滑动：
	int left=0,right=0;
	while (right< n) 	// n: 数组长度	
	{
		//Step3. 合法更新：每进行一次滑动时，必须要更新的变量：如Step1的哈希表，sum,res,len与start等等
		......
		if (满足条件) //满足某一种条件：例如滑动窗口的长度：right-left+1 与某个值相等时，则进行一次判断，保存临时结果
		{
			//更新：res=max(res,sum)  ......
		}
		//Step4: 非法更新
		//(1): 滑动窗口的长度固定：使用if来更新窗口
		while (right-left+1 > m.size())//举个例子：无重复字符的最长字串，你的窗口长度大于哈希表的长度，则一定含有重复元素，因此更新左边界，使用if
		{
			.....
		}
		//(2)： 滑动窗口的长度不固定，使用while来更新窗口	
		if (right>=k-1)//举个例子：子数组的最大平均值，子数组规定长度不能超过k，因此滑窗长度固定
		{
			.....
		}
		right++;//此处可以改为for循环
	}
	return res;//Step5: 返回结果
}
```


# 经典例题

## 3. 无重复字符的最长字串
传送门：
[https://leetcode.cn/problems/longest-substring-without-repeating-characters/](https://leetcode.cn/problems/longest-substring-without-repeating-characters/)

Step4： 滑动窗口不具有固定长度，所以使用**while循环**来更新滑动窗口
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        //1. 确定维护变量：存储字符个数的哈希表
        unordered_map<char,int> m;
        int max_len=0;
        //2. 定义滑动窗口的边界，开始滑动窗口
        int n=s.size();
        int left=0,right=0;
        while (right<n)
        {
            //3. 合法更新：哈希表存储字符的更新，字符放到哈希表中
            m[s[right]]++;
            if (right-left+1==m.size())
            {
                max_len=max(max_len,right-left+1);
            }
            //4. 非法更新：窗口的长度小于哈希表的长度
            //想象一下：哈希表存储每个字符，如果遇到相同的字符则长度不变，但是窗口的长度会变，因此就造成了窗口里有重复的单词，非法了，需要更新窗口的左边界，必要时删除此字符
            while (right-left+1>m.size())
            {
                m[s[left]]--;
                if (m[s[left]]==0)
                {
                    m.erase(s[left]);
                }
                left++;
            }
            right++;
        }
        //5. 返回结果
        return max_len;
    }
};
```



---


## 643. 子数组最大平均数 I
传送门：
[https://leetcode.cn/problems/maximum-average-subarray-i/](https://leetcode.cn/problems/maximum-average-subarray-i/)


Step4：滑动窗口的长度固定：为k  ，使用 **if条件**来更新滑动窗口

```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        //1. 定义维护变量
        int sum=0;
        int res=INT_MIN;
        //2. 确定滑动窗口的左右边界，开始滑动窗口
        int left=0,right=0;
        int n=nums.size();
        while (right<n)
        {
            //3. 合法更新：滑动每一步，只要滑动的长度等于k，则记录一下此时的sum值
            sum+=nums[right];
            if (right-left+1==k)
            {
                res=max(res,sum);
            }
            //4. 非法更新：滑动窗口的长度固定，使用if来更新，
            if (right>=k-1)
            {
                sum-=nums[left];
                left++;
            }
            right++;
        }
        return static_cast<double>(res)/k;
    }
};
```

----

## 159. 至多包含两个不同字符的最长子串
传送门：
[https://leetcode-cn.com/problems/longest-substring-with-at-most-two-distinct-characters/](https://leetcode-cn.com/problems/longest-substring-with-at-most-two-distinct-characters/)

Step4：滑动窗口**长度不固定**： 使用 **while循环**来更新滑动窗口
```cpp
//至多包含两个不同字符的最长字串
class Solution_159 {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		//1. 定义维护变量
		unordered_map<char, int> m;
		int len = 0;

		//2. 确定窗口的左右边界，开始滑动窗口
		int left = 0, right = 0;
		int n = s.size();
		while (right < n)
		{
			//3. 合法更新：滑动过程中map存储每一个字符
			m[s[right]]++;
			if (m.size() <= 2)
			{
				len = max(len, right - left + 1);
			}
			//4. 非法更新：最多存储两个不同的字符，但是对于每种字符的存储数量没有限制，因此可以存储很多很多，但是不能超过两种，所以滑动窗口的长度不固定 使用while来更新滑动窗口
			// 哈希表的长度大于3，则至少出现了3种不同的字符，因此窗口不合法， 需要更新
			while (m.size() > 2)	// right >= k-1
			{
				m[s[left]]--;
				if (m[s[left]] == 0)
				{
					m.erase(s[left]);
				}
				left++;
			}
			right++;
		}
		return len;
	}
};

```

---
## 209. 长度最小的子数组
传送门： 
[https://leetcode.cn/problems/minimum-size-subarray-sum/](https://leetcode.cn/problems/minimum-size-subarray-sum/)

Step4：滑动窗口**长度不固定**： 使用 **while循环**来更新滑动窗口
```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum=0;
        int len=INT_MAX;
        int left=0,right=0;
        int n=nums.size();
        while (right<n)
        {
        	//3. 合法更新，窗口滑动一下，把这个数字想加，计算之和
            sum+=nums[right];
            //4. 非法更新（二次更新）：当sum满足条件时，试探是否有更好的办法可以实现，即缩小窗口，有没有长度更小的子数组满足>=target
            while (sum>=target)
            {
                len=min(len,right-left+1);
                sum-=nums[left];
                left++;
            }
            right++;
        }
        return (len==INT_MAX)?0:len;
    }
};
```

---
## 1695. 删除子数组的最大得分
传送门：
[https://leetcode.cn/problems/maximum-erasure-value/](https://leetcode.cn/problems/maximum-erasure-value/)


Step4：滑动窗口**长度不固定**： 使用 **while循环**来更新滑动窗口
```cpp
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        unordered_map<int,int> m;
        int sum=0;
        int res=0;
        int left=0,right=0;
        int n=nums.size();
        while (right<n)
        {
            //3. 合法更新： sum每次相加,并且记录当前字符的种类，如果字符种类等于滑动窗口的长度，则滑动窗口出现的字符种类都等于哈希表里存储的种类，满足条件，相加，保存结果
            m[nums[right]]++;
            sum+=nums[right];
            if (right-left+1==m.size())
            {
                res=max(res,sum);
            }
            //4. 非法更新： 滑动窗口长度大于哈希表的长度
            //说明滑动窗口里有重复元素出现，则左边界收缩，哈希表删除左边界元素，进行窗口的更新
            while (right-left+1>m.size())
            {
                sum-=nums[left];
                m[nums[left]]--;
                if (m[nums[left]]==0)
                {
                    m.erase(nums[left]);
                }
                left++;
            }
            right++;
        }
        return res;
    }
};
```

---
## 438. 找到字符串中所有字母异位词
传送门：
[https://leetcode.cn/problems/find-all-anagrams-in-a-string/](https://leetcode.cn/problems/find-all-anagrams-in-a-string/)

Step4：滑动窗口长度固定： 使用 **if条件**来更新滑动窗口
```cpp
class Solution {
private:
    unordered_map<char,int> m_s;
    unordered_map<char,int> m_p;
public:
    vector<int> findAnagrams(string s, string p) {
        for (auto& x:p)
        {
            m_p[x]++;
        }
        int left=0,right=0;
        int n1=s.size();
        int n2=p.size();

        vector<int> vec;
        while (right<n1)
        {
        	//3. 合法更新： 窗口滑动，字符存储入哈希表
            m_s[s[right]]++;
            //当哈希表的元素存储和目标p完全一致。则left起始下标就是一个目标下标
            if (m_s == m_p)
            {
                vec.push_back(left);
            }
            //4. 非法更新：滑动窗口有固定长度，长度为p的长度，因此使用if条件来维护
            if (right>=n2-1)
            {
                m_s[s[left]]--;
                if (m_s[s[left]]==0)
                {
                    m_s.erase(s[left]);
                }
                left++;
            }
            right++;
        }
        return vec;
    }
};
```


---

## 567. 字符串的排列
传送门：
[https://leetcode.cn/problems/permutation-in-string/description/](https://leetcode.cn/problems/permutation-in-string/description/)

Step4：滑动窗口长度固定： 使用 **if条件**来更新滑动窗口
```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char,int> m_s1;
        unordered_map<char,int> cnt;   
        for (auto& x:s1)
        {
            m_s1[x]++;
        }
        int left=0,right=0;
        int n1=s1.size();
        int n2=s2.size();
        while (right<n2)
        {
        	//3. 合法更新：存储字符串到哈希表中，然后与目标哈希表存储元素进行比较
            cnt[s2[right]]++;
            if (cnt==m_s1)
            {
                return true;
            }
            //4. 非法更新：滑动窗口长度固定，更新维护变量，缩短左边界
            if (right>=n1-1)
            {
                cnt[s2[left]]--;
                if (cnt[s2[left]]==0)
                {
                    cnt.erase(s2[left]);
                }
                left++;
            }
            right++;
        }
        return false;
    }
};
```

## 76.最小覆盖子串
1. m_t哈希表存储要覆盖的字符串t的字符
2. m_s存储滑动窗口每次滑动时添加的字符及次数
3. 判断m_s是否含有m_t，即s字符串包含t字符串，如果它包含，那么进行接下来的二次更新
4. 二次更新：左边界left右移，m_s哈希表存储的这个left字符计数减一，为0时则直接删除，进而达到缩小窗口的目的。同时，每缩小一次，我们记录此时的长度len和开始位置start，我们的len要取得每次的最小值，则len就是最小覆盖子串的长度，start就是其起始下标。

注意：**最小覆盖字串的长度是不固定**的，因此，Step4： 我们要使用while循环来更新滑动窗口。

```cpp
class Solution {
private:
	unordered_map<char, int> m_s;
	unordered_map<char, int> m_t;
public:
	bool check()
	{
		for (auto& x : m_t)
		{
			if (m_s[x.first] < x.second)
			{
				return false;
			}
		}
		return true;
	}
	string minWindow(string s, string t) {
		//1. 确定维护的变量，是一个哈希表，存储t中的字符
		for (auto& x : t)
		{
			m_t[x]++;
		}
		string res;
		int len = INT_MAX;      //记录字符串长度
		int start = -1;         //目标字符串序列位置
		//2. 定义滑动窗口边界，开始滑动窗口
		int left = 0, right = 0;
		int n = s.size();
		while (right < n)
		{
			//3. 合法更新：滑动窗口每移动一次，字符就放进哈希表中
			m_s[s[right]]++;
			//4. 非法更新:无固定长度，使用while循环，每次使得t串能够包含于s串中
			//并且要尽量让s串取到《最小包含》，因此每次都更新左边界，试探是否有最小的包含，并且更新滑动窗口
			while (check() && left <= right)
			{
				if (right - left + 1 <= len)
				{
					len = right - left + 1;
					start = left;
				}
				m_s[s[left]]--;
				if (m_s[s[left]] == 0)
				{
					m_s.erase(s[left]);
				}
				left++;
			}
			right++;
		}
		//5. 返回结果
		return (start == -1) ? "" : s.substr(start, len);
	}
};
```



