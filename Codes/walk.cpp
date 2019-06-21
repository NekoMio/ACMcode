#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
struct edge{
    int END,next;
}v[500005];
int first[505],p,du[505];
void add(int a,int b){
    v[p].END=b;
    v[p].next=first[a];
    first[a]=p++;
}
template<typename T>
int cmp(const T a,const T b){
    return a > b;
}
double a[505][505],x[505],f[500005];
int n,m;
void gauss(){
    int im,num=1;
    for(int k=1;k<=n;k++,num++){
        im=k;
        for(int i=k+1;i<=n;i++)
            if(fabs(a[i][k])>fabs(a[im][k]))
                im=i;
        if(im!=k){
            for(int i=k;i<=n+1;i++)
                swap(a[num][i],a[im][i]);
        }
        if(!a[num][k]){
            num--;continue;
        }
        for(int i=num+1;i<=n;i++){
            if(!a[num][i])continue;
            double t=a[i][k]/a[num][k];
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
    }
}
int main()
{
    //freopen("walk.in","r",stdin);
	//freopen("walk.out","w",stdout);
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    int s,e;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&s,&e);
        du[s]++;du[e]++;
        add(s,e);add(e,s);
    }
    n--;
    a[1][n+1]=-1;
    for(int i=1;i<=n;i++){
        a[i][i]=-1;
        for(int j=first[i];j!=-1;j=v[j].next){
            if(v[j].END!=n+1)
                a[i][v[j].END]+=(double)1/(du[v[j].END]);
        }
    }
    gauss();
    for(int i=0;i<p;i++){
        //if(v[i].END!=n+1)
            f[i>>1]+=x[v[i].END]/du[v[i].END];
    }
    //for(int i=0;i<m;i++){
    //    printf("%lf\n",f[i+1]);
    //}
    //while(1);
    sort(f,f+m,cmp<double>);
    double ans=0;
    for(int i=0;i<m;i++){
        ans+=f[i]*(i+1);
    }
    printf("%.3lf",ans);
    //while(1);
}
