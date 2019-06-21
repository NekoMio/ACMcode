#include <bits/stdc++.h>
using namespace std;
char s[10005];
double f[10005];
int cnt[25];
int main() {
	scanf ("%s", s + 1);
	int n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) {
		cnt[s[i] - 'A'] ++;
	}
	f[0] = 0;
	f[1] = (n - 1.0) * (n - 1) / n;
	for (int i = 1; i <= n; ++i) {
		f[i + 1] = 2 * f[i] - f[i - 1] - (n - 1.0) / (n - i);
	}
	double ans = 0;
	for (int i = 0; i <= 25; ++i) {
		ans = ans + f[cnt[i]];
	}
	printf ("%.1f\n", ans);
}