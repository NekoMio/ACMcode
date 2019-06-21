#include <bits/stdc++.h>
using namespace std;
struct data
{
    int a, b, c;
    data(int _a = 0, int _b = 0, int _c = 0): a(_a), b(_b), c(_c){}
};
vector<data> vc;
int lst[1005];
void pop()
{
    vc.pop_back();
}
void add(int a, int b, int c)
{
    // fprintf (stderr, "%d %d %d\n", a, b, c);
    vc.push_back(data(a, b, c));
}
int n, k, p;
void Push()
{
    FILE *f = fopen("nm9.out", "w");
    fprintf (f, "%d %d %d\n", n, vc.size(), k);
    for (auto x : vc)
        fprintf (f, "%d %d %d\n", x.a, x.b, x.c);
    fclose(f);
}
int main()
{
    // freopen ("workspace/problem_56/nm7.in", "r", stdin);
    scanf ("%d %d %d\n", &n, &k, &p);
    for (int i = 1; i <= n; i++)
    {
        cin >> lst[i];
        for (int j = lst[i]; j <= n; j++)
            add(i, j, 1);
        for (int j = 1; j < i; j++)
            if (lst[j] < lst[i])
                add(i, lst[j], 1);
    }
    Push();
}