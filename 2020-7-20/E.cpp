#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
#define inf 0x3f3f3f3f
#define m(a) memset(a, 0, sizeof(a))
#define mm(a) memset(a, -1, sizeof(a))
#define mi(a) memset(a, 0x3f3f3f3f, sizeof(a))
int n, t;
int a[2000005];
int f(int x) {
  int cen = (n + 1) / 2;
  if (a[x] == cen) return 1;
  int f = 1;
  if (a[x] > cen) f = 0;
  int l = 0, sum = 0;
  for (int i = 1; i <= n; i++) {
    if (i == x) {
      l = 0;
      continue;
    }
    if ((a[i] > a[x]) == f) {
      l++;
      if (l == 3) {
        sum++;
        l -= 2;
      }
    } else if (l != 0)
      l--;
  }
  if (sum >= abs(a[x] - cen)) return 1;
  return 0;
}
int main() {
  scanf ("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
      if (f(i))
        printf("%d", 1);
      else {
        printf("%d", 0);
      }
    }
    printf ("\n");
  }
}