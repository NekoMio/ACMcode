#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;
const int INF=0x7fffffff;
int idIndex;
int read(){
    int res=0;
    static char ch;int flag=1;
	while((ch=getchar())<'0'||ch>'9')if(ch=='-')flag=-1;res=ch-48;
	while((ch=getchar())>='0'&&ch<='9')res=(res<<1)+(res<<3)+ch-48;
    return res*flag;
}
struct edge{
    int END,next,cap;
}v[1000005];
int first[10005],p;
void add(int a,int b,int c){
    v[p].END=b;v[p].next=first[a];v[p].cap=c;first[a]=p++;
    v[p].END=a;v[p].next=first[b];v[p].cap=0;first[b]=p++;
}
int a[150];
int Idx[1005],id[150][150];
int dis[10005],cur[10005];
bool vis[10005];
bool BFS(int S,int E){
    memset(dis,-1,sizeof(dis));
    memset(vis,0,sizeof(vis));
    vis[S]=1;dis[S]=0;
    queue<int> Q;
    Q.push(S);
    while(!Q.empty()){
        int u=Q.front();Q.pop();
        for(int i=first[u];i!=-1;i=v[i].next){
            if(!vis[v[i].END]&&v[i].cap>0){
                vis[v[i].END]=1;
                dis[v[i].END]=dis[u]+1;
                if(v[i].END==E)return 1;
                Q.push(v[i].END);
            }
        }
    }
    return 0;
}
int DFS(int S,int E,int a){
    if(S==E||a==0)return a;
    int flow=0,f;
    for(int &i=cur[S];i!=-1;i=v[i].next){
        if(dis[v[i].END]==dis[S]+1&&(f=DFS(v[i].END,E,min(a,v[i].cap)))>0){
            v[i].cap-=f;
            v[i^1].cap+=f;
            a-=f;
            flow+=f;
            if(f==0)break;
        }
    }
    //
    if(!flow) dis[S]=-1;
    return flow; 
}
int Dinic(int S,int E){
    int ans=0;
    while(BFS(S,E)){
        memcpy(cur,first,sizeof(first));
        ans+=DFS(S,E,INF);
    }
    return ans;
}
int main()
{
    int n,m;
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    int S=++idIndex,T=++idIndex;
    int maxn=0;
    for(int i=1;i<=n;i++) maxn=max(maxn,a[i]=read());
    for(int i=1;i<=maxn;i++){
        Idx[i]=++idIndex;
        add(Idx[i],T,m*i*i);
    }
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)id[i][j]=++idIndex;
    int x;
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            x=read();
            if(i==j)x-=a[i],add(id[i][j],Idx[a[i]],INF);
            else {
                if(id[i+1][j])add(id[i][j],id[i+1][j],INF);
                if(id[i][j-1])add(id[i][j],id[i][j-1],INF);
            }
            if(x>0) ans+=x,add(S,id[i][j],x);
            else add(id[i][j],T,-x);
        }
    }
    ans-=Dinic(S,T);
    printf("%d\n",ans);
    getchar();
    getchar();
    return 0;
}