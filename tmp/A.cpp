#include <vector>
#include <cstring>
#include <cstdio>
#include <bitset>
using namespace std;
const int MAXN = 1e5 + 5;
int a[MAXN];
vector<int> T[MAXN], F[MAXN];
bitset<MAXN> TT, FF, ans1, ans2, ans;
int main() {
  int t;
  scanf ("%d", &t);
  while (t--) {
    int n, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf ("%d", &a[i]);
      if (a[i] < 0) {
        F[-a[i]].push_back(i);
        FF[i] = 1;
      }
      else {
        T[a[i]].push_back(i);
        TT[i] = 1;
      }
    }
    int FFc = FF.count();
    for (int i = 1; i <= n; i++) {
      if (FFc - (int)F[i].size() + (int)T[i].size() == m) {
        for (int j = 0; j < T[i].size(); j++)
          TT[T[i][j]] = 0, ans2[T[i][j]] = 1;
        for (int j = 0; j < F[i].size(); j++)
          FF[F[i][j]] = 0, ans1[F[i][j]] = 1;
        ans1 |= TT, ans2 |= FF;
        for (int j = 0; j < T[i].size(); j++)
          TT[T[i][j]] = 1;
        for (int j = 0; j < F[i].size(); j++)
          FF[F[i][j]] = 1;
      }
    }
    ans = ans1 ^ ans2;
    for (int i = 1; i <= n; i++) {
      if (ans[i] && ans1[i]) printf ("Lie\n");
      if (ans[i] && ans2[i]) printf ("Truth\n");
      if (!ans[i]) printf ("Not defined\n");
    }
    for (int i = 1; i <= n; i++) T[i].clear(), F[i].clear();
    TT.reset(), FF.reset(), ans1.reset(), ans2.reset(), ans.reset();
  }
}