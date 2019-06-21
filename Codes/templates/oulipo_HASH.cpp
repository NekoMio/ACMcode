#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
unsigned long long B[1000050],hash[1000050];
char T[1000050],S[1000050];
int main()
{
    freopen("oulipo.in","r",stdin);
    freopen("oulipo.out","w",stdout);
    int base=31;
    B[0]=1;
    for(int i=1;i<=1000005;i++)B[i]=B[i-1]*base;
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%s",T);
        scanf("%s",S);
        int lenT=strlen(T);
        int lenS=strlen(S);
        unsigned long long sum=0;
        for(int i=lenT-1;i>=0;i--){
            sum=sum*base+T[i];
        }
        hash[lenS]=0;
        for(int i=lenS-1;i>=0;i--){
            hash[i]=hash[i+1]*base+S[i];
        }
        int ans=0;
        for(int i=0;i<=lenS-lenT;i++){
            if(sum==hash[i]-hash[i+lenT]*B[lenT])
                ans++;
        }
        printf("%d\n",ans);
    }
}