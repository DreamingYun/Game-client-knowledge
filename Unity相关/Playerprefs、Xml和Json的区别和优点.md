**Playerprefs、Xml和Json的区别和优点**

**PlayerPrefs（Unity内 置持久化存储类）**

using System;

using UnityEngine;

using UnityEngine.SocialPlatforms.Impl;

 

public class PlayerPrefsDemo : MonoBehaviour

{

​    private void Start()

​    {

​        //1.Unity提供的PlayerPrefs类，本地持久化存储

​        //一个Key对应一个值

​        //文件格式.plist

​        //存储 Int\Float\String

​        //存储不能同名，即使是不同数据类型

​        //同名的话，后者会覆盖前者

​        

​        //存储  Set ---SetInt\SetFloat\SetString

​        // PlayerPrefs.SetFloat("Score",100);

​        // Debug.Log("存储成功！");

​        

​        //读取  Get ---GetInt\GetFloat\GetString

​        // float value = PlayerPrefs.GetFloat("Score");

​        // Debug.Log(value);

​        

​        //尝试读取,如果没有就给一个默认值

​        // int value = PlayerPrefs.GetInt("Rank", 99);

​        // Debug.Log(value);

​        

​        //判断某个Key值是否存在

​        // bool haskey = PlayerPrefs.HasKey("Rank");

​        // Debug.Log(haskey);

​        

​    }

}



两种文档的读取方法在前面已经记录过，下面分析两者的区别

XML：

优点：可读性强

缺点：冗余信息多

JSON：

优点：数据实体转化为字符串和从一个字符串中解析出数据实体

缺点：不直观，不宜于查找







XML适用于建立游戏装备数据库，存储游戏装备数据，便于查找

通常这样的数据，大多是新建新的物体的时候，只用查找物体的ID（通常是数字）

对比游戏装备数据库，来建立和调用这个数据库里面相对应的内容

XML同样适用于游戏 小型数据类型的存储。



Unity3D中的数据持久化方案PlayerPrefs，则适用于 经常调用，

并且十分频繁的数据，像 药水、技能等（根据不同项目实际需要判断）



用于背包系统的调用

JSON适用于建立游戏存档，用于 存储/读取 游戏存档数据

这些游戏存档数据也是相当多，那么建立JSON存档文件的时候，

最好是建立相对应的 文件夹 ，在 一个 档案下 不同类型（地图，装备，）建立游戏存档文件

不同类型（地图，装备，）存档文件 根据实际需要 ，调整相关代码





XML（适合做配置文件，不经常修改和信息传输）

语法：

<?xml version="1.0" encoding="UTF-8" ?>

<!-- 注释 -->

<!--xml一般指可扩展标记语言，优点可读性强、缺点字符含量多-->

<!--最外面的标签称之为根标签-->

<AllStudnets>

​    <!--标签对、键值对-->

​    <Student Hobby="Pingpang" Lesson="math"> <!--属性-->

​        <StudentName>xiaoming</StudentName>

​        <StudentAge>18</StudentAge>

​        <!--单标签【在标签没有值的时候可以使用】-->

​        <SrudentAdress/>

​    </Student>

​    <!--标签的名字可以重复-->

​    <Student>

​        <StudentName>xiaohong</StudentName>

​        <StudentAge>19</StudentAge>

​        <!--标签可以用英文、中文和数字，但不能用符号-->

​        <学生籍贯>北京</学生籍贯>

​    </Student>

</AllStudnets>

生成 ：

using System;

using System.Xml;//关于xml操作的命名空间

using UnityEngine;

 

public class XMLGenarate : MonoBehaviour

{

​    private void Start()

​    {

​        //1.实例化xml文档对象

​        XmlDocument doc = new XmlDocument();

​        

​        //2.创建头文本节点--------------------------头文本节点

​        XmlDeclaration headText = doc.CreateXmlDeclaration("1.0", "UTF-8", "");//版本号，编码，平台

​        //将头文本节点添加到xml文档中

​        doc.AppendChild(headText);

​        

​        //3.创建根元素节点[GameObject]--------------根元素

​        XmlElement rootElement = doc.CreateElement("GameObject");

​        //创建属性节点

​        XmlAttribute layerAtt = doc.CreateAttribute("Layer");

​        //给属性节点赋值

​        //layerAtt.Value = gameObject.layer.ToString();

​        layerAtt.Value = LayerMask.LayerToName(gameObject.layer);

​        //给元素添加属性---方法1【Name】

​        rootElement.SetAttribute("Name", gameObject.name);

​        //给元素添加属性---方法2【Layer】

​        rootElement.SetAttributeNode(layerAtt);

​        //创建子节点【Transform】----------------子节点

​        XmlElement transformElement = doc.CreateElement("Transform");

​        //继续创建子节点---方法1【position】--------------子节点的子节点

​        XmlElement positionElement = doc.CreateElement("position");

​        //给元素节点设置值【文本节点】

​        positionElement.InnerText = transform.position.ToString();//Verctor3

​        //继续创建子节点【Rotation】--------------子节点的子节点

​        XmlElement rotationElement = doc.CreateElement("Rotation");

​        //给元素节点设置值【文本节点】

​        rotationElement.InnerText = transform.eulerAngles.ToString();//欧拉角

​        //继续创建子节点---方法2【LocalScale】------------子节点的子节点

​        XmlNode localScaleNode = doc.CreateNode(XmlNodeType.Element, "LocalSacle","");//节点类型

​        //给元素节点设置值【文本节点】

​        localScaleNode.InnerText = transform.localScale.ToString();

​        

​        //添加的时候最好是从里往外添加

​        //4.将position和rotation节点添加到transform节点上

​        transformElement.AppendChild(positionElement);

​        transformElement.AppendChild(rotationElement);

​        transformElement.AppendChild(localScaleNode);

​        //将transform节点添加到根元素节点GameObject节点上

​        rootElement.AppendChild(transformElement);

​        //将根元素节点添加到xml文档中

​        doc.AppendChild(rootElement);

​        

​        //5.保存文档

​        doc.Save(Application.dataPath + "/XMLs/GenaratedXML.xml");

 

​    }

}

解析： 

using System;

using System.Xml;

using UnityEngine;

 

public class XMLParse : MonoBehaviour

{

​    private void Start()

​    {

​        //创建一个xml文档对象

​        XmlDocument doc = new XmlDocument();

​        //读取xml文档

​        doc.Load(Application.dataPath + "/XMLs/GenaratedXML.xml");

​        //解析xml中的一个节点

​        XmlNode posNode = doc.SelectSingleNode("GameObject/Transform/Position");

​        Debug.Log(posNode.InnerText);

​        //解析xml的多个节点

​        XmlNodeList list = doc.SelectNodes("//Transform");

​        //遍历list中的所有节点

​        for (int i = 0; i < list.Count; i++)

​        {

​            Debug.Log("Position:" + list[i].ChildNodes[0].InnerText);

​            Debug.Log("Rotation:" + list[i].ChildNodes[1].InnerText);

​            Debug.Log("LocalScale:" + list[i].ChildNodes[2].InnerText);

​        }

​    }

}



JSON Demo

{

 "name": "中国"，

 "province": [ { "name": "黑龙江"， "citys": { "city": [ "哈尔滨"， "大庆" ] } }， { "name": "广东"， "citys": { "city": [ "广州"， "深圳"， "珠海" ] } }， { "name": "台湾"，

 "citys": { "city": [ "台北"， "高雄" ] } }， { "name": "新疆"， "citys": { "city": [ "乌鲁木齐" ] } } ]

}