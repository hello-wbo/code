#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<iostream>
using namespace std;
/*���ɡ�n�����س�����n��С��100�����ݡ�*/
/*input.txt*/
int main()
{
	int n;
	cin>>n;
	ofstream out("input.txt");
	out<<n<<'\n';
	srand((unsigned)time(NULL));
	for(int i=0;i<n;i++)
	{
		out<<rand()%100<<' ';
		if((i+1)%10==0) out<<'\n';
	}
	out.close();
	return 0;
}

