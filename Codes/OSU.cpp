#include<cstdio>
#include<cstring>
using namespace std;
double x[100005],x2[100005],f[100005];
int main()
{
    int n;
    double a;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf",&a);
        x[i]=(x[i-1]+1)*a;
        x2[i]=(x2[i-1]+2*x[i-1]+1)*a;
        f[i]=f[i-1]+(3*x2[i-1]+3*x[i-1]+1)*a;
    }
    printf("%.1f",f[n]);
}