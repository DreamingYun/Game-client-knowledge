lua没有办法直接访问C#，一定是先从C#中调用Lua脚本后，才会把核心逻辑交给lua来编写，输入main文件作为主入口来启动lua脚本

public class Main : MonoBehaviour

{

​    void Start()

​    {

​        LuaManager.GetInstance().Init();

​        LuaManager.GetInstance().DoLuaFile("Main");

​    }

}



**类**

1.模板 CS.命名空间.类名

2.lua中没有new，所以直接用类名加上括号就是在实例化一个对象（相当于是无参的构造）-- CS.命名空间.类名；local obj1 = CS.UnityEngine.GameObject()

local obj2 = CS.UnityEngine.GameObject("em")

3.但是每次都要加上类名会比较麻烦，所以可以使用全局变量去存储C#中的类

，相当于起了别名，也会形成便利的使用

GameObject = CS.UnityEngine.GameObject

local obj3 = GameObject("冲冲冲")

Debug也可以调用

Debug = CS.UnityEngine.Debug

Debug.Log(obj4.transform.position)--(0.00, 0.00, 0.00)

4.类中的静态方法也可以直接调用，在得到了对象之后，直接对象 . 就可以得到对象中的成员变量，也就可以使用相关API

local obj4 = GameObject.Find("em")

print(obj4.transform.position)

5.如果要使用对象中的成员方法，一定要加上：

Vector3 = CS.UnityEngine.Vector3

obj4.transform:Translate(Vector3.right)

Debug.Log(obj4.transform.position)--(1.00, 0.00, 0.00)

6.使用自定义类就需要先实例化出对象，然后才能使用类中的成员方法。如果要使用在命名空间内的方法，就使用命名空间 . 即可

C#中自定义类

public class Test1ForLua

{

​    public void Speak(string str)

​    {

​        Debug.Log("Test1"+str);

​    }

}

namespace JJD

{

​    public class Test2ForLua

​    {

​        public void Speak(string str)

​        {

​            Debug.Log("Test2"+str);

​        }

​    }

}

Lua中调用类

local t1 = CS.Test1ForLua()

t1:Speak("t1在说话")--Test1t1在说话

local t2 = CS.JJD.Test2ForLua()

t2:Speak("t2在说话")--Test2t2在说话



7.继承了Mono的类，首先是不能直接new的，要通过GameObject的AddComponent来添加脚本。

xlua中是不支持无参泛型函数的，所以要使用另一个AddComponent的重载，并且使用xlua的一个API--typeof（反射）来获取到类（脚本）的Type（与重载对应）

local obj5 = GameObject("加脚本测试")

obj5:AddComponent(typeof(CS.LuaCallCSharp))