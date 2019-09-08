#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
struct Point
{
	int x, y;
	void Cross(const Point &a, const Point &b) {
		x = a.x + b.x >> 1;
		y = a.y + b.y >> 1;
	}
	bool operator == (const Point &a) {
		return x == a.x && y == a.y;
	}
}a[1005], d[1005 * 1005];

int main() {
	int n = read();
	for (int i = 1; i <= n; i++) {
		a[i].x = read() * 2, a[i].y = read() * 2;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			d[++cnt].Cross(a[i], a[j]);
		}
	}
	sort(d + 1, d + cnt + 1, [&](const Point &a, const Point &b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	});
	int Max = 1, Num = 0;
	for (int i = 1; i <= cnt; i++) {
		if (d[i] == d[i - 1]) {
			Num++;
			Max = max(Max, Num);
		} else {
			Num = 1;
		}
	}
	printf ("%d\n", n - Max);
	// while (1);
}