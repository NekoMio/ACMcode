#include <cstdio>
int main()
{
    int n,ans=0,x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        ans^=x;
    }
    if(ans || (n & 1)) puts("first player");
    else puts("second player");
}