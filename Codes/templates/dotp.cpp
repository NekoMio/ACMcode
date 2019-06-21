#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int mp[305][305],du[305],n;
long double a[305][305],x[305],sum;
void gauss(){
    int im,num=1;
    for(int k=1;k<=n;k++,num++){
        im=k;
        for(int i=k+1;i<=n;i++){
            if(fabs(a[i][k])>fabs(a[im][k]))
                i=im;
        }
        if(im!=k){
            for(int i=k;i<=n+1;i++)
                swap(a[num][i],a[im][i]);
        }
        if(!a[num][k]){
            num--;continue;
        }
        for(int i=num+1;i<=n;i++){
            if(!a[num][k])continue;
            long double t=a[i][k]/a[num][k];
            for(int j=k;j<=n+1;j++){
                a[i][j]-=t*a[k][j];
            }
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=n;j>=i+1;j--){
            a[i][n+1]-=a[i][j]*x[j];
        }
        x[i]=a[i][n+1]/a[i][i];
        sum+=x[i];
    }
}
int main()
{
    freopen("dotp.in","r",stdin);
    freopen("dotp.out","w",stdout);
    int m,p,q,s,e;
    scanf("%d%d%d%d",&n,&m,&p,&q);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&s,&e);
        mp[s][e]++;mp[e][s]++;
        du[s]++;du[e]++;
    }
    a[1][n+1]=1;
    for(int i=1;i<=n;i++){
        a[i][i]=1;
        for(int j=1;j<=n;j++){
            if(mp[i][j]){
                a[i][j]+=((long double)p/q-1)/du[j]*mp[i][j];
            }
        }
    }
    gauss();
    for(int i=1;i<=n;i++){
        printf("%.9lf\n",(double)(x[i]/sum));
    }
    //while(1);
}