#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

deque<int> Q;
int N, K, L, R;
int a[50005];

int Max[(50005 << 1) + 200][16], Min[(50005 << 1) + 200][16];

int QueryMax(int l, int r)
{
    if (l > N || r < 0) return -0x3f3f3f3f;
    if (l <= 0) l = 1;
    if (r > N) r = N;
    int k = 0;
    while ((1 << k) <= (r - l + 1)) k++; k--;
    return max(Max[l][k], Max[r - (1 << k) + 1][k]);
}

int QueryMin(int l, int r)
{
    if (l > N || r < 0) return 0x3f3f3f3f;
    if (l <= 0) l = 1;
    if (r > N) r = N;
    int k = 0;
    while ((1 << k) <= (r - l + 1)) k++; k--;
    return min(Min[l][k], Min[r - (1 << k) + 1][k]);
}

bool Judge(double mid)
{
//	printf ("%.4lf\n", mid);
	Q.clear();
    for (int i = L + 1; i <= N; i++)
    {
    	while (!Q.empty() && Q.front() < i - R + 1) Q.pop_front();
    	while (!Q.empty() && a[Q.back()] - mid * Q.back() > a[i - L] - mid * (i - L)) Q.pop_back();
    	Q.push_back(i - L);
//		printf ("1: %d %.4lf %.4lf\n", Q.front(), a[Q.empty() ? 0 : Q.front()] - mid * (Q.empty() ? 0 :Q.front()), (a[i] - mid * (i + K)) - a[Q.empty() ? 0 : Q.front()] - mid * (Q.empty() ? 0 :Q.front()));
    	if ((a[i] - mid * (i + K)) > a[Q.empty() ? 0 : Q.front()] - mid * (Q.empty() ? 0 :Q.front())) return 1;
	}
	Q.clear();
	for (int i = N - L; i >= 1; i--)
	{
		while (!Q.empty() && Q.front() > i + R - 1) Q.pop_front();
		while (!Q.empty() && a[Q.back()] + mid * (Q.back() + K) > a[i + L] + mid * (i + L + K)) Q.pop_back();
		Q.push_back(i + L);
//		printf("2: %.4lf %.4lf\n", a[Q.empty() ? 0 : Q.front()] + ((Q.empty() ? 0 :Q.front()) + K) * mid, a[i] + mid * i - a[Q.empty() ? 0 : Q.front()] + ((Q.empty() ? 0 :Q.front()) + K) * mid);
		if (a[i] + mid * i > a[Q.empty() ? 0 : Q.front()] + ((Q.empty() ? 0 :Q.front()) + K) * mid) return 1;
	}
//	printf ("\n");
	return 0;
}

int main()
{
    int t = read();
    while (t--)
    {
        N = read(), K = read(), L = read(), R = read();
        memset (Max, -0x3f, sizeof(Max));
        memset (Min, 0x3f, sizeof(Min));
        for (int i = 1; i <= N; i++)
            a[i] = read(), Max[i][0] = Min[i][0] = a[i];
        for (int i = 1; i <= 15; i++)
            for (int j = 1; j <= N; j++)
            {
                Max[j][i] = max(Max[j][i - 1], Max[j + (1 << (i - 1))][i - 1]);
                Min[j][i] = min(Min[j][i - 1], Min[j + (1 << (i - 1))][i - 1]);
            }
        double ans = 0;
        for (int i = L; i <= N; i++)
        	ans = max(ans, ((double)QueryMax(i - L + 1, i) - QueryMin(i - L + 1, i)) / (L - 1 + K));
        double r = 1e3, l = 0;
//        printf ("%.4lf\n",ans);
		while (l + 1e-6 <= r)
        {
            double mid = (l + r) / 2;
            if (Judge(mid)) l = mid;
            else r = mid;
        }
        printf ("%.4lf\n", max(ans, l));
    }
}
