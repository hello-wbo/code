#include<stdio.h>
#include <iostream>
using namespace std;
#define MAXN 20  //最多20个物品 

int  n=4;   //4种物品 
int W=6;   //最大重量6 
int w[]={0,5,3,2,1};  //存放4个物品重量，下标为0元素不用 
int v[]={0,4,4,3,1};  //存放4个物品价值，下标为0元素不用 

int x[MAXN];  //bool数组，记录是否被选中
int maxv;   //最优解 
void dfs(int i,int cur_w,int cur_v,int option[])
{
	if(i>n)   //叶节点
	{
		if(cur_v>maxv)  //如果有更好的就记录下
		{
			maxv=cur_v;
			for(int j=1;j<=n;j++)
			x[j]=option[j];
		 } 
	 } 
	 else   //递归
	 {
	 	option[i]=1;  //选
		 dfs(i+1,cur_w+w[i],cur_v+v[i],option);
		 option[i]=0;//不选
		 dfs(i+1,cur_w,cur_v,option); 
	 }	 
}
void dispsolution()   //display
{
	int i;
	printf("最优解：\n");
	for(i=1;i<=n;i++)
	if(x[i]==1)
	printf(" 选取第%d个物品\n",i);
	printf("总重量=%d,总价值=%d\n",W,maxv);
 } 
 int main(){
	// string s;
	// getline(cin,s);
	
	// int 
	// s+='1';
 	int op[MAXN];  //存放临时解 
 	dfs(1,0,0,op);  //i从1开始 
 	dispsolution();
 	return 0;
 }
 
