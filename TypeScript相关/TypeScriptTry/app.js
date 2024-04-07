"use strict";
//数据类型
//Boolean类型
var flag = false;
//Number类型
var age = 20; //整数
var float = 20.1; //浮点数
//String类型
var username = "Admin";
var str = "Hello World!";
var flags = "false";
//Array类型
var users = ["Lily", "Lucy", "Jetty"];
var list = ["ML", "Come", "On"];
//Enum类型
var Color;
(function (Color) {
    Color[Color["Red"] = 0] = "Red";
    Color[Color["Green"] = 1] = "Green";
    Color[Color["Black"] = 2] = "Black";
})(Color || (Color = {}));
;
var c = Color.Red;
console.log(c); //0
var Color1;
(function (Color1) {
    Color1[Color1["Red"] = 1] = "Red";
    Color1[Color1["Green"] = 2] = "Green";
    Color1[Color1["Black"] = 3] = "Black";
})(Color1 || (Color1 = {}));
;
var c1 = Color1.Red;
console.log(c1); //1
var Color2;
(function (Color2) {
    Color2[Color2["Red"] = 1] = "Red";
    Color2[Color2["Green"] = 2] = "Green";
    Color2[Color2["Black"] = 3] = "Black";
})(Color2 || (Color2 = {}));
;
var c2 = Color2[2];
console.log(c2); //Green
//Any不确定类型
var notSure = 4;
notSure = false;
notSure = "Hello world!";
var anyList = ["hello", 1, false, ["JJD", "Come On"]];
anyList[0] = false; //anylist的any数组，本身不能是其他类型，但其中的值可以是any类型
//void类型
function a() {
    console.log(123);
}
a();
//类的创建
class Animal {
    //使用get和set访问器解决子类不能引用父类private修饰的属性的问题
    get Age() {
        return this.thisAge;
    }
    set Age(thisAge) {
        this.thisAge = thisAge;
    }
    //类的构造器
    constructor(name, thisAge) {
        this.name = name;
        this.thisAge = thisAge;
    }
    //类的方法
    sayHello() {
        console.log("Hello Animal" + this.name);
    }
}
var testAnimal = new Animal("Cat", 6);
testAnimal.sayHello();
//类的继承
class Dog extends Animal {
    //重写父类的方法
    sayHello() {
        console.log("Hello Dog" + this.name + " " + this.Age);
    }
}
class Bird extends Animal {
    //重写父类的方法
    sayHello() {
        console.log("Hello Bird" + this.name + " " + this.Age);
    }
}
var testDog = new Dog("dogg", 7);
var testBird = new Bird("birdd", 8);
testDog.sayHello();
testBird.sayHello();
//静态属性
class Table {
}
Table.width = 100;
Table.height = 50;
var width = Table.width;
console.log(width);
//类继承接口
class Square {
    constructor() {
        this.width = 100;
        this.height = 100;
    }
}
//模块
var JJDPlace;
(function (JJDPlace) {
    //export控制是否可以被外部访问
    class Animal {
        /*get name(): string {
            return this.name;
        }

        set name(name: string) {
            this.name = name;
        }*/
        constructor(name) {
            this.name = name;
        }
    }
    JJDPlace.Animal = Animal;
})(JJDPlace || (JJDPlace = {}));
//别名
var Shapes;
(function (Shapes) {
    let AllShapes;
    (function (AllShapes) {
        class Square {
        }
        AllShapes.Square = Square;
        class Triangle {
        }
        AllShapes.Triangle = Triangle;
    })(AllShapes = Shapes.AllShapes || (Shapes.AllShapes = {}));
})(Shapes || (Shapes = {}));
var NowShapes = Shapes.AllShapes; //别名
var sq = new NowShapes.Square();
var tr = new NowShapes.Triangle();
//函数定义
function add(x, y) {
    return x + y;
}
var myAdd = function (x, y) {
    return x + y;
};
console.log(add(1, 2));
console.log(myAdd(1, 2));
console.log(1); //断点停住
//# sourceMappingURL=app.js.map