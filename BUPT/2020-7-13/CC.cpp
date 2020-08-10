#include<bits/stdc++.h>
using namespace std;
const int MaxN = 200010, MaxM = 200010;
 
struct edge
{
    int to, next;
};
 
edge e[MaxM];
int head[MaxN], cnt;
bool vis[MaxN];
int degree[MaxN];
int n, m, s;
 
inline void add_edge( int u, int v )
{
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt++;
}
 
void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
    //memset(degree,0,sizeof(degree));
    memset(vis,false,sizeof(vis));
}
struct node{
    int id,chain;
    int dis;
    node(int _id,int _chain,int _dis){
        id=_id;
        chain=_chain;
        dis=_dis;
    }
    node(){}
};
struct nn{
    int s,e,dis;
}v[MaxN];
//int ans=0;
//int v[MaxN][3];
//int c[MaxN];
int bfs(int st)
{
    queue<node> q;
    int cnt=0;
    q.push(node(st,cnt,0));
    v[cnt].s=st;
    v[cnt].e=st;
    v[cnt].dis=0;
    while(!q.empty()){
        node temp=q.front();q.pop();
        int x=temp.id,chain=temp.chain;
        int dis=temp.dis;
        vis[x]=true;
        int first=1;
        for(int i=head[x];~i;i=e[i].next){
            int y=e[i].to;
            if(vis[y]) continue;
            if(first) first=0,v[chain].e=y,v[chain].dis=dis,q.push(node(y,chain,dis+1));
            else{
                ++cnt;
                v[cnt].s=st;
                v[cnt].e=y;
                v[cnt].dis=dis;
//              v[++cnt][0]=st;
//              v[cnt][1]=y;
//              v[cnt][2]=dis;
                q.push(node(y,cnt,dis+1));
            }
        }
    }
    return cnt;
}
 
 
inline int read(){
 
   int s=0,w=1;
 
   char ch=getchar();
 
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
 
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
 
   return s*w;
 
}
 
int cmp(nn &p1,nn &p2)
{
    return p1.dis<p2.dis;
}
int main()
{
    scanf( "%d", &n);
    if(n==1){
        printf("0\n");
        return 0;
    }
    m=n-1;
    init();
    for( register int i = 0; i < m; ++i )
    {
        register int u, v;
        //scanf( "%d%d", &u, &v);
        u=read(),v=read();
        add_edge( u, v );
        add_edge(v,u);
        degree[u]++;
        degree[v]++;
    }
    int st;
    for(int i=1;i<=n;i++) if(degree[i]==1){st=i;break;}
    int cnt=bfs(st);
    sort(v,v+cnt+1,cmp);
//  printf("%d\n",cnt+1);
//  for(int i=0;i<=cnt;i++){
//      cout<<v[i][0]<<" "<<v[i][1]<<endl;
//  }
    int t1=0,t2=cnt;
    if(cnt%2==1){
        printf("%d\n",(cnt-1)/2+2);
        printf("%d %d\n",v[cnt].s,v[cnt].e);
        printf("%d %d\n",v[cnt-1].s,v[cnt-1].e);
        t1=0;t2=cnt-2;
        while(t1+1<t2){
            int num1=v[t1].e;
            int num2=v[t2].e;
            printf("%d %d\n",num1,num2);
            t1++,t2--;
        }
    }
    else{
        printf("%d\n",cnt/2+1);
        printf("%d %d\n",v[cnt].s,v[cnt].e);
        t1=0,t2=cnt-1;
        while(t1<t2){
            printf("%d %d\n",v[t1].e,v[t2].e);
            t1++,t2--;
        }
    }
    return 0;
}