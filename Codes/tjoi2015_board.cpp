#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
int P, K, N;
int a[4][7];
unsigned int f[2][(1 << 6) + 1];
bool ok[65][65];
bool Ok[65];
struct Matrix
{
    int n, m;
    unsigned int a[65][65];
    Matrix(int x, int y)
    {
        n = x, m = y;
        memset(a, 0, sizeof(a));
    }
    void Init()
    {
        for (int i = 0; i <= n; i++)
            a[i][i] = 1;
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ans(n, b.m);
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                for (int k = 0; k <= b.m; k++)
                    ans.a[i][j] = ans.a[i][j] + a[i][k] * b.a[k][j];
        return ans;
    }
    Matrix operator^(const long long &b) const
    {
        Matrix ans(n, m);
        ans.Init();
        Matrix c = *this;
        long long k = b;
        while (k)
        {
            if (k & 1)
                ans = c * ans;
            k >>= 1;
            c = c * c;
        }
        return ans;
    }
    void print()
    {
        printf("\n{n,m} = {%d,%d}\n", n, m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                printf("%lld ", a[i][j]);
            printf("\n");
        }
        printf("\n");
    }
};
bool OK(int x)
{
	for (int i = 1; i < K; i++)
		if(a[2][i])
			if((x << (K - i)) & x & N)
				return 0;
	for (int i = K + 1; i <= P; i++)
		if(a[2][i])
			if((x >> (i - K)) & x & N)
				return 0;
	return 1;
}
bool OK(int x, int y)
{
	for (int i = 1; i < K; i++)
		if (a[1][i])
			if ((x << (K - i)) & y & N)
				return 0;
	for (int i = K; i <= P; i++)
		if (a[1][i])
			if ((x >> (i - K)) & y & N)
				return 0;
	for (int i = 1; i < K; i++)
		if (a[3][i])
			if ((y << (K - i)) & x & N)
				return 0;
	for (int i = K; i <= P; i++)
		if (a[3][i])
			if ((y >> (i - K)) & x & N)
				return 0;
	return 1;
}
int main()
{
	freopen("tjoi2015_board.in","r",stdin);
	freopen("tjoi2015_board.out","w",stdout);
	int n, m;
	scanf("%d%d%d%d", &n, &m, &P, &K);
	K++;
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= P; j++)
			scanf("%d", &a[i][j]);
	N = (1 << m) - 1;
	int now = 1;
	char S[10];
	Matrix A(N, N);
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
			A.a[i][j] = (OK(i, j) && OK(i) && OK(j));
	Matrix B(0, N);
	for (int i = 0; i <= N; i++)
			B.a[0][i] = OK(i);
	A = A ^ (n - 1);
	B = B * A;
	unsigned int ans = 0;
	for (int i = 0; i <= N; i++)
		ans += B.a[0][i];
	printf("%u", ans);
}