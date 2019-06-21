#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
double a[200][200],b[200],x[200];
int gauss(){
    int im,num=1;
    for(int k=1;k<=n;k++,num++){
        im=k;
        for(int i=k+1;i<=n;i++){
            if(fabs(a[i][k])>fabs(a[im][k]))
                im=i;
        }
        if(im!=k){
            for(int i=k;i<=n;i++)
                swap(a[num][i],a[im][i]);
            swap(b[num],b[im]);
        }
        if(!a[num][k]) {num--;continue;}
        for(int i=num+1;i<=n;i++){
            if(!a[num][k]) continue;
            double t=a[i][k]/a[num][k];
            for(int j=k;j<=n+1;j++)
                a[i][j]-=t*a[k][j];
            b[i]-=t*b[k];
        }
    }
    for(int i=num;i<=n;i++)
        if(!a[i][n]&&b[i])
            return -1;
    for(int i=n;i>=1;i--){
        for(int j=n;j>=i+1;j--)
            b[i]-=a[i][j]*x[j];
        if(!a[i][i]&&b[i]!=0)
            return -1;
        if(!a[i][i]&&!b[i])
            return 0;
        x[i]=b[i]/a[i][i];
    }
    return 1;
}
int main()
{
    freopen("gaess.in","r",stdin);
    freopen("gaess.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%lf",&a[i][j]);
        }
        scanf("%lf",&b[i]);
    }
    int s=gauss();
    if(s!=1)
        printf("%d",s);
    else {
        for(int i=1;i<=n;i++){
            if(x[i]==0)
                printf("x%d=0\n",i);
            else{
                printf("x%d=%.2lf\n",i,x[i]);
            }
        }
    }
    //while(1);
}