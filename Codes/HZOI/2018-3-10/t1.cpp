#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char s[500];
struct BigNum
{
    bitset<300> a;
    BigNum operator + (const BigNum &b)
    {
        BigNum Ans = *this;
        BigNum Carry = b;
        bitset<300> tmp;
        while (Carry.a.count())
        {
            tmp = Ans.a;
            Ans.a = tmp ^ Carry.a;
            Carry.a = (tmp & Carry.a) << 1;
        }
        return Ans;
    }
    BigNum operator * (int c)
    {
        BigNum ans;
        for (int i = 1; i <= c; i++)
            ans = ans + *this;
        return ans;
    }
    void print(int x)
    {
        for (int i = x - 1; i >= 0; i--)
            printf ("%d", (int)a[i]);
    }
}po10[201], to[201];
vector<BigNum> f[205];
int main()
{
    int n = read();
    po10[0].a = 1;
    for (int i = 1; i <= 200; i++) po10[i] = po10[i - 1] * 10;
    to[0].a = 1;
    for (int i = 1; i <= 200; i++) to[i].a = to[i - 1].a << 1;
    for (int i = 1; i <= 200; i++) 
        f[i].push_back(po10[i - 1]);
    for (int i = 1; ; i++)
    {
        if (f[i].size() >= n)
        {
            f[i][n - 1].print(i);
            break;
        }
        n -= f[i].size();
        for (auto v : f[i])
        {
            long long t = i + 1;
            for (BigNum j = po10[i], k = to[i]; (!(v.a & k.a).count()) && t <= 200; j = j * 10, t++, k.a <<= 1)
                f[t].push_back(v + j);
        }
    }
}