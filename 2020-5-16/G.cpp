#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
#define inf 0x3f3f3f3f
#define m(a) memset(a, 0, sizeof(a))
#define mm(a) memset(a, -1, sizeof(a))
#define mi(a) memset(a, 0x3f3f3f3f, sizeof(a))
int a[15], b[15];
int main() {
  ll n;
  int t = 9;
  a[1] = 10;
  a[2] = 29;
  for (int i = 3; i <= 9; i++) {
    a[i] = a[i - 1];
    a[i] += 9 + (i - 1) * 10;
  }
  cin >> t;
  int flag = 0;
  while (t--) {
    cin >> n;
    ll q = n, ans = 0;
    int i = 1;
    int c;
    if (n == 1) {
      cout << "0" << endl;
      continue;
    }
    if (n == 2) {
      cout << "1" << endl;
      continue;
    }
    while (q) {
      c = q % 10;
      q /= 10;
      if (c != 0) break;
    }
    if (q == 0) {
      flag = 1;
      n--;
    }
    q = n;
    while (q) {
      b[i] = q % 10;
      q /= 10;
      i++;
    }
    i--;
    ans += a[i - 1];
    q = i;
    if (b[i] > 1) ans += b[i];
    for (int j = 2; j < i; j++) {
      if (b[j] != 0) ans += b[j] + 1;
    }
    if (i != 1) ans += b[1];
    ans -= 1;
    if (flag)
      cout << ans + 1 << endl;
    else {
      cout << ans << endl;
    }
    flag = 0;
  }
}