#include <bits/stdc++.h>
using namespace std;
int main()
{
    srand(time(NULL));
    int n;
    scanf ("%d", &n);
    printf ("%d\n", n);
    for (int i = 1; i <= n; i++)
    {
        int x = rand() % 10 + 1, y = rand() % 10 + 1;
        if (x > y) swap(x, y);
        printf ("%d %d\n", x, y);
    }
    while (1);
}