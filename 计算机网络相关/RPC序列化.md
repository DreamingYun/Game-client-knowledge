**RPC（详细讲序列化）**



**什么是RPC协议？**

远程过程调用（Remote Procedure Call，RPC）是一种计算机通信协议。它允许一个计算机程序在另一台计算机上执行代码，而不需要程序员显式编写网络代码。RPC协议的实现可以使分布式计算更加容易和透明。

RPC协议的核心是一个客户端和一个服务端，它们可以运行在不同的机器上。客户端调用服务端的某个函数，服务端执行该函数并返回结果。客户端可以像调用本地函数一样调用远程函数，而不需要知道底层的网络细节。

**如何实现RPC协议？**

RPC协议的实现通常包括以下几个步骤：

定义接口。客户端和服务端需要共同定义一套接口，描述函数的输入参数和返回值。

生成代理代码。客户端需要生成一个代理，它可以将函数调用转换成网络消息，并将结果返回给客户端。

序列化和反序列化。客户端和服务端之间需要将数据序列化成网络字节流，以便进行传输。收到数据后，需要将其反序列化成可读的数据格式。

网络传输。客户端和服务端之间需要进行网络传输，以便进行数据交换。

调用远程函数。客户端通过代理调用服务端的函数，服务端执行该函数并返回结果。

返回结果。服务端将执行结果序列化后发送给客户端，客户端将其反序列化成可读的数据格式。

RPC协议的优点在于它可以隐藏底层的网络细节，使分布式计算更加容易和透明。但是，RPC协议也存在一些缺点。首先，RPC协议的实现通常需要复杂的代码生成和序列化反序列化操作。其次，RPC协议的性能可能不如本地函数调用，因为它需要进行网络传输和序列化反序列化操作。



JDK原生序列化

案例：

import java.io.*;

public class Student implements Serializable {

​    //学号

​    private int no;

​    //姓名

​    private String name;

​    public int getNo() {

​        return no;

​    }

​    public void setNo(int no) {

​        this.no = no;

​    }

​    public String getName() {

​        return name;

​    }

​    public void setName(String name) {

​        this.name = name;

​    }

​    @Override

​    public String toString() {

​        return "Student{" +

​                "no=" + no +

​                ", name='" + name + '\'' +

​                '}';

​    }

​    public static void main(String[] args) throws IOException, ClassNotFoundException {

​        String home = System.getProperty("user.home");

​        String basePath = home + "/Desktop";

​        FileOutputStream fos = new FileOutputStream(basePath + "student.dat");

​        Student student = new Student();

​        student.setNo(100);

​        student.setName("TEST_STUDENT");

​        ObjectOutputStream oos = new ObjectOutputStream(fos);

​        oos.writeObject(student);

​        oos.flush();

​        oos.close();

​        FileInputStream fis = new FileInputStream(basePath + "student.dat");

​        ObjectInputStream ois = new ObjectInputStream(fis);

​        Student deStudent = (Student) ois.readObject();

​        ois.close();

​        System.out.println(deStudent);

​    }

}

序列化具体由ObjectOutputStream完成

反序列化的具体实现是由ObjectInputStream完成

JDK序列化过程：

序列化过程就是在读取对象数据的时候，不断加入一些特殊分隔符，这些特殊分隔符用于在反序列化过程中截断用。

头部数据，声明序列化协议、序列化版本，用于高低版本向后兼容

对象数据主要包括类名、签名、属性名、属性类型及属性值，当然还有开头结尾等数据，除了属性值属于真正的对象值，其他都是为了反序列化用的元数据

存在对象引用、继承的情况下，就是递归遍历“写对象”逻辑

将对象的类型、属性类型、属性值按固定格式写到二进制字节流中来完成序列化，再按固定格式读出对象的类型、属性类型、属性值，通过这些信息重建一个新的对象，完成反序列化。



JSON

典型KV方式，没有数据类型，是一种文本型序列化框架。

JSON进行序列化的额外空间开销较大

JSON没有类型，但像Java这种强类型语言，需通过反射统一解决，性能不太好

所以如果RPC框架选用JSON序列化，服务提供者与服务调用者之间传输的数据量要相对较小。





 Hessian

动态类型、二进制、紧凑的，并且可跨语言移植的一种序列化框架。比JDK、JSON更加紧凑，性能上要比JDK、JSON序列化高效很多，而且生成的字节数更小。

使用代码示例如下：

Student student = new Student();

student.setNo(101);

student.setName("HESSIAN");

//把student对象转化为byte数组

ByteArrayOutputStream bos = new ByteArrayOutputStream();

Hessian2Output output = new Hessian2Output(bos);

output.writeObject(student);

output.flushBuffer();

byte[] data = bos.toByteArray();

bos.close();

//把刚才序列化出来的byte数组转化为student对象

ByteArrayInputStream bis = new ByteArrayInputStream(data);

Hessian2Input input = new Hessian2Input(bis);

Student deStudent = (Student) input.readObject();

input.close();

System.out.println(deStudent);

相对于JDK、JSON，由于Hessian更加高效，生成的字节数更小，有非常好的兼容性和稳定性，所以Hessian更加适合作为RPC框架远程通信的序列化协议。

但Hessian本身也有问题，官方版本对Java里面一些常见对象的类型不支持，比如：

Linked系列，LinkedHashMap、LinkedHashSet等，但是可以通过扩展CollectionDeserializer类修复

Locale类，可以通过扩展ContextSerializerFactory类修复

Byte/Short反序列化的时候变成Integer



**Protobuf**

Protobuf 是 Google 公司内部的混合语言数据标准，是一种轻便、高效的结构化数据存储格式，可以用于结构化数据序列化，支持Java、Python、C++、Go等语言。Protobuf使用的时候需要定义IDL（Interface description language），然后使用不同语言的IDL编译器，生成序列化工具类，它的优点是：

序列化后体积相比 JSON、Hessian小很多；

IDL能清晰地描述语义，所以足以帮助并保证应用程序之间的类型不会丢失，无需类似 XML 解析器；

序列化反序列化速度很快，不需要通过反射获取类型；

消息格式升级和兼容性不错，可以做到向后兼容。

使用代码示例如下：

/**

 *

 \* // IDl 文件格式

 \* synax = "proto3";

 \* option java_package = "com.test";

 \* option java_outer_classname = "StudentProtobuf";

 *

 \* message StudentMsg {

 \* //序号

 \* int32 no = 1;

 \* //姓名

 \* string name = 2;

 \* }

 \* 

 */

 

StudentProtobuf.StudentMsg.Builder builder = StudentProtobuf.StudentMsg.newBuilder();

builder.setNo(103);

builder.setName("protobuf");

//把student对象转化为byte数组

StudentProtobuf.StudentMsg msg = builder.build();

byte[] data = msg.toByteArray();

//把刚才序列化出来的byte数组转化为student对象

StudentProtobuf.StudentMsg deStudent = StudentProtobuf.StudentMsg.parseFrom(data);

System.out.println(deStudent);



Protobuf 非常高效，但是对于具有反射和动态能力的语言来说，这样用起来很费劲，这一点就不如Hessian，比如用Java的话，这个预编译过程不是必须的，可以考虑使用Protostuff。

Protostuff不需要依赖IDL文件，可以直接对Java领域对象进行反/序列化操作，在效率上跟Protobuf差不多，生成的二进制格式和Protobuf是完全相同的，可以说是一个Java版本的Protobuf序列化框架。但在使用过程中，我遇到过一些不支持的情况，也同步给你：

不支持null；

ProtoStuff不支持单纯的Map、List集合对象，需要包在对象里面。