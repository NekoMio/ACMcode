#include <bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
    int n, m;
	scanf ("%d%d", &n, &m);
	printf ("%d %d 0\n", n, m);
	for (int i = 2; i <= n; i++)
		printf ("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % 10 + 1);
	while (m--)
	{
		int a = rand() % n + 1, b = rand() % n + 1;
		printf ("query %d %d %d\n", min(a, b), max(a, b), rand() % n + 1);
	}
}