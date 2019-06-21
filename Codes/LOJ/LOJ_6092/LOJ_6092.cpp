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
inline char readchar()
{
    char ch = getchar();
    while (ch<'a'||ch>'z') ch=getchar();
    return ch;
}
const int MAXN = 1505;
char s[MAXN];
int Sum[MAXN][26];
int ans[MAXN][26];
inline void gmax(int &a, int b) { if (a < b) a = b; }
int main()
{
    int n = read();
    scanf ("%s", s + 1);
    for (int i = 1; i <= n; i++)
        Sum[i][s[i] - 'a']++;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 26; j++)
            Sum[i][j] += Sum[i - 1][j];
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            for (int k = 0; k < 26; k++)
                gmax(ans[j - i + 1 - (Sum[j][k] - Sum[i - 1][k])][k], j - i + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 26; j++)
            gmax(ans[i][j], ans[i - 1][j]);
    int q = read();
    while (q--)
    {
        int m = read(), c = readchar();
        printf ("%d\n", ans[min(n, m)][c - 'a']);
    }
}