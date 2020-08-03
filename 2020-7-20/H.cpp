#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int v[maxn];//v[i]:第i个数的最小质因子
int prime[maxn];//记录找到的素数
int m;//找到素数的个数
int vis[maxn];
void find_primes(int n)
{
    memset(v,0,sizeof(v));
    m=0;
    for(int i=2;i<=n;i++){
        if(v[i]==0){
            v[i]=i;
            prime[++m]=i;
        }
        for(int j=1;j<=m;j++){
            if(prime[j]>v[i]||prime[j]>n/i) break;
            v[i*prime[j]]=prime[j];
        }
    }
}
int main()
{
    find_primes(maxn-5);
    int t,n;scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        memset(vis,0,sizeof(vis));
        pair<int,int> ans[maxn];
        int tot=0;
        for(int i=1;i<=m;i++){
            int p=prime[i];
            if(p>n/2+1) break;
            int flag=1;
            int first_num;
            for(int j=p;j<=n;j+=p){
                //cout<<"test:"<<p<<" "<<j<<" "<<first_num<<" "<<flag<<endl;
                //if(first&&j+p>n) continue;
                if(vis[j]) continue;
                //cout<<"hohho:"<<tot<<" "<<p<<" "<<first<<endl;
                if(flag){
                    first_num=j;
                    //ans[++tot].first=j;
                }
                else{
                    ans[++tot].first=first_num;
                    ans[tot].second=j;
                    vis[first_num]=vis[j]=1;
                    //cout<<"fuck:"<<j<<endl;
                }
                flag=1-flag;
            }
        }
        printf("%d\n",tot);
        for(int i=1;i<=tot;i++){
            printf("%d %d\n",ans[i].first,ans[i].second);
        }
    }
}