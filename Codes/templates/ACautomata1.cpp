#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
char S[1000005];
int Index;
struct Trie{
    Trie *ch[26];
    Trie *fail;
    int id,num;
    Trie(){memset(ch,0,sizeof(ch));fail=NULL;fail=0;num=0;id=++Index;}
}*root,*word[220];
void insert(char *s,int x){
    int len=strlen(s);
    Trie *now=root;
    for(int i=0;i<len;i++){
        if(!now->ch[s[i]-'a'])now->ch[s[i]-'a']=new Trie();
        now=now->ch[s[i]-'a'];
        now->num++;
    }
    word[x]=now;
}
struct edge{
    Trie *END;edge *next;
}*first[26000500];
void add(Trie *a,Trie *b){
    edge *k=new edge;
    k->END=b;
    k->next=first[a->id];
    first[a->id]=k;
}
void get_fail(){
    queue<Trie*> Q;
    Trie *now=root,*temp;
    Q.push(now);
    while(!Q.empty()){
        temp=Q.front();Q.pop();
        for(int i=0;i<26;i++){
            if(temp->ch[i]){
                if(temp==root){
                    temp->ch[i]->fail=root;
                    add(root,temp->ch[i]);
                }
                else{
                    now=temp->fail;
                    while(now&&now->ch[i]==NULL) now=now->fail;
                    if(now==NULL)add(root,temp->ch[i]),temp->ch[i]->fail=root;
                    else add(now->ch[i],temp->ch[i]),temp->ch[i]->fail=now->ch[i];
                }
                Q.push(temp->ch[i]);
            }
        }
    }
}
void dfs(Trie *rt){
    for(edge *now=first[rt->id];now;now=now->next){
        dfs(now->END);
        rt->num+=now->END->num;
    }
}
int main()
{
    int n;
    root=new Trie();
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",S);
        insert(S,i);
    }
    get_fail();
    dfs(root);
    for(int i=1;i<=n;i++){
        printf("%d\n",word[i]->num);
    }
}