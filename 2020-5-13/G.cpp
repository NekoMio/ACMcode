#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
struct data {
  int a, id;
  bool type;
  bool operator < (const data &c) const {
    return a < c.a;
  }
}a[MAXN * 2], b[MAXN * 2];
list<int> ls;
set<int> ST[MAXN]; 
int main() {
  int n, X1, Y1, X2, Y2;
  scanf ("%d", &n);  
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    scanf ("%d%d%d%d", &X1, &Y1, &X2, &Y2);
    a[++cnt].a = X1, a[cnt].type = 0, a[cnt].id = i;
    b[cnt].a = Y1, b[cnt].type = 0, b[cnt].id = i;
    a[++cnt].a = X2, a[cnt].type = 1, a[cnt].id = i;
    b[cnt].a = Y2, b[cnt].type = 1, b[cnt].id = i;
  }
  sort(a + 1, a + cnt + 1);
  sort(b + 1, b + cnt + 1);
  bool flag = 0;
  for (int i = 1; i <= cnt; i++) {
    if (a[i].type == 0) {
      ls.push_front(a[i].id);
    } else {
      for (auto j = ls.begin(); j != ls.end(); j++) {
        // printf ("%d ", *j);
        if (*j != a[i].id) {
          ST[*j].insert(a[i].id);
          ST[a[i].id].insert(*j);
        } else {
          ls.erase(j);
          break;
        }
      }
    }
  }
  for (int i = 1; i <= cnt; i++) {
    if (b[i].type == 0) {
      ls.push_front(b[i].id);
    } else {
      for (auto j = ls.begin(); j != ls.end(); j++) {
        if (*j != b[i].id) {
          if (ST[*j].find(b[i].id) != ST[*j].end())
            flag = 1;
          if (ST[b[i].id].find(*j) != ST[b[i].id].end())
            flag = 1;
        } else {
          ls.erase(j);
          break;
        }
      }
    }
  }
  if (flag == 0) printf ("0\n");
  else printf ("1\n");
}