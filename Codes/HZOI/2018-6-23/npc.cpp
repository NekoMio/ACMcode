#include <bits/stdc++.h>
using namespace std;
int Num = 0, Num2 = 0;
bool Fail;
void Test(int x, int y) {
  if (x > y) swap(x, y);
  if (x == 1 && y != 1) {
    Num = y + 1;
    Num2 = y - 1;
    return;
  }
  if (x == y) {
    Fail = 1;
    return;
  }
  Test(x, y - x);
  if (Fail) return;
  Num += 1;
  Num2 += 2;
}
int va[105], vb[105], *sa = va, *sb = vb;
int cnta, cntb, id;
void Build(int a, int b) {
  bool flag = 0;
  // if (a > b) swap(a, b), flag = 1;
  if (a == 1) {
    sa[++cnta] = id++;
    for (int i = 1; i <= b; ++i)
      sb[++cntb] = id++;
    for (int i = 1; i < b; ++i)
      printf ("%d %d\n", sb[i], sb[i + 1]);
    return;
  } else if (b == 1) {
    sb[++cntb] = id++;
    for (int i = 1; i <= a; ++i)
      sa[++cnta] = id++;
    for (int i = 1; i < a; ++i)
      printf ("%d %d\n", sa[i], sa[i + 1]);
    return;
  }
  if (b > a) {
    Build(a, b - a);
    sb[++cntb] = id++;
    printf ("%d %d\n", sa[cnta - 1], sb[cntb]);
    printf ("%d %d\n", sb[cntb - 1], sb[cntb]);
  } else {
    Build(a - b, b);
    sa[++cnta] = id++;
    printf ("%d %d\n", sa[cnta - 1], sa[cnta]);
    printf ("%d %d\n", sb[cntb - 1], sa[cnta]);
  }
  // if (flag) swap(sa, sb), swap(cnta, cntb);
}
int main() {
  int n;
  scanf ("%d", &n);
  int tp = 0;
  for (int i = 1; i <= n; ++i) {
    Fail = 0;
    Test(i, n - i);
    if (Num <= 50) {
      tp = i;
      break;
    }
  }
  printf ("%d %d\n", Num, Num2);
  Build(tp, n - tp);
}

