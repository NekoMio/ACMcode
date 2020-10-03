#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
typedef long long ll;
#define inf 0x3f3f3f3f
#define m(a) memset(a,0,sizeof(a))
int main(){
  int t;cin>>t;
  while(t--){
    int n;cin>>n;
    int nw=0;
    for(int i=1;i<=n;i++){
      ll x;cin>>x;
      for(int j=3;j<=sqrt(x);j+=2){
        if(x%j==0){
          nw++;
          break;
        }
      }
    }
    int num=n-nw;
    if(num%2==0){
      if(nw%2){
        cout<<"W"<<endl;
        continue;
      }
      else{
        cout<<"L"<<endl;
        continue;
      }
    }
    else{
      cout<<"W"<<endl;
        continue;
    }
  }
}