#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
struct data {
  int a, b, id;
  bool type;
  bool operator < (const data &c) const {
    return a < c.a;
  }
}a[MAXN * 2];
int HashA[MAXN * 2], HashB[MAXN * 2], cntA, cntB;
int SumA[MAXN * 2], SumB[MAXN * 2], AnsA[MAXN], AnsB[MAXN];
int cnt = 0;
#define lowbit(_) ((_) & (-_))
void Add(int *Sum, int x) {
  for (int i = x; i <= cnt; i += lowbit(i)) {
    Sum[i]++;
  }
}
int Query(int *Sum, int x) {
  int ans = 0;
  for (int i = x; i > 0; i -= lowbit(i)) {
    ans += Sum[i];
  }
  return ans;
}
int Num[MAXN], Num2[MAXN];
int main() {
  int n, X1, Y1, X2, Y2;
  scanf ("%d", &n);  
  for (int i = 1; i <= n; i++) {
    scanf ("%d%d%d%d", &X1, &Y1, &X2, &Y2);
    a[++cnt].a = X1, a[cnt].b = Y1, a[cnt].type = 0, a[cnt].id = i;
    a[++cnt].a = X2, a[cnt].b = Y2, a[cnt].type = 1, a[cnt].id = i;
    HashA[++cntA] = X1, HashB[++cntB] = Y1;
    HashA[++cntA] = X2, HashB[++cntB] = Y2;
  }
  sort(HashA + 1, HashA + cnt + 1);
  sort(HashB + 1, HashB + cnt + 1);
  for (int i = 1; i <= cnt; i++) {
    a[i].a = lower_bound(HashA + 1, HashA + cnt + 1, a[i].a) - HashA;
    a[i].b = lower_bound(HashB + 1, HashB + cnt + 1, a[i].b) - HashB; 
    if (a[i].type == 0) Num[a[i].id] = a[i].b;
    if (a[i].type == 1) Num2[a[i].id] = a[i].b;
  }
  sort (a + 1, a + cnt + 1);
  for (int i = 1; i <= cnt; i++) {
    if (a[i].type == 0) {
      AnsA[a[i].id] += Query(SumA, a[i].b);
      AnsB[a[i].id] += Query(SumB, a[i].b);
      AnsA[a[i].id] -= Query(SumA, Num2[a[i].id]);
      AnsB[a[i].id] -= Query(SumB, Num2[a[i].id]);
      Add(SumA, a[i].b);
    } else {
      AnsA[a[i].id] += Query(SumA, a[i].b);
      AnsB[a[i].id] += Query(SumB, a[i].b);
      AnsA[a[i].id] -= Query(SumA, Num[a[i].id]);
      AnsB[a[i].id] -= Query(SumB, Num[a[i].id]);
      Add(SumB, a[i].b);
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (AnsA[i] != AnsB[i]) {
      ans = 1;
      // printf ("%d\n", i);
    }
  }
  printf ("%d\n", ans);
}