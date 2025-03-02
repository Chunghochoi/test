#include <bits/stdc++.h>
using namespace std;
int ngto(int a)
{
for(int i=2;i<=sqrt(a);i++)
if(a%i==0) return 0;
if(a!=1) return 1;
else return 0;
}
int main() {
    int n,m,d=0;
    float t=0;
    cin >> m>>n;
    for(int i=m;i<=n;i++)
        if(ngto(i)==1)
        {
            t+=i;
            d++;
          // cout<<i<<endl;
        }
        t=t/d;
        if(d==0) cout<<"-";
        else cout<<fixed<<setprecision(2)<<t;
    return 0;
}