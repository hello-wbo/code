#include<iostream>
using namespace std;
int main(){
    int n,a[1000];
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int dp[1000]={0},max=1,t;//t����ʱ���Ž�
    dp[1]=1;//�����еĵ�һ������
    for(int i=2;i<=n;i++){
        t=0; 
        for(int j=i-1;j>0;j--){
            if(a[i]>a[j]&&dp[j]>t){
                t=dp[j]; 
            }
        }
        dp[i]=dp[i]+t+1; 
        if(dp[i]>max)
            max=dp[i];
    }
    cout<<max<<endl;
    return 0;
}
/*8
1 2 3 8 9 4 5 6 */