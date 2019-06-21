#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = int(1e5 + 5) << 1;
const long long INF = 0x3f3f3f3f3f3f3f;
char s[MAXN];
int n, t;
int buc[MAXN], wa[MAXN], wb[MAXN], N;
int r[MAXN], sa[MAXN], Rank[MAXN], height[MAXN];
void GetHeight(int n)
{
    int i, j, k = 0;
    for (i = 0; i < n; i++)
        Rank[sa[i]] = i;
    for (i = 0; i < n; height[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; r[i + k] == r[j + k]; k++);
    return;
}
bool cmp(int *c, int a, int b, int d)
{
    return c[a] == c[b] && c[a + d] == c[b + d];
}
void da(int n, int m = 129)
{
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++) buc[i] = 0;
    for (i = 0; i < n; i++) buc[x[i] = r[i]]++;
    for (i = 1; i < m; i++) buc[i] += buc[i - 1];
    for (i = n - 1; ~i; i--) sa[--buc[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p)
    {
        for (i = n - j, p = 0; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < m; i++) buc[i] = 0;
        for (i = 0; i < n; i++) buc[x[y[i]]]++;
        for (i = 1; i < m; i++) buc[i] += buc[i - 1];
        for (i = n - 1; ~i; i--) sa[--buc[x[y[i]]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++) 
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
    GetHeight(n);
    return;
}
int Min[20][MAXN];
int belong[MAXN], R[MAXN], L[MAXN], Log[MAXN];
int LCP(int a, int b)
{
    if (a == b) return n - a;
    a = Rank[a], b = Rank[b];
    if (a > b) swap(a, b);
    int k = Log[b - a];
    return min(Min[k][a + 1], Min[k][b - (1 << k) + 1]);
}

struct PAM
{
    int len[MAXN], fail[MAXN], tr[MAXN][26];
    int cnt, now, Maxlen;
    PAM() {cnt = 1, fail[0] = fail[1] = 1, len[1] = -1; Maxlen = 0;}
    int extend(int c, int pos)
    {
        int p = now;
        while (s[pos - len[p] - 1] != s[pos]) p = fail[p];
        if (!tr[p][c])
        {
            int np = ++cnt, q = fail[p];
            len[np] = len[p] + 2;
            Maxlen = max(Maxlen, len[np]);
            while (s[pos - len[q] - 1] != s[pos]) q = fail[q];
            fail[np] = tr[q][c];
            tr[p][c] = np;
        }
        now = tr[p][c];
        return pos - len[now];
    }
}pam;
long long f[MAXN];
bool vis[MAXN];
long long Calc(int x)
{
    if (s[x] < 'a') x = n;
    if (vis[x]) return INF;
    if (f[x] > 0) return f[x];
    long long ans = -1;
    vis[x] = 1;
    if (x == n)
    {
        for (int i = 1; i <= t + t; i++)
            ans = max(ans, Calc(L[i]));
    }
    else
    {
        int pos = belong[x];
        for (int i = (pos > t ? 1 : t + 1); i <= (pos > t ? t : t + t); i++)
        {
            int tmp = min(LCP(x, L[i]), min(R[pos] - x, R[i] - L[i]));
            if (x + tmp == R[pos])
                ans = max(ans, Calc(L[i] + tmp) + tmp * 2);
            else if (L[i] + tmp == R[i])
                ans = max(ans, Calc(x + tmp) + tmp * 2);
            else
                ans = max(ans, 1ll * tmp * 2);
        }
    }
    ans = max(ans, 0ll), ans = min(ans, INF);
    vis[x] = 0;
    // printf ("%d %d\n", x, ans);
    return f[x] = ans;
}
int main()
{
    scanf ("%d", &t);
    if (t == 1)
    {
        scanf ("%s", s + 1);
        n = strlen(s + 1);
        for (int i = n + 1; i <= 2 * n; i++)
            s[i] = s[i - n];
        for (int i = 1; i < 2 * n; i++)
            pam.extend(s[i] - 'a', i);
        int p = pam.extend(s[2 * n - 'a'], 2 * n);
        if (p <= n) printf ("Infinity\n");
        else printf ("%d\n", pam.Maxlen);
    }
    else 
    {
        for (int i = 1; i <= t; i++)
        {
            scanf("%s", s + n);
            L[i] = n;
            while (s[n])
                belong[n++] = i;
            R[i] = n;
            s[n++] = 'a' - 1;
        }
        int pos = 0;
        for (int i = t + 1; i <= t + t; i++)
        {
            L[i] = n;
            while (s[pos] >= 'a')
                belong[n] = i, s[n++] = s[pos++];
            R[i] = n;
            s[n++] = s[pos++];
            reverse(s + L[i], s + R[i]);
        }
        s[n++] = 0;
        for (int i = 0; i < n; i++)
            r[i] = s[i];
        da(n);
        for (int i = 2; i <= n; i++)
            Log[i] = Log[i >> 1] + 1;
        memset (Min, 0x3f, sizeof (Min));
        for (int i = 0; i <= n; i++)
            Min[0][i] = height[i];
        //return 0;
        for (int i = 1; i <= Log[n]; i++)
            for (int j = 0; j <= n - (1 << i) + 1; j++)
                Min[i][j] = min(Min[i - 1][j], Min[i - 1][j + (1 << (i - 1))]);
        memset (f, -1, sizeof (f));
        long long ans = Calc(n);
        for (int i = 1; i <= t; i++)
        {
            for (int j = L[i], k = R[i + t] - 1; j < R[i]; j++, k--)
            {
                int tmp = min(LCP(j, k), min(R[i] - j, R[i + t] - k));
                if (j + tmp == R[i])
                    ans = max(ans, Calc(k + tmp) + 2 * tmp - 1);
                else if (k + tmp == R[i + t])
                    ans = max(ans, Calc(j + tmp) + 2 * tmp - 1);
                else
                    ans = max(ans, 2ll * tmp - 1);
            }
            for (int j = L[i] + 1, k = R[i + t] - 1; j < R[i]; j++, k--)
            {
                int tmp = min(LCP(j, k), min(R[i] - j, R[i + t] - k));
                if (j + tmp == R[i])
                    ans = max(ans, Calc(k + tmp) + 2 * tmp);
                else if (k + tmp == R[i + t])
                    ans = max(ans, Calc(j + tmp) + 2 * tmp);
                else
                    ans = max(ans, 2ll * tmp);
            }
        }
        if (ans >= INF) printf ("Infinity\n");
        else printf ("%lld\n", ans);
    }
    // while (1);
}
