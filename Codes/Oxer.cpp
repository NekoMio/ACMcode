#include<cstdio>  
#include<cstring>  
#include<cstdlib>  
#include<cmath>  
#include<algorithm>  
#include<iostream>  
#define maxn 1010000   
  
using namespace std;  
  
int l[1010],r[1010];  
int tag[1010];  
int a[maxn],b[maxn],bel[maxn];  
char s[10];  
int n,m,tot,block,T;  
  
void rebuild(int x)  
{  
    for (int i=l[x];i<=r[x];i++) b[i]=a[i];  
    sort(b+l[x],b+r[x]+1);  
}  
  
int solve(int L,int R,int c)  
{  
    int l=L,r=R,ans=R+1;  
    while (l<=r)  
    {  
        int mid=(l+r)/2;  
        if (b[mid]<c) l=mid+1;  
        else ans=mid,r=mid-1;  
    }  
    return R-ans+1;  
}  
  
int main()  
{  
    scanf("%d%d",&n,&T);  
    block=(int)sqrt(n);tot=(n-1)/block+1;  
    for (int i=1;i<=n;i++)  
    {  
        if (!l[(i-1)/block+1]) l[(i-1)/block+1]=i;  
        r[(i-1)/block+1]=i;  
        bel[i]=(i-1)/block+1;  
    }  
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);  
    for (int i=1;i<=n;i++) b[i]=a[i];  
    for (int i=1;i<=tot;i++) sort(b+l[i],b+r[i]+1);  
    while (T--)  
    {  
        int x,y,z;  
        scanf("%s%d%d%d",s,&x,&y,&z);  
        if (s[0]=='M')  
        {  
            if (bel[x]==bel[y])  
            {  
                for (int i=x;i<=y;i++) a[i]+=z;  
                rebuild(bel[x]);  
            }  
            else  
            {  
                for (int i=bel[x]+1;i<=bel[y]-1;i++) tag[i]+=z;  
                for (int i=x;i<=r[bel[x]];i++) a[i]+=z;  
                rebuild(bel[x]);  
                for (int i=l[bel[y]];i<=y;i++) a[i]+=z;  
                rebuild(bel[y]);  
            }  
        }  
        else  
        {  
            int ans=0;  
            if (bel[x]==bel[y])  
            {  
                for (int i=x;i<=y;i++) if (a[i]>=z) ans++;  
                printf("%d\n",ans);  
            }  
            else  
            {  
                for (int i=bel[x]+1;i<=bel[y]-1;i++) ans+=solve(l[i],r[i],z-tag[i]);  
                for (int i=x;i<=r[bel[x]];i++) if (a[i]>=z) ans++;  
                for (int i=l[bel[y]];i<=y;i++) if (a[i]>=z) ans++;  
                printf("%d\n",ans);  
            }  
        }  
    }  
    return 0;   
}  