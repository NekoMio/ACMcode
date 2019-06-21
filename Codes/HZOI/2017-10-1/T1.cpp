#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
// #include <ctime>
using namespace std;
int Base = 10000;
struct BigNum1
{
	int c[10005];
	int len;
	BigNum1(int x = 0)
	{
		c[len = 1] = x;
	}
	const int operator [] (const int x)const
	{
		return c[x];
	}
	int& operator [] (const int x)
	{
		return c[x];
	}
	BigNum1 operator-(const BigNum1 &b) const
    {
        BigNum1 ans = *this;
        int m = max(len, b.len);
        for (int i = 1; i <= m; i++)
        {
            if (ans[i] < b[i])
                ans[i + 1] -= 1, ans[i] += Base;
            ans[i] -= b[i];
        }
        while (ans.len > 1 && ans[ans.len] == 0)
            ans.len--;
        return ans;
    }
	BigNum1 operator * (const int &b) const 
	{
		BigNum1 ans;
		BigNum1 a = *this;
		ans.len = len;
		int y = 0;
		for (int i = 1; i <= len; i++)
		{
			ans[i] = a[i] * b + y;
			y = ans[i] / Base;
			ans[i] %= Base;
		}
		while(y)
		{
			ans[++ans.len] = y % Base;
			y /= Base;
		}
		return ans;
	}
	BigNum1 operator / (const int &b) const 
	{
		BigNum1 ans;
		BigNum1 a = *this;
		ans.len = len;
		int y = 0;
		for (int i = len; i; i--)
		{
			ans[i] = (y + a[i]) / b;
			y = (y + a[i]) % b * Base;
		}
		while(!ans[ans.len] && ans.len > 1)
			ans.len--;
		return ans;
	}
	void print()
    {
    	printf("%d", c[len]);
        for (int i = len - 1; i >= 1; i--)
            printf("%04d", c[i]);
    }
};
BigNum1 C(int n, int m)
{
	BigNum1 ans(1);
	for (int i = 1; i <= m; i++) ans = ans * (n - i + 1);
	for (int i = 1; i <= m; i++) ans = ans / i;
	return ans;
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	// int a = clock();
	BigNum1 c1 = C(n + m, m) - C(n + m, m - 1);
	c1.print();
	// printf("%lf", (double)(clock() - a) / CLOCKS_PER_SEC);
}