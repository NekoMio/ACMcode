#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int MOD;
struct Matrix
{
    int a[25][25], n;
    Matrix()
    {
        memset (a, 0, sizeof (a));
        n = 0;
    }
    int *operator[](int x)
    {
        return a[x];
    }
    const int *operator[](const int x) const
    {
        return a[x];
    }
    Matrix operator * (const Matrix b)
    {
        Matrix ans;
        ans.n = n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    ans[i][j] = (ans[i][j] + a[i][k] * b[k][j] % MOD) % MOD;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans, a = *this;
        ans.n = n;
        for (int i = 0; i < n; i++) ans[i][i] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}trans;
char s[25];
int fail[25];
void Init(int m)
{
    int j = 0;
    for (int i = 2; i <= m; i++)
    {
        while (j > 0 && s[j + 1] != s[i]) j = fail[j];
        if (s[j + 1] == s[i]) j++;
        fail[i] = j;
    }
    for (int i = 0; i < m; i++)
    {
        for (j = 0; j <= 9; j++)
        {
            int p = i;
            while (p > 0 && s[p + 1] - '0' != j) p = fail[p];
            if (s[p + 1] - '0' == j) p++;
            if (p != m) trans[p][i] = (trans[p][i] + 1) % MOD;
        }
    }
}
int main()
{
    int n = read(), m = read();
    MOD = read();
    scanf ("%s", s + 1);
    trans.n = m;
    Init(m);
    trans = trans ^ n; 
    int ans = 0;
    for (int i = 0; i < m; i++)
        ans = (ans + trans[i][0]) % MOD;
    printf ("%d\n", ans);
    // while (1);
}