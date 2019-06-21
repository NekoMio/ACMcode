#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[55], b[1025], m;
int Sum[1025];
bool OK;
int T, Wis, mid;
void dfs(int x, int now)
{
    if(!x)
    {
        OK = 1;
        return;
    }
    if(Sum[mid] + Wis > T) return;
    for (int i = now; i <= m; i++)
    {
        if(a[i] >= b[x])
        {
            a[i] -= b[x];
            if (a[i] < b[1])
            	Wis += a[i];
            if(b[x] == b[x - 1])
            	dfs(x - 1, i);
            else
            	dfs(x - 1, 1);
            if (a[i] < b[1])
            	Wis -= a[i];
            a[i] += b[x];
            if(OK)
                return;
        }
    }
}
bool Judge(int mid)
{
    OK = 0;
    dfs(mid, 1);
    return OK;
}
int main()
{
	// freopen("fence8.in","r",stdin);
	// freopen("fence8.out","w",stdout);
    int n;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", a + i);
    	T += a[i];
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", b + i);
    }
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
    	Sum[i] = Sum[i - 1] + b[i];
    while(Sum[n] > T) n--;
    sort(a + 1, a + m + 1);
    int l = 1, r = n + 1;
    int ans = 0;
    while(l < r)
    {
    	Wis = 0;
        mid = l + r >> 1;
        //printf("%d\n", mid);
        if(Judge(mid))
            ans = mid, l = mid + 1;
        else
            r = mid;
    }
    printf("%d", ans);
}