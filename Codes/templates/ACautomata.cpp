#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct Trie{
    int cnt;
    Trie *ch[26],*fail;
    Trie(){cnt=0;memset(ch,0,sizeof(ch));fail=0;}
}*root;
void insert(char *s,int num){
    int len=strlen(s);
    Trie *now=root;
    for(int i=0;i<len;i++){
        if(!now->ch[s[i]-'a']) now->ch[s[i]-'a']=new Trie();
        now=now->ch[s[i]-'a'];
    }
    now->cnt=num;
}
queue<Trie*> Q;
void KMP(){
    Trie *now=root,*temp;
    Q.push(now);
    while(!Q.empty()){
        temp=Q.front();Q.pop();
        for(int i=0;i<26;i++){
            if(temp->ch[i]){
                now=temp->fail;
                while(now&&!now->ch[i])now=now->fail;
                if(!now) temp->ch[i]->fail=root;
                else temp->ch[i]->fail=now->ch[i];
                Q.push(temp->ch[i]);
            }
        }
    }
}
int Times[11];
void Query(char *s){
    int len(strlen(s));
    Trie *now=root,*temp;
    for(int i=0;i<len;i++){
        while(now&&!now->ch[s[i]-'a'])now=now->fail;
        //now=now->ch[s[i]-'a'];
        if(!now)now=root;
        else{
            now=now->ch[s[i]-'a'];
            temp=now;
            while(temp){
                if(temp->cnt) Times[temp->cnt]++;
                temp=temp->fail;
            }
        }
    }
} 
char text[100000008];
int Main()
{
    freopen("ACautomata.in","r",stdin);
    freopen("ACautomata.out","w",stdout);
    int n;
    scanf("%d",&n);
    root=new Trie();
    char s[11][60];
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]);
        insert(s[i],i);
    }
    KMP();
    scanf("%s",text);
    Query(text);
    for(int i=1;i<=n;i++){
        printf("%s %d\n",s[i],Times[i]);
    }
    return 0;
    //while(1);
}
int A=Main();
int main(){;}