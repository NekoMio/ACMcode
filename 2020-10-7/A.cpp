#include <bits/stdc++.h>
using namespace std;
struct edge {
  int END, next;
}v[505];
int first[205], p;
int val[205];
int du[205];
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
  du[b]++;
}
int q1[204], q2[205];
bool Judge(int j, int k, int a, int b) {
  if ((val[q1[j]] ^ val[q2[k]]) != (val[q1[a]] ^ val[q2[b]])) return (val[q1[j]] ^ val[q2[k]]) > (val[q1[a]] ^ val[q2[b]]);
  if ((val[q1[j]]) != (val[q1[a]])) return (val[q1[j]]) > (val[q1[a]]);
  if (q1[j] != q1[a]) return q1[j] > q1[a];
  return q2[k] > q2[b]; 
}
int main() {
  int n;
  scanf ("%d", &n);
  memset(first, -1, sizeof(first));
  for (int i = 1; i <= 2 * n; i++) {
    scanf ("%d", &val[i]);
  }
  int b;
  for (int i = 1; i <= 2 * n; i++) {
    scanf ("%d", &b);
    if (b != 0)
      add(i, b);
  }
  int qe1 = 0, qe2 = 0;
  for (int i = 1; i <= n; i++) {
    if (du[i] == 0) q1[++qe1] = i;
  }
  for (int i = n + 1; i <= 2 * n; i++) {
    if (du[i] == 0) q2[++qe2] = i;
  }
  for (int i = 1; i <= n; i++) {
    int a = 0;
    b = 0;
    for (int j = 1; j <= qe1; j++) {
      if (q1[j] != 0) {
        for (int k = 1; k <= qe2; k++) {
          if (q2[k] != 0) {
            if (Judge(j, k, a, b)) {
              a = j;
              b = k;
            }
          }
        }
      }
    }
    // if (a == 0 || b == 0) break;
    for (int j = first[q1[a]]; j != -1; j = v[j].next) {
      du[v[j].END]--;
      if (du[v[j].END] == 0) q1[++qe1] = v[j].END;
    }
    for (int j = first[q2[b]]; j != -1; j = v[j].next) {
      du[v[j].END]--;
      if (du[v[j].END] == 0) q2[++qe2] = v[j].END;
    }
    printf ("%d ", val[q1[a]] ^ val[q2[b]]);
    q1[a] = 0, q2[b] = 0;
  }
}