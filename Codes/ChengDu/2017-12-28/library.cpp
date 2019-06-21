#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

#define ULL unsigned long long

const int MAXN = 2005;
const ULL BASE = 31;

set<ULL> st;
char s[MAXN];
int t, n;
bool Hash(int x, ULL &H)
{
	ULL ZHash[25], FHash[25];
	ZHash[0] = FHash[0] = 0;
	int cnt = 0;
	for (int i = 0; i < n; i++)
		if (x & (1 << i))
		{
			cnt++;
			ZHash[cnt] = ZHash[cnt - 1] * BASE + s[i];
		}
	cnt = 0;
	for (int i = n - 1; i >= 0; i--)
		if (x & (1 << i))
		{
			cnt++;
			FHash[cnt] = FHash[cnt - 1] * BASE + s[i];
		}
	H = FHash[cnt];
	return FHash[cnt] == ZHash[cnt];
}

bool Judge(int x)
{
	ULL H = 0;
	if (!Hash(x, H)) return 0;
	t++;
	if (st.count(H)) return 0;
	st.insert(H);
	return 1;
}

int main()
{
	//freopen ("library.in", "r", stdin);
	//freopen ("library.out", "w", stdout);
	scanf ("%s", s);
	n = strlen(s);
	int N = (1 << n) - 1;
	int ans = 0;
	for (int i = 1; i <= N; i++)
		if (Judge(i)) ans++;
	printf ("%d\n", t - ans);
}
