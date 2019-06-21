#include "quantumbreak.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;
double q = sqrt(0.5);
double C[2][2] = {{q, q}, {q, -q}};
vector<int> vc;
int Num(unsigned int x)
{
	unsigned int tmp = x
					 - ((x >> 1) & 033333333333)
					 - ((x >> 2) & 011111111111);
	tmp = (tmp + (tmp >> 3)) & 030707070707;
	return tmp % 63;
}
int query_xor(int n, int t)
{
	int ans = 0;
	for (int j = 0; j <= 20; j++)
	{
		for (int i = 0; i < n; i++)
			manipulate(C, i);
		vc.push_back(query());
	}
	// for (auto x : vc)
		// printf ("%d\n", x);
	for (int i = 1; i < (1 << n); i++)
	{
		bool flag = 0;
		for (auto x : vc)
		{
			// if (i == 42163) printf ("%d\n", Num(x & i));
			if (Num(x & i) & 1)
			{
				flag = 1;
				break;
			}
		}
		if (!flag) return i;
	}
	// printf ("%d\n", ans);
	return 0;
}

