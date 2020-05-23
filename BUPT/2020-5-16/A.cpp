#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<stack>
#include<vector>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
#define inf 0x3f3f3f3f
#define m(a) memset(a,0,sizeof(a))
#define mm(a) memset(a,-1,sizeof(a))
#define mi(a) memset(a,0x3f3f3f3f,sizeof(a))
int poww(int a, int b,int m) {
    long long ans = 1, base = a;
    while (b != 0) {
        if (b & 1 != 0){
            ans *= base;
            ans%=m;
        }
        base *= base;
        base %= m;
        b >>= 1;
    }
    return ans;
}
int main(){
    int t,a,b;cin>>t;
    while(t--){
        cin>>a>>b;
        ll q=poww(3,a+b,1e9+7);
        ll p=poww(2,a*b,1e9+7);
        int ans=1ll * q*p % 1000000007;
        cout<<ans<<endl;
    }
}