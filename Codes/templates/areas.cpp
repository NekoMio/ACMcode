#include<cstdio>
#include<algorithm>
using namespace std;
template<class _Tp>
struct Vector
{
    _Tp x,y;
    _Tp operator * (const Vector &a)
    {
        return x*a.y-a.x*y;
    } 
};
Vector<int> a[105];
int main()
{
    freopen("areas.in","r",stdin);
    freopen("areas.out","w",stdout);
    int n;
    scanf("%d",&n);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    for(int i=1;i<n;i++)
        ans+=a[i]*a[i+1];
    ans+=a[n]*a[1];
    printf("%d",ans/2);
}
    
