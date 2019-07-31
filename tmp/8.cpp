#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 100005
using namespace std;
int T, n, m;
struct no {
  no* ch[2];
  int size;
  no() { ch[0] = ch[1] = 0, size = 0; }
}* null = new no(), *root[N];
no* new_node() {
  no* x = new no();
  x->ch[0] = null, x->ch[1] = null;
  x->size = 0;
  return x;
}
int A[N];
void build(no* la, no* nw, int to, int l, int r) {
  //    cout<<l<<' '<<r<<' '<<to<<endl;
  nw->size = la->size + 1;
  if (l == r) return;
  int mid = (l + r) >> 1;
  if (to > mid) {
    nw->ch[0] = la->ch[0];
    nw->ch[1] = new_node();
    build(la->ch[1], nw->ch[1], to, mid + 1, r);
  } else {
    nw->ch[1] = la->ch[1];
    nw->ch[0] = new_node();
    build(la->ch[0], nw->ch[0], to, l, mid);
  }
}
int get_sum(no* la, no* nw, int l, int r, int to) {
  int mid;
  int ans = 0;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (to > mid) {
      ans += nw->ch[0]->size - la->ch[0]->size;
      nw = nw->ch[1], la = la->ch[1];
      l = mid + 1;
    } else {
      nw = nw->ch[0], la = la->ch[0];
      r = mid;
    }
    if (l == r) {
      ans += nw->size - la->size;
      break;
    }
  }
  return ans;
}
int find(no* la, no* nw, int l, int r, int to) {
  if (!(nw->size - la->size)) return 0;
  if (l == r) return nw->size - la->size;
  int mid = (l + r) >> 1;
  if (to > mid)
    return find(la->ch[1], nw->ch[1], mid + 1, r, to);
  else
    return find(la->ch[0], nw->ch[0], l, mid, to);
}
int rank_get(no* la, no* nw, int l, int r, int sum) {
  if (l == r) return r;
  int mid = (l + r) >> 1;
  if (nw->ch[0]->size - la->ch[0]->size >= sum)
    return rank_get(la->ch[0], nw->ch[0], l, mid, sum);
  else
    return rank_get(la->ch[1], nw->ch[1], mid + 1, r,
                    sum - (nw->ch[0]->size - la->ch[0]->size));
}
int Mx = 1000000;
int work(int l, int r, int p, int k) {
  if (l > r) swap(l, r);
  int aa = get_sum(root[l - 1], root[r], 1, Mx, p),
      bb = find(root[l - 1], root[r], 1, Mx, p);
  if (aa - bb == 0) return abs(p - rank_get(root[l - 1], root[r], 1, Mx, k));
  if (aa == r - l + 1)
    return abs(p - rank_get(root[l - 1], root[r], 1, Mx, (r - l + 1 - k + 1)));
  int RR, LL;  // cout<<"assdasdd"<<endl;
  RR = rank_get(root[l - 1], root[r], 1, Mx, r - l + 1);
  LL = rank_get(root[l - 1], root[r], 1, Mx, 1);
  if (k == r - l + 1) {
    return max(abs(RR - p), abs(LL - p));
  }
  if (bb) k--, aa--;
  int L, R, ll, rr;
  L = rank_get(root[l - 1], root[r], 1, Mx, aa);
  R = rank_get(root[l - 1], root[r], 1, Mx, aa + bb + 1);
  ll = aa, rr = aa + bb + 1;
  if (bb && k == 0) return 0;
  int js = 0;
  //    cout<<bb<<' '<<aa<<' '<<k<<endl;
  for (int i = 1; i < k; i++) {
    //    cout<<L<<' '<<R<<' '<<i<<endl;
    if (L == LL) {
      rr++;
      if (abs(R - p) > abs(L - p)) {
        js++;
        //    if(js==2)
        {
          L = -Mx;
          i++;
          LL = -Mx;
          if (i == k) break;
        }
      }
      R = rank_get(root[l - 1], root[r], 1, Mx, rr);

    } else if (R == RR) {
      ll--;
      if (abs(R - p) < abs(L - p)) {
        js++;
        //    if(js==2)
        {
          R = Mx;
          i++;
          RR = Mx;
          if (i == k) break;
        }
      }
      L = rank_get(root[l - 1], root[r], 1, Mx, ll);
      //    cout<<"asdasd"<<L<<endl;

    } else if (abs(L - p) > abs(R - p)) {
      rr++;
      R = rank_get(root[l - 1], root[r], 1, Mx, rr);
    } else {
      ll--;
      L = rank_get(root[l - 1], root[r], 1, Mx, ll);
    }
  }
  //    cout<<L<<' '<<R<<endl;
  return min(abs(L - p), abs(R - p));
}
int main() {
  // freopen("test.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &T);
  null->ch[0] = null->ch[1] = null;
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &A[i]);
    }
    root[0] = new_node();
    for (int i = 1; i <= n; i++) {
      root[i] = new_node();
      build(root[i - 1], root[i], A[i], 1, 1000000);
    }
    int la = 0;
    for (int i = 1; i <= m; i++) {
      //    if(i%1000==0) cout<<i<<endl;
      int l, r, k, p;
      scanf("%d%d%d%d", &l, &r, &p, &k);
      l ^= la, r ^= la, p ^= la, k ^= la;
      la = work(l, r, p, k);
      printf("%d\n", la);
    }
  }
  return 0;
}