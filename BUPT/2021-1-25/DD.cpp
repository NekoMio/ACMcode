#include<iostream>
#include<cstdio>
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
#define inf 0x3f3f3f3f
#define m(a) memset(a,0,sizeof(a))
#define mm(a) memset(a,-1,sizeof(a))
#define mi(a) memset(a,0x3f3f3f3f,sizeof(a))
#define hzt cout<<1;
int a[10];
int main(){
  for(int i=1;i<=10000;i++){
    int q=i;
    while(q){
      a[q%10]+=1;
      q/=10;
    }
    int p=0;
    for(int j=0;j<=9;j++){
      if(a[j]>=a[p]){
        p=j;
      }
    }
    cout<<i<<" "<<p<<endl;
  }
}