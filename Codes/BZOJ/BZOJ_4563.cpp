#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int base = 10000;
struct BigNum
{
	int c[1005];
	int len;
	BigNum(int x = 0)
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
	BigNum operator * (const int &b) const 
	{
		BigNum ans;
		BigNum a = *this;
		ans.len = len;
		int y = 0;
		for (int i = 1; i <= len; i++)
		{
			ans[i] = a[i] * b + y;
			y = ans[i] / base;
			ans[i] %= base;
		}
		while(y)
		{
			ans[++ans.len] = y % base;
			y /= base;
		}
		return ans;
    }
    BigNum operator + (const BigNum &b) const 
    {
        BigNum ans;
        BigNum a = *this;
        ans.len = max(len, b.len);
        int y = 0;
        for (int i = 1; i <= ans.len; i++)
        {
            ans[i] = a[i] + b[i] + y;
            y = ans[i] / base;
            ans[i] %= base;
		}
		while (y)
		{
			ans.len++;
			ans[ans.len] += y;
			y = ans[ans.len] / base;
			ans[ans.len] %= base;
		}
		return ans;
	}
	void print()
    {
    	printf("%d", c[len]);
        for (int i = len - 1; i >= 1; i--)
            printf("%04d", c[i]);
    }
};
BigNum f[3];
int main()
{
	int n;
	scanf ("%d", &n);
	f[1] = 0;
	f[2] = 1;
	for (int i = 3; i <= n; i++)
	{
		f[i % 3] = (f[(i - 1 + 3) % 3] + f[(i - 2 + 3) % 3]) * (i - 1);
	}
	f[n % 3].print();
	return 0;
}