## shared_ptr的计数器底层是怎么实现的

智能指针本身:定义了一个模板类 shared_ptr,用于表示**指向类型为 T** 的共享内存对象的指针,其中需要记录**被指向对象的指针**和一个计数器,用于管理内存的生命周期。

引用计数器:用一个额外的类(如 std::shared_count)来管理引用计数,在其中维护一个计数器m_count。 在构造函数中,计数器初始化为1 在拷贝构造函数中,计数值加1 在析构函数中引用计数减1,如果减1后为0,则调用delete释放对象。 注意,使用 shared_ptr 时,可能会出现循环引用导致内存泄漏的情况。可以使用 weak_ptr 来解决这个问题





## 循环引用问题

两个对象相互使用**shared_ptr**指向对方。造成的后果是：内存泄漏



下面是循环引用的例子

```c++
#include <memory>
using namespace std;
class A;
class B;
class A {
public:
    std::shared_ptr<B> bptr;
    ~A() {
        cout << "A is deleted" << endl; // 析构函数后，才去释放成员变量
    }
};

class B {
public:
    std::shared_ptr<A> aptr;
    ~B() {
        cout << "B is deleted" << endl; // 析构函数后，才去释放成员变量 
    }
};


int main()
{
    std::shared_ptr<A> pa;
    {
        std::shared_ptr<A> ap(new A);
        std::shared_ptr<B> bp(new B);
        ap->bptr = bp;
        bp->aptr = ap;
    }
    return 0;
}
这种状态下，它们的引用计数为均为2
{
    std::shared_ptr<A> ap(new A);
    std::shared_ptr<B> bp(new B);
    ap->bptr = bp;
    bp->aptr = ap;

}
```



在作用域内ap和bp的引用计数都为2，但是当它们退出循环的时候，ap的引用计数减1，bp的引用计数也减1，但它们依旧不为0，引用计数均为1。

现在，对于ap和bp来说，它们都拿着对方的share_ptr，没法使得ab和bp的引用计数为0。那么**A和B的对象均无法析构**。于是造成了内存泄漏。



## 使用weak_ptr解决循环引用问题

shared_ptr采用引用计数的方式，为0的时候就会去析构对象。

可以发现weak_ptr，不影响引用计数，是一种不控制对象生命周期的智能指针。

```C++
int main()
{
    shared_ptr<int> sp(new int(10));
    cout<<sp.use_count()<<endl; //输出1
    weak_ptr<int> wp1=sp;
    weak_ptr<int> wp2=sp;
    cout<<sp.use_count()<<endl; //输出1
}
```

因此只要将例子一中，类成员从shared_ptr改为weak_ptr，即可解决循环引用问题







## weak_ptr怎么判断对象是否被销毁，底层怎么实现的

weak_ptr被设计为与shared_ptr共同工作，可以从一个shared_ptr或者另一个weak_ptr对象构造，获得资源的观测权。但weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加。同样，在weak_ptr析构时也不会导致引用计数的减少，它只是一个静静地观察者。weak_ptr没有重载operator*和->，这是特意的，因为它不共享指针，不能操作资源，这是它弱的原因。但它可以使用一个非常重要的成员函数lock()从被观测的shared_ptr获得一个可用的shared_ptr对象，从而操作资源。

 weak_ptr用于解决”引用计数”模型循环依赖问题，weak_ptr指向一个对象，并不增减该对象的引用计数器。weak_ptr用于配合shared_ptr使用，并不影响动态对象的生命周期，即其存在与否并不影响对象的引用计数器。weak_ptr并没有重载operator->和operator *操作符，因此不可直接通过weak_ptr使用对象。weak_ptr提供了expired()与lock()成员函数，前者用于判断weak_ptr指向的对象是否已被销毁，后者返回其所指对象的shared_ptr智能指针(对象销毁时返回”空”shared_ptr)。

 weak_ptr并没有重载operator->和operator *操作符，因此不可直接通过weak_ptr使用对象，典型的用法是调用其lock函数来获得shared_ptr示例，进而访问原始对象。



