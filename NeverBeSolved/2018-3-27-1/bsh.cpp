#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 52005;
struct data
{
	int a, b, id;
	data(int _a = 0, int _b = 0, int _id = 0): a(_a), b(_b), id(_id) {}
};
struct edge
{
	int END, next;
}v[MAXN * 4];
int first[MAXN], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int Rank[MAXN];
int dis[MAXN][2];
bool vis[MAXN];
int ans[MAXN * 2], Color[MAXN];
void Spfa(int S, int d)
{
	queue<int> Q;
	dis[S][d] = 0;
	Q.push(S);
	vis[S] = 1;
	while (!Q.empty())
	{
		int k = Q.front(); Q.pop();
		vis[k] = 0;
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END][d] > dis[k][d] + 1)
			{
				dis[v[i].END][d] = dis[k][d] + 1;
				if (!vis[v[i].END])
				{
					vis[v[i].END] = 1;
					Q.push(v[i].END);
				}
			}
		}
	}
}
void Divide(vector<int> u, vector<data> s, vector<data> Q)
{
	if (u.size() == 3)
	{
		for (int i = 0; i < Q.size(); i++)
			if (Q[i].a != Q[i].b)
				ans[Q[i].id] = 1;
			else ans[Q[i].id] = 0;
		return;
	}
	// cerr << "=========START=========" << endl;
	int Min = 0x3f3f3f3f, id = 0;
	for (int i = 0; i < s.size(); i++)
	{
		int tmp = max(abs(Rank[s[i].a] - Rank[s[i].b]), (int)u.size() - abs(Rank[s[i].a] - Rank[s[i].b]));
		if (tmp < Min)
		{
			Min = tmp;
			id = i;
		}
	}
	// cerr << "=========ADD EDGE=========" << endl;
	for (int i = 0; i < u.size(); i++)
		first[u[i]] = -1;
	p = 0;
	for (int i = 0; i < u.size() - 1; i++)
	{
		add(u[i], u[i + 1]);
		add(u[i + 1], u[i]);
	}
	add(u[0], u[u.size() - 1]);
	add(u[u.size() - 1], u[0]);
	for (int i = 0; i < s.size(); i++)
	{
		add(s[i].a, s[i].b);
		add(s[i].b, s[i].a);
	}
	// cerr << "=========ADD EDGE END=========" << endl;
	int l = Rank[s[id].a] - 1, r = Rank[s[id].b] - 1;
	if (l > r) swap(l, r);
	for (int i = 0; i < u.size(); i++)
	{
		if (i < l || i > r)
			Color[u[i]] = 0;
		else
			Color[u[i]] = 1;
	}
	// cerr << "=========Start Spfa=========" << endl;
	Spfa(s[id].a, 0);
	Spfa(s[id].b, 1);
	// cerr << "=========END Spfa=========" << endl;
	for (int i = 0; i < Q.size(); i++)
		if (Color[Q[i].a] != Color[Q[i].b])
		{
			ans[Q[i].id] = dis[Q[i].a][0] + dis[Q[i].b][0];
			ans[Q[i].id] = min(ans[Q[i].id], dis[Q[i].a][0] + dis[Q[i].b][1] + 1);
			ans[Q[i].id] = min(ans[Q[i].id], dis[Q[i].a][1] + dis[Q[i].b][0] + 1);
			ans[Q[i].id] = min(ans[Q[i].id], dis[Q[i].a][1] + dis[Q[i].b][1]);
		}
	for (int i = 0; i < u.size(); i++)
		dis[u[i]][0] = dis[u[i]][1] = 0x3f3f3f3f;
	vector<int> v1;
	int Index = 0;
	for (int i = 0; i < u.size(); i++)
	{
		if (i == l || i == r)
		{
			v1.push_back(u[i]);
			Rank[u[i]] = ++Index;
		}
		else if (Color[u[i]] == 0)
		{
			v1.push_back(u[i]);
			Rank[u[i]] = ++Index;
		}
	}
	vector<data> s1, s2;
	for (int i = 0; i < s.size(); i++)
	{
		if (i == id) continue;
		if (Color[s[i].a] == Color[s[i].b])
		{
			if (Color[s[i].a] == 0)
				s1.push_back(s[i]);
			else
				s2.push_back(s[i]);
		}
		else if (s[i].a == u[l] || s[i].a == u[r])
		{
			if (Color[s[i].b] == 0)
				s1.push_back(s[i]);
			else
				s2.push_back(s[i]);
		}
		else if (s[i].b == u[l] || s[i].b == u[r])
		{
			if (Color[s[i].a] == 0)
				s1.push_back(s[i]);
			else
				s2.push_back(s[i]);
		}
	}
	vector<data> Q1, Q2;
	for (int i = 0; i < Q.size(); i++)
		if (Color[Q[i].a] == Color[Q[i].b])
		{
			if (Color[Q[i].a] == 0)
				Q1.push_back(Q[i]);
			else
				Q2.push_back(Q[i]);
		}
	// cerr << "=========Start 1========= " << v1.size() << endl;
	Divide(v1, s1, Q1);
	v1.clear();
	for (int i = 0; i < u.size(); i++)
	{
		if (i < l || i > r)
			Color[u[i]] = 0;
		else
			Color[u[i]] = 1;
	}
	Index = 0;
	for (int i = 0; i < u.size(); i++)
	{
		if (i == l || i == r)
		{
			v1.push_back(u[i]);
			Rank[u[i]] = ++Index;
		}
		else if (Color[u[i]] == 1)
		{
			v1.push_back(u[i]);
			Rank[u[i]] = ++Index;
		}
	}
	// cerr << "=========Start 2========= " << v1.size() << endl;
	Divide(v1, s2, Q2);
}
vector<data> s, Q;
vector<int> u;
int main()
{
	memset (dis, 0x3f, sizeof (dis));
	int n = read();
	for (int i = 1; i <= n - 3; i++)
	{
		int a = read(), b = read();
		s.push_back(data(a, b));
	}
	int m = read();
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read();
		Q.push_back(data(a, b, i));
	}
	for (int i = 1; i <= n; i++)
	{
		u.push_back(i);
		Rank[i] = i;
	}
	// cerr << "=========Start=========" << endl;
	Divide(u, s, Q);
	for (int i = 1; i <= m; i++)
		printf ("%d\n", ans[i]);
}