/*
 * @Author: WildRage 
 * @Date: 2017-06-13 10:24:04 
 * @Last Modified by:   WildRage 
 * @Last Modified time: 2017-06-13 10:24:04 
 */
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct Trie_Node{
    Trie_Node *ch[27];
    Trie_Node(){
        memset(ch,0,sizeof(ch));
    }
}*root;
int ans;
inline void insert(char *s){
    int len=strlen(s);
    Trie_Node *now=root;
    for(int i=0;i<len;i++){
        if(now->ch[s[i]-'A']==NULL)
            now->ch[s[i]-'A']=new Trie_Node,ans++;
        now=now->ch[s[i]-'A'];
    }
}
int main()
{
    freopen("trie.in","r",stdin);
    freopen("trie.out","w",stdout);
    char s[105];
    root=new Trie_Node;ans++;
    while(scanf("%s",s)!=EOF) insert(s);
    printf("%d",ans);
}