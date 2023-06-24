#include<stdio.h>
 
#define N 100
 
int a[N][N],answer[N][N];
 
int n,maxV; 
 
int judge(int temp,int k){
	int i,j;
	for(i=1;i<=a[k][0];i++){
		for(j=i+1;j<=a[k][0];j++){
			if(a[k][i]+a[k][j]==temp)
			   return 0;
		}
	}
	return 1;
	
}
 
void backtrack(int temp){
	int i,j;
	if(temp>maxV){
		for(i=0;i<n;i++){
			for(j=0;j<=a[i][0];j++){  
				answer[i][j] = a[i][j];
			}
		}
		maxV = temp;
	}
	
	for(i=0;i<n;i++){
		a[i][a[i][0]+1]=temp;
		if(judge(temp,i)){
			a[i][0]+=1;
			backtrack(temp+1);
			a[i][0]-=1;
		}
	} 
}
 
void output(){
	int i,j;
	printf("%d\n",maxV-1);
	for(i=0;i<n;i++){
		for(j=1;j<=answer[i][0];j++){
			printf("%d\temp",answer[i][j]);
		}
		printf("\n");
	} 
}
 
int main(){
	
	scanf("%d",&n);
	maxV = 0;
	backtrack(1);
	output();
	return 0;
}