#include <stdio.h>
#include <math.h>
int main()
{
    //tìm ước chung lớn nhất
    int n,m,max=0; scanf("%d %d",&n,&m);
    if(n>m)
    {
        int tg=n;
        n=m;
        m=tg;
    }
    for(int i=1;i<=n;i++)
    if(n%i==0&&m%i==0)
    if(i>max) max=i;
    printf("%d",max);
    return 0;
}