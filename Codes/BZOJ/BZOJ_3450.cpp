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
const int MAXN = 300005;
double l[MAXN];
char s[MAXN];
int main()
{
    int n = read();
    scanf ("%s", s + 1);
    double ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 'o') ans += 2 * l[i - 1] + 1, l[i] = l[i - 1] + 1;
        else if (s[i] == 'x') l[i] = 0;
        else ans += (2 * l[i - 1] + 1) / 2, l[i] = (l[i - 1] + 1) / 2;
    }
    printf ("%.4f\n", ans);
    // while (1);
}