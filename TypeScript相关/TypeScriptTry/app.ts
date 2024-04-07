//数据类型

//Boolean类型
var flag: boolean = false;

//Number类型
var age: number = 20;//整数
var float: number = 20.1;//浮点数

//String类型
var username: string = "Admin";
var str: string = "Hello World!";
var flags: string = "false";

//Array类型
var users: string[] = ["Lily", "Lucy", "Jetty"];
var list: Array<string> = ["ML", "Come", "On"];

//Enum类型
enum Color { Red, Green, Black };
var c: Color = Color.Red;
console.log(c);//0

enum Color1 { Red = 1, Green, Black };
var c1: Color1 = Color1.Red;
console.log(c1);//1

enum Color2 { Red = 1, Green = 2, Black = 3 };
var c2: string = Color2[2];
console.log(c2);//Green

//Any不确定类型
var notSure: any = 4;
notSure = false;
notSure = "Hello world!";

var anyList: any[] = ["hello", 1, false, ["JJD", "Come On"]];
anyList[0] = false;//anylist的any数组，本身不能是其他类型，但其中的值可以是any类型


//void类型
function a(): void {
    console.log(123);
}
a();

//类的创建
class Animal {
    //类的属性
    name: string;//（公有）
    private thisAge: number;

    //使用get和set访问器解决子类不能引用父类private修饰的属性的问题
    get Age(): number {
        return this.thisAge;
    }
    set Age(thisAge: number) {
        this.thisAge = thisAge;
    }

    //类的构造器
    constructor(name: string, thisAge: number) {
        this.name = name;
        this.thisAge = thisAge;
    }
    //类的方法
    sayHello(): void {
        console.log("Hello Animal" + this.name);
    }
}

var testAnimal = new Animal("Cat",6);
testAnimal.sayHello();


//类的继承
class Dog extends Animal {
    //重写父类的方法
    sayHello(): void {
        console.log("Hello Dog" + this.name + " " + this.Age);
    }
}


class Bird extends Animal {
    //重写父类的方法
    sayHello(): void {
        console.log("Hello Bird" + this.name + " " + this.Age);
    }
}

var testDog = new Dog("dogg", 7);
var testBird = new Bird("birdd", 8);
testDog.sayHello();
testBird.sayHello();



//静态属性
class Table {
    static width: Number = 100;
    static height: Number = 50;
}

var width: Number = Table.width;
console.log(width);


//接口
interface Graphic {
    width: Number;
    height: Number;
}

//类继承接口
class Square implements Graphic {
    //实现接口
    width: Number;
    height: Number;

    constructor() {
        this.width = 100;
        this.height = 100;
    }

}


//接口继承接口
interface penStroke {
    penWidth: Number;
}
interface Square extends Graphic, penStroke {
    sideLength: Number;
}


//模块
module JJDPlace {
    //export控制是否可以被外部访问
    export class Animal {
        private name: string;

        /*get name(): string {
            return this.name;
        }

        set name(name: string) {
            this.name = name;
        }*/

        constructor(name: string) {
            this.name = name;
        }
    }
}


//别名
module Shapes {
    export module AllShapes {
        export class Square { }
        export class Triangle { }
    }
}

import NowShapes = Shapes.AllShapes;//别名
var sq = new NowShapes.Square();
var tr = new NowShapes.Triangle();


//函数定义
function add(x: number, y: number): number {
    return x + y;
}

var myAdd = function (x: number, y: number): number {
    return x + y;
}

console.log(add(1, 2));
console.log(myAdd(1, 2));


console.log(1);//断点停住
