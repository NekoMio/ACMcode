#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> ch[2000005];
struct Tree{
    int v;
}tree[2000005];
int m,ans;
int cmp(const int a,const int b){
    return tree[a].v<tree[b].v;
}
void dfs(int rt){
    for(int i=0;i<ch[rt].size();i++) dfs(ch[rt][i]);
    sort(ch[rt].begin(),ch[rt].end(),cmp);
    int i;
    for(i=0;i<ch[rt].size();i++){
        if(tree[rt].v+tree[ch[rt][i]].v-1<=m){
            tree[rt].v+=tree[ch[rt][i]].v-1;
            ans++;            
        }
        else break;        
    }
}
int main()
{
    //freopen("sakura.in","r",stdin);
    //freopen("sakura.out","w",stdout);
    int n,t,s;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)scanf("%d",&tree[i].v);
    for(int i=0;i<n;i++){
        scanf("%d",&t);
        tree[i].v+=t;
        while(t--){
            scanf("%d",&s);
            ch[i].push_back(s);
        }
    }
    dfs(0);
    printf("%d\n",ans);
    //while(1);
}