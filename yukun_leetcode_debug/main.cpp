#include<bits/stdc++.h>
using namespace std;
#include "util.cpp"
#include "solution.cpp"

template<class T,class ...Arg>
void myCin(T first, Arg... arg);
void myCin(){}
int main(){//已经定义好了n，root(二叉)，head(链表)，nums（vector<int>）
    const char* input=      "[6,5,5]"         ;
    ss<<input;
    myCin(nums);

    Solution sol;
    auto ans = sol.majorityElement(nums);
    printAns(nums);cout<<endl;
    printAns(ans);
    return 0;
}










template<class T,class ...Arg>
void myCin(T first, Arg... arg){
    string type =typeid(first).name();
    bool x=((type=="St6vectorIiSaIiEE"));
    if(type=="i"){scanf("%d",n);}
    else if(type=="St6vectorIiSaIiEE"){//vector<int>
        
        string input;
        getline(ss,input);
        nums=s2vi(input);
    }
    else if(type=="P8TreeNode"){
        string input;
        getline(ss,input);
        root=s2t(input);
    }
    else if(type=="P8ListNode"){
        string input;
        getline(ss,input);
        head=s2l(input);
    }
    myCin( arg...);
}

