#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> a, b, c;
int main(int argc, char const *argv[])
{
    int n, s;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &s);
        a.push_back(s);
    }
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d", &s);
        b.push_back(s);
    }
    for (int i = 0; i < n - 2; i++)
    {
        scanf("%d", &s);
        c.push_back(s);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    for (auto i = a.begin(), j = b.begin(); i != a.end(); j++, i++)
    {
        if (j == b.end() || *i != *j)
        {
            cout << *i << endl;
            break;
        }
    }
    for (auto i = b.begin(), j = c.begin(); i != b.end(); j++, i++)
    {
        if (j == c.end() || *i != *j)
        {
            cout << *i << endl;
            break;
        }
    }
    return 0;
}
