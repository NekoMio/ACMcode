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
int vc[1005], cnt;
bool flag[1005];
void add1(int x) {
  vc[++cnt] = x;
}
void Del1(int x) {
  for (int i = 1; i <= cnt; ++i) {
    if (vc[i] == x) flag[i] = 1;
  }
}
void Update1(int x) {
  for (int i = 1; i <= cnt; ++i) {
    if (!flag[i]) vc[i] += x;
  }
}
int Query1(int x) {
  int ans = 0;
  for (int i = 1; i <= cnt; ++i) {
    if (!flag[i]) {
      if (vc[i] & (1 << x)) ans++;
    }
  }
  return ans;
}
const int MAXN = 5e5 + 5;
struct Hash_Table {
  struct edge {
    int x, ans, next;
  } v[MAXN];
  int first[76545], p;
  Hash_Table() {
    memset (first, -1, sizeof (first));
    p = 0;
  }
  int &operator [] (const int x) {
    int H = (x % 76543 + 76543) % 76543;
    for (int i = first[H]; i != -1; i = v[i].next)
      if (v[i].x == x)
        return v[i].ans;
    v[p].x = x;
    v[p].next = first[H];
    first[H] = p++;
    return v[p - 1].ans = 0;
  }
}mp;
#define lowbit(_) ((_) & (-_))
struct BIT {
  int Sum[MAXN], N;
  void add(int x, int v) {
    x++;
    for (int i = x; i <= N; i += lowbit(i))
      Sum[i] += v;
  }
  int Query(int x) {
    int ans = 0;
    x++;
    for (int i = x; i >= 1; i -= lowbit(i))
      ans += Sum[i];
    return ans;
  }
}bit[20];
int bin[20], AD, add[20];
int Query(int k) {
  int l = bin[k], r = bin[k + 1] - 1;
  l = (l - add[k] + bin[k + 1]) & (bin[k + 1] - 1);
  r = (r - add[k] + bin[k + 1]) & (bin[k + 1] - 1);
  if (r >= l) return bit[k].Query(r) - bit[k].Query(l - 1);
  else return bit[k].Query(r) + bit[k].Query(bit[k].N - 1) - bit[k].Query(l - 1);
}
int main() {
  int T = read();
  bin[0] = 1;
  for (int i = 1; i <= 19; ++i) bin[i] = bin[i - 1] * 2;
  for (int i = 0; i <= 18; ++i) bit[i].N = bin[i + 1];
  while (T--) {
    int op = read(), x = read();
    if (op == 0) {
      mp[x - AD]++;
      for (int i = 0; i <= 18; ++i) {
        int tmp = x & (bin[i + 1] - 1);
        tmp = (tmp - add[i] + bin[i + 1]) & (bin[i + 1] - 1);
        bit[i].add(tmp, 1);
      }
    } else if (op == 1) {
      int num = mp[x - AD];
      for (int i = 0; i <= 18; ++i) {
        int tmp = x & (bin[i + 1] - 1);
        tmp = (tmp - add[i] + bin[i + 1]) & (bin[i + 1] - 1);
        bit[i].add(tmp, -num);
      }
      mp[x - AD] = 0;
    } else if (op == 2) {
      AD += x;
      for (int i = 0; i <= 18; ++i)
        add[i] = (add[i] + x) & (bin[i + 1] - 1);
    } else if (op == 3) {
      printf ("%d\n", Query(x));
    }
  }
}
