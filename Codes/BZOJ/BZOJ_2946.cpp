#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
// #define int long long 
const int MAXN = 2005;
char s[4005];
int ans[MAXN << 1];
struct sam
{
    int a[MAXN << 1][27], fa[MAXN << 1], Max[MAXN << 1];
    int Min[MAXN << 1], v[MAXN << 1], q[MAXN << 1];
    int cnt, last;
    sam()
    {
        last = ++cnt;
    }
    void extend(int c)
    {
        int p = last, np = last = ++cnt;
        Max[np] = Max[p] + 1;
        while (!a[p][c] && p) a[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = a[p][c];
            if (Max[q] == Max[p] + 1) fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                memcpy(a[nq], a[q], sizeof(a[q]));
                fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
    }
    void PRE()
    {
        for (int i = 1; i <= cnt; i++) ans[i] = Max[i];
        for (int i = 1; i <= cnt; i++) v[Max[i]]++;
        for (int i = 1; i <= cnt; i++) v[i] += v[i - 1];
        for (int i = cnt; i >= 1; i--) q[v[Max[i]]--] = i;
    }
    void Update(char *s)
    {
        int p = 1, len = 0;
        memset (Min, 0, sizeof (Min));
        int n = strlen(s + 1);
        for (int i = 1; i <= n; i++)
        {
            int c = s[i] - 'a';
            // printf ("p = %d\n", p);
            while (!a[p][c] && p) p = fa[p];
            if (p == 0) p = 1, len = 0;
            else  len = min(len, Max[p]) + 1, p = a[p][c];
            Min[p] = max(Min[p], len);
        }
        for (int i = cnt; i >= 1; i--)
            Min[fa[q[i]]] = max(Min[fa[q[i]]], Min[q[i]]);
        for (int i = 1; i <= cnt; i++)
            ans[i] = min(ans[i], Min[i]);
    }
}SAM;

int main()
{
    // freopen ("1.out", "w", stdout);
    int n;
    std::cin >> n;
    std::cin >> (s + 1);
    int m = strlen(s + 1);
    for (int i = 1; i <= m; i++)
        SAM.extend(s[i] - 'a');
    SAM.PRE();
    // for (int i = 1; i <= SAM.cnt; i++) printf ("%d\n", SAM.q[i]);
    for (int i = 2; i <= n; i++)
    {
        std::cin >> s + 1;
        SAM.Update(s);
        // printf (":::%d\n", i - 1);
        // for (int j = 1; j <= SAM.cnt; j++) printf ("%d\n", ans[j]);
    }
    int Ans = 0;
    for (int i = 1; i <= SAM.cnt; i++)
        Ans = max(Ans, ans[i]);
    std::cout << Ans << std::endl;
}