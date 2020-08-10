#include <bits/stdc++.h>
using namespace std;
const int MaxN = 100010, MaxM = 100010;
struct edge {
  int to, w, next;
};
edge e[MaxM << 1];
int head[MaxN], cnt;
int n;
inline void add_edge(int u, int v, int w) {
  cnt++;
  e[cnt].w = w;
  e[cnt].to = v;
  e[cnt].next = head[u];
  head[u] = cnt;
}
struct node {
  int w, sz, wsz, id;
  node(int _w, int _sz, int _wsz, int _id) {
    w = _w;
    sz = _sz;
    wsz = _wsz;
    id = _id;
  }
};
int cmp(node &n1, node &n2) {
  return (n1.sz - 2 * n1.wsz) > (n2.sz - 2 * n2.wsz);
}
int cmp2(node &n1, node &n2) {
  return n1.wsz < n2.wsz;
}
int ans = 0;
int sz[MaxN];
int wsz[MaxN];
int a[MaxN];
void init() {
  ans = 0;
  memset(head, 0, sizeof(head));
  cnt = 0;
  for (int i = 1; i <= n; i++) sz[i] = wsz[i] = 0;
}
void dfs_pre(int now, int pre, int prew) {
  int nxt, w;
  sz[now] = a[now];
  wsz[now] = prew;
  for (int i = head[now]; i; i = e[i].next) {
    nxt = e[i].to;
    w = e[i].w;
    if (nxt == pre) continue;
    dfs_pre(nxt, now, w);
    sz[now] += sz[nxt];
    wsz[now] += wsz[nxt];
  }
}
void dfs(int now, int pre, int HP, int prew) {
  int nxt, w;
  HP += a[now];
  int res = 0;
  vector<node> v;
  for (int i = head[now]; i; i = e[i].next) {
    nxt = e[i].to;
    w = e[i].w;
    if (nxt == pre) continue;
    v.push_back(node(w, sz[nxt], wsz[nxt], nxt));
  }
  int siz = v.size();
  sort(v.begin(), v.end(), cmp);
  auto t = v.begin();
  for (; t != v.end(); t++) {
    if (t->sz - 2 * t->wsz < 0) break;
  }
  sort(v.begin(), t, cmp2);
  for (int i = 0; i < siz; i++) {
    nxt = v[i].id;
    w = v[i].w;
    if (nxt == pre) continue;
    if (HP >= w) {
      dfs(nxt, now, HP - w, w);
    } else {
      ans += w - HP;
      HP = w;
      dfs(nxt, now, 0, w);
    }
    // cout<<"test:"<<HP<<" "<<sz[nxt]<<" "<<wsz[nxt]<<endl;
    HP = max(0, HP + v[i].sz - 2 * v[i].wsz);
  }
  //	for(int i=head[now];i;i=e[i].next){
  //		nxt=e[i].to;
  //		w=e[i].w;
  //		if(nxt==pre) continue;
  //		if(HP>=w){
  //			dfs(nxt,now,HP-w,w);
  //		}
  //		else{
  //			ans+=w-HP;
  //			HP=w;
  //			dfs(nxt,now,0,w);
  //		}
  //		//cout<<"test:"<<HP<<" "<<sz[nxt]<<" "<<wsz[nxt]<<endl;
  //		HP=max(0,HP+sz[nxt]-2*wsz[nxt]);
  //		//cout<<now<<" "<<nxt<<" "<<HP<<endl;
  //	}
  // cout<<now<<" "<<pre<<" "<<HP<<" "<<prew<<endl;
  // cout<<ans<<endl;
  if (pre == 0) return;
  if (HP >= prew) return;
  ans += prew - HP;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    init();
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i < n; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      add_edge(u, v, w);
      add_edge(v, u, w);
    }
    dfs_pre(1, 0, 0);
    //		for(int i=1;i<=n;i++) {
    //			cout<<"i:"<<i<<" "<<sz[i]<<" "<<wsz[i]<<endl;
    //		}
    dfs(1, 0, 0, 0);
    printf("%d\n", ans);
  }
}
