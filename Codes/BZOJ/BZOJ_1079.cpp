#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define ULL unsigned long long
int n, k;
const int MOD = 1e9 + 7;
int c[20];
int temp[20];
map<ULL, long long> mp; 
const int base = 9091;
long long DFS(int Dep, int last)
{
	if (Dep == n)
		return 1;
	int h = 0;
	for (int i = 1; i <= k; i++)
		if (i != last)
			temp[++h] = c[i];
	sort(temp + 1, temp + h + 1);
	temp[++h] = c[last];
	ULL Hash = 0;
	for (int i = 1; i <= h; i++) Hash = Hash * base + temp[i];
	if (mp.count(Hash))
		return mp[Hash];
	long long ans = 0;
	for (int i = 1; i <= k; i++)
	{
		if (i != last && c[i])
		{
			c[i]--;
			(ans += DFS(Dep + 1, i)) %= MOD;
			c[i]++;
		}
	}
	mp[Hash] = ans;
	return ans;
}
int main()
{
	scanf ("%d", &k);
	for (int i = 1; i <= k; i++)
		scanf ("%d", &c[i]), n += c[i];
	printf("%lld", DFS(0, 0));
	// while (1);
}
