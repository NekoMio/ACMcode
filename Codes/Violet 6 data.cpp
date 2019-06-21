#include<cstdio>  
#include<ctime>  
#include<cstdlib>  
#include<iostream>  
using namespace std;  
int main()  
{  
    freopen("input.in","w",stdout);  
    int n,m;  
    n=40000;m=50000;  
    srand(time(0));  
    printf("%d %d\n",n,m);  
    for (int i=1;i<=n;i++){  
        int x=rand()*rand()%1000000000+1;  
        cout<<x<<" ";  
    }  
    printf("\n");  
    for (int i=1;i<=m;i++){  
        int l=rand()*rand()%n+1;  
        int r=rand()*rand()%n+1;  
        cout<<l<<" "<<r<<endl;  
    }  
    return 0;  
}  