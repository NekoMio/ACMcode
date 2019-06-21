#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[1000005],T[1000005],ans[1000005];
int fail[1000005],len,next[1000005];
void get_next(){
    fail[0]=-1;fail[1]=0;
    for(int i=2,j=0;T[i];i++){
        while(~j&&T[j+1]!=T[i])j=fail[j];
        fail[i]=++j;
    }
}
int main()
{
    //freopen("4.in","r",stdin);
    //freopen("0.out","w",stdout);
    scanf("%s",a);
    scanf("%s",T);
    len=strlen(T);
    get_next();
    int top=0;
    for(int i=0,j=0;a[i];i++){
        j=next[top];
        ans[++top]=a[i];
        while(~j&&T[j+1]!=a[i])j=fail[j];
        j++;
        next[top]=j;
        if(j+1==len)top-=len;
    }
    ans[++top]='\0';
    printf("%s",ans+1);
    //while(1);
}