#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
struct node{
    int tot;
    vector<int> min_f;
}a[maxn];
char s[maxn];
int n;
void solve()
{
    int ptr1=-1,ptr0=-1;
    int len=strlen(s);
    int num;
    int tot=0;
    vector<int> temp;
    for(int i=len-1;i>=0;i--){
        s[i]=='a'?num=0:num=1;
        if(num){
            if(ptr1==-1){
                temp.push_back(0);
                tot++;
            }
            else{
                temp[ptr1]=tot-ptr1;
                temp.push_back(0);
                tot++;
            }
            ptr1=tot-1;
        }
        else{
            if(ptr0==-1){
                temp.push_back(0);
                tot++;
            }
            else{
                temp[ptr0]=tot-ptr0;
                temp.push_back(0);
                tot++;
            }
            ptr0=tot-1;
        }
        a[i].min_f=temp;
        a[i].tot=tot;
    }
    for(int i=0;i<len;i++) reverse(a[i].min_f.begin(),a[i].min_f.end());
//  for(int i=0;i<len;i++){
//      for(int j=0;j<a[i].min_f.size();j++){
//          cout<<a[i].min_f[j]<<" ";
//      }
//      cout<<endl;
//  }
}
int cmp(node &n1,node &n2)
{
    for(int i=0;i<min(n1.tot,n2.tot);i++){
        if(n1.min_f[i]!=n2.min_f[i]){
            return n1.min_f[i]<n2.min_f[i];
        }
    }
    return n1.tot<n2.tot;
}
int main()
{
    while(scanf("%d%s",&n,s)!=EOF){
        solve();
        sort(a,a+n,cmp);
        for(int i=0;i<n;i++){
            printf("%d ",n+1-a[i].tot);
        }
        printf("\n");
    }
}