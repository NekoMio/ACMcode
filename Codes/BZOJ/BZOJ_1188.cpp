#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 22;
int n;
int SG[N];
int sg(int x)
{
    static bool f[N * N * 1];
    memset (f, 0, sizeof (f));
    for (int i = x + 1; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if ((SG[i] ^ SG[j]) <= N * N) f[SG[i] ^ SG[j]] = 1;
        }
    }
    for (int i = 0; i <= N * N; i++)
        if (!f[i]) return i;
}
int a[N];
int main()
{
    int t = read();
    while (t--)
    {
        int ans = 0, cnt = 0;
        n = read();
        SG[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--) SG[i] = sg(i);
        for (int i = 0; i < n; i++)
            ans ^= (((a[i] = read()) & 1) ? SG[i] : 0);
        for (int i = 0; i < n; i++) if (a[i])
            for (int j = i + 1; j < n; j++)
                for (int k = j; k < n; k++)
                    if (((ans ^ SG[i] ^ SG[j] ^ SG[k]) == 0) && ++cnt == 1)
                        printf ("%d %d %d\n", i, j, k);
        if (!cnt) printf ("-1 -1 -1\n0\n");
        else printf ("%d\n", cnt);
    }
    // while (1);
}
