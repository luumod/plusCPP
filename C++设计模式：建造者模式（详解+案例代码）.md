@[toc]

# 建造者模式

建造者模式是一种对象创建型模式之一，用来隐藏复合对象的创建过程，它把复合对象的创建过程加以抽象，通过子类继承和重载的方式，动态地创建具有复合属性的对象。官方说法就是**将一个复杂对象的构造与它的表示分离，使同样的构建过程可以创建不同的表示。**


主要解决在软件系统中，有时候面临着"一个复杂对象"的创建工作，其通常由各个部分的子对象用一定的算法构成；由于需求的变化，这个复杂对象的各个部分经常面临着剧烈的变化，但是将它们组合在一起的算法却相对稳定。

## 实现步骤

1. 提供**抽象建造者类**: 为创建产品各个部分，统一抽象接口
2. 提供**具体建造者类**：具体实现抽象建造者各个部件的接口
3. （可选）提供**抽象产品类**：为产品提供统一接口
3. 提供多个**具体产品类**:实现抽象产品类的接口。
4. （重要）提供一个**指挥类**：负责安排和调度复杂对象的各个建造过程


![请添加图片描述](https://img-blog.csdnimg.cn/bc9b77a650aa4abd8b9e045a9c0d75de.png)

## 实现代码
### 案例一： 组装电脑
1. 抽象产品类：AbstractProduct，把电脑的各个组成部件抽象为一个统一的接口
2. 具体产品类：Computer，电脑产品
3. 抽象建造类：AbstractBuilder：创建电脑的各个部分，提供统一接口
4. 具体建造类：ComputerBuilder：电脑建造者，负责实现抽象建造者的接口。
5. 指挥类：Director： 相当于一个指挥者，指挥电脑建造者构造电脑。
```cpp
/*
建造者模式
组装电脑：显示器  主机  键盘  鼠标
*/

/*
1. 抽象产品类
*/
class AbstractProduct
{
public:
	virtual ~AbstractProduct() {}
	virtual void setDisplay(string display) = 0;
	virtual void setHost(string host) = 0;
	virtual void setKeyBoard(string KeyBoard) = 0;
	virtual void setMouse(string mouse) = 0;
	virtual void show() = 0;
};

/*
2. 具体产品类
*/
class Computer:public AbstractProduct
{
public:
	~Computer() {}
	void setDisplay(string display)
	{
		m_vec.emplace_back(display);
	}
	void setHost(string host)
	{
		m_vec.emplace_back(host);
	}
	void setKeyBoard(string KeyBoard)
	{
		m_vec.emplace_back(KeyBoard);
	}
	void setMouse(string mouse)
	{
		m_vec.emplace_back(mouse);
	}
	void show()
	{
		cout << "----------组装电脑---------" << endl;
		for (auto& x : m_vec)
		{
			cout << x << endl;
		}
	}
private:
	vector<string> m_vec;
};

/*
3. 抽象建造者
*/
class AbstractBuilder
{
public:
	//创建电脑产品
	AbstractBuilder()
		:product(new Computer) {}
	virtual ~AbstractBuilder() {}
	//抽象电脑产品创建的统一抽象接口
	virtual void BuildDisplay(string display) = 0;
	virtual void BuildHost(string host) = 0;
	virtual void BuildKeyBoard(string KeyBoard) = 0;
	virtual void BuildMouse(string mouse) = 0;
	AbstractProduct* getProduct()
	{
		return product;
	}
protected:
	AbstractProduct* product;
};

/*
4. 具体建造者：具体实现抽象建造者各个部件的接口
*/
class ComputerBuilder :public AbstractBuilder
{
public:
	~ComputerBuilder() {}
	void BuildDisplay(string display)
	{
		product->setDisplay(display);
	}
	void BuildHost(string host)
	{
		product->setHost(host);
	}
	void BuildKeyBoard(string KeyBoard)
	{
		product->setKeyBoard(KeyBoard);
	}
	void BuildMouse(string mouse)
	{
		product->setMouse(mouse);
	}
};

/*
5. 指挥者：安排和调度复杂对象的创建过程
*/
class Director
{
public:
	Director(AbstractBuilder* builder)
		:m_builder(builder) {}
	~Director() {}
	AbstractProduct* createComputer(string display, string host, string KeyBoard, string mouse)
	{
		m_builder->BuildDisplay(display);
		m_builder->BuildHost(host);
		m_builder->BuildKeyBoard(KeyBoard);
		m_builder->BuildMouse(mouse);
		return m_builder->getProduct();
	}
private:
	AbstractBuilder* m_builder;
};
int main()
{
	//1. 创建电脑建造者
	AbstractBuilder* Computer_Builder = new ComputerBuilder;
	//2. 创建电脑建造者的 管理者
	Director* pDcomp = new Director{ Computer_Builder };
	//3. 管理者指挥 建造者制造电脑产品
	AbstractProduct* computerPro = pDcomp->createComputer("联想显示器", "外星人主机", "雷蛇键盘", "罗技鼠标");
	//4. 电脑产品制造完成
	computerPro->show();

	//别忘了释放内存
	delete Computer_Builder;
	delete pDcomp;
	delete computerPro;

	return 0;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/e9a02c2910714a3197c3e2abaa2a9893.png)

---

### 案例二：汉堡店点餐
1. 抽象产品类： AbstractFood
2. 具体产品类：Food
3. 抽象建造者：AbstractBuilder
4. （套餐A）**具体建造者A**：Meal_1 
5. （套餐B）**具体建造者B**：Meal_2
6.  指挥者：Director ：**负责上菜**

```cpp
/*
点餐：

1. 香辣鸡肉汉堡 + 薯条 + 可乐
2. 墨西哥鸡肉卷 + 鸡块 + 芬达 
*/

//1. 抽象产品类
class AbstractFood
{
public:
	virtual ~AbstractFood() {}
	virtual void add(string foodname, int price) = 0;
	virtual void show() = 0;
};

//2. 具体产品类
class Food:public AbstractFood
{
public:
	virtual ~Food() {}
	void add(string foodname, int price)
	{
		m_vec.emplace_back(make_pair(foodname, price));
	}
	void show()
	{
		int sum = 0;
		for (int i = 0; i < m_vec.size(); i++)
		{
			sum += m_vec[i].second;
			cout << m_vec[i].first <<": "<< m_vec[i].second<<"元" << endl;
		}
		cout << "总计: " << sum << "元" << endl;
	}
private:
	vector<pair<string,int>> m_vec;
};

//3. 抽象建造者
class AbstractBuilder
{
public:
	AbstractBuilder()
		:food(new Food) {}
	virtual ~AbstractBuilder() {}
	virtual void BuildFood1() = 0;
	virtual void BuildFood2() = 0;
	virtual void BuildFood3() = 0;
	AbstractFood* getFood()
	{
		return food;
	}
protected:
	AbstractFood* food;
};

//4.1 具体建造者A
class Meal_1 :public AbstractBuilder
{
public:
	~Meal_1() {}
	void BuildFood1()
	{
		food->add("香辣鸡腿堡", 10);
	}
	void BuildFood2()
	{
		food->add("薯条", 5);
	}
	void BuildFood3()
	{
		food->add("可乐", 3);
	}
};

//4.2 具体建造者B
class Meal_2 :public AbstractBuilder
{
public:
	~Meal_2() {}
	void BuildFood1()
	{
		food->add("墨西哥鸡肉卷", 10);
	}
	void BuildFood2()
	{
		food->add("鸡块", 5);
	}
	void BuildFood3()
	{
		food->add("芬达", 3);
	}
};

//5. 指挥者： 最后上菜
class Director
{
public:
	~Director() {}
	Director(AbstractBuilder* foodBuilder)
		:fooder(foodBuilder) {}
	AbstractFood* createFood()
	{
		fooder->BuildFood1();
		fooder->BuildFood2();
		fooder->BuildFood3();
		return fooder->getFood();
	}
private:
	AbstractBuilder* fooder;
};

void menu()
{
	cout << "-----------欢迎光临汉堡店：-----------" << endl;
	cout << "-------1. 香辣鸡肉汉堡 + 薯条 + 可乐" << endl;
	cout << "-------2. 墨西哥鸡肉卷 + 鸡块 + 芬达" << endl;
	cout << "------------------------------------" << endl;
}
int main()
{
	unique_ptr<AbstractBuilder> fooder1(new Meal_1);
	unique_ptr<Director> pD1(new Director(fooder1.get()));
	unique_ptr<AbstractFood> food1((pD1.get()->createFood()));

	unique_ptr<AbstractBuilder> fooder2(new Meal_2);
	unique_ptr<Director> pD2(new Director{ fooder2.get()});
	unique_ptr<AbstractFood> food2(pD2.get()->createFood());

	int choice{};
	menu();
	cout << "您的选择：";
	cin >> choice;
	switch (choice)
	{
	case 1:
		food1->show();
		break;
	case 2:
		food2->show();
		break;
	}
	return 0;
}
```
运行如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/d9591f6bf6a44bb7be3fad9c60b2f374.png)

------


 tips： C++实现建造者模式容易出现内存泄露的隐患，例如汉堡店的这个例子：
 我们建议使用智能指针，**否则会造成隐晦的delete操作不明确的事实**。

```cpp
//1. 做套餐A的厨师
AbstractBuilder* Fooder1 = new Meal_1;
//2. 指挥者指挥厨师可以做了
Director* pD1 = new Director{ Fooder1 };
//3. 套餐A做好了
AbstractFood* food1 =  Fooder1->getFood();
//4. 上菜
food1->show();

AbstractBuilder* Fooder2 = new Meal_2;
Director* pD2 = new Director{ Fooder2 };
AbstractFood* food2 = Fooder2->getFood();

....
// 6 个delete一个都不能少！！！！
delete Fooder1;
delete pD1 ;
delete food1 ;

delete Fooder2;
delete pD2;
delete food2 ;
```

----
## 优缺点

**优点**

+ 封装性好，构建和表示分离

+ 扩展性好，各个具体的建造者相互独立，有利于系统的解耦

+ 控制细节风险，客户端无需详知细节，建造者细化创建过程

**缺点**

+ 产品的组成部分必须相同，这限制了其使用范围

+ 产品内部发生变化，建造者需同步修改，后期维护成本较大
