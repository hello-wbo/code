#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
#define ll long long
int a[500],b[500],dp[500][500];// dp[k,x]表示完成k个作业且机器A 花费x 时间的条件下机器B 所花费时间的最小值
const int INF=1<<30;
int n,sum;
int main()
{
    cin>>n;
    int i,j;
    sum=0;
    for (i=0;i<n;i++){
        cin>>a[i];
        sum+=a[i];
    }
    for (i=0;i<n;i++)
        cin>>b[i];
    for (i=1;i<=n;i++)//n个作业
    {
        for (j=0;j<=sum;j++)//机器a完成的时间
        if (j<a[i-1])//a完成不了
            dp[i][j]=dp[i-1][j]+b[i-1];
        else if (dp[i-1][j-a[i-1]]>dp[i-1][j]+b[i-1])//用b完成更优
            dp[i][j]=dp[i-1][j]+b[i-1];
        else
            dp[i][j]=dp[i-1][j-a[i-1]];
    }
    int temp,ans=INF;
    for (i=0;i<=sum;i++)
    {
        temp=dp[n][i]>i?dp[n][i]:i;//ab中选择时间较长的作为总时间  
        if (temp<ans)
        ans=temp;       //选择总时间最短的       
    }
    cout<<ans<<endl;
    return 0;
}