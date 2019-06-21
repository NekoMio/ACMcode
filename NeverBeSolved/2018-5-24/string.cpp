#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int MAXN = 1e5 + 5;
list<int> dq;
set<unsigned int> st;
int a[MAXN << 1], cnt;
char s[10];
void addl(int x) { dq.push_front(x); }
void addr(int x) { dq.push_back(x); }
bool Judge(int l, int r) {
  for (int i = l, j = r; i != j; i++, j--) {
    if (a[i] != a[j]) return 0;
  }
  return 1;
}
unsigned int base = 31;
unsigned int Hash(int l, int r) {
  unsigned int ans = 0;
  for (int i = l; i <= r; i++) ans = ans * base + a[i];
  return ans;
}
unsigned int h[MAXN << 1], bin[MAXN << 1];
unsigned int Get_Hash(int l, int r) { return h[r] - h[l - 1] * bin[r - l + 1]; }
int Calc(unsigned int x, int len) {
  int ans = 0;
  for (int i = 1; i + len - 1 <= cnt; i++) {
    if (Get_Hash(i, i + len - 1) == x) ans++;
  }
  return ans;
}
int transl(int l1, int r1, int l2, int r2) {
  st.clear();
  cnt = 0;
  int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
  for (auto x : dq) a[++cnt] = x;
  int len = 0, ans = 0;
  for (int i = 1; i <= cnt; i++) {
    h[i] = h[i - 1] * base + a[i];
  }
  unsigned int tmp = 0;
  for (; len < min(len1, len2) && a[r1 - len] == a[r2 - len]; len++) {
  }
  for (int i = l1; r1 - i + 1 >= len; i++) {
    if (Judge(i, r1) && !st.count(tmp = Hash(i, r1))) {
      ans += (r1 - i + 1) * Calc(tmp, r1 - i + 1);
      st.insert(tmp);
    }
  }
  for (int i = r2 - len; i >= l2; i--) {
    if (Judge(i, r2) && !st.count(tmp = Hash(i, r2))) {
      ans += (r2 - i + 1) * Calc(tmp, r2 - i + 1);
      st.insert(tmp);
    }
  }
  return ans;
}
int transr(int l1, int r1, int l2, int r2) {
  st.clear();
  cnt = 0;
  int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
  for (auto x : dq) a[++cnt] = x;
  int len = 0, ans = 0;
  unsigned int tmp = 0;
  for (int i = 1; i <= cnt; i++) {
    h[i] = h[i - 1] * base + a[i];
  }
  for (; len < min(len1, len2) && a[l1 + len] == a[l2 + len]; len++) {
  }
  for (int i = r1; i - l1 + 1 >= len; i--) {
    if (Judge(l1, i) && !st.count(tmp = Get_Hash(l1, i))) {
      ans += (i - l1 + 1) * Calc(tmp, i - l1 + 1);
      st.insert(tmp);
    }
  }
  for (int i = l2 + len; i <= r2; i++) {
    if (Judge(l2, i) && !st.count(tmp = Get_Hash(l2, i))) {
      ans += (i - l2 + 1) * Calc(tmp, i - l2 + 1);
      st.insert(tmp);
    }
  }
  return ans;
}
int main() {
  int n = read(), q = read();
  if (n <= 3e2) {
    bin[0] = 1;
    for (int i = 1; i <= (MAXN << 1) - 1; i++) bin[i] = bin[i - 1] * base;
    for (int i = 1; i <= n; i++) dq.push_back(read());
    while (q--) {
      scanf("%s", s);
      if (s[0] == 'a') {
        if (s[3] == 'l') {
          addl(read());
        } else {
          addr(read());
        }
      } else {
        if (s[5] == 'l') {
          int l1 = read(), r1 = read(), l2 = read(), r2 = read();
          printf("%d\n", transl(l1, r1, l2, r2));
        } else {
          int l1 = read(), r1 = read(), l2 = read(), r2 = read();
          printf("%d\n", transr(l1, r1, l2, r2));
        }
      }
    }
  }
}
