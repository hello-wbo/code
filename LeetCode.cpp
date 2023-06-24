#include <bits/stdc++.h>
using namespace std;
#include "LeetCode.h"

int main(){
    Solution sln;
    vector<int>nums;
    string s="adsd";
    nums={4,5,2147483647,1,2};
    int n=2;
    TreeNode node1=TreeNode(-2,NULL,NULL);
    TreeNode node2=TreeNode(3,NULL,NULL);
    TreeNode node3=TreeNode(1,&node1,&node2);
    sln.maxPathSum(&node1) ;
    cout<<maxLen;
}
