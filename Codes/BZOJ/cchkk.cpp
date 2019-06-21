#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct edge{
    int END,next;
}v[100005];
int first[1005],Index,du[1005],n;
void add(int a,int b){
    du[a]++;
    v[Index].END=b;
    v[Index].next=first[a];
    first[a]=Index++;
}
int p[1005][1005];
double f[1005][1005];
void spfa(int x){
    queue<int> Q;
    bool flag[1005]={0};
    int dis[1005],fr[1005];
    memset(dis,0x3f,sizeof(dis));
    memset(fr,0,sizeof(fr));
    dis[x]=0;
    flag[x]=1;Q.push(x);
    while(!Q.empty()){
        int k=Q.front();
        Q.pop();flag[k]=0;
        for(int i=first[k];i!=-1;i=v[i].next){
            if(dis[v[i].END]>dis[k]+1||(dis[v[i].END]==dis[k]+1&&k<fr[v[i].END])){
                dis[v[i].END]=dis[k]+1;
                fr[v[i].END]=k;
                if(!flag[v[i].END]){
                    flag[v[i].END]=1;
                    Q.push(v[i].END);
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
        if(i!=x)
            p[i][x]=fr[i];
}
double dfs(int s,int e){
    if(s==e)return f[s][e]=0;
    if(p[s][e]==e||p[p[s][e]][e]==e)return f[s][e]=1;
    if(f[s][e]<=1e9) return f[s][e];
    int tmp=p[p[s][e]][e];
    f[s][e]=1;
    for(int i=first[e];i!=-1;i=v[i].next){
        f[s][e]+=dfs(tmp,v[i].END)/(du[e]+1);
    }
    f[s][e]+=dfs(tmp,e)/(du[e]+1);
    return f[s][e];
}
int main()
{
    freopen("cchkk.in","r",stdin);
	freopen("cchkk.out","w",stdout);
    memset(first,-1,sizeof(first));
    memset(f,0x7f,sizeof(f));
    int m,s,e,a,b;
    scanf("%d%d%d%d",&n,&m,&s,&e);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
    }
    for(int i=1;i<=n;i++)
        spfa(i);
    printf("%.3lf",dfs(s,e));
    //while(1);
}