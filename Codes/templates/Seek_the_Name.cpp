#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[400005];
int Next[400005];
int main()
{
	while (scanf("%s", s) != EOF)
	{
		int m = strlen(s);
		int j = 0, k = -1;
		Next[0] = -1;
		while(j < m)
			if (k == -1 || s[j] == s[k])
				Next[++j] = ++k;
			else
				k = Next[k];
		static int ans[400005];
		k = m;
		int p = 0;
		while(k > 0)
		{
			ans[++p] = k;
			k = Next[k];
		}
		for (int i = p; i >= 1; i--)
			printf("%d ", ans[i]);
		printf("\n");
	}
}