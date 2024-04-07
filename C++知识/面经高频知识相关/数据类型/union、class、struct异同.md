## union

概述

在C++编写中，当多个基本数据类型或复合数据结构要占用同一片内存时，我们要使用联合体；当多种类型，多个对象，多个事物只取其一时，我们也可以使用联合体来发挥其长处。

在任意时刻，联合中只能有一个数据成员可以有值。当给联合中某个成员赋值之后，该联合中的其它成员就变成未定义状态了。联合体的内存大小就是最大的成员的内存大小，同样如果被赋值，就会赋值到同一片内存中，数值也是对应的。

下面是union利用共享内存来类型转换的例子

```c++
struct Vector2 {
    float x, y;
};

struct Vector4
{
    union
    {
        //union只能有一个成员（内存），之后都与第一个内存相同，所以可以用结构体包装需要的变量
        struct
        {
            float x, y, z, w;
        };
        struct 
        {
            Vector2 a, b;//这里2个元素就和上面四个float内存一致
        };
    };
};

void PrintVector2(const Vector2& vector) {
     std::cout << vector.x << "," << vector.y << std::endl;
}

int main() {
    Vector4 vector = { 1.0f,2.0f,3.0f,4.0f };
    PrintVector2(vector.a);
    PrintVector2(vector.b);
    std::cin.get();
}
```









## union/class/struct异同

### 1.访问权限

struct、union的默认访问权限都是public

class的默认访问权限是private。

不过**都**可以通过显式来指定访问权限。

### 2.内存大小

struct、class的内存大小为所有成员的内存之和

union的内存大小为最大的成员的内存大小，成员变量之间共享内存。

### 3.继承

struct、class都可以进行继承与被继承，不过struct只能添加带参数的构造函数。

union不可以作为基类，也不能从别的基类派生。

### 4.成员

union不能包含虚函数，静态数据变量，也不能存放带有构造、析构、拷贝构造等函数的类。(比如就不能添加vector变量，不过可以添加结构体)

### 5.template模板

class可以使用模板，而struct不可以