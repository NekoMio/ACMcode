/*
 * @Author: WildRage 
 * @Date: 2017-06-13 14:48:36 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-06-13 15:08:00
 */
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct edge{
    int END,next,v;
}v[1000005];
int first[100005],p;
int XOR[100005];
void add(int s,int e,int c){
    v[p].END=e;
    v[p].next=first[s];
    v[p].v=c;
    first[s]=p++;
}
void dfs(int rt,int fa,int Xor){
    XOR[rt]=Xor;
    for(int i=first[rt];i!=-1;i=v[i].next){
        if(v[i].END==fa)continue;
        dfs(v[i].END,rt,Xor^v[i].v);
    }
}
struct Trie{
    Trie *ch[2];
    void *operator new (size_t size);
}*root,*C,*num;
void* Trie::operator new (size_t size){
    if(C==num){
        C=new Trie[1<<15];
        memset(C,0,sizeof(Trie)*(1<<15));
        num=C+(1<<15);
    }
    return C++;
}
void insert(int num){
    Trie *now=root;
    for(int i=30;i>=0;i--){
        int t=num&(1<<i);
        t>>=i;
        if(now->ch[t]==NULL)now->ch[t]=new Trie();
        now=now->ch[t];
    }
}
int main()
{
    int n;
    memset(first,-1,sizeof(first));
    scanf("%d",&n);
    int u,v,w;
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1,0,0);
    root=new Trie();
    for(int i=1;i<=n;i++){
        insert(XOR[i]);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        Trie *now=root;
        int sum=0;
        for(int j=30;j>=0;j--){
            int t=XOR[i]&(1<<j);
            t>>=j;
            if(now->ch[t^1])now=now->ch[t^1],sum^=(t^1)<<j;
            else now=now->ch[t],sum^=(t)<<j;
        }
        ans=max(ans,sum^XOR[i]);
    }
    printf("%d",ans);
    //while(1);
}