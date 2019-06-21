/*
 * @Author: WildRage 
 * @Date: 2017-06-14 08:15:56 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-06-14 08:19:55
 */
#include<iostream>
#include<cstdio>
using namespace std;
double f[10005],g[10005];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=n-1;i>=0;i--)f[i]=f[i+1]+(double)n/(n-i);
    for(int i=n-1;i>=0;i--)g[i]=(double)i/(n-i)*f[i]+g[i+1]+f[i+1]+(double)n/(n-i);
    printf("%.2f",g[0]);
}