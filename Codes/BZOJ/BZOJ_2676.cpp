#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Matrix
{
    double a[111][111];
    int n;
    Matrix(int x = 0)
    {
        memset (a, 0, sizeof (a));
        n = x;
    }
    void Init()
    {
        for (int i = 1; i <= n; i++)
            a[i][i] = 1;
    }
    double *operator[](const int x)
    {
        return a[x];
    }
    const double *operator[](const int x) const
    {
        return a[x];
    }
    Matrix operator * (const Matrix &b) const
    {
        Matrix ans;
        ans.n = n;
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (a[i][j] < 1e-15) continue;
                for (int k = 0; k <= n; k++)
                {
                    if (b[j][k] < 1e-15) continue;
                    ans[i][k] += a[i][j] * b[j][k];
                }
            }
        }
        return ans;
    }
    Matrix operator ^ (int b) const
    {
        Matrix ans, a = *this;
        ans.n = n;
        ans.Init();
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
    void print()
    {
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
                printf ("%.3lf ", a[i][j]);
            printf ("\n");
        }
        printf("\n");
    }
};
int n, r, q;
int id[6][22], cnt;
bool Judge(double mid, int s)
{
    Matrix A;
    A.n = r * q;
    A[cnt][cnt] = 1;
    for (int i = 1; i <= q; i++)
    {
        for (int j = 1; j <= r; j++)
        {
            A[cnt][id[i][j]] = mid * j;
            if (i < q && j < r)
                A[id[i + 1][j + 1]][id[i][j]] += mid;
            else if (i < q)
                A[id[i + 1][j]][id[i][j]] += mid;
            else if (j < r)
                A[id[i][j + 1]][id[i][j]] += mid;
            else
                A[id[i][j]][id[i][j]] += mid;
            if (i > 1) A[id[i - 1][1]][id[i][j]] += (1 - mid);
        }
    }
    // A.print();
    A = A ^ n;
    return A[cnt][id[q][1]] <= s;
}
int main()
{
    int s;
    scanf("%d%d%d", &n, &r, &q);
    scanf ("%d", &s);
    for (int i = 1; i <= q; i++)
        for (int j = 1; j <= r; j++)
            id[i][j] = cnt++;
    if (Judge(1, s))
        return printf("Impossible.\n"), 0;
    double l = 0, r = 1;
    while (l + 1e-8 < r)
    {
        double mid = (l + r) / 2;
        if (Judge(mid, s)) l = mid;
        else r = mid;
    }
    printf ("%.6lf", l);
}
