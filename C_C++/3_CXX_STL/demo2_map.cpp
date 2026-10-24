#include<map>
#include<unordered_map>
#include<iostream>
#include<set>
#include<vector>
using namespace std;

void word_find(){    
    string word="hello world,i love you,my body,my eyes,my hands.my herat";
    map<string,int> sum;
    string a;
    for(int i=0;i<=word.size();i++){//故意多走一格
        // if(('a'<=word[i] && word[i]<='z')||('A'<=word[i]&&word[i]<='Z')){
        //     a+=word[i];
        // }
        if(i<word.size()&&isalpha(word[i])){
            a+=tolower(word[i]);
        }
        else if(!a.empty()){
           sum[a]++;
           a="";
        }
    }

    for(auto& [k,v]:sum){
        cout<<k<<" 出现: "<<v<<" 次 "<<endl;
    }
}

void map_or_unorderedmap(){
    map<string,int> ma;
    unordered_map<string,int> uma;
    ma.insert({"one",1});
    ma.insert({"two",2});
    ma.insert({"three",3});
    ma.insert({"four",4});
    ma.insert({"five",5});

    uma.insert({"one",1});
    uma.insert({"two",2});
    uma.insert({"three",3});
    uma.insert({"four",4});
    uma.insert({"five",5});

    cout<<"-----------------map"<<endl;
    for(auto & [k,v]:ma){
        cout<<k<<" : "<<v<<endl;
    }
    cout<<"-----------------unordered_map"<<endl;
    for(auto & [k,v]:ma){
        cout<<k<<" : "<<v<<endl;
    }

}

void vector_set(){
    vector<int> ve={1,3,5,7,9,9,8,6,4,2,0,1};
    set<int> se(ve.begin(),ve.end());
    for(auto x:se){
        cout<<x<<" ";
    }

}

int main(){
    //word_find();
    //map_or_unorderedmap();
    //vector_set();
    return 0;
}