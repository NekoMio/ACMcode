#include <bits/stdc++.h>
using namespace std;
struct data {
  char name[12];
  string val;
  int time, pos, tp;
  bool operator < (const data &a) const  {
    if (time == a.time) return pos < a.pos;
    return time < a.time;
  } 
}a[2005];
map<string, int> mp;
set<pair<int, pair<string, string>>> st;
map<pair<string, string>, int> id;
set<pair<string, string>> flag;
bool Judge(string &s) {
  for (auto x : s) {
    if (x < '0' || x > '9') return 0;
  }
  if (s.length() != 18) return 0; 
  return 1;
}
int main() {
  int D, P;
  scanf ("%d%d", &D, &P);
  int cnt = 0;
  int SS = 0;
  for (int i = 1; i <= D; i++) {
    int T, S;
    scanf ("%d%d", &T, &S);
    int t1, t2;
    for (int j = 1; j <= T; j++) {
      cin >> a[j].name >> a[j].val >> a[j].tp;
      scanf ("%d:%d", &t1, &t2);
      a[j].time = t1 * 60 + t2;
      a[j].pos = j;
    }
    sort(a + 1, a + T + 1);
    for (int j = 1; j <= T; j++) {
      if (Judge(a[j].val)) {
        if (!mp.count(a[j].val) || i - mp[a[j].val] > P) {
          cout << a[j].name << " " << a[j].val << "\n";
          S--;
          id[pair<string, string>(a[j].name, a[j].val)] = ++cnt;
          mp[a[j].val] = i;
          if (S == 0) break;
        }
        if (a[j].tp == 1) {
          if (id.count(pair<string, string>(a[j].name, a[j].val)) && !flag.count(pair<string, string>(a[j].name, a[j].val))) {
            st.insert(pair<int, pair<string, string>>(id[pair<string, string>(a[j].name, a[j].val)], pair<string, string>(a[j].name, a[j].val)));
            flag.insert(pair<string, string>(a[j].name, a[j].val));
          }
        } else if (flag.count(pair<string, string>(a[j].name, a[j].val))) {
          st.erase(pair<int, pair<string, string>>(id[pair<string, string>(a[j].name, a[j].val)], pair<string, string>(a[j].name, a[j].val)));
          flag.erase(pair<string, string>(a[j].name, a[j].val));
        }
      }
    }
  }
  for (auto x : st) {
    cout << x.second.first << " " << x.second.second << '\n';
  }
}