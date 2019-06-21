#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
	freopen ("2017math.in", "r", stdin);
	freopen ("2017math.out", "w", stdout);
	long long n, m;
	scanf ("%lld%lld", &n, &m);
	if (n < m) swap(n, m);
	printf ("%lld\n", n * (m - 1) - m);
	//fclose(stdin), fclose(stdout);
	return 0;
}
