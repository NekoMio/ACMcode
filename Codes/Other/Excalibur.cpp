#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int INF=0x7fffffff;
struct edge{
    int END,cap,next;
}v[500000];
int first[10005],p;
void add(int a,int b,int c){
    v[p].END=b;v[p].next=first[a];v[p].cap=c;first[a]=p++;
    v[p].END=a;v[p].next=first[b];v[p].cap=0;first[b]=p++;
}
int dis[10005];
bool vis[10005];
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
int DFS(int x,int a,int E){
    if(x==E||a==0)return a;
    int flow=0,f;
    for(int i=first[x];i!=-1;i=v[i].next){
        if(dis[x]+1==dis[v[i].END]&&(f=DFS(v[i].END,min(a,v[i].cap),E))>0){
            v[i].cap-=f;
            v[i^1].cap+=f;
            flow+=f;
            a-=f;
            if(a==0)break;
        }
    }
    if(!flow)dis[x]=-1;
    return flow;
}
int Dinic(int S,int E){
    int flow=0;
    while(BFS(S,E)){
        flow+=DFS(S,INF,E);
    }
    return flow;
}
int a[105][105];
template<class T>inline void read(T &res){
	static char ch;T flag=1;
	while((ch=getchar())<'0'||ch>'9')if(ch=='-')flag=-1;res=ch-48;
	while((ch=getchar())>='0'&&ch<='9')res=(res<<1)+(res<<3)+ch-48;res*=flag;
}
int Main(){
	freopen("Excalibur.in","r",stdin);
    freopen("Excalibur.out","w",stdout);
    memset(first,-1,sizeof(first));
    int m,n;
    int sum=0;
    read(m),read(n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++){
            read(a[i][j]);
            sum+=a[i][j];
    	}
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if((i&1)^(j&1)){
                add(0,n*(i-1)+j,a[i][j]);
                if(j-1>=1)add(n*(i-1)+j,n*(i-1)+j-1,INF);
				if(i-1>=1)add(n*(i-1)+j,n*(i-2)+j,INF);
				if(i+1<=m)add(n*(i-1)+j,n*(i)+j,INF);
				if(j+1<=n)add(n*(i-1)+j,n*(i-1)+j+1,INF);
            }
            else{
                add(n*(i-1)+j,n*m+1,a[i][j]);
            }
            
        }
    }
    return printf("%d",sum-Dinic(0,m*n+1));
}
int A=Main();
int main(){;}