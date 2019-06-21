#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char text[1350005];
int n;
struct Trie{
    vector<int> Q;
    Trie *ch[26],*fail;
    Trie(){
        Q.clear();memset(ch,0,sizeof(ch));fail=NULL;
    }
    void* operator new(size_t size);
}*root,*C,*num,*Q[100005];
void* Trie::operator new(size_t size){
    if(C==num){
        C=new Trie[1<<15];
        num=C+(1<<15);
    }
    return C++;
}
void insert(char *s,int x){
    int len=strlen(s);
    Trie *now=root;
    for(int i=0;i<len;i++){
        if(now->ch[s[i]-'a']==NULL)now->ch[s[i]-'a']=new Trie();
        now=now->ch[s[i]-'a'];
    }
    now->Q.push_back(x);
}
void build()
{
    root->fail=NULL;
    Q[0]=root;
    for(int i=0,j=0;i<=j;i++){
        for(int l=0;l<26;l++){
            if(Q[i]->ch[l]){
                Trie *now=Q[i]->fail;
                while(now&&!now->ch[l])now=now->fail;
                Q[i]->ch[l]->fail=now?now->ch[l]:root;
                Q[++j]=Q[i]->ch[l];
            }
        }
    }
}
bool read(){
    char c;
    int head=0;
    if(cin>>c){
        while(c!='$'){
            if(c=='\n'||c==' '){c=getchar();continue;}
            text[head++]=c;c=getchar();
        }
        text[head++]='$';
        return 1;
    }
    return 0;
}
bool via[105];
void work(){
    memset(via,0,sizeof(via));
    Trie *now=root;
    for(int i=0;text[i]!='$';i++){
        while(now&&!now->ch[text[i]-'a'])now=now->fail;
        now=now?now->ch[text[i]-'a']:root;
        for(Trie *i=now;i;i=i->fail){
            if(!i->Q.empty()){
                int l=i->Q.size();
                for(int j=0;j<l;j++)via[i->Q[j]]=1;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)if(via[i])ans++;
    if(ans==n)puts("Yes");
    else puts("No");
}
int main()
{
    freopen("lettera.in","r",stdin);
    freopen("lettera.out","w",stdout);
    root=new Trie();
    char s[1000];
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        insert(s,i);
    }
    build();
    while(read()) work();
}