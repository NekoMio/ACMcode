#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
inline long long read()
{
    long long x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
long double u[3];
int main()
{
	u[0] = read(), u[1] = read();
	long long a = read(), b = read(), c = read(), n = read();
	for (int i = 2; i <= n; i++)
	{
		u[i % 3] = a + 1.0 * b / u[(i + 2) % 3] + 1.0 * c / (u[(i + 1) % 3] * u[(i + 2) % 3]);
		printf ("%.10f\n", double(u[i % 3]));
		if (abs(u[i % 3] - u[(i + 2) % 3]) <= 3e-7)
		{
			// printf ("%d\n", i);
			printf ("%.10f\n", double(u[i % 3]));
			return 0;
		}
	}
	printf ("%.10f\n", double(u[n % 3]));
}
