#include<iostream>
#include<string>
#include<vector>//vector
#include<map>//map
#include<algorithm>//sort
#include<memory>//make_unique,shared_ptr
#include<utility>//move,swap,exchange
using namespace std;
/*
C++11/17核心特性

1.auto:让编译器推导类型
2.范围for：更整洁地遍历容器
3.lambda：在需要的位置直接定义匿名函数
4.智能指针：自动管理动态资源
5.nullptr：类型安全的空指针
6.move：转移资源，减少不必要的复制

*/

//1.auto：自主类型推导
//C++14可以推导函数返回类型
auto add(int a,int b){return a+b;}
//auto不是动态类型，变量类型任然会在编译期确定，只是由编译器根据初始化表达式推导。
void auto_main(){
//1.基本用法
    auto number=42;//int
    auto price=3.14;//double
    auto name=string("Name");//std::string

    vector<int>numbers{1,2,3,4};
    auto first=numbers[0];//int
    auto size=numbers.size();//通常是std::size_t

    cout<<number<<endl;
    cout<<price<<endl;
    cout<<name<<endl;
    cout<<first<<endl;
    cout<<size<<endl;
    //迭代器写法:下面俩种写法相同
    std::vector<int>::iterator it=numbers.begin();
    auto its=numbers.begin();
    /*
    auto特别适合：
        -类名很长
        -类型已经从右侧表达式清楚体现
        -使用模板、迭代器、lambda等不方便手写类型的场景
    */

//2.auto默认会忽略顶层const和引用
    int x=10;
    const int cx=20;
    auto a=x;//int
    auto b=cx;//int,不保留const
    //如果想要保留引用或const，要主动写出来:
    auto value=x;//int,复制x
    auto& ref=x;//int&,引用x
    const auto & cref=x;//const int&,只读引用
    ref=20;//修改x
    //cref=30;//报错只读不能修改
    /*
    常见三种用法：
    auto x=value       复制        需要独立副本
    auto& x=value      引用原对象   修改原来的值
    const auto& =value 只读引用     避免复制，只读取
    */

//3.不要对auto推导的类型想当然
    vector<int> numberss{1,2,3};
    auto c=numberss.size();//无符号整数类型
    auto d=0;//int
    //遍历容器下标时，可以使用：
    //1.std:size_t i
    for(std::size_t i=0;i<numberss.size();i++ ){
        cout<<numberss[i]<<" ";
    }
    cout<<endl;
    //2.auto i=std::size_t{0}
    for(auto i=std::size_t{0};i<numberss.size();i++){
        cout<<numberss[i]<<" ";
    }
    cout<<endl;

//4.花括号初始化的特殊之处
    auto aa=42;//int
    auto bb{42};//int
    auto cc={42};//std:initializer_list<int>
    //因此定义普通整数优先使用:
    auto value4=42;

//5.auto && 不一定是右值引用
    int expression=5;
    auto&& value5=expression;
    //他通常是转发引用，既可以绑定左值，也可以绑定右值，不能理解成简单的接收右值

//6.C++14/17中的拓展
    //1.C++14可以推导函数返回类型:auto add
    //2.C++17支持结构化绑定
    map<string,int>scores6{{"Alice",90},{"Bob",85}};
    auto [name6,score6] =*scores6.begin();
    cout<<name6<<" : "<<score6<<endl;

//7.使用原则：让代码更清楚，而不是让代码更短。
}

//2.范围for：简介遍历容器
void range_for(){
//1.基本格式
    vector<int>numbers{1,2,3,4};
    cout<<"传统写法:"<<"\n";
    for(std::size_t i=0;i<numbers.size();i++){
        cout<<numbers[i]<<" ";
    }
    cout<<endl;

    cout<<"范围for写法:"<<"\n";
    for(auto number:numbers){
        cout<<number<<" ";
    }
    cout<<"\n";
    //它表达的是：依次取出容器中的每个元素。

//2.值传递：修改的是副本，不会改变原来值
    cout<<"只是值传递，修改的副本，不改变原来值："<<"\n";
    for(int number:numbers){
        number*=2;
        cout<<number<<" ";
    }
    cout<<"\n";
    for(int number:numbers){
        cout<<number<<" ";
    }
    cout<<"\n";

//3.引用传递：修改原元素
    cout<<"引用传递，修改原元素:"<<"\n";
    for(auto& number:numbers){
        number*=2;
        cout<<number<<" ";
    }
    cout<<"\n";
    for(auto number:numbers){
        cout<<number<<" ";
    }
    cout<<"\n";

//4.只读遍历：优先使用const auto&
    cout<<"只读变量，优先使用const auto&:"<<"\n";
    vector<string>names4{"Alice","Bob","Charlie"};
    for(const auto&name:names4){
        cout<<name<<" ";
    }
    cout<<"\n";
    //这里使用引用，可以避免每次复制一个string

    /*
    范围 for 的选择规则：
    需求 	                        推荐写法 
    修改容器中的元素	            for (auto& item : container)
    只读取元素，且复制成本较高	     for (const auto& item : container)
    元素很小，只需要副本	         for (auto item : container)
    对于 int、double 等小类型，auto 和 const auto& 通常差别不大。
    */

//5.配合C++17结构化绑定遍历map
    map<string,int>scores5{{"Alice",90},{"Bob",85},{"Charlie",75}};
    for(const auto&[name,score]:scores5){
        cout<<name<<":"<<score<<"____";
    }
    cout<<"\n";
    for(auto&[name,score]:scores5){
        score+=5;//修改分数，整体+5//注意key值不能这样修改
        cout<<name<<":"<<score<<"____";
    }
    cout<<"\n";

//6.常见错误：遍历时随意增删元素，容易导致迭代器失效
    /*
    范围 for 内部仍然依赖迭代器。向 vector 中添加元素，可能引发重新分配，使正在使用的迭代器失效。
    核心原则：范围 for 适合遍历；遍历时修改容器结构，需要单独确认迭代器失效规则。
    */
}

//3.lambda:匿名函数
void anonymous_lambda(){

//1.基本语法
    /*
    [捕获列表](参数列表)->返回类型{
        函数体
    }
    */
    //简单示例
    auto sayHello=[]()->void{
    cout<<"Hello\n";
    };
    sayHello();
    //含参lambda
    auto add=[](int a,int b){return a+b;};
    cout<<add(2,3)<<"\n";

//2.为什么需要捕获列表：lambda外部局部变量，默认不能在函数体里直接使用
    int threshold=60;
    auto passed1=[](int score){
        return score>=60;
    };//也就是说，如果要用变量，必须有捕获
    //按值捕获：
    auto passed2=[threshold](int socre){
        return socre>=threshold;
    };
    cout<<passed1(80)<<"\n";
    cout<<passed2(80)<<"\n";
    //捕获相当于在创建 lambda 时，把需要的外部变量保存进去。

//3.按值捕获与按引用捕获
    //1.按值捕获[value]，捕获时复制当时的x
    cout<<"按值捕获[value]，捕获时复制当时的x:"<<"\n";
    int x=10;
    auto f3=[x](){cout<<x<<"\n";};
    x=20;
    f3();
    //2.按引用捕获[&value],使用的是原来的x
    x=10;
    cout<<"按引用捕获[&value],使用的是原来的x:"<<"\n";
    auto f33=[&x](){cout<<x<<"\n";};
    x=20;
    f33();

//4.常用捕获形式
    /*
    [=]        // 需要的外部局部变量按值捕获
    [&]        // 需要的外部局部变量按引用捕获
    [x]        // 只按值捕获 x
    [&x]       // 只按引用捕获 x
    [=, &x]    // 默认按值，但 x 按引用
    [&, x]     // 默认按引用，但 x 按值
    [this]     // 捕获当前对象的 this 指针

    初学：
    建议显式写出需要的变量，减少意外捕获：
    [threshold](int score) {
        return score >= threshold;
    }
    */

//5.mutable:修改按值捕获的副本
    //lambda默认不允许修改按值捕获的变量：
    int count5=0;
    auto f5=[count5]{
        //++count;//默认错误
    };
    //加上mutable
    auto f55=[count5]()mutable{
        ++count5;
        cout<<count5<<"\n";
    };
    f55();
    f55();
    cout<<"count5:"<<count5<<endl;//任然是0，lambda修改的是内部副本，不是外部

//6.配合标准库算法
    vector<int> numbers6{5,2,8,1,9};
    //直接完成cmp，不用再写一个
    cout<<"直接完成sort里面的cmp，不用多写一个函数:"<<"\n";
    sort(numbers6.begin(),numbers6.end(),[](int a,int b){return a>b;});
    for(const auto& number:numbers6){
        cout<<number<<" ";
    }
    cout<<"\n";

    cout<<"配合count计算大于阈值的元素个数：";
    int threshold6=4;
    auto count=count_if(numbers6.begin(),numbers6.end(),[threshold6](int value){return value>threshold6;});
    cout<<count<<endl;

//7.C++14：初始化捕获与泛型lambda
    //初始化捕获可以把表达式结构保存进lambda
    cout<<"初始化捕获可以把表达式结构保存进lambda:"<<"\n";
    auto f7=[threshold7=60,bonus7=5](int score){
        return score+bonus7>=threshold7;
    };
    //这也常用于把智能移动的对象捕获进lambda
    cout<<"这也常用于把智能移动的对象捕获进lambda:"<<"\n";
    auto ptr7 = std::make_unique<int>(42);
    auto f77=[ptr=std::move(ptr7)](){
        cout<<*ptr<<"\n";
    };
    f77();
    //泛型lambda使用auto参数：
    cout<<"泛型lambda使用auto参数："<<"\n";
    auto print=[](const auto& value){
        cout<<value<<'\n';
    };
    print(42);
    print(3.14);
    print("Hello");

//8.最重要的坑：悬空引用
    //错误示例：
    /*
    auto createFunction() {
    int x = 10;
        return [&x]() {
            std::cout << x << '\n';
        };
    }
    */
    //函数返回后，局部变量 x 已经销毁。返回的 lambda 再访问 x，就会产生未定义行为。

    /*
    核心原则：lambda 的生命周期可能比它捕获的局部变量更长。
    需要长期保存或返回时，尤其谨慎使用引用捕获。
    */
}

//4.智能指针：自动管理动态资源
//只使用对象、不接管所有权：
void printValue(const int& value){cout<<value<<'\n';}
//或者只观察指针：
void printPointer(const int*p){
    if(p!=nullptr){
        cout<<*p<<'\n';
    }
}
//需要接管所有权
void takeOwnership(std::unique_ptr<int>p){cout<<*p<<'\n';}
void intelligent_pointer(){
    //现代c++中，不应该把手动new/dekete作为常规资源管理方式
    int*p=new int(42);

    //中间如果提前return或者抛出异常可能忘记delete
    delete p;

    //智能指针利用对象生命周期自动释放资源，核心是 RAII：资源的生命周期与对象绑定。
    /*
    主要掌握三种：
    智能指针 	         所有权 	 典型用途 
    std::unique_ptr<T>	独占	    默认选择
    std::shared_ptr<T>	共享	    多方共同拥有
    std::weak_ptr<T>	不拥有	    观察对象、打破循环引用
    */
//必须包含头文件#include<memory>
//1.std::unique_ptr:独占所有权
    cout<<"-----------unique_ptr独占所有权："<<'\n';
    auto p1=std::make_unique<int>(42);
    cout<<*p1<<"\n";
    *p1=100;
    cout<<*p1<<"\n";
    //离开作用域后自动释放，不需要delete
    //注意make_unique是c++14引入，c++11可以写
    unique_ptr<int> p11(new int(42));

//!!不能复制，只能移动
    //auto p2=p1;//报错
    auto p2=std::move(p1);//转移所有权给p2
    if(p1==nullptr){
        cout<<"p1 不在拥有资源\n";
    }
    cout<<p2<<" : "<<*p2<<endl;
    //移动之后，p1通常为空，p2接管资源

//作为函数参数：只使用对象、不接管所有权
    cout<<"作为函数参数：只使用对象、不接管所有权:"<<'\n';
    printValue(*p2);
//或者只观察指针：
    cout<<"只观察指针："<<'\n';
    printPointer(p2.get());
//需要接管所有权：
    cout<<"接管所有权："<<'\n';
    takeOwnership(move(p2));
    /*
    使用原则
    默认优先使用 unique_ptr。
    不要用 .get() 得到的原始指针再 delete。
    原始指针可以临时观察对象，但不负责释放。
    容器可以存放 unique_ptr，插入时经常需要 std::move
    */

//2.std::shared_ptr:共享所有权
    cout<<"-----------shared_ptr可共享："<<'\n';
    
    auto p21=std::make_shared<int>(42);
    {
    auto p22=p21;//可以复制，共享同一个对象
    //use_count计算由多个shared_ptr共同拥有对象
    cout<<p21.use_count()<<'\n';//通常为2
    cout<<*p22<<'\n';
    }
    //p22已经销毁了
    cout<<p21.use_count()<<"\n";//为1

    /*
    最后一个拥有该对象的 shared_ptr 销毁时，对象才会释放。
    不要因为 shared_ptr 可以复制，就处处使用它：
    它有控制块和引用计数开销；
    共享所有权会让资源生命周期更难分析；
    多方相互持有时可能形成循环引用。
    只有确实需要共同拥有资源时，才使用 shared_ptr。
    */

//3.std::weak_ptr:不拥有对象
    cout<<"-----------weak_ptr不拥有对象："<<'\n';
    //weak_ptr 用来观察一个由 shared_ptr 管理的对象，但不会增加强引用计数。
    std::weak_ptr<int> weak;
    {
        auto shared=make_shared<int>(42);
        weak=shared;
        if(auto locked=weak.lock()){
            cout<<*locked<<'\n';
        }
    }
    //shared已销毁，对象已经释放
    if(weak.expired()){//weak.expired()：检查对象是否已经销毁
        cout<<"对象已经不存在\n";
        /*
        expired() == false：观察的对象目前还存在。
        expired() == true：观察的对象已经释放，或者这个 weak_ptr 本来就是空的。
        */
    }

    //访问前通常通过 lock() 提升为 shared_ptr：
    if (auto shared = weak.lock()) {//weak.lock()：尝试获得一个 shared_ptr
        // 在这个 if 内，对象保证继续存在
    } else {
        // 对象已经释放
    }
    /*
    weak_ptr 常用于：
    打破 shared_ptr 循环引用；
    缓存；
    观察者模式；
    需要检查对象是否仍然存在的场景。
    */
}

//5.nullptr:类型安全的空指针
void safety_empty_pointer(){
//1.基本用法：
    //C++11之前
    int *p1=0;
    int *p11=NULL;
    //现在推荐
    int *p111=nullptr;
    //判断
    if(p111==nullptr){
        cout<<"空指针"<<endl;
    }
//2.为什么不用NULL：
    //因为在某些实现中NULL就是整数0，可能参与错误的函数重载
    //nullptr 的类型是 std::nullptr_t，可以转换为各种指针类型，但不是整数。

//3.智能指针也可以与nullptr比较
    unique_ptr<int> p31;
    if(p31==nullptr){
        cout<<"p31 当前没有对象"<<'\n';
    }
    //注意：nullptr 只解决空指针的表示问题，不会自动防止悬空指针
}

//6.move:移动语义与资源转移
void move_main(){
//1.为什么需要移动语句
    //复制一个字符串或容器，可能需要复制其中的全部数据：
    string a(100000,'x');
    string b=a;//复制a和b都有独立的内容
    //如果a后面不使用了，可以把内部资源转移给b：
    std::string b1=std::move(a);
    //移动通常不是逐字符复制，而是让目标对象接管源对象的内部资源

//2.std::move本身不移动任何东西
    //这是最重要的一点
    //std::move(a);
        //本质上只是进行一次类型转换，表示：这个对象接下来可以被当作可移动对象处理，允许别人接管它的资源。
    //真正执行移动的是移动构造函数或移动赋值运算符
    string a21="Hello";
    string b21=move(a21);//调用移动构造函数

//3.复制与移动对比
    string a31="A very long string ...";
    string b31=a31;
    string c31=move(a31);

    cout<<"b31:"<<b31<<endl;
    cout<<"c31:"<<c31<<endl;
    //移动后不要再假设 a 仍然是原字符串。

    /*
    标准只保证：
    移动后的对象仍处于有效但未指定的状态。
    也就是说，通常可以：
    销毁它；
    给它重新赋值；
    调用不依赖具体值的操作。

    std::string a = "Hello";
    std::string b = std::move(a);
    // 不要假设 a 一定为空
    // std::cout << a.size();  // 可以运行，但结果不应被当作业务依据
    */

//4.左值和右值的直观理解
    //-左值：有明确身份，可以多次使用的对象。
    //-右值：临时值，即将消失的值。
    int x4=10;
    int a4=x4;//x是左值
    int b4=10+20;//10+20的结果可视为临时值

    /*
    容易混淆的一点：
    void f(std::string&& s) {
        // 虽然 s 的类型是右值引用，
        // 但 s 本身有名字，在表达式中是左值。

        // 如果希望继续移动它：
        std::string result = std::move(s);
    }
    所以“右值引用类型的变量”与“右值表达式”不是一回事。
    */

//5.移动智能指针
    auto p51=make_unique<int>(42);
    auto p52=move(p51);
    //p51不在拥有对象
    //p52负责管理对象
    /*
    这正体现了 unique_ptr 的设计：
    不能复制所有权；
    可以明确转移所有权。
    */

//6.向容器中移动对象
    std::vector<std::string> words6;
    std::string word6 = "Hello";
    words6.push_back(word6);             // 复制，word 后文还可使用
    words6.push_back(std::move(word6));  // 移动，之后不再依赖 word 的原值
    cout<<word6<<endl;
    for(auto x:words6){
        cout<<x<<" ";
    }
    cout<<"\n";
    //不要对仍需保留原值的对象随意使用 std::move。

//7.不要对 const 对象期待移动
    const std::string a7 = "Hello";
    std::string b7 = std::move(a7);  // 通常仍然只能复制
    //因为移动需要修改源对象的内部状态，而 const 对象不能被这样修改。

//8.函数返回时，通常不要主动写 std::move
    /*
    std::string createString() {
        std::string result = "Hello";
        return result;  // 推荐
    }
    不推荐：
    std::string createString() {
        std::string result = "Hello";
        return std::move(result);  // 可能妨碍返回值优化
    }

    对于返回局部对象，编译器会按照语言规则进行返回值优化或移动处理。主动写 std::move 往往没有好处。
    C++17 还保证了某些纯右值场景的复制省略：
    std::string createString() {
        return std::string("Hello");
    }
    这里从临时结果初始化返回对象，C++17 保证不会额外调用复制或移动构造函数。
    但命名局部变量的 NRVO（命名返回值优化）仍不属于绝对保证，因此两种情形要区分。
    
    */

//9.移动构造函数与noexcept
    //一个支持移动的类型，通常会提供：
    /*
    ClassName(ClassName&& other) noexcept;
    ClassName& operator=(ClassName&& other) noexcept;
    */
    /*
    移动构造函数负责：
    接管源对象的资源；
    把源对象置于有效状态；
    避免资源被重复释放。

    noexcept 很重要。例如 std::vector 扩容时，如果类型的移动操作保证不抛异常，
    通常更愿意使用移动；否则可能为了保证异常安全而使用复制。
    */


}

int main(){
    //auto_main();
    //range_for();
    //anonymous_lambda();
    //intelligent_pointer();
    //safety_empty_pointer();
    //move_main();
    return 0;
}
