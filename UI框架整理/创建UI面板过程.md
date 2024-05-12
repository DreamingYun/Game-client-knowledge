先创建system（在其中可以包含store和system）

先不用import

0、创建好需要的文件夹，并且在index.ts中导入对应的文件

1、定义好当前UI的基础类型，名称和类型，以冒号对应（直接使用`ue-d-ts`json就可以自动生成，其类型不同只是取决于是否使用用户创建的控件，记得勾选是变量）位置`ue_bp.d.ts`

```ts
const UMGType = UT<UMG_UI_RoomList_C>;
```



2、定义好store存储/定义需要的数据类型，也可以去绑定逻辑控件

```ts
@D.store(EUITagDefine.UIRoomList)
class UIRoomListStore extends F.Store {
    @bind(ListViewStore)
    public List_Room!: Readonly<ListViewStore>;

    public refreshInterval: number = 0;
    public refreshTime: number = 0;
}
```

3、正式的逻辑写在system内部，在写之前需要依次进行以下操作

3.1、`UITagDefine.ts`中定义好tag，作为标识

3.2、`UIDefine.ts`中定义好名称

3.3、`AllUITemplates.ts`中结合tag和名称和特殊功能去设置好该UI

3.4、在system装饰器中参数列表填入对应参数



4、接着对对应的事件event、action分别写出protected的方法，当然也可以是按钮事件

```ts
@D.on(UIRoomListStore)
    protected onOpenWnd(event: OpenWndSEvent) {
        this.info(`[RoomList] ROOM LIST OPEN`);

        let store = event.getStore<UIRoomListStore>();
        ListViewUtil.init(store.List_Room, store);
        this.requestGetRoomList();
        this.resetRefreshTime();
        this.modify(this.getStore(), (v) => {
            v.refreshInterval = CommonData.getGameParam("RoomListInterval") as number;
            return true;
        });

        RegisterEscAction.do(store, UIRoomListStore);
        this.setL10NText(getRootWidget(store));
    }
```

强绑定了对应的UI，那么只会关心该UI的打开事件



5、事件

通用事件：event: OpenWndSEvent、action: EscActiveSAction、event: CloseWndSEvent

其他事件需要额外编写脚本

PublicAE中存放action，然后需要调用的时候

```ts
RequestGetRoomListAction.do();
```

一些通用事件，放在了整体的PublicAE中

```ts
export class OpenWndSEvent extends F.StoreEvent {
    public constructor(public params?: WndParams) {
        super();
    }
}
```





6、调用界面

```ts\
openWnd(EUIDefine.UIRankListMain);
```



7、子控件控制

```ts
@bind(ListViewStore)
    public List_Room!: Readonly<ListViewStore>;
```



```ts
ListViewUtil.setItems(store.List_Room, action.rooms);
```

来源于listview中Util.ts

listview同时设置有对应初始化和卸载的对应操作





define、system、index、（store可以放在system）



子控件可以单独进行操作，只是不能赋值。只需要找到一次基本控件就可以，并且设置好事件（完全仿照roomlist的蓝图进行）



8、Define.ts中定义好数据

例：来自服务器的数据，建立类



9、子控件

```ts
let store = event.getStore<UIRoomListItemStore>();
let widget = event.widget;//窗口
let data = event.data;//基础数据类型，具体data还要看
```



KFramework: Display: Standalone0: I WndSystem openWnd: Tag = UMG_UI_GameModeChoose
KFramework: Display: Standalone0: I WndSystem createWnd: Tag = UMG_UI_GameModeChoose
KFramework: Display: Standalone0: I UISystem buildUIStore: Tag=UMG_UI_GameModeChoose
KFramework: Display: Standalone0: create system by tag: UIGameModeChoose
KFramework: Display: Standalone0: I UISystem createUISystemByTag: tag=UIGameModeChoose
KFramework: Warning: Standalone0: [UI] 0ms, Load UMG /Game/Cooperation/UMG/Lobby/GameMode/UMG_UI_GameModeChoose.UMG_UI_GameModeChoose_C 
KFramework: Warning: Standalone0: [UI] 7ms, Load UMG /Game/Cooperation/UMG/Lobby/GameMode/UMG_UI_GameModeChoose.UMG_UI_GameModeChoose_C 
KFramework: Display: Standalone0: I UMGSystem **bindWidget**: name=UMG_UI_GameModeChoose
KFramework: Display: Standalone0: I UMGSystem addToViewport: name=UMG_UI_GameModeChoose
KFramework: Display: Standalone0: I UIGameModeChooseSystem [UIGameModeChoose] GAME MODE CHOOSE OPEN





KFramework: Display: Standalone0: I WndSystem openWnd: Tag = UMG_UI_PlayerMain
KFramework: Display: Standalone0: I WndSystem createWnd: Tag = UMG_UI_PlayerMain
KFramework: Display: Standalone0: I UISystem buildUIStore: Tag=UMG_UI_PlayerMain
KFramework: Display: Standalone0: create system by tag: UIPlayerMain
KFramework: Display: Standalone0: I UISystem createUISystemByTag: tag=UIPlayerMain
KFramework: Warning: Standalone0: [UI] 0ms, Load UMG /Game/Cooperation/UMG/Player/UMG_UI_PlayerMain.UMG_UI_PlayerMain_C 
KFramework: Warning: Standalone0: [UI] 5ms, Load UMG /Game/Cooperation/UMG/Player/UMG_UI_PlayerMain.UMG_UI_PlayerMain_C 
KFramework: Display: Standalone0: I UMGSystem **bindWidget**: name=UMG_UI_PlayerMain

KFramework: Display: Standalone0: I UISystem mountWidgetStore: widgetClassName=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UISystem buildUIStore: Tag=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: create system by tag: UIPlayerIcon
KFramework: Display: Standalone0: I UISystem createUISystemByTag: tag=UIPlayerIcon
KFramework: Display: Standalone0: I UMGSystem bindWidget: name=UMG_UI_PlayerIcon

KFramework: Display: Standalone0: I UISystem mountWidgetStore: widgetClassName=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UISystem buildUIStore: Tag=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UMGSystem bindWidget: name=UMG_UI_PlayerIcon

KFramework: Display: Standalone0: I UISystem mountWidgetStore: widgetClassName=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UISystem buildUIStore: Tag=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UMGSystem bindWidget: name=UMG_UI_PlayerIcon

KFramework: Display: Standalone0: I UISystem mountWidgetStore: widgetClassName=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UISystem buildUIStore: Tag=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UMGSystem bindWidget: name=UMG_UI_PlayerIcon

KFramework: Display: Standalone0: I UISystem mountWidgetStore: widgetClassName=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UISystem buildUIStore: Tag=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UMGSystem bindWidget: name=UMG_UI_PlayerIcon

KFramework: Display: Standalone0: I UISystem mountWidgetStore: widgetClassName=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UISystem buildUIStore: Tag=UMG_UI_PlayerIcon
KFramework: Display: Standalone0: I UMGSystem bindWidget: name=UMG_UI_PlayerIcon

KFramework: Display: Standalone0: I UMGSystem addToViewport: name=UMG_UI_PlayerMain
KFramework: Display: Standalone0: I UIPlayerMainSystem 1111

