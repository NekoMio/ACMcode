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
const int MAXN = 2e5 + 5;
int a[MAXN], b[MAXN];
long long SumA[MAXN], SumB[MAXN];
stack<int> st;
int main() {
  int T = read();
  while (T--) {
    int n = read(), k = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) b[i] = read();
    for (int i = 1; i <= n; i++) SumA[i] = SumA[i - 1] + a[i];
    for (int i = 1; i <= n; i++) SumB[i] = SumB[i - 1] + b[i];
    long long SumAA = 0, SumBB = 0;
    int pos = -1;
    for (int i = n, ds = n; i >= 0; i--) {
      if (SumA[i] > SumB[i]) {
        if (SumAA + SumA[i] - SumB[i] < k) {
          if (SumBB >= k)
            pos = i;
        } else {
          while (SumAA + SumA[i] - SumB[i] >= k && ds > i) 
            SumAA -= a[ds], SumBB -= b[ds], ds--;
          if (SumAA + SumA[i] - SumB[i] < k && SumBB >= k)
            pos = i;
        }
      } else {
        if (SumAA < k) {
          if (SumBB + SumB[i] - SumA[i] >= k) pos = i;
        } else {
          while (SumAA >= k && ds > i) 
            SumAA -= a[ds], SumBB -= b[ds], ds--;
          if (SumAA < k && SumBB + SumB[i] - SumA[i] >= k)
            pos = i;
        }
      }
      SumAA += a[i], SumBB += b[i];
    }
    if (pos == -1) {
      printf ("-1\n");
      continue;
    } else if (pos == 0) {
      printf ("0\n\n");
      continue;
    }
    bool flag = 0;
    SumAA = 0, SumBB = 0;
    st.push(pos + 1);
    for (int i = pos; i >= 0; i--) {
      if (SumA[i] > SumB[i]) {
        if (SumAA + SumA[i] - SumB[i] >= k) {
          if (i + 2 == st.top()) flag = 1;
          st.push(i + 1);
          SumAA = a[i + 1], SumBB = b[i + 1];
        }
      } else {
        if (SumAA >= k) {
          if (i + 2 == st.top()) flag = 1;
          st.push(i + 1);
          SumAA = a[i + 1], SumBB = b[i + 1];
        }
      }
      SumAA += a[i], SumBB += b[i];
    }
    if (flag) {
      printf ("-1\n");
      while (!st.empty()) st.pop();
      continue;
    }
    printf ("%d\n", st.size());
    while (!st.empty()) {
      if (st.size() != 1) printf ("%d ", st.top());
      else printf ("%d ", st.top() - 1);
      st.pop();
    }
    printf ("\n");
  }
}