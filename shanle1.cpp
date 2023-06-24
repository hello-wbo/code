#include<iostream>
using namespace std;
 
int f(int a)
{
    int b = 0;
    static int c = 3;
    a = c++,b++;
    return (a);
}
int main()
{
    int*a=new int[20];
    int b[20];
    cout<<sizeof(a)<<endl<<sizeof(b);

     
    return 0;
}