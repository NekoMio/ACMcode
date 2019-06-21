#include <bits/stdc++.h>
using namespace std;
int main()
{
    string name = "move";
    string run = "/home/wildrage/OIcode/moveX/std";
    for (int T = 1; T <= 20; T++)
    {
        FILE *f = fopen((name + to_string(T) + ".in").c_str(), "w");
        int a[55][55];
        memset (a, 0, sizeof (a));
        int n;
        scanf ("%d", &n);
        fprintf(f, "%d\n", n);
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int x = rand() % 6 == 0;
                fprintf (f, "%d", x);
                cnt += x;
            }
            fprintf(f, "\n");
        }
        while (cnt)
        {
            int x = rand() % n + 1, y = rand() % n + 1;
            while (a[x][y]) x = rand() % n + 1, y = rand() % n + 1;
            a[x][y] = 1;
            cnt--;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                fprintf(f, "%d", a[i][j]);
            fprintf(f, "\n");
        }
        system((run + " <" + name + to_string(T) + ".in" + " >" + name + to_string(T) + ".ans").c_str());
    }
}