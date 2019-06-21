#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
inline int read()
{
    int s = 0, k = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        k = ch == '-' ? -1 : k, ch = getchar();
    while (ch >= '0' && ch <= '9')
        s = s * 10 + (ch ^ 48), ch = getchar();
    return s * k;
}
int n;
bool Sum[4000005];
bool f[4000005];
bool a[4000005];
int main()
{
    n = read();
    int t = 0, op, l, r;
    int lastans = 0;
    while (n--)
    {
        op = read();
        if (op == 1)
        {
            l = read() ^ lastans;
            t++;
            a[t] = l;
            if (t == 1)
                f[t] = a[t];
            else
                f[t] = !(f[t - 1] & l);
            Sum[t] = Sum[t - 1] ^ f[t];
        }
        else
        {
            l = read(), r = read();
            if (lastans)
            {
                l = t - l + 1;
                r = t - r + 1;
                swap(l, r);
            }
            lastans = a[l];
            int i = l, now = !(a[l] & a[l + 1]);
            while (now != f[i + 1] && i < r)
            {
                lastans ^= now;
                i++;
                now = !(now & a[i + 1]);
            }
            if (i < r)
            {
                lastans ^= Sum[r] ^ Sum[i];
            }
            printf("%d\n", lastans);
        }
    }
    //while (1);
}
