#include <bits/stdc++.h>
using namespace std;
int base = 131;
struct Map{
  int a[6][6], Num;
  unsigned Hash;
  void Get_Hash() {
    Hash = 0;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        Hash = Hash * base + a[i][j];
      }
    }
  }
}a, k;
int v;
queue<Map> Q;
set<unsigned> st;
bool flag[11];
bool TryMove1(int a[][6], int i, int j, int op) {
  if (op == 1) {
    if (j + 2 == 6) return 0;
    if (a[i][j + 2] == 0) return 1;
    if (a[i][j + 2] != a[i][j]) return 0;
    if (j + 3 == 6) return 0;
    if (a[i][j + 3] == 0) return 1;
    if (a[i][j + 3] != a[i][j]) return 0;
  } else {
    if (j - 1 == -1) return 0;
    if (a[i][j - 1] == 0) return 1;
    if (a[i][j - 1] != 0) return 0;
  }
}
bool TryMove2(int a[][6], int i, int j, int op) {
  if (op == 1) {
    if (i + 2 == 6) return 0;
    if (a[i + 2][j] == 0) return 1;
    if (a[i + 2][j] != a[i][j]) return 0;
    if (i + 3 == 6) return 0;
    if (a[i + 3][j] == 0) return 1;
    if (a[i + 3][j] != a[i][j]) return 0;
  } else {
    if (i - 1 == -1) return 0;
    if (a[i - 1][j] == 0) return 1;
    if (a[i - 1][j] != 0) return 0;
  }
}
int main() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      scanf ("%d", &a.a[i][j]);
    }
  }
  a.Get_Hash();
  a.Num = 0;
  Q.push(a);
  st.insert(a.Hash);
  while (!Q.empty()) {
    k = Q.front();
    memset (flag, 0, sizeof(flag));
    Q.pop();
    if (k.a[2][5] == 1 && k.a[2][4] == 1) {
      printf ("%d\n", k.Num + 2);
      return 0;
    }
    if (k.Num == 8) continue;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        if (k.a[i][j] != 0 && !flag[k.a[i][j]]) {
          flag[k.a[i][j]] = 1;
          if (k.a[i][j + 1] == k.a[i][j]) {
            v = k.a[i][j];
            if (TryMove1(k.a, i, j, 1)) {
              int d;
              if (j + 2 < 6 && k.a[i][j + 2] == v) d = 2;
              else d = 1;
              k.a[i][j] = 0, k.a[i][j + d + 1] = v;
              k.Get_Hash();
              if (st.find(k.Hash) == st.end()) {
                k.Num++;
                Q.push(k);
                st.insert(k.Hash);
                k.Num--;
              }
              k.a[i][j] = v, k.a[i][j + d + 1] = 0;
            }
            if (TryMove1(k.a, i, j, -1)) {
              int d;
              if (j + 2 < 6 && k.a[i][j + 2] == v) d = 2;
              else d = 1;
              k.a[i][j - 1] = v, k.a[i][j + d] = 0;
              k.Get_Hash();
              if (st.find(k.Hash) == st.end()) {
                k.Num++;
                Q.push(k);
                st.insert(k.Hash);
                k.Num--;
              }
              k.a[i][j - 1] = 0, k.a[i][j + d] = v;
            }
          } else {
            v = k.a[i][j];
            if (TryMove2(k.a, i, j, 1)) {
              int d;
              if (i + 2 < 6 && k.a[i + 2][j] == v) d = 2;
              else d = 1;
              k.a[i][j] = 0, k.a[i + d + 1][j] = v;
              k.Get_Hash();
              if (st.find(k.Hash) == st.end()) {
                k.Num++;
                Q.push(k);
                st.insert(k.Hash);
                k.Num--;
              }
              k.a[i][j] = v, k.a[i + d + 1][j] = 0;
            }
            if (TryMove2(k.a, i, j, -1)) {
              int d;
              if (i + 2 < 6 && k.a[i + 2][j] == v) d = 2;
              else d = 1;
              k.a[i - 1][j] = v, k.a[i + d][j] = 0;
              k.Get_Hash();
              if (st.find(k.Hash) == st.end()) {
                k.Num++;
                Q.push(k);
                st.insert(k.Hash);
                k.Num--;
              }
              k.a[i - 1][j] = 0, k.a[i + d][j] = v;
            }
          }
        }
      }
    }
  }
  printf ("-1\n");
}