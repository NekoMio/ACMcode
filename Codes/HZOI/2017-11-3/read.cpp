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
