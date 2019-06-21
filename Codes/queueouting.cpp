#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[1005];
int main()
{
    int n,b;
    int sum=0;double ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&b),a[b]++;
    n++;
    for(int i=1;i<=1000;i++){
        if(a[i]){
            ans+=(double)n/(n-sum)*a[i];
            sum+=a[i];
        }
    }
    printf("%.2lf",ans);
}