## 一、什么是placement new

placement new就是在用户指定的内存位置上（这个内存是已经预先分配好的）构建新的对象，因此这个构建过程**不需要额外分配内存**，只需要调用对象的构造函数在该内存位置上**构造对象**即可

语法格式：address：placement new所指定的内存地址（指针）

ClassConstruct：对象的构造函数

Object * p = new (address) ClassConstruct(...);

优点：在已分配好的内存上进行对象的构建，构建速度快

已分配好的内存可以反复利用，有效的避免内存碎片问题

## 二、用法

下面与普通的new操作符来做比较，演示placement new的用法：

普通的new操作符分配一个对象的过程如下：

①使用new分配对象内存（堆中）

②调用对象类的构造函数在该内存地址创建对象

例如：

int *p = new int(1);

placement new分配一个对象的过程如下：

①使用new引用一个已经分配好的内存

int* buff = new int;



②调用对象类的构造函数在该内存地址上创建对象

例如：

//先分配一对内存

int* buff = new int;

memset(buff,0,sizeof(int));

//此处new的placement new，在buff的内存上构造int对象，不需要**分配额外**的内存

int *p = new (**buff**)**int(3)**;

std::cout << *p << std::endl; 



## 三、优势

一般是维护一个对象池，因为游戏里对象的创建和销毁比较频繁，如果频繁的去开辟新的空间，消耗是承担不起的