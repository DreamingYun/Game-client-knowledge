Array 数组

数组属于线性结构，在内存中是连续存放的。

优缺点：

优：存储在连续内存上；元素类型必须是相同类型；可以通过下标访问，**查找的速度很快**；

缺：初始化时必须指定其长度，元素插入不便，**新增和删除也很慢**；



ArrayList 动态数组

ArrayList的底层其实就是一个数组。

优缺点：

优：ArrayList在声明时不必指定长度，会根据**存储的数据动态的增加或减少长度**。会把**所有的元素都当做Object处理**，因此可以存储不同数据类型的元素。

缺：类型不安全，因为存储的是不同类型，都会当Object来处理。是非类型安全的，在插入和删除元素时**会进行拆箱和装箱问题**，影响性能，效率低。插入和删除一个元素时，会移动它之后所有元素的位置，效率低；



List 泛型

list在Unity中是比较常见的数据结构，因为ArrayList相当于Array的一个优化，**List又相当于ArrayList的泛型类**，成功**解决**ArrayList装箱拆箱的问题，既安全又提升了效率；

优缺点：

优：List是ArrayList的泛型类，Array和ArrayList结合，泛型在声明时指定具体的类型，规定其类型，避免了拆装箱操作，及安全又提升了效率；





Linkedlist

LinkedList集合：底层数据结构是链表，查询慢、增删快



LinkedList特有方法

方法名	说明

public void addFirst(E e)	添加元素到数组开头

public void addLast(E e)	添加元素到数组末尾

public E getFirst()	查询第一个元素

public E getLast()	查询最后一个元素

public E removeFirst()	删除并返回第一个元素

public E removeLast()	删除并返回最后一个元素