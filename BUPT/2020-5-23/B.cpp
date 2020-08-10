#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e5 + 5;
struct Node {
  int ch[2], size, x;
}root[MAXN];
void Update(int rt) {
  if (root[rt].ch[0] > root[rt].ch[1]) swap(root[rt].ch[0], root[rt].ch[1]);
  if (root[rt].ch[0])
    Update(root[rt].ch[0]);
  if (root[rt].ch[1])
    Update(root[rt].ch[1]);
  root[rt].size = root[root[rt].ch[0]].size + root[root[rt].ch[1]].size + 1;
}
bool flag[MAXN];
void DFS_RM(int rt) {
  if (root[rt].ch[0]) DFS_RM(root[rt].ch[0]);
  if (root[rt].ch[1]) DFS_RM(root[rt].ch[1]);
  flag[rt] = 0;
}
void Del(int rt, int k) {
  if (k == root[rt].size) {
    DFS_RM(rt);
    return;
  }
  if (root[root[rt].ch[1]].size >= k) {
    // if (root[root[rt].ch[1]].size == k) {
    //   DFS_RM(root[rt].ch[1]);
    // } else {
    Del(root[rt].ch[1], k);
    // }
  } else {
    DFS_RM(root[rt].ch[1]);
    Del(root[rt].ch[0], k - root[root[rt].ch[1]].size);
  }
}
int main() {
  int n, k;
  // memset (flag, 0, sizeof (flag));
  scanf ("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) flag[i] = 1;
  int tmp, rt;
  for (int i = 1; i <= n; i++) {
    root[i].x = i;
    scanf ("%d", &tmp);
    if (tmp != -1) {
      if (root[tmp].ch[0] != 0) root[tmp].ch[1] = i;
      else root[tmp].ch[0] = i;
    } else {
      rt = i;
    }
  }
  Update(rt);
  Del(rt, n - k);
  for (int i = 1; i <= n; i++) {
    if (flag[i]) printf ("1");
    else printf ("0");
  }
}