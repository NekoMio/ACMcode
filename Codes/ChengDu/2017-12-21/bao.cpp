#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}
int main()
{
	// freopen("1.out", "w", stdout);
	int n;
	int ans = 0x3f3f3f3f, ansk = 0;
	int i, j;
	scanf ("%d%d", &i, &j);
	for (int k = 1; k <= 10000; k++)
	{
		int d = (i + k) * (j + k) / gcd(i + k, j + k);
		if (d < ans) ansk = k, ans = d;
	}
	printf ("%d\n", ansk);
}