#include<iostream>
#include<thread>//线程库
#include<memory>//智能指针

//1、临时变量-引用变量
void testMistake(int& x) {
	x += 1;
}

//2、全局变量-地址
std::thread r;
int b = 1;//全局变量，其地址就会一直存在
void testThread() {
	//int b = 1;在这里是局部变量，就会导致函数运行结束，地址清楚，找不到传入的引用变量。数值会出现问题
	r = std::thread(testMistake, std::ref(b));
}
void testMistakePointer(int* x) {
	std::cout << *x << std::endl;//始终输出不确定数-已经报错，此处x变量是已经被清除的
}


//3、内存泄漏-即指针未被删除
class A {
private:
	friend void testMistakeClass();//作为友元，可以使用
	void testMismake() {
		std::cout << "Hello" << std::endl;
	}
};

void testMistakeClass() {
	//智能指针，使用完后自动删除内存
	std::shared_ptr<A> ptrA = std::make_shared<A>();
	std::thread y(&A::testMismake, ptrA);//传入引用
	y.join();
}


int main() {
	//1、临时变量-引用变量
	std::cout << "1:\n";
	int a = 1;
	//ref使得临时变量变为引用变量
	std::thread t(testMistake, std::ref(a));
	if(t.joinable()) t.join();
	std::cout << a << std::endl;//2

	//2、全局变量-地址
	std::cout << "2:\n";
	testThread();
	r.join();
	std::cout << b << std::endl;//2
	//展示错误，其实就是清除了内存
	int* aimptr = new int(1);
	std::thread showThread(testMistakePointer, aimptr);   
	delete aimptr;//手动释放内存
	showThread.join();

	//3、内存泄漏-即指针未被删除
	std::cout << "3:\n";
	testMistakeClass();

	return 0;
}