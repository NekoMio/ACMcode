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
int main() {
  int t;
  cin >> t;
  while (t--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a < b) {
      if (d < c) {
        cout << "AB//CD" << endl;
        continue;
      } else {
        if (b < d) {
          cout << "AB//DC" << endl;
          continue;
        } else {
          cout << "AB//CD" << endl;
          continue;
        }
      }
    }
    if (b < a) {
      if (c < d) {
        cout << "AB//DC" << endl;
        continue;
      } else {
        if (a < c) {
          cout << "AB//CD" << endl;
          continue;
        } else {
          cout << "AB//DC" << endl;
          continue;
        }
      }
    }
    if (b == a) {
      if (c > d) {
        cout << "AB//CD" << endl;
        continue;
      } else {
        cout << "AB//DC" << endl;
        continue;
      }
    }
  }
}