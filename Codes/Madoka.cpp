#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
char S[15005];
long long ans;
int fail[15005],K;
int KMP(char *s){
    int n=strlen(s+1);
    int j=0,k=0;
    for(int i=2;i<=n;i++){
        while(j&&s[j+1]!=s[i])j=fail[j];
        if(s[j+1]==s[i])j++;
        fail[i]=j;
        while(k&&s[k+1]!=s[i])k=fail[k];
        if(s[k+1]==s[i])k++;
        while(2*k>=i)k=fail[k];
        if(k>=K)ans++;
    }
}
int main()
{
    scanf("%s",S+2);
    scanf("%d",&K);
    int n=strlen(S+2);
    for(int i=1;i<=n;i++) KMP(S+i);
    printf("%lld\n",ans);
    //while(1);
}