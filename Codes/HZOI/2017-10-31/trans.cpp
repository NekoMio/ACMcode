#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[1000005];
int n, k;
void to_do(int pos, int op, int t)
{
    if (((k - t + op) & 1) == 1) s[pos] = '2', s[pos + 1] = '2', s[pos + 2] = '3';
    else s[pos] = '2', s[pos + 1] = '3', s[pos + 2] = '3';
}
int main()
{
    freopen ("trans.in", "r", stdin);
    freopen ("trans.out", "w", stdout);
    while (scanf("%d%d", &n, &k) != EOF)
    {
        scanf ("%s", s + 1);
        s[n + 1] = '\0';
        if (n <= 1000 && k <= 1000)
        {
            for (int t = 1; t <= k; t++)
            {
                int i;
                for (i = 1; i <= n; i++)
                {
                    if (s[i] == '2' && s[i + 1] == '3') 
                    {
                        if (i & 1) s[i + 1] = '2';
                        else s[i] = '3';
                        break;
                    }
                }
                if (i == n + 1) break;
            }
        }
        else
        {
            int t = 0;
            for (int i = 1; i <= n && t < k; i++)
            {
                if (s[i] == '2' && s[i + 1] == '3')
                {
                    if (i & 1)
                    {
                        if (s[i + 2] == '3') 
                        {
                            to_do(i, 0, t);
                            break;
                        }
                        else s[i + 1] = '2';
                        t++; 
                    }
                    else
                    {
                        if (s[i - 1] == '2')
                        {
                            to_do(i - 1, 1, t);
                            break;
                        }
                        else s[i] = '3';
                        t++;
                    }
                }
            }
        }
        printf ("%s\n", s + 1);
    }
    fclose(stdin), fclose(stdout);
    return 0;
}