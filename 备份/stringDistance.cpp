#include <iostream>
#include <fstream>
#include <string> 
#include <cmath>
#include <ctime>
using namespace std;
#define MAX 100000    //��ʶ���Ŀ�������
int val[300][300];    //�����洢�м�ֵ  
string strA="cmc";        //�ַ���A
string strB="snmn";       //�ַ���B
int k=2;        //��ֵk
//�����ַ�a��b��ASCII��Ĳ�ľ���ֵ
int dist(char a, char b)
{
	return abs(a-b);     
}
int comp()
{
	val[0][0] = 0;
	int tmp;
    int len1 = strA.length();
    int len2 = strB.length();
        
        for(int i=0; i<=len1; i++)      
            for(int j=0; j<=len2; j++)   
            {
                if(i+j)//i��j����һ������0
                {
                    val[i][j] = MAX;       
					 
                    tmp = val[i-1][j] + k;    
                    if(i && (tmp<val[i][j])) 
                        val[i][j] = tmp;                                              
                        
                    tmp = val[i][j-1]+k;    
                    if(j && (tmp<val[i][j]))
                    	val[i][j] = tmp;				             
                    	
                    tmp = val[i-1][j-1] + dist(strA[i], strB[j]); //���3)             
                    if((i*j) && (tmp<val[i][j])) 
                    	val[i][j] = tmp;    
                }
            }
        return val[len1][len2];
}
int main()
{
    ifstream f("input.txt");
    f>>strA>>strB>>k;
    f.close();
    strA = " " + strA;     
    strB = " " + strB;    
    clock_t start,end;
    start=clock();
    cout<<comp()<<endl;
    end=clock();
    printf("ʱ�䣺%fms\n",(double)(end-start)/CLK_TCK);
    return 0;
}
