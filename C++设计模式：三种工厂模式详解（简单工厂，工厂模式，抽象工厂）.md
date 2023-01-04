@[toc]


# 简单工厂模式


简单工厂模式属于**类的创建型模式**,又叫做**静态工厂方法模式。**

通过专门定义一个类来负责创建其他类的实例，**被创建的实例通常都具有共同的父类。**

简单工厂模式可以减少客户程序对类创建过程的依赖。

----

## 简单工厂实现步骤

1.提供一个**工厂类**

简单工厂模式的核心，它负责实现**创建所有实例的内部逻辑**。**工厂类可以被外界直接调用，创建所需的产品对象。**

2.提供一个**抽象产品类**

简单工厂模式所创建的所有对象的父类，它负责描述**所有实例所共有的公共接口**。

3.提供一个**具体产品类**

简单工厂模式所创建的具体实例对象

![请添加图片描述](https://img-blog.csdnimg.cn/72682a23dc3a40a18b218f0cd93357b2.png)


----

实现代码：
我们实现一个造飞机和火箭的系统。

1. `抽象产品类`**声明飞机产品和火箭产品的业务方法**（纯虚函数，等待子类实现）。
2. `具体产品类`**实现其父类的业务方法**
3. `具体工厂类`**创建产品对象**：创建造飞机厂和造火箭厂

```cpp
/*
造飞机造火箭
*/

/*----------------
1. 抽象产品类
----------------*/
class AbstractProduct
{
public:
	virtual ~AbstractProduct() {}
	virtual void MakeProduct() = 0;
};
/*----------------
2. 具体产品类
----------------*/

//2.1. 飞机产品类
class PlaneProduct :public AbstractProduct
{
public:
	~PlaneProduct() {}
	void MakeProduct()override
	{
		cout << "飞机产品" << endl;
	}
};
//2.2. 火箭产品类
class RocketProduct :public AbstractProduct
{
public:
	~RocketProduct() {}
	void MakeProduct()override
	{
		cout << "火箭产品" << endl;
	}
};
/*----------------
3. 具体工厂类：负责创建每一个实例产品对象
----------------*/
class Factory
{
public:
	//一个枚举，根据这个枚举的种类来决定你要创建哪个对象
	enum class ProductType { Plane, Rocket };
	static AbstractProduct* CreateProduct(ProductType type)
	{
		switch (type)
		{
		//创建飞机类
		case Factory::ProductType::Plane:
			return new PlaneProduct;
		//创建火箭类
		case Factory::ProductType::Rocket:
			return new RocketProduct;
		}
	}
};

int main()
{
	//1. 工厂创建产品
	AbstractProduct* Plane = Factory::CreateProduct(Factory::ProductType::Plane);
	//2. 使用产品
	Plane->MakeProduct();
	delete Plane;
	delete Rocket;
	
	AbstractProduct* Rocket = Factory::CreateProduct(Factory::ProductType::Rocket);
	Rocket->MakeProduct();
	delete Plane;
	delete Rocket;
	
	return 0;
}
```

## 简单工厂优缺点

**优点**：

- 帮助封装

  实现组件封装，面向接口编程

- 解耦合

  客户端和具体实现类的解耦合

**缺点**：

-  可能增加客户端的复杂度
-  不方便扩展子工厂
----
# 工厂模式

工厂方法模式同样属于类的创建型模式又被称为`多态工厂模式 `。工厂方法模式的意义是 定义一个创建产品对象的工厂接口，将实际创建工作推迟到子类当中。 核心工厂类不再负责产品的创建，这样`核心类成为一个抽象工厂角色`，**仅负责具体工厂子类 必须实现的接口**，这样进一步抽象化的好处是使得工厂方法模式可以使系统在不修改具体工厂角色的情况下引进新的产品

## 工厂模式和简单工厂模式有什么不同？

工厂方法模式与简单工厂模式的区别在结构上的并不明显。

1. 而简单工厂模式把核心放在一个**具体工厂类**上。
2. 工厂方法类的核心是一个**抽象工厂类**。


 工厂方法模式之所以有一个别名叫**多态性工厂模式是因为具体工厂类都有共同的接口**， 或者有共同的抽象父类。 当系统扩展需要添加新的产品对象时，仅仅需要添加一个具体对象以及一个具体工厂对象，原有工厂对象不需要进行任何修改，也不需要修改客户端，很好的符合了《“开放－封闭”原则 》 。而简单工厂模式在添加新产品对象后不得不修改工厂方法，扩展性不好。工厂方法模式退化后可以演变成简单工厂模式。 

在添加新产品对象时的不同：

1. 简单工厂模式**需要修改工厂方法**，不符合《开放封闭原则》
2. 工厂模式无需修改抽象工厂方法，**只需添加一个具体工厂**，符合《开放封闭原则》

----

## 工厂模式实现步骤

1.提供一个**抽象工厂类** :所有具体工厂类的父类

2.提供与产品对应的**实例工厂类**:负责实例化产品对象

3.提供一个**抽象产品类**： 所有产品的父类

4.提供一个或多个**实例产品类**:工厂方法模式所创建的具体实例对象

![请添加图片描述](https://img-blog.csdnimg.cn/1c4b3d5370634e6c9f1efadf5219de96.png)

----
## 实现代码
依旧是造飞机和火箭的例子，我们来看看它与简单工厂模式有什么不同？

1. **抽象产品类**：飞机产品与火箭产品所具有的业务方法
2.  **抽象工厂类**：这是相比简单工厂模式不同的地方，把各个产品的工厂分隔开，实现一个抽象工厂，其声明了各个工厂创建对象的方法。
3. **具体产品类**
4. **具体工厂类**

```cpp
#include <iostream>
using namespace std;

//造飞机造火箭

/*----------------
1. 抽象产品类
----------------*/
class AbstractProduct
{
public:
	virtual void MakeProduct() = 0;
};

/*----------------
2. 抽象工厂类
----------------*/
class AbstractFactory
{
public:
	virtual AbstractProduct* CreateProduct() = 0;
};

/*----------------
3. 具体产品类： 飞机
----------------*/
class PlaneProduct:public AbstractProduct
{
public:
	void MakeProduct()override
	{
		cout << "飞机产品" << endl;
	}
};
/*----------------
4. 具体工厂类：造飞机
----------------*/
class PlaneFactory :public AbstractFactory
{
public:
	AbstractProduct* CreateProduct()override
	{
		return new PlaneProduct;
	}
};

/*----------------
3. 具体产品类： 火箭
----------------*/
class RocketProduct :public AbstractProduct
{
public:
	void MakeProduct()override
	{
		cout << "火箭产品" << endl;
	}
};
/*----------------
4. 具体工厂类：造火箭
----------------*/
class RocketFactory :public AbstractFactory
{
public:
	AbstractProduct* CreateProduct()override
	{
		return new RocketProduct;
	}
};
int main()
{
	//1. 开设工厂（飞机，火箭）
	AbstractFactory* factory = new PlaneFactory;
	//2. 制造产品
	AbstractProduct* product =  factory->CreateProduct();
	//3. 使用产品
	product->MakeProduct();

	factory = new RocketFactory;
	product = factory->CreateProduct();
	product->MakeProduct();

	return 0;
}
```
## 工厂模式优缺点

**优点**：

+ 需求改变时改动最小

+ 具体的创建实例过程与客户端分离

**缺点：**

+ 新增功能时，工程量稍大

----

# 抽象工厂模式

抽象工厂模式是所有形态的工厂模式中最为抽象和最一般性的。抽象工厂模式可以向客户端提供一个接口，**使得客户端在不必指定产品的具体类型的情况下，能够创建多个产品族的产品对象。** 


抽象工厂方法是针对与一个产品族，使得易于交换产品系列，只需改变具体的工厂就可以使用不同的产品配置。当一个族中的产品对象被设计成一起工作且一个应用只适用同一族的对象，例如设计系统生成不同风格的UI界面，按钮，边框等UI元素在一起使用，并且只能同属于一种风格，这很容易使用抽象工厂实现。

## 抽象工厂模式实现步骤


1. 提供一个**抽象工厂类**：声明一组创建一族产品的工厂方法
2. 提供一个**具体工厂类**：实现了在抽象工厂创建产品的工厂方法
3. 提供一个**抽象产品类**：抽象产品中声明了产品具有的业务方法
4. （可选）提供**抽象产品族**：抽象产品族表示了某些不同族的产品类型（键盘，鼠标..）
5. 提供一个**具体产品类**：实现抽象产品接口中声明的业务方法
![请添加图片描述](https://img-blog.csdnimg.cn/8643ed09f9ce43b39d74f7d9a7881996.png)


## 实现代码

```cpp
#include <iostream>
using namespace std;
/*
抽象工厂模式
1. 抽象产品类
2. 抽象产品族
3. 具体产品类
4. 抽象工厂类
5. 具体工厂类
*/

//----生产键盘和鼠标----

//抽象产品类： 声明了产品具有的业务方法
class AbstractProduct
{
public:
	virtual ~AbstractProduct() {}
	virtual void MakeProduct() = 0;
};

//1. 键盘
//抽象产品族
class KeyBoard :public AbstractProduct {};

//具体产品类：实现产品的具体方法
class LogiKeyBoard :public KeyBoard
{
public:
	~LogiKeyBoard() {}
	void MakeProduct()override
	{
		cout << "罗技键盘" << endl;
	}
};
class RazerKeyBoard :public KeyBoard
{
public:
	~RazerKeyBoard() {}
	void MakeProduct()override
	{
		cout << "雷蛇键盘" << endl;
	}
};

//2. 鼠标
//抽象产品族
class Mouse :public AbstractProduct {};

//具体产品类
class LogiMouse :public Mouse
{
public:
	~LogiMouse() {}
	void MakeProduct()override
	{
		cout << "罗技鼠标" << endl;
	}
};
class RazerMouse :public Mouse
{
public:
	~RazerMouse() {}
	void MakeProduct()override
	{
		cout << "雷蛇鼠标" << endl;
	}
};

/*
//TODO：在此增加新的产品族与具体产品类...
//
//*/

//抽象工厂类: 声明提供创建每一族产品的方法
class AbstractFactory
{
public:
	virtual ~AbstractFactory() {}
	virtual KeyBoard* CreateKeyBoard() = 0;
	virtual Mouse* CreateMouse() = 0;
	//TODO: 提供每一个产品族的创建方法...
};

//具体工厂类：实现创建产品的方法
//1. 罗技工厂
class LogiFactory:public AbstractFactory
{
public:
	~LogiFactory() {}
	KeyBoard* CreateKeyBoard()override
	{
		return new LogiKeyBoard;
	}
	Mouse* CreateMouse()override
	{
		return new LogiMouse;
	}
};
//2. 雷蛇工厂
class RazerFactory :public AbstractFactory
{
public:
	~RazerFactory() {}
	KeyBoard* CreateKeyBoard()override
	{
		return new RazerKeyBoard;
	}
	Mouse* CreateMouse()override
	{
		return new RazerMouse;
	}
};

int main()
{
	AbstractFactory* Factory = new RazerFactory;
	KeyBoard* keyBoard =  Factory->CreateKeyBoard();
	Mouse* mouse =  Factory->CreateMouse();
	keyBoard->MakeProduct();
	mouse->MakeProduct();

	delete Factory;
	delete keyBoard;
	delete mouse;
	
	Factory = new LogiFactory;
	keyBoard = Factory->CreateKeyBoard();
	mouse = Factory->CreateMouse();
	keyBoard->MakeProduct();
	mouse->MakeProduct();

	delete Factory;
	delete keyBoard;
	delete mouse;
	Factory = nullptr;
	keyBoard = nullptr;
	mouse = nullptr;
	return 0;
}
```
## 抽象工厂模式优缺点

**优点**：

+ 抽象工厂封装了变化，封装了对象创建的具体细节
+ 增加新的产品族很方便，无须修改已有系统
+ 针对接口进行编程而不是针对具体进行编程

**缺点：**

+  增加新的产品等级结构需对原系统做较大修改(违背开放封闭)
