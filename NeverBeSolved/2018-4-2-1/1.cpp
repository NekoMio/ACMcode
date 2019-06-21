# include <stdio.h>
# include <iostream>
# include <cstring> 
# include <algorithm> 
# define RG register 
# define REP(i, a, b) for (RG int i = (a), i##__end = (b); i <= i##__end; ++i)
const int MAXN = 4e5 + 5; 
const int Inf = 0x3f3f3f3f; 
int val[MAXN], n, Q, st[21][MAXN << 1], bin[25], Log[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
	RG int x = 0, f = 1; char ch = getc;
	for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
	return x * f;
}

inline void gmin(int &x, const int &y) {
	if (x > y) x = y; 
}

inline int Query(int x, int y) {
	if (x > y) std::swap(x, y); 
	RG int len = Log[y - x + 1];
	return std::min(st[len][x], st[len][y - bin[len] + 1]);
}

inline int Query(int x1, int y1, int x2, int y2) {
	int Ans = Inf;  
	if (x1 <= x2) {
		gmin(Ans, abs(val[x2] - y2) + 1);
		for (int i = x2 - 1; i >= x1; --i) {
			if (Query(i, x2) < val[i]) continue;
			gmin(Ans, abs(val[i] - y2) + 1);
		}
		for (int i = x1 - 1; i; --i) {
			RG int t = Query(i, x2);
			gmin(Ans, abs(t - y2) + (x1 - i) * 2 + (std::min(Query(i, x1), y1) < t));
		}
		for (int i = x2 + 1; i <= n; ++i) {
			RG int t = Query(x2, i);
			gmin(Ans, abs(t - y2) + (i - x2) * 2 + (std::min(Query(x1, i), y1) < t));
		}
	}
	else {
		gmin(Ans, abs(val[x2] - y2) + 1);
		for (int i = x2 + 1; i <= x1; ++i) {
			if (Query(x2, i) < val[i]) continue; 
			gmin(Ans, abs(val[i] - y2) + 1);
		}
//		printf("%d\n", Ans); 
		for (int i = x1 + 1; i <= n; ++i) {
			RG int t = Query(x2, i);
			gmin(Ans, abs(t - y2) + (i - x1) * 2 + (std::min(Query(x1, i), y1) < t));
		}
		for (int i = x2 - 1; i; --i) {
			RG int t = Query(i, x2);
			gmin(Ans, abs(t - y2) + (x2 - i) * 2 + (std::min(Query(i, x1), y1) < t));
		}
	}
	return Ans; 
}

int main() {
//	freopen("T1.in", "r", stdin);
//	freopen("T1.out", "w", stdout);
	n = read();
	REP (i, 1, n) val[i] = read(), st[0][i] = val[i];  
	bin[0] = 1;
	REP (i, 1, 20) bin[i] = bin[i - 1] << 1;
	REP (i, 2, n) Log[i] = Log[i >> 1] + 1;
	REP (j, 1, 19) 
		for (int i = 1; i + bin[j] - 1 <= n; ++i)
			st[j][i] = std::min(st[j - 1][i], st[j - 1][i + bin[j - 1]]);
	Q = read();
	RG int x1, y1, x2, y2, Ans;
	while (Q --) {
		x1 = read(), y1 = read(), x2 = read(), y2 = read(); 
		Ans = Inf; 
		int to = std::min(y1, Query(x1, x2)), t = abs(x1 - x2);
		gmin(Ans, abs(to - y2));
		gmin(Ans, y2 + 1);
		gmin(Ans, Query(x1, y1, x2, y2));
		Ans += t; 
		printf("%d\n", Ans); 
	}
	return 0;
}