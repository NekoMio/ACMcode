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
map<ll, map<ll, int> > ls;
vector<pair<int, int> > q;
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    q.push_back(make_pair(x, y));
  }
  int maxx = 0;
  int l = q.size();
  for (int i = 0; i < l; i++) {
    double x1 = q[i].first, y1 = q[i].second;
    for (int j = 0; j < l; j++)
      if (i != j) {
        double x2 = q[j].first, y2 = q[j].second;
        if (x1 == 0) {
          if (x2 == 0) {
            continue;
          }
          if (y2 == 0) {
            maxx =
                max(maxx, ++ls[(ll)round(5000000 * (x2))][(ll)round(
                              5000000 * y1)]);  // cout<<i<<" "<<x1<<" "<<y1<<"
                                                // "<<x2<<" "<<y2<<" "<<x2/2<<"
                                                // "<<y1/2<<" "<<maxx<<endl;
            continue;
          }
          double ansy = y1 / 2;
          double ansx = ((y2 * y2 - y1 * y2) / x2 + x2) / 2;
          maxx =
              max(maxx, ++ls[(ll)round(10000000 * ansx)][(ll)round(
                            10000000 * ansy)]);  // cout<<i<<" "<<x1<<" "<<y1<<"
                                                 // "<<x2<<" "<<y2<<" "<<ansx<<"
                                                 // "<<ansy<<" "<<maxx<<endl;
          continue;
        }
        if (y1 == 0) {
          if (x2 == 0) {
            maxx =
                max(maxx, ++ls[(ll)round(5000000 * (x1))][(ll)round(
                              5000000 * y2)]);  // cout<<i<<" "<<x1<<" "<<y1<<"
                                                // "<<x2<<" "<<y2<<" "<<x1/2<<"
                                                // "<<y2/2<<" "<<maxx<<endl;
            continue;
          }
          if (y2 == 0) continue;
          double ansx = x1 / 2;
          double ansy = -(x1 - x2) * x2 / (2 * y2) + y2 / 2;
          maxx =
              max(maxx, ++ls[(ll)round(10000000 * ansx)][(ll)round(
                            10000000 * ansy)]);  // cout<<i<<" "<<x1<<" "<<y1<<"
                                                 // "<<x2<<" "<<y2<<" "<<ansx<<"
                                                 // "<<ansy<<" "<<maxx<<endl;
          continue;
        }
        if (x2 == 0) {
          double ansy = y2 / 2;
          double ansx = ((y1 * y1 - y2 * y1) / x1 + x1) / 2;
          maxx =
              max(maxx, ++ls[(ll)round(10000000 * ansx)][(ll)round(
                            10000000 * ansy)]);  // cout<<i<<" "<<x1<<" "<<y1<<"
                                                 // "<<x2<<" "<<y2<<" "<<ansx<<"
                                                 // "<<ansy<<" "<<maxx<<endl;
          continue;
        }
        if (y2 == 0) {
          double ansx = x2 / 2;
          double ansy = -(x2 - x1) * x1 / (2 * y1) + y1 / 2;
          maxx =
              max(maxx, ++ls[(ll)round(10000000 * ansx)][(ll)round(
                            10000000 * ansy)]);  // cout<<i<<" "<<x1<<" "<<y1<<"
                                                 // "<<x2<<" "<<y2<<" "<<ansx<<"
                                                 // "<<ansy<<" "<<maxx<<endl;
          continue;
        }
        // double ansx=(y2-y1)*(x1*x1+y1*y1-y2*y2-x2*x2)/(x1*y2-x2*y1);
        double ansx =
            (y1 * y1 * y2 - y2 * y2 * y1 + x1 * y2 * x1 - x2 * x2 * y1) /
            (2 * x1 * y2 - 2 * x2 * y1);
        double ansy = -ansx * (x1 / y1) + x1 * x1 / 2 / y1 + y1 / 2;
        maxx = max(
            maxx, ++ls[(ll)round(10000000 * ansx)][(ll)round(10000000 * ansy)]);
        // cout<<i<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<ansx<<" "<<ansy<<"
        // "<<maxx<<endl;
      }
    ls.clear();
  }
  cout << maxx + 1 << endl;
}