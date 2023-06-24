#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;
#define N 1000
int cost[N][N];//��i������ɵ�j��������Ҫ�ķ���
int flag[N]={0};//��¼��n�������Ƿ����
int n;
int co;
void solution(int a, int b) 
{
	if(b > co) return;
	if(a == n) 	{ 
        if(b < co) co=b;
		return;
	}
	for(int j=0;j<n;j++) {
		if(flag[j]==0){ 
			flag[j]=1;solution(a+1, b+cost[a][j]);
			flag[j]=0; 
        }
    }
}

int main()
{
	ifstream in("input.txt");
	in>>n;
	for(int i=0;i<n;i++) 
		for(int j=0;j<n;j++)
			in>>cost[i][j];  
	in.close(); 
	co=N; 
	clock_t start,end;
    start=clock();
	solution(0,0);  
	end=clock();
    printf("ʱ�䣺%fms\n",(double)(end-start)/CLK_TCK);
	ofstream out("output.txt");
	out<<co;
	out.close();
	return 0;
}    

