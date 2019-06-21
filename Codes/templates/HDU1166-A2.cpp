#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=50005;
int sum[maxn<<2];
void Pushup(int rt){
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void buildtree(int l,int r,int rt){
    if(l==r){
        scanf("%d",&sum[rt]);
        return;
    }
    int m=(l+r)>>1;
    buildtree(l,m,rt<<1);
    buildtree(m+1,r,rt<<1|1);
    Pushup(rt);
}
void updata(int p,int add,int l,int r,int rt){
    if(l==r){
        sum[rt]+=add;
        return;
    }
    int m=(l+r)>>1;
    if(p<=m) updata(p,add,l,m,rt<<1);
    else updata(p,add,m+1,r,rt<<1|1);
    Pushup(rt);
}
int query(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R)return sum[rt];
    int m=(l+r)>>1;
    int ret=0;
    if(L<=m) ret+=query(L,R,l,m,rt<<1);
    if(R>m) ret+=query(L,R,m+1,r,rt<<1|1);
    return ret;
}
int main()
{
    int T,n;
    int k=1;
    scanf("%d",&T);
    while(T--){
        memset(sum,0,sizeof(sum));
        scanf("%d",&n);
        printf("Case %d:\n",k++);
        buildtree(1,n,1);
        string s;
        while(cin>>s){
            int i,j;
            if(s[0]=='E') break;
            scanf("%d%d",&i,&j);
            if(s[0]=='Q'){
                printf("%d\n",query(i,j,1,n,1));
            }
            else if(s[0]=='S')updata(i,-j,1,n,1);
            else updata(i,j,1,n,1);
        }
    }
}
 