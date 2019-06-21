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
