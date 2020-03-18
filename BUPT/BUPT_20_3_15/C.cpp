#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define N 2004
using namespace std;
int T, n;
int zz, a[N];
struct ro {
  int to, next, l;
} road[N * N];
void build(int x, int y, int z) {
  zz++;
  road[zz].to = y;
  road[zz].next = a[x];
  road[zz].l = z;
  a[x] = zz;
}
long long dis[N];
bool rd[N];
long long p = 998244353;
queue<int> q1;
long long spfa(int S) {
  memset(dis, 0x3f, sizeof(dis));
  dis[S] = 0;
  q1.push(S);
  while (!q1.empty()) {
    int x = q1.front();
    q1.pop();
    rd[x] = 0;
    for (int i = a[x]; i; i = road[i].next) {
      int y = road[i].to;
      if (dis[y] > dis[x] + road[i].l) {
        dis[y] = dis[x] + road[i].l;
        if (!rd[y]) {
          rd[y] = 1;
          q1.push(y);
        }
      }
    }
  }
  long long sm = 0;
  for (int i = 1; i <= n; i++) sm += dis[i], sm %= p;
  return sm;
}
long long get(long long x, long long y) {
  for (int i = 1; i <= x * y; i++) {
    if (((int)sqrt(x * y * i)) * ((int)sqrt(x * y * i)) == x * y * i) return i;
  }
  return x * y;
}
int main() {
  int T = 100;
  long long ans = 0;
  for (int ll = 1; ll <= T; ll++) {
    n = ll;
    for (int j = 1; j < n; j++) {
      long long x = get(n, j);
      //	cout<<n<<' '<<j<<' '<<x<<endl;
      build(j, n, x);
      build(n, j, x);
    }
    ans += spfa(n);
    ans %= p;
    printf("%d   %lld\n", ll, ans);
  }
  return 0;
}
/*
3
2 2 1
00
10
5 5 1
00100
10101
00100
01000
11101
1
5 5 2
00100
10101
00100
01000
11101
*/
