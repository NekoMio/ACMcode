#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
int buc[MAXN], wa[MAXN], wb[MAXN];
int r[MAXN], height[MAXN], Rank[MAXN], sa[MAXN];
void GetHeight(int n)
{
    int i, j, k = 0;
    for (i = 0; i < n; i++) Rank[sa[i]] = i;
    for (i = 0; i < n; height[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; r[i + k] == r[j + k]; k++);
    return;
}
bool cmp(int *c, int a, int b, int d)
{
    return c[a] == c[b] && c[a + d] == c[b + d];
}
void da(int n, int m = 130)
{
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++) buc[i] = 0;
    for (i = 0; i < n; i++) buc[x[i] = r[i]]++;
    for (i = 1; i < m; i++) buc[i] += buc[i - 1];
    for (i = n - 1; ~i; i--) sa[--buc[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p)
    {
        for (i = n - j, p = 0; i < n; i++)
            y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                y[p++] = sa[i] - j;
        for (i = 0; i < m; i++) buc[i] = 0;
        for (i = 0; i < n; i++) buc[x[y[i]]]++;
        for (i = 1; i < m; i++) buc[i] += buc[i - 1];
        for (i = n - 1; ~i; i--) sa[--buc[x[y[i]]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
    GetHeight(n);
}
int n;
struct Chairman_Tree
{
    struct Node
    {
        int sum;
        Node *ch[2];
        Node()
        {
            sum = 0;
            ch[0] = ch[1] = NULL;
        }
        #define Sum(_) ((_) ? (_)->sum : 0)
        void PushUp()
        {
            sum = Sum(ch[0]) + Sum(ch[1]);
        }
    } * root[100005], *null;
    Chairman_Tree()
    {
        null = new Node();
        null->ch[0] = null->ch[1] = null;
        root[0] = null;
    }
    Node *NewNode()
    {
        Node *S = new Node();
        S->ch[0] = S->ch[1] = null;
        return S;
    }
    void copy(Node *&a, Node *b)
    {
        if(b == null)
            a = null;
        else
            a = NewNode(), *a = *b;
    }
    void Update(Node *&rt1, Node *rt2, int l, int r, int c)
    {
        copy(rt1, rt2);
        if(rt1 == null)
            rt1 = NewNode();
        if(l == r)
        {
            rt1->sum++;
            return;
        }
        int m = l + r >> 1;
        if(c <= m) Update(rt1->ch[0], rt2->ch[0], l, m ,c);
        else Update(rt1->ch[1], rt2->ch[1], m + 1, r, c);
        rt1->PushUp();
    }
    int Query(Node *rt1, Node *rt2, int L, int R, int l, int r)
    {
        if(L <= l && R >= r)
            return rt1->sum - rt2->sum;
        int m = l + r >> 1;
        int ans = 0;
        if (L <= m)
            ans += Query(rt1->ch[0], rt2->ch[0], L, R, l, m);
        if (R > m)
            ans += Query(rt1->ch[1], rt2->ch[1], L, R, m + 1, r);
        return ans;
    }
    void Update(int i, int c)
    {
        Update(root[i], root[i - 1], 1, n, c);
    }
    int Query(int a, int b, int L, int R)
    {
        return Query(root[b], root[a - 1], L, R, 1, n);
    }
}root;
int Min[MAXN][17];
void InitST()
{
    for (int i = 1; i <= n; i++) Min[i][0] = height[i];
    for (int j = 1; j < 17; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
}
bool Judge(int mid, int a, int b, int c, int d)
{
    int l = Rank[c - 1], r = Rank[c - 1];
    for (int i = 16; i >= 0; i--) if(l >= (1 << i) && Min[l - (1 << i) + 1][i] >= mid) l -= (1 << i);
    for (int i = 16; i >= 0; i--) if(r + (1 << i) <= n && Min[r + 1][i] >= mid) r += (1 << i);
    return root.Query(a, b - mid + 1, l, r) > 0;
}
char s[MAXN];
int main()
{
    int m;
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    for (int i = 0; i < n; i++)
        r[i] = s[i];
    da(n + 1);
    for (int i = 0; i < n; i++)
        root.Update(i + 1, Rank[i]);
    InitST();
    int a, b, c, d;
    while (m--)
    {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int l = 0, r = min(b - a + 1, d - c + 1) + 1, ans = 0;
        while (l < r)
        {
            int mid = l + r >> 1;
            if(Judge(mid, a, b, c, d))
                ans = mid, l = mid + 1;
            else
                r = mid;
        }
        printf("%d\n", ans);
    }
}