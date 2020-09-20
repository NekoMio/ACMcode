#include<bits/stdc++.h>
using namespace std;
#define m(a) memset(a,0x3f3f3f3f,sizeof(a))
char s[100005],c[100005];
char q[10][6][4]={
  "QQQ","QQQ","QQQ","QQQ","QQQ","QQQ",
  "QQW","QWQ","WQQ","QQW","QWQ","WQQ",
  "QQE","QEQ","EQQ","QQE","QEQ","EQQ",
  "WWW","WWW","WWW","WWW","WWW","WWW",
  "WWQ","WQW","QWW","WWQ","WQW","QWW",
  "EWW","EWW","WEW","WWE","WEW","WWE",
  "EEE","EEE","EEE","EEE","EEE","EEE",
  "QEE","EQE","EEQ","QEE","EQE","EEQ",
  "WEE","EWE","EEW","WEE","EWE","EEW",
  "QWE","QEW","EWQ","EQW","WQE","WEQ"
};
int dp[100005][6],tot;
int le(int nn,int x,int y,int z){
  if(q[x][z][0]==q[nn][y][1]&&q[x][z][1]==q[nn][y][2]){
    return 1;
  }
  if(q[x][z][0]==q[nn][y][2])return 2;
  return 3;
}
map<char,int>val;
int main(){
  cin>>s+1;
  val['Y']=0;
  val['V']=1;
  val['G']=2;
  val['C']=3;
  val['X']=4;
  val['Z']=5;
  val['T']=6;
  val['F']=7;
  val['D']=8;
  val['B']=9;
  m(dp);
  int n=strlen(s+1);int ans=n;
  for(int i=1;i<=n;i++){
      if(s[i]==s[i-1]){
        continue;
      }
      c[++tot]=s[i];
  }
  int minn=0x3f3f3f3f;
  for(int i=0;i<6;i++){
    dp[1][i]=3;
  }
  for(int i=2;i<=tot;i++){
    for(int j=0;j<6;j++){
      for(int k=0;k<6;k++){
          dp[i][k]=min(dp[i][k],dp[i-1][j]+le(val[c[i-1]],val[c[i]],j,k));
      }
    }
  }
  for(int i=0;i<6;i++){
    minn=min(dp[tot][i],minn);
  }

  cout<<minn+ans<<endl;

}