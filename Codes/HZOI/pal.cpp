#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std; 
#define ULL unsigned long long
ULL Hash1[5005],Hash2[5005];
ULL base = 31;
char s[5005];
ULL B[5005];
bool OK(int l, int r)
{
	return Hash1[r] - Hash1[l] * B[r - l] == Hash2[l] - Hash2[r] * B[r - l];
}
int ans[5005][5005];
int main()
{
	scanf("%s",s);
	int n = strlen(s);
	B[0] = 1;
	for (int i = 1; i <= n; i++)
		B[i] = B[i - 1] * base;
	for (int i = 0; i <= n; i++)
		Hash1[i] = Hash1[i - 1] * base + s[i];
	for (int i = n ; i >= 0; i--)
		Hash2[i] = Hash2[i + 1] * base + s[i];
	for (int l = 0; l < n; l++)
		for (int i = 0; i < n - l + 1; i++)
			ans[i][i + l - 1] = ans[i + 1][i + l - 1] + ans[i][i + l - 2] - ans[i + 1][i + l - 2] + OK(i, i + l - 1);
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		printf("%d\n", ans[l][r]);
	}
}