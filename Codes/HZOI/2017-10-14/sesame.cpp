#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
bool Judge(int a, int b)
{
	return !(a == 0 || b == 0);
}
void Change(int &a, int &b)
{
	if (a > b) a -= b, b *= 2;
	else b -= a, a *= 2;
}
int main()
{
    int n, m, k;
    scanf ("%d%d%d", &n, &m, &k);
    int T = k, a = n, b = m;
    while (T-- && Judge(a, b)) Change(a, b);
    printf ("%d", min(a, b));
}