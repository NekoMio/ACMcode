#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#define N 100005
using namespace std;
char S[N];
int A[N], n, K;
int sm[30][N], L[30], R[30];
int su[N][30], zz[30];
int ans[N];
int sum[30];
bool check(int x) {
  int smm = 0;
  for (int i = 1; i <= 26; i++) {
    int tmp = su[n][i] - su[x - 1][i];
    tmp += sum[i];
    smm += min(R[i], tmp);
    if (tmp >= L[i]) {
      continue;
    }
    return 0;
  }
  if (smm < K) return 0;
  return 1;
}
int main() {
  while (~scanf("%s", S + 1)) {
    n = strlen(S + 1);
    scanf("%d", &K);
    int s = 0;
    for (int i = 1; i <= 26; i++) scanf("%d%d", &L[i], &R[i]), s += L[i];
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= n; i++) A[i] = S[i] - 'a' + 1;
    for (int i = 1; i <= 26; i++) sm[i][0] = 0, zz[i] = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= 26; j++) {
        su[i][j] = su[i - 1][j] + (A[i] == j);
      }
      sm[A[i]][0]++;
      sm[A[i]][sm[A[i]][0]] = i;
    }
    if (!check(1)) {
      printf("-1\n");
      continue;
    }
    int now = 0;
    for (int i = 1; i <= K; i++) {
      for (int j = 1; j <= 26; j++) {
        if (zz[j] > sm[j][0]) continue;
        if (sum[j] == R[j]) continue;
        while (zz[j] <= sm[j][0] && sm[j][zz[j]] < now) zz[j]++;
        if (zz[j] > sm[j][0]) continue;
        if (check(sm[j][zz[j]]) && K - i >= s - (sum[j] <= L[j])) {
          ans[i] = j;
          // cout<<i<<endl;
          now = sm[j][zz[j]];
          sum[j]++;
          if (sum[j] <= L[j]) {
            s--;
          }
          zz[j]++;
          break;
        }
      }
    }
    for (int i = 1; i <= K; i++) {
      printf("%c", 'a' + ans[i] - 1);
    }
    printf("\n");
  }
  return 0;
}
/*
ababc 4
0 3
0 3
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
aaabbb 4
0 4
1 3
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
*/