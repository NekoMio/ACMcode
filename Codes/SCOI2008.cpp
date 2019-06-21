#include<iostream>
#include<cstdio>
using namespace std;
int w[16];
int p[16];
double f[105][1<<15];
int main()
{
    int n,k;
    scanf("%d%d",&k,&n);
    int a;
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        while(scanf("%d",&a)&&a!=0) p[i]|=1<<(a-1);
    }
    int S=(1<<n)-1;
    for(int i=k;i>=1;i--){
        for(int j=0;j<=S;j++){
            for(int m=1;m<=n;m++)
                if((p[m]&j)==p[m])
                    f[i][j]+=max(f[i+1][j],f[i+1][j|(1<<(m-1))]+w[m]);
                else f[i][j]+=f[i+1][j];
            f[i][j]/=n;
        }
    }
    printf("%.6lf",f[1][0]);
}