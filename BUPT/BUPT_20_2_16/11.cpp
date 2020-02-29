#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstring>
#include<cmath>
#include<vector>
#include<string.h>
#define LL long long
using namespace std;
const int INF=0x3f3f3f3f;
int dp2[111][111];
int dp[111];
char s1[111],s2[111];
int main()
{
    //freopen("D:\\in.txt","r",stdin);
    int T,cas,i,j,k,n,m,len;
    while(scanf("%s%s",s1+1,s2+1)!=EOF)
    {
       len=strlen(s2+1);
       memset(dp2,0,sizeof(dp2));
       memset(dp,0,sizeof(dp));
       for(i=1;i<=len;i++)
        dp2[i][i]=1;
       for(i=len-1;i>=1;i--)
       {
           for(j=i+1;j<=len;j++)
           {
                //dp2[i][j]=min(dp2[i+1][j]+(s2[i]==s2[i+1]?0:1),dp2[i+1][j-1]+(s2[j]==s2[j-1]?0:1));
                dp2[i][j]=dp2[i+1][j]+1;
                for(k=i+1;k<=j;k++)
                {
                    if(s2[i]==s2[k])
                    dp2[i][j]=min(dp2[i][j],dp2[i+1][k-1]+dp2[k][j]);
                }
           }
       }
    //    for (int i = 1; i <= len; i++) {
    //   for (int j = 1; j <= len; j++) {
    //     printf ("%d ", dp2[i][j]);
    //   }
    //   printf ("\n");
    // }
       for(i=1;i<=len;i++)
       {
           dp[i]=dp2[1][i];
           if(s1[i]==s2[i])
           {
               if(i==1)
                dp[i]=0;
               else
                dp[i]=dp[i-1];
           }
           else
           {
                for(j=1;j<i;j++)
                {
                    dp[i]=min(dp[i],dp[j]+dp2[j+1][i]);
                }
           }
       }
       printf("%d\n",dp[len]);
    }
    return 0;
}