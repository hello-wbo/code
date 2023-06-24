#include<bits/stdc++.h>
const int N=410, INF=0x3f3f3f3f;
using namespace std;  

int main()
{
	int n;
	cin >> n;
	int a[N];            
	int sum[N];          
	int min0[N][N];     
	int max0[N][N];     

	memset(min0,INF,sizeof min0);      
	memset(max0,0,sizeof max0);
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		a[i+n]=a[i];     
	} 
	
	for(int i=1;i<=2*n;i++)
	{
		min0[i][i]=0;     
		max0[i][i]=0;	
		sum[i]=sum[i-1]+a[i];    
	} 
	
	for(int length=2;length<=n;length++)      
	{
		for(int left=1;left+length-1<=2*n;left++)      
		{
			int right=left+length-1;         
	 		for(int k=left; k<right; k++)          
			{
                
	 			min0[left][right]=min(min0[left][right],min0[left][k]+min0[k+1][right]+sum[right]-sum[left-1]);
	 			max0[left][right]=max(max0[left][right],max0[left][k]+max0[k+1][right]+sum[right]-sum[left-1]);
	 		}
		} 
	} 

	int minn=INF, maxx=0;
	for(int i=1;i<=n;i++)
	{
		minn=min(minn,min0[i][i+n-1]);                 
		maxx=max(maxx,max0[i][i+n-1]);                 
	}
	cout << minn << endl << maxx;
	return 0;	
}
