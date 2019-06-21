#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int N;
int c[50010],a[50010];
inline int lowbit(int x){return x&(-x);}
void update(int x,int num){
    while(x<=N){
        c[x]+=num;
        x+=lowbit(x);
    }
}
int sum(int x){
    int sum=0;
    while(x>0){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}
inline int sum(int x1,int x2){return sum(x2)-sum(x1-1);}
int main()
{
    int T;
    cin>>T;
    for(int ii=1;ii<=T;ii++){
        scanf("%d",&N);
        printf("Case %d:\n",ii);
        //cout<<"Case "<<ii<<":"<<endl;
        memset(c,0,sizeof(c));
        memset(a,0,sizeof(a));
        for(int i=1;i<=N;i++){
            scanf("%d",&a[i]);
            //cin>>a[i];
            update(i,a[i]);
        }
        string s;
        int i,j;
        while(cin>>s){
            if(s=="End")break;
            scanf("%d%d",&i,&j);
            //cin>>i>>j;
            if(s=="Add"){update(i,j);continue;}
            if(s=="Sub"){update(i,-j);continue;}
            if(s=="Query"){cout<<sum(i,j)<<endl;continue;}
        }
    }
}