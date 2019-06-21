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
int t[20], w[20];
int Sum[65537], T[65537];
int F[65537];
int main()
{
    int W = read(), n = read();
    for (int i = 1; i <= n; i++)
        t[i] = read(), w[i] = read();
    int N = (1 << n) - 1;
    for (int i = 1; i <= N; i++)
    {
        int j = 0;
        for (j = 1; j <= n; j++)
            if (i & (1 << (j - 1)))
                break;
        Sum[i] = Sum[i ^ (1 << (j - 1))] + w[j];
        T[i] = max(T[i ^ (1 << (j - 1))], t[j]);
    }
    memset (F, 0x3f, sizeof (F));
    F[0] = 0;
    for (int i = 1; i <= N; i++)
        for (int j = i; j ; j = (j - 1) & i)
            if (Sum[j] <= W)
                F[i] = min(F[i], F[j ^ i] + T[j]);
    printf ("%d\n", F[N]);
}