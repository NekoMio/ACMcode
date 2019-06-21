#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[1000005], p[1000005];
int Next[1000005];
void Get_next(int m)
{
	int j = 0, k = -1;
	Next[0] = -1;
	while (j < m)
		if(k == -1 || p[j] == p[k])
			Next[++j] = ++k;
		else
			k = Next[k];
}
int Kmp(int n, int m)
{
	int i = 0, j = 0, ans = 0;
	while(i < n)
	{
		if(j == -1 || s[i] == p[j])
			j++, i++;
		else
			j = Next[j];
		if(j == m)
			ans++, j = Next[j];
	}
	return ans;
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%s", p);
		scanf("%s", s);
		int m = strlen(p), n = strlen(s);
		Get_next(m);
		int ans = Kmp(n, m);
		printf("%d\n", ans);
	}
}