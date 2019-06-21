#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAXN = 5e5 + 5;
char s[MAXN];
struct Sam
{
    int last, cnt;
    int a[MAXN << 1][26], fa[MAXN << 1], Max[MAXN << 1], val[MAXN << 1], Sum[MAXN << 1];
    int v[MAXN], q[MAXN << 1];
    Sam()
    {
        last = ++cnt;
    }
    void extend(int c)
    {
        int p = last, np = last = ++cnt;
        Max[np] = Max[p] + 1, val[np] = 1;
        while (!a[p][c] && p) a[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = a[p][c];
            if (Max[p] + 1 == Max[q]) fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                memcpy(a[nq], a[q], sizeof (a[nq]));
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
    }
    void pre(int T)
    {
        int n = strlen(s + 1);
        for (int i = 1; i <= n; i++) extend(s[i] - 'a');
        for (int i = 1; i <= cnt; i++) v[Max[i]]++;
        for (int i = 1; i <= n; i++) v[i] += v[i - 1];
        for (int i = cnt; i >= 1; i--) q[v[Max[i]]--] = i;
        for (int i = cnt; i >= 1; i--)
        {
            int now = q[i];
            if (T == 1) val[fa[now]] += val[now];
            else val[now] = 1;
        }
        val[1] = 0;
        for (int i = cnt; i >= 1; i--)
        {
            int now = q[i]; 
            for (int j = 0; j < 26; j++) Sum[now] += Sum[a[now][j]];
            Sum[now] += val[now];
        }
    }
    void DFS(int x, int K)
    {
        if (K <= val[x]) return;
        K -= val[x];
        for (int i = 0; i < 26; i++)
            if (a[x][i])
            {
                int t = a[x][i];
                if (K <= Sum[t])
                {
                    printf ("%c", i + 'a');
                    DFS(t, K);
                    return;
                }
                K -= Sum[t];
            }
    }
}sam;

int main()
{
    scanf ("%s", s + 1);
    int T, K;
    scanf ("%d%d", &T, &K);
    sam.pre(T);
    if (K > sam.Sum[1]) printf ("-1\n");
    else sam.DFS(1, K);
}