#include<iostream>
#include<string>
#include<memory>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

/*
auto tasks 推导出 std::unique_ptr<std::vector<Task>>；
make_unique 创建独占资源；
lambda 捕获 threshold；
const auto& 用于只读遍历；
auto& 用于修改任务；
nullptr 判断智能指针是否为空；
std::move 转移 unique_ptr 所有权。
*/

struct Task{
    string name;
    int priority;
};
void illustrate(){
        auto tasks=make_unique<vector<Task>>();

    tasks->push_back(Task{"学习 auto",1});
    tasks->push_back(Task{"学习 lambda",3});
    tasks->push_back(Task{"学习移动语义",2});

    int threshold=2;

    //lambda按值捕获 threshold
    auto isImportant =[threshold](const Task&task){
        return task.priority>=threshold;
    };

    cout<<"重要任务：\n";

    //只读遍历，使用const auto&
    for(const auto& task:*tasks){
        if(isImportant(task)){
        cout<<task.name<<",优先级："<<task.priority<<"\n";
        }
    }

    //给所有任务提高优先级
    for(auto& task:*tasks){
        task.priority++;
    }

    //转移unique_ptr的所有权
    auto newOwner=move(tasks);

    if(tasks==nullptr){
        cout<<"tasks已经转移所有权\n";
    }

    cout<<"任务总数："<<newOwner->size()<<"\n";
}


/*
练习一：auto 与范围 for
定义一个 std::vector<int>，完成：
使用范围 for 输出全部元素；
将所有偶数乘以 2；
不修改元素，计算总和。
要求分别使用 auto、auto&、const auto& 中合适的形式。
*/
void practice_one(){
    vector<int> ve{1,3,5,7,6,4,2,0};
    for(auto x:ve){
        cout<<x<<" ";
    }
    cout<<endl;
    for(auto &x:ve){
        if(x%2==0)x*=2;
    }
    int sum=0;
    for(const auto& x:ve){
        sum+=x;
    }
    cout<<sum;
}

/*
练习二：lambda
给定：
cpp
std::vector<int> numbers{3, 8, 12, 5, 20, 7};
使用 std::count_if 和 lambda，统计：
大于 10 的元素；
大于外部变量 threshold 的元素；
所有偶数。
*/
void practice_two(){
    vector<int> numbers{3, 8, 12, 5, 20, 7};
    auto count=count_if(numbers.begin(),numbers.end(),[](int x){return x>10;});
    cout<<"大于10的元素："<<count<<endl;
    int threshold=15;    
    count=count_if(numbers.begin(),numbers.end(),[threshold](int x){return x>threshold;});
    cout<<"大于threshold的元素："<<count<<endl;
    count=count_if(numbers.begin(),numbers.end(),[](int x){return x%2==0;});
    cout<<"所有偶数："<<count<<endl;
}

/*
练习三：智能指针
定义一个 Book 类，在构造函数和析构函数中输出提示：
cpp
class Book {
public:
    Book() {
        std::cout << "Book 构造\n";
    }

    ~Book() {
        std::cout << "Book 析构\n";
    }
};
分别创建：
unique_ptr<Book>；
两个共享同一对象的 shared_ptr<Book>；
一个观察该对象的 weak_ptr<Book>。
观察对象何时析构。
*/
class Book{
    public:
        Book(){
            cout<<"Book 构造\n";
        }
        ~Book(){
            cout<<"Book 析构\n";
        }
};
void practice_three(){
    // 独占拥有一个 Book
    auto ptr_unique = make_unique<Book>();

    weak_ptr<Book> ptr_weak;

    {
        // 两个 shared_ptr 共享另一个 Book
        auto ptr_shared1 = make_shared<Book>();
        auto ptr_shared2 = ptr_shared1;

        // weak_ptr 观察这个 Book，但不拥有它
        ptr_weak = ptr_shared1;
        cout << boolalpha;
        cout << "shared_ptr 数量："
             << ptr_shared1.use_count() << '\n';  // 2
        cout << "对象是否已经销毁："
             << ptr_weak.expired() << '\n';       // false
        // weak_ptr 通过 lock() 获得一个 shared_ptr
        if (auto locked = ptr_weak.lock()) {
            cout << "lock 成功，当前 shared_ptr 数量："
                 << locked.use_count() << '\n';   // 3
        }
        // locked 已离开 if 的作用域，强引用计数恢复为 2
        // ptr_shared1 放弃所有权
        ptr_shared1.reset();
        cout << "reset 后，ptr_shared2 的计数："
             << ptr_shared2.use_count() << '\n';  // 1

        cout << "对象是否已经销毁："
             << ptr_weak.expired() << '\n';       // false
    }
    // ptr_shared2 离开作用域，最后一个 shared_ptr 销毁
    // 它管理的 Book 在这里析构
    cout << "离开作用域后，对象是否已经销毁："
         << ptr_weak.expired() << '\n';           // true
    if (auto locked = ptr_weak.lock()) {
        cout << "lock 成功\n";
    } else {
        cout << "lock 失败，对象已经不存在\n";
    }
    // 函数结束时，ptr_unique 销毁，它管理的 Book 析构

}

/*
练习四：移动语义
编写一个 Buffer 类，分别给复制构造和移动构造输出提示：
Buffer(const Buffer& other) {
    std::cout << "复制构造\n";
}

Buffer(Buffer&& other) noexcept {
    std::cout << "移动构造\n";
}
然后比较：
cpp
Buffer b1;
Buffer b2 = b1;
Buffer b3 = std::move(b1);
进一步把对象放入 std::vector<Buffer>，观察 push_back 和扩容时的复制／移动行为。
*/
class Buffer{
public:
    Buffer(){}
    Buffer(const Buffer& other) {
        std::cout << "复制构造\n";
    }

    Buffer(Buffer&& other) noexcept {
        std::cout << "移动构造\n";
    }
    ~Buffer(){}
};
void practice_four(){
    cout << "=== 构造 b1、b2、b3 ===\n";

    Buffer b1;
    Buffer b2 = b1;             // 复制构造
    Buffer b3 = std::move(b1);  // 移动构造

    cout << "\n=== 放入 vector ===\n";

    vector<Buffer> ve;
    cout << "第一次 push_back(b1)：\n";
    ve.push_back(b1);           // 复制构造
    cout << "size = " << ve.size()
         << "，capacity = " << ve.capacity() << '\n';

    cout << "\n第二次 push_back(b2)：\n";
    ve.push_back(b2);           // 复制构造，并可能扩容
    cout << "size = " << ve.size()
         << "，capacity = " << ve.capacity() << '\n';

    cout << "\n第三次 push_back(b3)：\n";
    ve.push_back(b3);           // 复制构造，并可能再次扩容
    cout << "size = " << ve.size()
         << "，capacity = " << ve.capacity() << '\n';

    cout << "\n第四次 push_back(move(b3))：\n";
    ve.push_back(std::move(b3)); // 移动构造
    cout << "size = " << ve.size()
         << "，capacity = " << ve.capacity() << '\n';
}

int main(){
    //illustrate();
    //practice_one();
    //practice_two();
    //practice_three();
    //practice_four();
    return 0;
}
/*
验收清单
学完后，你应该能独立回答：
1.auto 是否会改变程序的静态类型特性？
2.为什么 auto value = x 默认不是引用？
3.范围 for 中，auto、auto&、const auto& 分别适合什么场景？
4.lambda 的捕获列表有什么作用？
5.为什么返回一个按引用捕获局部变量的 lambda 很危险？
6.unique_ptr 为什么不能复制？
7.shared_ptr 和 weak_ptr 的关系是什么？
8.nullptr 相比 NULL 有什么优势？
9.为什么说 std::move 本身不执行移动？
10.移动后的对象还能不能使用？
11.为什么返回局部变量时通常不写 return std::move(value)？

最重要的三条实践原则是：
遍历容器：只读常用 const auto&，修改使用 auto&。
动态资源：默认优先考虑 unique_ptr，不要滥用 shared_ptr。
只有源对象之后不再需要原值时，才使用 std::move；移动后不要依赖它的具体状态。

answer
1.auto 只是让编译器在编译期根据初始化表达式推导类型。推导完成后，变量类型就固定了，程序仍然是静态类型的。
2.auto value = x 按值推导并创建一个新对象，默认会去掉引用和顶层 const，所以通常是对 x 的复制。
3.
auto：复制元素，适合 int 等复制成本低的类型，或者确实需要独立副本时。
auto&：引用原元素，适合需要修改容器中元素的场景。
const auto&：只读引用，适合不需要修改元素，并且希望避免复制的场景。
4.捕获列表让 lambda 能够访问并使用它定义位置之外的局部变量，可以按值复制，也可以按引用访问。
5.局部变量在函数返回时会被销毁，但返回的 lambda 仍保存着对它的引用。之后调用 lambda，就会访问已经销毁的对象，形成悬空引用，产生未定义行为。
6.因为 unique_ptr 表示独占所有权。如果允许复制，就会出现两个 unique_ptr 都认为自己拥有同一个对象，销毁时可能重复释放资源。
7.shared_ptr 拥有对象并参与强引用计数；weak_ptr 观察由 shared_ptr 管理的对象，但不拥有它，也不会增加强引用计数。
8.nullptr 是类型安全的空指针字面量，类型为 std::nullptr_t，可以转换为各种指针类型，但不是整数；而 NULL 在某些实现中可能是整数 0，可能引发函数重载歧义。
9.std::move 本质上只是进行一次类型转换，把表达式转换成右值，从而允许调用移动构造函数或移动赋值运算符。真正转移资源的是这些函数。
10.移动后的对象仍然处于有效状态，但具体值通常是未指定的。可以销毁它、给它重新赋值，也可以调用不依赖原值的操作，但不要依赖它原来的内容。
11.返回局部对象时，编译器会按照语言规则尝试返回值优化；不能优化时，符合条件的局部对象也可以自动按移动处理。主动写 std::move 可能妨碍命名返回值优化，反而增加一次移动。
*/