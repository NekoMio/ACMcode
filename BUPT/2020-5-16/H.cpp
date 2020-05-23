#include <bits/stdc++.h>
using namespace std;
int R[7][7], C[7][7];
int Map[7][7], ans;
int SS[7][100][7], Num[7];
int rr, cc;
bool Judge() {
  for (int i = 1; i <= cc; i++) {
    int Num = 0, now = 1;
    for (int j = 1; j <= rr; j++) {
      if (Map[j][i] == 0) {
        if (Num != 0) {
          if (Num != C[i][now] || now > C[i][0])
            return 0;
          now++;
        }
        Num = 0;
      }
      else {
        Num++;
      }
    }
    if (Num != 0) {
      if (Num != C[i][now] || now > C[i][0])
        return 0;
      now++;
    }
    if (now <= C[i][0]) return 0;
  }
  return 1;
}
void DFS(int Dep, int r) {
  if (Dep == r + 1) {
    if (Judge()) ans++;
    return;
  }
  for (int i = 1; i <= Num[Dep]; i++) {
    int now = 0;
    for (int j = 1, k = 1; j <= SS[Dep][i][0]; j++, k++) {
      for (int l = 1; l <= SS[Dep][i][j]; l++) Map[Dep][++now] = 0;
      if (k <= R[Dep][0]) for (int l = 1; l <= R[Dep][k]; l++) Map[Dep][++now] = 1;
    }
    DFS(Dep + 1, r);
  }
}
int tmp[7];
void Init(int n, int c, int R[], int I, int dep) {
  if (c < 0) return;
  if (dep == n) {
    if (c != 0) SS[I][++Num[I]][0] = n + 1, SS[I][Num[I]][n + 1] = c;
    else SS[I][++Num[I]][0] = n;
    for (int i = 1; i <= n; i++) SS[I][Num[I]][i] = tmp[i - 1];
    return;
  }
  if (c == 0) return;
  for (int i = (dep != 0); i <= c; i++) {
    tmp[dep] = i;
    Init(n, c - R[dep + 1] - i, R, I, dep + 1);
  }
}
int main() {
  scanf ("%d%d", &rr, &cc);
  for (int i = 1; i <= rr; i++) {
    scanf ("%d", &R[i][0]);
    for (int j = 1; j <= R[i][0]; j++) {
      scanf ("%d", &R[i][j]);
    }
  }
  for (int i = 1; i <= cc; i++) {
    scanf ("%d", &C[i][0]);
    for (int j = 1; j <= C[i][0]; j++) {
      scanf ("%d", &C[i][j]);
    }
  }
  for (int i = 1; i <= rr; i++) {
    Init(R[i][0], cc, R[i], i, 0);
  }
  DFS(1, rr);
  printf ("%d\n", ans);
}