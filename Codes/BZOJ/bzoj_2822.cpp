#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int base = 10000;
struct BigNum
{
	int c[100005];
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
	BigNum operator / (const int &b) const 
	{
		BigNum ans;
		BigNum a = *this;
		ans.len = len;
		int y = 0;
		for (int i = len; i; i--)
		{
			ans[i] = (y + a[i]) / b;
			y = (y + a[i]) % b * base;
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
int main()
{
	int x;
	scanf("%d", &x);
	BigNum ans(1);
	for (int i = 2; i <= x; i++)
	{
		ans = ans * (4 * i - 2) / (i + 1);
		// ans.print();
		// printf("\n");
	}
	ans.print();
}