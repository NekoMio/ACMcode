/*
 * @Author: WildRage 
 * @Date: 2017-06-13 17:54:04 
 * @Last Modified by:   WildRage 
 * @Last Modified time: 2017-06-13 17:54:04 
 */
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
struct Trie{
    int T;
    Trie *ch[2];
    void *operator new (size_t size);
}*root,*num,*C;
void* Trie::operator new(size_t size){
    if(C==num){
        C=new Trie[1<<10];
        memset(C,0,sizeof(Trie)*(1<<10));
        num=C+(1<<10);
    }
    return C++;
}
int Index=0,cnt;
void insert(char *s){
    Trie *now=root;
    for(int i=0;i<cnt;i++){
        if(now->ch[s[i]-'0']==NULL)now->ch[s[i]-'0']=new Trie;
        now=now->ch[s[i]-'0'];
    }
    now->T=++Index;
}
int st[10005];
int query(char *s,int l,int r){
    int h=0;
    Trie *now=root;
    for(int i=0;i<cnt;i++){
        if(now->ch[s[i]-'0']==NULL)break;
        now=now->ch[s[i]-'0'];
        if(!now->T)continue;
        if(now->T>r)continue;
        if(now->T<l)while(h>=1)h--;
        if(now->T>=l&&now->T<=r){
            while(h>=1&&now->T<st[h])h--;
            st[++h]=now->T;
        }
    }
    return h;
}
int main()
{
    int m;
    scanf("%d",&m);
    char S[2],s[105];
    int a[5],b,l,r;
    root=new Trie;
    for(int i=1;i<=m;i++){
        scanf("%s",S);
        if(S[0]=='A'){
            cnt=0;
            scanf("%d.%d.%d.%d/%d",&a[1],&a[2],&a[3],&a[4],&b);
            for(int i=1;i<=4;i++){
                for(int j=7;j>=0;j--){
                    if(cnt+1>b)break;
                    if((a[i]>>j)&1)s[cnt]='1';
                    else s[cnt]='0';
                    cnt++;
                }
            }
            insert(s);
        }
        else{
            cnt=0;
            scanf("%d.%d.%d.%d %d %d",&a[1],&a[2],&a[3],&a[4],&l,&r);
            for(int i=1;i<=4;i++){
                for(int j=7;j>=0;j--){
                    if((a[i]>>j)&1)s[cnt]='1';
                    else s[cnt]='0';
                    cnt++;
                }
            }
            printf("%d\n",query(s,l,r));
        }
    }
}