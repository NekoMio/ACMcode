#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char S[400005];
int nxt[400005];
char c[5];
int la, lb;
void Get_fail(int len)
{
    int j = 0, k = -1;
    nxt[0] = -1;
    while (j < len)
        if (k == -1 || S[j] == S[k])
            j++, k++, nxt[j] = k;
        else
            k = nxt[k];
}
int main()
{
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        memset (nxt, 0, sizeof(nxt));
        scanf ("%d%d", &la, &lb);
        scanf ("%s", S);
        S[la] = '&';
        for (int i = 1; i <= lb; i++)
            S[la + i] = S[i - 1];
        int len = la + lb + 2;
        scanf ("%s", c);
        S[len - 1] = c[0];
        Get_fail(len);
        if (nxt[len] == -1)
            printf ("0\n");
        else
            printf ("%d\n", nxt[len]);
    }
    // while (1);
}