Tags and Layers

Tag

从数据角度出发是一串字符串

物体设置tag标签，也可以理解为标记物体，用以**区分物体**（需要通过标签确定物品类别）

标签对碰撞体控制脚本中的**触发器**很有用

常见的 Tag 相关函数

//访问Tag gameObject.tag

//查找场景中指定标签的物体--找不到未激活(active)的物体。 GameObject.FindObjectWithTag()

//返回场景中指定标签的所有物体 GameObject.FindGameObjectsWithTag()



Layer

从数据角度出发是 int

在 Unity 编辑器中使用图层可以创建具有共同特定特征的对象组。图层主要用于**限制射线投射或渲染等操作**。以便它们仅应用于相关的对象组。标记为 Builtin Layer 的图层是 Unity 使用的默认图层.

Unity中是用**int32来表示32个Layer层**。int32表示二进制一共有32位（0—31） 在Unity中每个GameObject都有Layer属性，**默认的Layer都是Default**。在**Unity中可编辑的Layer共有24个**（8—**31**层），**官方已使用的是0—7层**，默认不可编辑

使用场景:

让摄像机只渲染某些层的物体，对另一些层的物体不渲染 让光源只照亮对某些层的物体，而对另一些层的物体不影响。 供射线投射用于选择性地**忽略**碰撞体或创建碰撞 常用Layer相关函数

//设置物体层级

SetGameObjectLayer({},{});

//LayerMask用于在渲染或者其他检查操作时裁剪（忽略）掉某些物体

LayerMask mask = 1 << 3；表示开启Layer3。

LayerMask mask = 0 << 8；表示关闭Layer8。

LayerMask mask = 1<<1|1<<9；表示开启Layer1和Layer9。

LayerMask mask = 0<<4|0<<5；表示关闭Layer4和Layer5。

LayerMask mask = ~(1 << 0) 打开所有的层。

LayerMask mask = ~(1 << 9) 打开除了第9之外的层。

//也可以使用层的名称设置，例如：

LayerMask mask  = 1 << LayerMask.NameToLayer(“TestLayer”);  表示开启层名“TestLayer” 的层 。

LayerMask mask  = 0 << LayerMask.NameToLayer(“TestLayer”);  表示关闭层名“TestLayer” 的层 。







Collider2D

Material 材质

关联材质，默认是一个2D物理材质Physics Material 2D，用来调整2D物理对象碰撞时这些对象之间的**摩擦和弹性**。

Collision 碰撞（2collider+1rigid）

可以通过Collision相关函数检测Enter2D、Exit2D、Stay2D碰撞

Is Trigger 触发器（开关 collider）

选中后，这个2D碰撞体会**作为触发器**，可以通过Trigger相关函数检测Enter2D、Exit2D、Stay2D触发



Rigidbody2D

Body Type刚体类型

一共可设置成三种：Dynamic动态、Kinematic运动学、Static静态。

Dynamic动态：**正常**的物体行为，**完全参与物理模拟** Kinematic运动学：只可以**通过transform**来改变物体的运动位置 Static静态 ：完全不动的物体

Collision Detection

检测碰撞的方式 Discrete  碰撞时在物理更新期间**可以重叠/穿过彼此**，在移动速度够快时

Continuous 不会穿过彼此（引擎**会自动计算第一个碰撞点**，并将游戏对象**移动到该点**）



Gravity Scale

重力影响（Dynamic动态下） 定义**游戏对象受重力影响的程度**，0==不受重力影响。



射线检测

Rhysics2D.Raycast 是实现射线检测的函数，可以设置射线开始的位置origin、direction、distance、layermask（参与检测Layer）