#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const long long mod=1000000007;
char S[1000005];
int fail[1000005],num[1000005];
int main()
{
    //freopen("zoo.in","r",stdin);
    //freopen("zoo.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",S+1);
        long long ans=1;
        int n=strlen(S+1);
        int j=0;
        num[1]=1;
        for(int i=2;i<=n;i++){
            while(j&&S[j+1]!=S[i])j=fail[j];
            if(S[j+1]==S[i])j++;
            fail[i]=j;
            num[i]=num[j]+1;
        }
        j=0;
        for(int i=2;i<=n;i++){
            while(j&&S[j+1]!=S[i])j=fail[j];
            if(S[j+1]==S[i])j++;
            while(j&&(j<<1)>i)j=fail[j];
            ans=ans*(num[j]+1)%mod;
        }
        printf("%lld\n",ans);
    }
}