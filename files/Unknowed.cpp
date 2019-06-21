#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge{
    int START,END,next,v;
    bool operator < (const edge a)const{
        return v<a.v;
    }
}v[600005],re[600005];
int first[100005],p=1,father[100005],Deep[100005];
bool vis[100005];
int f[100005][25],maxn[100005][25];
int find(int a){
    if(father[a]!=a)father[a]=find(father[a]);
    return father[a];
}
void add(int a,int b,int c){
    v[p].END=b;
    v[p].v=c;
    v[p].next=first[a];
    first[a]=p++;
}
void dfs(int x,int dep){
    vis[x]=1;
    Deep[x]=dep;
    for(int i=first[x];i!=-1;i=v[i].next){
        if(!vis[v[i].END]){
            f[v[i].END][0]=x;
            maxn[v[i].END][0]=v[i].v;
            dfs(v[i].END,dep+1);
        }
    }
}
int LCA(int x,int y){
    int lca=-1;
    int i=0;
    if(Deep[x]<Deep[y])swap(x,y);
    //for(i=0;(1<<i)<=Deep[x];i++);
    //i--;
    for(int j=24;j>=0;j--){
        if(Deep[x]-(1<<j)>=Deep[y]){
            lca=max(lca,maxn[x][j]);
            x=f[x][j];
        }
    }
    if(x==y)return lca;
    for(int j=24;j>=0;j--){
        if(f[x][j]!=f[y][j]){
            lca=max(lca,max(maxn[x][j],maxn[y][j]));
            x=f[x][j];
            y=f[y][j];
        }
    }
    lca=max(lca,max(maxn[x][0],maxn[y][0]));
    if(x==1||y==1||lca==0)return -1;
    return lca;
}
int main(){
    //freopen("1.txt","r",stdin);
    //freopen("3.txt","w",stdout);
    int n,m,t=1;
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    int a,b,c;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a,&b,&c);
        re[t].START=a;
        re[t].END=b;
        re[t].v=c;
        t++;
    }
    sort(re+1,re+t);
    int k=0;
    for(int i=1;i<=n;i++)father[i]=i;
    for(int i=1;i<t;i++){
        int x=re[i].START;
        int y=re[i].END;
        if(find(x)!=find(y)){
            father[find(x)]=find(y);
            add(x,y,re[i].v);
            add(y,x,re[i].v);
            k++;
        }
        if(k==n-1)break;
    }
    f[1][0]=0;maxn[1][0]=0;
    dfs(1,0);
    for(int j=1;j<=24;j++){
        for(int i=1;i<=n;i++){
            f[i][j]=f[f[i][j-1]][j-1];
            maxn[i][j]=max(maxn[i][j-1],maxn[f[i][j-1]][j-1]);
        }
    }
    int Q;
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++){
        scanf("%d%d",&a,&b);
        int ans=LCA(a,b);
        if(ans!=-1)printf("%d\n",ans);
        else puts("impossible");
    }
}