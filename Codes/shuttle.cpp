/*
 * @Author: WildRage 
 * @Date: 2017-06-13 21:23:24 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-06-13 21:48:22
 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int INF=0x7fffffff;
struct edge{
    int END,next,cap;
}v[100005];
int first[1005],p;
void add(int a,int b,int c){
    v[p].END=b;v[p].next=first[a];v[p].cap=c;first[a]=p++;
    v[p].END=a;v[p].next=first[b];v[p].cap=0;first[b]=p++;
}
int cur[1005],dis[1005];
bool vis[1005];
bool BFS(int S,int E){
    memset(vis,0,sizeof(vis));
    memset(dis,-1,sizeof(dis));
    queue<int> Q;
    Q.push(S);
    dis[S]=0;vis[S]=1;
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
    for(int i=first[S];i!=-1;i=v[i].next){
        if(dis[S]+1==dis[v[i].END]&&(f=DFS(v[i].END,E,min(a,v[i].cap)))>0){
            v[i].cap-=f;
            v[i^1].cap+=f;
            flow+=f;
            a-=f;
        }
    }
    if(!flow)dis[S]=-1;
    return flow;
}
int Dinic(int S,int E){
    int ans=0;
    while(BFS(S,E)){
        ans+=DFS(S,E,INF);
    }
    //printf("%d\n",ans);
    //while(1);
    return ans;
}
int Main()
{
    memset(first,-1,sizeof(first));
    int n,m;
    freopen("shuttle.in","r",stdin);
	freopen("shuttle.out","w",stdout);
    scanf("%d%d",&n,&m);
    int ans=0;
    char ch;
    for(int x,i=1;i<=n;i++){
        scanf("%d",&x);ans+=x;
        add(0,i,x);
        while(1){
            while((ch=getchar())==' ');
            ungetc(ch,stdin);
            if(ch=='\n'||ch=='\r')break;
            scanf("%d",&x);
            add(i,x+n,INF);
        }
    }
    for(int x,i=1;i<=m;i++){
        scanf("%d",&x);
        add(i+n,m+n+1,x);
    }
    ans=ans-Dinic(0,n+m+1);
    for(int i=1;i<=n;i++)
        if(dis[i]>=0)
            printf("%d ",i);
    puts("");
    for(int i=1;i<=m;i++)
        if(dis[i+n]>=0)
            printf("%d ",i);
    puts("");
    printf("%d\n",ans);
    return 0;
}
int Wild=Main();
int main(){;}