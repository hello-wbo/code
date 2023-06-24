#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
struct City{
	bool operator <(City c){
		return x<=c.x;
	}
	City(){
		x=w=c=0;
	}
	static void init(int n);
	float x;
	float w;
	float c;
};
//addone[i][j]代表服务点i右侧建立j个服务点后增加的费用，t[n+1][n+1]存储动规子问题的最优解
int t[1001][101],addone[1001][1001],dp[1001][1001];//dp[i][j]表示前i个居民点 最优解中，第j个机构的居民点编号 
City* city;
ifstream in("input.txt");
ofstream out("output.txt");
 
//计算居民点pos到最近的服务机构r寻求服务的费用 
float wMulx(int r,int pos){
	City c1=city[r],c2=city[pos];
	return c2.w*(c2.x-c1.x);
}
//计算所有可能的 i 到 j 服务转移费用 
void init(int n){
	float cost,mid;
	City c1,c2,c3;
	//第一家服务机构j的建立
	for(int j=1;j<=n;j++){
		c1=city[j];
		cost=c1.c;
		for(int i=1;i<j;i++){
			c2=city[i];
			cost+=c2.w*(c1.x-c2.x);
		}
		addone[0][j]=cost;
	} 
	//第i个服务机构右侧增加机构j,计算增加的总费用 
	for(int i=1;i<n;i++)
		for(int j=i+1; j<=n;j++){
			c1=city[i];
			c2=city[j];
			cost=c2.c;//建设费用 
			mid=(c1.x+c2.x)/2;//中点 
			for(int k=i+1;k<j;k++){
				c3=city[k];
				if(c3.x>mid){
					cost+=c3.w*(c2.x+c1.x-2*c3.x); 
				}
			}
			addone[i][j]=cost; 
		}
}
void solve(int n,int k){
	sort(city+1,city+n+1);
	init(n);
	//计算前i个居民点建立j个服务机构的费用 
	int max;
	float f1,f2;
	for(int i=1;i<=n;i++){//前i个居民点 
		max=min(k,i);//最多建立的机构数目 
		for(int j=1;j<=max;j++){//j个服务点 
			f2=t[i-1][j-1]+addone[ dp[i-1][j-1] ] [ i ];//第i个居民点作为服务机构 
			if(j==i){//居民点数目和机构数目一样多 
				t[i][j]=f2;
				dp[i][j]=i;//前i个居民点建立k个服务机构最优解中，第j个服务机构是居民点i 
			}
			else{
				f1=t[i-1][j]+wMulx(dp[i-1][j],i);//第i个居民点不作为服务机构 
				t[i][j]=min(f1,f2);//取较小的 
				if(f2<=f1){//选取居民点i，更新p 
					dp[i][j]=i;//前i个居民点建立k个服务机构最优解中，第j个服务机构是居民点i 
				}
				else {
					dp[i][j]=dp[i-1][j];
				}
			}
		}
	}
}
void output(int n,int k){
	int min=0x7fffffff,num=0;
	// for(int i=0;i<=n;i++){
	// 	for(int j=0;j<=k;j++)
	// 		cout<<t[i][j]<<' ';
	// 	cout<<'\n';
	// }
			
	for(int i=1;i<=k;i++)
		if(t[n][i]<min){
			min=t[n][i];
			num=k;
		}
	// cout<<"k:"<<k<<'\n';
	cout  <<min<<'\n';
	out<<min; 
}
int main(){
	int n,k;
	in>>n>>k;
	city=new City[n+1];
	City C;
	for(int i=1;i<=n;i++){
		in>>C.x>>C.w>>C.c;
		city[i]=C;
	}
	solve(n,k);
	output(n,k);
	in.close();
	out.close();
	return 0;
}