Socket（套接字）概念

​       Socket是应用层与TCP/IP协议族通信的中间软件抽象层，它是一组接口。在设计模式中，Socket其实就是一个门面模式，它把复杂的TCP/IP协议族隐藏在Socket接口后面，对用户来说，一组简单的接口就是全部，让Socket去组织数据，以符合指定的协议。　　

　    在使用Socket API编程时，需要重点先了解几个API，包括：socket()、bind()、connect()、listen()、accept()、send()和recv()、sendto()和recvfrom()、close()和shutdown()、getpeername()、gethostname()。这些接口是在Winsock2.h 中定义的不是在 MFC 中定义的，只需包含 Winsock2.h 头文件和 Ws2_32.lib 库就可以了。

　　 服务器端先初始化Socket，然后与端口绑定(bind)，对端口进行监听(listen)，调用accept阻塞，等待客户端连接。在这时如果有个客户端初始化一个Socket，然后连接服务器(connect)，如果连接成功，这时客户端与服务器端的连接就建立了。客户端发送数据请求，服务器端接收请求并处理请求，然后把回应数据发送给客户端，客户端读取数据，最后关闭连接，一次交互结束。

**1.3.1 客户端/服务端模式：**

　　在TCP/IP网络应用中，通信的两个进程相互作用的主要模式是客户/服务器模式，即客户端向服务器发出请求，服务器接收请求后，提供相应的服务。 **服务端**：建立socket，声明自身的端口号和地址并绑定到socket，使用listen打开监听，然后不断用accept去查看是否有连接，如果有，捕获socket，并通过recv获取消息的内容，通信完成后调用closeSocket关闭这个对应accept到的socket，如果不再需要等待任何客户端连接，那么用closeSocket关闭掉自身的socket。 　**客户端**：建立socket，通过端口号和地址确定目标服务器，使用Connect连接到服务器，send发送消息，等待处理，通信完成后调用closeSocket关闭socket。

Socket的英文原义是"孔"或"插座"。作为BSD UNIX的进程通信机制，取后一种意思。通常也称作"套接字"，用于描述IP地址和端口，是一个通信链的句柄，可以用来实现不同虚拟机或不同计算机之间的通信。在Internet上的主机一般运行了多个服务软件，同时提供几种服务。每种服务都打开一个Socket，并绑定到一个端口上，不同的端口对应于不同的服务。Socket正如其英文原义那样，像一个多孔插座。一台主机犹如布满各种插座的房间，每个插座有一个编号，有的插座提供220伏交流电， 有的提供110伏交流电，有的则提供有线电视节目。 客户软件将插头插到不同编号的插座，就可以得到不同的服务

Socket抽象层是存在于应用层（用户进程）和传输层（TCP和UDP）之间的。是一组接口，在设计模式当中把复杂的TCP/IP协议族隐藏在Socket接口之后。

Socket编程——TCP服务器/客户端简单通信实现步骤

TCP协议是面向连接的可靠传输，也就是计算机网络中所学的知识，TCP实现可靠传输靠的是三握手，TCP通信示意图如下



1）建立Socket，注意引用命名空间

Socket tcpServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);



2）绑定Bind()服务器端IP地址以及端口号——服务器端

IPAddress iPAddress = new IPAddress(new byte[] { 192, 168, 1, 3 });

EndPoint endPoint = new IPEndPoint(iPAddress, 8899);

tcpServer.Bind(endPoint);



3）利用Listen()方法开启监听——服务器端

tcpServer.Listen(100);

Console.WriteLine("开始监听");



4）利用Accept()方法尝试与客户端建立一个连接——服务器端

Socket client = tcpServer.Accept();

Console.WriteLine("-------有个客户端已连接--------");



5）利用Connect()方法与服务器建立连接——客户端

tcpClient.Connect(new IPEndPoint(IPAddress.Parse("192.168.1.3"), 8899));



6）利用Send()方法向建立连接的主机发送消息

string s = Console.ReadLine();

tcpClient.Send(Encoding.UTF8.GetBytes(s));



7）利用Receive()方法接受来自建立连接主机的消息（实现可靠连接）

byte[] data = new byte[1024];    //接收服务器传过来的信息

int length = tcpClient.Receive(data);   //传递信息的有效长度

string message = Encoding.UTF8.GetString(data, 0, length);

Console.WriteLine(message);



总的来说TCP通信大致就是六步，建立socket->绑定Bind->监听Listen->通过Accept()与客户端建立连接->客户端Connect()连接服务器->Send()给服务器发送消息->通过Receive()方法来建立连接，从而实现可靠传输。

Socket编程——UDP服务器/客户端简单通信实现步骤





UDP协议是无连接不可靠传输，实现的流程图如下

1）建立Socket，注意引用命名空间

Socket udpServer = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);



2）绑定Bind()服务器端IP地址以及端口号——服务器端

IPAddress iPAddress = new IPAddress(new byte[] { 192, 168, 1, 3 });

EndPoint endPoint = new IPEndPoint(iPAddress, 8899);

udpServer.Bind(endPoint);



3）通过SendTo()方法向建立连接的主机发送消息（需要提供IP地址及端口）

string message = Console.ReadLine();

udpServer.SendTo(Encoding.UTF8.GetBytes(message), new IPEndPoint(IPAddress.Parse("192.168.1.3"), 8899));



4）通过ReciveFrom()方法接收指定主机发送的消息（需要提供主机IP地址及端口）

byte[] data = new byte[1024];

EndPoint endPoint1 = new IPEndPoint(IPAddress.Any, 0);		//下一句要重新赋值的，所以先随便给一个

int length = udpServer.ReceiveFrom(data, ref endPoint1);	//ref是既进又出，out是只出不进

string message = Encoding.UTF8.GetString(data, 0, length);

Console.WriteLine(message + "-----ip:" + (endPoint1 as IPEndPoint).Address + "-----port:" + (endPoint1 as IPEndPoint).Port);









用死循环来传递消息的情况的话会有短暂的卡顿现象，但是用开启线程的方式来进行消息的传递的话并不会出现卡顿的现象。