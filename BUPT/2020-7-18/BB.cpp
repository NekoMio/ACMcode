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
char s[2000006];
int main() {
  scanf ("%s", s);
  int q = strlen(s);
  int n;
  scanf("%d", &n);
  ll now = 0;
  while (n--) {
    char xx[3];
    int x;
    scanf ("%s%d", xx, &x);
    if (xx[0] == 'A') {
      int qqq = ((x + now) % q + q) % q;
      if (qqq == 0) qqq = q;
      printf("%c\n", s[qqq - 1]);
    } else {
      now += x;
      now %= q;
    }
  }
}