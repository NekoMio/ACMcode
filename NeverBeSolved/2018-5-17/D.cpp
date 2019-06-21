#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
map<unsigned int, int> H;
unsigned int base = 31;
char s[8][25];
unsigned int Hash(int x, int y)
{
	unsigned int ans = 0;
	for (int i = 1; i <= 7; i++)
		for (int j = 1; j <= 4; j++)
			ans = ans * base + s[i + x - 1][j + y - 1];
	return ans;
}
int main()
{
	H[1607820544u] = 0, H[66798888u] = 1, H[2111781440u] = 2, H[2236796264u] = 3, H[690775060u] = 4, H[2435495488u] = 5, H[3745592428u] = 6, H[3102713832u] = 7, H[741861312u] = 8, H[3726731668u] = 9;
	int T;scanf ("%d", &T);
	while (T--)
	{
		for (int i = 0; i < 7; i++)
			scanf ("%s", s[i]);
		printf ("%d%d:%d%d\n", H[Hash(0, 0)], H[Hash(0, 5)], H[Hash(0, 12)], H[Hash(0, 17)]);
	}
}