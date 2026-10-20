#include<iostream>
#include<map>
using namespace std;


int main(){

    map<string,int> ma1;//空构造
    map<string,int> ma2={{"apple",3},{"banana",2}};//初始化列表c++11

    //插入
    ma1.insert({"orenge",1});
    ma1.insert({"orenge",5});//1.insert,key存在则什么都不会做
    ma1.insert(make_pair("grape",4));//2.
    ma1["peach"]=8;//3.operator[],如果key存在则覆盖值
        //区别insert不覆盖旧的值，operator[]会覆盖
    
    //访问
    cout<<ma1["peach"]<<endl;//8
    cout<<ma1["ghost"]<<endl;//0 !!!如果ghost不存在会插入，并且复制为0，size++

    //-安全访问:先判断是否存在，在输出，也可以count计数判断
    auto it=ma1.find("apple");
    if(it!=ma1.end()){
        cout<<it->first<<" = "<<it->second<<endl;
    }
    else{
        cout<<"不存在"<<endl;
    }
    
    if(ma1.count("apple")){//存在
    }

    //修改值
    ma1["peach"]=99;//改value值
    //key不能改，如果想换key要删了重新插入

    //删除
    ma1.erase("grape");//按key删除
    ma1.erase(ma1.begin());//按迭代去删除，如：第一个

    //遍历C++17
    for(auto&[key,val]:ma1){
        cout<<key<<" : "<<val<<endl;
    }
    
    //有序性相关的操作
    auto itlower=ma1.lower_bound("b");
    auto itupper=ma1.upper_bound("b");
    if(itlower!=ma1.end())
    cout<<"lower_bound:第一个>=b的迭代器:"<<itlower->first<<" "<<itlower->second<<endl;
    if(itupper!=ma1.end())
    cout<<"upper_bound:第一个>b的迭代器:"<<itupper->first<<" "<<itupper->second<<endl;

    
    return 0;
}