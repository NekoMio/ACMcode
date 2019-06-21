#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
char s[101];
int st[500], top;
char cst[500];
int D[500], C[500];
set<char> mp;
int get_num(int pos)
{
	int ans = 0;
	while (s[pos]>='0'&&s[pos]<='9')
	{
		ans = ans * 10 + s[pos] - '0';
		pos++;
	}
	return ans;
}
int main()
{
	freopen("2017complexity.in", "r", stdin);
	freopen("2017complexity.out", "w", stdout);
	int T;
	scanf ("%d", &T);
	while (T--)
	{
		memset(st, 0, sizeof (st));
		memset(D, 0, sizeof (D));
		memset(cst, 0, sizeof (cst));
		memset(C, 0, sizeof (C));
		mp.clear();
		top = 0;
		int L = 0, cmp = 0;
		bool flag = 0;
		scanf ("%d O(%s)", &L, s);
		if (s[0] == 'n')
			cmp = get_num(2);
		for (int i = 1; i <= L; i++)
		{
			scanf ("%s", s);
			if (s[0] == 'F')
			{
				scanf ("%s", s);
				if (mp.count(s[0])) flag = 1;
				else mp.insert(s[0]);
				cst[++top] = s[0];
				scanf ("%s", s);
				if (s[0] == 'n') 
				{
					st[top] = 0;
					scanf ("%s", s);
					if (s[0] != 'n') C[top] = 1;
				}
				else
				{
					int a = get_num(0);
					scanf ("%s", s);
					if (s[0] != 'n')
					{
						int b = get_num(0);
						if (a > b) st[top] = 0, C[top] = 1;
						else st[top] = 0;
					}
					else st[top] = 1;
				}
				D[top + 1] = 0, C[top + 1] = 0;
			}
			else
			{
				if (top == 0) flag = 1;
				else
				{
					if (C[top]) D[top] = max(D[top], 0);
					else D[top] = max(D[top], D[top + 1] + st[top]);
					mp.erase(cst[top]);
					top--;
				}
			}
		}
		if (flag || top) printf ("ERR\n");
		else if (D[1] == cmp) printf ("Yes\n");
		else printf ("No\n");
	}
	//fclose(stdin), fclose(stdout);
	return 0;
}
