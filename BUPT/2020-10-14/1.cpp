#include <algorithm>
#include <cmath>
#include <cstdio>
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
#define hzt cout << 1;
map<string, int> ls;
int main() {
  int t;
  cin >> t;
  int cnt = 1;
  ls["Beijing"] = 8;
  ls["Washington"] = -5;
  ls["London"] = 0;
  ls["Moscow"] = 3;
  while (t--) {
    int a, b;
    string y, s1, s2;
    scanf("%d:%d", &a, &b);
    string bb = to_string(b);
    if (bb.size() == 1) {
      bb = "0" + bb;
    }
    cin >> y;
    cin >> s1 >> s2;
    if (a == 12) a = 0;
    a += ls[s2] - ls[s1];
    if (y == "PM") a += 12;
    cout << "Case " << cnt++ << ": ";
    if (a < -12) {
      cout << "Yesterday " << 11 << ":" << bb << " "
           << "AM" << endl;
      continue;
    }
    if (a == -12) {
      cout << "Yesterday " << 12 << ":" << bb << " "
           << "PM" << endl;
      continue;
    }
    if (a < 0) {
      cout << "Yesterday " << 12 + a << ":" << bb << " "
           << "PM" << endl;
      continue;
    }
    if (a == 0) {
      cout << "Today " << 12 << ":" << bb << " "
           << "AM" << endl;
      continue;
    }
    if (a < 12) {
      cout << "Today " << a << ":" << bb << " "
           << "AM" << endl;
      continue;
    }
    if (a == 12) {
      cout << "Today " << 12 << ":" << bb << " "
           << "PM" << endl;
      continue;
    }
    if (a < 24) {
      cout << "Today " << a - 12 << ":" << b << " "
           << "PM" << endl;
      continue;
    }
    if (a == 24) {
      cout << "Tomorrow " << 12 << ":" << bb << " "
           << "AM" << endl;
      continue;
    }
    if (a < 36) {
      cout << "Tomorrow " << a - 24 << ":" << bb << " "
           << "AM" << endl;
      continue;
    }
    if (a == 36) {
      cout << "Tomorrow " << 12 << ":" << b << " "
           << "PM" << endl;
      continue;
    } else {
      cout << "Tomorrow " << a - 36 << ":" << b << " "
           << "PM" << endl;
      continue;
    }
  }
}