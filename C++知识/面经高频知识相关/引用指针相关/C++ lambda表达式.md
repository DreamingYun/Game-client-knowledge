int main() {

​    int a=9;

​    auto fun1=[=]{return ++a;};//代码片段1

​    auto fun2=[&]{return ++a;};//代码片段2

​    auto fun2=[=]()mutable{return ++a;};//代码片段3 

​    return 0;

}







代码片段1：auto fun1 = [=] { return ++a; };

 这里的 Lambda 表达式 fun1 捕获了外部变量 a，捕获方式是值捕获 [=]，表示使用外部变量 a 的值，但是不允许修改 a 的值。Lambda 表达式中的 ++a 尝试对 a 进行自增操作，但是由于使用了值捕获 [=]，编译器会报错，因为不能修改被值捕获的外部变量。



代码片段2：auto fun2 = [&] { return ++a; }; 

这里的 Lambda 表达式 fun2 同样捕获了外部变量 a，但捕获方式是引用捕获 [&]，表示使用外部变量 a 的引用，并且允许修改 a 的值。Lambda 表达式中的 ++a 对 a 进行自增操作，并且能够成功编译和执行，因为引用捕获允许修改被捕获变量。



代码片段3：auto fun3 =[=] mutable { return ++a; };

 这里的 Lambda 表达式 fun3 也是值捕获 [=]，但是使用了 mutable 关键字，表示可以修改被值捕获的外部变量。Lambda 表达式中的 ++a 对 a 进行自增操作，并且能够成功编译和执行，因为使用了 mutable 关键字允许修改被捕获变量。