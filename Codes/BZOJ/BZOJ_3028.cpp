#include <cstdio>
int MOD = 10007;
inline int read()
{
    int x=0;char ch=getchar();
    while (ch<'0'||ch>'9'){ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x*10+ch-'0')%MOD;ch=getchar();}
    return x;
}
int main()
{
    int n = read();
    printf ("%d\n", n * (n + 1) % MOD * (n + 2) % MOD * 1668 % MOD);
}