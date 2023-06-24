 #include<stdio.h>
int main()
{
    int n,k,i,a[100];
    int count=0;
    int s=0;
    scanf("%d%d",&n,&k);
    for(i=0;i<=k;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<=k;i++)
    {
        s=s+a[i];
        if(s>n)
        {
            count++;
            s=a[i];
        }
    }
    printf("count=%d\n",count);
    
    
}