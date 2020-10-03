#pragma comment(linker, "/STACK:10240000000,10240000000")
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
int MOD;
const int MAXM = 1e5 + 5;
const int MD2 = 21788233;
struct Hash_Table {
  struct edge {
    int next, y;
    long long x;
    __int128 ans;
  }v[MAXM * 150];
  int first[MD2 + 1], p;
  void clear() {
    memset (first, -1, sizeof (first));
    p = 0;
  }
  Hash_Table() { clear(); }
  bool count(long long x, int y) {
    int H = (1ll * x * 7717 + 1ll * y * 19991) % MD2;
    for (int i = first[H]; i != -1; i = v[i].next) {
      if (v[i].x == x && v[i].y == y) {
        return 1;
      }
    }
    return 0;    
  }
  __int128 &operator () (long long x, int y) {
    int H = (1ll * x * 7717 + 1ll * y * 19991) % MD2;
    for (int i = first[H]; i != -1; i = v[i].next) {
      if (v[i].x == x && v[i].y == y) {
        return v[i].ans;
      }
    }
    v[p].x = x, v[p].y = y;
    v[p].next = first[H];
    first[H] = p++;
    return v[p - 1].ans = 0;
  }
}mp;
const int MAXN = 1e6 + 1;
bool isnprime[MAXN];
int prime[MAXN], cnt;
long long Sum[MAXN];
void Get_Prime(int n) {
  isnprime[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isnprime[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt; j++) {
      if (i * prime[j] > n) break;
      isnprime[i * prime[j]] = 1;
      if (i % prime[j] == 0) break; 
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!isnprime[i])
      Sum[i] = Sum[i - 1] + i;
    else
      Sum[i] = Sum[i - 1];
  } 
}
__int128 S(long long n, int m) {
  // printf ("%lld %d\n", n, m);
  if (m == 0 || m == 1) return (((__int128)2 + n) * (n - 1) / 2);
  if (mp.count(n,m)) return mp(n,m);
  if (1ll * m * m > n) return S(n, floor(sqrt(n)));
  if (isnprime[m]) return S(n, m - 1);
  return mp(n,m) = ((S(n, m - 1) -  m * (S(n / m, m - 1) - Sum[m - 1])));
}
bool flag[1004];
int main() {
  int T;
  scanf ("%d", &T);
  Get_Prime(200000);
  for (int i = 2; i <= 1000; i++) {
    memset (flag, 0, sizeof(flag));
    int Num = ((2 + i) * (i - 1) / 2);
    for (int j = 2; j * j < i; j++) {
      for (int k = 2; k * j <= i; k++){
        if (!flag[k * j]) {
          Num -= k * j;
          flag[k * j] = 1;
        }
      }
      mp(i, j) = Num;
    }
  }
  while (T--) {
    long long n;
    // mp.clear();
    scanf("%lld%d", &n, &MOD);
    printf ("%lld\n", (long long)(((((__int128)3 + n) * n / 2 - 4) % MOD) + S(n + 1, floor(sqrt(n + 1))) % MOD) % MOD);
  }
}