#include<stdio.h>
#include <iostream>
using namespace std;
#define MAXN 20  //���20����Ʒ 

int  n=4;   //4����Ʒ 
int W=6;   //�������6 
int w[]={0,5,3,2,1};  //���4����Ʒ�������±�Ϊ0Ԫ�ز��� 
int v[]={0,4,4,3,1};  //���4����Ʒ��ֵ���±�Ϊ0Ԫ�ز��� 

int x[MAXN];  //bool���飬��¼�Ƿ�ѡ��
int maxv;   //���Ž� 
void dfs(int i,int cur_w,int cur_v,int option[])
{
	if(i>n)   //Ҷ�ڵ�
	{
		if(cur_v>maxv)  //����и��õľͼ�¼��
		{
			maxv=cur_v;
			for(int j=1;j<=n;j++)
			x[j]=option[j];
		 } 
	 } 
	 else   //�ݹ�
	 {
	 	option[i]=1;  //ѡ
		 dfs(i+1,cur_w+w[i],cur_v+v[i],option);
		 option[i]=0;//��ѡ
		 dfs(i+1,cur_w,cur_v,option); 
	 }	 
}
void dispsolution()   //display
{
	int i;
	printf("���Ž⣺\n");
	for(i=1;i<=n;i++)
	if(x[i]==1)
	printf(" ѡȡ��%d����Ʒ\n",i);
	printf("������=%d,�ܼ�ֵ=%d\n",W,maxv);
 } 
 int main(){
	// string s;
	// getline(cin,s);
	
	// int 
	// s+='1';
 	int op[MAXN];  //�����ʱ�� 
 	dfs(1,0,0,op);  //i��1��ʼ 
 	dispsolution();
 	return 0;
 }
 
