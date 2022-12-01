
@[toc]

# 正则表达式
什么是正则表达式？ 
正则表达式(regular expression)描述了一种**字符串匹配**的模式（pattern），可以用来检查一个串**是否含有某种子串**、**将匹配的子串替换**或者从某个串中取出**符合某个条件的子串**等。

> 我们直接从例子入手，如果要规定输入账号，指定账号的长度在5位到11位之间，且不能输入字符等其他字符，只能输入数字，那么你要如何编写C++程序呢？？

c++伪代码：
1. 首先规定长度len，长度大于5位，小于11位，否则重新输入。
2. 然后规定输入数字，如果输入了数字直接重新输入。

regex正则表达式：

```c
void fun()
{
	regex rex{ R"(\d{5,11})" };
	string account;
	smatch sm;
	cout << "请输入账号:";
	while (getline(cin, account))
	{
		if (regex_match(account, sm, rex))
		{
			break;
		}
		cout << "请重新输入:";
	}
	cout << "你的账号是: " << account << endl;
}
```
怎么样，是不是感觉很高端？ 利用正则表达式还可以写出更加高效的代码，我们在等会给大家演示！

---

## 基本语句
首先先让我们来初步认识正则表达式的**基本语句**。
有一篇博客总结的不错，这里我引用以下这个博主所总结的：
[正则表达式](https://blog.csdn.net/wyb880501/article/details/79813658?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166839081616782428632450%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166839081616782428632450&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-79813658-null-null.142%5Ev63%5Econtrol_1,201%5Ev3%5Econtrol_2,213%5Ev2%5Et3_esquery_v2&utm_term=Regex&spm=1018.2226.3001.4187)
<div class="table-box"><table border="1" cellspacing="0"><thead><tr><th style="border-color:#000000;vertical-align:baseline;">字符</th><th style="border-color:#000000;vertical-align:baseline;">描述</th></tr></thead><tbody><tr><td style="border-color:#666666;vertical-align:baseline;">\</td><td style="border-color:#666666;vertical-align:baseline;">将下一个字符标记为一个特殊字符、或一个原义字符、或一个 后向引用、或一个八进制转义符。例如，'n' 匹配字符 "n"。'\n' 匹配一个换行符。序列 ‘\\' 匹配 "\" 而 "\(" 则匹配 "("。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">^</td><td style="border-color:#666666;vertical-align:baseline;">匹配输入字符串的开始位置。如果设置了&nbsp;RegExp&nbsp;对象的&nbsp;Multiline&nbsp;属性，^ 也匹配 ‘\n' 或 ‘\r' 之后的位置。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">$</td><td style="border-color:#666666;vertical-align:baseline;">匹配输入字符串的结束位置。如果设置了RegExp&nbsp;对象的&nbsp;Multiline&nbsp;属性，$ 也匹配 ‘\n' 或 ‘\r' 之前的位置。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">*</td><td style="border-color:#666666;vertical-align:baseline;">匹配前面的子表达式零次或多次。例如，zo* 能匹配 "z" 以及 "zoo"。 * 等价于{0,}。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">+</td><td style="border-color:#666666;vertical-align:baseline;">匹配前面的子表达式一次或多次。例如，'zo+' 能匹配 "zo" 以及 "zoo"，但不能匹配 "z"。+ 等价于 {1,}。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">?</td><td style="border-color:#666666;vertical-align:baseline;">匹配前面的子表达式零次或一次。例如，"do(es)?" 可以匹配 "do" 或 "does" 中的"do" 。? 等价于 {0,1}。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">{n}</td><td style="border-color:#666666;vertical-align:baseline;">n&nbsp;是一个非负整数。匹配确定的&nbsp;n&nbsp;次。例如，'o{2}' 不能匹配 "Bob" 中的 ‘o'，但是能匹配 "food" 中的两个 o。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">{n,}</td><td style="border-color:#666666;vertical-align:baseline;">n&nbsp;是一个非负整数。至少匹配n&nbsp;次。例如，'o{2,}' 不能匹配 "Bob" 中的 ‘o'，但能匹配 "foooood" 中的所有 o。'o{1,}' 等价于 ‘o+'。'o{0,}' 则等价于 ‘o*'。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">{n,m}</td><td style="border-color:#666666;vertical-align:baseline;">m&nbsp;和&nbsp;n&nbsp;均为非负整数，其中n&nbsp;&lt;=&nbsp;m。最少匹配&nbsp;n&nbsp;次且最多匹配&nbsp;m&nbsp;次。刘， "o{1,3}" 将匹配 "fooooood" 中的前三个 o。'o{0,1}' 等价于 ‘o?'。请注意在逗号和两个数之间不能有空格。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">?</td><td style="border-color:#666666;vertical-align:baseline;">当该字符紧跟在任何一个其他限制符 (*, +, ?, {n}, {n,}, {n,m}) 后面时，匹配模式是非贪婪的。非贪婪模式尽可能少的匹配所搜索的字符串，而默认的贪婪模式则尽可能多的匹配所搜索的字符串。例如，对于字符串 "oooo"，'o+?' 将匹配单个 "o"，而 ‘o+' 将匹配所有 ‘o'。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">.</td><td style="border-color:#666666;vertical-align:baseline;">匹配除 "\n" 之外的任何单个字符。要匹配包括 ‘\n' 在内的任何字符，请使用象 ‘[.\n]‘ 的模式。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">(pattern)</td><td style="border-color:#666666;vertical-align:baseline;">匹配pattern&nbsp;并获取这一匹配。所获取的匹配可以从产生的 Matches 集合得到，在VBScript 中使用&nbsp;SubMatches&nbsp;集合，在JScript 中则使用&nbsp;$0…$9&nbsp;属性。要匹配圆括号字符，请使用 ‘<span class="MathJax_Preview" style="color: inherit; display: none;"></span><span class="MathJax" id="MathJax-Element-1-Frame" tabindex="0" style="position: relative;" data-mathml="<math xmlns=&quot;http://www.w3.org/1998/Math/MathML&quot;><mo>&amp;#x2018;</mo><mrow class=&quot;MJX-TeXAtom-ORD&quot;><mo>&amp;#x6216;</mo></mrow><mo>&amp;#x2018;</mo></math>" role="presentation"><nobr aria-hidden="true"><span class="math" id="MathJax-Span-1" style="width: 1.67em; display: inline-block;"><span style="display: inline-block; position: relative; width: 1.372em; height: 0px; font-size: 120%;"><span style="position: absolute; clip: rect(1.253em, 1001.31em, 2.562em, -999.997em); top: -2.199em; left: 0em;"><span class="mrow" id="MathJax-Span-2"><span class="mo" id="MathJax-Span-3" style="font-family: MathJax_Main;">‘</span><span class="texatom" id="MathJax-Span-4"><span class="mrow" id="MathJax-Span-5"><span class="mo" id="MathJax-Span-6"><span style="font-family: STIXGeneral, &quot;Arial Unicode MS&quot;, serif; font-size: 83%; font-style: normal; font-weight: normal;">或</span></span></span></span><span class="mo" id="MathJax-Span-7" style="font-family: MathJax_Main;">‘</span></span><span style="display: inline-block; width: 0px; height: 2.205em;"></span></span></span><span style="display: inline-block; overflow: hidden; vertical-align: -0.282em; border-left: 0px solid; width: 0px; height: 1.361em;"></span></span></nobr><span class="MJX_Assistive_MathML" role="presentation"><math xmlns="http://www.w3.org/1998/Math/MathML"><mo>‘</mo><mrow class="MJX-TeXAtom-ORD"><mo>或</mo></mrow><mo>‘</mo></math></span></span><script type="math/tex" id="MathJax-Element-1">‘ 或 ‘</script>'。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">(?:pattern)</td><td style="border-color:#666666;vertical-align:baseline;">匹配&nbsp;pattern&nbsp;但不获取匹配结果，也就是说这是一个非获取匹配，不进行存储供以后使用。这在使用 "或" 字符 (|) 来组合一个模式的各个部分是很有用。例如， ‘industr(?:y|ies) 就是一个比 ‘industry|industries' 更简略的表达式。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">(?=pattern)</td><td style="border-color:#666666;vertical-align:baseline;">正向预查，在任何匹配&nbsp;pattern&nbsp;的字符串开始处匹配查找字符串。这是一个非获取匹配，也就是说，该匹配不需要获取供以后使用。例如， ‘Windows (?=95|98|NT|2000)' 能匹配 "Windows 2000" 中的 "Windows" ，但不能匹配 "Windows 3.1" 中的 "Windows"。预查不消耗字符，也就是说，在一个匹配发生后，在最后一次匹配之后立即开始下一次匹配的搜索，而不是从包含预查的字符之后开始。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">(?!pattern)</td><td style="border-color:#666666;vertical-align:baseline;">负向预查，在任何不匹配Negative lookahead matches the search string at any point where a string not matching&nbsp;pattern&nbsp;的字符串开始处匹配查找字符串。这是一个非获取匹配，也就是说，该匹配不需要获取供以后使用。例如'Windows (?!95|98|NT|2000)' 能匹配 "Windows 3.1" 中的 "Windows"，但不能匹配 "Windows 2000" 中的 "Windows"。预查不消耗字符，也就是说，在一个匹配发生后，在最后一次匹配之后立即开始下一次匹配的搜索，而不是从包含预查的字符之后开始</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">x|y</td><td style="border-color:#666666;vertical-align:baseline;">匹配&nbsp;x&nbsp;或&nbsp;y。例如，'z|food' 能匹配 "z" 或 "food"。'(z|f)ood' 则匹配 "zood" 或 "food"。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">[xyz]</td><td style="border-color:#666666;vertical-align:baseline;">字符集合。匹配所包含的任意一个字符。例如， ‘[abc]‘ 可以匹配 "plain" 中的 ‘a'。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">[^xyz]</td><td style="border-color:#666666;vertical-align:baseline;">负值字符集合。匹配未包含的任意字符。例如， ‘[^abc]‘ 可以匹配 "plain" 中的'p'。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">[a-z]</td><td style="border-color:#666666;vertical-align:baseline;">字符范围。匹配指定范围内的任意字符。例如，'[a-z]‘ 可以匹配 ‘a' 到 ‘z' 范围内的任意小写字母字符。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">[^a-z]</td><td style="border-color:#666666;vertical-align:baseline;">负值字符范围。匹配任何不在指定范围内的任意字符。例如，'[^a-z]‘ 可以匹配任何不在 ‘a' 到 ‘z' 范围内的任意字符。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\b</td><td style="border-color:#666666;vertical-align:baseline;">匹配一个单词边界，也就是指单词和空格间的位置。例如， ‘er\b' 可以匹配"never" 中的 ‘er'，但不能匹配 "verb" 中的 ‘er'。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\B</td><td style="border-color:#666666;vertical-align:baseline;">匹配非单词边界。'er\B' 能匹配 "verb" 中的 ‘er'，但不能匹配 "never" 中的 ‘er'。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\cx</td><td style="border-color:#666666;vertical-align:baseline;">匹配由x指明的控制字符。例如， \cM 匹配一个 Control-M 或回车符。&nbsp;x&nbsp;的值必须为 A-Z 或 a-z 之一。否则，将 c 视为一个原义的 ‘c' 字符。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\d</td><td style="border-color:#666666;vertical-align:baseline;">匹配一个数字字符。等价于 [0-9]。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\D</td><td style="border-color:#666666;vertical-align:baseline;">匹配一个非数字字符。等价于 [^0-9]。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\f</td><td style="border-color:#666666;vertical-align:baseline;">匹配一个换页符。等价于 \x0c 和 \cL。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\n</td><td style="border-color:#666666;vertical-align:baseline;">匹配一个换行符。等价于 \x0a 和 \cJ。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\r</td><td style="border-color:#666666;vertical-align:baseline;">匹配一个回车符。等价于 \x0d 和 \cM。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\s</td><td style="border-color:#666666;vertical-align:baseline;">匹配任何空白字符，包括空格、制表符、换页符等等。等价于 [ \f\n\r\t\v]。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\S</td><td style="border-color:#666666;vertical-align:baseline;">匹配任何非空白字符。等价于 [^ \f\n\r\t\v]。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\t</td><td style="border-color:#666666;vertical-align:baseline;">匹配一个制表符。等价于 \x09 和 \cI。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\v</td><td style="border-color:#666666;vertical-align:baseline;">匹配一个垂直制表符。等价于 \x0b 和 \cK。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\w</td><td style="border-color:#666666;vertical-align:baseline;">匹配包括下划线的任何单词字符。等价于'[A-Za-z0-9_]‘。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\W</td><td style="border-color:#666666;vertical-align:baseline;">匹配任何非单词字符。等价于 ‘[^A-Za-z0-9_]‘。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\xn</td><td style="border-color:#666666;vertical-align:baseline;">匹配&nbsp;n，其中&nbsp;n&nbsp;为十六进制转义值。十六进制转义值必须为确定的两个数字长。例如， ‘\x41′ 匹配 "A"。'\x041′ 则等价于 ‘\x04′ &amp; "1"。正则表达式中可以使用 ASCII 编码。.</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\num</td><td style="border-color:#666666;vertical-align:baseline;">匹配&nbsp;num，其中&nbsp;num&nbsp;是一个正整数。对所获取的匹配的引用。例如，'(.)\1′ 匹配两个连续的相同字符。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\n</td><td style="border-color:#666666;vertical-align:baseline;">标识一个八进制转义值或一个后向引用。如果 \n&nbsp;之前至少&nbsp;n&nbsp;个获取的子表达式，则&nbsp;n&nbsp;为后向引用。否则，如果&nbsp;n&nbsp;为八进制数字 (0-7)，则&nbsp;n&nbsp;为一个八进制转义值。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\nm</td><td style="border-color:#666666;vertical-align:baseline;">标识一个八进制转义值或一个后向引用。如果 \nm&nbsp;之前至少有is preceded by at least&nbsp;nm&nbsp;个获取得子表达式，则&nbsp;nm&nbsp;为后向引用。如果 \nm&nbsp;之前至少有&nbsp;n&nbsp;个获取，则&nbsp;n&nbsp;为一个后跟文字&nbsp;m&nbsp;的后向引用。如果前面的条件都不满足，若&nbsp;n&nbsp;和&nbsp;m均为八进制数字 (0-7)，则 \nm&nbsp;将匹配八进制转义值&nbsp;nm。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\nml</td><td style="border-color:#666666;vertical-align:baseline;">如果&nbsp;n&nbsp;为八进制数字 (0-3)，且&nbsp;m&nbsp;和&nbsp;l&nbsp;均为八进制数字 (0-7)，则匹配八进制转义值&nbsp;nml。</td></tr><tr><td style="border-color:#666666;vertical-align:baseline;">\un</td><td style="border-color:#666666;vertical-align:baseline;">匹配&nbsp;n，其中&nbsp;n&nbsp;是一个用四个十六进制数字表示的 Unicode 字符。例如， \u00A9 匹配版权符号 (?)。</td></tr></tbody></table></div>

## regex_match 
regex_match可以**精准的匹配**正则表达式与字符串。


接受参数： 
```c
s − 它是一个带有目标序列的字符串。
rgx − 它是要匹配的 basic_regex 对象。
flags − 用于控制 rgx 的匹配方式。
m − 它是 match_results 类型的对象。
```

返回值：
如果 rgx 与目标序列匹配，则返回 true。 否则为 false 。


*  .* ： . 表示输入任意一个字符，* 表示输入任意多个，即在<>的范围内输入任意多个字符
```c
regex myReg1{ "<.*>" };
bool ret1 = regex_match("<1234asd89>", myReg1);
assert(ret1);	//正确
```
* 一个比较上一个较复杂的例子：第一个<>内输入任意多个字符，然后在外面在接受任意多个字符，之后在最后一个<>内指定输入一个**数字**（使用转义字符转换为\d）
```c
regex myReg2{ "<.*>.*<(\\d)>" };
bool ret2 = regex_match("<woaini>abc<5>", myReg2);
assert(ret2);	//正确
```

* regex_match的另一种版本：

```c
cmatch m;	//一个接受匹配后字符串的类，存储匹配后的字符串
auto ret = regex_match("<woaini>666</xml>", m, regex{ "<(.*)>(.*)</(.*)>" });
if (ret)
{
	cout << m.str() << endl;
	cout << m.length() << endl;
	cout << m.position() << endl;
}
```
通过cmatch接受const char*类型的字符串，当然通过smatch也可以接受string类型的字符串。我们可以调用它所拥有的方法，比如得到这个字符串：str()，得到长度: length()，得到某个子匹配项在整个大的匹配项中所处的位置。

*	 `三种方法`得到匹配后的字符串：

```c
for (int i = 0	; i < m.size(); i++)
{
	cout << m[i].str() << " " << m.str(i) << endl;
}
cout << " -----------------------" << endl;
for (auto it = m.begin(); it != m.end(); it++)
{
	cout << *it << endl;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/354fb89fd106454bba3e24f9d81c2823.png)

----

## regex_search
搜索：整个字符序列中，是否有部分（或整体）符合匹配模式。

他接受的参数和返回值与regex_match一致。


在s中我们的字符序列在尾部多了一个end，显然与对应的匹配模式不符合，但是search和match不同的是，它只要有部分包含，则就是成功，返回正确匹配的一部分序列。

注意：在字符串前面加 R 表示原生 字符串 ，是防止 转义，否则你就要使用两个 \\ 来表示转义。
* \d：表示接受一个数字。
* {3}：表示接受3个数字，与前面合起来则表示：接受  3个数字。
* [0-9]：表示接受任意一个数字，与 \d一个意思
* \* 表示接受任意多字符，则表示接受 任意多个数字。
```c
void f3()
{
	//regex_search: 字符串s的格式 在regex中匹配一部分，则返回匹配的部分内容，不必完全匹配
	//string s{ "123456<ylh><qq>: <1173012900>654321" };
	string s{ "<ylh>666<1173012900>  end" };
	smatch sm;
	auto ret = regex_search(s, sm, regex{ R"(<(.*)>\d{3}<[0-9]*>)" });
	if (ret)
	{
		//cout << sm.str() << endl;
		for (auto& x : sm)
		{
			cout << x << endl;
		}
		cout << sm.prefix() << endl;	//返回前部分不匹配的
		cout << sm.suffix() << endl;	//返回后部分不匹配的
	}
}
```
smatch存储了匹配的部分字符序列，\<ylh>666<1173012900>，因此可以得到其前缀：prefix()，得到其后缀：suffix()  ，这里的前缀与后缀都是指相对于**匹配的这一部分**前面的不匹配部分和后面不匹配部分。


## regex_token_iterator
使用分词迭代器给字符序列分组：
```c
void f5()
{
	//模板类regex_token_iterator<>提供分词迭代器
	string s{ "1173012900@qq.com,123456789@vip666.com,656dawda@163.cmo" };
	regex rex{ "," };
	sregex_token_iterator pos{ s.begin(),s.end(),rex,-1 };
	decltype(pos) end;
	for (; pos != end; ++pos)
	{
		cout << pos->str() << endl;
	}
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/5be75cb776a8490fbbf7caa3d26f7c39.png)
## regex_replace
替换指定的字符

```c
void f6()
{
	string s{ "he....llo. .w..orl...d" };
	regex rex{ "\\." };
	cout << regex_replace(s, rex, "");
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/7341d0d022ca4ed5bb9cfeea206e5184.png)
## 示例
### 匹配电话号码
* 电话号码的位数为 11位，第一位一定是1 
* 第一位：1 
* 后10位：\d{10} 或者 [0-9]{10} 都可以
* ^ 表示序列的开始  $表示序列的结束
```c
void exp1()
{
	string s;
	regex reg{ "^1[0-9]{10}$" };	// "^1\d{10}$"
	smatch sm;
	cout << "输入你的电话号码: ";
	while (getline(cin, s))
	{
		if (regex_match(s,sm, reg))
		{
			break;
		}
		cout << "输入格式错误，请重新输入:";
	}
	cout << "您的电话号码是: " << s << endl;
}
```
### 匹配QQ号码
QQ号码的位数可以是5位到11位：

* 第一位：[1-9]  或者 \d
* 后四位到后十位：[0-9]{4,10}

```c
//匹配qq号码
void exp2()
{
	string s;
	regex reg{ "[1-9]\\d{4,10}" };	//5位或者11位 第一位不为0
	smatch sm;
	cout << "输入你的qq号码: ";
	while (getline(cin, s))
	{
		if (regex_match(s, sm, reg))
		{
			break;
		}
		cout << "输入格式错误，请重新输入:";
	}
	cout << "您的qq号码是: " << s << endl;
}
```

### 匹配IP地址
IP地址可以有四个数字部分和三个 .  部分如： 127.125.56.254

注意：它的每一位都是 0 - 255的数字，你可能以为 直接 \\d{1,3} 输入三位不就好了？但是别忘了不能超过 255最大数字；你可能还会想通过 [0-5]{1,3}不就好了，但是你别忘了只是超过200之后不能超过255，没说小于200的不能超过255，因此，通过简单的表达式无法求出ip地址的匹配，我们可以通过下面的几种情况分类讨论：

1.  第一组：  0 - 9
2.  第二组：  10 - 99
3.  第三组：  100 - 199
4.  第四组：   200 - 249
5.  第五组：   250 - 255

* 通过或把每一种可能性连接起来，表示这五组只要有一组成立就可以，并且用（）把这一个统一的括起来，表示ip地址的第一个数字部分：

```c
([0-9]|[1-9][0-9]|1\\d{2}|2[0-4][0-9]|25[0-5])
```
* 前三个数字部分后面都带一个点分隔符，直接重复三次，并且使用 ?:  来匹配各个组的统一模式

```c
(?:(?:[0-9]|[1-9][0-9]|1\\d{2}|2[0-4][0-9]|25[0-5])\\.){3}
```
* 最后一个数字后面没有点，因此单独写一条：别忘了加上 ^与$
```c
^(?:(?:[0-9]|[1-9][0-9]|1\\d{2}|2[0-4][0-9]|25[0-5])\\.){3}(?:[0-9]|[1-9][0-9]|1\\d{2}|2[0-4][0-9]|25[0-5])$ 
```

```c
//匹配ip地址
void exp3()
{
	string s;
	//忽略子匹配内容字符： ?:
	regex reg{ "^(?:(?:[0-9]|[1-9][0-9]|1\\d{2}|2[0-4][0-9]|25[0-5])\\.){3}(?:[0-9]|[1-9][0-9]|1\\d{2}|2[0-4][0-9]|25[0-5])$" };
	smatch sm;
	cout << "输入你的ip号码: ";
	while (getline(cin, s))
	{
		if (regex_match(s, sm, reg))
		{
			break;
		}
		cout << "输入格式错误，请重新输入:";
	}
	cout << "您的ip号码是: " << s << endl;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/f7ad79fa8514467da1a31aaf8b0214b2.png)

