#include<iostream>
#include<vector>
using namespace std;
//无参构造
vector<int> vec1;
//参数空间大小构造
vector<int> vec2(10);
//参数空间大小+内容构造
vector<int> vec3(10,1);
int main(){   
    vec1.push_back(1);
    cout<<vec1[0]<<endl;
    cout<<vec2.at(0)<<endl;
    vec1.push_back(2);
    cout<<"内存空间大小："<<vec1.capacity()<<endl;
    vec1.push_back(3);
    cout<<"内存空间大小："<<vec1.capacity()<<"插入三个元素空间翻倍成4了"<<endl;

    //中间插入，insert可能会导致扩容，需要返回新的迭代器继续使用
    //因为扩容是翻倍后把原先内容复制过来
    auto it=vec1.begin();
    cout<<"未插入的原地址"<<vec1.data()<<endl;
    it=vec1.insert(it+1,222);//1 222 2 3  //it现在在222的位置
    cout<<"插入222后的地址,四个元素未扩容，地址不变："<<vec1.data()<<endl;
    it=vec1.insert(it+1,333);//1 222 333 2 3 //it现在在333的位置
    cout<<"插入333后的地址,五个元素扩容成8，地址改变："<<vec1.data()<<endl;
    it=vec1.begin();//it现在在1的位置
    it=vec1.insert(it+1,444);//1 444 222 333 2 3 //it现在在444的位置

    for(auto it=vec1.begin();it!=vec1.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;

    vec1.erase(vec1.begin()+1);//删除444
    for(auto it=vec1.begin();it!=vec1.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    cout<<"空间大小"<<vec1.capacity()<<endl;//8
    cout<<"元素个数"<<vec1.size()<<endl;//5
    cout<<"_M_start:"<<vec1.data()<<endl;
    cout<<"_M_finish:"<<vec1.data()+vec1.size()<<endl;
    cout<<"_M_end:"<<vec1.data()+vec1.capacity()<<endl;

    //清理没用的空间
    vec1.shrink_to_fit();
    cout<<"清理没用的空间"<<endl;
    cout<<"空间大小"<<vec1.capacity()<<endl;//5
    cout<<"元素个数"<<vec1.size()<<endl;//5

    //clear清空元素+shrink_to_fit()清理没用的空间，完全清空
    vec1.clear();
    cout<<"清空元素"<<endl;
    for(auto it=vec1.begin();it!=vec1.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    cout<<"空间大小"<<vec1.capacity()<<endl;//5
    cout<<"元素个数"<<vec1.size()<<endl;//0
    vec1.shrink_to_fit();
    cout<<"清理没用的空间"<<endl;
    cout<<"空间大小"<<vec1.capacity()<<endl;//0

    return 0;
}