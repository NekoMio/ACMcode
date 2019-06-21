# include <stdio.h> 
# include <cstring>
# include <iostream> 
# define int long long 
const int Inf = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 2e5 + 5;  
int first[MAXN], e = 1, val[MAXN], n, to, T; 
 
 
char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f; 
}
 
struct edge {
    int u, v, next;
} a[MAXN << 1];
 
inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++; 
}
 
struct data {
    int pay, gain; 
    inline bool operator < (const data &a) const {
        return pay == a.pay ? gain > a.gain : pay < a.pay; 
    }
};
 
struct node {
    node *ls, *rs; 
    int dep; data val; 
    node() { ls = rs = NULL; dep = 0; }
    node(int gain, int pay) { ls = rs = NULL; dep = 0; val.gain = gain; val.pay = pay; }
} *root[MAXN], mempool[MAXN << 1];
 
int tot ;
 
# define d(_) ((_) ? (_) -> dep : (0))
 
inline node* newnode(int gain, int pay) {
    mempool[tot].dep = 0; mempool[tot].ls = NULL;mempool[tot].rs = NULL;
    mempool[tot].val.pay = pay; mempool[tot].val.gain = gain;
    return &mempool[tot++];
}
 
inline node* merge(node *x, node *y) {
    if (!x || !y) return x ? x : y;
    if (y -> val < x -> val) std::swap(x, y);
    x -> rs = merge(x -> rs, y);
    if (d(x -> ls) < d(x -> rs)) std::swap(x -> ls, x -> rs);
    x -> dep = d(x -> rs) + 1; 
    return x; 
}
 
inline void dfs(int u, int fa) {
//  printf("%d\n", u); 
    root[u] = NULL;
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa)
            dfs(a[i].v, u), root[u] = merge(root[u], root[a[i].v]);
    int pay = std::max(0ll, -val[u]), gain = std::max(0ll, val[u]), pay_v, gain_v;
    while (root[u]) {
        pay_v = root[u] -> val.pay, gain_v = root[u] -> val.gain;
        if (gain > pay && gain < pay_v) break; // 因为pay_u小于pay_v, 走到u后走不走到v尚不确定. 
        if (gain > pay_v) gain += gain_v - pay_v;
        else pay += pay_v - gain, gain = gain_v;  
        root[u] = merge(root[u] -> ls, root[u] -> rs);
    }
    if (gain > pay)
        root[u] = merge(root[u], newnode(gain, pay));
    else root[u] = NULL; 
}
 
inline void erase(node *&o) {
    if (!o) return ;
    erase(o -> ls);
    erase(o -> rs);
    o = NULL; 
}
 
signed main() {
//  freopen("escape1.in", "r", stdin);
    T = read();
    while (T --) {
        memset(first, 0, sizeof first);
        e = 1; 
        tot = 0; 
        n = read(), to = read();
        for (int i = 1; i <= n; ++i) val[i] = read();
 
        for (int i = 1, u, v; i < n; ++i) {
            u = read(), v = read();
            push(u, v), push(v, u);
        }
        val[n + 1] = Inf;
        push(to, n + 1);
         
        dfs(1, 0);
        long long Hp = 0;
        while (root[1]) {
//          printf("%d %d\n", root[1] -> val.pay, root[1] -> val.gain);
            if (Hp >= root[1] -> val.pay) 
                Hp += root[1] -> val.gain - root[1] -> val.pay;
            else break; 
//          printf("%d %d\n", root[1] -> ls == NULL, root[1] -> rs == NULL);
            root[1] = merge(root[1] -> ls, root[1] -> rs);
        }
        puts(Hp >= Inf ? "escaped" : "trapped");
        for (int i = 1; i <= n; ++i) erase(root[i]);
    }
    return 0; 
}