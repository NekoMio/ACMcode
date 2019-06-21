#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char p[1000005];
int Next[1000005];
int Get_next(int m)
{
	int j = 0, k = -1;
	Next[0] = -1;
	while(j < m)
		if(k == -1 || p[j] == p[k])
			k++, j++, Next[j] = k;
		else
			k = Next[k];
}
int main()
{
	while(scanf("%s", p))
	{
		if(p[0]=='.')
			break;
		int m = strlen(p);
		Get_next(m);
		printf("%d\n",(m % (m - Next[m]) == 0 ) ? (m / (m - Next[m])) : 1);
	}
}