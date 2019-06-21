#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 50;
char s[2][50];
int len[2];
int Cnt[2][50], F[505][2], n, m, K;
int ID[200];
const int MOD = 1e9 + 7;
struct SAM
{
	int a[MAXN << 1][4], fa[MAXN << 1], Max[MAXN << 1];
	int count[4];
	int last, cnt;
	SAM()
	{
		last = ++cnt;
	}
	void clear()
	{
		memset (a, 0, sizeof (a));
		memset (fa, 0, sizeof (fa));
		memset (Max, 0, sizeof (Max));
		memset (count, 0, sizeof (count));
		cnt = 0;
		last = ++cnt;
	}
	void extend(int c)
	{
		int p = last, np = last = ++cnt;
		Max[np] = Max[p] + 1;
		while (!a[p][c] && p) a[p][c] = np, p = fa[p];
		if (!p) fa[np] = 1;
		else
		{
			int q = a[p][c];
			if (Max[q] == Max[p] + 1) fa[np] = q;
			else
			{
				int nq = ++cnt;
				Max[nq] = Max[p] + 1;
				memcpy(a[nq], a[q], sizeof (a[nq]));
				fa[nq] = fa[q];
				fa[np] = fa[q] = nq;
				while (a[p][c] == q) a[p][c] = nq, p = fa[p];
			}
		}
		count[c] = 1;
	}
}SA, SB;
struct Matrix
{
	int a[200][200];
	int n, m;
	Matrix(int _n = 0, int _m = 0)
	{
		n = _n, m = _m;
		memset (a, 0, sizeof (a));
	}
	void clear(int _n = 0, int _m = 0)
	{
		n = _n, m = _m;
		memset (a, 0, sizeof (a));
	}
	Matrix operator * (const Matrix &b)
	{
		Matrix ans(n, b.m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) if (a[i][j])
				for (int k = 1; k <= b.m; k++) if (b.a[j][k])
					ans.a[i][k] = (ans.a[i][k] + 1ll * a[i][j] * b.a[j][k] % MOD) % MOD;
		return ans;
	}
	Matrix operator ^ (int b)
	{
		Matrix ans(n, m), a = *this;
		for (int i = 1; i <= n; i++) ans.a[i][i] = 1;
		while (b)
		{
			if (b & 1) ans = ans * a;
			b >>= 1;
			a = a * a;
		}
		return ans;
	}
}B, A;
int id[50][50], cnt;
int idB[200];
int DFS(int sa, int sb)
{
	if (id[sa][sb]) return id[sa][sb];
	id[sa][sb] = ++cnt;
	idB[cnt] = sb; 
	for (int i = 0; i < 4; i++)
	{
		if (SA.count[i])
		{
			if (SB.count[i])
			{
				if (sb && sa) A.a[id[sa][sb]][DFS(SA.a[1][i], SB.a[1][i])]++;
				else if (sa) A.a[id[sa][sb]][DFS(SA.a[sa][i], SB.a[1][i])]++;
				else if (sb) A.a[id[sa][sb]][DFS(SA.a[1][i], SB.a[sb][i])]++;				
			}
			else
			{
				if (sb) A.a[id[sa][sb]][DFS(SA.a[1][i], 0)]++;
				else if (SA.a[sa][i]) A.a[id[sa][sb]][DFS(SA.a[sa][i], 0)]++;
			}
		}
		else
		{
			if (SB.count[i])
			{
				if (sa) A.a[id[sa][sb]][DFS(0, SB.a[1][i])]++;
				else if (SB.a[sb][i]) A.a[id[sa][sb]][DFS(0, SB.a[sb][i])]++;
			}
		}
	}
	return id[sa][sb];
}
int main()
{
	int T = read();
	ID['A'] = 0, ID['T'] = 1, ID['C'] = 2, ID['G'] = 3;
	while (T--)
	{
		memset (id, 0, sizeof (id));
		memset (idB,0, sizeof(idB));
		SA.clear(), SB.clear();
		n = read(), m = read(), K = read();
		scanf ("%s%s", s[0] + 1, s[1] + 1);
		for (int i = 1; i <= n; i++)
			SA.extend(ID[s[0][i]]);
		for (int i = 1; i <= m; i++)
			SB.extend(ID[s[1][i]]);
		B.clear();
		A.clear();
		for (int i = 0; i < 4; i++)
			if (SA.a[1][i])
				B.a[1][DFS(SA.a[1][i], 0)] = 1;
		++cnt;
		for (int i = 1; i <= cnt; i++)
			if (idB[i])
				A.a[i][cnt] = 1;
		A.a[cnt][cnt] = 1;
		A.n = A.m = cnt;
		B.n = 1, B.m = cnt;
		A = A ^ K;
		B = B * A;
		printf ("%d\n", B.a[1][cnt]);
	}
	// while (1);
}
