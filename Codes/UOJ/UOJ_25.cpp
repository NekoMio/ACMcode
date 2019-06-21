#include "wall.h"
#include <algorithm>
using std::max;
using std::min;
const int INF = 0x3f3f3f3f;
struct Node {
  Node *ch[2];
  int Max, Min;
  Node() {
    ch[0] = ch[1] = nullptr;
    Max = 0;
    Min = INF;
  }
  void PushMax(int x) {
    Max = max(Max, x);
    Max = max(Max, x);  
    Min = max(Min, x);
    Min = max(Min, x);
  }
  void PushMin(int x) {
    Max = min(Max, x);
    Max = min(Max, x);  
    Min = min(Min, x);
    Min = min(Min, x);
  }
  void Pushdown() {
    if (ch[0]) {
      ch[0]->PushMax(Max);
      ch[0]->PushMin(Min);
    }
    if (ch[1]) {
      ch[1]->PushMax(Max);
      ch[1]->PushMin(Min);
    }
    Max = 0, Min = INF;
  }
}*root = nullptr;
void Build(Node *&rt, int l, int r) {
  if (rt == nullptr) rt = new Node();
  if (l == r) {
    rt->Min = rt->Max = 0;
    return;
  }
  int mid = l + r >> 1;
  Build(rt->ch[0], l, mid);
  Build(rt->ch[1], mid + 1, r);
}
void Get_Max(Node *rt, int L, int R, int l, int r, int x) {
  if (L <= l && R >= r) {
    rt->PushMax(x);
    return;
  }
  int mid = l + r >> 1;
  rt->Pushdown();
  if (L <= mid) Get_Max(rt->ch[0], L, R, l, mid, x);
  if (R > mid) Get_Max(rt->ch[1], L, R, mid + 1, r, x);
}
void Get_Min(Node *rt, int L, int R, int l, int r, int x) {
  // fprintf (stderr, "%d %d\n", l, r);
  if (L <= l && R >= r) {
    rt->PushMin(x);
    return;
  }
  rt->Pushdown();
  int mid = l + r >> 1;
  if (L <= mid) Get_Min(rt->ch[0], L, R, l, mid, x);
  if (R > mid) Get_Min(rt->ch[1], L, R, mid + 1, r, x);
}
void DFS(Node *rt, int l, int r, int *ans) {
  if (l == r) {
    ans[l] = max(rt->Max, rt->Min);
    return;
  }
  int mid = l + r >> 1;
  rt->Pushdown();
  DFS(rt->ch[0], l, mid, ans);
  DFS(rt->ch[1], mid + 1, r, ans);
} 
void buildWall(int n, int k, int op[], int left[], int right[], int height[],
               int finalHeight[]) {
  n--;
  Build(root, 0, n);
  // fprintf (stderr, "000");
  for (int t = 0; t < k; ++t) {
    // fprintf (stderr, "%d\n", t);
    if (op[t] == 1) {
      Get_Max(root, left[t], right[t], 0, n, height[t]);
    } else {
      // fprintf (stderr, "%d %d\n", left[t], right[t]);
      Get_Min(root, left[t], right[t], 0, n, height[t]);
    }
    // fprintf (stderr, "%d\n", t);
  }
  // fprintf (stderr, "start DFS\n");
  DFS(root, 0, n, finalHeight);
  return;
}