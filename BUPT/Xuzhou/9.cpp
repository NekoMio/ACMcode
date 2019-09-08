#include <bits/stdc++.h>
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
const int MAXN = 1e5 + 5;
int in[MAXN], a[MAXN], block = 300, ans[MAXN], Ans;
bool flag[MAXN];
struct data {
  int l, r, id;
  bool operator < (const data &b) const {
		return in[l] == in[b.l] ? r > b.r : l < b.l;
	}
}Q[MAXN];
vector<int> vc[MAXN];
void Upd(int x, int val) {
  flag[x] = val > 0;
  for (auto v : vc[x])
    if (flag[v]) Ans += val;
}
int main() {
  int n = read(), m = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
    in[i] = i / block + 1;
    if (a[i] != 1) {
      for (int j = 1; j * j <= a[i]; j++) {
        if (a[i] % j == 0) {
          vc[a[i]].push_back(j);
          if (j * j != a[i] && j != 1)
            vc[a[i]].push_back(a[i] / j);
        }
      }
    }
    for (int j = 2; j * a[i] <= n; j++) {
      vc[a[i]].push_back(j * a[i]);
    }
  }
  for (int i = 1; i <= m; i++)
    Q[i].l = read(), Q[i].r = read(), Q[i].id = i;
  sort(Q + 1, Q + m + 1);
  Ans = 0;
  for (int i = 1; i <= n; i++)
    Upd(a[i], 1);
  int l = 1, r = n;
  for (int i = 1; i <= m; i++) {
    while(l < Q[i].l) {Upd(a[l], -1); l++;}
		while(l > Q[i].l) {l--; Upd(a[l], 1);}
		while(r > Q[i].r) {Upd(a[r], -1); r--;}
		while(r < Q[i].r) {r++; Upd(a[r], 1);}
    ans[Q[i].id] = Ans;
  }
  for (int i = 1; i <= m; i++) {
    printf ("%d\n", ans[i]);
  }
  // while (1);
}