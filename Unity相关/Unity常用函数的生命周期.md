1.Reset()：此函数是用户首次为游戏对象添加带有该函数的脚本或者用户单击Reset按钮时调用，也就是说该函数是在**把脚本挂载到游戏对象上时就生效**，一般不常用，一般用来批量生成游戏对象

2.Awake()：该函数在脚本对象**实例化时就立即调用**，换句话说，对象初始化之后第一调用的函数就是Awake，当一个游戏对象上挂载了多个脚本，都带有awake，它是乱序的，没有固定顺序执行。**Awake不管脚本是否enabled都会被调用**

3.onEnable()：脚本被启用时调用一次

4.Start()：则Start函数在**第一帧更新之前**被调用，意思就是在创建出游戏对象后，在第一帧刷新前被调用（也就是在update执行之前调用之前）。Start如果对象被SetAcive(false)或者enabled= false了是不会被调用的。

5.FixedUpdate()：**物理更新函数**，不受电脑性能影响，每0.02s更新一次（默认是每秒调用50次，时间可以在首选项中进行更改）

6.Update()：更新函数，**每帧执行一次**，受电脑性能影响

7.LateUpdate()：稍后更新函数，在每次Update函数**更新完后立即**更新

8.OnGUI():在**渲染和处理GUI事件**时被调用，每帧都执行

9.Ondisable()：当脚本**被禁用时**就被调用

10.OnDestory()：当脚本被销毁时披调用，只会在被激活的物体上调用