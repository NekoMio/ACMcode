Problem1000:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int MOD = 1e9 + 7;
struct Matrix
{
	long long a[1005];
	int n;
	Matrix(int x)
	{
		n = x;
		memset(a, 0, sizeof(a));
	}
	Matrix operator*(const Matrix &b)
	{
		Matrix ans(n);
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
			{
				int t = (i - k + n) % n;
				ans.a[i] = (ans.a[i] + a[k] * b.a[t]) % MOD;
			}
		}
		return ans;
	}
	Matrix operator^(const int b)
	{
		Matrix c = *this, ans(n);
		ans.a[0] = 1;
		int k = b;
		while (k)
		{
			if (k & 1)
				ans = ans * c;
			k >>= 1;
			c = c * c;
		}
		return ans;
	}
};
long long pow_mod(long long a, int b, int p)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return ans;
}
bool flag[1005];
int map[1005];
int rt;
int main()
{
	//freopen("rand.in","r",stdin);
	//freopen("rand.out","w",stdout);
	int n, m, M, a;
	scanf("%d%d%d", &n, &m, &M);
	for (int i = 1; i <= M; i++)
	{
		bool no = 0;
		memset(flag, 0, sizeof(flag));
		for (int j = 1; j <= M - 1; j++)
		{
			int now = pow_mod(i, j, M);
			if (!flag[now])
				flag[now] = 1;
			else
			{
				no = 1;
				break;
			}
		}
		if (!no)
		{
			rt = i;
			break;
		}
	}
	//printf("%d\n",rt);
	for (int i = 0; i <= M - 2; i++)
	{
		map[pow_mod(rt, i, M)] = i;
	}
	Matrix A(M - 1);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a);
		A.a[map[a]] = (A.a[map[a]] + pow_mod(n, MOD - 2, MOD)) % MOD;
	}
	A = A ^ m;
	long long ans = 0;
	for (int i = 0; i <= M - 2; i++)
	{
		ans = (ans + A.a[i] * pow_mod(rt, i, M)) % MOD;
	}
	printf("%lld\n",ans);
}
------------------------------------------------------
Problem1001:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct edge
{
	int END, next;
} v[200005];
int first[100005], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int Sum[100005], c[100005];
int a[100005];
int b[100005];
void dfs1(int rt, int fa, int Dep)
{
	Sum[rt] = a[rt];
	b[1] += Dep * a[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		dfs1(v[i].END, rt, Dep + 1);
		Sum[rt] += Sum[v[i].END];
	}
}
void Get_b(int rt, int fa)
{
	if (rt != 1)
		b[rt] = b[fa] + Sum[1] - 2 * Sum[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		Get_b(v[i].END, rt);
	}
}
int Get_Sum(int rt, int fa)
{
	if (rt != 1)
		Sum[rt] = (b[fa] - b[rt] + Sum[1]) / 2;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		Get_Sum(v[i].END, rt);
	}
}
int Get_a(int rt, int fa)
{
	a[rt] = Sum[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		Get_a(v[i].END, rt);
		a[rt] -= Sum[v[i].END];
	}
}
int Get_c(int rt, int fa)
{
	if (rt != 1)
		c[rt] = b[rt] - b[fa];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		Get_c(v[i].END, rt);
	}
}
int n;
void worka()
{
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	dfs1(1, 0, 0);
	Get_b(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ", b[i]);
	printf("\n");
}
void workb()
{
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
	}
	Get_c(1, 0);
	long long All = 0;
	for (int i = 2; i <= n; i++)
		All += c[i];
	Sum[1] = (All + 2 * b[1]) / (n - 1);
	Get_Sum(1, 0);
	Get_a(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
}
int main()
{
	//freopen("single.in","r",stdin);
	//freopen("single.out","w",stdout);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(Sum, 0, sizeof(Sum));
		memset(first, -1, sizeof(first));
		memset(c, 0, sizeof(c));
		p = 0;
		int s, e;
		scanf("%d", &n);
		for (int i = 1; i < n; i++)
		{
			scanf("%d%d", &s, &e);
			add(s, e);
			add(e, s);
		}
		int t;
		scanf("%d", &t);
		if (t)
			workb();
		else
			worka();
	}
	return 0;
}

------------------------------------------------------
Problem1002:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1000000007;
long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
long long F[100005];
long long C(int a, int b)
{
	if (b > a)
		return 0;
	return F[a] * pow_mod(F[b] * F[a - b] % MOD, MOD - 2) % MOD;
}
long long Catalan(int n)
{
	return C(2 * n, n) * pow_mod(n + 1, MOD - 2) % MOD;
}
long long f[1005];
int main()
{
	int n, type;
	scanf("%d%d", &n, &type);
	F[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		F[i] = F[i - 1] * i % MOD;
	}
	if (type == 0)
	{
		long long ans = 0;
		for (int i = 0; i <= n; i += 2)
		{
			ans = (ans + (C(n, i) * C(i, i / 2) % MOD) * C(n - i, (n - i) / 2) % MOD) % MOD;
		}
		printf("%lld\n", ans);
	}
	else if (type == 1)
	{
		printf("%lld\n", Catalan(n / 2));
	}
	else if (type == 2)
	{
		f[0] = 1;
		for (int i = 2; i <= n; i += 2)
		{
			for (int j = 2; j <= i; j += 2)
			{
				f[i] = (f[i] + f[i - j] * Catalan(j / 2 - 1) * 4 % MOD) % MOD;
			}
		}
		printf("%lld\n", f[n]);
	}
	else
	{
		long long ans = 0;
		for (int i = 0; i <= n; i += 2)
		{
			ans = (ans + (C(n, i) * Catalan(i / 2) % MOD) * Catalan((n - i) / 2) % MOD) % MOD;
		}
		printf("%lld\n", ans);
	}
	//while (1);
}
------------------------------------------------------
Problem1003:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[25][55], Max, n;
bool isnprime[100005];
int prime[20005], Idx;
void Get_Prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= Max; i++)
    {
        if (!isnprime[i])
            prime[++Idx] = i;
        for (int j = 1; j <= Idx; j++)
        {
            if (i * prime[j] > Max)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int ans = 0x3f3f3f3f;
void dfs(int x, int y)
{
    if (a[y - 1][n] == 0)
    {
        ans = x;
        return;
    }
    for (int i = 1; i <= Idx; i++)
    {
        int Sum1 = x, Sum2 = 0;
        for (int j = 1; j <= n; j++)
        {
            Sum1 += a[y - 1][j] % prime[i];
            a[y][j] = a[y - 1][j] / prime[i];
            if (a[y - 1][j] < prime[i])
                Sum2 = Sum1;
        }
        if (Sum2 >= ans)
            return;
        if (Sum1 >= ans)
            continue;
        dfs(Sum1, y + 1);
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[0][i]);
    sort(a[0] + 1, a[0] + n + 1);
    Max = a[0][n];
    if (Max == 1)
        Max = 2;
    //printf("%d\n",Max);
    Get_Prime();
    dfs(0, 1);
    printf("%d", ans);
}

------------------------------------------------------
Problem1004:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 200000;
int f[2 * N + 5][20];
int w[N + 5];
int father[2 * N + 5];
struct data
{
	int a, b;
};
vector<int> ch[2 * N + 2];
vector<data> ls[2 * N + 2];
int find(int x)
{
	if (father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}
int Dep[2 * N + 5];
void Init(int rt, int dep)
{
	Dep[rt] = dep;
	for (int i = 1; i <= 18; i++)
		f[rt][i] = f[f[rt][i - 1]][i - 1];
	for (int i = 0; i < ch[rt].size(); i++)
		Init(ch[rt][i], dep + 1);
}
int LCA(int a, int b)
{
	if (Dep[a] < Dep[b])
		swap(a, b);
	int l = Dep[a] - Dep[b];
	for (int i = 18; i >= 0; i--)
		if (l >= (1 << i))
		{
			a = f[a][i];
			l -= (1 << i);
		}
	if (a == b)
		return a;
	for (int i = 18; i >= 0; i--)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}
int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n + m + 1; i++)
		father[i] = i;
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	int a, b;
	int Id = n;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &a, &b);
		int x = find(a), y = find(b);
		father[x] = ++Id, father[y] = Id;
		f[x][0] = Id, f[y][0] = Id;
		ch[Id].push_back(x), ch[Id].push_back(y);
	}
	for (int i = 1; i <= Id; i++)
		if (!Dep[i])
			Init(find(i), 0);
	for (int i = 1; i <= k; i++)
	{
		scanf("%d%d", &a, &b);
		if (find(a) == find(b))
		{
			int lca = LCA(a, b);
			//printf("%d ", lca);
			ls[lca].push_back((data){a, b});
		}
	}
	long long ans = 0;
	for (int i = n + 1; i <= Id; i++)
	{
		for (int j = 0; j < ls[i].size(); j++)
		{
			a = min(w[ls[i][j].a], w[ls[i][j].b]);
			w[ls[i][j].a] -= a, w[ls[i][j].b] -= a;
			ans += a;
		}
	}
	printf("%lld\n", ans << 1);
}

------------------------------------------------------
Problem1005:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int map[1005][1005];
int x1,y_1,x2,y2,n,m;
struct Point
{
	int x,y;
	Point(int a=0,int b=0)
	{
		x=a,y=b;
	}
};
int dx[4] = {0,0,-1,1},
	dy[4] = {1,-1,0,0};
bool flag[1005][1005];
void bfs()
{
	memset(flag,0,sizeof(flag));
	queue<Point> Q;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(!map[i][j])
			{
				Q.push(Point(i,j));
				flag[i][j] = 1;
			}
	while(!Q.empty())
	{
		Point k = Q.front();
		Q.pop();
		flag[k.x][k.y] = 0;
		for(int i = 0; i <= 3; i++)
		{
			Point now(k.x+dx[i],k.y+dy[i]);
			if(now.x<=0||now.x>n)continue;
			if(now.y<=0||now.y>m)continue;
			if(map[now.x][now.y] > map[k.x][k.y] + 1)
			{
				map[now.x][now.y] = map[k.x][k.y] + 1;
				if(!flag[now.x][now.y])
				{
					Q.push(now);
					flag[now.x][now.y] = 1;
				}
			}
		}
	}
}
int dis[1005][1005];
bool spfa(int t)
{
	memset(flag,0,sizeof(flag));
	memset(dis,0x3f,sizeof(dis));
	queue<Point> Q;
	Q.push(Point(x1,y_1));
	if(map[x1][y_1] < t)return 0;
	flag[x1][y_1] = 1;
	dis[x1][y_1] = 0;
	while(!Q.empty())
	{
		Point k = Q.front();
		Q.pop();
		flag[k.x][k.y] = 0;
		for(int i = 0; i <= 3; i++)
		{
			Point now(k.x+dx[i],k.y+dy[i]);
			if(now.x<=0||now.x>n)continue;
			if(now.y<=0||now.y>m)continue;
			if(map[now.x][now.y]<t)continue;
			if(dis[now.x][now.y] > dis[k.x][k.y] + 1)
			{
				dis[now.x][now.y] = dis[k.x][k.y] + 1;
				if(!flag[now.x][now.y])
				{
					Q.push(now);
					flag[now.x][now.y] = 1;
				}
			}
		}
	}
	return dis[x2][y2] != 0x3f3f3f3f;
}
int main()
{
	//freopen("1.in","r",stdin);
	int e;
	memset(map,0x3f,sizeof(map));
	scanf("%d%d%d",&e,&n,&m);
	scanf("%d%d%d%d",&x1,&y_1,&x2,&y2);
	x1++,x2++,y_1++,y2++;
	int a,b;
	for(int i = 1; i <= e; i++)
	{
		scanf("%d%d",&a,&b);
		map[a+1][b+1] = 0;
	}
	bfs();
	int l = 0,r = 2005;
	int len = 0,ans = 0;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(spfa(mid))
		{
			l = mid + 1;
			len = mid;
			ans = dis[x2][y2];
		}
		else
			r = mid;
	}
	printf("%d %d\n",len,ans);
}
------------------------------------------------------
Problem1006:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MaxN = (1 << 20) + 1;
int N;
double P[MaxN], f[MaxN];
double a[25];
int Get_Num(int n)
{
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j < n; j++)
            if ((1 << j) & i)
            {
                P[i] += a[j + 1];
            }
    }
}
int main()
{
    int n, b;
    scanf("%d", &n);
    long long ans1 = 0;
    double all = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%d", &a[i], &b);
        ans1 += b;
        all += a[i];
    }
    all = 1. - all;
    printf("%lld\n", ans1);
    N = (1 << n) - 1;
    Get_Num(n);
    for (int i = 0; i <= N; i++)
        P[i] += all;
    f[N] = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (!((1 << j) & i))
            {
                f[i] += f[i | (1 << j)] * a[j + 1];
            }
        }
        f[i] = (f[i] + 1)/(1 - P[i]);
    }
    printf("%.3lf\n", f[0]);
    //while (1);
}

------------------------------------------------------
Problem1007:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;
struct edge
{
    int END, next, v;
} E[100005], v[100005];
int Head[50005], q, first[50005], p;
void add(int a, int b, int c, int op)
{
    if (op == 1)
    {
        E[q].END = b;
        E[q].next = Head[a];
        E[q].v = c;
        Head[a] = q++;
    }
    else
    {
        v[p].END = b;
        v[p].next = first[a];
        v[p].v = c;
        first[a] = p++;
    }
}
int dfn[50005], low[50005], Index, T, belong[50005];
stack<int> st;
bool instack[50005];
void Tarjan(int rt)
{
    dfn[rt] = low[rt] = ++Index;
    st.push(rt);
    instack[rt] = 1;
    for (int i = Head[rt]; i != -1; i = E[i].next)
    {
        if (!dfn[E[i].END])
        {
            Tarjan(E[i].END);
            low[rt] = min(low[rt], low[E[i].END]);
        }
        else if (instack[E[i].END])
            low[rt] = min(low[rt], dfn[E[i].END]);
    }
    if (dfn[rt] == low[rt])
    {
        T++;
        int a;
        do
        {
            a = st.top();
            st.pop();
            instack[a] = 0;
            belong[a] = T;
        } while (dfn[a] != low[a]);
    }
}
struct data
{
    int END, v;
    bool operator<(const data &a) const
    {
        return v > a.v;
    }
};
priority_queue<data> Q;
int dis[50005];
int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        memset(Head, -1, sizeof(Head));
        memset(first, -1, sizeof(first));
        memset(belong, 0, sizeof(belong));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(instack, 0, sizeof(instack));
        memset(dis, 0x3f, sizeof(dis));
        while (!st.empty())
            st.pop();
        q = p = Index = T = 0;
        if (n == 0 && m == 0)
            break;
        int a, b, c;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c, 1);
        }
        for (int i = 0; i < n; i++)
            if (!dfn[i])
                Tarjan(i);
        for (int i = 0; i < n; i++)
            for (int j = Head[i]; j != -1; j = E[j].next)
                if (belong[i] != belong[E[j].END])
                    add(belong[i], belong[E[j].END], E[j].v, 0);
        int S = belong[0];
        dis[S] = 0;
        Q.push((data){S, 0});
        while (!Q.empty())
        {
            data k = Q.top();
            Q.pop();
            for (int i = first[k.END]; i != -1; i = v[i].next)
                if (dis[v[i].END] > v[i].v)
                {
                    Q.push((data){v[i].END, v[i].v});
                    dis[v[i].END] = v[i].v;
                }
        }
        long long ans = 0;
        for (int i = 1; i <= T; i++)
            ans += dis[i];
        printf("%lld\n", ans);
    }
}
------------------------------------------------------
Problem1008:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long ans = 0;
int a[50005];
int Max[50005], Min[50005];
int T[500005];
void dfs(int l, int r)
{
    if (l == r)
    {
        ans++;
        return;
    }
    int mid = l + r >> 1;
    Max[mid] = Min[mid] = a[mid];
    Max[mid + 1] = Min[mid + 1] = a[mid + 1];
    for (int i = mid + 2; i <= r; i++)
    {
        Max[i] = max(Max[i - 1], a[i]);
        Min[i] = min(Min[i - 1], a[i]);
    }
    for (int i = mid - 1; i >= l; i--)
    {
        Max[i] = max(Max[i + 1], a[i]);
        Min[i] = min(Min[i + 1], a[i]);
    }
    for (int j = mid; j >= l; j--)
    {
        int i = j + (Max[j] - Min[j]);
        if (i > mid && i <= r && Max[j] > Max[i] && Min[j] < Min[i])
            ans++;
    }
    for (int i = mid + 1; i <= r; i++)
    {
        int j = i - (Max[i] - Min[i]);
        if (j <= mid && j >= l && Max[j] < Max[i] && Min[j] > Min[i])
            ans++;
    }
    int p1 = mid + 1, p2 = mid + 1;
    for (int i = mid; i >= l; i--)
    {
        while (p1 <= r && Min[p1] >= Min[i])
        {
            T[Max[p1] - p1 + mid]++;
            p1++;
        }
        while (p2 < p1 && Max[p2] <= Max[i])
        {
            T[Max[p2] - p2 + mid]--;
            p2++;
        }
        ans += T[Min[i] - i + mid];
    }
    for (int i = l; i <= r; i++)
        T[Max[i] - i + mid] = 0;
    p1 = p2 = mid;
    for (int i = mid + 1; i <= r; i++)
    {
        while (p1 >= l && Min[p1] >= Min[i])
        {
            T[Max[p1] + p1 - mid]++;
            p1--;
        }
        while (p2 > p1 && Max[p2] <= Max[i])
        {
            T[Max[p2] + p2 - mid]--;
            p2--;
        }
        ans += T[Min[i] + i - mid];
    }
    for (int i = l; i <= r; i++)
        T[Max[i] + i - mid] = 0;
    dfs(l, mid), dfs(mid + 1, r);
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int c, b;
        scanf("%d%d", &c, &b);
        a[c] = b;
    }
    dfs(1, n);
    printf("%lld", ans);
    //while (1);
}
------------------------------------------------------
Problem1009:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long extgcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long gcd = extgcd(b, a % b, x, y);
    long long tmp = x;
    x = y;
    y = tmp - a / b * y;
    return gcd;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        long long a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        if (c < 0)
            a = -a, b = -b, c = -c;
        if (a == 0)
        {
            if (b == 0)
            {
                if (c == 0)
                    printf("ZenMeZheMeDuo\n");
                else
                    printf("0\n");
                continue;
            }
            else
            {
                if (c % b == 0 && c / b > 0)
                    printf("ZenMeZheMeDuo\n");
                else
                    printf("0\n");
                continue;
            }
        }
        if (b == 0)
        {
            if (c % a == 0 && c / a > 0)
                printf("ZenMeZheMeDuo\n");
            else
                printf("0\n");
            continue;
        }
        if (c == 0)
        {
            if (a * b < 0)
            {
                printf("ZenMeZheMeDuo\n");
                continue;
            }
            else
            {
                printf("0\n");
                continue;
            }
        }
        if (a < 0 && b < 0)
        {
            printf("0\n");
            continue;
        }
        long long x, y;
        long long gcd = extgcd(abs(a), abs(b), x, y);
        //printf("%d\n", gcd);
        if (c % gcd != 0)
        {
            printf("0\n");
            continue;
        }
        if (a * b < 0)
        {
            printf("ZenMeZheMeDuo\n");
            continue;
        }
        long long t1 = b / gcd;
        x = x * c / gcd;
        y = y * c / gcd;
        long long x1 = (x % t1 + t1) % t1;
        if (x1 == 0)
            x1 += t1;
        //printf("x1 := %d\n", x1);
        long long t2 = a / gcd;
        long long y2 = (y % t2 + t2) % t2;
        //printf("y := %d\n", y);
        if (y2 == 0)
            y2 += t2;
        //printf("y2 := %d\n", y2);
        long long x2 = (c - y2 * b) / a;
        //printf("x2 := %d\n", x2);
        long long ans = (x2 - x1) / t1 + 1;
        if (ans < 0)
            printf("0\n");
        else if (ans > 65535)
            printf("ZenMeZheMeDuo\n");
        else
            printf("%lld\n", ans);
        //printf("\n");
    }
    //while (1);
}
------------------------------------------------------
Problem1010:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
struct edge
{
    int END, next;
    long long v;
} v[4005];
int first[2005], p, m, n;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
long long f[2005][2005];
int size[2005];
long long tmp[2005];
void DP(int rt, int fa)
{
    size[rt] = 1;
    f[rt][0] = f[rt][1] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        DP(v[i].END, rt);
        for (int j = 0; j <= size[rt]; j++)
            tmp[j] = f[rt][j];
        for (int j = min(size[rt], m); j >= 0; j--)
        {
            for (int k = 0; k <= size[v[i].END] && k + j <= m; k++)
            {
                long long add = ((size[v[i].END] - k) * (n - m - size[v[i].END] + k) + k * (m - k)) * v[i].v + f[v[i].END][k];
                f[rt][j + k] = max(f[rt][j + k], tmp[j] + add);
            }
        }
        size[rt] += size[v[i].END];
    }
}
int main()
{
    // freopen("haoi2015_t1.in", "r", stdin);
    // freopen("haoi2015_t1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    memset(first, -1, sizeof(first));
    memset(f, 0xF0, sizeof(f));
    int a, b, c;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    DP(1, 0);
    printf("%lld", f[1][m]);
}
------------------------------------------------------
Problem1011:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
long long ans;
vector<pair<int,int> > v[2];
void add(int x,int y)
{
	v[0].push_back(pair<int,int>(x - y, x));
	v[1].push_back(pair<int,int>(x + y, x));
}
bool mark;
void move(int &x, int &y, int &dx, int &dy)
{
	int op = (dx != dy);
	pair<int, int> now = pair<int, int>((op ? x + y : x - y), x);
	vector<pair<int, int> >::iterator it = upper_bound(v[op].begin(), v[op].end(), now);
	while (it->first != now.first)
		it--;
	if (dx < 0)
		while (it->second >= x)
			it--;
	ans += abs(x - (it->second)) - 1;
	x = it->second;
	y = op ? (it->first - x):(x - it->first);
	bool flagA = binary_search(v[0].begin(),v[0].end(),pair<int,int>(x - y - dx, x - dx));
	bool flagB = binary_search(v[0].begin(),v[0].end(),pair<int,int>(x - y + dy, x));
	if(flagA == flagB)
	{
		mark = 1;
		dx = -dx;
		dy = -dy;
	}
	else
 	{
 		if(flagA)
 			x -= dx, dy = -dy;
 		else if(flagB)
 			y -= dy, dx = -dx;
	}
}
int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++)
		add(0, i), add(n + 1, i);
	for (int i = 0; i <= n + 1; ++i)
		add(i, 0), add(i, m + 1);
	int a, b;
	for (int i = 0; i < k; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
	}
	int x, y, dx, dy;
	scanf("%d%d", &x, &y);
	char s[5];
	scanf("%s",s);
	dx = (s[0] == 'N' ? -1 : 1);
	dy = (s[1] == 'W' ? -1 : 1);
	sort(v[0].begin(), v[0].end());
	sort(v[1].begin(), v[1].end());
	move(x, y, dx, dy);
	int sx = x, sy = y, sdx = dx, sdy = dy;
	ans = 0;
	while (1)
	{
		move(x, y, dx, dy);
		if(x == sx && y == sy && sdx == dx && sdy == dy)
			break;
	}
	printf("%lld\n", mark?(ans>>1):ans);
}
------------------------------------------------------
Problem1012:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
	int END, next, Id;
}v[200005];
int first[100005], p;
int size[100005], n, m;
void add(int a, int b, int id)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].Id = id;
	first[a] = p++;
}
bool vis[100005], flag[100005], mark[100005];
int num = 0;
void dfs(int x)
{
	vis[x] = 1;
	for (int i = first[x]; i != -1; i = v[i].next)
	{
		mark[v[i].Id] = 1;
		if(!vis[v[i].END])
			dfs(v[i].END);
	}
}
bool IsOK()
{
	for (int i = 1; i <= n; i++)
		if(flag[i])
		{
			dfs(i);
			break;
		}
	for (int i = 0; i < p; i++)
		if (!mark[v[i].Id])
			return 0;
	return 1;
}
int self;
int main()
{
	memset(first, -1, sizeof(first));
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &a, &b);
		flag[a] = flag[b] = 1;
		add(a, b, i);
		if(a != b)
		{
			size[a]++;
			add(b, a, i);
			size[b]++;
		}
		else
			self++;
	}
	if (!IsOK())
	{
		printf("0\n");
		return 0;
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans += ((long long)size[i] * (size[i] - 1) / 2);
	ans += ((long long)self * (m - self));
	ans += ((long long)self * (self - 1) / 2);
	printf("%lld\n",ans);
}
------------------------------------------------------
Problem1013:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
int a[105];
long long Sum[105];
int main()
{
    int n;
    long long k;
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Sum[i] = Sum[i - 1] + a[i];
    }
    k += Sum[n];
    long long ans = 0;
    for (long long i = 1, pos; i <= k / 2 + 1; i = pos + 1)
    {
        pos = k / (k / i);
        long long now = 0;
        for (int j = 1; j <= n; j++)
            now += (a[j] / pos) + (a[j] % pos > 0);
        if (now <= k / pos)
            ans = pos;
    }
    printf("%lld", ans);
}
------------------------------------------------------
Problem1014:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long f[305][305];
int MOD;
int main()
{
	int k;
	scanf("%d%d", &k, &MOD);
	f[1][0] = f[1][1] = 1 % MOD;
	for (int i = 1; i < k; i++)
	{
		for (int l = 0; l <= k - i + 1; l++)
			for (int r = 0; r <= k - i + 1; r++)
			{
				long long num = f[i][l] * f[i][r] % MOD;
				if (r + l <= k - i)
				{
					f[i + 1][r + l] = (f[i + 1][r + l] + num) % MOD;
					f[i + 1][r + l] = (f[i + 1][r + l] + 2 * num * (l + r) % MOD) % MOD;
				}
				if (r + l + 1 <= k - i)
					f[i + 1][r + l + 1] = (f[i + 1][r + l + 1] + num) % MOD;
				if (r + l - 1 <= k - i)
				{
					f[i + 1][r + l - 1] = (f[i + 1][r + l - 1] + 2 * num * l * r % MOD) % MOD;
					f[i + 1][r + l - 1] = (f[i + 1][r + l - 1] + num * (l * (l - 1) + r * (r - 1)) % MOD) % MOD;
				}
			}
	}
	printf("%lld", f[k][1]);
}

------------------------------------------------------
Problem1015:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct data
{
	int a, b;
	bool operator < (const data &c) const 
	{
		return b - a == c.b - c.a ? a < c.a : b - a > c.b - c.a;
	}
}v[100005];
long long f[100005];
int a[15];
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d%d", &v[i].a, &v[i].b);
		}
		sort(v + 1, v + n + 1);
		long long ans = 0, y = 0;
		for (int i = 1; i <= n; i++)
			if(y >= v[i].b)
				y -= v[i].a;
			else
				ans += v[i].b - y, y = v[i].b - v[i].a;
		printf("%lld\n", ans);
	}
}
------------------------------------------------------
Problem1016:
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;
int MOD = 1e9 + 7;
long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while(b)
	{
		if(b & 1)
			ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
long long f[1000005];
int main()
{
	int T;
	scanf("%d", &T);
	long long ans = 1;
	f[1] = 2;
	for (int i = 2; i <= 1000000; i++)
	{
		ans = (ans * (4 * i - 2) % MOD) * pow_mod(i + 1, MOD - 2) % MOD;
		f[i] = ans * (i + 1) % MOD;
	}
	while(T--)
	{
		int n;
		scanf("%d", &n);
		printf("%lld\n", f[n]);
	}
}
------------------------------------------------------
Problem1016:
#include <cstdio>
#include <cstring>
using namespace std;
int MOD = 1e9 + 7;
long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while(b)
	{
		if(b & 1)
			ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
long long f[1000005];
int main()
{
	int T;
	scanf("%d", &T);
	long long ans = 1;
	f[1] = 2;
	for (int i = 2; i <= 1000000; i++)
	{
		ans = (ans * (4 * i - 2) % MOD) * pow_mod(i + 1, MOD - 2) % MOD;
		f[i] = ans * (i + 1) % MOD;
	}
	while(T--)
	{
		int n;
		scanf("%d", &n);
		printf("%lld\n", f[n]);
	}
}
------------------------------------------------------
Problem1017:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std; 
#define ULL unsigned long long
ULL Hash1[5005],Hash2[5005];
ULL base = 31;
char s[5005];
ULL B[5005];
bool OK(int l, int r)
{
	return Hash1[r] - Hash1[l] * B[r - l] == Hash2[l] - Hash2[r] * B[r - l];
}
int ans[5005][5005];
int main()
{
	scanf("%s",s);
	int n = strlen(s);
	B[0] = 1;
	for (int i = 1; i <= n; i++)
		B[i] = B[i - 1] * base;
	for (int i = 0; i <= n; i++)
		Hash1[i] = Hash1[i - 1] * base + s[i];
	for (int i = n ; i >= 0; i--)
		Hash2[i] = Hash2[i + 1] * base + s[i];
	for (int l = 0; l < n; l++)
		for (int i = 0; i < n - l + 1; i++)
			ans[i][i + l - 1] = ans[i + 1][i + l - 1] + ans[i][i + l - 2] - ans[i + 1][i + l - 2] + OK(i, i + l - 1);
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		printf("%d\n", ans[l][r]);
	}
}
------------------------------------------------------
Problem1018:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
	int END, next;
}v[2000005];
int first[1000005], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int size[1000005], cnt[1000005];
void dfs(int x, int fa)
{
	size[x] = 1;
	for (int i = first[x]; i != -1; i = v[i].next)
	{
		if(v[i].END == fa)continue;
		dfs(v[i].END, x);
		size[x] += size[v[i].END];
	}
	cnt[size[x]]++;
}
int n;
bool Judge(int x)
{
	int ans = 0;
	for (int i = 1; i * x <= n; i++)
	{
		ans += cnt[i * x];
	}
	if(ans == n / x)
		return 1;
	else
		return 0;
}
int main()
{
	memset(first, -1, sizeof(first));
	int a, b;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if(n % i)
			continue;
		ans += Judge(i);
	}
	printf("%d\n", ans);
}
------------------------------------------------------
Problem1019:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int Sum[100005];
int a[100005], n, m;
int Bound(int l, int r, int x)
{
	int ans = 0;
	while(l < r)
	{
		int mid = l + r >> 1;
		if(Sum[mid] <= x)
			ans = mid, l = mid + 1;
		else
			r = mid;
	}
	return ans;
}
bool Judge(int mid)
{
	for (int i = 1; Sum[i] < mid; i++)
	{
		int t = m;
		int now = i;
		while(t--)
		{
			now = Bound(1, 2 * n, Sum[now] + mid);
			if(now - i >= n)
				return 1;
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	int l = 0, r = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		r += a[i];
	}
	for (int i = n + 1; i <= n + n; i++)
		a[i] = a[i - n];
	for (int i = 1; i <= 2 * n; i++)
		Sum[i] = Sum[i - 1] + a[i];
	int ans = 0;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if(Judge(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else
			l = mid + 1;
	}
	printf("%d", ans);
}
------------------------------------------------------
Problem1020:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int dx[8] = {1,1,-1,-1,2,2,-2,-2},
	dy[8] = {2,-2,2,-2,1,-1,1,-1};
int map[55][55], n, m;
#define ID(_ , __) ((_) * 51 + (__))
vector<int> v[55 * 55];
bool Check(int x, int y, int i)
{
	if(x + dx[i] > n || x + dx[i] < 1 || y + dy[i] > m || y + dy[i] < 1)
		return 0;
	if(map[x + dx[i]][y + dy[i]] == 2)
		return 0;
	return 1;
}
void ADD(int sx, int sy, int x, int y)
{
	v[ID(sx,sy)].push_back(ID(x,y));
}
void ADD(int a, int b)
{
	v[a].push_back(b);
}
bool flag[55][55], flag1[55][55], Add[55 * 55][55 * 55];
int tmp[55 * 55], tot;
void DFS(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		if(!Check(x, y, i))
			continue;
		int nx = x + dx[i], ny = y + dy[i];
		if (map[nx][ny] != 1 && !flag1[nx][ny])
		{
			flag1[nx][ny] = 1;
			tmp[++tot] = ID(nx, ny);
		}
		if (map[nx][ny] == 1 && !flag[nx][ny])
		{
			flag[nx][ny] = 1;
			DFS(nx, ny);
		}
	}
}
int Sx,Sy,Ex,Ey;
bool vis[55 * 55];
int dis[55 * 55];
int ans[55 * 55];
void BFS()
{
	queue<int> Q;
	Q.push(ID(Sx, Sy));
	vis[ID(Sx,Sy)] = 1;
	dis[ID(Sx,Sy)] = 0;
	ans[ID(Sx,Sy)] = 1;
	while(!Q.empty())
	{
		int k = Q.front();
		Q.pop();
		//vis[k] = 0;
		if(k == ID(Ex, Ey))
			continue;
		for (int i = 0; i < v[k].size(); i++)
		{
			if(dis[v[k][i]] > dis[k] + 1)
			{
				dis[v[k][i]] = dis[k] + 1;
				ans[v[k][i]] = ans[k];
				if(!vis[v[k][i]])
				{
					Q.push(v[k][i]);
					vis[v[k][i]] = 1;
				}
			}
			else if(dis[v[k][i]] == dis[k] + 1)
			{
				ans[v[k][i]] += ans[k];
				if(!vis[v[k][i]])
				{
					Q.push(v[k][i]);
					vis[v[k][i]] = 1;
				}
			}
		}
	}

}
int main()
{
	scanf("%d%d", &n, &m);
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &map[i][j]);
			if(map[i][j] == 3)
				Sx = i, Sy = j;
			if(map[i][j] == 4)
				Ex = i, Ey = j;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if(map[i][j] != 2 && map[i][j] != 1)
				for (int k = 0; k < 8; k++)
					if(Check(i, j, k) && map[i + dx[k]][j + dy[k]] != 1)
						ADD(i, j, i + dx[k], j + dy[k]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if(map[i][j] == 1 && !flag[i][j])
			{
				tot = 0;
				memset(flag1, 0, sizeof(flag1));
				flag[i][j] = 1;
				DFS(i, j);
				for (int k = 1; k <= tot; k++)
					for (int l = k + 1; l <= tot; l++)
						if(!Add[tmp[k]][tmp[l]])
						{
							Add[tmp[k]][tmp[l]] = Add[tmp[l]][tmp[k]] = 1;
							ADD(tmp[k], tmp[l]);
							ADD(tmp[l], tmp[k]);
						}

			}
		}
	BFS();
	if(dis[ID(Ex, Ey)] == 0x3f3f3f3f)
		return printf("-1\n"),0;
	printf("%d\n%d\n",dis[ID(Ex,Ey)] - 1, ans[ID(Ex,Ey)]);
}
------------------------------------------------------
Problem1021:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int cnt, a[40005];
bool flag[40005];
int f[40005];
int main()
{
	memset(f, 0x3f, sizeof(f));
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	f[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		cnt = 0;
		memset(flag, 0, sizeof(flag));
		for (int j = i; j >= 1; j--)
		{
			if(!flag[a[j]])
			{
				cnt++;
				flag[a[j]] = 1;
			}
			if(f[i] > f[j - 1] + cnt * cnt)
				f[i] = f[j - 1] + cnt * cnt;
			if(cnt * cnt > i) break;
		}
	}
	printf("%d\n",f[n]);
}
------------------------------------------------------
Problem1021:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int a[40005];
int pre[40005], pos[40005], cnt[40005];
int f[40005];
int main()
{
	memset(f,0x3f,sizeof(f));
	int n,k;
	scanf("%d%d",&n,&k);
	int m = sqrt(n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	f[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			if(pre[a[i]] <= pos[j])
				cnt[j]++;
		pre[a[i]] = i;
		for (int j = 1; j <= m; j++)
			if(cnt[j] > j)
			{
				pos[j]++;
				while(pre[a[pos[j]]] > pos[j]) pos[j]++;
				cnt[j]--;
			}
		for (int j = 1; j <= m; j++)
			f[i] = min(f[i], f[pos[j]] + j * j);
	}
	printf("%d", f[n]);
}
------------------------------------------------------
Problem1022:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Point
{
	int x,y;
	bool operator < (const Point &a)const 
	{
		return x == a.x ? y < a.y : x < a.x;
	}
}a[20005];
int n;
struct limit
{
	int x1, y1, x2, y2;
}v[5];
bool dfs(int dep, int mid)
{
	int X1 = 0x3f3f3f3f, X2 = -0x3f3f3f3f, Y1 = 0x3f3f3f3f, Y2 = -0x3f3f3f3f;
	for (int i = 1; i <= n; i++)
	{
		bool flag = 0;
		for (int j = 3; j > dep; j--)
			if(a[i].x <= v[j].x2 && a[i].x >= v[j].x1 && a[i].y <= v[j].y2 && a[i].y >= v[j].y1)
				flag = 1;
		if(!flag)
		{
			X1 = min(X1, a[i].x);
			X2 = max(X2, a[i].x);
			Y1 = min(Y1, a[i].y);
			Y2 = max(Y2, a[i].y);
		}
	}
	if(X1 == 0x3f3f3f3f) return 1;
	if(dep == 1)
	{
		if(X2 - X1  <= mid && Y2 - Y1  <= mid)
			return 1;
		else
			return 0;
	}
	bool ans = 0;
	v[dep].x1 = X1;
	v[dep].x2 = X1 + mid ;
	v[dep].y1 = Y1;
	v[dep].y2 = Y1 + mid ;
	ans |= dfs(dep - 1, mid);
	v[dep].x1 = X1;
	v[dep].x2 = X1 + mid ;
	v[dep].y2 = Y2;
	v[dep].y1 = Y2 - mid ;
	ans |= dfs(dep - 1, mid);
	v[dep].x2 = X2;
	v[dep].x1 = X2 - mid ;
	v[dep].y2 = Y2;
	v[dep].y1 = Y2 - mid ;
	ans |= dfs(dep - 1, mid);
	v[dep].x2 = X2;
	v[dep].x1 = X2 - mid ;
	v[dep].y1 = Y1;
	v[dep].y2 = Y1 + mid ;
	ans |= dfs(dep - 1, mid);
	return ans;
}
bool Judge(int x)
{
	return dfs(3, x);
}
int main()
{
	//freopen("cover1.in","r",stdin);
	//freopen("cover.out","w",stdout);
	scanf("%d",&n);
	int l, r = -0x3f3f3f3f, M = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i].x,&a[i].y);
		r = max(r, max(a[i].x, a[i].y));
		M = min(M, min(a[i].x, a[i].y));
	}
	l = 0, r = r - M + 10;
	int ans = 0;
	while(l <= r)
	{
		int mid = l + r >> 1;
		if(Judge(mid))
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	//printf("%d",Judge(175));
	printf("%d\n", ans);
}
------------------------------------------------------
Problem1023:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long I[100005], I2[100005];
struct data
{
	long long l, r;
	long long Sum, Sumi, Sumi2;
	long long lazy;
}Tree[100005 << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void PushUp(int rt)
{
	Tree[rt].Sum = Tree[rt << 1].Sum + Tree[rt << 1 | 1].Sum;
	Tree[rt].Sumi = Tree[rt << 1].Sumi + Tree[rt << 1 | 1].Sumi;
	Tree[rt].Sumi2 = Tree[rt << 1].Sumi2 + Tree[rt << 1 | 1].Sumi2;
}
void buildtree(int l, int r, int rt)
{
	Tree[rt].l = l, Tree[rt].r = r;
	if(l == r)
		return;
	int m = l + r >> 1;
	buildtree(lch);
	buildtree(rch);
}
void PushDown(int rt)
{
	if(Tree[rt].lazy)
	{
		Tree[rt<<1].lazy += Tree[rt].lazy;
		Tree[rt<<1|1].lazy += Tree[rt].lazy;
		Tree[rt<<1].Sum += (Tree[rt<<1].r - Tree[rt<<1].l + 1) * Tree[rt].lazy;
		Tree[rt<<1].Sumi += (I[Tree[rt<<1].r] - I[Tree[rt<<1].l - 1]) * Tree[rt].lazy;
		Tree[rt<<1].Sumi2 += (I2[Tree[rt<<1].r] - I2[Tree[rt<<1].l - 1]) * Tree[rt].lazy;
		Tree[rt<<1|1].Sum += (Tree[rt<<1|1].r - Tree[rt<<1|1].l + 1) * Tree[rt].lazy;
		Tree[rt<<1|1].Sumi += (I[Tree[rt<<1|1].r] - I[Tree[rt<<1|1].l - 1]) * Tree[rt].lazy;
		Tree[rt<<1|1].Sumi2 += (I2[Tree[rt<<1|1].r] - I2[Tree[rt<<1|1].l - 1]) * Tree[rt].lazy;
		Tree[rt].lazy = 0;
	}
}
void Update(int L, int R, int c, int rt)
{
	int l = Tree[rt].l, r = Tree[rt].r;
	if(L <= l && R >= r)
	{
		Tree[rt].lazy += c;
		Tree[rt].Sum += (r - l + 1) * c;
		Tree[rt].Sumi += (I[r] - I[l - 1]) * c;
		Tree[rt].Sumi2 += (I2[r] - I2[l - 1]) * c;
		return;
	}
	int m = l + r >> 1;
	PushDown(rt);
	if(L <= m) Update(L,R,c,rt<<1);
	if(R > m) Update(L,R,c,rt<<1|1);
	PushUp(rt);
}
data Query(int L, int R, int rt)
{
	int l = Tree[rt].l, r = Tree[rt].r;
	if(L <= l && R >= r)
	{
		return Tree[rt];
	}
	int m = l + r >> 1;
	PushDown(rt);
	data ans;
	if(R <= m) return Query(L, R, rt<<1);
	if(L > m) return Query(L, R, rt<<1|1); 
	data X = Query(L,R,rt<<1);
	data Y = Query(L,R,rt<<1|1);
	ans.Sum = X.Sum + Y.Sum;
	ans.Sumi = X.Sumi + Y.Sumi;
	ans.Sumi2 = X.Sumi2 + Y.Sumi2;
	return ans;
}
long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a % b);
}
int main()
{
	int n, m, l, r, d;
	char s[10];
	for (int i = 1; i <= 100000; i++)
		I[i] = I[i - 1] + i, I2[i] = I2[i - 1] + (long long)i * i;
	scanf("%d%d", &n, &m);
	buildtree(1, n - 1, 1);
	for (int i = 1; i <= m; i++)
	{
		scanf("%s",s);
		if(s[0] == 'C')
		{
			scanf("%d%d%d", &l, &r, &d);
			r--;
			Update(l,r,d,1);
		}
		else
		{
			long long Sum = 0;
			scanf("%d%d", &l, &r);
			r--;
			data A = Query(l, r, 1);
			Sum = -A.Sum * (r + 1) * (l - 1) + (l + r) * A.Sumi - A.Sumi2;
			long long S = ((long long)(r - l + 2)) * (r - l + 1) / 2;
			long long GCD = gcd(Sum, S);
			printf("%lld/%lld\n", Sum/GCD, S/GCD);
		}
	}
}
------------------------------------------------------
Problem1024:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[2005][2005];
int n, m;
bool Judge(int mid)
{
	for (int i = mid; i <= n; i++)
	{
		for (int j = mid; j <= m; j++)
		{
			if(a[i][j] - a[i][j - mid] - a[i - mid][j] + a[i - mid][j - mid] == mid * mid)
				return 1;
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d",&a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] += (a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1]);
	int l = 0, r = min(n, m) + 1;
	int ans = 0;
	while(l < r)
	{
		int mid = l + r >> 1;
		if(Judge(mid))
			ans = mid, l = mid + 1;
		else
			r = mid;
	}
	printf("%d\n", ans);
}
------------------------------------------------------
Problem1026:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[1000005];
int in[1000005], block = 1000;
int read()
{
	int ans = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){ans = ans * 10 + ch - '0'; ch = getchar();}
	return ans * f;
}
struct Query
{
	int l, r, ID;
	bool operator < (const Query &a)const
	{
		return in[l] == in[a.l] ? r > a.r : in[l] < in[a.l];
	}
}Q[1000005];
int out[1000005];
int cnt[1000005];
int main()
{
	//freopen("count.in","r",stdin);
	//freopen("count.out","w",stdout);
	int n, q;
	n = read(), q = read();
	int r = n, ans = 0;
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		in[i] = (i - 1) / block + 1;
		cnt[a[i]]++;
	}
	for (int i = 1; i <= n; i++)
		if(cnt[i] == i) 
			ans++;
	for (int j = 1; j <= q; j++)
	{
		Q[j].l = read();
		Q[j].r = read();
		if(Q[j].l > Q[j].r) 
			swap(Q[j].l, Q[j].r);
		Q[j].ID = j;
	}
	sort(Q + 1, Q + q + 1);
	int l = 1;
	for (int i = 1; i <= q; i++)
	{
		while(l < Q[i].l){ cnt[a[l]]--; if(cnt[a[l]] == a[l] - 1) ans--; else if (cnt[a[l]] == a[l]) ans++; l++;}
		while(l > Q[i].l){ l--; cnt[a[l]]++; if(cnt[a[l]] == a[l]) ans++; else if (cnt[a[l]] == a[l] + 1) ans--;}
		while(r > Q[i].r){ cnt[a[r]]--; if(cnt[a[r]] == a[r] - 1) ans--; else if (cnt[a[r]] == a[r]) ans++; r--;}
		while(r < Q[i].r){ r++; cnt[a[r]]++; if(cnt[a[r]] == a[r]) ans++; else if (cnt[a[r]] == a[r] + 1) ans--;}
		out[Q[i].ID] = ans;
	}
	for (int i = 1; i <= q; i++)
		printf("%d\n", out[i]);
}

------------------------------------------------------
Problem1030:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
// #include <ctime>
using namespace std;
int Base = 10000;
struct BigNum1
{
	int c[10005];
	int len;
	BigNum1(int x = 0)
	{
		c[len = 1] = x;
	}
	const int operator [] (const int x)const
	{
		return c[x];
	}
	int& operator [] (const int x)
	{
		return c[x];
	}
	BigNum1 operator-(const BigNum1 &b) const
    {
        BigNum1 ans = *this;
        int m = max(len, b.len);
        for (int i = 1; i <= m; i++)
        {
            if (ans[i] < b[i])
                ans[i + 1] -= 1, ans[i] += Base;
            ans[i] -= b[i];
        }
        while (ans.len > 1 && ans[ans.len] == 0)
            ans.len--;
        return ans;
    }
	BigNum1 operator * (const int &b) const 
	{
		BigNum1 ans;
		BigNum1 a = *this;
		ans.len = len;
		int y = 0;
		for (int i = 1; i <= len; i++)
		{
			ans[i] = a[i] * b + y;
			y = ans[i] / Base;
			ans[i] %= Base;
		}
		while(y)
		{
			ans[++ans.len] = y % Base;
			y /= Base;
		}
		return ans;
	}
	BigNum1 operator / (const int &b) const 
	{
		BigNum1 ans;
		BigNum1 a = *this;
		ans.len = len;
		int y = 0;
		for (int i = len; i; i--)
		{
			ans[i] = (y + a[i]) / b;
			y = (y + a[i]) % b * Base;
		}
		while(!ans[ans.len] && ans.len > 1)
			ans.len--;
		return ans;
	}
	void print()
    {
    	printf("%d", c[len]);
        for (int i = len - 1; i >= 1; i--)
            printf("%04d", c[i]);
    }
};
BigNum1 C(int n, int m)
{
	BigNum1 ans(1);
	for (int i = 1; i <= m; i++) ans = ans * (n - i + 1);
	for (int i = 1; i <= m; i++) ans = ans / i;
	return ans;
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	// int a = clock();
	BigNum1 c1 = C(n + m, m) - C(n + m, m - 1);
	c1.print();
	// printf("%lf", (double)(clock() - a) / CLOCKS_PER_SEC);
}
------------------------------------------------------
Problem1031:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
	int next, END;
}v[110005];
int first[110005], p;
int du[110005], belong[110005], cnt[110005];
bool vis[110005], flag[110005];
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
void dfs(int x, int Be)
{
	vis[x] = 1;
	belong[x] = Be;
	for (int i = first[x]; i != -1; i = v[i].next)
	{
		if(!vis[v[i].END])
			dfs(v[i].END, Be);
	}
}
int Index;
int main()
{
	memset(first, -1, sizeof(first));
	int n, m;
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &a, &b);
		if (a == 0) a = ++n;
		if (b == 0) b = ++n;
		add(a, b), add(b, a);
		du[a]++, du[b]++;
	}
	for (int i = 1; i <= n; i++)
		if(du[i] && !vis[i])
			dfs(i, ++Index);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (du[i] > 2)
		{
			ans++;
			du[i] = (du[i] & 1 ? 1 : 2);
			flag[belong[i]] = 1;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if(du[i] == 1)
		{
			cnt[belong[i]]++;
			if(cnt[belong[i]] == 4)
				ans++, cnt[belong[i]] = 2;
		}
	}
	if (Index != 1)
	{
		for (int i = 1; i <= Index; i++)
			if(!flag[i] && !cnt[i])
				ans++;
		ans += Index;
	}
	else
		ans += (cnt[1] != 0);
	printf("%d", ans);
}
------------------------------------------------------
Problem1032:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int w[2][1045][15], m, n1, n2, n;
int f[1055][1055];
void dfs(int rt, int Dep, int S)
{
	memset(f[rt], 0, sizeof(f[rt]));
	if (Dep == n - 1)
	{
		for (int i = 0; i <= n - 2; i++)
			if(S & (1 << i)) f[rt][1] += w[1][rt][i];
			else f[rt][0] += w[0][rt][i];
		return;
	}
	int last = 1 << (n - Dep - 1);
	dfs(rt << 1, Dep + 1, S), dfs(rt << 1 | 1, Dep + 1, S);
	for (int i = 0; i <= last >> 1; i++)
		for (int j = 0; j <= last >> 1; j++)
			f[rt][i + j] = max(f[rt][i + j], f[rt << 1][i] + f[rt << 1 | 1][j]);
	dfs(rt << 1, Dep + 1, S | (1 << Dep)), dfs(rt << 1 | 1, Dep + 1, S | (1 << Dep));
	for (int i = 0; i <= last >> 1; i++)
		for (int j = 0; j <= last >> 1; j++)
			f[rt][i + j] = max(f[rt][i + j], f[rt << 1][i] + f[rt << 1 | 1][j]);
}
int main()
{
	scanf ("%d%d", &n, &m);
	n1 = (1 << (n - 1)) - 1, n2 = 1 << (n - 1);
	for (int i = n2; i <= 2 * n2 - 1; i++)
		for (int j = n - 2; j >= 0; j--)
			scanf("%d", &w[1][i][j]);
	for (int i = n2; i <= 2 * n2 - 1; i++)
		for (int j = n - 2; j >= 0; j--)
			scanf("%d", &w[0][i][j]);
	dfs(1, 0, 0);
	int ans = 0;
	for (int i = 0; i <= m; i++)
		ans = max(ans, f[1][i]);
	printf("%d", ans);
}
------------------------------------------------------
Problem1033:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int prime[200005], tot;
bool isnprime[1000005];
void Get_prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= 1000000; i++)
    {
        if(!isnprime[i]) 
            prime[++tot] = i;
        for (int j = 1; j <= tot; j++)
        {
            if(i * prime[j] > 1000000) break;
            isnprime[prime[j] * i] = 1;
            if(i % prime[j] == 0) 
                break;
        }
    }
}
struct Query
{
    int opt, l, r;
}Q[200005];
int a[200005];
int Index, ans[200005];
int main()
{
    Get_prime();
    int n, q, k;
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d%d", &Q[i].opt, &Q[i].l, &Q[i].r);
    }
    while (Q[q].opt & 1) q--;
    bool ok = 0; int lastans = 0;
    for (int i = 1; i <= q; i++)
    {
        if(!ok)
        {
            if(!(Q[i].opt & 1)) a[Q[i].l] = Q[i].r;
            else ok = 1;
        }
        else
        {
            if(Q[i].opt & 1)
            {
                lastans = Q[i].opt ^ 2;
                Q[i].l ^= lastans, Q[i].r ^= lastans;
                a[Q[i].l] = Q[i].r; 
            }
            else
            {
                lastans = Q[i].opt^1;ans[++Index] = lastans;
            }
        }
    }
    lastans = Q[q].opt ^ 1; Q[q].l ^= lastans, Q[q].r ^= lastans;
    sort(a + Q[q].l, a + Q[q].r + 1);
    int l = 0;
    for (int i = Q[q].l; i <= Q[q].r; i++)
        if(!isnprime[a[i]])
        {
            l++;
            if(l == k)
                ans[++Index] = a[i];
        }
    for (int i = 1; i <= Index; i++)
        printf("%d\n", ans[i]);
}
------------------------------------------------------
Problem1036:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct data
{
    int a, b, c, d;
} a[20];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d%d%d", &a[i].a, &a[i].b, &a[i].c, &a[i].d);
    int N = (1 << n) - 1;
    long long ans = 0;
    for (int i = 0; i <= N; i++)
    {
        long long LevelOI = 0;
        long long LevelWHK = 0;
        for (int j = 0; j < n; j++)
        {
            if(i & (1 << j))
            {
                LevelOI += a[j].c;
                LevelWHK -= a[j].d;
                if(LevelWHK < 0) LevelWHK = 0;
            }
            else
            {
                LevelWHK += a[j].a;
                LevelOI -= a[j].b;
                if(LevelOI < 0) LevelOI = 0;
            }
        }
        ans = max(ans, LevelOI * LevelWHK);
    }
    printf("%lld", ans);
}
------------------------------------------------------
Problem1037:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int map[2005][2005];
int H[2005][2005], S[2005][2005];
int Get_map(int x_1, int y_1, int x_2, int y_2)
{
    return map[x_2][y_2] - map[x_1 - 1][y_2] - map[x_2][y_1 - 1] + map[x_1 - 1][y_1 - 1];
}
int Get_ans(int x_1, int y_1, int x_2, int y_2)
{
    return Get_map(x_1, y_1, x_2, y_2) - (H[x_2][y_2] - H[x_2][y_1 - 1] - H[x_1][y_2] + H[x_1][y_1 - 1]) - (S[x_2][y_2] - S[x_2][y_1] - S[x_1 - 1][y_2] + S[x_1 - 1][y_1]);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("duty.in", "r", stdin);
    freopen("duty.out", "w", stdout);
#endif
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%1d", &map[i][j]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            H[i][j] = (map[i][j] && map[i - 1][j]);
            S[i][j] = (map[i][j] && map[i][j - 1]);
            // printf("%d ", H[i][j]);
        }
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //         printf("%d ", S[i][j]);
    //     printf("\n");
    // }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            map[i][j] += (map[i - 1][j] + map[i][j - 1] - map[i - 1][j - 1]);
            H[i][j] += (H[i - 1][j] + H[i][j - 1] - H[i - 1][j - 1]);
            S[i][j] += (S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1]);
        }
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //         printf("%d ", map[i][j]);
    //     printf("\n");
    // }
    // printf("\n");
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //         printf("%d ", H[i][j]);
    //     printf("\n");
    // }
    // printf("\n");
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //         printf("%d ", S[i][j]);
    //     printf("\n");
    // }
    // printf("\n");
    while (q--)
    {
        int x_1, x_2, y_1, y_2;
        scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
        printf("%d\n",Get_ans(x_1, y_1, x_2, y_2));
    }
    // while(1);
}
------------------------------------------------------
Problem1038:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define LL long long
int c[(int)1e5 + 5], n;
LL a;
#define lowbit(_) ((_) & (-_))
void add(int x)
{
    for (int i = x; i <= a + 1; i += lowbit(i))
        c[i] += 1;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}
int main()
{
    // freopen("fly.in", "r", stdin);
    // freopen("fly.in", "w", stdout);
    LL x, mod;
    scanf("%d%lld%lld%lld", &n, &x, &a, &mod);
    long long ans = 0;
    int i, s = x;
    for (i = 1; i <= n && x < mod; i++, x += a);
    int t = 0, m = 0, h = 0, cnt = 0, S = 0; x %= mod;
    for (; i <= n; i++, cnt++, x = (x + a) % mod)
    {
        if(x < a)
        {
            S = Query(x + 1);
            add(x + 1), t++, cnt = 0;
            m = S;
            if(x > s) m += (x - s) / a + 1;
        }
        else
        {
            m = S + t * cnt;
            if(x > s) m += (x - s) / a + 1;
        }
        ans += i - m - 1;
    }
    printf("%lld\n", ans);
    // while(1);
}
------------------------------------------------------
Problem1039:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
#define LL long long
map<LL, set<int> > mp;
LL Pow[1005][65];
LL f[100005][18];
LL a[100005];
LL RMQ(int l, int r)
{
    int len = r - l + 1;
    int k = 0;
    while((1 << k) <= len) k++;
    k--;
    return min(f[l][k], f[r - (1 << k) + 1][k]);
}
bool OK(int l, int r)
{
    LL Min = RMQ(l, r);
    int j = 0;
    for (j = l; j <= r; j++)
        if(a[j] != a[l])
            break;
    if(j == r + 1) return 1;
    set<LL> Q;
    int now = 1;
    for (int i = l; i <= r; i++)
    {
        if(a[i] % Min || !mp[a[i] / Min].size()) return 0;
        if(Q.count(a[i])) return 0;
        Q.insert(a[i]);
        if(a[i] != Min && now == 1) now = *mp[a[i] / Min].begin();
        if(!mp[a[i] / Min].count(now)) return 0;
    } 
    return 1;
}
int n;
bool Judge(int mid)
{
    for (int i = 1; i <= n - mid + 1; i++)
        if(OK(i, i + mid - 1)) return 1;
    return 0;
}
int main()
{
    // freopen("seq.in", "r", stdin);
    // freopen("seq.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    Pow[1][0] = Pow[1][1] = 1;
    mp[1].insert(1);
    for (int i = 2; i <= 1000; i++)
    {
        LL now = 1;
        Pow[i][0] = 1;
        mp[1].insert(i);
        for (int j = 1; j < 64; j++)
        {
            if((long double)now * i > 1e18) break;
            else
            { 
                Pow[i][j] = now = now * i;
                mp[now].insert(i);
            }
        }
    }
    for (int i = 1; i <= n; i++) f[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    int l = 1, r = 200, ans = 0;
    while (l < r)
    {
        int mid = l + r >> 1;
        if(Judge(mid)) 
            ans = mid, l = mid + 1;
        else 
            r = mid;
    }
    printf("%d\n", ans);
    // while(1);
}

------------------------------------------------------
Problem1040:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
struct edge
{
    int next, END;
}v[6005];
int first[3005], p;
bool is_not_root[3005];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
const int MOD = 1e9 + 7;
int size[3005], son[3005], n;
long long f[3005][3005], g[3005][3005], G[3005], F[3005];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if(b&1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
void dfs(int rt)
{
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
        dfs(v[i].END), size[rt]+=size[v[i].END];
    long long Inv = pow_mod(son[rt], MOD - 2);
    memset(F, 0, sizeof(F));
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        int now = v[i].END;
        for (int k = 0; k <= n; k++)
            G[k] = 1;
        for (int j = first[rt]; j != -1; j = v[j].next)
        {
            int x = v[j].END;
            for (int k = 0; k <= size[x] + 1; k++)
            {
                long long FF = G[k];
                if(k) FF -= G[k - 1];
                if(x == now) F[k] = ((f[x][k] * G[k] + g[x][k] * FF - f[x][k] * FF) % MOD + MOD) % MOD;
                else if (k) F[k] = ((f[x][k - 1] * G[k] + g[x][k - 1] * FF - f[x][k - 1] * FF) % MOD + MOD) % MOD;
            }
            G[0] = F[0], F[0] = 0;
            for (int k = 1; k <= size[x] + 1; k++)
                G[k] = (G[k - 1] + F[k]) % MOD, F[k] = 0;
        }
        for (int k = size[rt]; k > 0; k--)
            G[k] = (G[k] - G[k - 1] + MOD) % MOD;
        for (int k = 0; k <= size[rt]; k++)
            g[rt][k] = (G[k] * Inv % MOD + g[rt][k]) % MOD;
    }
    if(size[rt] == 1)
        g[rt][0] = 1;
    f[rt][0] = g[rt][0];
    for (int i = 1; i <= size[rt] + 1; i++)
        f[rt][i] = g[rt][i], g[rt][i] = (g[rt][i] + g[rt][i - 1]) % MOD;
}
int main()
{
    // freopen("tree.in", "r", stdin);
    // freopen("tree.out", "w", stdout); 
    memset(first, -1, sizeof(first));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int e;
        scanf("%d", &son[i]);
        for (int j = 1; j <= son[i]; j++)
        {
            scanf("%d", &e);
            add(i, e);
            is_not_root[e] = 1;
        }
    }
    int root = 1;
    for (int i = 1; i <= n; i++)
        if(!is_not_root[i])
            root = i;
    dfs(root);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        (ans += f[root][i] * i) %= MOD;
    printf("%lld", ans);
    getchar(), getchar();
    return 0;
}
------------------------------------------------------
Problem1041:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if(b&1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long f[2005], g[2005];
long long fn[2005];
long long C[2005][2005];
int main()
{
    // freopen("play.in", "r", stdin);
    // freopen("play.out", "w", stdout);
    int n;
    scanf("%d",&n);
    C[0][0] = 1;
    for (int i = 1; i <= 2000; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 2000; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    for (int i = 1; i <= n; i++)
    {
        f[i] = g[i] = pow_mod(2, (i - 1) * (i - 2) / 2);
        for (int j = 1; j < i; j++)
        {
            f[i] = (f[i] - (f[j] * g[i - j] % MOD) * C[i - 1][j - 1] % MOD + MOD) % MOD;
        }
    }
    printf("%lld", f[n] * C[n][2] % MOD);
}
------------------------------------------------------
Problem1042:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int Gcd(int a, int b)
{
    return b == 0 ? a : Gcd(b, a % b);
}
set<int> st;
int a[100005];
int main()
{
    int n;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i]);
    st.insert(a[1]);
    int Min_Num = a[1], Min_Less = 0;
    int ans = 1;
    for (int i = 2; i <= n; i++)
    {
        if(Gcd(abs(a[i] - Min_Num), Min_Less) == 1 || st.count(a[i]))
        {
            ans++;
            Min_Num = a[i], Min_Less = 0;
            st.clear();
            st.insert(a[i]);
            // printf("%d\n", a[i]);
        }
        else
        {
            st.insert(a[i]);
            Min_Less = Gcd(abs(a[i] - Min_Num), Min_Less);
            Min_Num = min(a[i], Min_Num);
        }
    }
    printf("%d", ans);
    // while (1);
}
------------------------------------------------------
Problem1043:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next;
}v[800005][2];
int first[800005][2], p[2];
void add (int a, int b, int op)
{
    v[p[op]][op].END = b;
    v[p[op]][op].next = first[a][op];
    first[a][op] = p[op]++;
}
int id, n, m;
int Type[800005], size[800005];
bool DFS(int rt, int S, int tp, int END)
{
    if (tp == 0)
    {
        if (rt == END) return 1;
        if (Type[rt] != tp && Type[rt] != -1 && size[rt] != 1) return 0;
    }
    else if (S != rt)
    {
        if (Type[rt] != tp && Type[rt] != -1 && size[rt] != 1) return 0;
    }
    if (rt == END) return 1;
    bool ans = 0;
    for (int i = first[rt][tp]; i != -1; i = v[i][tp].next)
    {
        ans |= DFS(v[i][tp].END, S, tp, END);
    }
    return ans;
}
int Get_Ans(int x, int y)
{
    if (x == y) return 1;
    if (x <= n && y <= n) return 0;
    if (x < y)
        return DFS(x, x, 1, y);
    else
        return DFS(x, x, 0, y);
}
int main()
{
    memset (first, -1, sizeof (first));
    scanf ("%d%d", &n, &m);
    id = n;
    for (int i = 1; i <= n; i++) Type[i] = -1;
    int op, K, a, tpye;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%d%d%d", &tpye, &op, &K);
        if (tpye == 0)
        {
            Type[++id] = op;
            size[id] = K;
            for (int j = 1; j <= K; j++)
            {
                scanf ("%d", &a);
                add(a, id, 1);
                add(id ,a, 0);
            }
        }
        else
        {
            // OP = X, K = Y;
            printf("%d\n", Get_Ans(op, K));
        }
    }
    // while (1);
}
------------------------------------------------------
Problem1044:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
int a[500005], A[500005], pos[500005];
int B[500005];
int f[500005];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q1, Q2;
signed main()
{
    int n, k;
    scanf ("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf ("%lld", &a[i]), A[i] = A[i - 1] + a[i];
    for (int i = 1; i <= n; i++)
        scanf ("%lld", &B[i]);
    for (int i = 0; i < n; i++)
    {
        int l = i + 1, r = n;
        while (l <= r)
        {
            int mid = l + r >> 1;
            if(A[mid] - A[i] > B[i + 1]) r = mid - 1;
            else pos[i] = mid, l = mid + 1;
        }
    }
    memset (f, 0x3f, sizeof (f));
    f[0] = 0;
    if(pos[0])
        Q1.push(pair<int, int>(B[1], 0));
    else
        Q2.push(pair<int, int>(0, 0));
    for (int i = 1; i <= n; i++)
    {
        while (!Q1.empty())
        {
            if (Q1.top().second < i - k) 
            {
                Q1.pop();
                continue;
            }
            if (pos[Q1.top().second] < i) 
            {
                Q2.push(pair<int, int> (f[Q1.top().second] - A[Q1.top().second], Q1.top().second));
                Q1.pop();
                continue;
            }
            f[i] = min(f[i], Q1.top().first);
            break;
        }
        while (!Q2.empty())
        {
            // printf("%d\n", Q2.size());
            if (Q2.top().second < i - k)
            {
                Q2.pop();
                continue;
            }
            f[i] = min(f[i], Q2.top().first + A[i]);
            break;
        }
        Q1.push(pair<int, int>(f[i] + B[i + 1], i));
    }
    printf("%lld\n", f[n]);
    // while(1);
}

------------------------------------------------------
Problem1045:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
long long pow_mod(long long a, long long b)
{
    if (a < 0) return 0;
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int main()
{
    long long n, m;
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lld%lld", &n, &m);
        long long ans = m % MOD;
        if(n > 1) ans = ans * ((m - 1 + MOD) % MOD) % MOD;
        if(n > 2) ans = ans * pow_mod((m - 2 + MOD) % MOD, n - 2) % MOD;
        printf ("%lld\n", ans);
    }
}
------------------------------------------------------
Problem1046:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1000005;
struct edge
{
    int next, END;
}v[N << 1];
int a[N], first[N], p;
int du[N];
double f[N], g[N];
void add(int a, int b)
{
    v[p].next = first[a];
    v[p].END = b;
    first[a] = p++;
}
void dfs(int rt, int fa)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        f[rt] += g[v[i].END] / du[rt];
        g[rt] += g[v[i].END] / (du[rt] - 1); 
    }
    f[rt] += a[rt];
    g[rt] += a[rt];
}
void DP(int rt, int fa)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        f[v[i].END] += (g[rt] - g[v[i].END] / (du[rt] - 1)) / du[v[i].END];
        g[v[i].END] += (g[rt] - g[v[i].END] / (du[rt] - 1)) / (du[v[i].END] - 1);
        DP(v[i].END, rt);
    }
}
int main()
{
    int n;
    memset(first, -1, sizeof(first));
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int s, e;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &s, &e);
        add(s, e);
        add(e, s);
        du[e]++, du[s]++;
    }
    int rt = 1;
    for (int i = 1; i <= n; i++)
        if(du[i] != 1)
        {
            rt = i;
            break;
        }
    dfs(rt, 0);
    DP(rt, 0);
    double Max = 1e15;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (f[i] < Max)
        {
            Max = f[i];
            ans = i;
        }
    printf("%d\n", ans);
}
------------------------------------------------------
Problem1047:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[500005];
int now[500005];
int t[500005], idx;
struct Node{
	int v,key,size,rev;
	Node *ch[2];
	Node(){;}
	Node(int x){
		v=x;key=rand();size=1;rev=0;
		ch[0]=ch[1]=NULL;
	}
	#define size(_) ((_)?(_)->size:(0))
	void Pushup(){
		size=1+size(ch[1])+size(ch[0]);
	}
	void reverse(){
		if(!this)return;
		swap(ch[0],ch[1]);
		rev^=1;
	}
	void Pushdown(){
		if(!this)return;
		if(rev){
			ch[0]->reverse();
			ch[1]->reverse();
			rev=0;
		}
	}
	void *operator new (size_t size);
}*root,*C,*num;
void* Node::operator new (size_t size){
	if(C==num){
		C=new Node[1<<15];
		memset(C,0,sizeof(Node)*(1<<15));
		num=C+(1<<15);
	}
	return C++;
}
typedef pair<Node*,Node*> DNode;
Node *Merge(Node *A,Node *B){
	if(!A)return B;
	if(!B)return A;
	if(A->key<B->key){
		A->Pushdown();
		A->ch[1]=Merge(A->ch[1],B);
		A->Pushup();
		return A;
	}else{
		B->Pushdown();
		B->ch[0]=Merge(A,B->ch[0]);
		B->Pushup();
		return B;
	}
}
DNode Split(Node *rt,int k){
	if(!rt)return DNode(NULL,NULL);
	DNode o;
	rt->Pushdown();
	if(size(rt->ch[0])>=k){
		o=Split(rt->ch[0],k);
		rt->ch[0]=o.second;
		rt->Pushup();
		o.second=rt;
	}else{
		o=Split(rt->ch[1],k-size(rt->ch[0])-1);
		rt->ch[1]=o.first;
		rt->Pushup();
		o.first=rt;
	}
	return o;
}
Node *kth(int k){
	DNode x=Split(root,k-1);
	DNode y=Split(x.second,1);
	Node *ans=y.first;
	root=Merge(Merge(x.first,ans),y.second);
	return ans;
}
int Rank(Node* rt,int x){
	if(!rt)return 0;
	return x<=rt->v ? Rank(rt->ch[0],x):Rank(rt->ch[1],x)+size(rt->ch[0])+1;
}
void Insert(int x){
	int k=Rank(root,x);
	DNode y=Split(root,k);
	Node *n=new Node(x);
	root=Merge(Merge(y.first,n),y.second);
}
void remove(int x){
	int k=Rank(root,x);
	DNode a=Split(root,k);
	DNode b=Split(a.second,1);
	root=Merge(a.first,b.second);
}
void dfs(Node* rt){
	if(rt){
		rt->Pushdown();
		dfs(rt->ch[0]);
		now[++idx] = rt->v;
		dfs(rt->ch[1]);
	}
}
Node *st[4000005];
Node *build(int m)
{
    //memset(st, 0, sizeof(st));
    Node *x, *last;
    int p = 0;
    for (int i = 1; i <= m; i++)
    {
        x = new Node(i);
        last = NULL;
        while (p && st[p]->key > x->key)
        {
            st[p]->Pushup();
            last = st[p];
            st[p--] = NULL;
        }
        if (p)
            st[p]->ch[1] = x;
        x->ch[0] = last;
        st[++p] = x;
    }
    while (p)
        st[p--]->Pushup();
    return st[1];
}
void Swap(int l, int r)
{
    DNode x=Split(root,l-1);
    DNode y=Split(x.second,r-l+1);
    y.first->reverse();
    root=Merge(x.first,Merge(y.first,y.second));
}
int fa[500005], a[500005];
char L[500005];
bool flag[500005];
int find(int x)
{
	if(fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
int main()
{
	int n, m;
	long long k;
    scanf("%d%d%lld", &n, &m ,&k);
    scanf("%s", s + 1);
    int c, b;
    root = build(n);
    for (int i = 1; i <= m; i++)
    {
		scanf("%d %d", &c, &b);
		if (c > b) swap(b, c);
        Swap(c, b);
	}
	dfs(root);
    for (int i = 1; i <= n; i++)
        fa[i] = i, L[i] = s[i];
    for (int i = 1; i <= n; i++)
    {
        if(find(i) != find(now[i]))
        {
            if(L[find(i)] != '?')
                L[find(now[i])] = L[find(i)];
            fa[find(i)] = find(now[i]);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if(L[find(i)] == '?' && !flag[find(i)]) 
            t[++cnt] = i, flag[find(i)] = 1;
    int pos = 0;
    k--;
    while(k)
    {
        a[++pos] = k % 26;
        k /= 26;
    }
	for (int i = cnt, j = 1; i >= 1; i--, j++) L[find(t[i])] = a[j] + 'a';
	for (int i = 1; i <= n; i++)
	{
		printf("%c", L[find(i)]);
	}
	// while(1);
}
------------------------------------------------------
Problem1047:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[500005];
int now[500005];
int t[500005], idx;
struct Node{
	int v,key,size,rev;
	Node *ch[2];
	Node(){;}
	Node(int x){
		v=x;key=rand();size=1;rev=0;
		ch[0]=ch[1]=NULL;
	}
	#define size(_) ((_)?(_)->size:(0))
	void Pushup(){
		size=1+size(ch[1])+size(ch[0]);
	}
	void reverse(){
		if(!this)return;
		swap(ch[0],ch[1]);
		rev^=1;
	}
	void Pushdown(){
		if(!this)return;
		if(rev){
			ch[0]->reverse();
			ch[1]->reverse();
			rev=0;
		}
	}
	void *operator new (size_t size);
}*root,*C,*num;
void* Node::operator new (size_t size){
	if(C==num){
		C=new Node[1<<15];
		memset(C,0,sizeof(Node)*(1<<15));
		num=C+(1<<15);
	}
	return C++;
}
typedef pair<Node*,Node*> DNode;
Node *Merge(Node *A,Node *B){
	if(!A)return B;
	if(!B)return A;
	if(A->key<B->key){
		A->Pushdown();
		A->ch[1]=Merge(A->ch[1],B);
		A->Pushup();
		return A;
	}else{
		B->Pushdown();
		B->ch[0]=Merge(A,B->ch[0]);
		B->Pushup();
		return B;
	}
}
DNode Split(Node *rt,int k){
	if(!rt)return DNode(NULL,NULL);
	DNode o;
	rt->Pushdown();
	if(size(rt->ch[0])>=k){
		o=Split(rt->ch[0],k);
		rt->ch[0]=o.second;
		rt->Pushup();
		o.second=rt;
	}else{
		o=Split(rt->ch[1],k-size(rt->ch[0])-1);
		rt->ch[1]=o.first;
		rt->Pushup();
		o.first=rt;
	}
	return o;
}
Node *kth(int k){
	DNode x=Split(root,k-1);
	DNode y=Split(x.second,1);
	Node *ans=y.first;
	root=Merge(Merge(x.first,ans),y.second);
	return ans;
}
int Rank(Node* rt,int x){
	if(!rt)return 0;
	return x<=rt->v ? Rank(rt->ch[0],x):Rank(rt->ch[1],x)+size(rt->ch[0])+1;
}
void Insert(int x){
	int k=Rank(root,x);
	DNode y=Split(root,k);
	Node *n=new Node(x);
	root=Merge(Merge(y.first,n),y.second);
}
void remove(int x){
	int k=Rank(root,x);
	DNode a=Split(root,k);
	DNode b=Split(a.second,1);
	root=Merge(a.first,b.second);
}
void dfs(Node* rt){
	if(rt){
		rt->Pushdown();
		dfs(rt->ch[0]);
		now[++idx] = rt->v;
		dfs(rt->ch[1]);
	}
}
Node *st[4000005];
Node *build(int m)
{
    //memset(st, 0, sizeof(st));
    Node *x, *last;
    int p = 0;
    for (int i = 1; i <= m; i++)
    {
        x = new Node(i);
        last = NULL;
        while (p && st[p]->key > x->key)
        {
            st[p]->Pushup();
            last = st[p];
            st[p--] = NULL;
        }
        if (p)
            st[p]->ch[1] = x;
        x->ch[0] = last;
        st[++p] = x;
    }
    while (p)
        st[p--]->Pushup();
    return st[1];
}
void Swap(int l, int r)
{
    DNode x=Split(root,l-1);
    DNode y=Split(x.second,r-l+1);
    y.first->reverse();
    root=Merge(x.first,Merge(y.first,y.second));
}
int fa[500005], a[500005];
char L[500005];
bool flag[500005];
int find(int x)
{
	if(fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
int main()
{
	int n, m;
	long long k;
    scanf("%d%d%lld", &n, &m ,&k);
    scanf("%s", s + 1);
    int c, b;
    root = build(n);
    for (int i = 1; i <= m; i++)
    {
		scanf("%d %d", &c, &b);
		if (c > b) swap(b, c);
        Swap(c, b);
	}
	dfs(root);
    for (int i = 1; i <= n; i++)
        fa[i] = i, L[i] = s[i];
    for (int i = 1; i <= n; i++)
    {
        if(find(i) != find(now[i]))
        {
            if(L[find(i)] != '?')
                L[find(now[i])] = L[find(i)];
            fa[find(i)] = find(now[i]);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if(L[find(i)] == '?' && !flag[find(i)]) 
            t[++cnt] = i, flag[find(i)] = 1;
    int pos = 0;
    k--;
    while(k)
    {
        a[++pos] = k % 26;
        k /= 26;
    }
	for (int i = cnt, j = 1; i >= 1; i--, j++) L[find(t[i])] = a[j] + 'a';
	for (int i = 1; i <= n; i++)
	{
		printf("%c", L[find(i)]);
	}
	// while(1);
}
------------------------------------------------------
Problem1051:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long a[20005], c[20005];
const long long mod = 2147483647;
int main()
{
    int n;
    int t = 0;
    while (scanf("%d", &n) != EOF)
    {
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld", a + i);
            c[i] = a[i];
        }
        sort(a + 1, a + n + 1);
        int cnt = unique(a + 1, a + n + 1) - a - 1;
        if (cnt == 1) 
        {
            printf("Case #%d: %d\n", ++t, -1);
            continue;
        }
        for (int i = cnt + 1; i <= cnt << 1; i++) a[i] = a[i - cnt];
        int ans = 0;
        a[0] = a[cnt];
        for (int i = 1; i <= n; i++)
        {
            int d = lower_bound(a + 1, a + cnt + 1, c[i]) - a;
            if(((a[d - 1] + c[i]) % mod) == a[d + 1]) ans++;
        }
        printf("Case #%d: %d\n", ++t, ans);
    }
}
------------------------------------------------------
Problem1052:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
    int n, t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        int k = 0;
        for (int i = 1; i <= n; i++)
        {
            k = (k + n - i + 1) % i;
        }
        printf("%d\n", k + 1);
    }
}
------------------------------------------------------
Problem1057:
#include <cstdio>
#include <cstring>
#include <algorithm>
// #include <ctime>
using namespace std;
int f[1010005];
int main()
{
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 10; j >= i; j--)
            f[i] = min(f[i], f[j] + j - i);
        for (int j = 1; i * j <= n + 10; j++)
            f[i * j] = min(f[i * j], f[i] + j);
        // for (int j = n + 99; j >= 1; j--)
            // f[i] = min(f[i], f[i + 1] + 1);
    }
    printf("%d\n", f[n]);
    // printf("%lf", (double)(clock() - t)/CLOCKS_PER_SEC);
    // while (1);
}
------------------------------------------------------
Problem1057:
#include <cstdio>
#include <cstring>
using namespace std;
int f[1010005];
int main()
{
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 10; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 10; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    printf("%d\n", f[n]);
}
------------------------------------------------------
Problem1057:
#include <cstdio>
#include <cstring>
using namespace std;
int f[1001005];
int main()
{
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // if (f[i] > f[i + 1] + 1) f[i] = f[i + 1] + 1;
        for (int j = i + 10; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 10; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    printf("%d\n", f[n]);
}
------------------------------------------------------
Problem1057:
#include <cstdio>
#include <cstring>
using namespace std;
int f[1001005];
int main()
{
    //freopen("666.in", "r", stdin);
    //freopen("666.out", "w", stdout);
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // if (f[i] > f[i + 1] + 1) f[i] = f[i + 1] + 1;
        for (int j = i + 5; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 5; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    printf("%d\n", f[n]);
}
------------------------------------------------------
Problem1057:
#include <cstdio>
#include <cstring>
using namespace std;
int f[1001005];
int main()
{
    //freopen("666.in", "r", stdin);
    //freopen("666.out", "w", stdout);
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // if (f[i] > f[i + 1] + 1) f[i] = f[i + 1] + 1;
        for (int j = i + 3; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 3; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    printf("%d\n", f[n]);
}
------------------------------------------------------
Problem1057:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
using namespace std;
int f[1001005];
int main()
{
    // freopen("666.in", "r", stdin);
    //freopen("666.out", "w", stdout);
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // if (f[i] > f[i + 1] + 1) f[i] = f[i + 1] + 1;
        for (int j = i + 5; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 5; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    printf("%d\n", f[n]);
}
------------------------------------------------------
Problem1057:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
using namespace std;
int f[1001005];
int main()
{
    // freopen("666.in", "r", stdin);
    //freopen("666.out", "w", stdout);
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // if (f[i] > f[i + 1] + 1) f[i] = f[i + 1] + 1;
        for (int j = i + 4; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 4; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    // for (int i = 1; i <= n; i++)
    printf("%d\n", f[n]);
}
------------------------------------------------------
Problem1057:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
using namespace std;
int f[1001005];
int main()
{
    // freopen("666.in", "r", stdin);
    //freopen("666.out", "w", stdout);
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // if (f[i] > f[i + 1] + 1) f[i] = f[i + 1] + 1;
        for (int j = i + 3; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 3; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    // for (int i = 1; i <= n; i++)
    printf("%d\n", f[n]);
}
------------------------------------------------------
Problem1057:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
using namespace std;
int f[1000105];
int main()
{
    // freopen("666.in", "r", stdin);
    //freopen("666.out", "w", stdout);
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // if (f[i] > f[i + 1] + 1) f[i] = f[i + 1] + 1;
        for (int j = i + 3; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 3; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    // for (int i = 1; i <= n; i++)
    printf("%d\n", f[n]);
}
------------------------------------------------------
Problem1057:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
using namespace std;
int f[1000006];
int main()
{
    // freopen("666.in", "r", stdin);
    //freopen("666.out", "w", stdout);
    int n;
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // if (f[i] > f[i + 1] + 1) f[i] = f[i + 1] + 1;
        for (int j = i + 4; j >= i; j--)
            if (f[i] > f[j] + j - i) f[i] = f[j] + j - i;
        for (int j = 1; i * j <= n + 4; j++)
            if (f[i * j] > f[i] + j)
                f[i * j] = f[i] + j;
    }
    // for (int i = 1; i <= n; i++)
    printf("%d\n", f[n]);
}
------------------------------------------------------
Problem1058:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 3e7 + 5;
int mu[N], prime[N / 10], cnt;
bool isnprime[N];
struct hash
{
    long long v, val;
    int next;
}v[N / 10];
int first[76545], p;
void add(int x, int a)
{
    v[p].next = first[x % 76543];
    v[p].v = x;
    v[p].val = a;
    first[x % 76543] = p++;
}
void Get_mu()
{
    mu[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > N) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 2; i <= N; i++) mu[i] += mu[i - 1]; 
}
long long Query(long long x)
{
    if (x <= N) return mu[x];
    int ans = 1;
    long long last;
    for (int i = first[x % 76543]; i != -1; i = v[i].next)
        if(v[i].v == x) return v[i].val;
    for (long long i = 2; i <= x; i = last + 1)
    {
        last = x / (x / i);
        ans -= (last -  i + 1) * Query(x / i);
    }
    add(x, ans);
    return ans;
}
long long S(long long a, long long b)
{
    return Query(b) - Query(a - 1);
}
int main()
{
    memset(first, -1, sizeof(first));
    Get_mu();
    long long ans = 0, n, last, kk;
    scanf("%lld", &n);
    kk = sqrt(n);
    for (long long i = 1; i <= kk; i = last + 1)
    {
        last = sqrt(n / (n / (i * i)));
        ans += S(i, last) * (n / (i * i));
    }
    printf("%lld", ans);
    // while(1);
}
------------------------------------------------------
Problem1058:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 4e7 + 5;
int mu[N], prime[N / 10], cnt;
bool isnprime[N];
struct hash
{
    long long v, val;
    int next;
}v[N / 10];
int first[76545], p;
void add(int x, int a)
{
    v[p].next = first[x % 76543];
    v[p].v = x;
    v[p].val = a;
    first[x % 76543] = p++;
}
void Get_mu()
{
    mu[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > N) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 2; i <= N; i++) mu[i] += mu[i - 1]; 
}
long long Query(long long x)
{
    if (x <= N) return mu[x];
    int ans = 1;
    long long last;
    for (int i = first[x % 76543]; i != -1; i = v[i].next)
        if(v[i].v == x) return v[i].val;
    for (long long i = 2; i <= x; i = last + 1)
    {
        last = x / (x / i);
        ans -= (last -  i + 1) * Query(x / i);
    }
    add(x, ans);
    return ans;
}
long long S(long long a, long long b)
{
    return Query(b) - Query(a - 1);
}
int main()
{
    memset(first, -1, sizeof(first));
    Get_mu();
    long long ans = 0, n, last, kk;
    scanf("%lld", &n);
    kk = sqrt(n);
    for (long long i = 1; i <= kk; i = last + 1)
    {
        last = sqrt(n / (n / (i * i)));
        ans += S(i, last) * (n / (i * i));
    }
    printf("%lld", ans);
    // while(1);
}
------------------------------------------------------
Problem1058:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 3e7 + 5e6 + 5;
int mu[N], prime[N / 10], cnt;
bool isnprime[N];
struct hash
{
    long long v, val;
    int next;
}v[N / 10];
int first[76545], p;
void add(int x, int a)
{
    v[p].next = first[x % 76543];
    v[p].v = x;
    v[p].val = a;
    first[x % 76543] = p++;
}
void Get_mu()
{
    mu[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > N) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 2; i <= N; i++) mu[i] += mu[i - 1]; 
}
long long Query(long long x)
{
    if (x <= N) return mu[x];
    int ans = 1;
    long long last;
    for (int i = first[x % 76543]; i != -1; i = v[i].next)
        if(v[i].v == x) return v[i].val;
    for (long long i = 2; i <= x; i = last + 1)
    {
        last = x / (x / i);
        ans -= (last -  i + 1) * Query(x / i);
    }
    add(x, ans);
    return ans;
}
long long S(long long a, long long b)
{
    return Query(b) - Query(a - 1);
}
int main()
{
    memset(first, -1, sizeof(first));
    Get_mu();
    long long ans = 0, n, last, kk;
    scanf("%lld", &n);
    kk = sqrt(n);
    for (long long i = 1; i <= kk; i = last + 1)
    {
        last = sqrt(n / (n / (i * i)));
        ans += S(i, last) * (n / (i * i));
    }
    printf("%lld", ans);
    // while(1);
}
------------------------------------------------------
Problem1058:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 3e7 - 5e6 + 5;
int mu[N], prime[N / 10], cnt;
bool isnprime[N];
struct hash
{
    long long v, val;
    int next;
}v[N / 10];
int first[76545], p;
void add(int x, int a)
{
    v[p].next = first[x % 76543];
    v[p].v = x;
    v[p].val = a;
    first[x % 76543] = p++;
}
void Get_mu()
{
    mu[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > N) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 2; i <= N; i++) mu[i] += mu[i - 1]; 
}
long long Query(long long x)
{
    if (x <= N) return mu[x];
    int ans = 1;
    long long last;
    for (int i = first[x % 76543]; i != -1; i = v[i].next)
        if(v[i].v == x) return v[i].val;
    for (long long i = 2; i <= x; i = last + 1)
    {
        last = x / (x / i);
        ans -= (last -  i + 1) * Query(x / i);
    }
    add(x, ans);
    return ans;
}
long long S(long long a, long long b)
{
    return Query(b) - Query(a - 1);
}
int main()
{
    memset(first, -1, sizeof(first));
    Get_mu();
    long long ans = 0, n, last, kk;
    scanf("%lld", &n);
    kk = sqrt(n);
    for (long long i = 1; i <= kk; i = last + 1)
    {
        last = sqrt(n / (n / (i * i)));
        ans += S(i, last) * (n / (i * i));
    }
    printf("%lld", ans);
    // while(1);
}
------------------------------------------------------
Problem1059:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2000010;
struct Query
{
    int opt, a, b;
}Q[N];
int v[N << 1];
int vl[N << 2], vr[N << 2], Max[N << 2], Map[N << 2];
int a[N], Hash[N], t, cnt;
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int Queryl(int x, int l, int r, int rt)
{
    if (x > Max[rt]) return 0;
    if (l == r) return 1;
    int m = l + r >> 1;
    if (x > Max[rt << 1 | 1])
        return Queryl(x, lch);
    else
        return vl[rt << 1] + Queryl(x, rch);
}
int Queryr(int x, int l, int r, int rt)
{
    if (x > Max[rt]) return 0;
    if (l == r) return 1;
    int m = l + r >> 1;
    if (x > Max[rt << 1])
        return Queryr(x, rch);
    else 
        return Queryr(x, lch) + vr[rt << 1 | 1];
}
void Pushup(int l, int r, int rt)
{
    Max[rt] = Max[rt << 1], Map[rt] = Map[rt << 1];
    if (Max[rt << 1 | 1] > Max[rt])
        Max[rt] = Max[rt << 1 | 1], Map[rt] = Map[rt << 1 | 1];
    int m = l + r >> 1;
    vl[rt << 1] = Queryl(Max[rt << 1 | 1], lch);
    vr[rt << 1 | 1] = Queryr(Max[rt << 1], rch);
}
void Insert(int a, int b, int l, int r, int rt)
{
    if (l == r)
        return vl[rt] = vr[rt] = 1, Max[rt] = b, Map[rt] = l, void();
    int m = l + r >> 1;
    if (a <= m)
        Insert(a, b, lch);
    else
        Insert(a, b, rch);
    Pushup(l, r, rt);
}
void Delete(int a, int l, int r, int rt)
{
    if (l == r)
        return vl[rt] = vr[rt] = 0, Max[rt] = 0, void();
    int m = l + r >> 1;
    if (a <= m)
        Delete(a, lch);
    else
        Delete(a, rch);
    Pushup(l, r, rt);
}
typedef pair<long long, int> Pair;
Pair QueryMx(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Pair(Max[rt], Map[rt]);
    int m = l + r >> 1;
    Pair Max(0, 0);
    if (L <= m)
        Max = max(Max, QueryMx(L, R, lch));
    if (R > m) 
        Max = max(Max, QueryMx(L, R, rch));
    return Max;
}
Pair QueryL(int L, int R, int x, int l, int r, int rt)
{
    if (L == l && R == r)
        return Pair(Queryl(x, L, R, rt), max(Max[rt], x));
    int m = l + r >> 1;
    if (R <= m)
        return QueryL(L, R, x, lch);
    else if (L > m)
        return QueryL(L, R, x, rch);
    else
    {
        Pair A = QueryL(m + 1, R, x, rch);
        Pair B = QueryL(L, m, A.second, lch);
        return Pair(A.first + B.first, max(A.second, B.second));
    }
}
Pair QueryR(int L, int R, int x, int l, int r, int rt)
{
    if (L == l && R == r)
        return Pair(Queryr(x, L, R, rt), max(Max[rt], x));
    int m = l + r >> 1;
    if (R <= m) 
        return QueryR(L, R, x, lch);
    else if (L > m)
        return QueryR(L, R, x, rch);
    else
    {
        Pair A = QueryR(L, m, x, lch);
        Pair B = QueryR(m + 1, R, A.second, rch);
        return Pair(A.first + B.first, max(A.second, B.second));
    }
}
int Dep(int x)
{
    int ret = 0;
    if (x > 1)
        ret += QueryL(1, x - 1, v[x], 1, cnt, 1).first;
    if (x < cnt)
        ret += QueryR(x + 1, cnt, v[x], 1, cnt, 1).first;
    return ret;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &Q[i].opt);
        if (Q[i].opt == 0)
            scanf("%d%d", &Q[i].a, &Q[i].b), Hash[++t] = Q[i].a;
        else if (Q[i].opt == 1)
            scanf("%d", &Q[i].a);
        else if (Q[i].opt == 2)
            scanf("%d%d", &Q[i].a, &Q[i].b);
    }
    sort(Hash + 1, Hash + t + 1);
    cnt = unique(Hash + 1, Hash + t + 1) - Hash - 1;
    for (int i = 1; i <= n; i++)
    {
        if (Q[i].opt == 0)
            Q[i].a = lower_bound(Hash + 1, Hash + cnt + 1, Q[i].a) - Hash;
        else if (Q[i].opt == 1)
            Q[i].a = lower_bound(Hash + 1, Hash + cnt + 1, Q[i].a) - Hash;
        else if (Q[i].opt == 2)
            Q[i].a = lower_bound(Hash + 1, Hash + cnt + 1, Q[i].a) - Hash, Q[i].b = lower_bound(Hash + 1, Hash + cnt + 1, Q[i].b) - Hash;
    }
    for (int i = 1; i <= n; i++)
    {
        if (Q[i].opt == 0)
            Insert(Q[i].a, Q[i].b, 1, cnt, 1), v[Q[i].a] = Q[i].b;
        else if (Q[i].opt == 1)
            Delete(Q[i].a, 1, cnt, 1);
        else if (Q[i].opt == 2)
        {
            if (Q[i].a > Q[i].b)
                swap(Q[i].a, Q[i].b);
            int LCA = QueryMx(Q[i].a, Q[i].b, 1, cnt, 1).second;
            printf("%d\n", Dep(Q[i].a) + Dep(Q[i].b) - 2 * Dep(LCA));
        }
    }
    // while (1);
}

/**
12
0 4 17
0 10 38
0 2 21
0 1 61
2 1 10
2 10 4
1 10
1 1
0 8 42
2 8 4
2 8 2
2 4 2
*/
------------------------------------------------------
Problem1060:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
LL MOD;
LL pow_mod(LL a, LL b)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
LL f[100005], Inv[100005];
LL C(LL n, LL m)
{
    if (n < m) return 0;
    if (m == n || m == 0) return 1;
    return ((f[n] * Inv[m]) % MOD * Inv[n - m]) % MOD;
}
LL lucas(LL n, LL m)
{
    if (n == m || m == 0) return 1;
    if (n < m) return 0;
    return lucas(n / MOD, m / MOD) * C(n % MOD, m % MOD) % MOD;
}
int main()
{
    LL n, m;
    scanf ("%lld%lld%lld", &n, &m, &MOD);
    f[0] = 1;
    for (int i = 1; i < MOD; i++)
        f[i] = f[i - 1] * i % MOD;
    Inv[MOD - 1] = pow_mod(f[MOD - 1], MOD - 2) % MOD;
    for (int i = MOD - 2; i >= 0; i--)
        Inv[i] = Inv[i + 1] * (i + 1) % MOD;
    printf ("%lld", lucas(n ,m));
}
------------------------------------------------------
Problem1061:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
struct edge
{
    int END, next;
}v[200005];
int first[100005], p;
int size[100005];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
bool notroot[100005];
void DFS(int rt)
{
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        DFS(v[i].END);
        size[rt] += size[v[i].END];
    }
}
unsigned long long base = 31;
map<unsigned long long, int> Hash;
unsigned long long Get_Hash(int m)
{
    unsigned long long ans = 0;
    for (int i = 1; i <= m; i++)
        ans = ans * base + size[i];
    return ans;
}
int main()
{
    int n, m, q, a, b;
    scanf ("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
    {
        memset(notroot, 0, sizeof (notroot[0]) * (m + 2));
        memset(first, -1, sizeof (first[0]) * (m + 2));
        memset(size, 0, sizeof (size[0]) * (m + 2));
        p = 0;
        for (int j = 1; j < m; j++)
        {
            scanf ("%d%d", &a, &b);
            add(a, b);
            notroot[b] = 1;
        }
        int root = 1;
        for (int j = 1; j <= m; j++)
            if (!notroot[j])
            { 
                root = j;
                break;  
            }
        DFS(root);
        sort(size + 1, size + m + 1);
        Hash[Get_Hash(m)]++;
    }
    while (q--)
    {
        memset(notroot, 0, sizeof (notroot[0]) * (m + 2));
        memset(first, -1, sizeof (first[0]) * (m + 2));
        memset(size, 0, sizeof (size[0]) * (m + 2));
        p = 0;
        for (int j = 1; j < m; j++)
        {
            scanf ("%d%d", &a, &b);
            add(a, b);
            notroot[b] = 1;
        }
        int root = 1;
        for (int j = 1; j <= m; j++)
            if (!notroot[j])
            { 
                root = j;
                break;  
            }
        DFS(root);
        sort(size + 1, size + m + 1);
        printf ("%d\n", Hash[Get_Hash(m)]);
    }
    // while (1);
}
------------------------------------------------------
Problem1062:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100005;
int a[N];
int Max[N << 2], Min[N << 2], lazy[N << 2], Sum[10];
void Pushup(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
}
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        Max[rt] = Min[rt] = a[l];
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
void Pushdown(int rt)
{
    if (lazy[rt])
    {
        lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
        Max[rt << 1] = Min[rt << 1] = Max[rt << 1 | 1] = Min[rt << 1 | 1] = lazy[rt];
        lazy[rt] = 0;
    }
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        Min[rt] = Max[rt] = c;
        lazy[rt] = c;
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    if (L <= m) Update(L, R, c, lch);
    if (R > m) Update(L, R, c, rch);
    Pushup(rt);
}
void Query(int L, int R, int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        Sum[Max[rt]] += min(r, R) - max(l, L) + 1;
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    if (L <= m) Query(L, R, lch);
    if (R > m) Query(L, R, rch);
    Pushup(rt);
}
int ans[N];
void Get_Ans(int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        for (int i = l; i <= r; i++)
            ans[i] = Max[rt];
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    Get_Ans(lch);
    Get_Ans(rch);
}
int main()
{
    int n, q;
    scanf ("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i]);
    buildtree(1, n, 1);
    int l, r, op;
    while (q--)
    {
        scanf ("%d%d%d", &l, &r, &op);
        memset(Sum, 0, sizeof(Sum));
        Query(l, r, 1, n, 1);
        if (op == 0)
        {
            int now = l;
            for (int i = 1; i <= 7; i++)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
        else
        {
            int now = l;
            for (int i = 7; i >= 1; i--)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
    }
    Get_Ans(1, n, 1);
    for (int i = 1; i <= n; i++)
        printf ("%d ", ans[i]);
}
------------------------------------------------------
Problem1063:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 998244353;
long long pow_mod(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long f[10000007], Inv[10000007];
long long C(long long n, long long m)
{
    if (m > n || n < 0 || m < 0) return 0;
    return (f[n] * Inv[n - m] % MOD) * Inv[m] % MOD;
}
int main()
{
    // freopen("city.in", "r", stdin);
    // freopen("city.out", "w", stdout);
    f[0] = 1;
    for (int i = 1; i <= 10000000; i++)
        f[i] = f[i - 1] * i % MOD;
    Inv[10000000] = pow_mod(f[10000000], MOD - 2);
    for (int i = 9999999; i >= 0; i--) Inv[i] = Inv[i + 1] * (i + 1) % MOD;
    int n, m, k;
    scanf ("%d%d%d", &n, &m, &k);
    if (n >= m) printf("0\n");
    else
    {
        long long ans = 0;
        for (int i = 1; i <= m; i++)
        {
            if (i & 1)
                ans = (ans + (C(n, i) * C(m - (long long)i * k - 1, n - 1) % MOD)) % MOD;
            else
                ans = (ans - (C(n, i) * C(m - (long long)i * k - 1, n - 1) % MOD) + MOD) % MOD;
        }
        printf("%lld\n", (C(m - 1, m - n) - ans + MOD) % MOD);
    }
    // while(1);
}
------------------------------------------------------
Problem1064:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
struct edge
{
    int END, next, S;
}v[1000005];
int first[1000005], p, n;
void add(int a, int b)
{
    v[p].S = a;
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int low[1000005], dfn[1000005], Index, belong[1000005], T, size[1000005], Ans;
bool flag[1000005];
stack<int> st;
int f[1000005];
void dfs(int x)
{
    if (f[x]) return;
    f[x] = size[x];
    int now = 0;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        dfs(v[i].END);
        now = max(f[v[i].END], now);
    }
    f[x] += now;
}
void Tarjan(int rt)
{
    low[rt] = dfn[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    for(int i = first[rt]; i != -1; i = v[i].next)
    {
        if(!dfn[v[i].END])
        {
            Tarjan(v[i].END);
            low[rt] = min(low[rt],low[v[i].END]);
        }
        else if(flag[v[i].END])
        {
            low[rt] = min(low[rt],dfn[v[i].END]);
        }
    }
    if(dfn[rt]==low[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            flag[v] = 0;
            belong[v] = T;
            size[T]++;
        }while(dfn[v]!=low[v]);
    }
}
// int father[1000005];
// int find(int x)
// {
//     if (father[x] != x) father[x] = find(father[x]);
//     return father[x];
// }
int main()
{
    memset (first, -1, sizeof (first));
    int n, m;
    scanf ("%d%d", &n, &m);
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%d%d", &a, &b);
        add(a, b);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
    int tot = p;
    memset(first, -1, sizeof (first));
    p = 0;
    // for (int i = 1; i <= T; i++) father[i] = i;
    for (int i = 0; i < tot; i++)
    {
        if (belong[v[i].S] != belong[v[i].END])
        {
            // father[find(belong[v[i].S])] = find(belong[v[i].END]);
            add (belong[v[i].S], belong[v[i].END]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= T; i++) 
        dfs(i), ans = max(f[i], ans);
    printf ("%d", ans);
    // while (1);
}
------------------------------------------------------
Problem1066:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
struct data
{
    int l, r;
    bool operator < (const data &a) const 
    {
        return l == a.l ? r < a.r : l < a.l;
    }
}a[2005];
long long f[2050][4050];
// 这一个是 i 上一个是 j 方案数
int st[4005];
int main()
{
    int n;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1);
    for (int i = 1, j = 1; i <= 4000; st[i++] = j)
        while (j <= n && a[j].l <= i)
            j++;
    for (int i = 1; i <= 4000; i++)
        f[n + 1][i] = 1;
    for (int i = n; i > 0; i--)
    {
        for (int j = 4000; j >= 0; j--)
        {
            f[i][j] = f[i + 1][j];
            if (a[i].l <= j)
            {
                int p = a[i].r, q = j;
                if (p > q)
                    swap(p, q);
                (f[i][j] += f[st[p]][q]) %= MOD;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        (ans += f[i + 1][a[i].r]) %= MOD;
    printf ("%d", ans);
    // while (1);
}
------------------------------------------------------
Problem1069:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct data
{
    long long l, r;
    bool operator < (const data &a)const 
    {
        return r == a.r ? l < a.l : r < a.r;
    }
}a[200005];
int main()
{
    int n;
    scanf("%d", &n);
    long long c, d;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &c, &d);
        a[i].l = c - d, a[i].r = c + d;
    }
    sort(a + 1, a + n + 1);
    int ans = 0, now = -0x7fffffff;
    for (int i = 1; i <= n; i++)
    {
        if (a[i].l >= now)
        {
            now = a[i].r;
            ans++;
        }
    }
    printf("%d", ans);
}
------------------------------------------------------
Problem1070:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100005;
int Max[N << 2], MOD[N << 2];
long long Sum[N << 2];
void PushUp(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}
void BuildTree(int l, int r, int rt)
{
    if(l == r)
    {
        scanf("%d", &Max[rt]);
        Sum[rt] = Max[rt];
        return;
    }
    int m = l + r >> 1;
    BuildTree(l, m, rt << 1);
    BuildTree(m + 1, r, rt << 1 | 1);
    PushUp(rt);
}
void Update(int L, int R, int mod, int l, int r, int rt)
{
    if (Max[rt] < mod)
        return;
    if (l == r)
    {
        Max[rt] = Max[rt] % mod;
        Sum[rt] = Max[rt];
        return;
    }
    int m = l + r >> 1;
    if (L <= m) Update(L, R, mod, l, m, rt << 1);
    if (R > m) Update(L, R, mod, m + 1, r, rt << 1 | 1);
    PushUp(rt);
}
void Change(int x, int c, int l, int r, int rt)
{
    if (l == r)
    {
        Max[rt] = c, Sum[rt] = c;
        return;
    }
    int m = l + r >> 1;
    if (x <= m) Change(x, c, l, m, rt << 1);
    else Change(x, c, m + 1, r, rt << 1 | 1);
    PushUp(rt);
}
long long Query(int L, int R, int l, int r ,int rt)
{
    if (L <= l && R >= r)
        return Sum[rt];
    int m = l + r >> 1;
    long long ans = 0;
    if (L <= m) ans += Query(L, R, l, m, rt << 1);
    if (R > m) ans += Query(L, R, m + 1, r, rt << 1 | 1);
    return ans;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    BuildTree(1, n, 1);
    int op, a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &op);
        if(op == 1)
        {
            scanf("%d%d", &a, &b);
            printf("%lld\n", Query(a, b, 1, n ,1));
        }
        else if (op == 2)
        {
            scanf("%d%d%d", &a, &b, &c);
            Update(a, b, c, 1, n, 1);
        }
        else if (op == 3)
        {
            scanf("%d%d", &a, &b);
            Change(a, b, 1, n, 1);
        }
    }
}
------------------------------------------------------
Problem1071:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long m, bin[65], c[65][65];
long long k;
long long Judge(long long x)
{
    if(!x) return -1;
    long long ans = 0;
    int num = 0;
    for (int i = 63; i >= 0; i--)
    {
        if(bin[i] & x) {
            num++;
            ans += c[i][k - num];
        }
    }
    return ans;
}
long long Calc(long long m)
{
    long long l = 1, r = bin[62], mid, ans;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (Judge(mid) < m) l = mid + 1;
        else ans = mid, r = mid - 1;
    }
    return ans;
}
int main()
{
    bin[0] = 1;
    for (int i = 1; i <= 63; i++) bin[i] = bin[i - 1] << 1;
    c[0][0] = 1;
    for (int i = 1; i <= 63; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lld%lld", &m, &k);
        if (k == 1) {printf("-1\n");continue;}
        if (k == 63) {printf("1 4611686018427387903\n");continue;}
        if (k == 64) {printf("1 9223372036854775807\n");continue;}
        long long L = Calc(m);
        long long R = Calc(m + 1) - 1;
        printf("%lld %lld\n", L, R);
    }
}
------------------------------------------------------
Problem1072:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
char s[1000005];
long long f[1000005][4][4];
inline int Get(char x)
{
    if (x == '0')
        return 0;
    if (x == '1')
        return 1;
    if (x == '2')
        return 2;
    if (x == '*')
        return 3;
    else return 5;
}
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int l = Get(s[1]);
    if(l == 1 || l == 5)
        f[1][1][0] = 1;
    if(l == 3 || l == 5)
        f[1][3][0] = 1;
    if(l == 0 || l == 5)
        f[1][0][0] = 1;
    for (int i = 2; i <= n; i++)
    {
        int now = Get(s[i]);
        if (now == 0 || now == 5) 
        {
            f[i][0][2] = 0;
            f[i][0][3] = 0;
            f[i][0][1] = f[i - 1][1][3];
            f[i][0][0] = (f[i - 1][0][0] + f[i - 1][0][1]) % MOD;
        }
        if (now == 1 || now == 5)
        {
            f[i][1][0] = (f[i - 1][0][1] + f[i - 1][0][0]) % MOD;
            f[i][1][1] = f[i - 1][1][3];
            f[i][1][2] = 0;
            f[i][1][3] = (f[i - 1][3][1] + f[i - 1][3][2] + f[i - 1][3][3] + f[i - 1][3][0]) % MOD;
        }
        if (now == 2 || now == 5)
        {
            f[i][2][0] = 0;
            f[i][2][1] = 0;
            f[i][2][2] = 0;
            f[i][2][3] = (f[i - 1][3][1] + f[i - 1][3][2] + f[i - 1][3][3] + f[i - 1][3][0]) % MOD;
        }
        if (now == 3 || now == 5)
        {
            f[i][3][0] = 0;
            f[i][3][1] = (f[i - 1][1][0] + f[i - 1][1][1]) % MOD;
            f[i][3][2] = f[i - 1][2][3];
            f[i][3][3] = (f[i - 1][3][1] + f[i - 1][3][2] + f[i - 1][3][3] + f[i - 1][3][0]) % MOD; 
        }
    }
    long long ans = 0;
    ans = f[n][1][3] + f[n][0][1] + f[n][0][0] + f[n][3][1] + f[n][3][2] + f[n][3][3];
    printf("%d", (int)(ans % MOD));
    // while(1);
}
------------------------------------------------------
Problem1072:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
char s[1000005];
long long f[1000005][4][4];
inline int Get(char x)
{
    if (x == '0')
        return 0;
    if (x == '1')
        return 1;
    if (x == '2')
        return 2;
    if (x == '*')
        return 3;
    else return 5;
}
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int l = Get(s[1]);
    if(l == 1 || l == 5)
        f[1][1][0] = 1;
    if(l == 3 || l == 5)
        f[1][3][0] = 1;
    if(l == 0 || l == 5)
        f[1][0][0] = 1;
    for (int i = 2; i <= n; i++)
    {
        int now = Get(s[i]);
        if (now == 0 || now == 5) 
        {
            f[i][0][1] = f[i - 1][1][3];
            f[i][0][0] = (f[i - 1][0][0] + f[i - 1][0][1]) % MOD;
        }
        if (now == 1 || now == 5)
        {
            f[i][1][0] = (f[i - 1][0][1] + f[i - 1][0][0]) % MOD;
            f[i][1][1] = f[i - 1][1][3];
            f[i][1][3] = (f[i - 1][3][1] + f[i - 1][3][2] + f[i - 1][3][3] + f[i - 1][3][0]) % MOD;
        }
        if (now == 2 || now == 5)
        {
            f[i][2][3] = (f[i - 1][3][1] + f[i - 1][3][2] + f[i - 1][3][3] + f[i - 1][3][0]) % MOD;
        }
        if (now == 3 || now == 5)
        {
            f[i][3][1] = (f[i - 1][1][0] + f[i - 1][1][1]) % MOD;
            f[i][3][2] = f[i - 1][2][3];
            f[i][3][3] = (f[i - 1][3][1] + f[i - 1][3][2] + f[i - 1][3][3] + f[i - 1][3][0]) % MOD; 
        }
    }
    long long ans = 0;
    ans = f[n][1][3] + f[n][0][1] + f[n][0][0] + f[n][3][1] + f[n][3][2] + f[n][3][3];
    printf("%d", (int)(ans % MOD));
    // while(1);
}
------------------------------------------------------
Problem1073:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 100005;
int a[305][305];
int H[305][305], n, m;
int dx[4] = {0, 0, 1, -1}, 
    dy[4] = {1, -1, 0, 0};
#define id(_,__) (((_) - 1) * m + (__))
struct edge
{
    int END, next, s, v;
    bool operator < (const edge &b) const 
    {
        return v < b.v;
    }
}E[N << 3], v[N << 1];
int first[N], p, o;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int fa[N], dis[N];
int find(int x)
{
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
bool vis[N];
int main()
{
    memset(first, -1, sizeof(first));
    memset(H, 0x3f, sizeof(H));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i != 1) E[++o].END = id(i, j), E[o].s = id(i - 1, j), E[o].v = max(a[i][j], a[i - 1][j]);
            // E[++o].END = id(i, j), E[o].s = id(i + 1, j), E[o].v = max(a[i][j], a[i + 1][j]);
            if (j != 1) E[++o].END = id(i, j), E[o].s = id(i, j - 1), E[o].v = max(a[i][j], a[i][j - 1]);
            // E[++o].END = id(i, j), E[o].s = id(i, j + 1), E[o].v = max(a[i][j], a[i][j + 1]);
        }
    }
    for (int i = 1; i <= id(n, m); i++)
        fa[i] = i;
    int t = 0;
    sort(E + 1, E + o + 1);    
    for (int i = 1; i <= o; i++)
    {
        if(find(E[i].END) != find(E[i].s))
        {
            fa[find(E[i].END)] = find(E[i].s);
            add(E[i].END, E[i].s, E[i].v);
            add(E[i].s, E[i].END, E[i].v);
            t++;
            if(t == n * m - 1) break;
        }
    }
    queue<int> Q;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 2; i < m; i++)
    {
        Q.push(id(1, i)), dis[id(1, i)] = a[1][i]; vis[id(1, i)] = 1;
        Q.push(id(n, i)), dis[id(n, i)] = a[n][i]; vis[id(n, i)] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        Q.push(id(i, 1)), dis[id(i, 1)] = a[i][1]; vis[id(i, 1)] = 1;
        Q.push(id(i, m)), dis[id(i, m)] = a[i][m]; vis[id(i, m)] = 1;
    }
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > max(dis[k], v[i].v))
            {
                dis[v[i].END] = max(dis[k], v[i].v);
                if (!vis[v[i].END])
                {
                    Q.push(v[i].END);
                    vis[v[i].END] = 1;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            printf("%d ", max(0, dis[id(i, j)]) - a[i][j]);
        printf("\n");
    }
    // while(1);
}
------------------------------------------------------
Problem1074:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 200005;
const int MAXM = 500000;
int prime[MAXN], isnprime[MAXM + 1], mu[MAXM + 1], cnt;
void Get_mu()
{
    mu[1] = 1;
    for (int i = 2; i <= MAXM; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXM) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i]; 
        }
    }
}
struct edge
{
    int v, next;
}v[MAXM << 6];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].v = b;
    v[p].next = first[a];
    first[a] = p++;
}
bool vis[MAXN];
long long Ans, Sum[MAXM + 2];
int main()
{
    memset(first, -1, sizeof(first));
    int n, m, val;
    Get_mu();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val);
        for (int j = 1; j * j <= val; j++)
        {
            if(val % j) continue;
            add(i, j);
            if(val / j != j) add(i, val / j);
        }
    }
    while (m--)
    {
        scanf("%d", &val);
        if(vis[val]) 
            for (int i = first[val]; i != -1; i = v[i].next) Sum[v[i].v]--, Ans -= Sum[v[i].v] * mu[v[i].v];
        else
            for (int i = first[val]; i != -1; i = v[i].next) Ans += Sum[v[i].v] * mu[v[i].v], Sum[v[i].v]++;
        vis[val] ^= 1;
        printf("%lld\n", Ans);
    }
}
------------------------------------------------------
Problem1074:
#pragma GCC optimize("O3")
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 200005;
const int MAXM = 500000;
int prime[MAXN], isnprime[MAXM + 1], mu[MAXM + 1], cnt;
void Get_mu()
{
    mu[1] = 1;
    for (int i = 2; i <= MAXM; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXM) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i]; 
        }
    }
}
struct edge
{
    int v, next;
}v[MAXM << 6];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].v = b;
    v[p].next = first[a];
    first[a] = p++;
}
bool vis[MAXN];
long long Ans, Sum[MAXM + 2];
int main()
{
    memset(first, -1, sizeof(first));
    int n, m, val;
    Get_mu();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val);
        for (int j = 1; j * j <= val; j++)
        {
            if(val % j) continue;
            add(i, j);
            if(val / j != j) add(i, val / j);
        }
    }
    while (m--)
    {
        scanf("%d", &val);
        if(vis[val]) 
            for (int i = first[val]; i != -1; i = v[i].next) Sum[v[i].v]--, Ans -= Sum[v[i].v] * mu[v[i].v];
        else
            for (int i = first[val]; i != -1; i = v[i].next) Ans += Sum[v[i].v] * mu[v[i].v], Sum[v[i].v]++;
        vis[val] ^= 1;
        printf("%lld\n", Ans);
    }
}
------------------------------------------------------
Problem1075:
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long
int a[6], f[1000005][6], b[6];
int pow_mod(int a, int b, int p)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}
int C(int n, int m, int p)
{
    if (m == 0 || n == m) return 1;
    if (n < m) return 0;
    return f[n][p] * pow_mod(f[m][p] * f[n - m][p] % a[p], a[p] - 2, a[p]) % a[p];
}
int lucas(int n, int m, int p)
{
    if (m == 0 || n == m) return 1;
    if (n < m) return 0;
    return C(n % a[p], m % a[p], p) * lucas(n / a[p], m / a[p], p) % a[p]; 
}
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int CRT(int *a, int *b, int n)
{
    int N = 1, Ni, now, ans = 0;
    for (int i = 1; i <= n; i++) N *= a[i];
    for (int i = 1; i <= n; i++)
    {
        Ni = N / a[i];
        now = pow_mod(Ni, a[i] - 2, a[i]);
        ans = (ans + (b[i] * now % N) * Ni % N) % N;    
    }
    return ans;
}
signed main()
{
    int N, G;
    a[1] = 2, a[2] = 3, a[3] = 5, a[4] = 7, a[5] = 129011;
    f[0][1] = f[0][2] = f[0][3] = f[0][4] = f[0][5] = 1;
    for (int i = 1; i <= 1000000; i++)
        for (int j = 1; j <= 5; j++)
            f[i][j] = f[i - 1][j] * i % a[j];
    scanf("%lld%lld", &N, &G);
    for (int i = 1; i <= N; i++)
        if(gcd(i, N) == 1)
            for (int j = 1; j <= 5; j++)
                b[j] = (b[j] + lucas(G, i, j)) % a[j];
    int tmp = CRT(a, b, 5);
    tmp += 27092310;
    int ans = pow_mod(N, tmp, 54184622);
    printf("%lld", ans);
    // while (1);
}
------------------------------------------------------
Problem1076:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 101000;
char s[N];
int a[N];
int Max[N << 2], Min[N << 2], lazy[N << 2], Sum[30];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1 
void PushUp(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
}
void Pushdown(int rt)
{
    if (lazy[rt])
    {
        lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
        Max[rt << 1] = Min[rt << 1] = Max[rt << 1 | 1] = Min[rt << 1 | 1] = lazy[rt];
        lazy[rt] = 0;
    }
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        Max[rt] = Min[rt] = a[l];
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    PushUp(rt);
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        lazy[rt] = c;
        Max[rt] = Min[rt] = c;
        return;
    }
    Pushdown(rt);
    int m = l + r >> 1;
    if (L <= m) Update (L, R, c, lch);
    if (R > m) Update (L, R, c, rch);
    PushUp(rt);
}
void Query(int L, int R, int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        Sum[Max[rt]] += min(r, R) - max(L, l) + 1;
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    if (L <= m) Query(L, R, lch);
    if (R > m) Query(L, R, rch);
    PushUp(rt);
}
void Get_Ans(int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        for (int i = l; i <= r; i++)
            a[i] = Max[rt];
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    Get_Ans(lch);
    Get_Ans(rch);
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++)
        a[i] = s[i] - 'a' + 1;
    buildtree(1, n, 1);
    int l, r, op;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &l, &r, &op);
        if (op == 1)
        {
            memset(Sum, 0, sizeof(Sum));
            Query(l, r, 1, n, 1);
            int now = l;
            for (int i = 1; i <= 26; i++)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
        else
        {
            memset(Sum, 0, sizeof(Sum));
            Query(l, r, 1, n, 1);
            int now = l;
            for (int i = 26; i >= 1; i--)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
    }
    Get_Ans(1, n, 1);
    for (int i = 1; i <= n; i++)
    {
        printf("%c", char(a[i] + 'a' - 1));
    }
    // while (1);
}
------------------------------------------------------
Problem1076:
#pragma GCC optimize ("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 101000;
char s[N];
int a[N];
int Max[N << 2], Min[N << 2], lazy[N << 2], Sum[30];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1 
void PushUp(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
}
void Pushdown(int rt)
{
    if (lazy[rt])
    {
        lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
        Max[rt << 1] = Min[rt << 1] = Max[rt << 1 | 1] = Min[rt << 1 | 1] = lazy[rt];
        lazy[rt] = 0;
    }
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        Max[rt] = Min[rt] = a[l];
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    PushUp(rt);
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        lazy[rt] = c;
        Max[rt] = Min[rt] = c;
        return;
    }
    Pushdown(rt);
    int m = l + r >> 1;
    if (L <= m) Update (L, R, c, lch);
    if (R > m) Update (L, R, c, rch);
    PushUp(rt);
}
void Query(int L, int R, int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        Sum[Max[rt]] += min(r, R) - max(L, l) + 1;
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    if (L <= m) Query(L, R, lch);
    if (R > m) Query(L, R, rch);
    PushUp(rt);
}
void Get_Ans(int l, int r, int rt)
{
    if (Max[rt] == Min[rt])
    {
        for (int i = l; i <= r; i++)
            a[i] = Max[rt];
        return;
    }
    int m = l + r >> 1;
    Pushdown(rt);
    Get_Ans(lch);
    Get_Ans(rch);
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++)
        a[i] = s[i] - 'a' + 1;
    buildtree(1, n, 1);
    int l, r, op;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &l, &r, &op);
        if (op == 1)
        {
            memset(Sum, 0, sizeof(Sum));
            Query(l, r, 1, n, 1);
            int now = l;
            for (int i = 1; i <= 26; i++)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
        else
        {
            memset(Sum, 0, sizeof(Sum));
            Query(l, r, 1, n, 1);
            int now = l;
            for (int i = 26; i >= 1; i--)
                if (Sum[i])
                    Update(now, now + Sum[i] - 1, i, 1, n, 1), now += Sum[i];
        }
    }
    Get_Ans(1, n, 1);
    for (int i = 1; i <= n; i++)
    {
        printf("%c", char(a[i] + 'a' - 1));
    }
    // while (1);
}
------------------------------------------------------
Problem1077:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int MOD = 998244353;
int l[3005], r[3005];
long long f[3005][3005], A[3005][3005];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    A[0][0] = 1;
    for (int i = 1; i <= 3000; i++)
    {
        A[i][0] = 1;
        for (int j = 1; j <= 3000; j++)
            A[i][j] = A[i][j - 1] * (i - j + 1) % MOD;
    }
    int a, b;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a, &b), l[a]++, r[b]++;
    for (int i = 1; i <= m; i++)
        l[i] += l[i - 1], r[i] += r[i - 1];
    f[1][0] = 1;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j <= r[i]; j++)
        {
            if (j <= i - l[i - 1])
                f[i][j] = f[i][j] * A[i - l[i - 1] - j][l[i] - l[i - 1]] % MOD;
            else
                f[i][j] = 0;
        }
        if (i == m) break;
        for (int j = 0; j <= r[i]; j++)
        {
            f[i + 1][j] = (f[i + 1][j] + f[i][j]) % MOD;
            if (j != r[i + 1])
                f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j] * (r[i + 1] - j) % MOD) % MOD;
        }
    }
    printf("%lld", f[m][n]);
}
------------------------------------------------------
Problem1078:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100005], Sum[100005];
int n, N;
struct Node
{
    int s;
    Node *ch[2];
    Node()
    {
        ch[0] = ch[1] = NULL;
        s = 0;
    }
    #define size(_) ((_) ? (_)->s: 0)
}*root;
void Insert(int x)
{
    Node *rt = root;
    for (int i = n - 1; i >= 0; i--)
    {
        int next = (x >> i) & 1;
        if (!rt->ch[next])
            rt->ch[next] = new Node();
        rt = rt->ch[next];
        rt->s++;
    }
}
int Change(int x)
{
    return ((x >> (n - 1)) + (x << 1)) & N;
}
int ans = 0, cnt = 0;
void DFS(Node *rt, int Dep, int now)
{
    if (rt->ch[0] == NULL && rt->ch[1] == NULL)
    {
        if (now > ans) cnt = 1, ans = now;
        else if (ans == now) cnt += 1;
        return;
    }
    if (rt->ch[0] != NULL && rt->ch[1] != NULL)
    {
        DFS(rt->ch[0], Dep - 1, now);
        DFS(rt->ch[1], Dep - 1, now);
    }
    else
    {
        if (rt->ch[0] != NULL)
            DFS(rt->ch[0], Dep - 1, now | (1 << (Dep - 1)));
        else
            DFS(rt->ch[1], Dep - 1, now | (1 << (Dep - 1))) ;
    }
}
int main()
{
    root = new Node();
    int m;
    scanf("%d%d", &n, &m);
    N = (1 << n) - 1;
    for (int i = 1; i <= m; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        Sum[i] = Sum[i - 1] ^ a[i];
    int now = 0;
    for (int i = 0; i <= m; i++)
    {
        now ^= Change(a[i]);
        Insert(now ^ Sum[m] ^ Sum[i]);
    }
    DFS(root, n, 0);
    printf("%d\n%d\n", ans, cnt);
    // while (1);
}
------------------------------------------------------
Problem1079:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int t = 0;
bool Judge(char *s)
{
    int now = 1;
    while (s[now] == 'G') now++;
    return now - 1 == t;
}
int main()
{
    static char s[1000005];
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    if (n <= 10000)
    {
        for (int i = 1; i <= n; i++)
            if (s[i] == 'G') 
                t++;
        int ans = 0;
        while (!Judge(s))
        {
            for (int i = 1; i < n; i++)
                if (s[i] == 'B' && s[i + 1] == 'G') swap(s[i], s[i + 1]), i++;
            ans++;
        }
        printf("%d", ans);
        getchar(), getchar();
    }
    else
    {
        int h = 0, e = 0, ans = 0;
        for (int i = n; i >= 1; i--)
        {
            if (s[i] == 'G')
            {
                if (h) h--;
            }
            else
            {
                ++e;
                ans = max(ans, n - e + 1 - i + (n - e + 1 == i ? 0 : h++));
            }
        }
        printf("%d", ans);
    }
    return 0;
}
------------------------------------------------------
Problem1080:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int m;
double ans = 0;
double dp[1005][1005][15], s[1005][1005];
double a[1005][15], g[1005][1005][15];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("necklace.in", "r", stdin);
    freopen("necklace.out", "w", stdout);
#endif
    int n, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%lf", &a[i][j]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            g[i][i][j] = a[i][j];
        for (int j = i + 1; j <= n; j++)
            for (int k = 1; k <= m; k++)
                g[i][j][k] = g[i][j - 1][k] * a[j][k];
    }
    for (int i = 0; i <= n; i++) s[0][i] = 1; 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= m; k++)
            {
                dp[i][j][k] = s[i - 1][j] * g[i][i][k] - (i - j - 1 >= 0 ? (s[i - j - 1][j] - dp[i - j - 1][j][k]) * g[i - j][i][k] : 0);
                s[i][j] += dp[i][j][k];
            }
        }
    }
    for (int i = 1; i <= n; i++)
            ans += (s[n][i] - s[n][i - 1]) * i;
    printf("%.5lf", ans);
    // while (1);
}
------------------------------------------------------
Problem1081:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
int lim;
bool isheavy[100005];
int id[100005], t;
int cnt[100005][505];
long long Sum[505], Add[505], a[100005];
vector<int> All[100005], heavy[100005];
vector<int> v[100005];
int main()
{
    int n, m, q;
    scanf ("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    lim = sqrt(n);
    for (int i = 1; i <= m; i++)
    {
        int s, b;
        scanf ("%d", &s);
        if (s >= lim) id[i] = ++t, isheavy[i] = 1;
        for (int j = 1; j <= s; j++)
        {
            scanf ("%d", &b);
            All[b].push_back(i);
            v[i].push_back(b);
            if (isheavy[i])
            {
                Sum[id[i]] += a[b];
                heavy[b].push_back(i); 
            }
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < All[i].size(); j++)
            for (int k = 0; k < heavy[i].size(); k++)
                cnt[All[i][j]][id[heavy[i][k]]]++;
    // char op[4];
    int op;
    int x, y;
    while (q--)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf ("%d", &x);
            if (isheavy[x])
            {
                long long ans = Sum[id[x]];
                for (int i = 1; i <= t; i++) ans += cnt[x][i] * Add[i];
                printf ("%lld\n", ans);
                continue;
            }
            else
            {
                long long ans = 0;
                for (int i = 0; i < v[x].size(); i++)
                    ans += a[v[x][i]];
                for (int i = 1; i <= t; i++)
                    ans += cnt[x][i] * Add[i];
                printf("%lld\n", ans);
                continue;
            }
        }
        else
        {
            scanf("%d%d", &x, &y);
            if (isheavy[x])
                Add[id[x]] += y;
            else
            {
                for (int i = 0; i < v[x].size(); i++)
                    a[v[x][i]] += y;
                for (int i = 1; i <= t; i++)
                    Sum[i] += cnt[x][i] * y;
            }
        }
    }
    // while (1);
}
/*
5 3 5
5 -5 5 1 -4
2 1 2
4 2 1 4 5
2 2 5
1 2
2 3 4
1 1
2 2 1
1 2
*/
------------------------------------------------------
Problem1082:
#pragma GCC optimize("O3")
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
set<int> st;
set<int>::iterator it; 
template<typename _Tp>
inline void read(_Tp &a)
{
    int f = 1;
    a = 0;
    char ch = getchar();
    while (ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while (ch<='9'&&ch>='0'){a=a*10+ch-'0';ch=getchar();}
    a *= f;
}
bool OK(int x, int D, int L)
{
    int now = 0;
    while (now + D < L)
    {
        it = st.upper_bound(now + D);
        --it;
        if (*it <= now) return 0;
        else
        {
            now = *it;
            st.erase(it);
        }
    }
    return 1;
}
int main()
{
    // freopen("blue.in", "r", stdin);
    int T, a;
    read(T);
    while (T--)
    {
        st.clear();st.insert(0);
        int n, m, D, L;
        read(n), read(m), read(D), read(L);
        for (int i = 1; i <= n; i++)
            read(a), st.insert(a);
        int t = 0;
        while (OK(t + 1, D, L) && t < m) t++;
        if (t == m) printf("Excited\n");
        else printf("%d\n", t); 
    }
    // while (1);
}
------------------------------------------------------
Problem1083:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct M
{
    int op, v;
}a[200005];
int n;
const int N = 200005;
int Sum[N << 2], Add[N << 2], Del[N << 2], tmp[N << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int Query(int l, int r, int rt, int val)
{
    if (Add[rt] <= val) return 0;
    if (l == r) return (val == 0 ? Sum[rt] : 0);
    int m = l + r >> 1;
    if (Add[rt << 1 | 1] >= val)
        return tmp[rt] + Query(rch, val);
    else
        return Query(lch, val - Add[rt << 1 | 1] + Del[rt << 1 | 1]);
}
void Pushup(int l, int r, int rt)
{
    int m = l + r >> 1;
    Sum[rt] = Sum[rt << 1 | 1];
    Add[rt] = Add[rt << 1 | 1]; 
    Del[rt] = Del[rt << 1];
    if (Add[rt << 1] >= Del[rt << 1 | 1]) 
    {
        Add[rt] += Add[rt << 1] - Del[rt << 1 | 1];
        Sum[rt] += (tmp[rt] = Query(l, m, rt << 1, Del[rt << 1 | 1]));
    }
    else Del[rt] += Del[rt << 1 | 1] - Add[rt << 1], tmp[rt] = 0;
}
void Buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        if (a[l].op == 0)
            Sum[rt] = a[l].v, Add[rt] = 1, tmp[rt] = 0, Del[rt] = 0;
        else
            Del[rt] = a[l].v, tmp[rt] = 0, Sum[rt] = 0, Add[rt] = 0;
        return;
    }
    int m = l + r >> 1; 
    Buildtree(lch);
    Buildtree(rch);
    Pushup(l, r, rt);
}
void Update(int x, int op, int v, int l, int r, int rt)
{
    if (l == r)
    {
        if (op == 0)
            Sum[rt] = v, Add[rt] = 1, tmp[rt] = 0, Del[rt] = 0;
        else
            Del[rt] = v, tmp[rt] = 0, Sum[rt] = 0, Add[rt] = 0;
        return;
    }
    int m = l + r >> 1;
    if (x <= m)
        Update(x, op, v, lch);
    else 
        Update(x, op, v, rch);
    Pushup(l, r, rt);
}
int main()
{
    // freopen("weed.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    int rp;
    scanf("%d%d", &n, &rp);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &a[i].op, &a[i].v);
    Buildtree(1, n ,1);
    int c, x, y;
    while (rp--)
    {
        scanf("%d%d%d", &c, &x, &y);
        Update(c, x, y, 1, n, 1);
        printf ("%d\n", Sum[1]);
    }
}
------------------------------------------------------
Problem1083:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename _Tp>
inline void read(_Tp &a)
{
    int f = 1;
    a = 0;
    char ch = getchar();
    while (ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while (ch<='9'&&ch>='0'){a=a*10+ch-'0';ch=getchar();}
    a *= f;
}
struct M
{
    int op, v;
}a[200005];
int n;
const int N = 200005;
int Sum[N << 2], Add[N << 2], Del[N << 2], tmp[N << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int Query(const int &l,const int &r, const int &rt, const int &val)
{
    if (Add[rt] <= val) return 0;
    if (l == r) return (val == 0 ? Sum[rt] : 0);
    int m = l + r >> 1;
    if (Add[rt << 1 | 1] >= val)
        return tmp[rt] + Query(rch, val);
    else
        return Query(lch, val - Add[rt << 1 | 1] + Del[rt << 1 | 1]);
}
void Pushup(const int &l, const int &r, const int &rt)
{
    int m = l + r >> 1;
    Sum[rt] = Sum[rt << 1 | 1];
    Add[rt] = Add[rt << 1 | 1]; 
    Del[rt] = Del[rt << 1];
    if (Add[rt << 1] >= Del[rt << 1 | 1]) 
    {
        Add[rt] += Add[rt << 1] - Del[rt << 1 | 1];
        Sum[rt] += (tmp[rt] = Query(l, m, rt << 1, Del[rt << 1 | 1]));
    }
    else Del[rt] += Del[rt << 1 | 1] - Add[rt << 1], tmp[rt] = 0;
}
void Buildtree(const int &l, const int &r, const int &rt)
{
    if (l == r)
    {
        if (a[l].op == 0)
            Sum[rt] = a[l].v, Add[rt] = 1, tmp[rt] = 0, Del[rt] = 0;
        else
            Del[rt] = a[l].v, tmp[rt] = 0, Sum[rt] = 0, Add[rt] = 0;
        return;
    }
    int m = l + r >> 1; 
    Buildtree(lch);
    Buildtree(rch);
    Pushup(l, r, rt);
}
void Update(const int &x, const int &op, const int &v, const int &l, const int &r, const int &rt)
{
    if (l == r)
    {
        if (op == 0)
            Sum[rt] = v, Add[rt] = 1, tmp[rt] = 0, Del[rt] = 0;
        else
            Del[rt] = v, tmp[rt] = 0, Sum[rt] = 0, Add[rt] = 0;
        return;
    }
    int m = l + r >> 1;
    if (x <= m)
        Update(x, op, v, lch);
    else 
        Update(x, op, v, rch);
    Pushup(l, r, rt);
}
int main()
{
    // freopen("weed.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    int rp;
    read(n);
    read(rp);
    // scanf("%d%d", &n, &rp);
    for (int i = 1; i <= n; i++)
        read(a[i].op), read(a[i].v);
    Buildtree(1, n ,1);
    int c, x, y;
    while (rp--)
    {
        read(c), read(x), read(y);
        // scanf("%d%d%d", &c, &x, &y);
        Update(c, x, y, 1, n, 1);
        printf ("%d\n", Sum[1]);
    }
}
------------------------------------------------------
Problem1083:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct M
{
    int op, v;
}a[200005];
int n;
const int N = 200005;
int Sum[N << 2], Add[N << 2], Del[N << 2], tmp[N << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int Query(const int &l,const int &r, const int &rt, const int &val)
{
    if (Add[rt] <= val) return 0;
    if (l == r) return (val == 0 ? Sum[rt] : 0);
    int m = l + r >> 1;
    if (Add[rt << 1 | 1] >= val)
        return tmp[rt] + Query(rch, val);
    else
        return Query(lch, val - Add[rt << 1 | 1] + Del[rt << 1 | 1]);
}
void Pushup(const int &l, const int &r, const int &rt)
{
    int m = l + r >> 1;
    Sum[rt] = Sum[rt << 1 | 1];
    Add[rt] = Add[rt << 1 | 1]; 
    Del[rt] = Del[rt << 1];
    if (Add[rt << 1] >= Del[rt << 1 | 1]) 
    {
        Add[rt] += Add[rt << 1] - Del[rt << 1 | 1];
        Sum[rt] += (tmp[rt] = Query(l, m, rt << 1, Del[rt << 1 | 1]));
    }
    else Del[rt] += Del[rt << 1 | 1] - Add[rt << 1], tmp[rt] = 0;
}
void Buildtree(const int &l, const int &r, const int &rt)
{
    if (l == r)
    {
        if (a[l].op == 0)
            Sum[rt] = a[l].v, Add[rt] = 1, tmp[rt] = 0, Del[rt] = 0;
        else
            Del[rt] = a[l].v, tmp[rt] = 0, Sum[rt] = 0, Add[rt] = 0;
        return;
    }
    int m = l + r >> 1; 
    Buildtree(lch);
    Buildtree(rch);
    Pushup(l, r, rt);
}
void Update(const int &x, const int &op, const int &v, const int &l, const int &r, const int &rt)
{
    if (l == r)
    {
        if (op == 0)
            Sum[rt] = v, Add[rt] = 1, tmp[rt] = 0, Del[rt] = 0;
        else
            Del[rt] = v, tmp[rt] = 0, Sum[rt] = 0, Add[rt] = 0;
        return;
    }
    int m = l + r >> 1;
    if (x <= m)
        Update(x, op, v, lch);
    else 
        Update(x, op, v, rch);
    Pushup(l, r, rt);
}
int main()
{
    // freopen("weed.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    int rp;
    scanf("%d%d", &n, &rp);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &a[i].op, &a[i].v);
    Buildtree(1, n ,1);
    int c, x, y;
    while (rp--)
    {
        scanf("%d%d%d", &c, &x, &y);
        Update(c, x, y, 1, n, 1);
        printf ("%d\n", Sum[1]);
    }
}
------------------------------------------------------
Problem1084:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename _Tp>
inline void read(_Tp &a)
{
    int f = 1;
    a = 0;
    char ch = getchar();
    while (ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while (ch<='9'&&ch>='0'){a=a*10+ch-'0';ch=getchar();}
    a *= f;
}
char a[2005][2005], b[2005][2005];
int s[2005][2005];
int main()
{
    // freopen("drink.in","r",stdin);
    // freopen("1.out","w", stdout);
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            read(s[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] = s[i][j] + '0';
    int x, y, c;
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d%d", &x, &y, &c);
        for (int i = x; i <= x + c - 1; i++)
            for (int j = y; j <= y + c - 1; j++)
                b[i][j] = a[i][j];
        for (int i = x; i <= x + c - 1; i++)
            for (int j = y; j <= y + c - 1; j++)
                a[x + (j - y)][y + c - 1 - (i - x)] = b[i][j];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            printf ("%d ", (int)a[i][j] - '0');
        printf ("\n");
    }
}
------------------------------------------------------
Problem1084:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline void read(int &a)
{
    int f = 1;
    a = 0;
    char ch = getchar();
    while (ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while (ch<='9'&&ch>='0'){a=a*10+ch-'0';ch=getchar();}
    a *= f;
}
int id[2005][2005];
struct data
{
    int nxt[4], t, v;
}v[2005 * 2005];
int p;
int move0(int x)
{
    int nxt = v[x].nxt[(v[x].t + 0) % 4];
    for (int i = 0; i <= 3; i++)
    {
        if (v[nxt].nxt[i] == x)
        {
            v[nxt].t = (v[x].t - ((v[x].t + 2) % 4) + i + 4) % 4;
            return nxt;
        }
    }
    return 0;
}
int move1(int x)
{
    int nxt = v[x].nxt[(v[x].t + 1) % 4];
    for (int i = 0; i <= 3; i++)
    {
        if (v[nxt].nxt[i] == x)
        {
            v[nxt].t = (v[x].t - ((v[x].t + 3) % 4) + i + 4) % 4;
            return nxt;
        }
    }
    return 0;
}
int move2(int x)
{
    int nxt = v[x].nxt[(v[x].t + 2) % 4];
    for (int i = 0; i <= 3; i++)
    {
        if (v[nxt].nxt[i] == x)
        {
            v[nxt].t = i;
            return nxt;
        }
    }
    return 0;
}
int move3(int x)
{
    int nxt = v[x].nxt[(v[x].t + 3) % 4];
    for (int i = 0; i <= 3; i++)
    {
        if (v[nxt].nxt[i] == x)
        {
            v[nxt].t = (v[x].t - ((v[x].t + 1) % 4) + i + 4) % 4;
            return nxt;
        }
    }
    return 0;
}
int Move(int x, int y)
{
    int now = id[0][0];
    for (int i = 1; i <= y; i++)
        now = move1(now);
    for (int i = 1; i <= x; i++)
        now = move2(now);
    return now;
}
int main()
{
    // freopen("drink.in","r",stdin);
    // freopen("1.out","w", stdout);
    int n, m, q;
    read(n), read(m), read(q);
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++)
            id[i][j] = ++p;
    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= m + 1; j++)
        {
            if (i != 0) v[id[i][j]].nxt[0] = id[i - 1][j];
            if (j != 0) v[id[i][j]].nxt[3] = id[i][j - 1];
            v[id[i][j]].nxt[1] = id[i][j + 1];
            v[id[i][j]].nxt[2] = id[i + 1][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &v[id[i][j]].v);
        }
    }
    int x, y, c;
    while (q--)
    {
        read(x), read(y), read(c);
        if (c == 1) continue;
        int s = Move(x, y);
        static int st[2005], Center[5], H[2005], Y[2005];
        {
            for (int i = 1; i < c; i++)
            {
                s = move1(s);
                Y[i] = s;
                if (i != c - 1)
                {
                    H[i] = v[s].nxt[v[s].t];
                    st[i] = s;
                }
            }
            for (int i = 1; i < c; i++) 
            {
                s = move2(s);
                if (i != c - 1)
                {
                    int R = v[s].nxt[(v[s].t + 1) % 4];
                    for (int j = 0; j <= 3; j++)
                    {
                        if (s == v[R].nxt[j])
                        {
                            v[R].nxt[j] = st[i];
                            v[st[i]].nxt[v[st[i]].t] = R;
                            break;
                        }
                    }
                    st[i] = s;
                }
                else Center[1] = s;
            }
            for (int i = 1; i < c; i++)
            {
                s = move3(s);
                if (i != c - 1)
                {
                    int R = v[s].nxt[(v[s].t + 2) % 4];
                    for (int j = 0; j <= 3; j++)
                    {
                        if (s == v[R].nxt[j])
                        {
                            v[R].nxt[j] = st[i];
                            v[st[i]].nxt[(v[st[i]].t + 1) % 4] = R;
                            break;
                        }
                    }
                    st[i] = s;
                }
                else Center[2] = s;
            }
            for (int i = 1; i < c; i++)
            {
                s = move0(s);
                if (i != c - 1)
                {
                    int R = v[s].nxt[(v[s].t + 3) % 4];
                    for (int j = 0; j <= 3; j++)
                    {
                        if (s == v[R].nxt[j])
                        {
                            v[R].nxt[j] = st[i];
                            v[st[i]].nxt[(v[st[i]].t + 2) % 4] = R;
                            break;
                        }
                    }
                    st[i] = s;
                }
                else Center[3] = s;
            }
            for (int i = 1; i < c; i++)
            {
                if (i != c - 1)
                {
                    int R = H[i];
                    for (int j = 0; j <= 3; j++)
                    {
                        if (Y[i] == v[R].nxt[j])
                        {
                            v[R].nxt[j] = st[i];
                            v[st[i]].nxt[(v[st[i]].t + 3) % 4] = R;
                            break;
                        }
                    }
                }
                else Center[4] = Y[i];
            }
        }
        {
            int B1 = v[Center[4]].nxt[(v[Center[4]].t + 1) % 4];
            int B2 = v[Center[4]].nxt[v[Center[4]].t];
            int R = v[Center[1]].nxt[(v[Center[1]].t + 1) % 4];
            int D = v[Center[1]].nxt[(v[Center[1]].t + 2) % 4];
            for (int i = 0; i <= 3; i++)
            {
                if (v[R].nxt[i] == Center[1])
                {
                    v[R].nxt[i] = Center[4];
                    v[Center[4]].nxt[(v[Center[4]].t) % 4] = R;
                    break;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[D].nxt[i] == Center[1])
                {
                    v[D].nxt[i] = Center[4];
                    v[Center[4]].nxt[(v[Center[4]].t + 1) % 4] = D;
                    break;
                }
            }

            int L = v[Center[2]].nxt[(v[Center[2]].t + 3) % 4];
            D = v[Center[2]].nxt[(v[Center[2]].t + 2) % 4];
            for (int i = 0; i <= 3; i++)
            {
                if (v[L].nxt[i] == Center[2])
                {
                    v[L].nxt[i] = Center[1];
                    v[Center[1]].nxt[(v[Center[1]].t + 2) % 4] = L;
                    break;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[D].nxt[i] == Center[2])
                {
                    v[D].nxt[i] = Center[1];
                    v[Center[1]].nxt[(v[Center[1]].t + 1) % 4] = D;
                }
            }
            L = v[Center[3]].nxt[(v[Center[3]].t + 3) % 4];
            int U = v[Center[3]].nxt[v[Center[3]].t];
            for (int i = 0; i <= 3; i++)
            {
                if (v[L].nxt[i] == Center[3])
                {
                    v[L].nxt[i] = Center[2];
                    v[Center[2]].nxt[(v[Center[2]].t + 2) % 4] = L;
                    break;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[U].nxt[i] == Center[3])
                {
                    v[U].nxt[i] = Center[2];
                    v[Center[2]].nxt[(v[Center[2]].t + 3) % 4] = U;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[B1].nxt[i] == Center[4])
                {
                    v[B1].nxt[i] = Center[3];
                    v[Center[3]].nxt[(v[Center[3]].t) % 4] = B1;
                    break;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[B2].nxt[i] == Center[4])
                {
                    v[B2].nxt[i] = Center[3];
                    v[Center[3]].nxt[(v[Center[3]].t + 3) % 4] = B2;
                    break;
                }
            }
        }
        // for (int i = 1; i <= n; i++)
        // {
        //     int s = move1(id[i][0]);
        //     for (int j = 1; j <= m; j++, s = move1(s))
        //         printf("%d ", v[s].v);
        //     printf("\n");
        // }
        // printf ("\n\n");
    }
    for (int i = 1; i <= n; i++)
    {
        int s = move1(id[i][0]);
        for (int j = 1; j <= m; j++, s = move1(s))
            printf("%d ", v[s].v);
        printf("\n");
    }
    // while (1);
}
------------------------------------------------------
Problem1085:
#include <cstdio>
#include <algorithm>
#include <cstring>
struct data
{
    int a, b;
    bool operator < (const data &c) const 
    {
        return b < c.b;
    }
}d[200005];
int a[2000005], f[2000005];
int main()
{
    int n, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &d[i].a, &d[i].b);
    std::sort(d + 1, d + n + 1);
    int now = 0;
    for (int i = 1; i <= n; i++)
    {
        if (d[i].b - d[i - 1].b >= 18)  a[now + 18] += d[i].a, now += 18;
        else a[now + d[i].b - d[i - 1].b] += d[i].a, now += d[i].b - d[i - 1].b;
    }
    memset(f, 0x80, sizeof (f));
    f[0] = 0;
    int ans = 0;
    for (int i = 1; i <= now; i++)
    {
        if (i >= 4) f[i] = f[i - 4] + a[i];
        if (i >= 7) f[i] = std::max(f[i], f[i - 7] + a[i]);
        ans = std::max(ans, f[i]);
    }
    printf ("%d", ans);
}
------------------------------------------------------
Problem1085:
#include <cstdio>
#include <algorithm>
#include <cstring>
struct data
{
    int a, b;
    bool operator < (const data &c) const 
    {
        return b < c.b;
    }
}d[100005];
int a[2000005], f[2000005];
int main()
{
    int n, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf ("%d%d", &d[i].a, &d[i].b);
    std::sort(d + 1, d + n + 1);
    int now = 0;
    for (int i = 1; i <= n; i++)
    {
        if (d[i].b - d[i - 1].b >= 18)  a[now + 18] += d[i].a, now += 18;
        else a[now + d[i].b - d[i - 1].b] += d[i].a, now += d[i].b - d[i - 1].b;
    }
    memset(f, 0x80, sizeof (f));
    f[0] = 0;
    int ans = 0;
    for (int i = 4; i <= now; i++)
    {
        f[i] = f[i - 4] + a[i];
        if (i >= 7) f[i] = std::max(f[i], f[i - 7] + a[i]);
        ans = std::max(ans, f[i]);
    }
    printf ("%d", ans);
}
------------------------------------------------------
Problem1086:
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
long long f[35][35][2000];
int a[35][35];
int main()
{
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        int n, m;
        scanf ("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf ("%d", &a[i][j]);
        memset (f, 0x3f, sizeof (f));
        f[0][1][0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                for (int k = 0; k <= 1900; k++)
                {
                    if (f[i - 1][j][k] >= 0x3f3f3f3f3f && f[i][j - 1][k] >= 0x3f3f3f3f3f) continue;
                    f[i][j][k + a[i][j]] = min(f[i - 1][j][k], f[i][j - 1][k]) + (n + m - 1) * a[i][j] * a[i][j] - a[i][j] * a[i][j] - 2 * k * a[i][j];
                }
            }
        }
        long long ans = 0x3f3f3f3f3f;
        for (int i = 0; i <= 1900; i++)
        {
            ans = min(ans, f[n][m][i]);
        }
        printf("%lld\n", ans);
    }
}
------------------------------------------------------
Problem1087:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next, v;
}v[200005];
int first[100005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int dis[100005], size[100005];
int cnt[100005][32], f[32], b[32], Q[32], n, M;
void DFS1(int rt, int fa, int Dep)
{
    size[rt] = 1;
    cnt[rt][0] += 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS1(v[i].END, rt, Dep + v[i].v);
        dis[rt] += dis[v[i].END] + v[i].v * size[v[i].END];
        size[rt] += size[v[i].END];
        for (int j = 0; j <= 15; j++) cnt[rt][(j + v[i].v) & 15] += cnt[v[i].END][j];
    }
    
}
int ans[100005];
void Calc(int rt, int S)
{
    ans[rt] += S;
    for (int i = 0; i <= 15; i++)
        ans[rt] = ans[rt] - f[i] * i + f[i] * (i ^ M);
    ans[rt] -= M;
}
void DFS(int rt, int fa, int S)
{
    Calc(rt, S);
    int q[16];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        memcpy(q, f, sizeof (q));
        memset(b, 0, sizeof (b));
        memset(Q, 0, sizeof (Q));
        for (int j = 0; j <= 15; j++) b[(j + v[i].v) & 15] += cnt[v[i].END][j];
        for (int j = 0; j <= 15; j++) f[j] -= b[j];
        for (int j = 0; j <= 15; j++) Q[(j + v[i].v) & 15] += f[j];
        for (int j = 0; j <= 15; j++) f[j] = Q[j] + cnt[v[i].END][j];
        DFS(v[i].END, rt, S + (n - size[v[i].END] - size[v[i].END]) * v[i].v);
        memcpy(f, q, sizeof (f));
    }
}
int main()
{
    memset(first, -1, sizeof (first));
    scanf ("%d%d", &n, &M);
    int a, b, c;
    for (int i = 1; i < n; i++)
    {
        scanf ("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    DFS1(1, 0, 0);
    for (int i = 0; i <= 15; i++) f[i] = cnt[1][i];
    DFS(1, 0, dis[1]);
    for (int i = 1; i <= n; i++)
        printf ("%d\n", ans[i]);
    //while (1);
}
------------------------------------------------------
Problem1088:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 20100403;
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long f[2000005];
long long C(int n, int m)
{
    if (n < m) return 0;
    return f[n] * pow_mod(f[m] * f[n - m] % MOD, MOD - 2) % MOD;
}
int main()
{
    int n, m;
    f[0] = 1;
    for (int i = 1; i <= 2000000; i++)
        f[i] = f[i - 1] * i % MOD;
    scanf ("%d%d", &n, &m);
    long long ans = (C(n + m, m) - C(n + m, m - 1) + MOD) % MOD;
    printf("%lld", ans);
}
------------------------------------------------------
Problem1089:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
// #define int long long
const int N = 100005;
int Sum[N << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void Pushup(int rt)
{
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1]; 
}
void Update(int x, int c, int l, int r, int rt)
{
    if (l == r)
    {
        Sum[rt] = c;
        return;
    }
    int m = l + r >> 1;
    if (x <= m) Update(x, c, lch);
    else Update(x, c, rch);
    Pushup(rt);
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        Sum[rt] = 1;
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
int find(int w, int l, int r, int rt)
{
    if (l == r)
        return l;
    int m = l + r >> 1;
    if (Sum[rt << 1] >= w)
        return find(w, lch);
    else
        return find(w - Sum[rt << 1], rch);
}
int Query(int w, int L, int R, int l, int r, int rt)
{
    if (L == l && R == r)
    {
        if (Sum[rt] < w)
            return -Sum[rt];
        return find(w, l, r, rt);
    }
    int m = l + r >> 1;
    if (R <= m)
        return Query(w, L, R, lch);
    else if (L > m)
        return Query(w, L, R, rch);
    else
    {
        int s1 = Query(w, L, m, lch);
        if (s1 > 0) return s1;
        int s2 = Query(w + s1, m + 1, R, rch);
        if (s2 > 0) return s2;
        return s1 + s2;
    }    
}
int Query_Sum(int L, int R, int l, int r, int rt)
{
    if (L == l && R == r)
        return Sum[rt];
    int m = l + r >> 1;
    if (R <= m)
        return Query_Sum(L, R, lch);
    if (L > m)
        return Query_Sum(L, R, rch);
    return Query_Sum(L, m, lch) + Query_Sum(m + 1, R, rch);
}
struct data
{
    int w, id;
    bool operator < (const data & b) const 
    {
        return w == b.w ? id < b.id : w < b.w;
    }
}a[N];
signed main()
{
    int n, m, x;
    scanf ("%d%d%d", &n, &m, &x);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i].w);
    int c;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &c);
        a[i].id = i;
        if (a[i].w <= x)
            a[i].w = (int)(floor(1.0 * (x - a[i].w) / c) + 1);
        else a[i].w = 0;
    }
    sort(a + 1, a + n + 1);
    // for (int i = 1; i <= n; i++)
        // printf ("%d\n", a[i].id);
    // printf("\n\n");
    buildtree(1, n, 1);
    int ans = 0, index = 1;
    for (int i = 1; i <= m; i++)
    {
        int now = 0;
        while (index <= n)
        {
            if (!(a[index].w - ans))
            {
                Update(a[index].id, 0, 1, n, 1);
                ++index;
                // printf ("%d\n", index);
                continue;
            }
            if (now == n)
                break;
            int tmp = Query(a[index].w - ans, now + 1, n, 1, n, 1);
            if (tmp <= 0) break;
            Update(a[index].id, 0, 1, n, 1);
            now = tmp;
            ans = a[index].w;
            ++index;
        }
        if (now < n)
            ans += Query_Sum(now + 1, n, 1, n, 1);
    }
    printf ("%d", ans);
    // while (1);
}
------------------------------------------------------
Problem1090:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
struct Hash_Table
{
    struct list
    {
        int next, v;
        int x, y;
    }v[100055];
    int first[76545], p;
    void add(int x, int y, int a, int b)
    {
        v[p].next = first[a];
        v[p].v = b;
        v[p].x = x, v[p].y = y;
        first[a] = p++;
    }
    Hash_Table()
    {
        memset(first, -1, sizeof (first));
        p = 0;
    }
    void insert(int x, int y, int i)
    {
        int H = (x % 7307) * (y % 9091) % 76543;
        add(x, y, H, i);
    }
    int count(int x, int y)
    {
        int H = (x % 7307) * (y % 9091) % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x && v[i].y == y)
                return v[i].v;
        return -1;
    }
}Hash;
//9091 7307
struct data
{
    int type, ID;
    int nextX, nextY;
}v[100050];
struct read
{
    int x, y, type;
}a[100050];
int X[1000005], Y[1000005], p;
void add(int x, int y, int type, int i)
{
    v[p].type = type;
    v[p].nextX = X[x];
    v[p].nextY = Y[y];
    v[p].ID = i;
    X[x] = p;
    Y[y] = p++;
    Hash.insert(x, y, i);
}
int dfn[100005], low[100005], Index, size[100005], T;
bool flag[100050];
stack<int> st;
int dx[8] = {0,0,1,1,1,-1,-1,-1},
    dy[8] = {1,-1,1,-1,0,0,1,-1};
int belong[100005];
void Tarjan(int rt)
{
    dfn[rt] = low[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    if (a[rt].type == 1)
    {
        for (int i = X[a[rt].x]; i != -1; i = v[i].nextX)
        {
            if (!dfn[v[i].ID])
            {
                Tarjan(v[i].ID);
                low[rt] = min(low[rt], low[v[i].ID]);
            }
            else if (flag[v[i].ID])
                low[rt] = min(low[rt], dfn[v[i].ID]);
        }
    }
    else if (a[rt].type == 2)
    {
        for (int i = Y[a[rt].y]; i != -1; i = v[i].nextY)
        {
            if (!dfn[v[i].ID])
            {
                Tarjan(v[i].ID);
                low[rt] = min(low[rt], low[v[i].ID]);
            }
            else if (flag[v[i].ID])
                low[rt] = min(low[rt], dfn[v[i].ID]);
        }
    }
    else
    {
        for (int i = 0; i <= 7; i++)
        {
            int nxt = Hash.count(a[rt].x + dx[i], a[rt].y + dy[i]);
            if (nxt != -1)
            {
                if (!dfn[nxt])
                {
                    Tarjan(nxt);
                    low[rt] = min(low[rt], low[nxt]);
                }
                else if (flag[nxt])
                    low[rt] = min(low[rt], dfn[nxt]);
            }
        }
    }
    if(dfn[rt] == low[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            flag[v] = 0;
            belong[v] = T;
            size[T]++;
        }while(dfn[v] != low[v]);
    }
}
struct edge
{
    int END, next;
}V[1000005];
int first[100005];
void addedge(int a, int b)
{
    V[p].END = b;
    V[p].next = first[a];
    first[a] = p++;
}
int rudu[100005], cudu[100005], ans;
int f[100005];
void DFS(int rt)
{
    f[rt] = size[rt];
    int tmp = 0;
    for (int i = first[rt]; i != -1; i = V[i].next)
    {
        if (!f[V[i].END])
            DFS(V[i].END);
        tmp = max(tmp, f[V[i].END]);
    }
    f[rt] += tmp;
}
int main()
{
    memset(X, -1, sizeof (X));
    memset(Y, -1, sizeof (Y));
    memset(first, -1, sizeof (first));
    int n, r, c;
    scanf ("%d%d%d", &n, &r, &c);
    int x, y, t;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d%d%d", &x, &y, &t);
        a[i].x = x, a[i].y = y, a[i].type = t;
        add(x, y, t, i);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
    p = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i].type == 1)
        {
            for (int j = X[a[i].x]; j != -1; j = v[j].nextX)
            {
                if (belong[v[j].ID] != belong[i])
                {
                    rudu[v[j].ID]++, cudu[i]++;
                    addedge(belong[i], belong[v[j].ID]);
                }
            }
        }
        else if (a[i].type == 2)
        {
            for (int j = Y[a[i].y]; j != -1; j = v[j].nextY)
            {
                if (belong[v[j].ID] != belong[i])
                {
                    rudu[v[j].ID]++, cudu[i]++;
                    addedge(belong[i], belong[v[j].ID]);
                }
            }
        }
        else
        {
            for (int j = 0; j <= 7; j++)
            {
                int nxt = Hash.count(a[i].x + dx[j], a[i].y + dy[j]);
                if (nxt != -1)
                {
                    if (belong[nxt] != belong[i])
                    {
                        rudu[nxt]++, cudu[i]++;
                        addedge(belong[i], belong[nxt]);
                    }
                }
            }
        }
    }
    ans = 0;
    for (int i = 1; i <= T; i++)
    {
        DFS(i);
        ans = max(ans, f[i]);
    }
    printf ("%d", ans);
}
------------------------------------------------------
Problem1091:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
long long a, b, d, n;
bool Judge(long long mid)
{
    if (mid < b) return 1;
    long long T1 = ceil(((double)mid - a) / d);
    long long T2 = ceil(((double)mid - b) / d);
    return n >= T1 + T2;
}
int main()
{
    scanf ("%lld%lld%lld%lld", &n, &d, &a, &b);
    n--;
    long long l = a, r = 100000000000000000ll;
    long long ans = 0;
    while (l < r)
    {
        long long mid = l + r >> 1;
        if (Judge(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else 
            r = mid;
    }
    printf ("%lld", ans);
    // while (1);
    return 0;
}
------------------------------------------------------
Problem1092:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <deque>
using namespace std;
int a[100005], l[100005], r[100005];
int Hash[200005];
template<typename _Tp>
inline _Tp read()
{
    _Tp a = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -f; ch = getchar();}
    while (ch >= '0' && ch <= '9') {a = a * 10 + ch - 48; ch = getchar();}
    return a * f;
}
struct data
{
    int type, v;
}Query[100005];
long long Sum[200005];
int cnt;
#define lowbit(_) ((_) & (-_))
void add(int x, long long c)
{
    for (int i = x; i <= cnt; i += lowbit(i))
        Sum[i] += c;
}
long long Query_Sum(int x)
{
    long long ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
long long Calc(int i)
{
    long long L = i - l[i] + 1;
    long long R = r[i] - i + 1;
    return L * R;
}
int main()
{
    int n = read<int>();
    int q = read<int>();
    for (int i = 1; i <= n; i++)
        Hash[i] = a[i] = read<int>();
    char s[5];
    for (int i = 1; i <= q; i++)
    {
        scanf ("%s", s);
        if (s[0] == '>') Query[i].type = 1;
        else if (s[0] == '=') Query[i].type = 2;
        else if (s[0] == '<') Query[i].type = 3;
        Hash[i + n] = Query[i].v = read<int>();
    }
    sort(Hash + 1, Hash + n + q + 1);
    cnt = unique(Hash + 1, Hash + n + q + 1) - Hash - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(Hash + 1, Hash + cnt + 1, a[i]) - Hash;
    deque<pair<int, int> > Q;
    for (int i = 1; i <= n; i++) l[i] = r[i] = i;
    for (int i = 1; i <= n; i++)
    {
        pair<int, int> k(a[i], i);
        while (!Q.empty() && a[i] >= Q.back().first)
        {
            k = Q.back();
            Q.pop_back();
        }
        if (Q.empty()) l[i] = 1;
        else l[i] = l[k.second];
        Q.push_back(pair<int, int>(a[i], i));
    }
    Q.clear();
    for (int i = n; i >= 1; i--)
    {
        pair<int, int> k(a[i], i);
        while (!Q.empty() && a[i] > Q.back().first)
        {
            k = Q.back();
            Q.pop_back();
        }
        if(Q.empty()) r[i] = n;
        else r[i] = r[k.second];
        Q.push_back(pair<int, int>(a[i], i));
    }
    for (int i = 1; i <= n; i++)
        add(a[i], Calc(i));
    for (int i = 1; i <= q; i++)
    {
        Query[i].v = lower_bound(Hash + 1, Hash + cnt + 1, Query[i].v) - Hash;
        if (Query[i].type == 1)
        {
            printf ("%lld\n", Query_Sum(cnt) - Query_Sum(Query[i].v));
        }
        else if (Query[i].type == 2)
        {
            printf ("%lld\n", Query_Sum(Query[i].v) - Query_Sum(Query[i].v - 1));
        }
        else
            printf ("%lld\n", Query_Sum(Query[i].v - 1));
    }
    // while (1);
}
------------------------------------------------------
Problem1093:
#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
const int MOD = 1e9 + 7;
using namespace std;
int f[100050];
int Pow[100050], g[100050];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}
signed main()
{
    int n;
    scanf ("%lld", &n);
    f[0] = 1, Pow[0] = 1;
    for (int i = 1; i <= n; i++)
        f[i] = f[i - 1] * i % MOD, Pow[i] = Pow[i - 1] * 2 % MOD;
    for (int i = 1; i <= n; i++)
        g[i] = (g[i - 1] * i + (Pow[i - 1] - 1) * f[i - 1] % MOD) % MOD;
    printf ("%lld", g[n] * pow_mod(f[n], MOD - 2) % MOD);
}
------------------------------------------------------
Problem1094:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define LL long long
LL MOD;
LL pow_mod(LL a, LL b)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1) 
            ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}
int main()
{
    int n, m, k;
    scanf ("%d%d%d", &n, &m, &k);
    MOD = m + n;
    LL ans = n * pow_mod(2, k) % MOD;
    printf ("%lld", min(ans, MOD - ans));
    return 0;
}
------------------------------------------------------
Problem1095:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100005];
int last[100005];
void Update(int x, int id)
{
    if (x < 0) return;
    if (!x) return last[0] = id, void(0);
    for (int i = 1; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            last[i] = id;
            if (i * i != x)
                last[x / i] = id;
        }
    }
}
int main()
{
    int n, K;
    scanf ("%d%d", &n, &K);
    long long ans = 0;
    int Last = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &a[i]);
        if (a[i] > K) Last = max(max(last[a[i]], last[0]), Last);
        ans += i - Last;
        Update(a[i] - K, i);
    }
    printf ("%lld", ans);
}
------------------------------------------------------
Problem1096:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int N = 1e6;
int MOD;
int prime[N], Mini[N + 5];
bool isnprime[N + 5];
int tot;
void Get_prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i]) prime[++tot] = i, Mini[i] = tot;
        for (int j = 1; j <= tot; j++)
        {
            if (prime[j] * i > N) break;
            isnprime[i * prime[j]] = 1;
            Mini[i * prime[j]] = j;
            if (i % prime[j] == 0) break;
        }
    }
}
int size[N];
void add(int x, int c)
{
    while (Mini[x])
    {
        size[Mini[x]] += c;
        x /= prime[Mini[x]];
    }
}
int C[5005];
int Get_C()
{
    int ans = 1;
    for (int i = 1; i <= tot; i++)
    {
        if (size[i])
        {
            for (int j = 1; j <= size[i]; j++)
            {
                ans = (ans * prime[i]) % MOD;
            }
        }
    }
    return ans;
}
int g[5005][5005];
int f[2][5005];
int a[N];
signed main()
{
    int n, m;
    scanf ("%lld%lld%lld", &n, &m, &MOD);
    for (int i = 1; i <= n; i++) 
        scanf ("%lld", &a[i]);
    g[1][1] = 1;
    Get_prime();
    for (int i = 2; i <= 5000; i++)
    {
        for (int j = 2; j <= 5000; j++)
            g[i][j] = (g[i - 1][j - 1] * j % MOD + g[i - 1][j] * (j - 1) % MOD) % MOD;
    }
    for (int i = 1; i <= 5000 && i <= m; i++)
        add(m - i + 1, 1), add(i, -1), C[i] = Get_C();
    f[0][0] = 1;
    int now = 1;
    for (int i = 1; i <= n; i++, now ^= 1)
    {
        if (a[i] == 1)
        {
            f[now][1] = f[now ^ 1][0] * m % MOD;
            if (a[i - 1] == 1) f[now][1] = (f[now][1] - f[now ^ 1][1] + MOD) % MOD;
            f[now][0] = f[now][1];
        }
        else
        {
            f[now][0] = 0;
            for (int j = 2; j <= a[i] && j <= m; j++)
            {
                f[now][j] = (f[now ^ 1][0] * g[a[i]][j] % MOD) * C[j] % MOD;
                if (a[i - 1] >= j) f[now][j] = (f[now][j] - f[now ^ 1][j] * g[a[i]][j] % MOD + MOD) % MOD;
                (f[now][0] += f[now][j]) %= MOD;
            }
        }
    }
    printf ("%lld", f[now^1][0]);
}
------------------------------------------------------
Problem1097:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
void Get_String(char *s)
{
    char a[55];
    a[0] = '\0';
    while (a[0] == '\0') 
        gets(a);
    int len = strlen(a);
    for (int i = 0; i < len; i++)
        s[i] = a[i];
    s[len] = '\0';
}
bool oper(char c)
{
    return (c == '+' || c == '-' || c == '/' || c == '*');
}
int n;
char s[55];
bool Judge(int l, int r)
{
    if (s[l] == ')' && s[r] == '(') return 0;
    if (l > r) return 1;
    if (oper(s[l]) || oper(s[r])) return 0;
    int L = -1, R = -1;
    int top = 0;
    for (int i = l; i <= r; i++)
        if (s[i] == '(') top++;
        else if (s[i] == ')') top--;
    if (top) return 0;
    for (int i = l; i <= r; i++)
    {
        if (s[i] == '(')
        {
            top++;
            if (top == 1) 
                L = i;
        }
        else if (s[i] == ')')
        {
            top--;
            if (top == 0)
            {
                R = i;
                break;
            }
        }
    }
    if (L != -1 && R != -1)
    {
        if (L - 1 >= 0 && !oper(s[L - 1]) && s[L - 1] != '(') return 0;
        if (R + 1 < n && !oper(s[R + 1]) && s[R + 1] != ')') return 0;
        return Judge(l, L - 2) && Judge(L + 1, R - 1) && Judge(R + 2, r);
    }
    else if (L != -1 || R != -1)
        return 0;
    else
    {
        for (int i = l; i <= r; i++) if (oper(s[i])) {L = i; break;}
        if (L != -1)
            return Judge(l, L - 1) && Judge(L + 1, r);
        else
        {
            for (int i = l; i <= r; i++)
                if (s[i] < '0' || s[i] > '9') 
                    return 0;
            return 1;
        }
    }
}
int main()
{
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        memset(s, 0, sizeof (s));
        char a[100];
        Get_String(a);
        int n1 = strlen(a);
        bool flag = 0;
        int i, p;
        for (i = 0, p = 0; i < n1; i++)
        {
            if (a[i] == ' ')
                flag = 1;
            else
            {
                if (s[p - 1] >= '0' && s[p - 1] <= '9' && a[i] >= '0' && a[i] <= '9' && flag) 
                    s[p++] = '.', s[p++] = a[i];
                else s[p++] = a[i];
                flag = 0;
            }
        }
        s[p] = '\0';
        n = strlen(s);
        if (n != 0 && Judge(0, n - 1)) printf ("Yes\n");
        else printf ("No\n");
    }
}

------------------------------------------------------
Problem1098:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
#define ULL unsigned long long
map<ULL, int> mp;
int cnt;
const int MOD = 1000000007;
ULL Hash(char *s)
{
    const static ULL base = 31;
    ULL ans = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        ans = ans * base + s[i];
    return ans;
}
char A[100], B[100];
int rudu[50005], cudu[50005];
struct edge
{
    int END, next;
}v[200005];
int first[50005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
long long f[50005];
int main()
{
    memset(first, -1, sizeof(first));
    int m;
    scanf ("%d", &m);
    int a, b;
    ULL Ha,Hb;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%s%s", A, B);
        Ha = Hash(A), Hb = Hash(B);
        if(!mp.count(Ha)) mp[Ha] = ++cnt;
        if(!mp.count(Hb)) mp[Hb] = ++cnt;
        a = mp[Ha], b = mp[Hb];
        add(a, b);
        rudu[b]++, cudu[a]++;
    }
    queue<int> Q;
    for (int i = 1; i <= cnt; i++)
        if (rudu[i] == 0)
            Q.push(i), f[i] = 1;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            f[v[i].END] = (f[v[i].END] + f[k]) % MOD;
            rudu[v[i].END]--;
            if (rudu[v[i].END] == 0)
            {
                Q.push(v[i].END);
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= cnt; i++)
        if (cudu[i] == 0)
            ans = (ans + f[i]) % MOD;
    printf ("%lld", ans);
}
------------------------------------------------------
Problem1099:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
struct data
{
    int x, y;
    bool operator < (const data &a) const 
    {
	 	 return x == a.x ? y < a.y : x < a.x;
	}
	data(int x1 = 0, int y1 = 0)
	{
         x = x1, y = y1;
 	}
}a[5005];
long long pow_mod(long long a, long long b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
long long f[5005];
long long F[200005], Inv[200005];
long long C(int n, int m)
{
	if (n < m) return 0;
	return (F[n] * Inv[m] % MOD) * Inv[n - m] % MOD;
}
int main()
{

	int n, m, k;
	scanf ("%d%d%d", &n, &m, &k);
	F[0] = 1;
	for (int i = 1; i <= 200000; i++)
		F[i] = F[i - 1] * i % MOD;
	Inv[200000] = pow_mod(F[200000], MOD - 2);
	for (int i = 200000 - 1; i >= 0; i--)
		Inv[i] = Inv[i + 1] * (i + 1) % MOD; 
	for (int i = 1; i <= k; i++) scanf ("%d%d", &a[i].x, &a[i].y);
	k++;
	a[k].x = n, a[k].y = m;
	sort(a + 1, a + k + 1);
	for (int i = 1; i <= k; i++)
	{
		f[i] = C(a[i].x + a[i].y, a[i].x);
		for (int j = 1; j < i; j++)
			f[i] = (f[i] - f[j] * C(a[i].x - a[j].x + a[i].y - a[j].y, a[i].x - a[j].x) % MOD + MOD) % MOD;
	}
	printf ("%lld", f[k]);
}

------------------------------------------------------
Problem1100:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define int long long
const int MAXN = 293;
int k;
long long m;
int prime[MAXN], isnprime[MAXN + 1], cnt;
void Get_prime()
{
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
int Max[MAXN];
vector<pair<int, int> > Update(vector<pair<int, int> > a, int p)
{
    vector<pair<int, int> > ans;
    ans.clear();
    for (int i = 0; i < a.size(); i++)
    {
        int tot = 1;
        long long P = 1;
        while (m / P >= a[i].first)
        {
            ans.push_back(pair<int, int>(a[i].first * P, a[i].second * tot));
            P *= p, tot++;
        }
    }
    sort(ans.begin(), ans.end());
    unique(ans.begin(), ans.end());
    return ans;
}
void Update(int x)
{
    int now = k;
    while (now && Max[now - 1] < x) now--;
    for (int i = k; i > now; i--) Max[i] = Max[i - 1];
    Max[now] = x;
}
vector<pair<int, int> > change(vector<pair<int, int> > a)
{
    memset(Max, 0, sizeof (Max));
    vector<pair<int, int> > ans;
    ans.clear();
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i].second >= Max[k])
        {
            Update(a[i].second);
            ans.push_back(a[i]);
        }
    }
    return ans;
}
vector<pair<int, int> > Ans;
void Get_ans()
{
    Ans.push_back(pair<int,int>(1, 1));
    for (int i = 1; i <= cnt; i++)
    {
        Ans = Update(Ans, prime[i]);
        Ans = change(Ans);
        // for (int i = 0; i < Ans.size(); i++)
            // printf ("%lld ", Ans[i].first);
        // printf ("\n");
    }
}
signed main()
{
    long long n;
    int t;
    Get_prime();
    scanf ("%lld%lld%lld", &t, &k, &m);
    Get_ans();
    while (t--)
    {
        scanf ("%lld", &n);
        printf ("%lld\n", Ans[n - 1].first);
    }
    // while (1);
}
------------------------------------------------------
Problem1101:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int MAXN = 1e5 + 5;
int a[MAXN], type[MAXN];
int f[MAXN][35], pre[MAXN][35];
int ans[MAXN];
int val[MAXN];
int Get_Num(int x)
{
    int ans = 0;
    while (x)
    {
        ans += x & 1;
        x >>= 1;
    }
    return ans;
}
int main()
{
    int n, m, c;
    scanf ("%d%d%d", &n, &m, &c);
    char s[5];
    for (int i = 1; i < n; i++)
    {
        scanf ("%s", s);
        if (s[0] == 'X') type[i] = 1;
        else if (s[0] == 'A') type[i] = 2;
        else if (s[0] == 'O') type[i] = 3;
    }
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i]);
    f[1][a[1]] = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= m; j++) if (f[i][j])
        {
            for (int k = 0; k <= min(j, a[i + 1]); k++) if (j + a[i + 1] - k <= m)
            {
                if (type[i] == 1)
                    f[i + 1][j + a[i + 1] - 2 * k] = f[i][j], pre[i + 1][j + a[i + 1] - 2 * k] = j;
                if (type[i] == 2)
                    f[i + 1][k] = f[i][j], pre[i + 1][k] = j;
                if (type[i] == 3)
                    f[i + 1][j + a[i + 1] - k] = f[i][j], pre[i + 1][j + a[i + 1] - k] = j;
            }
        }
    }
    if (!f[n][Get_Num(c)]) return printf ("OvO\n"), 0;
    ans[n] = c;
    int now = Get_Num(c);
    for (int i = n; i >= 2; i--)
    {
        int p = pre[i][now];
        // printf ("%d\n", p);
        if (type[i - 1] == 2)
        {
            int mid = now;
            int s1 = 0, s2 = 0, s3 = 0;
            for (int j = 0; j < m; j++)
            {
                if ((ans[i]&(1<<j)) && (s1 < mid)) s1++, ans[i - 1] += (1 << j), val[i] += (1 << j);
                else if ((!(ans[i]&(1<<j))) && s2 + mid < p) s2++, ans[i - 1] += (1 << j);
                else if ((!(ans[i]&(1<<j))) && s3 + mid < a[i]) s3++, val[i] += (1 << j);
            }
        }
        else if (type[i - 1] == 1)
        {
            int mid = (p + a[i] - now) / 2;
            int s1 = 0, s2 = 0, s3 = 0;
            for (int j = 0; j < m; j++)
            {
                if ((!(ans[i]&(1<<j))) && (s1 < mid)) s1++, ans[i - 1] += (1 << j), val[i] += (1 << j); 
                else if ((ans[i]&(1<<j)) && (s2 + mid < p)) s2++, ans[i - 1] += (1 << j);
                else if ((ans[i]&(1<<j)) && (s3 + mid < a[i])) s3++, val[i] += (1 << j);
            }
        }
        else
        {
            int mid = p + a[i] - now;
            int s1 = 0, s2 = 0, s3 = 0;
            for (int j = 0; j < m; j++)
            {
                if ((ans[i]&(1<<j)) && (s1 < mid)) s1++, ans[i - 1] += (1 << j), val[i] += (1 << j);
                else if ((ans[i]&(1<<j)) && (s2 + mid < p)) s2++, ans[i - 1] += (1 << j);
                else if ((ans[i]&(1<<j)) && (s3 + mid < a[i])) s3++, val[i] += (1 << j);
            }
        }
        now = p;
    }
    val[1] += ans[1];
    for (int i = 1; i <= n; i++)
        printf ("%d ", val[i]);
    // while(1);
}

------------------------------------------------------
Problem1102:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
using namespace std;
const int MAXN = 300000;
const int MOD = 1e9 + 7;
struct edge
{
    int END, next;
}v[(MAXN + 5) << 1];
int first[MAXN + 5], p;
void add(int a, int c)
{
    v[p].END = c;
    v[p].next = first[a];
    first[a] = p++;
}
int b[MAXN + 5], Index;
long long F[MAXN + 5], Ans;
int du[MAXN + 5];
set<int> tmp[MAXN + 5];
long long pow_mod(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}
int Sum[MAXN + 5];
#define lowbit(_) ((_) & (-_))
void update(int x, int c)
{
    for (int i = x; i <= MAXN; i+=lowbit(i))
        Sum[i] += c;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i-=lowbit(i))
        ans += Sum[i];
    return ans;
}
long long f[MAXN + 5];
int size[MAXN + 5], L[MAXN + 5], R[MAXN + 5], ID[MAXN + 5];
bool vis[MAXN + 5];
void dfs(int rt, int fa)
{
    size[rt] = 1, f[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        f[rt] = f[v[i].END] * f[rt] % MOD;
        size[rt] += size[v[i].END];
        tmp[rt].insert(v[i].END);
    }
    f[rt] = f[rt] * F[fa ? du[rt] - 1 : du[rt]] % MOD;
    set<int>::iterator it;
    for (it = tmp[rt].begin(); it != tmp[rt].end(); it++)
        ID[*it] = ++Index, update(ID[*it], 1);
    update(Index + 1, -(int)tmp[rt].size());
    L[rt] = ID[*tmp[rt].begin()], R[rt] = Index;
}
bool Died;
void DFS(int rt, long long last, int pos)
{
    if (Died) return;
    long long rmp = 1;
    set<int>::iterator it;
    for (it = tmp[rt].begin(); it != tmp[rt].end(); it++)
        rmp = rmp * f[*it] % MOD;
    while (!tmp[rt].empty())
    {
        if (Died) return;
        it = tmp[rt].lower_bound(b[pos]);
        if (it == tmp[rt].end())
        {
            Ans = (Ans + rmp * F[tmp[rt].size() - 1] % MOD * last % MOD * tmp[rt].size() % MOD) % MOD;
            Died = 1;
            return;
        }
        if (*it > b[pos])
        {
            Ans = (Ans + rmp * F[tmp[rt].size() - 1] % MOD * last % MOD * (Query(ID[*it]) - 1) % MOD) % MOD;
            Died = 1;
            return;
        }
        else
        {
            Ans = (Ans + rmp * F[tmp[rt].size() - 1] % MOD * last % MOD * (Query(ID[*it]) - 1) % MOD) % MOD;
            rmp = rmp * pow_mod(f[*it], MOD - 2) % MOD;
            DFS(*it, last * rmp % MOD * F[tmp[rt].size() - 1] % MOD, pos + 1);
            if (Died) return;
            pos += size[*it];
            update(ID[*it], -1);
            update(R[rt] + 1, 1);
            tmp[rt].erase(it);
        }
    }
}
int main()
{
    memset (first, -1, sizeof (first));
    int n;
    F[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        F[i] = F[i - 1] * i % MOD;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &b[i]);
    int a, c;
    for (int i = 1; i < n; i++)
    {
        scanf ("%d%d", &a, &c);
        add(a, c);
        add(c, a);
        du[a]++, du[c]++;
    }
    long long tot = 1;
    for (int i = 1; i <= n; i++)
        tot = tot * F[du[i] - 1] % MOD;
    for (int i = 1; i < b[1]; i++)
        Ans = (Ans + tot * du[i] % MOD) % MOD;
    dfs(b[1], 0), DFS(b[1], 1, 2);
    printf ("%lld", Ans);
    // while(1);
}
------------------------------------------------------
Problem1103:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char S[400005];
int nxt[400005];
char c[5];
int la, lb;
void Get_fail(int len)
{
    int j = 0, k = -1;
    nxt[0] = -1;
    while (j < len)
        if (k == -1 || S[j] == S[k])
            j++, k++, nxt[j] = k;
        else
            k = nxt[k];
}
int main()
{
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        memset (nxt, 0, sizeof(nxt));
        scanf ("%d%d", &la, &lb);
        scanf ("%s", S);
        S[la] = '&';
        for (int i = 1; i <= lb; i++)
            S[la + i] = S[i - 1];
        int len = la + lb + 2;
        scanf ("%s", c);
        S[len - 1] = c[0];
        Get_fail(len);
        if (nxt[len] == -1)
            printf ("0\n");
        else
            printf ("%d\n", nxt[len]);
    }
    // while (1);
}
------------------------------------------------------
Problem1104:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
struct egde
{
    int END, next;
}v[MAXN << 2];
int first[MAXN], p;
int S, T;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
// int f[MAXN];
// int vis[MAXN];
// void dfs(int rt, int id)
// {
//     if (f[rt] != -1) return;
//     if (rt == T) return f[rt] = 1, void(0);
//     vis[rt] = id;
//     f[rt] = 0;
//     for (int i = first[rt]; i != -1; i = v[i].next)
//     {
//         if (vis[v[i].END] == id) continue;
//         dfs(v[i].END, id);
//         f[rt] |= f[v[i].END];
//     }
// }
int dfn[MAXN], low[MAXN], Index;
bool iscut[MAXN];
bool Judge(int a)
{
    if (!dfn[1] || !dfn[T]) return 0;
    if (dfn[1] <= Index && dfn[1] >= dfn[a] && dfn[T] <= Index && dfn[T] >= dfn[a]) return 0;
    if ((dfn[1] > Index || dfn[1] < dfn[a]) && (dfn[T] > Index || dfn[T] < dfn[a])) return 0;
    return 1;
}
void Tarjan(int rt, int fa)
{
    dfn[rt] = low[rt] = ++Index;
    int s = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        // if (!f[v[i].END]) continue;
        if (!dfn[v[i].END])
        {
            s++;
            Tarjan(v[i].END, rt);
            low[rt] = min(low[rt], low[v[i].END]);
            if (low[v[i].END] >= dfn[rt] && Judge(v[i].END))
                iscut[rt] = 1;
        }
        else
            low[rt] = min(low[rt], dfn[v[i].END]);
    }
    if (fa < 0 && s == 1)
        iscut[rt] = 0;
}
int main()
{
    int t;
    scanf ("%d", &t);
    while (t--)
    {
        int n, m;
        scanf ("%d%d", &n, &m);
        memset(first, -1, sizeof (first));
        // memset(f, -1, sizeof (f));
        memset (dfn, 0, sizeof (dfn));
        memset (low, 0, sizeof (low));
        // memset (vis, 0, sizeof (vis));
        memset (iscut, 0, sizeof (iscut));
        p = 0;
        int a, b;
        for (int i = 1; i <= m; i++)
        {
            scanf ("%d%d", &a, &b);
            add(a, b);
            add(b, a);
        }
        T = n;
        // dfs(1, 1);
        Tarjan(1, -1);
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                Tarjan(i, -1);
        int ans = 0;
        for (int i = 2; i < n; i++)
            if (iscut[i])
                ans++;
        printf ("%d\n", ans);
        for (int i = 2; i < n; i++)
            if (iscut[i])
                printf ("%d ", i);
        printf ("\n");
    }
}
------------------------------------------------------
Problem1105:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int MAXN = 1000005;
char s[MAXN << 1];
int NumB, NumR;
int Get_ans(int n, int N)
{
    int ans = 0, Sum = 0, LB = 0, LR = 0, RB = 0, RR = 0, mid = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 'B') LB++, Sum += LR;
        else LR++;
        if (LR * 2 > NumR)
        {
            mid = i + 1;
            break;
        } 
    }
    for (int i = n; i >= mid; i--)
    {
        if (s[i] == 'B') RB++, Sum += RR;
        else RR++;
    }
    ans = Sum;
    for (int i = n + 1; i <= N; i++)
    {
        if (s[i] == 'B')
        {
            LB--;
            RB++;
        }
        else
        {
            LR--;
            RR++;
            Sum = Sum - LB + RB;
            while (LR * 2 <= NumR)
            {
                if (s[mid] == 'B') Sum = Sum - RR + LR, ++LB, --RB;
                else ++LR, --RR;
                mid++;
            }
            ans = min(ans, Sum);
        }
    }
    return ans;
}
signed main()
{
    int T;
    scanf ("%lld", &T);
    while (T--)
    {
        scanf ("%s", s + 1);
        int n = strlen(s + 1);
        NumB = NumR = 0;
        for (int i = 1; i <= n; i++)
        {
            if (s[n + i] = s[i])
            if (s[i] == 'B') NumB++;
            if (s[i] == 'R') NumR++;
        }
        printf ("%lld\n", Get_ans(n, 2 * n));
    }
    // while (1);
}
------------------------------------------------------
Problem1109:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int read()
{
    int a = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {a = a * 10 + ch - '0'; ch = getchar();}
    return a * f;
}
struct data
{
    int yn, ym, zn, zm;
    data()
    {
        yn = 0, ym = 0x3f3f3f3f;
        zn = 0, zm = 0x3f3f3f3f;
    }
}a[100005], st[400005][18];
// #define lch l, m, rt << 1
// #define rch m + 1, r, rt << 1 | 1
void Merge(data &ans, data a, data b)
{
    ans.yn = max(a.yn, b.yn);
    ans.ym = min(a.ym, b.ym);
    ans.zn = max(a.zn, b.zn);
    ans.zm = min(a.zm, b.zm);
}
// void Pushup(int rt)
// {
//     Merge(tree[rt], tree[rt << 1], tree[rt << 1 | 1]);
// }
// void buildtree(int l, int r, int rt)
// {
//     if (l == r)
//     {
//         tree[rt] = a[l];
//         return;
//     }
//     int m = l + r >> 1;
//     buildtree(lch);
//     buildtree(rch);
//     Pushup(rt);
// }
// data Query(int L, int R, int l, int r, int rt)
// {
//     if (L <= l && R >= r)
//         return tree[rt];
//     int m = l + r >> 1;
//     data ans;
//     if (L <= m)Merge(ans, ans, Query(L, R, lch));
//     if (R > m) Merge(ans, ans, Query(L, R, rch));
//     return ans;
// }
int x, y, z;
data Query(int l, int r)
{
    int len = r - l + 1;
    int k = 0;
    while ((1 << k) <= len) k++;
    k--;
    data ans;
    Merge(ans, st[l][k], st[r - (1 << k) + 1][k]);
    return ans;
}
bool Judge(int mid)
{
    for (int i = 1; i <= x - mid + 1; i++)
    {
        data now = Query(i, i + mid - 1);
        // now.zm = min(now.zm, z), now.ym = min(now.ym, y);
        if (now.zm - now.zn + 1 >= mid && now.ym - now.yn + 1 >= mid) return 1;
    }
    return 0;
}
int main()
{
    // x = read();
    // printf ("%d", x);
    // scanf ("%d%d%d", &x, &y, &z);
    x = read(), y = read(), z = read();
    for (int i = 1; i <= x; i++)
    {
        // scanf ("%d%d%d%d", &a[i].yn, &a[i].zn, &a[i].ym, &a[i].zm);
        a[i].yn = read(), a[i].zn = read(), a[i].ym = read(), a[i].zm = read();
        st[i][0] = a[i];
    }
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j <= x; j++)
            Merge(st[j][i], st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    // buildtree(1, x, 1);
    int l = 0, r = min(x, min(z, y)) + 1;
    int ans = 0;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (Judge(mid))
            ans = mid, l = mid + 1;
        else 
            r = mid;
    }
    printf ("%d", ans);
}
------------------------------------------------------
Problem1109:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int read()
{
    int a = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {a = a * 10 + ch - '0'; ch = getchar();}
    return a * f;
}
struct data
{
    int yn, ym, zn, zm;
    data()
    {
        yn = 0, ym = 0x3f3f3f3f;
        zn = 0, zm = 0x3f3f3f3f;
    }
}a[100005], st[400005][18];
void Merge(data &ans, data a, data b)
{
    ans.yn = max(a.yn, b.yn);
    ans.ym = min(a.ym, b.ym);
    ans.zn = max(a.zn, b.zn);
    ans.zm = min(a.zm, b.zm);
}
int x, y, z;
data Query(int l, int r)
{
    int len = r - l + 1;
    int k = 0;
    while ((1 << k) <= len) k++;
    k--;
    data ans;
    Merge(ans, st[l][k], st[r - (1 << k) + 1][k]);
    return ans;
}
bool Judge(int mid)
{
    for (int i = 1; i <= x - mid + 1; i++)
    {
        data now = Query(i, i + mid - 1);
        if (now.zm - now.zn + 1 >= mid && now.ym - now.yn + 1 >= mid) return 1;
    }
    return 0;
}
int main()
{
    x = read(), y = read(), z = read();
    for (int i = 1; i <= x; i++)
    {
        a[i].yn = read(), a[i].zn = read(), a[i].ym = read(), a[i].zm = read();
        st[i][0] = a[i];
    }
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j <= x; j++)
            Merge(st[j][i], st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    int l = 0, r = min(x, min(z, y)) + 1;
    int ans = 0;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (Judge(mid))
            ans = mid, l = mid + 1;
        else 
            r = mid;
    }
    printf ("%d", ans);
}
------------------------------------------------------
Problem1110:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1e9 + 7;
const int Inv = 500000004;
int B[101] = {1, 8341501,16732001,25220501,33856001,42687501,51764001,61134501,70848001,80953501,91500001,102536501,114112001,126275501,139076001,152562501,166784001,181789501,197628001,214348501,232000001,250631501,270292001,291030501,312896001,335937501,360204001,385744501,412608001,440843501,470500001,501626501,534272001,568485501,604316001,641812501,681024001,721999501,764788001,809438501,856000001,904521501,955052001,7640494,62335994,119187494,178243994,239554494,303167994,369133494,437499994,508316494,581631994,657495494,735955994,817062494,900863994,987409494,76747987,168928487,263999987,362011487,463011987,567050487,674175987,784437487,897883987,14564480,134527980,257823480,384499980,514606480,648191980,785305480,925995980,70312473,218303973,370019473,525507973,684818473,847999973,15101466,186171966,361260466,540415966,723687466,911123966,102774459,298687959,498913459,703499959,912496459,125951952,343915452,566435952,793562452,25343945,261829445,503067945,749108445,999999945};
int main()
{
    int T = 5;
    while (T--)
    {
        int n;
        scanf ("%d", &n);
        int base = 10000000;
        int p;
        for (p = 1; p <= 100; p++)
            if (n < p * base) break;
        p--;
        long long ans = B[p];
        long long now = (1ll + p * base) * p % MOD * base % MOD * Inv % MOD + 1;
        for (int i = p * base + 1; i <= n; i++)
        {
            ans = (ans + now) % MOD;
            now = (now + i) % MOD;
        }
        printf ("%lld\n", ans);
    }
}
------------------------------------------------------
Problem1111:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
using namespace std;
int Num[10];
#define LL long long
LL C[20][20], g[20];
int c[20];
int f[7] = {0,1,2,3,5,8,13};
bool isf(int x)
{
    if (x == 0 || x == 1 || x == 2 || x == 3 || x == 5 || x == 8 || x == 13) return 1;
    return 0; 
}
vector<int> S;
map<vector<int>, LL> mp[20];
LL Query(int x, int y)
{
    if (x == 10)
    {
        if (y == 0) return 1;
        else return 0;
    }
    LL ans = 0;
    for (int i = 0; i <= 6; i++)
    {
        if (f[i] >= c[x])
        {
            if (f[i] - c[x] > y) break;
            ans += C[y][f[i] - c[x]] * Query(x + 1, y - (f[i] - c[x]));
        }
    }
    return ans;
}
LL Query(int x)
{
    for (int i = 0; i <= 13; i++) S[i] = 0;
    for (int i = 0; i <= 9; i++) S[c[i]]++;
    if (mp[x].count(S))
        return mp[x][S];
    return mp[x][S] = Query(0, x);
}
int a[20];
bool Check()
{
    for (int i = 0; i <= 9; i++) 
        if (!isf(c[i])) 
            return 0;
    return 1;
}
LL dfs(int x, int top)
{
    if (!top) return Query(x - 1);
    if (x == 1) return Check();
    LL ans = 0;
    for (int i = 0; i <= 9; i++)
    {
        if (top && a[x - 1] < i)
            break;
        c[i]++;
        ans += dfs(x - 1, top && (i == a[x - 1]));
        c[i]--;
    }
    return ans;
}
LL Q(LL x)
{
    if (!x) return 0;
    int len = 0;
    LL ans = 0;
    while (x) a[++len] = x % 10, x /= 10;
    for (int i = 1; i <= a[len]; i++) c[i]++, ans += dfs(len, i == a[len]), c[i]--;
    ans += g[len - 1];
    return ans;
}
int main()
{
    S.resize(14);
    C[0][0] = 1;
    for (int i = 1; i <= 19; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 19; j++)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    for (int i = 1; i <= 18; i++)
    {
        g[i] = Query(i) + g[i - 1];
        c[0]++;
        g[i] -= Query(i - 1);
        c[0]--;
    }
    int t = 5;
    while (t--)
    {
        LL n;
        scanf ("%lld", &n);
        LL l = 0, r = 4 * n;
        LL ans = 0;
        while(l <= r)
        {
            LL mid = l + r >> 1;
            if (Q(mid) < n)
                l = mid + 1;
            else
                r = mid - 1;
        }
        printf ("%lld\n", l);
    }
}
------------------------------------------------------
Problem1112:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 100005;
int f[N], g[N];
int main()
{
 	int n;
 	scanf ("%d", &n);
 	for (int i = 1; i <= n; i++)
	 	scanf ("%d", &f[i]), f[i] ^= f[i - 1];
 	for (int i = 1; i <= n; i++)
 		scanf ("%d", &g[i]), g[i] ^= g[i - 1];
    for (int i = 1; i <= n; i++)
    	printf ("%d ", g[i] ^ f[i]);
   	//while (1);
}

------------------------------------------------------
Problem1113:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[200005][2];
int n;
int get(int now, int pos)
{
 	if (a[pos][now] >= a[pos - 1][now] && a[pos][now] <= a[pos + 1][now]) return a[pos][now];
    if (a[pos][now] <= a[pos - 1][now] && a[pos][now] >= a[pos + 1][now]) return a[pos][now];
    if (a[pos - 1][now] >= a[pos][now] && a[pos - 1][now] <= a[pos + 1][now]) return a[pos - 1][now];
    if (a[pos - 1][now] <= a[pos][now] && a[pos - 1][now] >= a[pos + 1][now]) return a[pos - 1][now];
    if (a[pos + 1][now] >= a[pos - 1][now] && a[pos + 1][now] <= a[pos][now]) return a[pos + 1][now];
    if (a[pos + 1][now] <= a[pos - 1][now] && a[pos + 1][now] >= a[pos][now]) return a[pos + 1][now];
}
int main()
{
 	scanf ("%d", &n);
	int alle = 1;
 	for (int i = 1; i <= 2 * n - 1; i++)
	{
		scanf ("%d", &a[i][0]);
		if (a[i][0] != i) alle = 0;
	}
	if (alle) return printf ("%d", n), 0;
	if (n <= 1000)
	{
		int now = 0;
		for (int i = 1; i < n; i++)
		{
			now ^= 1;
			for (int j = i + 1; j <= 2 * n - i - 1; j++)
			{
				a[j][now] = get(now^1, j); 		 	
			}
		}
		printf ("%d", a[n][now]);
	}
	else
	{
		printf ("%d", get(0, n));
	}
}

------------------------------------------------------
Problem1115:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
struct point
{
    double x, y;
    double Max, Min;
    bool operator < (const point a) const
    {
        return x == a.x ? y < a.y : x < a.x;
    }
}a[6005];
int k, m;
int fa[6005];
int find(int x)
{
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
double dis(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
bool Judge(double mid)
{
    for (int i = 1; i <= k; i++)
    {
        fa[i] = i;
        a[i].Max = a[i].y + mid, a[i].Min = a[i].y - mid;
        if (a[i].Max >= m - mid && a[i].Min <= mid) return 0;
    }
    for (int i = 1; i <= k; i++)
    {
        for (int j = i + 1; j <= k; j++)
        {
            if (a[j].x - a[i].x > 2 * mid) break;
            if (dis(a[i], a[j]) <= 2 * mid && find(i) != find(j))
            {
                int J = find(j), I = find(i);
                if (a[J].Max < a[I].Max) a[J].Max = a[I].Max;
                if (a[J].Min > a[I].Min) a[J].Min = a[I].Min;
                fa[I] = J;
                if (a[J].Max >= m - mid && a[J].Min <= mid) return 0;
            }
        }
    }
    return 1;
}
int main()
{
    int n;
    scanf ("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++)
        scanf ("%lf%lf", &a[i].x, &a[i].y);
    sort(a + 1, a + k + 1);
    double l = 0, r = m / 2 + 1, mid;
    while (l + 1e-7 < r)
    {
        mid = (l + r) / 2;
        if (Judge(mid))
            l = mid;
        else
            r = mid;
    }
    printf ("%.9lf", l);
}

------------------------------------------------------
Problem1116:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2 * 1e5 + 5;
const int INF = 0x3f3f3f3f;
struct data
{
    int p, c, id;
    bool mark;
    bool operator < (const data &a) const{
        return p < a.p;
    }
}a[N];
int n;
int f[N];
int H[N << 2], Min[N << 2], lf[N << 2];
#ifndef lch
#define lch  l, m, rt << 1
#endif
#ifndef rch
#define rch m + 1, r, rt << 1 | 1
#endif
int Calc(int MaxH, int l, int r, int rt)
{
    if (l == r) return Min[rt];
    int m = l + r >> 1;
    if (H[rt << 1] < H[rt << 1 | 1]) return Calc(MaxH, rch);
    else
    {
        if (H[rt << 1 | 1] < MaxH) return Calc(MaxH, lch);
        else return min(lf[rt << 1], Calc(MaxH, rch));
    }
}
void Pushup(int l, int r, int rt)
{
    H[rt] = max(H[rt << 1], H[rt << 1 | 1]);
    int m = l + r >> 1;
    if (H[rt << 1 | 1] > H[rt << 1]) Min[rt] = Min[rt << 1 | 1], lf[rt << 1] = INF;
    else
        Min[rt] = min(lf[rt << 1] = Calc(H[rt << 1 | 1], lch), Min[rt << 1 | 1]);
}
int MH;
int Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        if (H[rt] < MH) return INF;
        else
        {
            int tmp = Calc(MH, l, r, rt);
            MH = H[rt];
            return tmp;
        }
    }
    int m = l + r >> 1;
    int ans = INF;
    if (R > m) ans = min(ans, Query(L, R, rch));
    if (L <= m) ans = min(ans, Query(L, R, lch));
    return ans;
}
void Update(int pos, int l, int r, int rt)
{
    if (l == r)
    {
        H[rt] = a[pos].p; Min[rt] = f[a[pos].id];
        return;
    }
    int m = l + r >> 1;
    if (a[pos].id <= m) Update(pos, lch);
    else Update(pos, rch);
    Pushup(l, r, rt);
}
int main()
{
    scanf("%d", &n);
    memset (lf, 0x3f, sizeof (lf));
    memset (Min, 0x3f, sizeof (Min));
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &a[i].p);
        a[i].id = i;
    }
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i].c);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    {
        MH = 0;
        int tmp = Query(1, a[i].id, 1, n, 1);
        if (tmp >= INF) f[a[i].id] = a[i].c;
        else f[a[i].id] = tmp + a[i].c;
        Update(i, 1, n, 1);
    }
    MH = 0;
    printf ("%d", Query(1, n, 1, n, 1));
}

------------------------------------------------------
Problem1117:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 5e5 + 5;
int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}
int c[N];
struct data
{
    int next, END;
}v[N];
int first[N], p, dep[N];
int que[N], cnt;
double ans[N];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
double K(int a, int b)
{
    return ((double)c[a] - c[b]) / (dep[a] - dep[b]);
}
void DFS(int rt, int len, int Dep)
{
    dep[rt] = Dep;
    int l = 1, r = len;
    int Ans = 1;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (mid == len) {Ans = len; break;}
        if (K(que[mid], que[mid + 1]) <= K(que[mid + 1], rt)) Ans = mid + 1, l = mid + 1;
        else r = mid - 1;
    }
    ans[rt] = -K(que[Ans], rt);
    Ans++;
    int tmp = que[Ans];
    que[Ans] = rt;
    for (int i = first[rt]; i != -1; i = v[i].next)
        DFS(v[i].END, Ans, Dep + 1);
    que[Ans] = tmp;
}
int main()
{
    int n;
    memset(first, -1, sizeof(first));
    n = read();
    for (int i = 1; i <= n; i++)
        c[i] = read();
    int a;
    for (int i = 2; i <= n; i++)
    {
        a = read();
        add(a, i);
    }
    DFS(1, 0, 0);
    for (int i = 2; i <= n; i++)
        printf ("%.10lf\n", ans[i]);
    // printf("%lf", (double)clock()/CLOCKS_PER_SEC);
}

------------------------------------------------------
Problem1118:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
int f[MAXN][MAXN], Sum[MAXN][MAXN];
const int MOD = 10000;
int main()
{
    // freopen("permut.in", "r", stdin);
    // freopen("permut.out", "w", stdout);
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        int n, k;
        scanf ("%d%d", &n, &k);
        memset(f, 0, sizeof (f));
        memset(Sum, 0, sizeof (Sum));
        f[1][0] = 1;
        for (int i = 0; i <= k; i++) Sum[1][i] = 1;
        for (int i = 2; i <= n; i++)
            for (int j = 0; j <= k; j++)
            {
                f[i][j] = (Sum[i - 1][j] - (j >= i ? Sum[i - 1][j - i] : 0) + MOD) % MOD;
                Sum[i][j] = (Sum[i][j - 1] + f[i][j]) % MOD;
            }
        printf("%d\n", f[n][k]);
    }
}

------------------------------------------------------
Problem1119:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int full = 11;
struct Trie
{
    struct Node
    {
        int s;
        Node *ch[2];
        Node()
        {
            s = 0;
            ch[0] = ch[1] = NULL;
        }
#define size(_) ((_)?(_)->s:0)
    }*root;
    Trie()
    {
        root = new Node();
    }
    void Insert(int x, int add)
    {
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            int next = (x >> i) & 1;
            if (rt->ch[next] == NULL)
                rt->ch[next] = new Node();
            rt = rt->ch[next];
            rt->s += add;
        }
    }
    int kth(int k)
    {
        Node *rt = root;
        int ret = 0;
        for (int i = full; i >= 0; i--)
        {
            if (k > size(rt->ch[0]))
            {
                k -= size(rt->ch[0]);
                ret |= 1 << i;
                if (!rt->ch[1]) break;
                rt = rt->ch[1];
            }
            else
                rt = rt->ch[0];
        }
        return ret;
    }
}root;
const int MAXN = 2005;
struct data
{
    int v, id, c;
    bool operator < (const data &a) const
    {
        return v == a.v ? id < a.id : v < a.v;
    }
}a[MAXN], Hash[MAXN];
int pos[MAXN];
int st[(MAXN << 1) + 200][12];
int Query(int l, int r)
{
    int d = r - l + 1;
    int k = 0;
    while ((1 << k) <= d) k++;
    k--;
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}
int main()
{
    // freopen("beautiful.in", "r", stdin);
    // freopen("beautiful.out", "w", stdout);
    int n;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i].v), a[i].id = i, Hash[i] = a[i];
    sort(Hash + 1, Hash + n + 1);
    for (int i = 1; i <= n; i++)
        a[i].c = lower_bound(Hash + 1, Hash + n + 1, a[i]) - Hash, pos[a[i].c] = a[i].id;
    int mid = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
            root.Insert(a[j].c, 1);
        for (int j = 1; j <= i; j++)
        {
            if (((i - j + 1) & 1))
            {
                mid = root.kth((i - j + 1) / 2 + 1);
                st[pos[mid]][0] = max(st[pos[mid]][0], (i - j + 1));
            }
            root.Insert(a[j].c, -1);
        }
    }
    for (int i = 1; i <= 11; i++)
        for (int j = 1; j <= n; j++)
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    int Q;
    scanf ("%d", &Q);
    int l, r;
    while (Q--)
    {
        scanf ("%d%d", &l, &r);
        printf("%d\n", Query(l, r));
    }
}

------------------------------------------------------
Problem1120:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int Num[65537];
int main()
{
    int n, x;
    char s[5];
    scanf ("%d", &n);
    while (n--)
    {
        scanf ("%s%d", s, &x);
        if (s[0] == 'a') Num[x]++;
        else if (s[0] == 'd') Num[x]--;
        else
        {
            int ans = Num[0];
            for (int i = x; i; i = (i - 1) & x)
                ans += Num[i];
            printf ("%d\n", ans);
        }
    }
}

------------------------------------------------------
Problem1124:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 100005;
struct edge
{
    int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int size[N], n, ans = -1;
void DFS(int rt, int fa)
{
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DFS(v[i].END, rt);
        if (size[v[i].END] == n >> 1) ans = i;
        size[rt] += size[v[i].END];
    }
}
int main()
{
    // freopen ("div.in", "r", stdin);
    // freopen ("div.out", "w", stdout);
    int a, b;
    n = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    if (n & 1) return printf ("-1"), 0;
    DFS(1, 0);
    if (ans == -1) printf ("-1");
    else printf ("%d", (ans >> 1) + 1);
    // fclose(stdin), fclose(stdout);
}
------------------------------------------------------
Problem1125:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e7 + 5;
const int MOD = 1e9 + 7;
long long F[MAXN];
long long pow_mod(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long C(long long n, long long m)
{
    if (n < m) return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
int main()
{
    // freopen("str.in", "r", stdin);
    // freopen("str.out", "w", stdout);
    int n;
    scanf ("%d", &n);
    int k = 0;
    F[0] = 1;
    for (int i = 1; i <= MAXN - 3; i++)
        F[i] = F[i - 1] * i % MOD;
    while ((1ll << k) <= n) k++; 
    k--;
    long long Ans = C(1 << k, (1 << (k + 1)) - n) * F[n] % MOD;    
    printf ("%lld", Ans);
    // fclose(stdin), fclose(stdout);
    // while (1);
}
------------------------------------------------------
Problem1126:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
long long f[5005][5005][2];
int MOD = 1e9 + 7;
int main()
{
    // freopen("val.in", "r", stdin);
    // freopen("val.out", "w", stdout);
    int n = read(), k = read();
    for (int i = 0; i <= k; i++) f[0][i][i == 0] = 1;
    for (int i = 1; i <= n; i++)
    {
        (f[i][0][1] += f[i - 1][1][0] + f[i - 1][1][1]) %= MOD;
        for (int j = 1; j <= k; j++)
        {
            if (j >= 2) (f[i][j][0] += f[i - 1][j - 2][0]) %= MOD;
            if (j >= 2) (f[i][j][1] += f[i - 1][j - 2][1]) %= MOD;
            if (j >= 1) (f[i][j][0] += f[i - 1][j - 1][0]) %= MOD;
            if (j >= 1) (f[i][j][1] += f[i - 1][j - 1][1]) %= MOD;
            if (j + 1 <= k) (f[i][j][0] += f[i - 1][j + 1][0]) %= MOD;
            if (j + 1 <= k) (f[i][j][1] += f[i - 1][j + 1][1]) %= MOD;
        }
    }
    int Ans = 0;
    for (int i = 0; i <= k; i++) (Ans += f[n][i][1]) %= MOD;
    printf ("%d", Ans);
    // fclose(stdin), fclose(stdout);
}
------------------------------------------------------
Problem1127:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <ctime>
#include <vector>
using namespace std;
int read()
{
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5 + 5;
struct point
{
    int x, y;
    bool operator < (const point &a) const 
    {
        return x == a.x ? y < a.y : x < a.x;
    }
    bool operator > (const point &a) const
    {
        return y == a.y ? x < a.x : y < a.y;
    }
    bool operator == (const point &a) const
    {
        return x == a.x && y == a.y;
    }
};
long long ans = 0;
struct data
{
    point a, b;
    void Read()
    {
        a.x = read(); a.y = read();
        b.x = read(); b.y = read();
        ans += (long long)2 * (b.x - a.x) * (b.y - a.y);
    }
    bool operator < (const data &c) const
    {
        return a == c.a ? b < c.b : a < c.a;
    }
}a[MAXN];
int Calc(int a, int b, int c, int d, int op)
{
    if (a <= c && b >= d) return (d - c + 1) * 2 - (a == c) - (b == d);
    if (a >= c && b <= d) return (b - a + 1) * 2 - (a == c) - (b == d);
    if (c <= b) 
    {
        if (a <= c && b <= d) return (b - c + 1) * 2 - (a == c) - (b == d);
    }
    if (a <= d)
    {
        if (a >= c && b >= d) return (d - a + 1) * 2 - (a == c) - (b == d);
    }
    if (c == b + 1) return 1;
    if (a == d + 1) return 1;
    return 0;
}
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i].Read();
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (a[j].a.x - 1 > a[i].b.x) break;
            if (a[j].a.x == a[i].b.x + 1)
            {
                ans += Calc(a[i].a.y, a[i].b.y, a[j].a.y, a[j].b.y, 1);
            }
            else if (a[j].a.y == a[i].b.y + 1)
            {
                ans += Calc(a[i].a.x, a[i].b.x, a[j].a.x, a[j].b.x, 0);
            }
            else if (a[j].b.x + 1 == a[i].a.x)
            {
                ans += Calc(a[i].a.y, a[i].b.y, a[j].a.y, a[j].b.y, 1);
            }
            else if (a[j].b.y + 1 == a[i].a.y)
            {
                ans += Calc(a[i].a.x, a[i].b.x, a[j].a.x, a[j].b.x, 0);
            }
        }
    }
    printf ("%lld", ans);
}
------------------------------------------------------
Problem1129:
#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long 
const int MOD = 1000000007;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int pow_mod(int a, int b)
{
    int ans = 1; 
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int w[1005];
int F[1005];
int C(int n, int m)
{
    if (n == m || !m) return 1;
    if (n < m) return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
signed main()
{
    // freopen("kat.in", "r", stdin);
    // freopen("kat.out", "w", stdout);
    int n, m, k;
    n = read(), m = read(), k = read();
    for (int i = 1; i <= m; i++)
        w[i] = read();
    if (n < k) return printf ("0"), 0;
    F[0] = 1;
    for (int i = 1; i <= 1000; i++)
        F[i] = F[i - 1] * i % MOD;
    int ans = 0;
    int Inv = pow_mod(m, MOD - 2) % MOD;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            ans = (ans + (((w[i] * pow_mod(Inv, j) % MOD) * C(k, j) % MOD) * pow_mod((i - 1) * Inv % MOD, k - j)) % MOD) % MOD;
        }
    }
    printf ("%lld", (ans * (n - k + 1) % MOD));
    // fclose(stdin), fclose(stdout);
    // while (1);
}
/*
2 2 2
1 2
750000007
*/

------------------------------------------------------
Problem1130:
#include <cstdio>
const int MAXN = 2005;
long long f[MAXN][MAXN], Sum;
int MOD;
int main()
{
    // freopen("rabbit.in", "r", stdin);
    // freopen("rabbit.out", "w", stdout);
    int n;
    scanf ("%d%d", &n, &MOD);
    f[1][1] = 1 % MOD;
    for (int i = 2; i <= n; i++)
    {
        Sum = 0;
        for (int j = 1; j <= i; j++)
        {
            Sum = (Sum + f[i - 1][i - j]) % MOD;
            f[i][j] = Sum;
        }
    }
    printf ("%lld", f[n][n] * 2 % MOD);
    // fclose(stdin);
    // fclose(stdout);
}

------------------------------------------------------
Problem1131:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char map[305][305];
int Num[60];
int main()
{
    // freopen("quilt.in", "r", stdin);
    // freopen("quilt.out", "w", stdout);
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        memset (Num, 0, sizeof (Num));
        int n, m;
        scanf ("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf ("%s", map[i] + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                Num[map[i][j] - 'a' + 1]++;
        int t1 = 0, t2 = 0;
        if ((n & 1) && (m & 1)) t1 = 1;
        if (n & 1) t2 += m;
        if (m & 1) t2 += n;
        t2 >>= 1;
        t2 -= t1;
        for (int i = 1; i <= 26; i++)
        {
            if (Num[i] & 1)
            {
                if (t1) t1 = 0,Num[i]--;
            }
            if (Num[i] % 4 != 0)
            {
                if (t2) t2--,Num[i] -= 2;
            }
            if (Num[i] % 4 == 0)
            {
                Num[i] = 0;
            }
        }
        bool flag = 0;
        for (int i = 1; i <= 26; i++)
            if (Num[i]) 
                flag = 1;
        printf ("%s\n", flag ? "No" : "Yes");
    }
    // fclose(stdin); fclose(stdout);
}
------------------------------------------------------
Problem1132:
// O(n)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
// char xch,xB[1<<15],*xS=xB,*xTT=xB;
// #define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
// inline int read()
// {
//     int x=0,f=1;char ch=getc();
//     while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
//     while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
//     return x*f;
// }
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 5000005;
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long f[MAXN], g[MAXN], Inv;
int dep[MAXN], S;
int d, P, q, t;
void dfs(int rt, int fa, int Dep)
{
    f[rt] = 0;
    dep[rt] = Dep;
    bool flag = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        flag = 1;
        dfs(v[i].END, rt, Dep + 1);
        (f[rt] += f[v[i].END]) %= MOD;
    }
    if (!flag) f[rt] = 1, S++;
    if (dep[rt] <= d) f[rt] = ((f[rt] * t % MOD) * Inv) % MOD;
}
long long Ans1 = 0;
void dfs1(int rt, int fa)
{
    if (rt == 1) g[1] = 0;
    else
    {
        if (dep[fa] <= d) g[rt] = (g[fa] + f[fa] - ((f[rt] * t) % MOD * Inv) % MOD + MOD) % MOD;
        else g[rt] = (g[fa] + f[fa] - f[rt] + MOD) % MOD;
        if (dep[rt] <= d) g[rt] = ((g[rt] * t) % MOD * Inv) % MOD;
    }
    int flag = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs1(v[i].END, rt);
        flag = 1;
    }
    if (!flag) (Ans1 += g[rt]) %= MOD;
}
int main()
{
    int n, a, b;
    n = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    d = read(), P = read(), q = read();
    t = q - P;
    Inv = pow_mod(q, MOD - 2) % MOD;
    dfs(1, 0, 0);
    dfs1(1, 0);
    printf ("%lld\n", ((long long)S * (S - 1) % MOD - Ans1 + MOD) % MOD);
    // printf ("%lld", Ans1);
    // while (1);
}
------------------------------------------------------
Problem1132:
// O(n)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read()
{
    int x=0,f=1;char ch=getc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}
//inline int read()
//{
//    int x=0,f=1;char ch=getchar();
//    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
//    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
//    return x*f;
//}
const int MAXN = 5000005;
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long f[MAXN], g[MAXN], Inv;
int dep[MAXN], S;
int d, P, q, t;
void dfs(int rt, int fa, int Dep)
{
    f[rt] = 0;
    dep[rt] = Dep;
    bool flag = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        flag = 1;
        dfs(v[i].END, rt, Dep + 1);
        (f[rt] += f[v[i].END]) %= MOD;
    }
    if (!flag) f[rt] = 1, S++;
    if (dep[rt] <= d) f[rt] = ((f[rt] * t % MOD) * Inv) % MOD;
}
long long Ans1 = 0;
void dfs1(int rt, int fa)
{
    if (rt == 1) g[1] = 0;
    else
    {
        if (dep[fa] <= d) g[rt] = (g[fa] + f[fa] - ((f[rt] * t) % MOD * Inv) % MOD + MOD) % MOD;
        else g[rt] = (g[fa] + f[fa] - f[rt] + MOD) % MOD;
        if (dep[rt] <= d) g[rt] = ((g[rt] * t) % MOD * Inv) % MOD;
    }
    int flag = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs1(v[i].END, rt);
        flag = 1;
    }
    if (!flag) (Ans1 += g[rt]) %= MOD;
}
int main()
{
    int n, a, b;
    n = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    d = read(), P = read(), q = read();
    t = q - P;
    Inv = pow_mod(q, MOD - 2) % MOD;
    dfs(1, 0, 0);
    dfs1(1, 0);
    printf ("%lld\n", ((long long)S * (S - 1) % MOD - Ans1 + MOD) % MOD);
    // printf ("%lld", Ans1);
    // while (1);
}
------------------------------------------------------
Problem1132:
// O(n)
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read()
{
    int x=0,f=1;char ch=getc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}
// inline int read()
// {
//     int x=0,f=1;char ch=getchar();
//     while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
//     while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
//     return x*f;
// }
const int MAXN = 5000005;
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long f[MAXN], g[MAXN], Inv;
int dep[MAXN], S;
int d, P, q, t;
void dfs(int rt, int fa, int Dep)
{
    f[rt] = 0;
    dep[rt] = Dep;
    bool flag = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        flag = 1;
        dfs(v[i].END, rt, Dep + 1);
        (f[rt] += f[v[i].END]) %= MOD;
    }
    if (!flag) f[rt] = 1, S++;
    if (dep[rt] <= d) f[rt] = ((f[rt] * t % MOD) * Inv) % MOD;
}
long long Ans1 = 0;
void dfs1(int rt, int fa)
{
    if (rt == 1) g[1] = 0;
    else
    {
        if (dep[fa] <= d) g[rt] = (g[fa] + f[fa] - ((f[rt] * t) % MOD * Inv) % MOD + MOD) % MOD;
        else g[rt] = (g[fa] + f[fa] - f[rt] + MOD) % MOD;
        if (dep[rt] <= d) g[rt] = ((g[rt] * t) % MOD * Inv) % MOD;
    }
    int flag = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs1(v[i].END, rt);
        flag = 1;
    }
    if (!flag) (Ans1 += g[rt]) %= MOD;
}
int main()
{
    int n, a, b;
    n = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    d = read(), P = read(), q = read();
    t = q - P;
    Inv = pow_mod(q, MOD - 2) % MOD;
    dfs(1, 0, 0);
    dfs1(1, 0);
    printf ("%lld\n", ((long long)S * (S - 1) % MOD - Ans1 + MOD) % MOD);
    // printf ("%lld", Ans1);
    // while (1);
}
------------------------------------------------------
Problem1134:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct edge
{
    int END, next, v;
}v[20005];
int first[10005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int ans = 0, k;
int fa[10005], size[10005];
int f[10005][10005];
int g[10005][10005];
int tmp[10005][2];
void DP(int rt, int fa)
{
    f[rt][1] = 0, g[rt][1] = 0;
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        DP(v[i].END, rt);
        for (int h = 1; h <= k; h++) tmp[h][0] = f[rt][h], tmp[h][1] = g[rt][h];
        for (int h = 1; h <= size[rt] && h <= k; h++)
        {
            for (int j = 1; j <= size[v[i].END] && j + h <= k; j++)
            {
                tmp[h + j][0] = min(tmp[h + j][0], f[rt][h] + f[v[i].END][j] + 2 * v[i].v);
                tmp[h + j][1] = min(tmp[h + j][1], f[rt][h] + g[v[i].END][j] + v[i].v);
                tmp[h + j][1] = min(tmp[h + j][1], g[rt][h] + f[v[i].END][j] + 2 * v[i].v);
            }
        }
        size[rt] += size[v[i].END];
        for (int h = 1; h <= k; h++) f[rt][h] = tmp[h][0], g[rt][h] = tmp[h][1];
    }
}
int main()
{
    // freopen("museum.in", "r", stdin);
    // freopen("museum.out", "w", stdout);
    int n, x;
    memset (first, -1, sizeof (first));
    scanf("%d%d%d", &n, &k, &x);
    int a, b, c;
    memset (f, 0x3f, sizeof(f));
    memset (g, 0x3f, sizeof(g));
    for (int i = 1; i < n; i++)
    {
        scanf ("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    ans = 0x3f3f3f3f;
    DP(x, 0);
    printf ("%d", min(g[x][k], f[x][k]));
}

------------------------------------------------------
Problem1135:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define int long long
using namespace std;
int prime[27] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
map<int, long long> mp[2000005];
map<pair<long long,long long>, int> Hash[26];
int C[21][21];
int Num[27], n, l, r, len;
long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}
void Update(long long &L, long long &R)
{
    int GCD = gcd(L, R);
    L /= GCD, R /= GCD;   
}
int DFS(int dep, long long L, long long R)
{
    Update(L, R);
    if (Hash[dep].count(pair<long long,long long>(L,R))) return Hash[dep][pair<long long,long long>(L,R)];
    if (dep == 3)
    {
        int ans = 0;
        for (int i = 0; i <= len; i++)
        {
            long long A = L << i, B = R << (len - i);
            Update(A, B);
            if (A > 2000000) continue;
            if (mp[A].count(B))
                ans += C[len][i] * mp[A][B];
        }
        return Hash[dep][pair<long long, long long>(L, R)] = ans;
    }
    int ans = 0;
    for (int i = 0; i <= Num[dep]; i++)
        ans += DFS(dep - 1, L * (i + 1), R * (Num[dep] - i + 1));
    return Hash[dep][pair<long long,long long>(L,R)] = ans;
}
int Ans[17] = {0,1,0,1,0,1,1,1,0,5,3,5,5,13,11,11,11};
signed main()
{
    // freopen("euler.in", "r", stdin);
    // freopen("euler.out", "w", stdout);
    scanf ("%lld", &n);
    if (n <= 16)
    {
        printf ("%lld", Ans[n]);
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        int m = i;
        for (int j = 1; j <= 25; j++)
            while (m % prime[j] == 0)
            {
                Num[j]++;
                m /= prime[j];
            }
    }
    for (int i = 0; i <= 20; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    for (int i = 0; i <= Num[1]; i++)
    {
        for (int j = 0; j <= Num[2]; j++)
        {
            for (int k = 0; k <= Num[3]; k++)
            {
                long long A = (i + 1) * (j + 1) * (k + 1);
                long long B = (Num[1] - i + 1) * (Num[2] - j + 1) * (Num[3] - k + 1);
                Update(A, B);
                mp[A][B]++;
            }
        }
    }
    // for (int i = 1; i <= 25; i++) printf ("%d%c", Num[i], " \n"[i == 25]);
    // while (1);
    for (int i = 25; i >= 1; i--)
    {
        if (Num[i] == 1 && Num[i + 1] == 0)
            r = i;
        else if (Num[i] != 1 && Num[i + 1] == 1)
        {
            l = i + 1;
            break;
        }
    }
    len = r - l + 1;
    printf ("%lld", DFS(l - 1, 1, 1) >> 1);
}

------------------------------------------------------
Problem1135:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define int long long
using namespace std;
int prime[27] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
map<int, long long> mp[2000005];
map<pair<long long,long long>, int> Hash[26];
int C[21][21];
int Num[27], n, l, r, len;
long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}
void Update(long long &L, long long &R)
{
    int GCD = gcd(L, R);
    L /= GCD, R /= GCD;   
}
int DFS(int dep, long long L, long long R)
{
    Update(L, R);
    if (Hash[dep].count(pair<long long,long long>(L,R))) return Hash[dep][pair<long long,long long>(L,R)];
    if (dep == 3)
    {
        int ans = 0;
        for (int i = 0; i <= len; i++)
        {
            long long A = L << i, B = R << (len - i);
            Update(A, B);
            if (A > 2000000) continue;
            if (mp[A].count(B))
                ans += C[len][i] * mp[A][B];
        }
        return Hash[dep][pair<long long, long long>(L, R)] = ans;
    }
    int ans = 0;
    for (int i = 0; i <= Num[dep]; i++)
        ans += DFS(dep - 1, L * (i + 1), R * (Num[dep] - i + 1));
    return Hash[dep][pair<long long,long long>(L,R)] = ans;
}
int Ans[17] = {0,1,0,1,0,1,1,1,0,5,3,5,5,13,11,11,11};
signed main()
{
    // freopen("euler.in", "r", stdin);
    // freopen("euler.out", "w", stdout);
    scanf ("%lld", &n);
    if (n <= 16)
    {
        printf ("%lld", Ans[n]);
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        int m = i;
        for (int j = 1; j <= 25; j++)
            while (m % prime[j] == 0)
            {
                Num[j]++;
                m /= prime[j];
            }
    }
    for (int i = 0; i <= 20; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    for (int i = 0; i <= Num[1]; i++)
    {
        for (int j = 0; j <= Num[2]; j++)
        {
            for (int k = 0; k <= Num[3]; k++)
            {
                long long A = (i + 1) * (j + 1) * (k + 1);
                long long B = (Num[1] - i + 1) * (Num[2] - j + 1) * (Num[3] - k + 1);
                Update(A, B);
                mp[A][B]++;
            }
        }
    }
    // for (int i = 1; i <= 25; i++) printf ("%d%c", Num[i], " \n"[i == 25]);
    // while (1);
    for (int i = 25; i >= 1; i--)
    {
        if (Num[i] == 1 && Num[i + 1] == 0)
            r = i;
        else if (Num[i] != 1 && Num[i + 1] == 1)
        {
            l = i + 1;
            break;
        }
    }
    len = r - l + 1;
    printf ("%lld", DFS(l - 1, 1, 1) >> 1);
}

------------------------------------------------------
Problem1136:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <ctime>
using namespace std;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read()
{
    int x=0,f=1;char ch=getc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}
// inline int read()
// {
//     int x=0,f=1;char ch=getchar();
//     while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
//     while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
//     return x*f;
// }
struct Node
{
    Node *ch[2];
    int Sum;
    Node()
    {
        ch[0] = ch[1] = NULL;
        Sum = 0;
    }
#define size(_) ((_)?(_)->Sum:0)
    void* operator new(size_t);
}*root, *C, *mempool;
void* Node::operator new(size_t)
{
    if (C == mempool)
    {
        C = new Node[1 << 15];
        mempool = C + (1 << 15);
    }
    return C++;
}
void Update(int x, int c, int l, int r, Node *&rt)
{
    if (rt == NULL) rt = new Node();
    rt->Sum += c;
    if (l == r) return;
    int m = l + r >> 1;
    if (x <= m) Update(x, c, l, m, rt->ch[0]);
    else Update(x, c, m + 1, r, rt->ch[1]);
}
int Query(int l, int r, Node *rt)
{
    if (!rt) return l;
    if (l == r) return l;
    int m = l + r >> 1;
    if (size(rt->ch[0]) < m - l + 1) return Query(l, m, rt->ch[0]);
    else return Query(m + 1, r, rt->ch[1]);
}
int Q[10000005], h = 1, t = 0;
int main()
{
    // freopen ("knowledge.in", "r", stdin);
    // freopen ("knowledge.out", "w", stdout);
    int m, type;
    m = read(), type = read();
    int op, x, lastans = 0;
    while (m--)
    {
        op = read();
        if (op == 1)
        {
            x = read();
            if (type) x ^= lastans;
            Update(x, 1, 0, 0x7fffffff, root);
        }
        else if (op == 2)
        {
            x = read();
            if (type) x ^= lastans;
            Q[++t] = x;
            Update(x, -1, 0, 0x7fffffff, root);
        }
        else if (op == 3)
        {
            x = Q[h++];
            Update(x, 1, 0, 0x7fffffff, root);
        }
        else
        {
            printf ("%d\n", lastans = Query(0, 0x7fffffff, root));
        }
    }
}
------------------------------------------------------
Problem1136:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <ctime>
using namespace std;
// char xch,xB[1<<15],*xS=xB,*xTT=xB;
// #define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
// inline int read()
// {
//     int x=0,f=1;char ch=getc();
//     while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
//     while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
//     return x*f;
// }
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct Node
{
    Node *ch[2];
    int Sum;
    Node()
    {
        ch[0] = ch[1] = NULL;
        Sum = 0;
    }
#define size(_) ((_)?(_)->Sum:0)
    void* operator new(size_t);
}*root, *C, *mempool;
void* Node::operator new(size_t)
{
    if (C == mempool)
    {
        C = new Node[1 << 15];
        mempool = C + (1 << 15);
    }
    return C++;
}
void Update(int x, int c, int l, int r, Node *&rt)
{
    if (rt == NULL) rt = new Node();
    rt->Sum += c;
    if (l == r) return;
    int m = l + r >> 1;
    if (x <= m) Update(x, c, l, m, rt->ch[0]);
    else Update(x, c, m + 1, r, rt->ch[1]);
}
int Query(int l, int r, Node *rt)
{
    if (!rt) return l;
    if (l == r) return l;
    int m = l + r >> 1;
    if (size(rt->ch[0]) < m - l + 1) return Query(l, m, rt->ch[0]);
    else return Query(m + 1, r, rt->ch[1]);
}
int Q[10000005], h = 1, t = 0;
int main()
{
    // freopen ("knowledge.in", "r", stdin);
    // freopen ("knowledge.out", "w", stdout);
    int m, type;
    m = read(), type = read();
    int op, x, lastans = 0;
    while (m--)
    {
        op = read();
        if (op == 1)
        {
            x = read();
            if (type) x ^= lastans;
            Update(x, 1, 0, 0x7fffffff, root);
        }
        else if (op == 2)
        {
            x = read();
            if (type) x ^= lastans;
            Q[++t] = x;
            Update(x, -1, 0, 0x7fffffff, root);
        }
        else if (op == 3)
        {
            x = Q[h++];
            Update(x, 1, 0, 0x7fffffff, root);
        }
        else
        {
            printf ("%d\n", lastans = Query(0, 0x7fffffff, root));
        }
    }
}
------------------------------------------------------
Problem1137:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
const int MAXN = 300005;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read()
{
    int x=0,f=1;char ch=getc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
struct data
{
    int v, cnt;
    data(int c = 0, int cn = 0)
    {
        v = c, cnt = cn;
    }
    bool operator < (const data &a) const
    {
        return cnt == a.cnt ? v < a.v : cnt < a.cnt;
    }
};
vector<data> Add[MAXN], rm[MAXN];
set<data> st[MAXN];
long long ans;
int C[MAXN], Ad[MAXN];
bool died;
void dfs(int rt, int fa)
{
    set<data>::iterator it;
    for (int i = 0; i < Add[rt].size(); i++)
        st[rt].insert(Add[rt][i]);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        if (died) return;
        if (st[v[i].END].size() > st[rt].size())
            swap(st[v[i].END], st[rt]), swap(Ad[v[i].END], Ad[rt]);
        for (it = st[v[i].END].begin(); it != st[v[i].END].end(); it++)
            st[rt].insert(data(it->v, C[it->v] = it->cnt - Ad[v[i].END] + Ad[rt]));
    }
    for (int i = 0; i < rm[rt].size(); i++)
        st[rt].erase(data(rm[rt][i].v, C[rm[rt][i].v]));
    if (rt == 1) return;
    if (st[rt].empty()) {died = 1; return;}
    ans += st[rt].begin()->cnt - Ad[rt];
    Ad[rt] += st[rt].begin()->cnt - Ad[rt];
}
signed main()
{
    int n = read(), m = read(), a, b, c;
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    for (int i = 1; i <= m; i++)
    {
        a = read(), b = read(), c = read();
        Add[a].push_back(data(i, c));
        rm[b].push_back(data(i, c));
        C[i] = c;
    }
    dfs(1, 0);
    if (died) printf ("-1");
    else printf ("%lld", ans);
}
------------------------------------------------------
Problem1139:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long F[61];
long long LCA(long long a, long long b)
{
	int t1 = 59, t2 = 59;
    while (a != b)
    {
    	if (a < b) swap(a, b), swap(t1, t2);
    	while (t1 && F[t1] >= a) t1--;
    	a -= F[t1];
    }
    return a;
}
int main()
{
    int m;
    scanf ("%d", &m);
    F[1] = 1; F[2] = 1;
    for (int i = 3; i <= 60; i++)
        F[i] = F[i - 1] + F[i - 2];
    long long a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%lld%lld", &a, &b);
        printf ("%lld\n", LCA(a, b));
    }
}
------------------------------------------------------
Problem1140:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 3e5 + 5;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
// #define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
// inline int read()
// {
//     int x=0,f=1;char ch=getc();
//     while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
//     while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
//     return x*f;
// }
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int full = 19;
int C[N];
struct Trie
{
    struct Node
    {
        int s;
        Node *ch[2];
        Node()
        {
            s = 0;
            ch[0] = ch[1] = NULL; 
        }
#define size(_) ((_)?(_)->s: 0)
    }*root;
    Trie()
    {
        root = new Node();
    }
    void Insert(int x, int c)
    {
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            int nxt = (x >> i) & 1;
            if (rt->ch[nxt] == NULL)
                rt->ch[nxt] = new Node();
            rt = rt->ch[nxt];
            rt->s += c;
        }
    }
    int Rank(int x)
    {
        int res = 0;
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            bool next = x >> i & 1;
            if (next) res += size(rt->ch[0]);
            if (!rt->ch[next])
                break;
            rt = rt->ch[next];
        }
        return res;
    }
}root[N];
int Query(int l, int r, int x)
{
    return root[x].Rank(r + 1) - root[x].Rank(l);
}
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
    {
        C[i] = read();
        root[C[i]].Insert(i, 1);
    }
    int op, x, l, r;
    for (int i = 1; i <= m; i++)
    {
        op = read();
        if (op == 1)
        {
            l = read(), r = read();
            x = read();
            printf ("%d\n", Query(l, r, x));
        }
        else
        {
            x = read();
            root[C[x]].Insert(x, -1);
            root[C[x]].Insert(x + 1, 1);
            root[C[x + 1]].Insert(x + 1, -1);
            root[C[x + 1]].Insert(x, 1);
            swap(C[x + 1], C[x]);
        }
    }
    // while (1);
}
------------------------------------------------------
Problem1141:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <cmath>
#include <vector>
using namespace std;
const int N = 131075;
int a[N];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
vector<int> st[(N << 1) + 200];
int fa[(N << 1) + 200];
int ans[N], cnt = 0;
int find(int x)
{
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
int main()
{
    int n = read(), k = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    if (k == 1)
    {
    	ans[0] = n;
        for (int i = n; i >= 1; i--)
        {
            bool flag = 0;
            for (int j = sqrt(a[i]) + 1; j <= 512; j++)
                if (st[j * j - a[i]].size())
                    flag = 1;
            if (flag)
            {
                ans[++cnt] = i;
            	for (int j = ans[cnt] + 1; j <= ans[cnt - 1]; j++)
					st[a[j]].clear();
            }
            st[a[i]].push_back(1);
         }
        printf ("%d\n", cnt + 1);
        for (int i = cnt; i >= 1; i--)
            printf ("%d ", ans[i]);
        printf("\n");
    }
    else
    {
        for (int i = 1; i <= 2 * N; i++)
        	fa[i] = i;
        ans[0] = n;
		for (int i = n; i >= 1; i--)
        {
        	bool flag = 0;
        	for (int j = sqrt(a[i]) + 1; j <= 512; j++)
        		if (st[j * j - a[i]].size())
    			{
    				int p = j * j - a[i];	
					for (int k = 0; k < st[p].size(); k++)
					{
						if (find(i) == find(st[p][k]))
    					{
    						flag = 1;
    						break;
						}
						fa[find(i)] = find(st[p][k] + N);
						fa[find(st[p][k])] = find(i + N);
 					}
 					if (flag) break;
				}
			if (flag) 
			{
				ans[++cnt] = i;
				for (int j = ans[cnt] + 1; j <= ans[cnt - 1]; j++)
					st[a[j]].clear();
			}
			st[a[i]].push_back(i);
	    }
	    printf ("%d\n", cnt + 1);
        for (int i = cnt; i >= 1; i--)
            printf ("%d ", ans[i]);
        printf("\n");
    }
    // while(1);
}
------------------------------------------------------
Problem1145:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[1000005];
int n, k;
void to_do(int pos, int op, int t)
{
    if (((k - t + op) & 1) == 1) s[pos] = '2', s[pos + 1] = '2', s[pos + 2] = '3';
    else s[pos] = '2', s[pos + 1] = '3', s[pos + 2] = '3';
}
int main()
{
    // freopen ("trans.in", "r", stdin);
    // freopen ("trans.out", "w", stdout);
    while (scanf("%d%d", &n, &k) != EOF)
    {
        scanf ("%s", s + 1);
        s[n + 1] = '\0';
        if (n <= 1000 && k <= 1000)
        {
            for (int t = 1; t <= k; t++)
            {
                int i;
                for (i = 1; i <= n; i++)
                {
                    if (s[i] == '2' && s[i + 1] == '3') 
                    {
                        if (i & 1) s[i + 1] = '2';
                        else s[i] = '3';
                        break;
                    }
                }
                if (i == n + 1) break;
            }
        }
        else
        {
            int t = 0;
            for (int i = 1; i <= n && t < k; i++)
            {
                if (s[i] == '2' && s[i + 1] == '3')
                {
                    if (i & 1)
                    {
                        if (s[i + 2] == '3') 
                        {
                            to_do(i, 0, t);
                            break;
                        }
                        else s[i + 1] = '2';
                        t++; 
                    }
                    else
                    {
                        if (s[i - 1] == '2')
                        {
                            to_do(i - 1, 1, t);
                            break;
                        }
                        else s[i] = '3';
                        t++;
                    }
                }
            }
        }
        printf ("%s\n", s + 1);
    }
    // fclose(stdin), fclose(stdout);
    return 0;
}
------------------------------------------------------
Problem1146:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int mp[205][6];
bool Use[205][6], Q[205][6];
int ans = 0, n, Max;
int f[205][2005][6];
int g[2005][6][6];
int main()
{
    // freopen ("snakevsblock.in", "r", stdin);
    // freopen ("snakevsblock.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 5; j++)
        {
            mp[i][j] = read();
            if (mp[i][j] > 0) Max += mp[i][j];
        }
    int m = read(), a, b;
    for (int i = 1; i <= m; i++)
        a = read(), b = read(), Q[a][b] = 1;
    memset (f, 0x80, sizeof (f));
    Max += 4;
    f[0][4][3] = 0;
    for (int i = 1; i <= n; i++)
    {
        memset (g, 0x80, sizeof (g));
        for (int j = 0; j <= Max; j++)
            for (int k = 1; k <= 5; k++)
                if (j >= mp[i][k])
                    g[j][k][k] = f[i - 1][j - mp[i][k]][k] + max(-mp[i][k], 0);
        for (int l = 2; l <= 5; l++)
            for (int k = 1; k <= 5 - l + 1; k++)
                for (int j = 0; j <= Max; j++)
                {
                    if (!Q[i][k] && j >= mp[i][k]) g[j][k][k + l - 1] = max(g[j][k][k + l - 1], g[j - mp[i][k]][k + 1][k + l - 1] + max(-mp[i][k], 0));
                    if (!Q[i][k + l - 2] && j >= mp[i][k + l - 1]) g[j][k][k + l - 1] = max(g[j][k][k + l - 1], g[j - mp[i][k + l - 1]][k][k + l - 2] + max(-mp[i][k + l - 1], 0));
                }
        for (int j = 0; j <= Max; j++)
            for (int k = 1; k <= 5; k++)
                for (int l = 1; l <= k; l++)
                    for (int r = k; r <= 5; r++)
                        f[i][j][k] = max(g[j][l][r], f[i][j][k]);
        for (int j = 0; j <= Max; j++)
            for (int k = 1; k <= 5; k++)
                ans = max(ans, f[i][j][k]);
    }
    printf ("%d", ans);
}
------------------------------------------------------
Problem1147:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 1e5 + 5;
struct edge
{
    int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int f[N << 2][17];
int dep[N];
int L[N], R[N], cnt;
void dfs(int rt, int fa, int Dep)
{
    L[rt] = ++cnt;
    dep[rt] = Dep;
    f[rt][0] = fa;
    for (int i = 1; i <= 16; i++)
        f[rt][i] = f[f[rt][i - 1]][i - 1];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt, Dep + 1);
    }
    R[rt] = ++cnt;
}
int LCA(int a, int b)
{
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 16; i >= 0; i--)
        if (d & (1 << i))
            d -= (1 << i), a = f[a][i];
    if (a == b) return a;
    for (int i = 16; i >= 0; i--)
        if (f[a][i] != f[b][i])
            a = f[a][i], b = f[b][i];
    return f[a][0];
}
struct data
{
    int a, b, lca;
    bool operator < (const data &c) const 
    {
        return dep[lca] > dep[c.lca];
    }
}Query[N * 3];
int Sum[N << 1];
#define lowbit(_) ((_)&(-_))
void U(int x, int c)
{
    for (int i = x; i <= cnt; i += lowbit(i))
        Sum[i] += c;
}
int Q(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
int Ans[N];
int main()
{
    // freopen("ping.in", "r", stdin);
    // freopen("ping.out", "w", stdout);
    int n = read(), m = read();
    memset (first, -1, sizeof (first));
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    dfs(1, 0, 0);
    int k = read();
    for (int i = 1; i <= k; i++) 
    {
        Query[i].a = read();
        Query[i].b = read();
        Query[i].lca = LCA(Query[i].a, Query[i].b);
    }
    sort(Query + 1, Query + k + 1);
    int ans = 0;
    for (int i = 1; i <= k; i++)
    {
        if (Q(L[Query[i].a]) + Q(L[Query[i].b]) - Q(L[Query[i].lca]) - Q(L[Query[i].lca] - 1)) continue;
        U(L[Query[i].lca], 1), U(R[Query[i].lca], -1);
        Ans[++ans] = Query[i].lca;
    }
    printf ("%d\n", ans);
    for (int i = 1; i <= ans; i++)
        printf ("%d ", Ans[i]);
    // fclose(stdin), fclose(stdout);
    return 0;
}
------------------------------------------------------
Problem1148:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 1000005;
struct edge
{
    int S, END, next, v, Need;
}v[N << 1];
int first[N], p;
void add(int a, int b, int c, int d)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    v[p].Need = d;
    first[a] = p++;
}
bool vis[N];
bool lst[N];
int ans = 0;
void dfs(int rt, int fa)
{
    int S = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        if (v[i].v == 0 && v[i].Need == 1)
            S += 1;
        else if (v[i].Need == 0) 
            S += lst[v[i].END];
        else
            ans += lst[v[i].END];
    }
    ans += S / 2;
    lst[rt] = S & 1;
}
int main()
{
    // freopen ("tiger.in", "r", stdin);
    // freopen ("tiger.out", "w", stdout);
    int n = read();
    memset (first, -1, sizeof (first));
    int x,y,z;
    for (int i = 2; i <= n; i++)
    {
        x = read(), y = read(), z = read();
        add(i, x, y ? 1 : 0, z ? 1 : 0);
        add(x, i, y ? 1 : 0, z ? 1 : 0);
    }
    dfs(1, 0);
    printf ("%d", ans + lst[1]);
    // fclose(stdin), fclose(stdout);
    return 0;
}
------------------------------------------------------
Problem1149:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int MOD = 1e9 + 7;
int n, m;
char Mp[1005][1005];
long long F[1005][1005];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int dx[4] = {0, 0, 1, -1},
    dy[4] = {1, -1, 0, 0};
int ans = 0;
bool Mark[10][10];
bool vis[10][10];
bool Judge(int a, int b)
{
    if (a > n || a < 1)
        return 0;
    if (b > m || b < 1)
        return 0;
    if (vis[a][b])
        return 0;
    return 1;
}
bool Judge()
{
    memset(vis, 0, sizeof(vis));
    int Wx = 0, Wy = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (Mark[i][j] == 0)
                Wx = i, Wy = j;
    queue<pair<int, int> > Q;
    Q.push(pair<int, int>(Wx, Wy));
    vis[Wx][Wy] = 1;
    while (!Q.empty())
    {
        pair<int, int> t = Q.front();
        Q.pop();
        for (int i = 0; i <= 3; i++)
        {
            if (!Judge(t.first + dx[i], t.second + dy[i]) || Mark[t.first + dx[i]][t.second + dy[i]])
                continue;
            vis[t.first + dx[i]][t.second + dy[i]] = 1;
            Q.push(pair<int, int>(t.first + dx[i], t.second + dy[i]));
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (Mark[i][j] == 0 && !vis[i][j])
                return 0;
    Wx = 0, Wy = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (Mark[i][j] == 1)
                Wx = i, Wy = j;
    Q.push(pair<int, int>(Wx, Wy));
    vis[Wx][Wy] = 1;
    while (!Q.empty())
    {
        pair<int, int> t = Q.front();
        Q.pop();
        for (int i = 0; i <= 3; i++)
        {
            if (!Judge(t.first + dx[i], t.second + dy[i]) || !Mark[t.first + dx[i]][t.second + dy[i]])
                continue;
            vis[t.first + dx[i]][t.second + dy[i]] = 1;
            Q.push(pair<int, int>(t.first + dx[i], t.second + dy[i]));
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (Mark[i][j] == 1 && !vis[i][j])
                return 0;
    for (int i = 1; i <= n; i++)
    {
        int flag = 1;
        for (int j = 2; j <= m; j++)
        {
            if (Mark[i][j] != Mark[i][j - 1] && flag)
                flag = 0;
            else if (Mark[i][j] != Mark[i][j - 1])
                return 0;
        }
    }
    for (int j = 1; j <= m; j++)
    {
        int flag = 1;
        for (int i = 2; i <= n; i++)
        {
            if (Mark[i][j] != Mark[i - 1][j] && flag)
                flag = 0;
            else if (Mark[i][j] != Mark[i - 1][j])
                return 0;
        }
    }
    return 1;
}
void dfs(int x, int y)
{
    if (x == n + 1)
    {
        if (Judge())
            ans++;
        return;
    }
    if (Mp[x][y] != '?')
    {
        if (y == m)
        {
            if (Mp[x][y] == 'W')
            {
                Mark[x][y] = 1;
                dfs(x + 1, 1);
            }
            else
                dfs(x + 1, 1);
        }
        else
        {
            if (Mp[x][y] == 'W')
            {
                Mark[x][y] = 1;
                dfs(x, y + 1);
            }
            else
                dfs(x, y + 1);
        }
    }
    else
    {
        if (y == m)
        {
            Mark[x][y] = 1;
            dfs(x + 1, 1);
            Mark[x][y] = 0;
            dfs(x + 1, 1);
        }
        else
        {
            Mark[x][y] = 1;
            dfs(x, y + 1);
            Mark[x][y] = 0;
            dfs(x, y + 1);
        }
    }
}
int Min[1005], Max[1005];
int Sum1[1005], Sum2[1005], Sum3[1005], Sum4[1005];
int SumB, SumM;
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        scanf("%s", Mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            SumB += Mp[i][j] == 'B', SumM += Mp[i][j] == 'W';
    // memset (Min, -1, sizeof (Min));
    memset (Max, -1, sizeof (Max));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (Mp[i][j] == 'B' && Max[i] == -1)
                Max[i] = j - 1;
            if (Mp[i][j] == 'W')
                Min[i] = j;
        }
    }
    for (int i = 1; i <= n; i++)
        if (Max[i] == -1)
            Max[i] = m;
    int ans = 0;
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = 0; k <= j; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    memset(F, 0, sizeof(F));
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = j; k <= m; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    memset(Max, -1, sizeof(Max));
    memset(Min, 0, sizeof(Min));
    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= 1; j--)
        {
            if (Mp[i][j] == 'B' && Max[i] == -1)
                Max[i] = m - j;
            if (Mp[i][j] == 'W')
                Min[i] = m - j + 1;
        }
    }
    for (int i = 1; i <= n; i++)
        if (Max[i] == -1)
            Max[i] = m;
    memset(F, 0, sizeof(F));
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = 0; k <= j; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    memset(F, 0, sizeof(F));
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = j; k <= m; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    int t = 0;
    for (int i = 1; i <= n; i++)
    {
        Sum1[i] = Sum1[i - 1], Sum2[i] = Sum2[i - 1];
        for (int j = 1; j <= m; j++)
        {
            Sum1[i] += Mp[i][j] == 'W';
            Sum2[i] += Mp[i][j] == 'B';
        }
        if (Sum1[i] == SumM && Sum2[i] == 0) t++;
        if (Sum1[i] == 0 && Sum2[i] == SumB) t++;
    }
    for (int j = 0; j <= m; j++)
    {
        if (j != 0)
            Sum3[j] = Sum3[j - 1], Sum4[j] = Sum4[j - 1];
        for (int i = 1; i <= n; i++)
        {
            Sum3[j] += Mp[i][j] == 'W';
            Sum4[j] += Mp[i][j] == 'B';
        }
        if (Sum3[j] == SumM && Sum4[j] == 0) t++;
        if (Sum3[j] == 0 && Sum4[j] == SumB) t++;
    }
    printf("%d", (ans - t + MOD) % MOD);
    // while (1);
}
------------------------------------------------------
Problem1149:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int MOD = 1e9 + 7;
int n, m;
char Mp[1005][1005];
long long F[1005][1005];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int Min[1005], Max[1005];
int Sum1[1005], Sum2[1005], Sum3[1005], Sum4[1005];
int SumB, SumM;
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        scanf("%s", Mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            SumB += Mp[i][j] == 'B', SumM += Mp[i][j] == 'W';
    // memset (Min, -1, sizeof (Min));
    memset (Max, -1, sizeof (Max));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (Mp[i][j] == 'B' && Max[i] == -1)
                Max[i] = j - 1;
            if (Mp[i][j] == 'W')
                Min[i] = j;
        }
    }
    for (int i = 1; i <= n; i++)
        if (Max[i] == -1)
            Max[i] = m;
    int ans = 0;
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = 0; k <= j; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    memset(F, 0, sizeof(F));
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = j; k <= m; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    memset(Max, -1, sizeof(Max));
    memset(Min, 0, sizeof(Min));
    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= 1; j--)
        {
            if (Mp[i][j] == 'B' && Max[i] == -1)
                Max[i] = m - j;
            if (Mp[i][j] == 'W')
                Min[i] = m - j + 1;
        }
    }
    for (int i = 1; i <= n; i++)
        if (Max[i] == -1)
            Max[i] = m;
    memset(F, 0, sizeof(F));
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = 0; k <= j; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    memset(F, 0, sizeof(F));
    for (int i = Min[1]; i <= Max[1]; i++)
        F[1][i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = Min[i]; j <= Max[i]; j++)
            for (int k = j; k <= m; k++)
                (F[i][j] += F[i - 1][k]) %= MOD;
    for (int i = Min[n]; i <= Max[n]; i++)
        (ans += F[n][i]) %= MOD;
    int t = 0;
    for (int i = 1; i <= n; i++)
    {
        Sum1[i] = Sum1[i - 1], Sum2[i] = Sum2[i - 1];
        for (int j = 1; j <= m; j++)
        {
            Sum1[i] += Mp[i][j] == 'W';
            Sum2[i] += Mp[i][j] == 'B';
        }
        if (Sum1[i] == SumM && Sum2[i] == 0) t++;
        if (Sum1[i] == 0 && Sum2[i] == SumB) t++;
    }
    for (int j = 0; j <= m; j++)
    {
        if (j != 0)
            Sum3[j] = Sum3[j - 1], Sum4[j] = Sum4[j - 1];
        for (int i = 1; i <= n; i++)
        {
            Sum3[j] += Mp[i][j] == 'W';
            Sum4[j] += Mp[i][j] == 'B';
        }
        if (Sum3[j] == SumM && Sum4[j] == 0) t++;
        if (Sum3[j] == 0 && Sum4[j] == SumB) t++;
    }
    printf("%d", (ans - t + MOD) % MOD);
    // while (1);
}
------------------------------------------------------
Problem1150:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1e9 + 7;
#define int long long
struct Matrix
{
    long long a[1005];
    int n;
    Matrix(int x = 0)
    {
        n = x;
        memset (a, 0, sizeof (a));
    }
    long long &operator[](int x)
    {
        return a[x];
    }
    const long long operator[](int x) const
    {
        return a[x];
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix ans(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                (ans[i] += a[j] * b[(i - j + n) % n] % MOD) %= MOD;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans(n), a = *this;
        ans[0] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}F[1005];
signed main()
{
    int n, m;
    scanf ("%lld%lld", &n, &m);
    F[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        F[i + 1].n = n;
        for (int j = 0; j < n; j++)
        {
            (F[i + 1][(j + i + 1) % n] += F[i][j]) %= MOD;
            if ((j + i + 1) % n != (j - i - 1 + n) % n)
                (F[i + 1][(j - i - 1 + n) % n] += F[i][j]) %= MOD;
        }
    }
    return printf ("%lld", ((F[n] ^ (m / n)) * F[m % n])[0]), 0;
}
------------------------------------------------------
Problem1150:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1e9 + 7;
#define int long long
struct Matrix
{
    long long a[1005];
    int n;
    Matrix(int x = 0)
    {
        n = x;
        memset (a, 0, sizeof (a));
    }
    inline long long &operator[](int x)
    {
        return a[x];
    }
    inline const long long operator[](int x) const
    {
        return a[x];
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix ans(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                (ans[i] += a[j] * b[(i - j + n) % n] % MOD) %= MOD;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans(n), a = *this;
        ans[0] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}F[1005];
signed main()
{
    int n, m;
    scanf ("%lld%lld", &n, &m);
    F[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        F[i + 1].n = n;
        for (int j = 0; j < n; j++)
        {
            (F[i + 1][(j + i + 1) % n] += F[i][j]) %= MOD;
            if ((j + i + 1) % n != (j - i - 1 + n) % n)
                (F[i + 1][(j - i - 1 + n) % n] += F[i][j]) %= MOD;
        }
    }
    return printf ("%lld", ((F[n] ^ (m / n)) * F[m % n])[0]), 0;
}
------------------------------------------------------
Problem1150:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1e9 + 7;
struct Matrix
{
    long long a[1005];
    int n;
    Matrix(int x = 0)
    {
        n = x;
        memset (a, 0, sizeof (a));
    }
    inline long long &operator[](int x)
    {
        return a[x];
    }
    inline const long long operator[](int x) const
    {
        return a[x];
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix ans(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                (ans[i] += a[j] * b[(i - j + n) % n] % MOD) %= MOD;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans(n), a = *this;
        ans[0] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
}F[1005];
signed main()
{
    int n, m;
    scanf ("%d%d", &n, &m);
    F[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        F[i + 1].n = n;
        for (int j = 0; j < n; j++)
        {
            (F[i + 1][(j + i + 1) % n] += F[i][j]) %= MOD;
            if ((j + i + 1) % n != (j - i - 1 + n) % n)
                (F[i + 1][(j - i - 1 + n) % n] += F[i][j]) %= MOD;
        }
    }
    return printf ("%lld", ((F[n] ^ (m / n)) * F[m % n])[0]), 0;
}
------------------------------------------------------
Problem1151:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long F[65][65];
long long ans = 1;
int main()
{
    // freopen("hanoi.in", "r", stdin);
    // freopen("hanoi.out", "w", stdout);
    int n, m;
    scanf ("%d%d", &n, &m);
    if (m == 3)
    {
        for (int i = 1; i <= n; i++)
            ans = ans * 2;
        printf ("%lld\n", ans - 1);
    }
    else
    {
        memset (F, 0x3f, sizeof (F));
        F[1][3] = 1;
        for (int i = 2; i <= n; i++) F[i][3] = F[i - 1][3] * 2 + 1;
        for (int j = 4; j <= m; j++)
        {
            F[1][j] = 1;
            for (int i = 2; i <= n; i++)
                for (int k = 1; k < i; k++)
                    F[i][j] = min(F[i][j], 2 * F[k][j] + F[i - k][j - 1]);
        }
        printf ("%lld\n", F[n][m]);
    }
    // fclose(stdin), fclose(stdout);
    return 0;
}
------------------------------------------------------
Problem1152:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int Rank[2000005], n, sa[2000005];
char ans[2000005];
int main()
{
    // freopen("rank.in", "r", stdin);
    // freopen("rank.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        Rank[i] = read();
    for (int i = 1; i <= n; i++)
        sa[Rank[i]] = i;
    int cnt = 0;
    ans[sa[1]] = cnt + 'a';
    for (int i = 1; i <= n; i++)
    {
        if (Rank[sa[i] + 1] < Rank[sa[i + 1] + 1])
            ans[sa[i + 1]] = cnt + 'a';
        else
            ans[sa[i + 1]] = (++cnt) + 'a';
    }
    ans[n + 1] = '\0';
    if (cnt > 26) return puts("-1"), 0;
    printf ("%s", ans + 1);
    // else puts("-1");
    // DFS(0);
}
------------------------------------------------------
Problem1153:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
}v[100005 << 1];
int first[100005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
long long dis1[100005], dis2[100005];
int du[100005];
void dfs(int rt, int fa)
{
	dis1[rt] = du[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
    	if (v[i].END == fa) continue;
    	dfs(v[i].END, rt);
    	(dis1[rt] += dis1[v[i].END]) %= MOD;
	}
}
void dfs1(int rt, int fa)
{
	if (rt != 1) dis2[rt] = (dis2[fa] + dis1[fa] - dis1[rt] + MOD) % MOD;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs1(v[i].END, rt);
	}
}
long long dep1[100005], dep2[100005], dep[100005];
int f[(100005 << 1) + 50][17];
void dfs2(int rt, int fa, int Dep)
{
	f[rt][0] = fa;
	for (int i = 1; i <= 16; i++)
		f[rt][i] = f[f[rt][i - 1]][i - 1];
	dep[rt] = Dep;
	dep1[rt] = (dep1[fa] + dis1[rt]) % MOD;
	dep2[rt] = (dep2[fa] + dis2[rt]) % MOD;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs2(v[i].END, rt, Dep + 1);
	}
}
int LCA(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	int d = dep[a] - dep[b];
	for (int i = 16; i >= 0; i--)
		if (d & (1 << i))
			d -= (1 << i), a = f[a][i];
	if (a == b) return a;
	for (int i = 16; i >= 0; i--)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}
int main()
{
//    freopen("tree.in", "r", stdin);
//    freopen("tree.out", "w", stdout);
	memset(first, -1, sizeof (first));
    int n = read(), Q = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        add(a, b);du[a]++;
        add(b, a);du[b]++;
    }
    dfs(1, 0);
    dfs1(1, 0);
    dfs2(1, 0, 0);
    int a, b;
    while (Q--)
    {
    	a = read(), b = read();
    	int lca = LCA(a, b);
    	printf ("%lld\n", ((dep1[a] - dep1[lca] + dep2[b] - dep2[lca]) % MOD + MOD) % MOD);
    }
//    fclose(stdin), fclose(stdout);
    return 0;
}
------------------------------------------------------
Problem1154:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1000005;
int a[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int Sum[N];
int Have[N];
int main()
{
	//freopen ("set.in", "r", stdin);
	//freopen ("set.out", "w", stdout);
	int n = read();
	Have[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		a[i] = read() % n;
		Sum[i] = (Sum[i - 1] + a[i]) % n;
		if (Have[Sum[i]])
		{
			printf ("%d\n", i - Have[Sum[i]]);
			for (int j = Have[Sum[i]] + 1; j <= i; j++)
				printf ("%d ", j);
			return 0;
		}
		Have[Sum[i]] = i;
	}
	printf ("-1");
	//fclose(stdin), fclose(stdout);
	return 0;
}
------------------------------------------------------
Problem1155:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int MAXM = 1005;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int Count[MAXM], X[MAXM], Y[MAXM], Z[MAXM], M, K, N;
int Head, Cnt;
int main()
{
	//freopen("read.in", "r", stdin);
	//freopen("read.out", "w", stdout);
	M = read(), K = read();
	for (int i = 1; i <= M; i++) Count[i] = read();
	for (int i = 1; i <= M; i++) X[i] = read();
	for (int i = 1; i <= M; i++) Y[i] = read();
	for (int i = 1; i <= M; i++) Z[i] = read();
	int S = (1 << K) - 1;
	int Head = -1;
	for (int i = 1; i <= M; i++)
	{
		N = N + 1;
		if (X[i] == Head || Head == -1){
			Cnt++;
			if (Head == -1) Head = X[i];
		}
		else 
		{
			Cnt--;
			if (Cnt == 0)
				Head = -1;
		}
		long long last = X[i];
		for (int j = 1; j < Count[i]; j++)
		{
			last = (last * Y[i] + Z[i]) & S;
			N = N + 1;
			if (last == Head || Head == -1){
				Cnt++;
				if (Head == -1) Head = last;
			}
			else 
			{
				Cnt--;
				if (Cnt == 0)
					Head = -1;
			}
		}
	}
	int Sum = 0;
	for (int i = 1; i <= M; i++)
	{
		if (X[i] == Head) Sum++;
		long long last = X[i];
		for (int j = 1; j < Count[i]; j++)
		{
			last = (last * Y[i] + Z[i]) & S;
			if (last == Head) Sum++;
		}
	}
	if (2 * Sum - N - 1 > 0) printf ("%d\n", 2 * Sum - N - 1);
	else printf ("0\n");
	//fclose(stdin), fclose(stdout);
}
------------------------------------------------------
Problem1156:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
int bin[31];
inline int read()
{
    int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct Node
{
	Node *ch[2];
	int s, f;
#define size(_) ((_)?(_)->s:0)
}*root;
int full = 30;
void Insert(int x)
{
	Node *rt = root;
	for (int i = full; i >= 0; i--)
	{
		int nxt = (x >> i) & 1;
		if (!rt->ch[nxt]) rt->ch[nxt] = new Node();
		rt = rt->ch[nxt];
		rt->s++;
	}
}
int Ans = 0, n, m;
void dfs(Node *rt, long long f, long long ans)
{
	if (rt->ch[0] == NULL && rt->ch[1] == NULL)
	{
		Ans ^= ans;
		return;	
	}
	if (rt->ch[0])
	{
		dfs(rt->ch[0], (f + size(rt->ch[1])) % MOD, (ans + size(rt->ch[1]) * (f + size(rt->ch[1])) % MOD * bin[m - 1] % MOD) % MOD);
	}
	if (rt->ch[1])
	{
		dfs(rt->ch[1], (f + size(rt->ch[0])) % MOD, (ans + size(rt->ch[0]) * (f + size(rt->ch[0])) % MOD * bin[m - 1] % MOD) % MOD);
	}
}
int main()
{
	root = new Node();
	bin[0] = 1;
	for (int i = 1; i <= 30; i++) bin[i] = bin[i - 1] << 1;
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		Insert(read());
	dfs(root, 0, 0);
	printf ("%d", Ans);
	return 0;
}
------------------------------------------------------
Problem1157:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
long long q[5005], p[5005];
long long f[2][5005];
int main()
{
//	freopen("kill.in", "r", stdin);
//	freopen("kill.out", "w", stdout);
	long long n = read(), m = read(), s = read();
	for (int i = 1; i <= n; i++)
		p[i] = read();
	for (int i = 1; i <= m; i++)
		q[i] = read();
	sort(p + 1, p + n + 1);
	sort(q + 1, q + m + 1);
	int now = 0;
	for (int i = 1; i <= n; i++) f[now][i] = 0x3f3f3f3f3f3f3f3fll;
	f[now][0] = 0;
	for (int i = 1; i <= m; i++)
	{
		now ^= 1;
		for (int j = 1; j <= n; j++) f[now][j] = 0x3f3f3f3f3f3f3f3fll;
		f[now][0] = 0;
		for (int j = 1; j <= i && j <= n; j++)
		{
			f[now][j] = max(f[now ^ 1][j - 1], abs(p[j] - q[i]) + abs(q[i] - s));
			f[now][j] = min(f[now][j], f[now ^ 1][j]);

		}
	}
	printf ("%lld", f[now][n]);
//	fclose(stdin), fclose(stdout);
	return 0;
}
------------------------------------------------------
Problem1157:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
long long q[5005], p[5005];
long long f[2][5005];
int main()
{
	//freopen("kill.in", "r", stdin);
	//freopen("kill.out", "w", stdout);
	long long n = read(), m = read(), s = read();
	for (int i = 1; i <= n; i++)
		p[i] = read();
	for (int i = 1; i <= m; i++)
		q[i] = read();
	sort(p + 1, p + n + 1);
	sort(q + 1, q + m + 1);
	int now = 0;
	for (int i = 1; i <= n; i++) f[now][i] = 0x3f3f3f3f3f3f3f3fll;
	for (int i = 1; i <= m; i++)
	{
		now ^= 1;
		for (int j = 1; j <= n; j++) f[now][j] = 0x3f3f3f3f3f3f3f3fll;
		for (int j = 1; j <= i && j <= n; j++)
		{
			f[now][j] = max(f[now ^ 1][j - 1], abs(p[j] - q[i]) + abs(q[i] - s));
			f[now][j] = min(f[now][j], f[now ^ 1][j]);

		}
	}
	printf ("%lld", f[now][n]);
	//fclose(stdin), fclose(stdout);
	return 0;
}
------------------------------------------------------
Problem1158:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct edge
{
	int END, next;
}v[200005];
int first[100005], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int D[100005];
int f[100005], size[100005];
int n, k, a;
long long ans = 0;
void dfs(int rt, int fa)
{
	size[rt] = D[rt];
	f[rt] = D[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs(v[i].END, rt);
		size[rt] += size[v[i].END];
		f[rt] += f[v[i].END];
		ans += f[v[i].END];
	}
	f[rt] = min(f[rt], k - size[rt]);
}
int main()
{
//	freopen("beauty.in", "r", stdin);
//	freopen("beauty.out", "w", stdout);
	n = read(), k = read() << 1, a = read();
	for (int i = 1; i <= k; i++)
		D[read()] = 1;
	int b;
	memset (first, -1, sizeof (first));
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	printf ("%lld", ans);
//	fclose(stdin), fclose(stdout);
	return 0;
}
------------------------------------------------------
Problem1158:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct edge
{
	int END, next;
}v[200005];
int first[100005], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int D[100005];
int f[100005], size[100005];
int n, k, a;
long long ans = 0;
void dfs(int rt, int fa)
{
	f[rt] = D[rt];
	size[rt] = D[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs(v[i].END, rt);
		size[rt] += size[v[i].END];
		f[rt] += f[v[i].END];
		ans += f[v[i].END];
	}
	f[rt] = min(f[rt], k - size[rt]);
}
int main()
{
	//freopen("beauty.in", "r", stdin);
	//freopen("beauty.out", "w", stdout);
	n = read(), k = read() << 1, a = read();
	for (int i = 1; i <= k; i++)
		D[read()] = 1;
	int b;
	memset (first, -1, sizeof (first));
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	printf ("%lld", ans);
	//fclose(stdin), fclose(stdout);
	return 0;
}
------------------------------------------------------
Problem1159:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
const int N = 100005;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct edge
{
	int next, END, v;
}v[N << 1];
int first[N], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}
int val[N], ans[N];
struct data
{
	int S, E, v, id;
	bool operator < (const data &d) const
	{
		return v < d.v;
	}
}e[N];
bool flag[N];
int n, m, s;
int father[N];
int find(int x)
{
	if (father[x] != x) father[x] = find(father[x]);
	return father[x];
}
int dep[N], top[N], son[N], size[N], fa[N], id[N], Index, pre[N];
void dfs1(int rt, int f, int Dep)
{
	dep[rt] = Dep;
	fa[rt] = f;
	size[rt] = 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == f) continue;
		dfs1(v[i].END, rt, Dep + 1);
		val[v[i].END] = v[i].v;
		size[rt] += size[v[i].END];
		if (size[v[i].END] > size[son[rt]]) son[rt] = v[i].END;
	}
}
void dfs2(int rt, int T)
{
	top[rt] = T;
	id[rt] = ++Index;
	pre[Index] = rt;
	if (son[rt]) dfs2(son[rt], T);
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa[rt] || v[i].END == son[rt]) continue;
		dfs2(v[i].END, v[i].END);
	}
}
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
struct Seg_Tree1
{
	int Max[N << 2];
	void Pushup(int rt)
	{
		Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
	}
	void Buildtree(int l, int r, int rt)
	{
		if (l == r)
		{
			Max[rt] = val[pre[l]];
			return;
		}
		int m = l + r >> 1;
		Buildtree(lch);
		Buildtree(rch);
		Pushup(rt);
	}
	int Query(int L, int R, int l, int r, int rt)
	{
		if (L <= l && R >= r)
			return Max[rt];
		int m = l + r >> 1; 
		int ans = 0;
		if (L <= m) ans = max(ans, Query(L, R, lch));
		if (R > m) ans = max(ans, Query(L, R, rch));
		return ans;
	}
}root;
struct Seg_Tree2
{
	int Min[N << 2], lazy[N << 2];
	void Buildtree(int l, int r, int rt)
	{
		Min[rt] = INF, lazy[rt] = INF;
		if (l == r) return;
		int m = l + r >> 1;
		Buildtree(lch);
		Buildtree(rch);
	}
	void Pushdown(int rt)
	{
		if (lazy[rt] != INF)
		{
			lazy[rt << 1] = min(lazy[rt << 1], lazy[rt]);
			lazy[rt << 1 | 1] = min(lazy[rt << 1 | 1], lazy[rt]);
			Min[rt << 1] = min(Min[rt << 1], lazy[rt]);
			Min[rt << 1 | 1] = min(Min[rt << 1 | 1], lazy[rt]);
			lazy[rt] = INF;
		}
	}
	void Update(int L, int R, int c, int l, int r, int rt)
	{
		if (L <= l && R >= r)
		{
			Min[rt] = min(Min[rt], c);
			lazy[rt] = min(lazy[rt], c);
			return;
		}
		int m = l + r >> 1;
		Pushdown(rt);
		if (L <= m) Update(L, R, c, lch);
		if (R > m) Update(L, R, c, rch);
	}
	int Query(int x, int l, int r, int rt)
	{
		if (l == r)
			return Min[rt];
		int m = l + r >> 1;
		Pushdown(rt);
		if (x <= m) return Query(x, lch);
		else return Query(x, rch);
	}
}rt;
void Update(int x, int y, int c)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		rt.Update(id[top[x]], id[x], c, 1, n, 1);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	if(x != y) rt.Update(id[x] + 1, id[y], c, 1, n, 1);
}
int Query(int x, int y)
{
	int ans = 0;
	while (top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		ans = max(ans, root.Query(id[top[x]], id[x], 1, n, 1));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	if(x != y) ans = max(ans, root.Query(id[x] + 1, id[y], 1, n, 1));
	return ans;
}
int main()
{
//	freopen("weight.in", "r", stdin);
//	freopen("weight.out", "w", stdout);
	n = read(), m = read(), s = read();
	int a, b, c;
	memset (first, -1, sizeof (first));
	for (int i = 1; i <= m; i++)
	{
		a = read(), b = read(), c = read();
		e[i].S = a, e[i].E = b, e[i].v = c, e[i].id = i;
	}
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; i++) father[i] = i;
	int t1 = 0;
	for (int i = 1; i <= m; i++)
	{
		if (find(e[i].S) != find(e[i].E))
		{
			father[find(e[i].S)] = find(e[i].E);
			t1++;
			flag[i] = 1;
			add(e[i].S, e[i].E, e[i].v);
			add(e[i].E, e[i].S, e[i].v);
			if (t1 == n - 1) break;
		}
	}
	dfs1(1, 0, 0);
	dfs2(1, 0);
	root.Buildtree(1, n, 1);
	rt.Buildtree(1, n, 1);
	for (int i = 1; i <= m; i++)
		if (!flag[i])
			Update(e[i].S, e[i].E, e[i].v);
	for (int i = 1; i <= m; i++)
	{
		if (find(e[i].S) != find(1))
		{
//			printf ("0 ");
		}
		else
		{
			if (flag[i])
			{
				a = e[i].S, b = e[i].E;
				if (a == fa[b]) swap(a, b);
				ans[e[i].id] = rt.Query(id[a], 1, n, 1);
				ans[e[i].id] = (ans[e[i].id] == INF ? -1: ans[e[i].id] - 1);
//				printf ("%d ", ans == INF ? -1: ans - 1);
			}
			else
			{
				ans[e[i].id] = Query(e[i].S, e[i].E) - 1;
//				printf ("%d ", Query(e[i].S, e[i].E) - 1);
			}
		}
	}
	for (int i = 1; i <= m; i++)
		printf ("%d ", ans[i]);
}
------------------------------------------------------
Problem1160:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 50005;
struct edge
{
	int END, next, S;
}v[N << 1];
int first[N], p;
int head[N], n, m, q;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].S = a;
	first[a] = p++;
}
int f[(N << 1) + 200][20]; 
queue<int> Q;
vector<int> In[N];
int du[N], dep[N];
int LCA(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	int d = dep[a] - dep[b];
	for (int i = 19; i >= 0; i--)
		if (d & (1 << i))
			d -= (1 << i), a = f[a][i];
	if (a == b) return a;
	for (int i = 19; i >= 0; i--)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}
int main()
{
//	freopen("attack.in", "r", stdin);
//	freopen("attack.out", "w", stdout);
	n = read(), m = read(), q = read();
	memset (first, -1, sizeof (first));
	memset (head, -1, sizeof (head));
	int a, b;
	for (int i = 1; i <= m; i++)
	{
		a = read(), b = read();
		In[b].push_back(a);
		add(a, b);
		du[b]++;
	}
	Q.push(1);
	dep[1] = 1;
	while (!Q.empty())
	{
		int k = Q.front();
		Q.pop();
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			du[v[i].END]--;
			if (du[v[i].END] == 0) Q.push(v[i].END);
		}
		if (k != 1)
		{
			int lca = 0;
			for (int i = 0; i < In[k].size(); i++)
			{
				if (lca == 0) lca = In[k][i];
				else lca = LCA(lca, In[k][i]);
			}
			f[k][0] = lca;
			dep[k] = dep[lca] + 1;
			for (int i = 1; i <= 19; i++)
				f[k][i] = f[f[k][i - 1]][i - 1];
		}
	}
	while (q--)
	{
		int k = read();
		int lca = read();
		for (int i = 2; i <= k; i++)
			lca = LCA(read(), lca);
		printf ("%d\n", dep[lca]);
	}
}
------------------------------------------------------
Problem1161:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
char S1[2005], S2[2005];
void Change(int len, char *s)
{
	if (s[len] == 'B')
		for (int i = 1; i <= (len - 1 >> 1); i++)
			swap(s[i], s[len - i]);
}
bool Judge(int len)
{
	for (int i = 1; i <= len; i++)
		if (S1[i] != S2[i])
			return 0;
	return 1;
}
int main()
{
//	freopen("reverse.in", "r", stdin);
//	freopen("reverse.out", "w", stdout);
	int t;
	scanf ("%d", &t);
	while (t--)
	{
		scanf ("%s%s", S1 + 1, S2 + 1);
		int len1 = strlen(S1 + 1), len2 = strlen(S2 + 1);
		if (len1 > len2) swap(len1, len2), swap(S1, S2);
		while (len1 < len2) Change(len2--, S2);
		while (len1)
		{
			if (Judge(len1)) break;
			Change(len1--, S1);
			Change(len2--, S2);
		}
		if (len1 == 0) printf ("-1\n");
		else
		{
			for (int i = 1; i <= len1; i++)
				printf ("%c", S1[i]);
			printf ("\n");
		}
	}
}
------------------------------------------------------
Problem1162:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e5 + 5;
struct edge
{
	int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int du[N];
double f[N], g[N];
double ans[N];
void dfs1(int rt, int fa)
{
	f[rt] += du[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs1(v[i].END, rt);
		f[rt] += f[v[i].END];
	}
}
void dfs2(int rt, int fa)
{
	if (rt != 1) g[rt] = g[fa] + f[fa] - f[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs2(v[i].END, rt);
	}
}
void dfs3(int rt, int fa, double Dep)
{
	ans[rt] = Dep;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs3(v[i].END, rt, Dep + g[v[i].END]);
	}
}
int main()
{
//	freopen("tree.in", "r", stdin);
//	freopen("tree.out", "w", stdout);
	int n = read(), a, b;
	memset (first, -1, sizeof (first));
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read();
		add(a, b);du[a]++;
		add(b, a);du[b]++;
	}
	dfs1(1, 0);
	dfs2(1, 0);
	dfs3(1, 0, 1);
	for (int i = 1; i <= n; i++)
		printf ("%.3lf\n", ans[i]);
//	while (1);
}
------------------------------------------------------
Problem1163:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int a[405][405], Sum[405][405];
int Num[1000005];
int main()
{
//	freopen("rally.in", "r", stdin);
//	freopen("rally.out", "w", stdout);
	int n = read(), m = read(), MOD = read();
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			a[i][j] = read();
			if(a[i][j] == MOD) a[i][j] = 0;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			Sum[i][j] = (Sum[i - 1][j] + Sum[i][j - 1] - Sum[i - 1][j - 1] + a[i][j] + MOD) % MOD;
	for (int i = 1; i <= n; i++)
	{
		for (int k = 0; k < i; k++)
		{
			Num[0] = 1;
			for (int j = 1; j <= m; j++)
			{
				ans += Num[(Sum[i][j] - Sum[k][j] + MOD) % MOD];
				Num[(Sum[i][j] - Sum[k][j] + MOD) % MOD]++;
			}
			for (int j = 1; j <= m; j++)
			{
				Num[(Sum[i][j] - Sum[k][j] + MOD) % MOD]--;
			}
		}
	}
	printf ("%lld\n", ans);
}
------------------------------------------------------
Problem1164:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
struct edge
{
	int END, next;
}v[N << 1];
int first[N], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int f[N][2];
int n, k, t, ans;
void dfs(int rt, int fa)
{
	f[rt][1] = INF;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs(v[i].END, rt);
	}
	if (f[rt][0] + f[rt][1] <= k) f[rt][0] = -INF;
	if (f[rt][0] == k) f[rt][1] = 0, /*printf ("%d ", rt), */ ans++, f[rt][0] = -INF;
	f[fa][0] = max(f[fa][0], f[rt][0] + 1);
	f[fa][1] = min(f[fa][1], f[rt][1] + 1);
}
int main()
{
//	freopen("general.in", "r", stdin);
//	freopen("general.out", "w", stdout);
	n = read(), k = read(), t = read();
	memset (first, -1, sizeof (first));
	int a, b;
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	if (f[1][0] >= 0) ans++;
	printf ("%d\n", ans);
}
------------------------------------------------------
Problem1165:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int Pos[40005], b[40005], C[40005];
int n, k, m;
struct edge
{
	int END, next, v;
}v[40005 * 64 * 2];
int first[40005], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}
int id[40005], Index;
int d[50][50], dis[40005];
queue<int> Q;
bool vis[40005];
void Spfa(int x)
{
	memset (dis, 0x3f, sizeof (dis));
	memset (vis, 0, sizeof (vis));
	Q.push(x);
	dis[x] = 0;
	vis[x] = 1;
	while (!Q.empty())
	{
		int rt = Q.front();
		Q.pop();
		vis[rt] = 0;
		for (int i = first[rt]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END] > dis[rt] + 1)
			{
				dis[v[i].END] = dis[rt] + 1;
				if (!vis[v[i].END])
				{
					vis[v[i].END] = 1;
					Q.push(v[i].END);
				}
			}
		}
	}
}
int f[65539];
int main()
{
	// freopen("starlit.in", "r", stdin);
	// freopen("starlit.out", "w", stdout);
	n = read(), k = read(), m = read();
	// for (int i = 1; i <= n; i++) Pos[i] = 1;
	memset (first, -1, sizeof (first));
	for (int i = 1; i <= k; i++)
		Pos[read()] = 1;
	for (int i = 1; i <= m; i++)
		b[i] = read();
	for (int i = 0; i <= n; i++) C[i] = Pos[i] ^ Pos[i + 1];
//	for (int i = 0; i <= n; i++) {
//		printf ("%d ", C[i]);
//	}
//	printf("\n");
	for (int i = 0; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (i - b[j] >= 0) add(i, i - b[j], 1);
			if (i + b[j] <= n) add(i, i + b[j], 1);
		}
	}
//	printf("1\n");
	for (int i = 0; i <= n; i++)
		if (C[i] == 1)
			id[i] = ++Index;
	memset (vis, -1, sizeof (vis));
	for (int i = 0; i <= n; i++)
	{
		if (C[i] == 1)
		{
			Spfa(i);
			for (int j = 0; j <= n; j++)
				if (C[j] == 1 && i != j)
					d[id[i]][id[j]] = dis[j];
		}
	}
	memset (f, 0x3f, sizeof (f));
	f[0] = 0;
	int N = (1 << Index) - 1;
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j < Index; j++)
		{
			if ((1 << j) & i) continue;
			for (int l = 0; l < Index; l++)
			{
				if (l == j) continue;
				if (((1 << l) & i)) continue;
				f[i ^ (1 << j) ^ (1 << l)] = min(f[i ^ (1 << j) ^ (1 << l)], f[i] + d[l + 1][j + 1]);
			}
		}
	}
	printf ("%d\n", f[N]);
}
------------------------------------------------------
Problem1166:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int base = 10000;
struct BigNum
{
    int a[30];
    int len;
    BigNum(const char *s = "")
    {
        long long sum = 0, su = 1;
        int n = strlen(s);
        memset (a, 0, sizeof (a));
        len = 0;
        for (int j = n - 1; j >= 0; j--)
        {
            sum += (s[j] - '0') * su;
            su *= 10;
            if (su == base)
            {
                a[++len] = sum;
                sum = 0, su = 1;
            }
        }
        if (sum != 0 || len == 0)
            a[++len] = sum;
    }
    BigNum operator-(const BigNum &b) const
    {
        BigNum ans = *this;
        int m = max(len, b.len);
        for (int i = 1; i <= m; i++)
        {
            if (ans.a[i] < b.a[i])
                ans.a[i + 1] -= 1, ans.a[i] += base;
            ans.a[i] -= b.a[i];
        }
        while (ans.len > 1 && ans.a[ans.len] == 0)
            ans.len--;
        return ans;
    }
    BigNum operator / (const int &b) const 
	{
		BigNum ans;
		ans.len = len;
		int y = 0;
		for (int i = len; i >= 1; i--)
		{
			ans.a[i] = (y + a[i]) / b;
			y = (y + a[i]) % b * base;
		}
		while(!ans.a[ans.len] && ans.len > 1)
			ans.len--;
		return ans;
    }
    BigNum operator * (const int &b) const
    {
        BigNum ans;
        ans.len = len;
        int y = 0;
        for (int i = 1; i <= ans.len; i++)
        {
            ans.a[i] = a[i] * b + y;
            y = ans.a[i] / base;
            ans.a[i] %= base;
        }
        while(y)
		{
			ans.a[++ans.len] = y % base;
			y /= base;
        }
        return ans;
    }
    bool operator<(const BigNum &b) const
    {
        if (b.len > len)
            return 1;
        if (len > b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] < b.a[i])
                return 1;
            else if (a[i] > b.a[i])
                return 0;
        return 0;
    }
    bool operator==(const BigNum &b) const
    {
        if (len != b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 0;
        return 1;
    }
    bool operator!=(const BigNum &b) const
    {
        if (len != b.len)
            return 1;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 1;
        return 0;
    }
    bool Judge()
    {
        return a[1] & 1;
    }
    void print()
    {
        printf ("%d", a[len]);
        for (int i = len - 1; i >= 1; i--)
            printf ("%04d", a[i]);
    }
}A, B;
int cnt;
bool Do(BigNum &a, BigNum &b)
{
    if (!a.Judge() && !b.Judge()) {a = a / 2; b = b / 2; cnt++; return 1;}
    if (!a.Judge()) {a = a / 2; return 1;}
    if (!b.Judge()) {b = b / 2; return 1;}
    return 0;
}
char s[105];
int main()
{
    // freopen("king.in", "r", stdin);
    // freopen("king.out", "w", stdout);
    int t;
    scanf ("%d", &t);
    while (t--)
    {
        cnt = 0;
        scanf ("%s", s);
        A = BigNum(s);
        scanf ("%s", s);
        B = BigNum(s);
        while (A != B)
        {
            while (Do(A, B));
            if (A == B) break;
            if (A < B) swap(A, B);
            A = A - B;
        }
        int tmp1 = cnt / 10, tmp2 = cnt % 10, p = 1 << 10;
        while (tmp1--) A = A * p;
        while (tmp2--) A = A * 2;
        if (A.len == 1 && A.a[1] == 1) printf ("Yes\n");
        else printf ("No\n");
    }
}
------------------------------------------------------
Problem1167:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 5e6 + 2;
char s[N];
int S[N << 1][3];
#define Num(_,__) S[_ + 5000000][__]
int Sum[N][3];
int main()
{
    int n;
    scanf ("%d", &n);
    scanf ("%s", s + 1);
    int now[3];
    int sum[3];
    now[0] = 0, now[1] = 0, now[2] = 0;
    sum[0] = 0, sum[1] = 0, sum[2] = 0;
    long long ans = 1ll * n * (n + 1) / 2;
    Num(0, 0) = 1, Num(0, 1) = 1, Num(0, 2) = 1;
    for (int i = 1; i <= n; i++)
    {
        sum[s[i] - '0'] += Num(now[s[i] - '0']++, s[i] - '0');
        sum[(s[i] - '0' + 1) % 3] -= Num(--now[(s[i] - '0' + 1) % 3], (s[i] - '0' + 1) % 3);
        sum[(s[i] - '0' + 2) % 3] -= Num(--now[(s[i] - '0' + 2) % 3], (s[i] - '0' + 2) % 3);
        ans -= sum[1] + sum[2] + sum[0];
        Num(now[1], 1)++, Num(now[0], 0)++, Num(now[2], 2)++;
    }
    printf ("%lld", ans);
    
}
------------------------------------------------------
Problem1169:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
struct data
{
    long double p, q, pq;
}v[100005];
int n, a, b;
int UseA[100005], UseB[100005];
long double f[100005];
long double ans = 0;
bool OK(long double m, long double c)
{
    memset (f, 0xfe, sizeof (f));
    memset (UseA, 0, sizeof (UseA));
    memset (UseB, 0, sizeof (UseB));
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = f[i - 1];
        UseA[i] = UseA[i - 1];
        UseB[i] = UseB[i - 1];
        if (f[i] < f[i - 1] + v[i].p - m)
        {
            f[i] = f[i - 1] + v[i].p - m;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1];
        }
        if (f[i] < f[i - 1] + v[i].q - c)
        {
            f[i] = f[i - 1] + v[i].q - c;
            UseA[i] = UseA[i - 1];
            UseB[i] = UseB[i - 1] + 1;
        }
        if (f[i] < f[i - 1] + v[i].pq - m - c)
        {
            f[i] = f[i - 1] + v[i].pq - m - c;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1] + 1;
        }
    }
    return UseA[n] > a;
}
bool Judge(long double m, long double &t)
{
    long double l = 0, r = 1;
    while (l + 1e-9 < r)
    {
        long double mid = (l + r) / 2;
        if (OK(mid, m)) l = mid;
        else r = mid;
    }
    t = l;
    return UseB[n] >= b;
}
int main()
{
    // freopen ("red.in", "r", stdin);
    // freopen ("red.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    while (cin >> n >> a >> b)
    {
        for (int i = 1; i <= n; i++)
            cin >> v[i].p;
        for (int i = 1; i <= n; i++)
            cin >> v[i].q;
        for (int i = 1; i <= n; i++)
            v[i].pq = v[i].p + v[i].q - v[i].p * v[i].q;
        a = min(a, n), b = min(b, n);
        long double l = 0, r = 1;
        long double t = 0;
        while (l + 1e-9 < r)
        {
            long double m = (l + r) / 2;
            if (Judge(m, t)) l = m;
            else r = m;
        }
        cout << fixed << setprecision(3) << f[n] + b * l + a * t << endl;
    }
}
------------------------------------------------------
Problem1169:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
struct data
{
    double p, q, pq;
}v[100005];
int n, a, b;
int UseA[100005], UseB[100005];
double f[100005];
double ans = 0;
bool OK(double m, double c)
{
    memset (f, 0xfe, sizeof (f));
    memset (UseA, 0, sizeof (UseA));
    memset (UseB, 0, sizeof (UseB));
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = f[i - 1];
        UseA[i] = UseA[i - 1];
        UseB[i] = UseB[i - 1];
        if (f[i] < f[i - 1] + v[i].p - m)
        {
            f[i] = f[i - 1] + v[i].p - m;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1];
        }
        if (f[i] < f[i - 1] + v[i].q - c)
        {
            f[i] = f[i - 1] + v[i].q - c;
            UseA[i] = UseA[i - 1];
            UseB[i] = UseB[i - 1] + 1;
        }
        if (f[i] < f[i - 1] + v[i].pq - m - c)
        {
            f[i] = f[i - 1] + v[i].pq - m - c;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1] + 1;
        }
    }
    return UseA[n] > a;
}
bool Judge(double m, double &t)
{
    double l = 0, r = 1;
    while (l + 1e-9 < r)
    {
        double mid = (l + r) / 2;
        if (OK(mid, m)) l = mid;
        else r = mid;
    }
    t = l;
    return UseB[n] >= b;
}
int main()
{
    // freopen ("red.in", "r", stdin);
    // freopen ("red.out", "w", stdout);
    // std::ios::sync_with_stdio(false);
    while (scanf ("%d%d%d", &n, &a, &b) == 3)
    {
        for (int i = 1; i <= n; i++)
            scanf ("%lf", &v[i].p);
        for (int i = 1; i <= n; i++)
            scanf ("%lf", &v[i].q);
        for (int i = 1; i <= n; i++)
            v[i].pq = v[i].p + v[i].q - v[i].p * v[i].q;
        a = min(a, n), b = min(b, n);
        double l = 0, r = 1;
        double t = 0;
        while (l + 1e-9 < r)
        {
            double m = (l + r) / 2;
            if (Judge(m, t)) l = m;
            else r = m;
        }
        printf ("%.3lf\n", f[n] + b * l + a * t);
    }
}
------------------------------------------------------
Problem1169:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
struct data
{
    double p, q, pq;
}v[100005];
int n, a, b;
int UseA[100005], UseB[100005];
double f[100005];
double ans = 0;
bool OK(double m, double c)
{
    memset (f, 0xfe, sizeof (f));
    memset (UseA, 0, sizeof (UseA));
    memset (UseB, 0, sizeof (UseB));
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = f[i - 1];
        UseA[i] = UseA[i - 1];
        UseB[i] = UseB[i - 1];
        if (f[i] < f[i - 1] + v[i].p - m)
        {
            f[i] = f[i - 1] + v[i].p - m;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1];
        }
        if (f[i] < f[i - 1] + v[i].q - c)
        {
            f[i] = f[i - 1] + v[i].q - c;
            UseA[i] = UseA[i - 1];
            UseB[i] = UseB[i - 1] + 1;
        }
        if (f[i] < f[i - 1] + v[i].pq - m - c)
        {
            f[i] = f[i - 1] + v[i].pq - m - c;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1] + 1;
        }
    }
    return UseA[n] > a;
}
bool Judge(double m, double &t)
{
    double l = 0, r = 1;
    while (l + 1e-8 < r)
    {
        double mid = (l + r) / 2;
        if (OK(mid, m)) l = mid;
        else r = mid;
    }
    t = l;
    return UseB[n] >= b;
}
int main()
{
    // freopen ("red.in", "r", stdin);
    // freopen ("red.out", "w", stdout);
    // std::ios::sync_with_stdio(false);
    while (scanf ("%d%d%d", &n, &a, &b) == 3)
    {
        for (int i = 1; i <= n; i++)
            scanf ("%lf", &v[i].p);
        for (int i = 1; i <= n; i++)
            scanf ("%lf", &v[i].q);
        for (int i = 1; i <= n; i++)
            v[i].pq = v[i].p + v[i].q - v[i].p * v[i].q;
        a = min(a, n), b = min(b, n);
        double l = 0, r = 1;
        double t = 0;
        while (l + 1e-8 < r)
        {
            double m = (l + r) / 2;
            if (Judge(m, t)) l = m;
            else r = m;
        }
        printf ("%.3lf\n", f[n] + b * l + a * t);
    }
}
------------------------------------------------------
Problem1169:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
struct data
{
    double p, q, pq;
}v[100005];
int n, a, b;
int UseA[100005], UseB[100005];
double f[100005];
double ans = 0;
bool OK(double m, double c)
{
    memset (f, 0xfe, sizeof (f));
    memset (UseA, 0, sizeof (UseA));
    memset (UseB, 0, sizeof (UseB));
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = f[i - 1];
        UseA[i] = UseA[i - 1];
        UseB[i] = UseB[i - 1];
        if (f[i] < f[i - 1] + v[i].p - m)
        {
            f[i] = f[i - 1] + v[i].p - m;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1];
        }
        if (f[i] < f[i - 1] + v[i].q - c)
        {
            f[i] = f[i - 1] + v[i].q - c;
            UseA[i] = UseA[i - 1];
            UseB[i] = UseB[i - 1] + 1;
        }
        if (f[i] < f[i - 1] + v[i].pq - m - c)
        {
            f[i] = f[i - 1] + v[i].pq - m - c;
            UseA[i] = UseA[i - 1] + 1;
            UseB[i] = UseB[i - 1] + 1;
        }
    }
    return UseA[n] > a;
}
bool Judge(double m, double &t)
{
    double l = 0, r = 1;
    while (l + 1e-8 < r)
    {
        double mid = (l + r) / 2;
        if (OK(mid, m)) l = mid;
        else r = mid;
    }
    t = l;
    return UseB[n] >= b;
}
int main()
{
    // freopen ("red.in", "r", stdin);
    // freopen ("red.out", "w", stdout);
    // std::ios::sync_with_stdio(false);
    while (scanf ("%d%d%d", &n, &a, &b) == 3)
    {
        for (int i = 1; i <= n; i++)
            scanf ("%lf", &v[i].p);
        for (int i = 1; i <= n; i++)
            scanf ("%lf", &v[i].q);
        for (int i = 1; i <= n; i++)
            v[i].pq = v[i].p + v[i].q - v[i].p * v[i].q;
        a = min(a, n), b = min(b, n);
        double l = 0, r = 1;
        double t = 0;
        while (l + 1e-8 < r)
        {
            double m = (l + r) / 2;
            if (Judge(m, t)) l = m;
            else r = m;
        }
        printf ("%.3lf\n", f[n] + b * l + a * t);
    }
}
------------------------------------------------------
Problem1170:
#include <cstdio>
int main()
{
    // freopen ("a.in", "r", stdin);
    // freopen ("a.out", "w", stdout);
    long long n, m, p;
    scanf ("%lld%lld%lld", &n, &m, &p);
    printf ("%lld", n * m % p);
}
------------------------------------------------------
Problem1171:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
}v[100005];
int first[100005], p;
inline void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int val[100005], tmp[100005];
int size[100005];
vector<int> f[100005];
int n, k;
void DP(int rt)
{
    size[rt] = first[rt] == -1;
    f[rt][0] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        DP(v[i].END);
        for (int j = 1; j <= size[rt] + size[v[i].END] && j <= k; j++) tmp[j] = 0;
        for (int j = 0; j <= size[rt] && j <= k; j++)
            for (int l = 0; l <= size[v[i].END] && l <= k; l++) if (j + l <= k)
                tmp[j + l] = max(tmp[j + l], f[v[i].END][l] + f[rt][j]);
        size[rt] += size[v[i].END];
        for (int j = 1; j <= size[rt] && j <= k; j++) f[rt][j] = tmp[j];
    }
    f[rt][1] = max(f[rt][1], val[rt]);
}
int main()
{
    // freopen("b.in", "r", stdin);
    // freopen("b.out", "w", stdout);
    n = read(), k = read() + 1;
    memset (first, -1, sizeof (first));
    for (int i = 2; i <= n; i++)
        add(read(), i), val[i] = read();
    for (int i = 1; i <= n; i++)
        f[i].resize(k + 1);
    DP(1);
    int ans = 0;
    for (int i = 0; i <= k; i++)
        ans = max(ans, f[1][i]);
    printf ("%d\n", ans);
    return 0;
}
------------------------------------------------------
Problem1172:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 300005;
struct data
{
    int l, r, mid;
    bool operator < (const data &a) const
    {
        return l < a.l;
    }
}a[N];
set<int> st;
bool vis[N];
int Sum[N][2], pre[N];
int f[N], g[N];
int main()
{
    // freopen ("c.in", "r", stdin);
    // freopen ("c.out", "w", stdout);
    int n = read(), t = read();
    int N = 0;
    for (int i = 1; i <= n; i++)
    {
        a[i].l = read();
        a[i].r = read();
        a[i].mid = a[i].l + a[i].r >> 1;
        N = max(a[i].r, N);
        pre[a[i].r] = max(a[i].l, pre[a[i].r]);
    }
    for (int i = 1; i <= n; i++)
        Sum[a[i].mid][0] ++,
        Sum[a[i].mid][1] += a[i].mid;
    for (int i = 1; i <= N; i++)
        Sum[i][0] += Sum[i - 1][0],
        Sum[i][1] += Sum[i - 1][1];
    for (int i = 1; i <= N; i++)
        pre[i] = max(pre[i], pre[i - 1]);    
    f[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        f[i] = f[pre[i - 1]] + 1;
        g[i] = 0x3f3f3f3f;
        for (int j = pre[i - 1]; j < i; j++)
            if (f[j] != f[i] - 1) break;
            else
            {
                int mid = j + i >> 1;
                g[i] = min(g[i], Sum[mid][1] - Sum[(j - 1) < 0 ? 0 : (j - 1)][1] - (Sum[mid][0] - Sum[(j - 1) < 0 ? 0 : (j - 1)][0]) * j \
                                + (Sum[i][0] - Sum[mid][0]) * i - Sum[i][1] + Sum[mid][1] + g[j]);
            }
    }
    printf ("%d\n", f[pre[N]]);
    if (!t) return 0;
    int ans = 0x3f3f3f3f;
    for (int j = pre[N]; j <= N; j++)
        if (f[j] > f[pre[N]]) break;
        else ans = min(ans, Sum[N][1] - Sum[j - 1][1] - (Sum[N][0] - Sum[j - 1][0]) * j + g[j]);
    printf ("%d", ans << 1);
}
------------------------------------------------------
Problem1173:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int C[50];
int To(int N, int k, int *a, int &Sum, int lim)
{
    int t = 0;
    Sum = 0;
    while (N)
    {
        if (t == lim) a[++t] = N, N = 0;
        else a[++t] = N % k;
        Sum += a[t];
        N /= k;
    }
    return t;
}
int main()
{
    // freopen ("a.in", "r", stdin);
    // freopen ("a.out", "w", stdout);
    int S, T, a, b;
    scanf ("%d%d%d%d", &S, &T, &a, &b);
    long long Pow = 1;
    int ans = 0x3f3f3f3f, Sum;
    for (int i = 0; i <= 30; i++)
    {
        if (Pow * S > T || Pow > 1000000000) break;
        int t = T - Pow * S;
        Pow *= b;
        if (t % a) continue;
        t /= a;
        memset (C, 0, sizeof (C));
        To(t, b, C, Sum, i);
        ans = min(ans, Sum + i);
    }
    printf ("%d", (ans == 0x3f3f3f3f ? -1: ans));
    // fclose(stdin), fclose(stdout);
    // while (1);
}
------------------------------------------------------
Problem1174:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct data
{
    int l, r;
}v[100005];
int n, m;
bool Judge(int mid)
{
    int l = -0x3f3f3f3f, r = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        if (v[i].r - v[i].l > mid)
        {
            r = min(v[i].r + v[i].l + mid, r);
            l = max(v[i].r + v[i].l - mid, l);
        }
    if (l > r) return 0;
    l = -0x3f3f3f3f, r = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        if (v[i].r - v[i].l > mid)
        {
            r = min(v[i].r - v[i].l + mid, r);
            l = max(v[i].r - v[i].l - mid, l);
        }
    if (l > r) return 0;
    return 1;
}
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
        v[i].l = read(), v[i].r = read();
    int l = 0, r = n;
    int ans = 0;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (Judge(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf ("%d\n", ans);
}
------------------------------------------------------
Problem1174:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int _=0,__=1;char ___=getchar();
    while(___<'0'||___>'9'){if(___=='-')__=-1;___=getchar();}
    while(___>='0'&&___<='9'){_=_*10+___-'0';___=getchar();}
    return _*__;
}
struct data
{
    int _, __;
}_[100005];
int _____, ______;
bool Judge(int ____)
{
    int __ = -0x3f3f3f3f, ___ = 0x3f3f3f3f;
    for (int _________ = 1; _________ <= _____; _________++)
        if (_[_________].__ - _[_________]._ > ____)
        {
            ___ = min(_[_________].__ + _[_________]._ + ____, ___);
            __ = max(_[_________].__ + _[_________]._ - ____, __);
        }
    if (__ > ___) return 0;
    __ = -0x3f3f3f3f, ___ = 0x3f3f3f3f;
    for (int _________ = 1; _________ <= _____; _________++)
        if (_[_________].__ - _[_________]._ > ____)
        {
            ___ = min(_[_________].__ - _[_________]._ + ____, ___);
            __ = max(_[_________].__ - _[_________]._ - ____, __);
        }
    if (__ > ___) return 0;
    return 1;
}
int main()
{
    _____ = read(), ______ = read();
    for (int _________ = 1; _________ <= ______; _________++)
        _[_________]._ = read(), _[_________].__ = read();
    int __ = 0, ___ = ______;
    int _______ = 0;
    while (__ <= ___)
    {
        int ____ = __ + ___ >> 1;
        if (Judge(____)) _______ = ____, ___ = ____ - 1;
        else __ = ____ + 1;
    }
    printf ("%d\n", _______);
}
------------------------------------------------------
Problem1174:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int ______________()
{
    int _=0,__=1;char ___=getchar();
    while(___<'0'||___>'9'){if(___=='-')__=-1;___=getchar();}
    while(___>='0'&&___<='9'){_=_*10+___-'0';___=getchar();}
    return _*__;
}
struct _____________
{
    int _, __;
}_[100005];
int _____, ______;
bool _______________(int ____)
{
    int __ = -0x3f3f3f3f, ___ = 0x3f3f3f3f;
    for (int _________ = 1; _________ <= _____; _________++)
        if (_[_________].__ - _[_________]._ > ____)
        {
            ___ = min(_[_________].__ + _[_________]._ + ____, ___);
            __ = max(_[_________].__ + _[_________]._ - ____, __);
        }
    if (__ > ___) return 0;
    __ = -0x3f3f3f3f, ___ = 0x3f3f3f3f;
    for (int _________ = 1; _________ <= _____; _________++)
        if (_[_________].__ - _[_________]._ > ____)
        {
            ___ = min(_[_________].__ - _[_________]._ + ____, ___);
            __ = max(_[_________].__ - _[_________]._ - ____, __);
        }
    if (__ > ___) return 0;
    return 1;
}
int main()
{
    _____ = ______________(), ______ = ______________();
    for (int _________ = 1; _________ <= ______; _________++)
        _[_________]._ = ______________(), _[_________].__ = ______________();
    int __ = 0, ___ = ______;
    int _______ = 0;
    while (__ <= ___)
    {
        int ____ = __ + ___ >> 1;
        if (_______________(____)) _______ = ____, ___ = ____ - 1;
        else __ = ____ + 1;
    }
    printf ("%d\n", _______);
}
------------------------------------------------------
Problem1175:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct data
{
    int a, b;
}c[2000005];
int n;
int a[2000005], b[2000005];
bool vis[2000005];
void dfs(int rt)
{
    if (vis[rt]) return;
    vis[rt] = 1;
    dfs(b[rt]);
}
bool Judge(int mid)
{
    memcpy (b, a, sizeof (b));
    memset (vis, 0, sizeof (vis));
    for (int i = 1; i <= mid; i++)
        swap(b[c[i].a], b[c[i].b]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i), ans++;
    return n - ans > mid;
}
int main()
{
    // freopen("c.in", "r", stdin);
    // freopen("c.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read() + 1;
    for (int i = 1; i <= 2 * n; i++)
        c[i].a = read() + 1, c[i].b = read() + 1;
    int l = 0, r = n + 1;
    int ans = 0;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (Judge(mid)) l = mid + 1;
        else ans = mid, r = mid - 1;
    }
    printf ("%d\n", ans);
    // while (1);
}
------------------------------------------------------
Problem1176:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
set<int> st;
set<int>::iterator it;
int main()
{
//	freopen ("d.in", "r", stdin);
//	freopen ("d.out", "w", stdout);
	int T;
	T = read();
	while (T--)
	{
		int n = read(), k = read();
		int a, flag = 0;
		st.clear();
		for (int i = 1; i <= n; i++)
		{
			a = read();
			if (flag) continue;
			it = st.upper_bound(a);
			if (it != st.begin())
			{
				it--;
				st.erase(it);
				st.insert(a);
			}
			else if (st.size() < k)
			{
				st.insert(a);
			}
			else flag = 1;
		}
		if (flag) printf ("NO\n");
		else printf ("YES\n");
	}
//	fclose(stdin), fclose(stdout);
	return 0;
}
------------------------------------------------------
Problem1177:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long f[2005][2005];
long long bin[2005];
int main()
{
//	freopen ("e.in", "r", stdin);
//	freopen ("e.out", "w", stdout);
	int n, p;
	scanf ("%d%d", &n, &p);
	bin[0] = 1; 
	for (int i = 1; i <= n; i++) bin[i] = (bin[i - 1] << 1) % p;
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			f[i][j] = (f[i][j - 1] * 2 + f[i - 1][j - 1]) % p;
		for (int j = 1; j <= n; j++)
			f[i][j] = f[i][j] * (n - j + 1) % p;
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans = (ans + f[i][n] * f[i - 1][n] % p + f[i][n] * f[i][n] % p) % p;
	printf ("%d", ans * 2 % p);
//	fclose(stdin), fclose(stdout);
	return 0;
}

------------------------------------------------------
Problem1178:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
stack<int> s;
int a[100005], pos[100005];
int L[100005], R[100005];
int U[(100005 << 1) + 200][17];
int st[(100005 << 1) + 200][17];
int QueryMx(int l, int r)
{
	int k = 0;
	while ((1 << k) <= r - l + 1) k++;
	k--;
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}
int Calc(int x, int mid, int &ans)
{
	for (int i = 16; i >= 0; i--)
		if (a[U[x][i]] <= mid)
			x = U[x][i], ans += (1 << i);
//	printf("%d\n",ans);
	if (a[x] == mid) return 0;
	if (min(L[x], R[x]) == mid)
	{
		ans ++;
		return 0;
	}
	else
	{
		ans += 2;
		return 1;
	}
}
int main()
{
//	freopen("f.in", "r", stdin);
//	freopen("f.out", "w", stdout);
	int n = read(), m = read();
	a[0] = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++)
		a[i] = read(), st[i][0] = a[i], pos[a[i]] = i;
	for (int i = 1; i <= n; i++)
	{
		while (!s.empty() && s.top() < a[i]) s.pop();
		L[i] = s.empty() ? 0 : s.top();
		s.push(a[i]);
	}
	while (!s.empty()) s.pop();
	for (int i = n; i >= 1; i--)
	{
		while (!s.empty() && s.top() < a[i]) s.pop();
		R[i] = s.empty() ? 0 : s.top();
		s.push(a[i]);
	}
	for (int i = 1; i <= 16; i++)
		for (int j = 1; j <= n; j++)
			st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
//	memset (U, 0x3f, sizeof (U));
	for (int i = 1; i <= n; i++) U[i][0] = pos[max(L[i], R[i])];
	for (int i = 1; i <= 16; i++)
		for (int j = 1; j <= n; j++)
			U[j][i] = U[U[j][i - 1]][i - 1];
	int x, y;
	while (m--)
	{
		x = read(), y = read();
		if (x > y) swap(x, y);
		int mid = QueryMx(x, y);
		int ans = 0;
		int X = Calc(x, mid, ans);
//		printf ("%d %d\n", ans, mid);
		int Y = Calc(y, mid, ans);
		if (X && Y) ans--; 
		printf ("%d\n", ans);
	}
//	fclose(stdin), fclose(stdout);
	return 0;
}
------------------------------------------------------
