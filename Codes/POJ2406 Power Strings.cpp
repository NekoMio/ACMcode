#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1000005;
char S[N];
int next[N],len;
void get_next(){
    next[0]=-1;next[1]=0;
    for(int i=2,j=0;i<=len;i++){
        while(~j&&S[j+1]!=S[i])j=next[j];
        next[i]=++j;
    }
}
int main()
{
    while(1){
        memset(S,0,sizeof(S));
        scanf("%s",S);
        len=strlen(S)-1;
        if(S[0]=='.')break;
        get_next();
        //for(int i=1;i<=len;i++)printf("%d ",next[i]);
        //puts("");
        if((len+1)%(len-next[len])==0)printf("%d\n",(len+1)/(len-next[len]));
        else puts("1");
    }
}
