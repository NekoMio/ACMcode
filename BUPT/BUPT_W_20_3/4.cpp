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
const int MOD = 1e9 + 7;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int a[MAXN];
const int full = 30;
const int INF = 0x7fffffff;
int Minn = 0, numm = 0;
long long Tot = 1;
struct Trie {
  struct Trie_Node {
    int s;
    Trie_Node *ch[2];
    Trie_Node() {
      ch[0] = ch[1] = NULL;
      s = 0;
    }
  } *root;
#define size(_) ((_) ? (_)->s : 0)
  Trie() { root = new Trie_Node(); }
  void Insert(int x) {
    Trie_Node *rt = root;
    for (int i = full; i >= 0; i--) {
      int nxt = (x >> i) & 1;
      if (rt->ch[nxt] == NULL) rt->ch[nxt] = new Trie_Node();
      rt = rt->ch[nxt];
      rt->s++;
    }
  }
  int Min(int x, Trie_Node *rt, int h, int &Size) {
    int res = 0;
    for (int i = h; i >= 0; i--) {
      int nxt = (x >> i) & 1;
      if (rt->ch[nxt]) {
        // res |= nxt << i;
        rt = rt->ch[nxt];
      } else {
        res |= 1 << i;
        rt = rt->ch[nxt ^ 1];
      }
    }
    Size = rt->s;
    return res;
  }
  void Calc(Trie_Node *rt1, Trie_Node *rt2, int num, int dep, int h) {
    if (dep == 0) {
      int Size = 0;
      int t = Min(num, rt1, h - 1, Size);
      // if (Size == 2) printf ("%d %d\n", t, Minn);
      if (t < Minn) {
        Minn = t;
        numm = Size * rt2->s;
      } else if (t == Minn) {
        numm += Size * rt2->s;
      }
    } else {
      if (rt2->ch[0]) Calc(rt1, rt2->ch[0], num, dep - 1, h);
      if (rt2->ch[1]) Calc(rt1, rt2->ch[1], num | (1 << dep - 1), dep - 1, h);
    }
  }
  long long DFS(Trie_Node *rt, int dep) {
    if (rt->ch[0] && rt->ch[1]) {
      Minn = INF;
      numm = 0;
      Calc(rt->ch[0], rt->ch[1], 0, dep, dep);
      Tot = Tot * numm % MOD;
      // printf ("%d\n", numm);
      return  (Minn | (1 << dep)) + DFS(rt->ch[0], dep - 1) + DFS(rt->ch[1], dep - 1);
    } else if (rt->ch[0]) {
      return DFS(rt->ch[0], dep - 1);
    } else if (rt->ch[1]) {
      return DFS(rt->ch[1], dep - 1);
    } else {
      if (rt->s > 1) {
        Tot = Tot * pow_mod(rt->s, rt->s - 2) % MOD;
        // printf ("%d---\n", rt->s);
      }
    }
    return 0;
  }
} root;

int main() {
  int n = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
    root.Insert(a[i]);
  }
  printf ("%lld\n", root.DFS(root.root, full));
  printf ("%lld\n", Tot);
  // while (1);
}