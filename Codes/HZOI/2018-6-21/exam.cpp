#pragma GCC optimize("O3")
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
const int MAXN = 1e5;
int prime[MAXN + 2], cnt;
bool isnprime[MAXN + 2];
unsigned int d[MAXN + 2], F[MAXN + 2];
unsigned int Hash[41][41][41];
void Get_mu() {
  for (int i = 1; i <= MAXN; ++i) d[i] = 1;
  for (int i = 2; i <= MAXN; ++i) {
    if (!isnprime[i]) {
      prime[++cnt] = i;
      for (int j = 1; j * i <= MAXN; ++j) {
        d[i * j] += d[j];
        isnprime[i * j] = 1;
      }
    }
  }
  for (int i = 1; i <= MAXN; ++i) F[i] = F[i - 1] + d[i];
  reverse(prime + 1, prime + cnt + 1);
  for (int i = 1; i <= 40; ++i)
    for (int j = 1; j <= 40; ++j)
      for (int k = 1; k <= 40; ++k)
        Hash[i][j][k] = Hash[i - 1][j][k] + Hash[i][j - 1][k] + Hash[i][j][k - 1] - Hash[i - 1][j - 1][k] - Hash[i - 1][j][k - 1] - Hash[i][j - 1][k - 1] + Hash[i - 1][j - 1][k - 1] + d[i * j * k];
}
unsigned int DFS(int dep, int A, int B, int C) {
  if (!prime[dep]) return F[A] * F[B] * F[C];
  if (prime[dep] > max(A, max(B, C)) && max(A, max(B, C)) <= 40) return Hash[A][B][C];
  if (A == 0 || B == 0 || C == 0) return 0;
  int ans = DFS(dep + 1, A, B, C);
  if (A >= prime[dep] && B >= prime[dep])
    ans = ans - DFS(dep + 1, A / prime[dep], B / prime[dep], C);
  if (A >= prime[dep] && C >= prime[dep])
    ans = ans - DFS(dep + 1, A / prime[dep], B, C / prime[dep]);
  if (B >= prime[dep] && C >= prime[dep])
    ans = ans - DFS(dep + 1, A, B / prime[dep], C / prime[dep]);
  if (A >= prime[dep] && B >= prime[dep] && C >= prime[dep])
    ans = ans + 2 * DFS(dep + 1, A / prime[dep], B / prime[dep], C / prime[dep]);
  return ans;
}
int main() {
  Get_mu();
  int A = read(), B = read(), C = read();
  int t = 1;
  while (prime[t] > A && prime[t] > B && prime[t] > C) t++;
  printf ("%u\n", DFS(t, A, B, C));
}
