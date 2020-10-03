#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int p[maxn];
int c[maxn];
int m;
int a[maxn];
int n;
void divide(int x)
{
  m=0;
  for(int i=2;i<sqrt(x);i++){
    if(x%i==0){
      p[++m]=i;c[m]=0;
      while(x%i==0) x/=i,c[m]++;
    }
  }
  if(x>1) p[++m]=x,c[m]=1;
}
int num2=0;
int num3=0;
void pre()
{
  if(p[1]==2){
    num2+=c[1];
    for(int i=2;i<=m;i++) num3+=c[i];
    return ;
  }
  for(int i=1;i<=m;i++){
   num3+=c[i]; 
  }
}
void init()
{
  num2=num3=0;
  m=0;
}
int NUM2=0;
int NUM23=0;
int NUM3=0;
void solve()
{
  for(int i=1;i<=n;i++){
    init();
    divide(a[i]);
    pre();
    if(num2&&!num3) NUM2++;
    else if(num2&&num3) NUM23++;
    else NUM3++;
  }
  int flag2,flag23,flag3;
  if(NUM2%2==0) flag2=0;
  else flag2=1;
  if(NUM23==3) flag23=0;
  else flag23=1;
  if(NUM3==3) flag3=1;
  else flag3=0;
  if((flag2+flag23+flag3)%2==0) cout<<"W"<<endl;
  else cout<<"L"<<endl;
}
int main(){
  int t;cin>>t;
  while(t--){
    NUM2=NUM23=NUM3=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    solve();
  }
}