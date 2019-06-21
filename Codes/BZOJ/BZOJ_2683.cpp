#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
// #define int long long
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct data
{
    int x, y, t, id;
    int type, v;
    bool operator < (const data &a) const
    {
        if (id == a.id && x == a.x) return y < a.y;
        if (id == a.id) return x < a.x;
        return id < a.id;
    }
}a[200005 << 2];
int cnt, id;
int ans[200005];

int cmp(const data &a, const data &b)
{
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
#define lowbit(_) ((_)&(-_))
int Sum[500005], Color[500005], C;
void Update(int x, int c)
{
    for (int i = x; i <= 500000; i += lowbit(i))
    {
        if (Color[i] != C) Sum[i] = 0;
        Color[i] = C;
        Sum[i] += c;
    }
}

int Query(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
    {
        if (Color[i] == C) 
            ans += Sum[i];
    }
    return ans;
}

void CDQ(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    CDQ(l, mid), CDQ(mid + 1, r);
    sort(a + l, a + mid + 1, cmp);
    sort(a + mid + 1, a + r + 1, cmp);
    C++;
    for (int j = mid + 1, i = l; j <= r; j++)
    {
        if (a[j].type)
        {
            for (; a[i].x <= a[j].x && i <= mid; i++) 
            {
                if (a[i].type == 0)
                    Update(a[i].y, a[i].v);
            }
            ans[a[j].t] += Query(a[j].y) * a[j].v;
        }
    }
}

signed main()
{
    int n = read();
    int x_1, y_1, x_2, y_2, c;
    for (int i = 1; i; i++)
    {
        int op = read();
        if (op == 3) break;
        else if (op == 1)
        {
            a[++cnt].x = read(), a[cnt].y = read(), a[cnt].v = read();
        }
        else
        {
            x_1 = read(), y_1 = read(), x_2 = read(), y_2 = read();
            id++;
            a[++cnt].x = x_1 - 1, a[cnt].t = id, a[cnt].y = y_1 - 1, a[cnt].v = 1, a[cnt].type = 1;
            a[++cnt].x = x_1 - 1, a[cnt].t = id, a[cnt].y = y_2, a[cnt].v = -1, a[cnt].type = 1;
            a[++cnt].x = x_2, a[cnt].t = id, a[cnt].y = y_1 - 1, a[cnt].v = -1, a[cnt].type = 1;
            a[++cnt].x = x_2, a[cnt].t = id, a[cnt].y = y_2, a[cnt].v = 1, a[cnt].type = 1;
        }
    }
    for (int i = 1; i <= cnt; i++) a[i].id = i;
    sort(a + 1, a + cnt + 1);
    CDQ(1, cnt);
    for (int i = 1; i <= id; i++)
        printf ("%d\n", ans[i]);
}
