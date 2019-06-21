#include <stdio.h>
#include <cstring>
#include <iostream>
#define MAXN 100500
using namespace std;
typedef long long ll;
char ch[MAXN];
int k,n;
int wa[MAXN],wb[MAXN],wv[MAXN],w[MAXN];
int sa[MAXN],r[MAXN],rank[MAXN],h[MAXN];
int log_2[MAXN],st[20][MAXN];
int L,R;
 
 
inline bool cmp(int *r,int x,int y,int l){
    return r[x]==r[y] && r[x+l] == r[y+l];
}
 
void get_sa(int *r,int *sa,int n,int m){
    int *x=wa,*y=wb,p=1;
    for(int i=0;i<m;i++)w[i]=0;
    for(int i=0;i<n;i++)w[x[i]=r[i]]++;
    for(int i=1;i<m;i++)w[i]+=w[i-1];
    for(int i=n-1;i>=0;i--)sa[--w[x[i]]]=i;
    for(int j=1;j<=n;j<<=1,m=p){
        p=0;
        for(int i=n-j;i<n;i++)y[p++]=i;
        for(int i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
        for(int i=0;i<n;i++)wv[i]=x[y[i]];
        for(int i=0;i<m;i++)w[i]=0;
        for(int i=0;i<n;i++)w[wv[i]]++;
        for(int i=1;i<m;i++)w[i]+=w[i-1];
        for(int i=n-1;i>=0;i--)sa[--w[wv[i]]]=y[i];
        swap(x,y);p=1;x[sa[0]]=0;
        for(int i=1;i<n;i++)x[sa[i]]=cmp(y,sa[i-1],sa[i],j)? p-1 : p++;
    }
    for(int i=1;i<n;i++)rank[sa[i]]=i;
    int k=0,j;
    for(int i=0;i<n-1;h[rank[i++]]=k)
        for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
 
void query_kth(ll k){
    for(int i=1;i<=n;i++){
        if(k>n-sa[i]-h[i])k-=n-sa[i]-h[i];
        else{
            L=sa[i],R=sa[i]+h[i]+k-1;
            return;
        }
    }
}
 
void RMQ_init(){
    log_2[1]=0;
    for(int i=2;i<=n;i++){
        log_2[i]=log_2[i-1];
        if((1<<log_2[i-1]+1)==i)log_2[i]++;
    }
    for(int i=1;i<=n;i++)st[0][i]=h[i];
    int now = 1;
    for(int i=1;i<=log_2[n];i++){
        for(int j=1;j<=n;j++){
            st[i][j]=st[i-1][j];
            if(j+now<=n)st[i][j]=min(st[i][j],st[i-1][j+now]);
        }
        now<<=1;
    }
}
 
int query(int l,int r){
    if(l==r)return n-sa[l]-1;
    if(l>r)swap(l,r);l++;
    int k = log_2[r-l+1];
    int w=1<<k;
    return min(st[k][l],st[k][r-w+1]);
}
 
bool ok(int l,int r){
    int len = query(rank[l],rank[L]);
    int len1=r-l+1,len2=R-L+1;
    if(l==L&&R==r)return 0;
    if(len1>len2 && len >= len2)return 1;
    if(len1<len2 && len >= len1)return 0;
    if(len >= len1 && len >= len2)return len1>len2;
    return ch[l+len]>ch[L+len];
}
 
bool check(ll x){
    query_kth(x);//kth子串
    int now = n-1;
    int cnt = 1;
    for(int i=n-1;i>=0;i--)
        if(ok(i,now)){//比较大小
            cnt ++;
            now=i;
            if(cnt >k)return 0;
        }
    return 1;
}
 
int main(){
    scanf("%d",&k);
    scanf("%s",ch);
    n=strlen(ch);
    for(int i=0 ;i <n;i++)r[i]=ch[i]-'a'+1;
    r[n]=0;
    get_sa(r,sa,n+1,30);
    ll l=1,r=0;
    for(int i=1;i<=n;i++)r+=n-sa[i]-h[i];
    RMQ_init();
    int ans = 0;
    while(l<=r){
        ll mid=l+r>>1;
        if(check(mid))r=mid-1;
        else l=mid+1;
    }
    query_kth(l);
    for(int i=L;i<=R;i++)printf("%c",ch[i]);
}