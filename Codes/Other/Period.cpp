#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[1000005];
int Next[1000005];
int Get_next(int m)
{
	int j = 0, k = -1;
	Next[0] = -1;
	while (j < m)
		if(k == -1 || s[j] == s[k])
			j++, k++, Next[j] = k;
		else
			k = Next[k];
}
int main()
{
	int n;
	int T = 0;
	while(scanf("%d", &n) != EOF && n != 0)
	{
		T++;
		scanf("%s", s);
		Get_next(n);
		printf("Test case #%d\n", T);
		for (int i = 1; i <= n; i++)
			if(i % (i - Next[i]) == 0 && Next[i] > 0)
				printf("%d %d\n", i, i / (i - Next[i]));
		printf("\n");
	}
}