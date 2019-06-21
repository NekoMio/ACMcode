#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
double c[20],a[15][15],b[15],x[15],d;
int n;
void gauss(){
    int im,num=1;
    for(int k=1;k<=n;k++,num++){
        im=k;
        for(int i=k+1;i<=n;i++)
            if(fabs(a[i][k])>fabs(a[im][k]))
                im=i;
        if(im!=k){
            for(int i=k;i<=n;i++)
                swap(a[num][i],a[im][i]);
            swap(b[num],b[im]);
        }
        if(!a[num][k]){num--;continue;}
        for(int i=num+1;i<=n;i++){
            if(!a[num][k])continue;
            double t=a[i][k]/a[num][k];
            for(int j=k;j<=n+1;j++){
                a[i][j]-=t*a[k][j];
            }
            b[i]-=t*b[k];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=n;j>=i+1;j--)
            b[i]-=a[i][j]*x[j];
        x[i]=b[i]/a[i][i];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lf",&c[i]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%lf",&d);
            a[i][j]=d-c[j];
            b[i]+=d*d-c[j]*c[j];
        }
        b[i]/=2;
    }
    gauss();
    for(int i=1;i<n;i++){
        printf("%.3lf ",x[i]);
    }
    printf("%.3lf",x[n]);
}