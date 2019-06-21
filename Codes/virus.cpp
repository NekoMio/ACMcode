#include<cstdio>
#include<cstring>
#include<queue>
#include<cctype>
using namespace std;
struct Trie{
    int cnt;
    Trie *ch[26];
    Trie *fail;
    Trie(){cnt=0;memset(ch,0,sizeof(ch));fail=NULL;}
}*root;
void Insert(char *s,int x){
    int len=strlen(s);
    Trie *now=root;
    for(int i=0;i<len;i++){
        if(!now->ch[s[i]-'A'])now->ch[s[i]-'A']=new Trie();
        now=now->ch[s[i]-'A'];
    }
    now->cnt=x;
}
void get_fail(){
    queue<Trie*> Q;
    Trie *now=root,*temp;
    Q.push(now);
    while(!Q.empty()){
        temp=Q.front();Q.pop();
        for(int i=0;i<26;i++){
            if(temp->ch[i]){
                if(temp==root)temp->ch[i]->fail=root;
                else{
                    now=temp->fail;
                    while(now&&!now->ch[i])now=now->fail;
                    if(!now) temp->ch[i]->fail=root;
                    else temp->ch[i]->fail=now->ch[i];
                    Q.push(temp->ch[i]);
                }
            }
        }
    }
}
int Times[1005];
void Query(char *s){
    int len(strlen(s));
    Trie *now=root,*temp;
    for(int i=0;i<len;i++){
        while(now&&!now->ch[s[i]-'A'])now=now->fail;
        if(!now) now=root;
        else {
            now=now->ch[s[i]-'A'];
            temp=now;
            while(temp){
                if(temp->cnt) Times[temp->cnt]++;
                temp=temp->fail;
            }
        }
    }
}
char s[1005][100],text[2000005],S[2000005];
int main()
{
    int n;
    root=new Trie();
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]);
        Insert(s[i],i);
    }
    get_fail();
    scanf("%s",text);
    int len=strlen(text),l=0;
    for(int i=0;i<len;i++){
        if(text[i]>='A'&&text[i]<='Z'){
            S[l++]=text[i];
        }
        else {
            S[l]='\0';
            Query(S);
            l=0;
        }
    }
    for(int i=1;i<=n;i++)
        if(Times[i])
            printf("%s: %d\n",s[i],Times[i]);
    //while(1);
}