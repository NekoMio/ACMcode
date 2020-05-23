#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#define N 5001
using namespace std;
int n;
int f[N], p[N], A[N], B[N], zz;
int q[N][2], cnt[10005];
priority_queue<int> q1;
int ans[N];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p[i]);
    A[i] = p[i];
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &f[i]);
    B[i] = f[i];
  }
  sort(A + 1, A + n + 1);
  sort(B + 1, B + n + 1);
  int K = 0;
  for (int i = 1; i <= n; i++) {
    if (K < n && B[i] > A[K + 1]) K++;
  }
  for (int i = 1; i <= K; i++) {
    q[i][0] = A[i];
    cnt[A[i]]++;
    q[i][1] = B[n - K + i];
  }
  zz = K;
  for (int i = 1; i < n - K + 1; i++) {
    q1.push(B[i]);
  }

  for (int i = 1; i <= n; i++) {
    if (!cnt[p[i]]) {
      if (q[zz][1] <= p[i]) {
        ans[i] = q1.top();
        q1.pop();
      } else {
        ans[i] = q[zz][1];
        cnt[q[zz][0]]--;
        q[zz][0] = q[zz][1] = 0;
        zz--;
      }
    } else {
      int bj = 0;
      for (int j = 1; j <= zz; j++) {
        if (q[j][0] == p[i] && q[j + 1][0] != p[i]) {
          bj = j;
          break;
        }
      }
      for (int j = bj + 1; j <= zz; j++) {
        if (q[j][0] < q[bj][1]) {
          swap(q[bj][1], q[j][1]);
        } else
          break;
      }
      cnt[p[i]]--;
      ans[i] = q[bj][1];
      for (int j = bj; j <= zz; j++) {
        q[j][0] = q[j + 1][0];
        q[j][1] = q[j + 1][1];
      }
      q[zz][0] = q[zz][1] = 0;
      zz--;
    }
  }
  for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
  return 0;
}