#include "bits/stdc++.h"
using namespace std;
#define N 5
#define M 9999999
void dijkstra(int G[][N],vector<int> &vis,vector<int>&dis,int start){
        for(int i=0;i<N;i++){
            dis[i]=G[start][i];
        }
    int min=0 ;//距离当前点最近的点（未访问）
    for(int i=0;i<N;i++){
        //找到未访问点中具有最小dis值的点
        for(int j=0;j<N;j++){
            if(vis[j]!=1){
                min=j;break;
            }
        }
        for(int j=min+1;j<N;j++){
            if(dis[j]<dis[min]&&vis[j]!=1){
                min=j;
            }
        }
        
        vis[min]=1;//!   
        //更新，对于找到的点所有可到达的点，更新权值
        for(int j=0;j<N;j++){
            if(G[min][j]+dis[min]<dis[j]){
                dis[j]=G[min][j]+dis[min];

            }
        }
    }
}
int main(){
    vector<int>vis(N,0);
    vector<int>dis(N,M);
    int G[N][N]={
		{0, 10, M, 30, 100},
        {M, 0, 50, M, M},
        {M, M, 0, M, 10},
        {M, M, 20, 0, 60},
        {M, M, M, M, 0}
    };
    int start=0;
    dijkstra(G,vis,dis,start);
    for(int i=0;i<N;i++){
        cout<<i<<"到"<<start<<"的最短距离为："<<dis[i]<<endl;
    }
    
}