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
struct data {
  int x, y, id;
  data operator - (const data &a) const {
    return (data){x - a.x, y - a.y, id};
  }
  bool operator < (const data &a) const {
    bool c = atan2(-y, x) == atan2(-a.y, a.x);
    return c ? atan2(-y, x) < atan2(-a.y, a.x) : id < a.id;
  }
  bool operator == (const data &a) const {
    return x == a.x && y == a.y;
  }
  long long operator * (const data &a) const {
    return 1ll * x * a.x + 1ll * y * a.y;
  }
  long long operator ^ (const data &a) const {
    return 1ll * x * a.y - a.x * y;
  }
  bool zero() {
    return x == 0 && y == 0;
  }
}p[2005], a[2005], tp[2005], tp2[2005];
int n, q;
int Calc1(int x) {
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    tp[++cnt] = p[i] - a[x];
    if (tp[cnt].zero()) cnt--;
  }
  int ans = 0;
  sort(tp + 1, tp + cnt + 1);
  for (int i = 1, j = 2; i <= cnt;) {
    int x1 = tp[i] * tp[j];
    int x2 = tp[i] ^ tp[j];
    if (x2 > 0) i++;
    else {
      if (x1 > 0) j++;
      else if (x1 == 0) ans++, i++;
      else i++;
      if (j == cnt + 1) j = 1;
    }
  }
  return ans;
}
int Ans[2005];
int Calc2(int x) {
  int cnt = 0;
  bool flag1 = 0, flag2 = 0;
  for (int i = 1; i <= n; i++) if (i != x) {
    tp[++cnt] = p[i] - p[x];
    if (tp[cnt].zero()) cnt--;
    if (tp[cnt].x == 0) flag1 = 1;
    if (tp[cnt].y == 0) flag2 = 1;
  }
  if (!flag2) tp[++cnt] = (data){1, 0, 0};
  if (!flag1) tp[++cnt] = (data){0, 1, 0};
  int cnt2 = 0;
  flag1 = 0, flag2 = 0;
  for (int i = 1; i <= q; i++) {
    tp2[++cnt2] = a[i] - p[x];
    if (tp2[cnt2].zero()) cnt2--;
    if (tp2[cnt2].x == 0) flag1 = 1;
    if (tp2[cnt2].y == 0) flag2 = 1;
  }
  if (!flag2) tp2[++cnt2] = (data){1, 0, 0};
  if (!flag1) tp2[++cnt2] = (data){0, 1, 0};
  // tp2[++cnt2] = (data){-1, 0, 0};
  // tp2[++cnt2] = (data){0, -1, 0};

  int ans = 0;
  sort(tp + 1, tp + cnt + 1);
  sort(tp2 + 1, tp2 + cnt2 + 1);
  // cnt2 = unique(tp2 + 1, tp2 + cnt2 + 1) - tp2;
  int tmp = 0;
  for (int i = 1; i <= cnt2; i++) {
    if (tp[1] < tp2[i]) {
      tmp = i;
      break;
    }
  }
  if (tmp != 0) {
    for (int i = 1, j = tmp; i <= cnt;) {
      int x1 = tp[i] * tp2[j];
      int x2 = tp[i] ^ tp2[j];
      if (x2 > 0) i++;
      else {
        if (x1 > 0) j++;
        else if (x1 == 0) {
          if (tp[i].id != 0) Ans[tp2[j].id]++;
          // fprintf(stderr, "::%d\n", tp2[j].id);
          i++;
        }
        else i++;
        if (j == cnt2 + 1) j = 1;
      }
    }
  }
  for (int i = 1; i <= cnt; i++) {
    if (tp2[1] < tp[i]) {
      tmp = i;
      break;
    }
  }
  if (tmp != 0) {
    for (int i = 1, j = tmp; i <= cnt2;) {
      int x1 = tp2[i] * tp[j];
      int x2 = tp2[i] ^ tp[j];
      if (x2 > 0) i++;
      else {
        if (x1 > 0) j++;
        else if (x1 == 0) {
          if (tp[j].id != 0) Ans[tp2[i].id]++;
          // fprintf(stderr, "::%d\n", tp2[j].id);
          i++;
        }
        else i++;
        if (j == cnt + 1) j = 1;
      }
    }
  }
}
int main() {
  n = read(), q = read();
  for (int i = 1; i <= n; i++) {
    p[i].x = read(), p[i].y = read();
    p[i].id = 10;
  }
  int ans = 0;
  for (int i = 1; i <= q; i++) {
    a[i].x = read(), a[i].y = read();
    a[i].id = i;
    Ans[i] += Calc1(i);
  }
  for (int i = 1; i <= n; i++) {
    Calc2(i);
  }
  for (int i = 1; i <= q; i++) {
    printf ("%d\n", Ans[i]);
  }
}