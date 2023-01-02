@[toc]


# QSpinBox
允许用户通过单击向上/向下按钮或按键盘上的**上/下**来选择一个值来**增加/减少**当前显示的值。用户还可以手动键入值
常用于处理 选择 ： 【1-99】 【星期1一 - 星期天】【1月-12月】

样式：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2d751655ed774fdba8f3593faa78b490.png)


继承自：
**QAbstractSpinBox**

-----
设置数据范围：

```cpp
spin->setMaximum(7);
spin->setMinimum(1);
//spin->setRange();
```
设置数据循环：即超过了最大值或者低于最小值则循环到另一边

```cpp
spin->setWrapping(true);
```
设置步长：

```cpp
//设置步长
spin->setSingleStep(5);
```

设置**前缀与后缀**

```cpp
spin->setPrefix("周");
spin->setSuffix("天");
```
效果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/dae8682184964fa386a9bf69f8a09fa7.png)

设置特殊文本：当最小值得时候

```cpp
 //最小值特殊文本
spin->setSpecialValueText("到底了");
```
设置**数字数据**得显示格式： 几进制？？

```cpp
//指定显示格式
spin->setDisplayIntegerBase(16);	//十六进制
```

扩展： 用于浮点型小数的调节 ： **QDoubleSpinBox**

-----
如何自定义文本呢？ 
**1：星期一。2：星期二  。。。。 7：星期天**

答案： 重写虚函数：
```cpp
[virtual protected] QString QSpinBox::textFromValue(int value) const
```

textFromValue：接受一个值，可以转换为你想要表示的相对应的QString，例如：星期的转换：

SpinBox重写QSpinBox的textFromValue的方法，注意下面创建对象的时候需要使用我们继承的这个新类：SpinBox，**textFromValue接受值，然后在列表中寻找对应的值，返回转换后的QStirng**
```cpp
class SpinBox:public QSpinBox
{
public:
    SpinBox(QWidget* parent=nullptr)
        :QSpinBox(parent)
    {
        strs<<"一"<<"二"<<"三"<<"四"<<"五"<<"六"<<"日";
    }
    QString textFromValue(int value)const override
    {
        //转换文本: 天数转换为大写
        return strs[(value-1)%7];
    }
private:
    QStringList strs;	//存储转换的文本
};
```
实例：
![在这里插入图片描述](https://img-blog.csdnimg.cn/4e654f91f74a4ac39fb4d4f6a887a690.png)

----


# QDateTimeEdit
作用：

1. 编辑日期和时间的单行文本框
2. 既可以用箭头调节, 也可以用键盘编辑输入
3. 可以单独调节某个部分

样例：
![在这里插入图片描述](https://img-blog.csdnimg.cn/ed67f9760b7e4942948a18337febe439.png)

我们可以自己输入信息，当然也可以进行键盘的调节。

继承自：QAbstractSpinBox


----

构造函数：

可以只创建Date：日期，也可以之创建Time：时间，也可以DateTime都创建，像上图一样。
```cpp
QDateTimeEdit(parent: QWidget = None)
QDateTimeEdit(Union[QDateTime, datetime.datetime], parent: QWidget = None)
QDateTimeEdit(Union[QDate, datetime.date], parent: QWidget = None)
QDateTimeEdit(Union[QTime, datetime.time], parent: QWidget = None)
```
**设置显示格式：**

```cpp
//设置显示格式
date->setDisplayFormat("yyyy年MM月dd日 hh::mm::ss");
```
Section控制

```cpp
 //Section控制
 //选择控制 《天》
date->setCurrentSection(QDateTimeEdit::Section::DaySection);
//打印出当前控制的块的数量，当前的块的信息，文本等
qInfo()<<date->sectionCount()<<date->currentSection()<<date->sectionText(QDateTimeEdit::Section::YearSection);

//API
sectionCount() -> int
	获取section个数
setCurrentSectionIndex(int)
	设置当前的section索引
currentSectionIndex() -> int
	获取section索引
setCurrentSection(QDateTimeEdit.Section)
	设置当前操作的日期时间section
currentSection() -> QDateTimeEdit.Section
	获取当前的section部分
sectionAt(index_int) -> QDateTimeEdit.Section
	获取指定索引位置的section
sectionText(QDateTimeEdit.Section) -> str
	获取指定section的文本内容
```

设置最小和最大的日期时间等

```cpp
setMaximumDateTime(QDateTime)
	默认
		9999年12月31日 23:59:59 999毫秒
maximumDateTime() -> QDateTime
clearMaximumDateTime()
setMinimumDateTime(QDateTime)
minimumDateTime() -> QDateTime
clearMinimumDateTime()
```

显示日历：

```cpp
 //显示日历
date->setCalendarPopup(true);
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/1153af9732f94f09a61abcdd9e92a22b.png)


信号：

**时间日期等改变时触发：**
```cpp
dateTimeChanged(QDateTime datetime)
dateChanged(QDate date)
timeChanged(QTime time)
```


相关子类：
**QDateEdit
QTimeEdit
QDateTime
QDate
QTime**


