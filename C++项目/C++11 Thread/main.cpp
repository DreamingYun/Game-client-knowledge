#include<iostream>
#include<thread>

void printHello(std::string msg) {
	std::cout << msg + "\n" << std::endl;
	for (int i = 0; i < 1000; i++) {
		std::cout << i << std::endl;
	}
}

int main() {
	//创建线程-以函数为基础
	std::thread thread1(printHello,"JJD is Great!");
	
	//严谨而言，要判断是否可以等待
	bool canJoin = thread1.joinable();
	if (canJoin) {
		//主线程会等待线程执行完再向下执行 - 否则不管执行完与否就向下结束程序
		thread1.join();
	}
	//分离进程，即使主线程停止，还是会让子线程继续在后台执行
	//thread1.detach();
	std::cout << "over！\n" << std::endl;

	return 0;
}