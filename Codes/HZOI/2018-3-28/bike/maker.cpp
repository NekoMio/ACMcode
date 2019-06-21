#include <bits/stdc++.h>
using namespace std;

int main()
{
	srand(time(NULL));
	int n;
	scanf ("%d", &n);
	printf ("%d %d\n", n, rand() % (min(n, 20)) + 1);
	for (int i = 1; i <= n; i++)
		printf ("%d ", rand() % 99 + 1);
	printf("\n");
	for (int i = 1; i <= n - 1; i++)
		printf ("%d ", rand() % 10 + 1);
	printf("\n");
}