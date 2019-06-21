#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
long long ans;
vector<pair<int,int> > v[2];
void add(int x,int y)
{
	v[0].push_back(pair<int,int>(x - y, x));
	v[1].push_back(pair<int,int>(x + y, x));
}
bool mark;
void move(int &x, int &y, int &dx, int &dy)
{
	int op = (dx != dy);
	pair<int, int> now = pair<int, int>((op ? x + y : x - y), x);
	vector<pair<int, int> >::iterator it = upper_bound(v[op].begin(), v[op].end(), now);
	while (it->first != now.first)
		it--;
	if (dx < 0)
		while (it->second >= x)
			it--;
	ans += abs(x - (it->second)) - 1;
	x = it->second;
	y = op ? (it->first - x):(x - it->first);
	bool flagA = binary_search(v[0].begin(),v[0].end(),pair<int,int>(x - y - dx, x - dx));
	bool flagB = binary_search(v[0].begin(),v[0].end(),pair<int,int>(x - y + dy, x));
	if(flagA == flagB)
	{
		mark = 1;
		dx = -dx;
		dy = -dy;
	}
	else
 	{
 		if(flagA)
 			x -= dx, dy = -dy;
 		else if(flagB)
 			y -= dy, dx = -dx;
	}
}
int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++)
		add(0, i), add(n + 1, i);
	for (int i = 0; i <= n + 1; ++i)
		add(i, 0), add(i, m + 1);
	int a, b;
	for (int i = 0; i < k; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
	}
	int x, y, dx, dy;
	scanf("%d%d", &x, &y);
	char s[5];
	scanf("%s",s);
	dx = (s[0] == 'N' ? -1 : 1);
	dy = (s[1] == 'W' ? -1 : 1);
	sort(v[0].begin(), v[0].end());
	sort(v[1].begin(), v[1].end());
	move(x, y, dx, dy);
	int sx = x, sy = y, sdx = dx, sdy = dy;
	ans = 0;
	while (1)
	{
		move(x, y, dx, dy);
		if(x == sx && y == sy && sdx == dx && sdy == dy)
			break;
	}
	printf("%lld\n", mark?(ans>>1):ans);
}