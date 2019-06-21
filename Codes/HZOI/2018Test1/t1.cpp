#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAXN = 30005;
const int MOD = 10007;
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int mp[MAXN];
int K[MAXN], p[MAXN], B[MAXN];
int st[MAXN], top, vis[MAXN];
int pow_mod(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int Query(int a);
int DFS(int rt)
{
    if (vis[rt]) 
    {
        int k = K[st[top - 1]], b = B[st[top - 1]];
        for (int i = top - 2; i >= vis[rt]; i--)
            k = k * K[st[i]] % MOD, b = (K[st[i]] * b % MOD + B[st[i]]) % MOD;
        if (k == 1 && b != 0) return -3;
        else if (k == 1 && b == 0) return -2;
        else return b * pow_mod((1 - k + MOD) % MOD, MOD - 2) % MOD;
    }
    vis[rt] = top;
    int t = Query(p[rt]);
    if (t == -2) return -2;
    else if (t == -3) return -3;
    return (K[rt] * t % MOD + B[rt]) % MOD;
}

int Query(int a)
{
    if (mp[a] != -1) return mp[a];
    else 
    {
        st[++top] = a;
        mp[a] = DFS(a);
        vis[a] = 0;
        top--;
        return mp[a];
    }
}
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        K[i] = read(), p[i] = read(), B[i] = read();
    int Q = read();
    char s[10];
    memset (mp, -1, sizeof (mp));
    for (int i = 1; i <= Q; i++)
    {
        scanf ("%s", s);
        if (s[0] == 'A')
        {
            printf ("%d\n", Query(read()));
        }
        else
        {
            memset (mp, -1, sizeof (mp));
            int a = read();
            K[a] = read(), p[a] = read(), B[a] = read();
        }
    }
}