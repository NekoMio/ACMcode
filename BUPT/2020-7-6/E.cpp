#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<stack>
#include<vector>
#include<cmath>
#include<queue>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
typedef long long ll;
#define int ll
#define inf 0x3f3f3f3f
const int 
#define m(a) memset(a,0,sizeof(a))
#define mm(a) memset(a,-1,sizeof(a))
#define mi(a) memset(a,0x3f3f3f3f,sizeof(a))
int a[30];
int f[10];
int dp[100000];
void h(int n){
    for(int i=2;i<=n;i++){
        if(n%i==0){
            f[i]++;
            n/=i;
            i--;
        }
    }
}
void ff(int n){
   for(int i=2;i<=n;i++){
        if(n%i==0){
            f[i]--;
            n/=i;
            i--;
        }
    } 
}
signed main(){
    string s;
    cin>>s;
    f[1]=inf;
    int si=s.find('=');
    ll sum1=1,sum2=1;
    for(int i=0;i<si;i+=2){
        if(s[i]>='a'&&s[i]<='z')
            a[s[i]-'a'+1]++;
        else
            ff(s[i]-'0');
    }
    for(int i=si+1;i<s.length();i+=2)
        h(s[i]-'0');
    for(int i=1;i<=9;i++){
        if(f[i]<0){
            cout<<"0";
            return 0;
        }
    }
    ll su=1;
    dp[0]=1;
    for(int i=1;i<=26;i++){
        if(a[i]==0)continue;
        for(int j=a[i];j<=f[2];j++){
            dp[j]=(dp[j]+dp[j-a[i]]) % 1000;
        }
    }
    su*=dp[f[2]];
    su%=1000000007;
    m(dp);
    dp[0]=1;
    for(int i=1;i<=26;i++){
        if(a[i]==0)continue;
        for(int j=a[i];j<=f[3];j++){
            dp[j]=dp[j]+dp[j-a[i]];
        }
    }
    su*=dp[f[3]];
    su%=1000000007;
    m(dp);
    dp[0]=1;
    for(int i=1;i<=26;i++){
        if(a[i]==0)continue;
        for(int j=a[i];j<=f[5];j++){
            dp[j]=dp[j]+dp[j-a[i]];
        }
    }
    su*=dp[f[5]];
    su%=1000000007;
    m(dp);
    dp[0]=1;
    for(int i=1;i<=26;i++){
        if(a[i]==0)continue;
        for(int j=a[i];j<=f[7];j++){
            dp[j]=dp[j]+dp[j-a[i]];
        }
    }
    su*=dp[f[7]];
    su%=1000000007;
    cout<<su<<endl;
}
