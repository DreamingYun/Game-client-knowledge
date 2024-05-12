## ESC框架

ECS是新的面向数据的游戏架构

#### 前语

Entity Component System (ECS) 是一个 gameplay 层面的框架，它是建立在渲染引擎、物理引擎之上的，主要解决的问题是如何建立一个模型来处理游戏对象 (Game Object) 的更新操作。

传统的很多游戏引擎是基于面向对象来设计的，游戏中的东西都是对象，每个对象有一个叫做 Update 的方法，框架遍历所有的对象，依次调用其 Update 方法。有些引擎甚至定义了多种 Update 方法，在同一帧的不同时机去调用。

这么做其实是有极大的缺陷的，我相信很多做过游戏开发的程序都会有这种体会。因为游戏对象其实是由很多部分聚合而成，引擎的功能模块很多，不同的模块关注的部分**往往互不相关**。比如渲染模块并不关心网络连接、游戏业务处理不关心玩家的名字、用的什么模型。从自然意义上说，把游戏对象的属性聚合在一起成为一个对象是很自然的事情，对于这个对象的生命期管理也是最合理的方式。但对于不同的业务模块来说，针对聚合在一起的对象做处理，把处理方法绑定在对象身上就不那么自然了。这会导致模块的内聚性很差、模块间也会出现不必要的耦合。 





#### 介绍

![](C:\Users\admin\Desktop\JJD\Personal\Game-client-knowledge\UI框架整理\images\v2-486c96a9740c61f1a0a3592657d3938c_720w.webp)

ECS 的 E ，也就是 Entity ，可以说就是传统引擎中的 Game Object 。但在这个系统下，它仅仅是 C/Component 的组合。它的意义在于生命期管理，这里是用 32bit ID 而不是指针来表示的，另外附着了渲染用到的资源 ID 。因为仅负责生命期管理，而不设计调用其上的方法，**用整数 ID 更健壮**。整数 ID 更容易指代一个无效的对象，而指针就很难做到。



C 和 S 是这个框架的核心。System 系统，也就是我上面提到的模块。对于游戏来说，每个模块应该专注于干好一件事，而每件事要么是作用于游戏世界里同类的一组对象的每单个个体的，要么是关心这类对象的某种特定的交互行为。比如碰撞系统，就只关心对象的体积和位置，不关心对象的名字，连接状态，音效、敌对关系等。它也不一定关心游戏世界中的所有对象，比如关心那些不参与碰撞的装饰物。所以对每个子系统来说，**筛选出系统关心的对象子集**以及只给它展示它所关心的数据就是框架的责任了



在 ECS 框架中，把每个可能单独使用的对象属性归纳为一个个 Component ，比如对象的名字就是一个 Component ，对象的位置状态是另一个 Component 。每个 Entity 是由多个 Component 组合而成，共享一个生命期；而 Component 之间可以组合在一起作为 System 筛选的标准。我们在开发的时候，可以定义一个 System 关心某一个**固定 Component 的组合**；那么框架就会把游戏世界中**满足有这个组合**的 Entity 都筛选出来供这个 System **遍历**，如果一个 Entity 只具备这组 Component 中的一部分，就不会进入这个筛选集合，也就不被这个 System 所关心了。



例：

根据输入状态来决定是不是要把长期不产生输入的对象踢下线的例子，就是要对象**同时具备连接组件、输入组件**等，然后这个 AFK 处理系统遍历所有符合要求的对象，根据最近输入事件产生的时间，把长期没有输入事件的对象通知下线；他特别说到，AI 控制的机器人，由于没有连接组件，虽然具备状态组件，但不满足 AFK 系统要求的完整组件组的要求，就根本不会遍历到，也就不用在其上面浪费计算资源了。我认为这是 ECS 相对传统对象 Update 模型的一点优势；用传统方法的话，很可能需要写一个空的 Update 函数。



游戏的业务循环就是在调用很多不同的系统，每个系统自己遍历自己感兴趣的对象，只有**预定义的组件部分可以被子系统感知到**，这样每个系统就能具备很强的内聚性。注意、这和传统的面向对象或是 Actor 模型是截然不同的。OO 或 Actor 强调的是对象自身处理自身的业务，然后框架去管理对象的集合，负责用消息驱动它们。而在 ECS 中，每个系统关注的是不同的对象集合，它处理的对象中有共性的切片。这是很符合守望先锋这种 MOBA 类游戏的。这类游戏关注的是对象间的关系，比如 A 攻击了 B 对 B 造成了伤害，这件事情是在 A 和 B 之间发生的，在传统模型中，你会纠结于伤害计算到底在 A 对象的方法中完成还是在 B 的方法中完成。而在 ECS 中不需要纠结，因为它可以在伤害计算这个 System 中完成，这个 System 关注的是所有对象中，和**伤害的产生有关的**那一小部分数据的集合。



ECS 的设计就是为了管理复杂度，它提供的指导方案就是 **Component 是纯数据组合**，没有任何操作这个数据的方法；而 **System 是纯方法组合**，它自己没有内部状态。它要么做成无副作用的纯函数，根据它所能见到的对象 Component 组合计算出某种结果；要么用来更新特定 Component 的状态。System 之间也不需要相互调用（减少耦合），是由游戏世界（外部框架）**来驱动若干 System** 的。如果满足了这些前提条件，每个 System 都可以独立开发，它只需要遍历给框架提供给它的组件集合，做出正确的处理，更新组件状态就够了。编写 Gameplay 的人更像是在用胶水粘合这些 System ，他只要清楚每个 System 到底做了什么，操作本身对哪些 Component 造成了影响，正确的书写 System 的更新次序就可以了。一个 System 对大多数 Component 是只读的，只对少量 Component 是会改写的，这个可以预先定义清楚，有了这个知识，一是容易管理复杂度，二是给并行处理留下了优化空间

ECS 的本质还是数据 C 和操作 S 分离。而操作 S 并不局限于对同类组件集合的管理，也可是是针对单个组件。作者自己也说，最终有 40% 的组件就是单件



#### 对于网络同步而言

比如说，ECS 规定每个需要根据输入表现的 System 都提供了一个 UpdateFixed 函数。守望先锋的同步逻辑是基于 60fps 的，所以这个 UpdateFixed 函数会每 16ms 调用一次，专门用于计算这个逻辑帧的状态。服务器会根据玩家延迟，稍微推迟一点时间，比客户端晚一些调用 UpdateFixed 。在我去年谈同步的 blog 中也说过，玩家其实不关心各个客户端和服务器是不是时刻上绝对一致（绝对一致是不可能做到的），而关心的是，不同客户端和服务器是不是展现了**相同的过程**。就像直播电影，不同的位置早点播放和晚点播放，大家看到的内容是一致的就够了，是不是同时在观看并不重要



但是，游戏和电影不一样的地方是，玩家自己的操作影响了电影的情节。我们需要在服务器仲裁玩家的输入对世界的影响。玩家需要告知服务器的是，我这个操作是在电影开场的几分几秒下达的，服务器按这个时刻，把操作插入到世界的进程中。如果客户端等待服务器回传操作结果那就实在是太卡了，所以客户端要在操作下达后自己模拟后果。如果操作不被打断，其实客户端模拟的结果和服务器仲裁后的结果是一样的，这样服务器在回传后告之客户端过去某个时间点的对象的状态，其实和当初客户端模拟的其实就是一致的，这种情况下，客户端就开开心心继续往前跑就好了

只有在预测操作时，比如玩家一直在向前跑，但是服务器那里感知到另一个玩家对他释放了一个冰冻，将他顶在原地。这样，服务器回传给玩家的位置数据：他在某时刻停留在某地就和当初他自己预测的那个时刻的**位置不同**。产生这种**预测失败后**，客户端就需要自己调节。有 ECS 的帮助，状态回滚到发生分歧的版本，考虑到服务器回传的结果和新了解到的世界变化，重新将之后一段时间的操作重新作用到那一刻的状态上，做起来就相对简单了。

对于服务器来说，它默认客户端会持续不断的以固定周期向它推送新的操作。正如前面所说，服务器的时刻是有意比客户端延后的，这样，它并非立刻处理客户端来的输入，而是把输入先放在一个缓冲区里，然后按和客户端固定的周期 ( 60fps ) 从缓冲区里取。由于有这个小的缓冲区的存在，轻微的网络波动（每个网络包送达的路程时间不完全一致）是完全没有影响的。但如果网络不稳定，就会出现到时间了客户端的操作还没有送到。这个时候，服务器也会尝试预测一下客户端发生了什么。等真的操作包到达后，比对一下和自己的预测值有什么不同，基于过去那个产生分歧的**预测产生的状态**和**实际上传的操作**计算出下一个状态。



这个时候服务器会意识到网络状态不好，它主动通知客户端说，网络不太对劲，这个时候的大家遵循的协议就比较有趣了。那就是客户端得到这个消息就开始做**时间压缩**，用**更高的频率**来跑游戏，从 60fps 提高到 65fps ，玩家会在感受到轻微的加速，结果就是客户端用更高的频率产生新的输入：从 16 ms 一次变成了 15.2 ms 一次。也就是说，短时间内，客户端的时刻更加领先服务器了，且越领先越多。这样，服务器的预读队列就能更多的**接收到未来**将发生的操作，遇到到点却不知道客户端输入的**可能性就变少**了。但是总流量并没有增加，因为假设一局游戏由一万个 tick 组成，无论客户端怎么压缩时间，提前时刻，总的数据还是一万个 tick 产生的操作，并没有变化。一旦度过了网络不稳定期，服务器会通知客户端已经正常了，这个时候客户端知道自己压缩时间导致的领先时长，对应的膨胀放慢时间（**降低**向服务器发送操作的频率）让状态回到原点即可。





守望先锋 是基于 UDP 通讯的，从演讲介绍看，对于 UDP 可能丢包的这个问题，他们处理的简单粗暴：客户端每次都将没有经过服务器确认的包打包在一起发送。由于每个逻辑帧的操作很少，打包在一起也不会超过 MTU 限制。

ECS 在这个过程中真正发生威力的地方是在预测错误后纠正错误的阶段。一旦需要纠正过去发生的错误，就需要回滚、重新执行指令。移动、射击这些都属于常规的设定，比较容易做回滚重新执行；技能本身是基于暴雪开发的 Statescript 的，通过它来达到同样的效果。ECS 的威力在于，把这些元素用 Component 分离了，可以单独处理。

比如说射击命中判定，就是一个单独的系统，它基于**被判定对象都有一个**叫做 ModifyHealthQueue 的组件。这个组件里记录的是 Entity 身上收到的所有伤害和治疗效果。这个组件可以用于 Entity 的**筛选器**，没有这个组件的对象不会受到伤害，也就不需要参与命中判定。真正影响命中判定的是 MovementState 组件，它也参与了命中判定这个系统的筛选，并真正参与了运算。命中判定在查询了敌对关系后从 MovementState 中获取应该比对的对象的位置，来预测它是否被命中（可能需要播放对应的动画）。但是伤害计算，也就是 ModifyHealthQueue 里的数据是只能在服务器填写并推送给客户端的。



MovementState 会因为需要纠正错误预测而被回退，同时还有一些非 MovementState 的状态也会回退，比如门的状态、平台的状态等等。这个回退是 Utility 函数的行为，它可能会影响受击的表现，**而受伤则是另一种固定行为**（服务器确定的推送）的后果。他们发生在 Entity 的不同组件切片上，就可以正交分离

射击预测和纠正可以利用对象的活动区域来减少判定计算量。如果能总是计算保持当前对象在过去一段时间的最大移动范围（即过去一段时间的包围盒的并集），那么当需要做一个之前发生的射击命中判定时，就只需要把射击弹道和当前所有对象的检测区域比较，只有相交才做进一步检测：回退相关对象到射击发生的时刻，做严格的命中校验。如果当初预测的命中结果和现在核验的一致就无所谓了，不需要修正结果（如果命中了，具体打中在哪不重要；如果未命中，也不管子弹射到哪里去了）。





如果 ping 值很高，客户端做命中预测往往是没有什么意义的，徒增计算量。所以在 Ping 超过 220ms 后，客户端就不再提前预测命中事件，直接等服务器回传。

ECS 框架在这件事上可以做到只去回滚和重算相关的 Component ，一个 System 知道哪些 Entity 才是它真正关心的，该怎么回退它所关心的东西。这样开发的复杂度就减少了。游戏本身是复杂的，但是和网络同步相关的影响到游戏业务的 System 却很少，而且参与的 Component 几乎都是只读的。这样我们就尽可能的把这个复杂的问题和引擎其它部分解耦。



参考文献

[云风的 BLOG: 浅谈《守望先锋》中的 ECS 构架 (codingnow.com)](https://blog.codingnow.com/2017/06/overwatch_ecs.html#more)





![](C:\Users\admin\Desktop\JJD\Personal\Game-client-knowledge\UI框架整理\images\屏幕截图 2024-04-18 122334.png)





## KTS框架

**主要分为system（只负责逻辑的处理）和store（只负责数据的存储）两个部分，且store与system一一对应，store只能由对应的system进行修改**



### 前置知识

D：装饰器

F：Framework框架中（封装了UE方法）

L：KTSUELauncher（启动引擎...，获得world）（启动jsenv，js的虚拟机）

整体思路：**hotfix-> 热加载（将js对应的内存对象、地址全部替换掉，虚拟机）**

C++（native）亦可热更UE中含有，但难度高





### System

作为处理事务的主要逻辑单位，**不允许存储数据，只写逻辑**，于 ECS 的 System 相同。手动创建system使用init初始化，手动删除的时候走uninit。

注意：在该UI面板销毁后，记得需要onSubscribe解绑掉事件，防止调用报错。

createobject对应destorypbjectbyinstanceid（这是ts中的唯一标识，蓝图是uniqueid）



|_ tagHelper

通过自定义的字符串，帮助system去管理【UITagDefine】Define的tag用于持久化的加载

|_ subscriberHelper
|_ friendMap
|_ Lifecycle Functions(init, postInit, preUninit, uninit)

生命周期

|_ Subscribe Functions(subscribe, unsubscribe, subscribeWithStore, unsubscribeWithStore, subscribeDelegate, unsubscribeDelegate, subscribeMulticastDelegate, unsubscribeMulticastDelegate, unsubscribeAll)

订阅事件，通过事件去触发逻辑

|_ Log Functions(trace, debug, info, warn, error, fatal)

规范日志系统

this.info(`[RoomList] This is the refresh cooldown period.`);



### Store

作为数据存储元，只存储数据，不带逻辑。相当于ECS中Entity、Component的综合体，树形结构。（也就是说存储了标识符---区分不同类型的标志  和基础数据）

Store
|_ SingletonStore 单例Store，全局数据（可以通过tag或者system去创建）
    |_ RootStore Store是一颗树，最根节点的Store(存储了很多单例store，同理其没有对应的system管理)



StoreOwner StoreOwner基类（**System**是Store的Owner，所以 继承自这个）
|_ RootStoreOwner （RootStore也得有个Owner，所以这个Owner是个特殊的，外部用不到）



GameObjectStore

 GameObjectActorStore(从而获取到Actor)

UI创建的流程，那就是启动system，然后创建对应的store，作为数据的存储，然后跑起来UI，以tag作为一个总的标识

store和system是绑定的





### Event Flow（事件流）

- Action-执行do，行为处理链，明确要做的事情（角色）-单播->有返回值

- Event-通知dispatch，有这个事情 -多播->无返回值（解耦）-UI永远被动，游戏可以没有UI

- StoreAction--**store=key**  传入特殊的状态机action 不需要map管理【解决多态】

  @D.on(UIRoomListStore) -- 语法糖，将当前的这个storeAction去动态绑定和这个相关的store（引入一个参数，从而去分发给不同的人，以第一个参数作为一个key去分发，绑定的时候也通过key）

    protected onEscActive(action: EscActiveSAction) {

  ​    this.closeRoomList();

    }

  

- StoreEvent -- 也就是storeAction的一个类比

  

- CppDelegate(Delegate，MulticastDelegate) 将引擎中普通的delegate和multicastDelegate进行一个封装，解绑和绑定更加安全







### Decorator（语法糖TS特殊）

- D.store(tag?: string); //让类去标明，它是一个store的**注册**

- D.system(tag: string, storeCtor?: typeof Store | typeof Store[]);

- D.on()//调用system**对应的绑定函数去绑定**

  在load的时候，统一进行一个注册，并且执行一个函数(一般为注册)
  
  



###  Misc

- HookManager

  拿到所有的UIsystem并且在其启动的时候，绑定对应的按键（时机）

- RuntimeContext

- SourceMapSupport

- StoreKeyHelper

- StoreLifecycleHelper

- SubscriberHelper

- Subscriber

- TagHelper

- Launcher--Load脚本

- GlobalFunction

  - Assert
  - Stacktrace
  - Log

- GlobalUEFunction--接口，将虚幻相关函数传入

  - getTSFramework
  - getEngine
  - getWorld
  - isChildOf







## KUIFramework

**全局的KGameInstance（游戏全局的生命周期）是KFrameWork封装了Gameinstance得来**。引用、计时器（即使是临时对象）需要自己管理（销毁）



### 关键概念

#### UI、Wnd、Prefab

UI 是所有交互界面的统称，一个能直接添加到屏幕上的 UI 称为 **Wnd**，而需要挂在其他 UI 上才能显示的称为 **Prefab**，Prefab 多为可复用组件。二者仅在概念上有区别，代码命名或资源命名上前缀均为 UI。

#### UIStore（Entity实体）

- UI 在脚本逻辑中会实例化为 UIStore，为了方便描述资源关系。
- UIStore 是一个壳，只简单存储父子 Store 之间的关系数据，所有逻辑数据根据功能需要封装成不同 Store，然后动态挂载到 UIStore 上。
- 每个 UIStore 会默认挂载 UMGBaseStore，用来存储 UMG 相关的基础数据。
- 如果一个 UIStore 是个可以打开的 Wnd，会默认挂载 WndBaseStore（额外的），用来存储 Wnd 相关的基础数据。
- 除了上述默认的 Store 之外，UIStore 创建时也会根据配置表中配置，对其他逻辑 Store 进行实例化并挂载。

#### WndManagerStore（存储了所有窗口UI--UIRootStore）

#### UIStoreSystem

管理 UIStore，负责构建 UIStore 和动态**创建挂载 Widget 控件相关的逻辑** Store，比如 Prefab、或者是**封装了操作的 ListView、TabBar** 等。

#### UMGBaseSystem

管理 UMGBaseStore，负责处理 UMG 资源相关的基础操作，如加载、卸载、添加至屏幕、屏幕上移除等。

#### WndManagerSystem

管理 WndBaseStore 和 WndManagerStore，负责处理窗口打开、关闭等 Action 操作，所有 Wnd 相关的概念会被封装在这些 Store 和 System 中，其他 UI 相关 Store、System 应避免出现 Wnd 概念。 

store权限管理，实现modify去修改内部，当store变化时，会通知其他地方，store产生了变化





## 其他信息

AD帐号 jiangjinduo 
AD密码 gN3cC7uA8a 
邮件地址 jiangjinduo@kingsoft.com 
SAP员工编号 00056399 
access token : glpat-if5bu4aKkGyevMRybGnE


提交：
git commit -m "feat: [UI]新建分支"

git reset --hard b7898831f6500e34ec1f29e88b2a75353ce55be4







