#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int son[100005],mid;
struct edge{
    int END,next;
}v[200005];
int first[100005],p,f[100005],q[100005],tot;
void add(int a,int b){
    v[p].END=b;v[p].next=first[a];first[a]=p++;
    v[p].END=a;v[p].next=first[b];first[b]=p++;
}
int cmp(const int a,const int b){
    return b<a;
}
void dfs(int rt,int fa){
    f[rt]=0;
    for(int i=first[rt];i!=-1;i=v[i].next)
        if(v[i].END!=fa) dfs(v[i].END,rt);
    int cnt=0;q[0]=0;
    for(int i=first[rt];i!=-1;i=v[i].next)
        if(v[i].END!=fa) q[++cnt]=f[v[i].END]+1;
    sort(q+1,q+cnt+1,cmp);
    if(!cnt) return;
    if(cnt==1){
        if(q[1]>mid){
            tot++;
            return;
        }
        else {f[rt]=q[1];return;}
    }
    int i=2;
    while(q[i-1]+q[i]>mid&&i<=cnt){
        tot++;
        i++;
    }
    if(i==cnt+1&&q[i-1]>mid)tot++;
    f[rt]=q[i-1];
}
int main()
{
    memset(first,-1,sizeof(first));
    int n,m;
    scanf("%d%d",&n,&m);
    int a,b;
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        add(a,b);
    }
    //int ans=0;
    int l=1,r=n;
    while(l<r){
        mid=l+r>>1;tot=0;
        dfs(1,0);
        if(tot<=m)r=mid;
        else l=mid+1;
    }
    printf("%d",l);
    //while(1);
}