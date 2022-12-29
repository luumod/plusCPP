@[toc]

# QLineEdit
QLineEdit是最基本的输入控件，继承自QObject ，常用于短行的输入。

构造函数：

可以指定一个默认文本以及父窗口
```cpp
 QLineEdit(const QString &contents, QWidget *parent = nullptr)
 QLineEdit(QWidget *parent = nullptr)
```

基本功能函数:

```cpp
void Widget::testQLineEdit()
{
    //创建行编辑框
    edit=new QLineEdit("我是编辑框",this);

    //设置文本
    edit->setText("edit");
    qInfo()<<edit->text();

    //清空文本
    edit->clear();

    //设置显示文本
    edit->setEchoMode(QLineEdit::EchoMode::Normal);

    //表面上是什么，实际就输出什么
    edit->displayText();

    //设置提示文本
    edit->setPlaceholderText("手机号/QQ/邮箱");

    //设置清空按钮
    edit->setClearButtonEnabled(true);

    //设置图标行为
    edit->addAction(QIcon("cha.png"),QLineEdit::ActionPosition::TrailingPosition);

    //设置自动补全
    QStringList compstr;
    compstr<<"123456"<<"zhangsan"<<"111122233";
    QCompleter* comp=new QCompleter(compstr,this);
    edit->setCompleter(comp);

    //限制输入长度
    edit->setMaxLength(5);

    //设置只读
    edit->setReadOnly(true);

    //设置验证器（用于输入验证）
    QIntValidator* valdator=new QIntValidator(0,100,this);
    edit->setValidator(valdator);

    //设置格式输入（输入按指定格式的文本）
    edit->setInputMask("AAAA-AAAA-AAAA-AAAA");

    edit->setText("123456789");

    //信号：textEdited文本编辑时触发
    //connect(edit,&QLineEdit::textEdited,this,[](const QString& str){qInfo()<<str;});

    //textChanged文本改变时触发，包括settext
    //connect(edit,&QLineEdit::textChanged,this,[](const QString& str){qInfo()<<str;});

    //回车触发
    connect(edit,&QLineEdit::returnPressed,this,[=](){qInfo()<<edit->text();});

    //编辑完成时触发
    //光标位置发生变化时
    //选择改变时
    connect(edit,&QLineEdit::selectionChanged,this,[=](){qInfo()<<edit->selectedText();});
}
```

---

信号：

```cpp
 void cursorPositionChanged(int oldPos, int newPos) 光标位置改变
 void editingFinished()	编辑完成的时候
 void inputRejected()	输入完成的时候
 void returnPressed()	输入回车的时候
 void selectionChanged() 选择改变的时候
 void textChanged(const QString &text)	文本改变的时候（包括settext）
 void textEdited(const QString &text) 	文本编辑的时候（只包括手动的编辑修改）
```

信号测试：
```cpp
//信号：textEdited文本编辑时触发
connect(edit,&QLineEdit::textEdited,this,[](const QString& str){qInfo()<<str;});

 //textChanged文本改变时触发，包括settext
 connect(edit,&QLineEdit::textChanged,this,[](const QString& str){qInfo()<<str;});

 //回车触发
 connect(edit,&QLineEdit::returnPressed,this,[=](){qInfo()<<edit->text();});

 //编辑完成时触发
 //光标位置发生变化时
 //选择改变时
 connect(edit,&QLineEdit::selectionChanged,this,[=](){qInfo()<<edit->selectedText();});
```

# QTextEdit
QTextEdit常用于一段话的输入，常用于长文本，继承自滑块类QAbstractScrollArea，因此他是一个具有滑动条的长文本编辑框。

构造函数：

```cpp
 QTextEdit(const QString &text, QWidget *parent = nullptr)
 QTextEdit(QWidget *parent = nullptr)
```

QTextEdit不仅像QLineEdit支持普通文本的输入，还支持Html，markdown等文本的输入。

多种格式的输入：

```cpp
//设置普通文本
tedit->setPlaceholderText("请输入你的简介");
//设置HTML
tedit->setHtml("<h1>999999daw,666</h1>");
//插入一个Html
tedit->insertHtml("我爱你");
//设置MarkDown
tedit->setMarkdown("# 一级标题\n - 选项一\n - 选项二");
```

文本的获取：
```cpp
//输出普通文本
qInfo()<<tedit->toPlainText();
//输出Html型文本
qInfo()<<tedit->toHtml();
//输出MarkDown型文本
qInfo()<<tedit->toMarkdown();
```





## QTextCursor
QTextCursor提供了由简单到复杂的对文本的插入操作，简单来说，你可以通过QTextCursor来插入东西到QTextEdit文本框中。

首先获取文本光标：任何插入都是基于光标的

```cpp
QTextEdit* tedit=new QTextEdit(this);
QTextCursor cursor=tedit->textCursor();
```

支持的插入操作的类包括：
**QTextFormat
QTextBlockFormat
QTextCharFormat：QTextImageFormat ；QTextTableCellFormat
QTextFrameFormat：QTextTableFormat
QTextListFormat**

----

**插入普通文本：**

```cpp
cursor.insertText("Hello World");
```

**插入带格式的复杂文本：（设置文本的格式）**
QTextCharFormat ：文本格式设置类，用它可以对文本的格式化进行设置，它里面包含了许多对文本格式的set，例如setFontUnderline设置下划线，setBackground设置背景颜色。。。setfont设置格式。。
```cpp
//设置文本的格式
QTextCharFormat tcf;
tcf.setAnchor(Qt::red);
tcf.setFontUnderline(Qt::blue);
tcf.setBackground(QBrush(Qt::yellow));
cursor.insertText("666",tcf);
```

**插入图片，设置图片的格式**
QTextImageFormat ：图片格式设置类。

```cpp
//插入图片，设置图片格式
QTextImageFormat tif;
tif.setName("cha.png");
cursor.insertImage(tif,QTextFrameFormat::Position::InFlow);
```
**插入一段话（文档内容）**
QTextDocumentFragment：类

```cpp
cursor.insertFragment(QTextDocumentFragment::fromHtml("<a href='https://www.baidu.com'>百度一下</a>"));
```

**插入列表**
QTextListFormat 列表类
```cpp
//插入列表   
QTextListFormat tlf;
cursor.insertList(tlf);

//列表的设置
QTextCursor tcur=tedit->textCursor();
QTextListFormat tlf;
tlf.setNumberPrefix("<");
tlf.setNumberSuffix(">");
tlf.setStyle(QTextListFormat::ListDecimal);
tcur.insertList(tlf);
```
**插入表格**
QTextTableFormat 类
```cpp
//插入表格
QTextTableFormat ttf;
ttf.setCellPadding(10);
//ttf.setBackground(Qt::blue);
cursor.insertTable(3,4,ttf);
```

