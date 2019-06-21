#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    cout << n << endl;
    for (int i = 1; i <= n; i++)
        cout << rand() % 20 << " ";
    cout << m << endl;
    for (int i = 1; i <= m; i++)
    {
        int r1 = rand() % n + 1, r2 = rand() % n + 1;
        int c1 = rand() % (r1 + 1), c2 = rand() % (r2 + 1);
        cout << r1 << " " << c2 << " " << r2 << " " << c2 << endl;
    }
}