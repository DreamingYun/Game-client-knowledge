**AssetBundle**

AssetBundle和Resource API一样也是通过将资源打包，然后从包中加载资源，但与Resource API不同的是，AssetBundle可以指定打包的路径，而Resource API是直接将资源包与应用程序绑定。当系统需要使用



某个资源包时AssetBundle**才将该资源包加载进内存**。AssetBundle的使用流程比较繁琐，大致上分为五个阶段：分组、打包、加载包、加载资源、卸载包。 

(1) 分组：分组就是将资源按照**特定的分组策略**将资源归类，这些类型在打包阶段会生成各自的资源包，AssetBundle分组需要考虑一些关键因素包括：**资源之间的关联性**（尽量将相互依赖的资源**放在一个资源包**内）、资源动态性（尽量将需要频繁加载的资源放在一个资源包内）、资源大小（尽量不要将大资源和小资源放在一个资源包内）、版本管理（Variable是对资源包的进一步分组，比如资源包的不同版本，当设置了不同的Variable，AssetBundle将会对变体进行单独打包）。

(2) 打包：通过Unity内置的BuildPipeline API可以实现将设置分组的资源进行打包，具体的打包流程包括： (a) 遍历AssetBundle分组：Unity会**遍历**每个已设置的**AssetBundle分组**。 (b) 查找分组中的资源和依赖项：对于每个分组，Unity会查找分组中的**资源及其依赖项**，并创建一个**资源清单**。 (c) 序列化资源和依赖项：Unity会将这些资源和依赖项进行**序列化**，并将它们保存到一个**二进制文件**中，以供**加载时使用**。 (d) 生成资源包文件：通过将**资源清单**和**序列化的资源**打包成二进制文件，Unity生成一个包含所有资源的**AssetBundle文件**。 (e) **压缩和加密（可选）**：可以选择对生成的AssetBundle文件进行压缩和加密，以确保资源的安全性和网络传输效率。

(3) 加载包：经过打包后，资源包**并没有被加载**进内存，通过**AssetBundle API**可以将**资源包加载进**内存。 

(4) 加载资源：通过**资产包在内存中的对象**来加载包中的资源。

(5) 卸载资源：当资源被加载进内存后，**资源就由应用程序接管，就可以从内存中卸载**了。 AssetBundle允许将**资源按需打包**，减小了项目的初始包体大小，提高了加载性能和启动速度。它使得可以在**运行时动态加载和卸载资源**，提供了更灵活的资源管理机制。除此之外可以**针对不同平台和版本进行打包**，以适配不同的环境。这使得在不同的平台上共享和部署资源更加方便和高效。由于AssetBundle可以单独打包和加载，**可以实现独立的资源更新和替换**，而无需重新发布整个应用程序。这样可以**节省更新**和发布的时间和带宽。 虽然AssetBundle有上述诸多优点，但是AssetBundle的使用对开发者很不友好，首先所有资源都要手动分组就增加了开发人员的工作量和复杂性。另外资产包内的资源之间存在相互依赖关系，如果被依赖的资产包未被加载，那么依赖的资源就无法使用，也进一步增加了使用者的工作量和复杂性。因此，是否决定要使用AssetBundle还需要慎重考虑。



 Addressable

鉴于AssetBundle的局限性，Unity进一步在AssetBundle API的基础上开发了Addressable。Addressable可在 Unity 编辑器中为开发者**提供用户界**面，并自动执行以前只能在脚本中手动管理的流程。使用Addressable系统，开发者可以在 **Unity 编辑器中组织资源**，并让**系统处理**依赖项、资源位置以及内存分配和解除分配。 资源（例如预制体）被标记为“可寻址”后，就会**为该资源生成一个全局地**址，系统可在任何地方通过该全局地址定位该资源。该地址是**可寻址对象系统与资产位置关联**的字符串标识符，无论该资产是驻留在您构建的游戏本地还是**内容交付网络**上。在脚本中，开发者可以使用**资产的地址**，而不是跟踪其位置，这样就不必编写指定位置的代码。 如果资产位置发生更改，也无需重写代码。 当运行Addressable系统时，Addressable会先利用AssetBundle构建资源包





**Unity实现动态资源加载的4种方式**



使用unity开发游戏的过程中，资源的加载一直都是需要重点关注的。unity一共提供了5种资源加载的方式，分别是

Resources（只能加载Resources目录中的资源）

AssetDatabase（只能加载Assets目录下的资源，但只能用于Editor）

AssetBundle（只能加载AB资源，当前设备允许访问的路径都可以）

WWW（可以加载任意处资源，包括项目外资源（如远程服务器））

UnityWebRequest（可以加载任意处资源，是WWW的升级版本）







Resouces方式：

T load = Resources.Load<T>(path);



AssetDatabase方式：

T load = AssetDatabase.LoadAssetAtPath<T>(path);



WWW方式：

Debug.Log("----WWW协程调用----");

​        //string url = string.Format(@"file://{0}/{1}.jpg", Application.streamingAssetsPath, Index.ToString());

​        WWW www = new WWW(url);

​        yield return www;

​        callback.Invoke(www);

​        yield return null;



UnityWebRequest方式：

   UnityWebRequest request = obj as UnityWebRequest;

​        Texture2D tex = DownloadHandlerTexture.GetContent(request);

​        BG.sprite = Sprite.Create(tex, new Rect(0, 0, tex.width, tex.height), Vector2.zero);

​        request.Dispose();