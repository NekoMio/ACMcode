#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int x[250005], y[250005];
class comp
{
  public:
    bool operator()(long long a, long long b)
    {
        return y[a] < y[b];
    }
};
priority_queue<long long, vector<long long>, comp> Q;
int main()
{
    freopen("wing.in", "r", stdin);
    freopen("wing.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &x[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &y[i]);
    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += x[i];
        if (sum >= y[i])
            sum -= y[i], Q.push(i);
        else
        {
            if (!Q.empty())
            {
                if (y[Q.top()] > y[i])
                {
                    sum += y[Q.top()];
                    Q.pop();
                    sum -= y[i];
                    Q.push(i);
                }
            }
        }
    }
    printf("%d\n", Q.size());
}