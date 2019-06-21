#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int Gcd(int a, int b)
{
    return b == 0 ? a : Gcd(b, a % b);
}
set<int> st;
int a[100005];
int main()
{
    int n;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i]);
    st.insert(a[1]);
    int Min_Num = a[1], Min_Less = 0;
    int ans = 1;
    for (int i = 2; i <= n; i++)
    {
        if(Gcd(abs(a[i] - Min_Num), Min_Less) == 1 || st.count(a[i]))
        {
            ans++;
            Min_Num = a[i], Min_Less = 0;
            st.clear();
            st.insert(a[i]);
            // printf("%d\n", a[i]);
        }
        else
        {
            st.insert(a[i]);
            Min_Less = Gcd(abs(a[i] - Min_Num), Min_Less);
            Min_Num = min(a[i], Min_Num);
        }
    }
    printf("%d", ans);
    // while (1);
}