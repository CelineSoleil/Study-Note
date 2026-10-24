/*
map基本原理

1.map是什么？
    -map<Key,Value>//键值对容器，key唯一，按key自动排序
    -底层：红黑树，每个节点存一个pair<const Key,Value>
    -核心特性：key一旦插入了就不能修改（会破坏排序），必须erase删除后重新插入。

2.内存结构
    vector：[1][2][3][4]一块连续内存，下标直达
    map:    8       离散节点，指针链接成树
         3    10    每个节点：key+value+左指针+右指针+父指针+颜色
        1 6     14  节点散落内存各处
    map没有vector的data()地址，capacity()容量,reserve()修改内存容量，map是节点new出来的

3.操作
    -访问：m[key]   时间复杂度：     logn 从上往下
    -插入：insert                   logn 找到位置+可能旋转修复
    -删除：erase                    logn 删除+旋转修复
    -查询：find/count(统计数量)      logn 
    -查询：lower_bound/upper_bound  logn 第一个>=key的元素，>key的元素，二分性质
    -遍历：                            n


注:
operator[]访问，先查找k，找到返回引用，否则insert一个(k，初始化)，在返回引用


二：unordered_map 哈希表
    -底层：哈希表（散列表）
    -核心思路通过哈希函数把key直接映射到数组下标，一步到位
key="apple" -> bash("apple") = 7 ->直接访问 数组[7]

理想情况下查找为O(1),与数据量无关

哈希冲突：不同key算出同一个下标（"apple"和"grape"都算出7）：
    -下标7：["apple"]->["grape"]->["peach"] 冲突解决方案：拉链表


三：map家族的其他容器
-1.multimap-key可重复的有序表
-2.set/unordered_set-只有key没用value

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!!!
-unordered_ 前缀=哈希表+无序+O(1)
-无前缀=红黑树+有序+O(logn)
-multi前缀=key可重复+无operator[]

四：选型决策树
要存键值对？
-需要按key有序遍历/范围查询——》map
-纯查找，数据量大，要速度——》unordered_map
-key会重复》——》multimap

只要判重/去重？
-顺便要排序——》set
-不排序——》unordered_set


*/

#include<map>
using namespace std;

int main(){
    map<int,int> ma;

    return 0;
}
