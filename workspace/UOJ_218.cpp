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
const int MAXN = 5e5 + 5;
struct Node {
  Node *ch[2], *pre;
  int Sum, tag;
  Node() {
    ch[0] = ch[1] = pre = NULL;
    Sum = tag = -1;
  }
} * root[MAXN];
int main() {
  
}
