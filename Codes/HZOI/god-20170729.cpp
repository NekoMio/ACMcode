#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
struct data
{
    int l, r, id;
    bool operator<(const data &a) const
    {
        return l == a.l ? r > a.r : l < a.l;
    }
} a[1000001];
int main(int argc, char const *argv[])
{
    stack<data> st;
    int n, s, r;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &s, &r);
        a[i].l = s - r, a[i].id = i, a[i].r = s + r;
    }
    sort(a, a + n);
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d %d %d\n", a[i].l, a[i].r, a[i].id);
    // }
    //while (1)
        ;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i].l == a[i + 1].l && i + 1 != n - 1)
        {
            st.push(a[i]);
            continue;
        }
        if (!st.empty() && a[i].r == st.top().r)
        {
            st.pop();
            ans++;
        }
        if (a[i].r != a[i + 1].l)
        {
            if (!st.empty())
                st.pop();
        }
    }
    printf("%d", ans + n + 1);
    return 0;
}