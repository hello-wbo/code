#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<iostream>
using namespace std;
int main()
{//��������Ϊn����������ַ����Ͳ�����5������k
	int n,m;
	cin>>n;
	m=n;
	ofstream out("input.txt");
	srand((unsigned)time(NULL));
	n=n+rand()%10;
	for(int i=0;i<n;i++)
	{
		char x='a'+rand()%26;
		out<<x;
	}
	out<<'\n';
	m=m+rand()%10;
	for(int i=0;i<m;i++)
	{
		char x='a'+rand()%26;
		out<<x;
	}
	out<<'\n';
	int k=rand()%5+1;
	out<<k;
	out.close();
	return 0;
}

