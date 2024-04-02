## 内存上

vector，实质上被叫为ArrayList更为恰当，因为可以不用提前设置好大小，是动态分配空间，随着元素的不断插入，它会按照自身的一套机制不断扩充自身的容量。

vector是连续存储，所以存储的对象在内存上是一条线的，在遍历寻找的时候，会有更优的性能。

vector数组的创建是在堆上创建底层的数据存储，通常在堆上分配内存来存储其元素



## vector优化-->避免不必要的析构与复制

push_back

在vector插入新的元素时，一般使用push_back函数，这个函数实质上是先将目标对象在栈帧创建出来(因为传入的参数是一个对象，已经包括了构造)，然后复制一份再赋值到vector的内存上。

所以要优化性能，可以将push_back统一替换为emplace_back，直接在vector上创建对象（构造），来省去复制赋值的过程

class Vertex{public:    float x, y, z;    Vertex(float x,float y,float z) :x(x), y(y), z(z) {}};

int main(){

​    std::vector<Vertex> verties;    verties.emplace_back(1, 2, 3);//直接在vector中创建对象

}



## vector扩容

而且如果vector目前容量不够，会把vector中的元素依照原有次序从旧的存储空间复制到新的存储空间中，接着要执行一遍元素们的析构函数和释放掉原先的存储空间，这对于性能的影响是十分巨大的所以可以在创建vector一开始就用reserve确定好大小，在堆上分配好对应的内存

int main(){    std::vector<Vertex> verties;    verties.reserve(2);//设置容量，分配内存

}