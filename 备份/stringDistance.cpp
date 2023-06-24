#include <iostream>
#include <fstream>
#include <string> 
#include <cmath>
#include <ctime>
using namespace std;
#define MAX 100000    //标识最大的可能整数
int val[300][300];    //用来存储中间值  
string strA="cmc";        //字符串A
string strB="snmn";       //字符串B
int k=2;        //定值k
//返回字符a与b的ASCII码的差的绝对值
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
                if(i+j)//i和j至少一个大于0
                {
                    val[i][j] = MAX;       
					 
                    tmp = val[i-1][j] + k;    
                    if(i && (tmp<val[i][j])) 
                        val[i][j] = tmp;                                              
                        
                    tmp = val[i][j-1]+k;    
                    if(j && (tmp<val[i][j]))
                    	val[i][j] = tmp;				             
                    	
                    tmp = val[i-1][j-1] + dist(strA[i], strB[j]); //情况3)             
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
    printf("时间：%fms\n",(double)(end-start)/CLK_TCK);
    return 0;
}
