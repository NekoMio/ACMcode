#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
char S1[2005], S2[2005];
void Change(int len, char *s)
{
	if (s[len] == 'B')
		for (int i = 1; i <= (len - 1 >> 1); i++)
			swap(s[i], s[len - i]);
}
bool Judge(int len)
{
	for (int i = 1; i <= len; i++)
		if (S1[i] != S2[i])
			return 0;
	return 1;
}
int main()
{
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
	int t;
	scanf ("%d", &t);
	while (t--)
	{
		scanf ("%s%s", S1 + 1, S2 + 1);
		int len1 = strlen(S1 + 1), len2 = strlen(S2 + 1);
		while (len1 < len2) Change(len2--, S2);
		while (len1)
		{
			if (Judge(len1)) break;
			Change(len1--, S1);
			Change(len2--, S2);
		}
		if (len1 == 0) printf ("-1\n");
		else
		{
			for (int i = 1; i <= len1; i++)
				printf ("%c", S1[i]);
			printf ("\n");
		}
	}
}
