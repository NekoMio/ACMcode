/*
 * @Author: WildRage 
 * @Date: 2017-06-12 17:26:02 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-06-12 19:01:45
 */
#include<cstdio>
#include<cstring>
using namespace std;
char S[1000005],T[1000005];
int next[1000005];
int len;
void get_next(char *a,int n){
    int j=0,k=-1;
    next[0]=-1;
    while(j<n){
        if(k==-1||T[j]==T[k]){
            next[++j]=++k;
        }
        else k=next[k];
    }
}
int main()
{
    freopen("oulipo.in","r",stdin);
    freopen("oulipo.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--){
        int ans=0;
        scanf("%s",T);scanf("%s",S);
        int n=strlen(S);
        int m=strlen(T);
        get_next(T,m);
        int i=0,j=0;
        for(int i=0;i<n;i++){
            while(j>0&&S[i]!=T[j]) j=next[j];
            if(S[i]==T[j])j++;
            if(j==m)ans++,j=next[j];
        }
        printf("%d\n",ans);
    }
}