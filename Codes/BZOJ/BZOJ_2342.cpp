#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
char s[500005], s_new[500005 << 1];
int f[500005 << 1], p[500005], m;
set<int> st;
void Manacher()
{
    int id = 0, mx = 0;
    for (int i = 1; i <= m; i++)
    {
        if (i < mx) f[i] = min(f[2 * id - i], mx - i);
        else f[i] = 1;
        while (s_new[i + f[i]] == s_new[i - f[i]]) f[i]++;
        if (i + f[i] > mx) mx = i + f[i], id = i;
    }
}
int h[500005];
int cmp(const int &a, const int &b)
{
    return a - p[a] < b - p[b];
}
int main()
{
    int n;
    scanf("%d", &n);
    scanf("%s", s + 1);
    m = n << 1 | 1;
    s_new[1] = '#'; s_new[0] = '$'; s_new[m + 1] = '\0';
    for (int i = 1; i <= n; i++)
        s_new[i << 1] = s[i], s_new[i << 1 | 1] = '#';
    Manacher();
    for (int i = 1; i <= n; i++) p[i] = (f[i << 1 | 1] - 1) / 2;
    // for (int i = 1; i <= n; i++) printf("%d\n", p[i]);
    for (int i = 1; i <= n; i++) h[i] = i;
    sort(h + 1, h + n + 1, cmp);
    // printf("\n");
    // for (int i = 1; i <= n; i++) printf("%d\n", h[i]);
    set<int>::iterator it;
    int now = 1, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        while (now <= n && h[now] - p[h[now]] <= i) 
            st.insert(h[now++]);
        it = st.upper_bound(i + p[i] / 2);
        if(it != st.begin()) 
            --it, ans = max(ans, (*it - i) * 4);
    }
    // while (1);
    printf("%d", ans);
    // while (1);
}

