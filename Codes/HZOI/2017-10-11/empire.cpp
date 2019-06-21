#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
int a[500005], A[500005], pos[500005];
int B[500005];
int f[500005];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q1, Q2;
signed main()
{
    int n, k;
    scanf ("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf ("%lld", &a[i]), A[i] = A[i - 1] + a[i];
    for (int i = 1; i <= n; i++)
        scanf ("%lld", &B[i]);
    for (int i = 0; i < n; i++)
    {
        int l = i + 1, r = n;
        while (l <= r)
        {
            int mid = l + r >> 1;
            if(A[mid] - A[i] > B[i + 1]) r = mid - 1;
            else pos[i] = mid, l = mid + 1;
        }
    }
    memset (f, 0x3f, sizeof (f));
    f[0] = 0;
    if(pos[0])
        Q1.push(pair<int, int>(B[1], 0));
    else
        Q2.push(pair<int, int>(0, 0));
    for (int i = 1; i <= n; i++)
    {
        while (!Q1.empty())
        {
            if (Q1.top().second < i - k) 
            {
                Q1.pop();
                continue;
            }
            if (pos[Q1.top().second] < i) 
            {
                Q2.push(pair<int, int> (f[Q1.top().second] - A[Q1.top().second], Q1.top().second));
                Q1.pop();
                continue;
            }
            f[i] = min(f[i], Q1.top().first);
            break;
        }
        while (!Q2.empty())
        {
            // printf("%d\n", Q2.size());
            if (Q2.top().second < i - k)
            {
                Q2.pop();
                continue;
            }
            f[i] = min(f[i], Q2.top().first + A[i]);
            break;
        }
        Q1.push(pair<int, int>(f[i] + B[i + 1], i));
    }
    printf("%lld\n", f[n]);
    // while(1);
}
