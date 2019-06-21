#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAXN = 5e4 + 5;

struct data
{
    int h, v, id;
    bool operator < (const data &a) const{
        return id < a.id;
    }
}a[MAXN];
double LL[MAXN], RL[MAXN];
int LM[MAXN], RM[MAXN];
int Hash[MAXN];


double Sum[MAXN];
int Max[MAXN], Color[MAXN], C;
#define lowbit(_) ((_) & (-_))

void Update(int x, int M, double L)
{
    for (int i = x; i <= MAXN - 5; i += lowbit(i))
    {
        if (Color[i] != C) Sum[i] = 0, Max[i] = 0;
        Color[i] = C;
        if (Max[i] == M) Sum[i] += L;
        else if (Max[i] < M)
            Sum[i] = L, Max[i] = M;
    }
}

double Query_Max(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        if (Color[i] == C)
            ans = max(ans, Max[i]);
    return ans;
}

double Query_cnt(int x)
{
    int Max_tmp = 0;
    double ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
    {
        if (Color[i] == C)
        {
            if (Max_tmp < Max[i]) Max_tmp = Max[i], ans = Sum[i];
            else if (Max_tmp == Max[i]) ans += Sum[i]; 
        }
    }
    return ans;
}

int cmp(const data &a, const data &b)
{
    if (a.h == b.h) return a.v < b.v;
    return a.h > b.h;
}

int cmp1(const data &a, const data &b)
{
    return a.id > b.id;
}

int cmp2(const data &a, const data &b)
{
    if (a.h == b.h) return a.v < b.v;
    return a.h < b.h;
}

void CDQ(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    CDQ(l, mid); 
    sort(a + l, a + mid + 1, cmp);
    sort(a + mid + 1, a + r + 1, cmp);
    C++;
    for (int j = mid + 1, i = l; j <= r; j++)
    {
        for (; a[i].h >= a[j].h && i <= mid; i++)
            Update(a[i].v, LM[a[i].id], LL[a[i].id]);
        double M = Query_Max(a[j].v) + 1;
        if (LM[a[j].id] == M) LL[a[j].id] += Query_cnt(a[j].v);
        else if (LM[a[j].id] < M) LL[a[j].id] = Query_cnt(a[j].v), LM[a[j].id] = M;
    }
    sort(a + mid + 1, a + r + 1);
    CDQ(mid + 1, r);
}
int n;
void CDQ2(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    CDQ2(l, mid); 
    sort(a + l, a + mid + 1, cmp2);
    sort(a + mid + 1, a + r + 1, cmp2);
    C++;
    for (int j = mid + 1, i = l; j <= r; j++)
    {
        for (; a[i].h <= a[j].h && i <= mid; i++)
            Update(a[i].v, RM[n - a[i].id + 1], RL[n - a[i].id + 1]);
        double M = Query_Max(a[j].v) + 1;
        if (RM[n - a[j].id + 1] == M) RL[n - a[j].id + 1] += Query_cnt(a[j].v);
        else if (RM[n - a[j].id + 1] < M) RL[n - a[j].id + 1] = Query_cnt(a[j].v), RM[n - a[j].id + 1] = M;
    }
    sort(a + mid + 1, a + r + 1);
    CDQ2(mid + 1, r);
}

double ans[MAXN];

int main()
{
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &a[i].h, &a[i].v), a[i].id = i, Hash[i] = a[i].v;
    sort(Hash + 1, Hash + n + 1);
    int cnt = unique(Hash + 1, Hash + n + 1) - Hash - 1;
    for (int i = 1; i <= n; i++) a[i].v = cnt - (lower_bound(Hash + 1, Hash + cnt + 1, a[i].v) - Hash) + 1;
    for (int i = 1; i <= n; i++) LM[i] = RM[i] = LL[i] = RL[i] = 1;
    CDQ(1, n);
    for (int i = 1; i <= n; i++) a[i].v = cnt - a[i].v + 1, a[i].id = n - a[i].id + 1;
    sort(a + 1, a + n + 1);
    int MaxAns = 0;
    double AllCnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (MaxAns == LM[i])
            AllCnt += LL[i];
        if (MaxAns < LM[i])
            AllCnt = LL[i], MaxAns = LM[i];
    }
    CDQ2(1, n);
    printf ("%d\n", MaxAns);
    for (int i = 1; i <= n; i++)
        if (LM[i] + RM[i] - 1 == MaxAns)
            printf ("%f ", (double)LL[i] * RL[i] / AllCnt);
        else printf ("0.0 ");
    // printf ("\n");
    // while (1);
}