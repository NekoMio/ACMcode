#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
double ex = 1e-6;
int a[100005], Sum;
int n;
bool Judge(long double x)
{
	long double Max = -10000000, sum = 0;
	for (int i = 2; i <= n - 1; i++)
	{
		long double now = a[i] - x;
		sum += now;
		if (sum > Max)
			Max = sum;
		if (sum < 0)
			sum = 0;
	}
	// printf("%.6lf\n",Max);
	return Sum - n * x - Max >= 0;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		Sum += a[i];
	}
	// printf("%d\n", Sum);
	// while(1);
	long double l = 0, r = 1000000;
	while (r - l > ex)
	{
		long double mid = (r + l) / 2;
		if(Judge(mid))
			l = mid;
		else
			r = mid;
	}
	printf("%.3lf",(double)l);
}
