#include "bits/stdc++.h"
using namespace std;
int main()
{
    int n;
    n = 30;
    ofstream out("input1.txt");
    out << n << endl;
    for (int i = 0; i < n; i++)
    {
        out << rand() % 100 <<' ';
    }

    //下面用于产生两行数据
    out<<endl;
    for (int i = 0; i < n; i++)
    {
        out << rand() % 100 <<' ';
    }
}