
// Problem1000:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;
long long f(int x)
{
    if (x == 1)
        return 1;
    if (x == 2)
        return 2;
    return f(x - 1) + f(x - 2);
}
int main()
{
    int n;
    cin >> n;
    cout << f(n);
}

// Problem1001:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define LL long long
using namespace std;
struct data
{
    int s, q;
};
int main()
{
    int a, n, m, x;
    cin >> a >> n >> m >> x;
    data b[n + 1], c[n + 1];
    b[1].s = 1;
    b[1].q = 0;
    b[2].s = 0;
    b[3].s = 1;
    b[2].q = b[3].s;
    for (int i = 4; i <= n; i++)
    {
        b[i].s = b[i - 1].s + b[i - 2].s;
        b[i - 1].q = b[i].s;
    }
    c[1].s = 1;
    c[1].q = 0;
    c[2].s = 1;
    c[2].q = 0;
    for (int i = 3; i <= n; i++)
    {
        c[i].s = c[i - 1].s + b[i - 2].s;
        c[i].q = c[i - 1].q + b[i - 2].q;
    }
    //cout<<m-a*c[n-1].s<<" "<<c[n-1].q;
    //double q=(m-a*c[n-1].s)%c[n-1].q;
    if (((m - a * c[n - 1].s) % c[n - 1].q) != 0)
    {
        cout << "No answer." << endl;
        return 0;
    }
    int p = (m - a * c[n - 1].s) / c[n - 1].q;
    cout << c[x].s * a + c[x].q * p;
}

// Problem1002:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define LL long long
using namespace std;
int main()
{
    LL a[40];
    a[0] = 1;
    a[1] = 2;
    for (int i = 2; i < 40; i++)
        a[i] = a[i - 1] + a[i - 2];
    //for(int i=0;i<40;i++)
    //        cout<<a[i]<<endl;
    int k;
    cin >> k;
    int i = 0;
    while (k >= a[i])
        i++;
    i--;
    cout << "m=" << a[i - 1] << endl
         << "n=" << a[i] << endl;
    //while(1);
}

// Problem1003:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <ctime>
#define LL long long
using namespace std;
bool fu = 0;
vector<int> read();
void read(vector<LL> &so)
{
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 1000000000)
        {
            so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || so.size() == 0)
    {
        so.push_back(sum);
    }
}
vector<int> read()
{
    vector<int> so;
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 10000)
        {
            so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || so.size() == 0)
    {
        so.push_back(sum);
    }
    return so;
}
void print(vector<int> y)
{
    if (fu)
        printf("-");
    printf("%d", y[y.size() - 1]);
    for (int i = y.size() - 2; i >= 0; i--)
        printf("%04d", y[i]);
    printf("\n");
}
void print(vector<LL> y)
{
    if (fu)
        printf("-");
    printf("%d", y[y.size() - 1]);
    for (int i = y.size() - 2; i >= 0; i--)
        printf("%09d", y[i]);
    printf("\n");
}
vector<int> add(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
            b.push_back(0);
    }
    else
        for (int i = a.size(); i < b.size(); i++)
            a.push_back(0);
    int y = 0;
    vector<int> c;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        int s = a[i] + b[i] + y;
        y = s / 10000;
        s = s % 10000;
        c.push_back(s);
    }
    if (y != 0)
        c.push_back(y);
    while (c[c.size() - 1] == 0 && c.size() > 1)
    {
        c.pop_back();
    }
    return c;
}
vector<LL> add(vector<LL> a, vector<LL> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
            b.push_back(0);
    }
    else
        for (int i = a.size(); i < b.size(); i++)
            a.push_back(0);
    int y = 0;
    vector<LL> c;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        int s = a[i] + b[i] + y;
        y = s / 1000000000;
        s = s % 1000000000;
        c.push_back(s);
    }
    if (y != 0)
        c.push_back(y);
    while (c[c.size() - 1] == 0 && c.size() > 1)
    {
        c.pop_back();
    }
    return c;
}
vector<int> sub(vector<int> a, vector<int> b)
{
    vector<int> so;
    if (a.size() < b.size())
    {
        vector<int> c = a;
        a = b;
        b = c;
        fu = 1;
    }
    if (a.size() == b.size())
    {
        bool io = 0;
        int k;
        for (k = a.size() - 1; k >= 0; k--)
        {
            if (a[k] < b[k])
            {
                fu = 1;
                io = 1;
                break;
            }
            if (a[k] > b[k])
            {
                fu = 0;
                io = 1;
                break;
            }
        }
        if (!io)
        {
            so.push_back(0);
            return so;
        }
        if (fu)
        {
            vector<int> c = a;
            a = b;
            b = c;
        }
    }
    for (int i = b.size(); i < a.size(); i++)
        b.push_back(0);
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] < b[i])
        {
            a[i] += 10000;
            a[i + 1]--;
        }
        so.push_back(a[i] - b[i]);
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
vector<int> mult(vector<int> a, vector<int> b)
{
    vector<int> so(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        int y = 0;
        for (int j = 0; j < b.size(); j++)
        {
            so[i + j] += a[i] * b[j] + y;
            y = so[i + j] / 10000;
            so[i + j] %= 10000;
        }
        so[i + b.size()] = y;
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
vector<LL> mult(vector<LL> a, vector<LL> b)
{
    vector<LL> so(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        int y = 0;
        for (int j = 0; j < b.size(); j++)
        {
            so[i + j] += a[i] * b[j] + y;
            y = so[i + j] / 1000000000;
            so[i + j] %= 1000000000;
        }
        so[i + b.size()] = y;
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
template <class T>
bool compare(vector<T> a, vector<T> b)
{
    if (a.size() > b.size())
        return 1;
    if (a.size() < b.size())
        return 0;
    for (int i = a.size() - 1; i >= 0; i--)
    {
        if (a[i] < b[i])
        {
            return 0;
        }
        if (a[i] > b[i])
        {
            return 1;
        }
    }
    return 1;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
//vector<int> f(int x)
//{
//            if(x==1) {vector<int> so(1,1);return so;}
//            if(x==2) {vector<int> so(1,1);return so;}
//            return add(f(x-1),f(x-2));
//}
int main()
{
    //freopen("2.txt","r",stdin);
    //freopen("1.txt","w",stdout);
    vector<LL> s1, s2, s3;
    //s2.push_back(1);
    //    vector<vector<int> > s;
    //    s.push_back(s2);
    //    s.push_back(s2);
    //    for(int i=2;i<=1000;i++)
    //    {
    //            s.push_back(add(s[i-1],s[i-2]));
    //    }
    //    int n,m;
    //    cin>>n;
    //    while(n--)
    //    {
    //              cin>>m;
    //              print(s[m-1]);
    //    }
    read(s1);
    vector<LL> i(1, 1);
    s2.push_back(1);
    s3.push_back(1);
    for (; compare(s1, i); i = add(i, s2))
    {
        s3 = mult(s3, i);
    }
    //print(s1);
    //s2=read();
    //print(s2);
    //s3=add(s1,s2);
    //s3=sub(s1,s2);
    //s3=mult(s1,s2);
    print(s3);
    //cout<<endl<<clock();
    //while(1);
}

// Problem1006:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
int main()
{
    char a;
    string s;
    cin >> a;
    while (a != 'E')
    {
        s += a;
        cin >> a;
    }
    int h = 0, d = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'W')
            h++;
        else
            d++;
        if ((h >= 11 || d >= 11) && (abs(h - d) >= 2))
        {
            cout << h << ":" << d << endl;
            h = 0;
            d = 0;
        }
    }
    cout << h << ":" << d << endl
         << endl;
    h = 0;
    d = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'W')
            h++;
        else
            d++;
        if ((h >= 21 || d >= 21) && (abs(h - d) >= 2))
        {
            cout << h << ":" << d << endl;
            h = 0;
            d = 0;
        }
    }
    cout << h << ":" << d << endl;
    getchar();
    getchar();
}

// Problem1010:
#include <iostream>
#include <cstdio>
using namespace std;
void f(int x, char A, char B, char C)
{
    if (x == 0)
        return;
    f(x - 1, A, C, B);
    cout << x << " " << A << " " << C << endl;
    f(x - 1, B, A, C);
}
int main()
{
    int n;
    cin >> n;
    f(n, 'A', 'C', 'B');
    //while(1);
}

// Problem1012:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
double a, b, c, d;
vector<double> ans, run;
double f(double x)
{
    return a * x * x * x + b * x * x + c * x + d;
}
double sear(double x1, double x2)
{
    double mid = (x1 + x2) / 2;
    if (abs(f(mid)) < 0.001)
        return mid;
    else
    {
        if (f(mid) * f(x1) > 0)
            return sear(mid, x2);
        else
            return sear(x1, mid);
    }
}
int main()
{
    cin >> a >> b >> c >> d;
    double g = 0, l = 0;
    for (int i = -100; i <= 100; i++)
    {
        if (abs(f(i)) < 0.001)
        {
            ans.push_back(i);
            g = 0;
        }
        if (!g)
        {
            g = f(i);
            l = i;
            //run.push_back(i);
        }
        else
        {
            if (g * f(i) > 0)
                continue;
            else
            {
                run.push_back(l);
                run.push_back(i);
                g = 0;
            }
        }
    }
    int i = 0;
    while (ans.size() < 3)
    {
        ans.push_back(sear(run[i], run[i + 1]));
        i += 2;
    }
    i = 0;
    sort(ans.begin(), ans.end());
    while (i < 3)
    {
        printf("%.2lf ", ans[i]);
        i++;
    }
    //while(1);
}

// Problem1013:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;
vector<int> read()
{
    vector<int> so;
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 10000)
        {
            so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || so.size() == 0)
    {
        so.push_back(sum);
    }
    return so;
}
void print(vector<int> y)
{
    printf("%d", y[y.size() - 1]);
    for (int i = y.size() - 2; i >= 0; i--)
        printf("%04d", y[i]);
    printf("\n");
}
vector<int> add(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
            b.push_back(0);
    }
    else
        for (int i = a.size(); i < b.size(); i++)
            a.push_back(0);
    int y = 0;
    vector<int> c;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        int s = a[i] + b[i] + y;
        y = s / 10000;
        s = s % 10000;
        c.push_back(s);
    }
    if (y != 0)
        c.push_back(y);
    while (c[c.size() - 1] == 0 && c.size() > 1)
    {
        c.pop_back();
    }
    return c;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int main()
{
    vector<int> s1, s2, s3;
    s1 = read();
    //print(s1);
    s2 = read();
    //print(s2);
    s3 = add(s1, s2);
    print(s3);
    //while(1);
}

// Problem1013:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
int a[245], b[245], c[245], lena, lenb, lenc;
int main()
{
    memset(a, 0, sizeof(a));
    string s;
    cin >> s;
    lena = s.size();
    for (int i = 1; i <= lena; i++)
        a[i] = s[lena - i] - '0';
    memset(b, 0, sizeof(b));
    cin >> s;
    lenb = s.size();
    for (int i = 1; i <= lenb; i++)
        b[i] = s[lenb - i] - '0';
    memset(c, 0, sizeof(c));
    int y = 0;
    int lenc = lena > lenb ? lena : lenb;
    lenc++;
    for (int i = 1; i <= lenc; i++)
    {
        c[i] = a[i] + b[i] + y;
        y = c[i] / 10;
        c[i] %= 10;
    }
    if (y != 0)
    {
        c[lenc++] = y;
    }
    while (c[lenc] == 0 && lenc > 1)
    {
        lenc--;
    }
    for (int i = lenc; i >= 1; i--)
    {
        cout << c[i];
    }
    // while(1);
}

// Problem1013:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <ctime>
#define LL long long
using namespace std;
int max(int a, int b) { return a > b ? a : b; }
struct number
{
    vector<LL> so;
    number operator+(const number &b)
    {
        number a = b;
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        int y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 1000000000;
            s = s % 1000000000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator+=(const number &a)
    {
        *this = *this + a;
        return *this;
    }
    number operator*(const number &a)
    {
        number c;
        for (int i = 0; i < a.so.size() + so.size() + 1; i++)
            c.so.push_back(0);
        for (int i = 0; i < so.size(); i++)
        {
            int y = 0;
            for (int j = 0; j < a.so.size(); j++)
            {
                c.so[i + j] += so[i] * a.so[j] + y;
                y = c.so[i + j] / 1000000000;
                c.so[i + j] %= 1000000000;
            }
            c.so[i + a.so.size()] = y;
        }
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator*=(const number &a)
    {
        *this = *this * a;
        return *this;
    }
    bool operator>(const number &a)
    {
        if (so.size() > a.so.size())
            return 1;
        if (so.size() < a.so.size())
            return 0;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 0;
            }
            if (so[i] > a.so[i])
            {
                return 1;
            }
        }
        return 0;
    }
    bool operator<(const number &a)
    {
        if (so.size() > a.so.size())
            return 0;
        if (so.size() < a.so.size())
            return 1;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 1;
            }
            if (so[i] > a.so[i])
            {
                return 0;
            }
        }
        return 0;
    }
    // bool operator ==(const number &a){return (!(a<*this))&&(!(a>*this));}
    //       bool operator >=(const number &a){return !a<*this;}
    //       bool operator <=(const number &a){return !a>*this;}
    //       bool operator !=(const number &a){return (a>*this)||(a<*this);}
    //
};
void read(number &a)
{
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 1000000000)
        {
            a.so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || a.so.size() == 0)
    {
        a.so.push_back(sum);
    }
}
void print(number a)
{
    //if(fu) printf("-");
    printf("%d", a.so[a.so.size() - 1]);
    for (int i = a.so.size() - 2; i >= 0; i--)
        printf("%09d", a.so[i]);
    printf("\n");
}
int main()
{
    number a, b;
    read(a);
    read(b);
    print(a + b);
}

// Problem1014:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;
bool fu = 0;
vector<int> read()
{
    vector<int> so;
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 10000)
        {
            so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || so.size() == 0)
    {
        so.push_back(sum);
    }
    return so;
}
void print(vector<int> y)
{
    if (fu)
        printf("-");
    printf("%d", y[y.size() - 1]);
    for (int i = y.size() - 2; i >= 0; i--)
        printf("%04d", y[i]);
    printf("\n");
}
vector<int> add(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
            b.push_back(0);
    }
    else
        for (int i = a.size(); i < b.size(); i++)
            a.push_back(0);
    int y = 0;
    vector<int> c;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        int s = a[i] + b[i] + y;
        y = s / 10000;
        s = s % 10000;
        c.push_back(s);
    }
    if (y != 0)
        c.push_back(y);
    while (c[c.size() - 1] == 0 && c.size() > 1)
    {
        c.pop_back();
    }
    return c;
}
vector<int> sub(vector<int> a, vector<int> b)
{
    vector<int> so;
    if (a.size() < b.size())
    {
        vector<int> c = a;
        a = b;
        b = c;
        fu = 1;
    }
    if (a.size() == b.size())
    {
        bool io = 0;
        int k;
        for (k = a.size() - 1; k >= 0; k--)
        {
            if (a[k] < b[k])
            {
                fu = 1;
                io = 1;
                break;
            }
            if (a[k] > b[k])
            {
                fu = 0;
                io = 1;
                break;
            }
        }
        if (!io)
        {
            so.push_back(0);
            return so;
        }
        if (fu)
        {
            vector<int> c = a;
            a = b;
            b = c;
        }
    }
    for (int i = b.size(); i < a.size(); i++)
        b.push_back(0);
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] < b[i])
        {
            a[i] += 10000;
            a[i + 1]--;
        }
        so.push_back(a[i] - b[i]);
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int main()
{
    vector<int> s1, s2, s3;
    s1 = read();
    //print(s1);
    s2 = read();
    //print(s2);
    //s3=add(s1,s2);
    s3 = sub(s1, s2);
    print(s3);
    //while(1);
}

// Problem1014:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;
int main()
{
    int a[241] = {0}, b[241] = {0}, c[241] = {0};
    string s1, s2;
    cin >> s1 >> s2;
    if (s1.size() < s2.size())
    {
        cout << "-";
        string s = s1;
        s1 = s2;
        s2 = s;
    }
    if (s1.size() == s2.size())
    {
        if (s1 == s2)
        {
            cout << "0";
            return 0;
        }
        if (s1 < s2)
        {
            cout << "-";
            string s = s1;
            s1 = s2;
            s2 = s;
        }
    }
    int lena = s1.size(), lenb = s2.size(), lenc = lena;
    for (int i = 1; i <= lena; i++)
        a[i] = s1[lena - i] - '0';
    for (int i = 1; i <= lenb; i++)
        b[i] = s2[lenb - i] - '0';
    for (int i = 1; i <= lenc; i++)
    {
        if (a[i] < b[i])
        {
            a[i] += 10;
            a[i + 1]--;
        }
        c[i] = a[i] - b[i];
    }
    while (c[lenc] == 0 && lenc > 1)
    {
        lenc--;
    }
    for (int i = lenc; i >= 1; i--)
        cout << c[i];
    // while(1);
}

// Problem1015:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;
bool fu = 0;
vector<int> read()
{
    vector<int> so;
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 10000)
        {
            so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || so.size() == 0)
    {
        so.push_back(sum);
    }
    return so;
}
void print(vector<int> y)
{
    if (fu)
        printf("-");
    printf("%d", y[y.size() - 1]);
    for (int i = y.size() - 2; i >= 0; i--)
        printf("%04d", y[i]);
    printf("\n");
}
vector<int> add(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
            b.push_back(0);
    }
    else
        for (int i = a.size(); i < b.size(); i++)
            a.push_back(0);
    int y = 0;
    vector<int> c;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        int s = a[i] + b[i] + y;
        y = s / 10000;
        s = s % 10000;
        c.push_back(s);
    }
    if (y != 0)
        c.push_back(y);
    while (c[c.size() - 1] == 0 && c.size() > 1)
    {
        c.pop_back();
    }
    return c;
}
vector<int> sub(vector<int> a, vector<int> b)
{
    vector<int> so;
    if (a.size() < b.size())
    {
        vector<int> c = a;
        a = b;
        b = c;
        fu = 1;
    }
    if (a.size() == b.size())
    {
        bool io = 0;
        int k;
        for (k = a.size() - 1; k >= 0; k--)
        {
            if (a[k] < b[k])
            {
                fu = 1;
                io = 1;
                break;
            }
            if (a[k] > b[k])
            {
                fu = 0;
                io = 1;
                break;
            }
        }
        if (!io)
        {
            so.push_back(0);
            return so;
        }
        if (fu)
        {
            vector<int> c = a;
            a = b;
            b = c;
        }
    }
    for (int i = b.size(); i < a.size(); i++)
        b.push_back(0);
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] < b[i])
        {
            a[i] += 10000;
            a[i + 1]--;
        }
        so.push_back(a[i] - b[i]);
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
vector<int> mult(vector<int> a, vector<int> b)
{
    vector<int> so(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        int y = 0;
        for (int j = 0; j < b.size(); j++)
        {
            so[i + j] += a[i] * b[j] + y;
            y = so[i + j] / 10000;
            so[i + j] %= 10000;
        }
        so[i + b.size()] = y;
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int main()
{
    vector<int> s1, s2, s3;
    s1 = read();
    //print(s1);
    s2 = read();
    //print(s2);
    //s3=add(s1,s2);
    //s3=sub(s1,s2);
    s3 = mult(s1, s2);
    print(s3);
    //while(1);
}

// Problem1015:
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
const double pi = acos(-1.);
struct Complex
{
    double x, y;
    Complex() { ; }
    Complex(double a, double b) : x(a), y(b) {}
    Complex operator+(const Complex &a) { return Complex(x + a.x, y + a.y); }
    Complex operator-(const Complex &a) { return Complex(x - a.x, y - a.y); }
    Complex operator*(const Complex &a) { return Complex(x * a.x - y * a.y, x * a.y + y * a.x); }
    Complex operator*(const double a) { return Complex(x * a, y * a); }
    Complex Get() { return Complex(x, -y); }
} A[150005 << 3], B[150005 << 3];
int rev[150005 << 3], N, FU;
double INV;
void FFt(Complex *a, int op)
{
    Complex w, wn, t;
    for (int i = 0; i < N; i++)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = Complex(cos(op * 2 * pi / k), sin(op * 2 * pi / k));
        for (int j = 0; j < N; j += k)
        {
            w = Complex(1, 0);
            for (int i = 0; i < (k >> 1); i++, w = w * wn)
            {
                t = a[i + j + (k >> 1)] * w;
                a[i + j + (k >> 1)] = a[i + j] - t;
                a[i + j] = a[i + j] + t;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < N; i++)
            a[i] = a[i] * INV;
}
void FFt(const int *a, const int *b, int *res, int n)
{
    N = 1;
    while (N < n)
        N <<= 1;
    INV = 1. / N;
    for (int i = 0; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    for (int i = 0; i < N; i++)
        A[i].x = a[i], B[i].x = b[i];
    FFt(A, 1), FFt(B, 1);
    for (int i = 0; i < N; i++)
        A[i] = A[i] * B[i];
    FFt(A, -1);
    for (int i = 0; i < N; i++)
        res[i] = round(A[i].x);
}
char s[150005 << 2];
struct BigNum
{
    int len;
    int a[1000005];
    void read()
    {
        scanf("%s", s);
        len = strlen(s);
        for (int i = len - 1, j = 0; i >= 0; i--, j++)
            a[j] = s[i] - '0';
    }
    BigNum operator*(const BigNum &b)
    {
        BigNum ans;
        ans.len = len + b.len - 1;
        FFt(a, b.a, ans.a, ans.len + 1);
        for (int i = 0; i <= ans.len + 2; i++)
        {
            if (ans.a[i] > 9)
            {
                ans.a[i + 1] += ans.a[i] / 10;
                ans.a[i] %= 10;
            }
        }
        while (ans.a[ans.len])
            ans.len++;
        return ans;
    }
    void print()
    {
        for (int i = len - 1; i >= 0; i--)
            printf("%d", a[i]);
        printf("\n");
    }
} a, b;

int main()
{
    //freopen("bettermul.in","r",stdin);
    //freopen("bettermul.out","w",stdout);
    a.read();
    b.read();
    (a * b).print();
    //while (1)
    ;
}

// Problem1016:
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#define LL long long
using namespace std;
int max(int a, int b) { return a > b ? a : b; }
struct number
{
    vector<LL> so;
    number() { ; }
    number(const int a) { *this = a; }
    int size()
    {
        int h = (so.size() - 1) * 5;
        int k = *(so.end() - 1);
        int i = 0;
        while (k)
        {
            k /= 10;
            i++;
        }
        return i + h;
    }
    void mod(int n)
    {
        if (this->size() <= n)
            return;
        so.erase(so.begin() + (n / 5), so.end());
    }
    number operator=(const int &a)
    {
        LL y = a / 100000;
        LL s = a % 100000;
        if (y != 0)
            so.push_back(y);
        so.push_back(s);
        return *this;
    }
    number operator+(const number &b)
    {
        number a = b;
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        int y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 100000;
            s = s % 100000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator+(const int &b)
    {
        number a;
        int y = b / 100000;
        int s = b % 100000;
        a.so.push_back(s);
        a.so.push_back(y);
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 100000;
            s = s % 100000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator+=(const number &a)
    {
        *this = *this + a;
        return *this;
    }
    number operator+=(const int &a)
    {
        *this = *this + a;
        return *this;
    }
    number operator*(const int &a)
    {
        number b = a;
        return *this * b;
    }
    number operator*=(const int &a)
    {
        *this = *this * a;
        return *this;
    }
    number operator-(const int &a)
    {
        so[0] -= a;
        return *this;
    }
    number operator*(const number &a)
    {
        number c;
        for (int i = 0; i < a.so.size() + so.size() + 1; i++)
            c.so.push_back(0);
        for (int i = 0; i < so.size(); i++)
        {
            int y = 0;
            for (int j = 0; j < a.so.size(); j++)
            {
                c.so[i + j] += so[i] * a.so[j] + y;
                y = c.so[i + j] / 100000;
                c.so[i + j] %= 100000;
            }
            c.so[i + a.so.size()] = y;
        }
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator*=(const number &a)
    {
        *this = *this * a;
        return *this;
    }
    bool operator>(const number &a) const
    {
        if (so.size() > a.so.size())
            return 1;
        if (so.size() < a.so.size())
            return 0;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 0;
            }
            if (so[i] > a.so[i])
            {
                return 1;
            }
        }
        return 0;
    }
    bool operator<(const number &a) const
    {
        if (so.size() > a.so.size())
            return 0;
        if (so.size() < a.so.size())
            return 1;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 1;
            }
            if (so[i] > a.so[i])
            {
                return 0;
            }
        }
        return 0;
    }
    bool operator==(const number &a) const { return (!(a < *this)) && (!(a > *this)); }
    bool operator>=(const number &a) const { return !(a > *this); }
    bool operator<=(const number &a) const { return !(a < *this); }
    bool operator!=(const number &a) const { return (a > *this) || (a < *this); }
};
void read(number &a)
{
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 100000)
        {
            a.so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || a.so.size() == 0)
    {
        a.so.push_back(sum);
    }
}
void print(number a)
{
    //printf("%d\n",a.size());
    //a.mod(500);
    int j = 0;
    if (a.so.size() <= 100)
    {
        for (int i = a.so.size(); i < 100; i++)
        {
            printf("00000");
            j++;
            if (j % 10 == 0)
                printf("\n");
        }
        for (int i = a.so.size() - 1; i >= 0; i--)
        {
            printf("%05d", a.so[i]);
            j++;
            if (j % 10 == 0)
                printf("\n");
        }
    }
    else
    {
        printf("%05d", a.so[a.so.size() - 1]);
        j++;
        for (int i = a.so.size() - 2; i >= 0; i--)
        {
            printf("%05d", a.so[i]);
            j++;
            if (j % 10 == 0)
                printf("\n");
        }
    }
    printf("\n");
}
number pow(number n, int p)
{
    number ans = 1;
    while (p)
    {
        if (p & 1)
        {
            ans = (ans * n);
            ans.mod(500);
        }
        p = p >> 1;
        n = n * n;
        n.mod(500);
    }
    return ans;
}
int main()
{
    //freopen("1.txt","w",stdout);
    int p;
    cin >> p;
    cout << (int)(p * log10(2) + 1) << endl;
    number ans = pow((number)2, p) - 1;
    print(ans);
    //while(1);
}

// Problem1017:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <ctime>
#define LL long long
using namespace std;
bool fu = 0;
vector<int> read();
void read(vector<LL> &so)
{
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 1000000000)
        {
            so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || so.size() == 0)
    {
        so.push_back(sum);
    }
}
vector<int> read()
{
    vector<int> so;
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 10000)
        {
            so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || so.size() == 0)
    {
        so.push_back(sum);
    }
    return so;
}
void print(vector<int> y)
{
    if (fu)
        printf("-");
    printf("%d", y[y.size() - 1]);
    for (int i = y.size() - 2; i >= 0; i--)
        printf("%04d", y[i]);
    printf("\n");
}
void print(vector<LL> y)
{
    if (fu)
        printf("-");
    printf("%d", y[y.size() - 1]);
    for (int i = y.size() - 2; i >= 0; i--)
        printf("%09d", y[i]);
    printf("\n");
}
vector<int> add(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
            b.push_back(0);
    }
    else
        for (int i = a.size(); i < b.size(); i++)
            a.push_back(0);
    int y = 0;
    vector<int> c;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        int s = a[i] + b[i] + y;
        y = s / 10000;
        s = s % 10000;
        c.push_back(s);
    }
    if (y != 0)
        c.push_back(y);
    while (c[c.size() - 1] == 0 && c.size() > 1)
    {
        c.pop_back();
    }
    return c;
}
vector<LL> add(vector<LL> a, vector<LL> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
            b.push_back(0);
    }
    else
        for (int i = a.size(); i < b.size(); i++)
            a.push_back(0);
    int y = 0;
    vector<LL> c;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        int s = a[i] + b[i] + y;
        y = s / 1000000000;
        s = s % 1000000000;
        c.push_back(s);
    }
    if (y != 0)
        c.push_back(y);
    while (c[c.size() - 1] == 0 && c.size() > 1)
    {
        c.pop_back();
    }
    return c;
}
vector<int> sub(vector<int> a, vector<int> b)
{
    vector<int> so;
    if (a.size() < b.size())
    {
        vector<int> c = a;
        a = b;
        b = c;
        fu = 1;
    }
    if (a.size() == b.size())
    {
        bool io = 0;
        int k;
        for (k = a.size() - 1; k >= 0; k--)
        {
            if (a[k] < b[k])
            {
                fu = 1;
                io = 1;
                break;
            }
            if (a[k] > b[k])
            {
                fu = 0;
                io = 1;
                break;
            }
        }
        if (!io)
        {
            so.push_back(0);
            return so;
        }
        if (fu)
        {
            vector<int> c = a;
            a = b;
            b = c;
        }
    }
    for (int i = b.size(); i < a.size(); i++)
        b.push_back(0);
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] < b[i])
        {
            a[i] += 10000;
            a[i + 1]--;
        }
        so.push_back(a[i] - b[i]);
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
vector<LL> sub(vector<LL> a, vector<LL> b)
{
    vector<LL> so;
    if (a.size() < b.size())
    {
        vector<LL> c = a;
        a = b;
        b = c;
        fu = 1;
    }
    if (a.size() == b.size())
    {
        bool io = 0;
        int k;
        for (k = a.size() - 1; k >= 0; k--)
        {
            if (a[k] < b[k])
            {
                fu = 1;
                io = 1;
                break;
            }
            if (a[k] > b[k])
            {
                fu = 0;
                io = 1;
                break;
            }
        }
        if (!io)
        {
            so.push_back(0);
            return so;
        }
        if (fu)
        {
            vector<LL> c = a;
            a = b;
            b = c;
        }
    }
    for (int i = b.size(); i < a.size(); i++)
        b.push_back(0);
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] < b[i])
        {
            a[i] += 1000000000;
            a[i + 1]--;
        }
        so.push_back(a[i] - b[i]);
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
vector<int> mult(vector<int> a, vector<int> b)
{
    vector<int> so(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        int y = 0;
        for (int j = 0; j < b.size(); j++)
        {
            so[i + j] += a[i] * b[j] + y;
            y = so[i + j] / 10000;
            so[i + j] %= 10000;
        }
        so[i + b.size()] = y;
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
vector<LL> mult(vector<LL> a, vector<LL> b)
{
    vector<LL> so(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        int y = 0;
        for (int j = 0; j < b.size(); j++)
        {
            so[i + j] += a[i] * b[j] + y;
            y = so[i + j] / 1000000000;
            so[i + j] %= 1000000000;
        }
        so[i + b.size()] = y;
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
template <class T>
bool compare(vector<T> a, vector<T> b)
{
    if (a.size() > b.size())
        return 1;
    if (a.size() < b.size())
        return 0;
    for (int i = a.size() - 1; i >= 0; i--)
    {
        if (a[i] < b[i])
        {
            return 0;
        }
        if (a[i] > b[i])
        {
            return 1;
        }
    }
    return 1;
}
template <class T>
vector<T> pow(vector<T> a, vector<T> b)
{
    vector<T> so(1, 1);
    vector<T> i(1, 1);
    vector<T> j(1, 1);
    for (; compare(b, i); i = add(i, j))
    {
        so = mult(so, a);
    }
    return so;
}
int max(int a, int b)
{
    return a > b ? a : b;
}

//vector<int> f(int x)
//{
//            if(x==1) {vector<int> so(1,1);return so;}
//            if(x==2) {vector<int> so(1,1);return so;}
//            return add(f(x-1),f(x-2));
//}
int main()
{
    //freopen("2.txt","r",stdin);
    //freopen("1.txt","w",stdout);
    vector<LL> s1, s2, s3;
    //s2.push_back(1);
    //    vector<vector<int> > s;
    //    s.push_back(s2);
    //    s.push_back(s2);
    //    for(int i=2;i<=1000;i++)
    //    {
    //            s.push_back(add(s[i-1],s[i-2]));
    //    }
    //    int n,m;
    //    cin>>n;
    //    while(n--)
    //    {
    //              cin>>m;
    //              print(s[m-1]);
    //    }
    read(s1);

    vector<LL> i(1, 1);
    s2.push_back(2);
    //s1=mult(s1,s2);
    s3 = pow(s2, s1);
    s3 = sub(s3, i);
    s3 = mult(s3, s2);
    //    s3.push_back(1);
    //    for(;compare(s1,i);i=add(i,s2))
    //    {
    //         s3=mult(s3,i);
    //    }
    //print(s1);
    //s2=read();
    //print(s2);
    //s3=add(s1,s2);
    //s3=sub(s1,s2);
    //s3=mult(s1,s2);
    print(s3);
    //cout<<endl<<clock();
    //while(1);
}

// Problem1019:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
void print(vector<int> so);
bool check(vector<int> a);
int main()
{
    vector<int> s1, s2, s3;
    int n, sum = 0;
    cin >> n;
    string s;
    cin >> s;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] >= '0' && s[i] <= '9')
            s1.push_back(s[i] - '0');
        if (s[i] >= 'a' && s[i] <= 'z')
            s1.push_back(s[i] - 'a' + 10);
    }
    //print(s1);
    //while(1);
    for (int i = 1; i <= 30; i++)
    {
        s2 = s1;
        //print(s2);
        reverse(s2.begin(), s2.end());
        //print(s2);
        //while(1);
        s3.clear();
        if (check(s1))
        {
            print(s1);
            cout << sum;
            return 0;
        }
        int y = 0;
        for (int i = 0; i < s1.size(); i++)
        {
            int s = s1[i] + s2[i] + y;
            y = s / n;
            s %= n;
            s3.push_back(s);
        }
        if (y != 0)
        {
            s3.push_back(y);
        }
        while (s3[s3.size() - 1] == 0 && s3.size() > 1)
        {
            s3.pop_back();
        }
        sum++;
        s1 = s3;
    }
    cout << "impossible";
    //print(s3);
    //while(1);
}
bool check(vector<int> a)
{
    for (int i = 0; i < (a.size() / 2); i++)
    {
        if (a[i] != a[a.size() - i - 1])
            return 0;
    }
    return 1;
}
void print(vector<int> so)
{
    for (int i = so.size() - 1; i >= 0; i--)
    {
        if (so[i] >= 10)
            cout << char(so[i] - 10 + 'a');
        else
            cout << so[i];
    }
    cout << endl;
}

// Problem1026:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
int main()
{
    string a;
    int s[9], j = 0, sum = 0;
    cin >> a;
    for (int i = 0; i < 11; i++)
    {
        if (i != 1 && i != 5)
        {
            s[j] = a[i] - 48;
            j++;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        sum += s[i] * (i + 1);
    }
    int b = sum % 11;
    if (b == 10)
    {
        if (a[12] == 'X')
            cout << "Right";
        else
        {
            a.erase(12, 1);
            a = a + 'X';
            cout << a;
        }
    }
    else
    {
        if ((a[12] - 48) == b)
            cout << "Right";
        else
        {
            a.erase(12, 1);
            a = a + (char)(b + 48);
            cout << a;
        }
    }
    getchar();
    getchar();
}

// Problem1028:
#include <iostream>
#include <queue>
using namespace std;
int main()
{
    priority_queue<int, vector<int>, greater<int>> a;
    int n;
    ;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int m;
        cin >> m;
        a.push(m);
    }
    int sum = 0, u = 0;
    while (a.size() != 1)
    {
        int p = a.top();
        a.pop();
        int q = a.top();
        a.pop();
        u = p + q;
        sum += u;
        a.push(u);
    }
    cout << sum << endl;
    //while(1);
}

// Problem1029:
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    vector<int> a;
    vector<int>::iterator s1, s2;
    int w, n, c;
    cin >> w >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> c;
        a.push_back(c);
    }
    sort(a.begin(), a.end());
    s1 = a.begin();
    s2 = a.end() - 1;
    //cout<<*s1<<endl;
    int sum = 0;
    //while(1);
    while (s1 <= s2)
    {
        if (*s1 + *s2 <= w)
        {
            sum++;
            s1++;
            s2--;
        }
        else
        {
            s2--;
            sum++;
        }
    }
    cout << sum;
}

// Problem1031:
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;
int comp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second > b.second;
}
int comp1(const int &a, const int &b)
{
    return a < b;
}
int main()
{
    map<int, int> s1, s2;
    //vector<int> x3,y3;
    //priority_queue<map<int,int>,vector<map<int,int> >,comp> a,b;
    vector<pair<int, int>>::iterator o1, o2;
    map<int, int>::iterator it;
    int m, n, k, l, d;
    int x1, y1, x2, y2;
    cin >> m >> n >> k >> l >> d;
    for (int i = 1; i <= d; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2)
        {
            it = s1.find(min(y1, y2));
            if (it == s1.end())
            {
                s1[min(y1, y2)] = 1;
            }
            else
            {
                it->second++;
            }
        }
        else
        {
            it = s2.find(min(x1, x2));
            if (it == s2.end())
            {
                s2[min(x1, x2)] = 1;
            }
            else
            {
                it->second++;
            }
        }
    }
    int l1 = s1.size(), l2 = s2.size();
    vector<pair<int, int>> s3(s1.begin(), s1.end());
    vector<pair<int, int>> s4(s2.begin(), s2.end());
    sort(s3.begin(), s3.end(), comp);
    sort(s4.begin(), s4.end(), comp);
    o1 = s3.begin(), o2 = s4.begin();
    vector<int> s5, s6;
    while (l2 > 0 && k > 0)
    {
        s5.push_back(o2->first);
        k--;
        o2++;
        l2--;
    }
    while (l1 > 0 && l > 0)
    {
        s6.push_back(o1->first);
        l--;
        o1++;
        l1--;
    }
    int p1 = s5.size(), p2 = s6.size();
    sort(s5.begin(), s5.end(), comp1);
    sort(s6.begin(), s6.end(), comp1);
    vector<int>::iterator o3 = s5.begin(), o4 = s6.begin();
    while (p1)
    {
        cout << *o3 << " ";
        o3++;
        p1--;
    }
    cout << endl;
    while (p2)
    {
        cout << *o4 << " ";
        o4++;
        p2--;
    }
    //while(1);
}

// Problem1035:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f(int x)
{
    return x == 0 ? 1 : x * f(x - 1);
}
int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%5d", a[i]);
    }
    cout << endl;
    int s = f(n);
    for (int i = 1; i < s; i++)
    {
        next_permutation(a, a + n);
        for (int i = 0; i < n; i++)
        {
            printf("%5d", a[i]);
        }
        cout << endl;
    }
    //while(1);
}

// Problem1038:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;
char a[12] = "";
int main()
{
    gets(a);
    bool first = 1;
    if (strlen(a) == 1)
    {
        if (a[0] == '0')
            cout << "0";
    }
    if (a[0] == '-')
    {
        if (strlen(a) == 2)
            if (a[1] == '0')
                cout << "-" << '0';
        for (int i = strlen(a) - 1; i >= 1; i--)
        {
            if (first)
            {
                if (a[i] != '0')
                {
                    cout << "-" << a[i];
                    first = 0;
                }
            }
            else
                cout << a[i];
        }
    }
    else
    {
        for (int i = strlen(a) - 1; i >= 0; i--)
        {
            if (first)
            {
                if (a[i] != '0')
                {
                    cout << a[i];
                    first = 0;
                }
            }
            else
                cout << a[i];
        }
    }
    //    while(1);
}

// Problem1039:
#include <cstring>
//#include<cmath>
//#include<windows.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 100000000
#define LL long long
using namespace std;
bool b[10000] = {0};
int sum = 0, a[10000], s[10000];
int search(int i);
int print(int);
int n, c, ans = 0, q = 1, sum2 = 0;
int search(int i)
{
    int j;
    for (j = q; j <= n; j++)
        if (!b[j])
        {
            ans += a[j];
            if (ans > c)
            {
                ans -= a[j];
                continue;
            }
            s[i] = j;
            b[j] = 1;
            if (ans == c)
            {
                print(i);
                exit(0);
            }
            else
            {
                q = j;
                search(i + 1);
            }
            b[j] = 0;
            ans -= a[j];
        }
}
int main()
{
    //freopen("1.txt","r",stdin);
    //freopen("3.txt","w",stdout);
    cin >> n >> c;
    for (int i = 1; i <= n; i++)
    {
        //cin>>a[i];
        scanf("%d", &a[i]);
        sum2 += a[i];
    }
    if (sum2 < c)
        goto end;
    search(1);
    if (sum == 0)
    end:
        cout << "No Solution!";
    //cout<<((double)clock()/CLOCKS_PER_SEC);
    //while(1);
}

int print(int n)
{
    int i;
    for (i = 1; i <= n; i++)
        cout << a[s[i]] << " ";
    cout << endl;
    //cout<<((double)clock()/CLOCKS_PER_SEC);
}

// Problem1040:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
bool p[1000000], b[21] = {0};
int a[21], sum = 0, l = 0, k, n, c = 1;
void prime();
int search(int);
void prime()
{
    memset(p, 1, sizeof(p));
    p[1] = 0;
    for (int i = 2; i <= 1000; i++)
    {
        if (p[i])
            for (int j = i * i; j <= 1000000; j += i)
                p[j] = 0;
    }
}
int main()
{
    prime();
    //for(int i=1;i<=100;i++)
    //           if(p[i])cout<<i<<" ";
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    search(1);
    printf("%d", l);
    //while(1);
}
int search(int i)
{
    for (int j = c; j <= n; j++)
    {
        if (!b[j])
        {
            //if(i!=k&&p[sum+a[j]]) continue;
            b[j] = 1;
            sum += a[j];
            if (i == k && p[sum])
                l++;
            else if (i < k)
            {
                c = j;
                search(i + 1);
            }
            b[j] = 0;
            sum -= a[j];
        }
    }
}

// Problem1041:
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
vector<int> a, c;
int ans = 0;
void qsort(int r, int l)
{
    if (r == l)
        return;
    int mid = (r + l) / 2;
    qsort(r, mid);
    qsort(mid + 1, l);
    int i = r, j = mid + 1;
    int it = mid, jt = l;
    while (i <= it && j <= jt)
    {
        if (a[i] > a[j])
        {
            ans += mid - i + 1;
            c.push_back(a[j]);
            j++;
        }
        else
        {
            c.push_back(a[i]);
            i++;
        }
    }
    while (i <= it)
    {
        c.push_back(a[i]);
        i++;
    }
    while (j <= jt)
    {
        c.push_back(a[j]);
        j++;
    }
    //for(int i=0;i<c.size();i++)
    //     {
    //             cout<<c[i]<<" ";
    //     }
    //     cout<<endl;
    vector<int>::iterator it2 = c.begin(), it1 = a.begin() + r;
    while (it2 != c.end())
    {
        *it1 = *it2;
        it1++;
        it2++;
    }
    c.clear();
}
void read()
{
    int n, b;
    scanf("%d", &n);
    //a.push_back(0);
    while (n--)
    {
        scanf("%d", &b);
        a.push_back(b);
    }
}
int main()
{
    read();
    qsort(0, a.size() - 1);
    //for(int i=0;i<a.size();i++)
    //    {
    //            cout<<a[i]<<" ";
    //    }
    //while(1);
    cout << ans;
}

// Problem1044:
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;
struct data
{
    double di, pi;
};
int main()
{
    double d1, c, d2, p, di, pi;
    int n;
    vector<data> a;
    cin >> d1 >> c >> d2 >> p >> n;
    if (n == 0)
    {
        if (d2 * c >= d1)
        {
            printf("%.2lf\n", p * (d1 / d2));
            return 0;
        }
        else
        {
            cout << "No Solution" << endl;
            return 0;
        }
    }
    //a.push(data{0,p});
    for (int i = 1; i <= n; i++)
    {
        cin >> di >> pi;
        a.push_back((data){di, pi});
    }
    int o = 0;
    double ans = 0;
    //vector<data>::iterator o=a.begin();
    double ps = p, c1 = 0;
    data s2 = (data){0, p};
    while (1)
    {
        double s = c * d2, minn = 10000000;
        int pl = -1;
        while (a[o].di <= s + s2.di && o < n)
        {
            if (a[o].pi < minn)
            {
                minn = a[o].pi;
                pl = o;
            }
            o++;
        }
        o = pl + 1;
        if (pl == -1)
        {
            if ((d1 - s2.di) / d2 > c)
            {
                cout << "No Solution" << endl;
                return 0;
            }
            ans += s2.pi * (d1 / d2 - c1);
            break;
        }
        if (a[pl].pi > s2.pi)
        {
            if (s > d1)
            {
                ans += s2.pi * (d1 / d2 - c1);
                break;
            }
            ans += s2.pi * (c - c1);
            d1 -= (a[pl].di - s2.di);
            c1 = c - (a[pl].di - s2.di) / d2;
            s2 = a[pl];
        }
        else
        {
            ans += s2.pi * ((a[pl].di - s2.di) / d2);
            d1 -= (a[pl].di - s2.di);
            c1 = 0;
            s2 = a[pl];
        }
    }
    printf("%.2lf\n", ans);
    //while(1);
}

// Problem1045:
#include <iostream>
#include <string>
#include <queue>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
int main()
{
    LL b, p, k;
    cin >> b >> p >> k;
    LL b1 = b, p1 = p, k1 = k;
    LL ans = 1;
    b %= k;
    while (p > 0)
    {
        if (p & 1)
            ans = (ans * b) % k;
        p = p >> 1;
        b = (b * b) % k;
    }
    cout << b1 << "^" << p1 << " mod " << k1 << "=" << ans << endl;
    getchar();
    getchar();
    //getchar();
    //getchar();
}

// Problem1046:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iomanip>
using namespace std;
int n, t = 0;
void solve(int q)
{
    if (q == 4)
    {
        cout << "step" << setw(2) << t++ << ":";
        for (int i = 1; i <= q; i++)
            cout << "o";
        for (int i = 1; i <= q; i++)
            cout << "*";
        cout << "--";
        for (int i = q; i < n; i++)
            cout << "o*";
        cout << endl;
        cout << "step" << setw(2) << t++ << ":";
        cout << "ooo--***o*";
        for (int i = 4; i < n; i++)
            cout << "o*";
        cout << endl;
        cout << "step" << setw(2) << t++ << ":";
        cout << "ooo*o**--*";
        for (int i = 4; i < n; i++)
            cout << "o*";
        cout << endl;
        cout << "step" << setw(2) << t++ << ":";
        cout << "o--*o**oo*";
        for (int i = 4; i < n; i++)
            cout << "o*";
        cout << endl;
        cout << "step" << setw(2) << t++ << ":";
        cout << "o*o*o*--o*";
        for (int i = 4; i < n; i++)
            cout << "o*";
        cout << endl;
        cout << "step" << setw(2) << t++ << ":";
        cout << "--o*o*o*o*";
        for (int i = 4; i < n; i++)
            cout << "o*";
        cout << endl;
        //while(1);
    }
    else
    {
        cout << "step" << setw(2) << t++ << ":";
        for (int i = 1; i <= q; i++)
            cout << "o";
        for (int i = 1; i <= q; i++)
            cout << "*";
        cout << "--";
        for (int i = q; i < n; i++)
            cout << "o*";
        cout << endl;
        cout << "step" << setw(2) << t++ << ":";
        for (int i = 1; i <= q - 1; i++)
            cout << "o";
        cout << "--";
        for (int i = 1; i <= q - 1; i++)
            cout << "*";
        cout << "o*";
        for (int i = q; i < n; i++)
            cout << "o*";
        cout << endl;
        solve(q - 1);
    }
}
int main()
{
    //freopen("1.txt","w",stdout);
    cin >> n;
    solve(n);
    //while(1);
}

// Problem1047:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int a[200][200];
int pow(int x)
{
    int ans = 1;
    for (int i = 1; i <= x; i++)
    {
        ans *= 2;
    }
    return ans;
}
void full(int n)
{
    if (n == 2)
    {
        a[1][1] = 1;
        a[1][2] = 2;
        a[2][1] = 2;
        a[2][2] = 1;
        return;
    }
    else
    {
        full(n / 2);
        int k = 1, k2 = 1;
        for (int i = n / 2 + 1; i <= n; i++)
        {
            for (int j = n / 2 + 1; j <= n; j++)
            {
                a[i][j] = a[k][k2];
                k2++;
            }
            k++;
            k2 = 1;
        }
        k = 1;
        k2 = 1;
        for (int i = 1; i <= n / 2; i++)
        {
            for (int j = n / 2 + 1; j <= n; j++)
            {
                a[i][j] = a[k][k2] + n / 2;
                k2++;
            }
            k++;
            k2 = 1;
        }
        k = 1;
        k2 = n / 2 + 1;
        for (int i = n / 2 + 1; i <= n; i++)
        {
            for (int j = 1; j <= n / 2; j++)
            {
                a[i][j] = a[k][k2];
                k2++;
            }
            k++;
            k2 = n / 2 + 1;
        }
    }
}
void print(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    memset(a, 0, sizeof(a));
    int m;
    cin >> m;
    int n = pow(m);
    full(n);
    print(n);
    //while(1);
}

// Problem1049:
#include <iostream>
#include <algorithm>
using namespace std;
int v[105], m[105], f[1005];
int main()
{
    int V, M;
    cin >> V >> M;
    for (int i = 1; i <= M; i++)
        cin >> v[i] >> m[i];
    for (int i = 1; i <= M; i++)
    {
        for (int vi = V; vi >= v[i]; vi--)
        {
            f[vi] = max(f[vi], f[vi - v[i]] + m[i]);
        }
    }
    cout << f[V] << endl;
}

// Problem1050:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
bool f[1005];
int s[7];
int main()
{
    for (int i = 1; i <= 6; i++)
        cin >> s[i];
    for (int i1 = 0; i1 <= s[1]; i1++)
    {
        for (int i2 = 0; i2 <= s[2]; i2++)
        {
            for (int i3 = 0; i3 <= s[3]; i3++)
            {
                for (int i4 = 0; i4 <= s[4]; i4++)
                {
                    for (int i5 = 0; i5 <= s[5]; i5++)
                    {
                        for (int i6 = 0; i6 <= s[6]; i6++)
                        {
                            f[i1 * 1 + i2 * 2 + i3 * 3 + i4 * 5 + i5 * 10 + i6 * 20] = 1;
                        }
                    }
                }
            }
        }
    }
    int sum = 0;
    for (int i = 1; i <= 1000; i++)
        if (f[i])
            sum++;
    cout << "Total=" << sum << endl;
}

// Problem1050:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
bool f[1005];
int s[7];
int c[7] = {0, 1, 2, 3, 5, 10, 20};
int main()
{
    int sum = 0;
    for (int i = 1; i <= 6; i++)
        cin >> s[i];
    f[0] = 1;
    for (int i = 1; i <= 6; i++)
    {
        for (int v = 1000; v >= c[i]; v--)
        {
            for (int j = 1; j <= s[i]; j++)
            {
                if (v >= c[i] * j && f[v] == 0 && f[v - c[i] * j] != 0)
                {
                    f[v] = f[v - c[i] * j];
                    sum++;
                }
            }
        }
    }
    cout << "Total=" << sum << endl;
}

// Problem1051:
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int w[30], v[30], f[30005];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> v[i] >> w[i];
        w[i] *= v[i];
    }
    for (int i = 1; i <= m; i++)
        for (int vi = n; vi >= v[i]; vi--)
            f[vi] = max(f[vi], f[vi - v[i]] + w[i]);
    cout << f[n] << endl;
}

// Problem1052:
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int w[10005], v[10005], f[10005];
int main()
{
    int N, M;
    cin >> M >> N;
    for (int i = 1; i <= N; i++)
        cin >> w[i] >> v[i];
    for (int i = 1; i <= N; i++)
        for (int vi = v[i]; vi <= M; vi++)
            f[vi] = max(f[vi], f[vi - v[i]] + w[i]);
    cout << f[M] << endl;
}

// Problem1053:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[1005];
int w[11];
int main()
{
    for (int i = 1; i <= 10; i++)
        cin >> w[i];
    int V;
    cin >> V;
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= 10; i++)
    {
        for (int v = i; v <= V; v++)
        {
            f[v] = min(f[v], f[v - i] + w[i]);
        }
    }
    cout << f[V] << endl;
}

// Problem1054:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[405][405];
int w[55], vi[55], c[55];
int n, V, M;
int main()
{

    cin >> V >> M >> n;
    for (int i = 1; i <= n; i++)
        cin >> vi[i] >> w[i] >> c[i];
    for (int i = 1; i <= n; i++)
    {
        for (int v = V; v >= vi[i]; v--)
        {
            for (int m = M; m >= w[i]; m--)
            {
                f[v][m] = max(f[v][m], f[v - vi[i]][m - w[i]] + c[i]);
            }
        }
    }
    cout << f[V][M] << endl;
    //while(1);
}

// Problem1055:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[10005];
int w[10005], c[10005], s[10005];
int n, m, maxl;
void ZOPack(int cost, int weight);
void CPack(int cost, int weight);
int main()
{

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> c[i] >> w[i] >> s[i];
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 0)
        {
            CPack(c[i], w[i]);
        }
        else
        {
            int k = 1;
            while (k < s[i])
            {
                ZOPack(k * c[i], k * w[i]);
                s[i] = s[i] - k;
                k *= 2;
            }
            ZOPack(s[i] * c[i], s[i] * w[i]);
        }
        //cout<<endl;
        //cout<<i<<":"<<endl;
        //for(int j=1;j<=m;j++)cout<<f[j]<<" ";
        // cout<<endl;
    }
    cout << f[m] << endl;
    //while(1);
}
void ZOPack(int cost, int weight)
{
    for (int v = m; v >= cost; v--)
    {
        f[v] = max(f[v], f[v - cost] + weight);
        //maxl=max(maxl,f[v]);
    }
}
void CPack(int cost, int weight)
{
    for (int v = cost; v <= m; v++)
    {
        f[v] = max(f[v], f[v - cost] + weight);
        //maxl=max(maxl,f[v]);
    }
}

// Problem1055:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
int m, n, f[15000], vv[15000], ww[15000];
inline int read()
{
    int s = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = (s << 1) + (s << 3) + ch - '0';
        ch = getchar();
    }
    return s * f;
}
int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= n; i++)
    {
        int v, p, w, t = 1, n1 = 0;
        v = read();
        w = read();
        p = read();
        if (p == 0)
            for (int j = m; j >= v; j--)
                f[j] = max(f[j], f[j - v] + w);
        else
        {
            while (p >= t)
            {
                vv[++n1] = v * t;
                ww[n1] = w * t;
                p -= t;
                t *= 2;
            }
            vv[++n1] = v * p;
            ww[n1] = w * p;
            for (int i = 1; i <= n1; i++)
                for (int j = m; j >= vv[i]; j--)
                    f[j] = max(f[j], f[j - vv[i]] + ww[i]);
        }
    }
    printf("%d", f[m]);
}

// Problem1056:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i, s, N) for (int i = (s); i <= (N); i++)
using namespace std;
int TotalW, n, w[105];
int f[100005], g[105][100005];
bool d[105];
int main()
{
    cin >> TotalW >> n;
    FOR(i, 1, n)
        cin >> w[i];
    f[0] = 1;
    FOR(i, 1, n)
    {
        for (int v = TotalW; v >= w[i]; v--)
        {
            if (f[v - w[i]] != 0)
                g[i][v] = 1;
            f[v] += f[v - w[i]];
        }
    }
    if (f[TotalW] == 0)
        cout << "0" << endl;
    if (f[TotalW] > 1)
        cout << "-1" << endl;
    if (f[TotalW] == 1)
    {
        int v = TotalW;
        for (int i = n; i > 0; i--)
        {
            if (g[i][v])
            {
                d[i] = 1;
                v -= w[i];
            }
        }
        FOR(i, 1, n)
            if (!d[i]) cout << i << " ";
    }
}

// Problem1057:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
int father[20500];
int n;
inline void Init();
inline void read();
inline void solve();
inline void q_read(int &a);
inline void q_print(char *s);
inline void merge(int a, int b);
int find(int a);
inline bool check(int a, int b);
int main()
{
    //Init();
    read();
    solve();
}
inline void Init()
{
    for (int i = 1; i <= n; i++)
        father[i] = i;
}
inline void read()
{
    int m;
    int a, b;
    q_read(n);
    q_read(m);
    //cin>>n>>m;
    Init();
    while (m--)
    {
        //scanf("%d%d",&a,&b);
        q_read(a);
        q_read(b);
        merge(a, b);
    }
}
inline void solve()
{
    int Q;
    q_read(Q);
    //cin>>Q;
    int c, d;
    while (Q--)
    {
        //scanf("%d%d",&c,&d);
        q_read(c);
        q_read(d);
        if (check(c, d)) /*cout<<"Yes"<<endl;*/
            q_print("Yes");
        else /*cout<<"No"<<endl;*/
            q_print("No");
    }
}
inline void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x == y)
        return;
    else
        father[y] = x;
}
int find(int a)
{
    if (father[a] != a)
        father[a] = find(father[a]);
    return father[a];
}
inline bool check(int a, int b)
{
    if (find(a) == find(b))
        return 1;
    else
        return 0;
}
inline void q_read(int &a)
{
    char c = getchar();
    a = 0;
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        a = a * 10 + c - '0';
        c = getchar();
    }
}
inline void q_print(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        putchar(s[i]);
    }
    putchar('\n');
}
// Problem1057:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
int father[20500];
int n;
inline void Init();
inline void read();
inline void solve();
inline void q_read(int &a);
inline void q_print(char *s);
inline void merge(int a, int b);
int find(int a);
inline bool check(int a, int b);
int main()
{
    //Init();
    read();
    solve();
}
inline void Init()
{
    for (int i = 1; i <= n; i++)
        father[i] = i;
}
inline void read()
{
    int m;
    int a, b;
    q_read(n);
    q_read(m);
    //cin>>n>>m;
    Init();
    while (m--)
    {
        //scanf("%d%d",&a,&b);
        q_read(a);
        q_read(b);
        merge(a, b);
    }
}
inline void solve()
{
    int Q;
    q_read(Q);
    //cin>>Q;
    int c, d;
    while (Q--)
    {
        //scanf("%d%d",&c,&d);
        q_read(c);
        q_read(d);
        if (check(c, d)) /*cout<<"Yes"<<endl;q_print("Yes");*/
            printf("Yes\n");
        else /*cout<<"No"<<endl;q_print("No");*/
            printf("No\n");
    }
}
inline void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x == y)
        return;
    else
        father[y] = x;
}
int find(int a)
{
    if (father[a] != a)
        father[a] = find(father[a]);
    return father[a];
}
inline bool check(int a, int b)
{
    if (find(a) == find(b))
        return 1;
    else
        return 0;
}
inline void q_read(int &a)
{
    char c = getchar();
    a = 0;
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        a = a * 10 + c - '0';
        c = getchar();
    }
}
inline void q_print(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        putchar(s[i]);
    }
    putchar('\n');
}
// Problem1059:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <ctime>
#include <algorithm>
#define LL long long
using namespace std;
void merge(int a, int b);
int find(int a);
int father[1005];
int b[1005][1005];
int main()
{
    int n, m;
    cin >> n >> m;
    int a, d, c;
    for (int i = 1; i <= n; i++)
        father[i] = i;
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> d >> c;
        if (!a)
        {
            merge(d, c);
        }
        else
        {
            b[d][c] = 1;
            b[c][d] = 1;
        }
    }
    //for(int i=1;i<=n;i++) b[i][i]=0;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (b[i][k] == 1 && b[k][j] == 1)
                    merge(i, j);
    //cout<<father[6]<<endl;
    //while(1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i == father[i])
            sum++;
    }
    cout << sum << endl;
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
    {
        father[y] = x;
    }
}
int find(int a)
{
    if (a != father[a])
        father[a] = find(father[a]);
    return father[a];
}

// Problem1069:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define LL long long
using namespace std;
struct data
{
    LL v, i;
};
vector<LL> a;
LL l[400002], r[400002];
int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.out","w",stdout);
    deque<data> s;
    int n, b;
    data k = (data){0, 0};
    scanf("%d", &n);
    LL maxn = 0;
    //deque<data>::iterator it;
    for (int i = 1; i <= n; i++)
        l[i] = r[i] = i;
    for (LL i = 1; i <= n; i++)
    {
        scanf("%d", &b);
        a.push_back(b);
    }
    for (LL i = 0; i < n; i++)
    {
        k = (data){a[i], i + 1};
        while (!s.empty() /*&&it!=s.begin()-1&&a[i]<it->v*/ && a[i] <= (s.end() - 1)->v)
        {
            k = s.back();
            //k=*it;
            //it--;
            //maxn=max(maxn,(s.end()-1)->v*(s.end()-1)->i);
            s.pop_back();
        }
        if (s.empty())
            l[i + 1] = 1;
        else
            l[i + 1] = l[k.i];
        s.push_back((data){a[i], i + 1});
        //maxn=max(maxn,s.begin()->v*(i+1));
        //for(LL j=1;j<s.size();j++){
        //  maxn=max(maxn,(s.begin()+j)->v*((s.begin()+j)->i-(s.begin()+j-1)->i-1));
        //}
    }
    s.clear();
    for (LL i = n - 1; i >= 0; i--)
    {
        k = (data){a[i], i + 1};
        while (!s.empty() /*&&it!=s.begin()-1&&a[i]<it->v*/ && a[i] <= (s.end() - 1)->v)
        {
            k = s.back();
            //k=*it;
            //it--;
            //maxn=max(maxn,(s.end()-1)->v*(s.end()-1)->i);
            s.pop_back();
        }
        if (s.empty())
            r[i + 1] = n;
        else
            r[i + 1] = r[k.i];
        s.push_back((data){a[i], i + 1});
        //maxn=max(maxn,s.begin()->v*(i+1));
        //for(LL j=1;j<s.size();j++){
        //  maxn=max(maxn,(s.begin()+j)->v*((s.begin()+j)->i-(s.begin()+j-1)->i-1));
        //}
    }
    for (LL i = 1; i <= n; i++)
        maxn = max(maxn, a[i - 1] * (r[i] - l[i] + 1));

    //while(!s.empty()){
    //      maxn=max(maxn,(s.end()-1)->v*(s.end()-1)->i);
    //      s.pop_back();
    //}
    //cout<<s.begin()->v*n<<endl;
    cout << maxn << endl;
}

// Problem1073:
#include <iostream>
#include <queue>
#include <map>
#include <cstring>
using namespace std;
struct data
{
    int x;
    bool operator<(data a) const
    {
        return a.x < x;
    }
};
queue<int> a;
map<int, bool> b;
priority_queue<data> c;
int n, s = 0;
int main()
{
    cin >> n;
    a.push(1);
    b[1] = 1;
    while (1)
    {
        int k = a.front();
        a.pop();
        c.push((data){k});
        if (b[2 * k + 1] != 1)
        {
            b[2 * k + 1] = 1;
            a.push(2 * k + 1);
        }
        if (b[3 * k + 1] != 1)
        {
            b[3 * k + 1] = 1;
            a.push(3 * k + 1);
        }
        if (c.size() >= 50000)
            break;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << c.top().x << " ";
        c.pop();
    }
    //while(1);
}

// Problem1075:
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int qx[12] = {1, 2, -1, -2, 2, -2, -1, -2, 1, 2, -2, 2},
          qy[12] = {2, 1, -2, -1, 2, -2, 2, 1, -2, -1, 2, -2};
int dis[120][120];

int main()
{
    //began:system("cls");
    queue<int> a, b, c;
    memset(dis, 0xff, sizeof(dis));
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    dis[1][1] = 0;
    a.push(1);
    b.push(1);
    c.push(0);
    while (!a.empty())
    {
        int x = a.front();
        int y = b.front();
        for (int i = 0; i < 12; i++)
        {
            int nx = x + qx[i], ny = y + qy[i];
            if (nx <= 0 || ny <= 0)
                continue;
            if (dis[nx][ny] == -1)
            {
                dis[nx][ny] = dis[x][y] + 1;
                a.push(nx);
                b.push(ny);
                c.push(dis[nx][ny]);
            }
            if (dis[x1][y1] >= 0 && dis[x2][y2] >= 0)
            {
                cout << dis[x1][y1] << endl
                     << dis[x2][y2];
                getchar();
                getchar();
                //goto began;
                return 0;
            }
        }
        a.pop();
        b.pop();
        c.pop();
    }
}

// Problem1076:
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int qx[8] = {1, -1, 0, 0, 1, -1, -1, 1},
          qy[8] = {0, 0, -1, 1, 1, -1, 1, -1};
bool d[12][12] = {0}, e[11][11] = {0};
bool first = 1;
int main()
{
//#define lon
//began:system("cls");
#ifdef lon
    freopen("1.txt", "r", stdin);
#endif
    queue<int> a, b, c;
    int x = 0, y = 0, sum = 0;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            cin >> d[i][j];
            //if(!d[i][j]&&!d[i-1][j]&&!d[i][j-1])
            //           {
            //                x=i;
            //                y=j;
            //                //first=0;
            //           }
        }
    a.push(x);
    b.push(y);
    while (!a.empty())
    {
        x = a.front();
        y = b.front();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + qx[i];
            int ny = y + qy[i];
            if (nx < 0 || ny < 0 || nx > 11 || ny > 11)
                continue;
            if (!d[nx][ny])
            {
                a.push(nx);
                b.push(ny);
                d[nx][ny] = 1;
            }
        }
        a.pop();
        b.pop();
    }
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            //cout<<d[i][j]<<" ";
            if (!d[i][j])
                sum++;
        }
    //cout<<endl;
    cout << sum << endl;
#ifdef lon
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
            cout << d[i][j] << " ";
        cout << endl;
    }
    while (1)
        ;
#endif
}

// Problem1077:
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int main()
{
    int s[210], k[210];
    bool e[210] = {0};
    int n, a, b;
    queue<int> c;
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    c.push(a);
    k[a] = 0;
    while (!c.empty())
    {
        int x = c.front();
        e[x] = 1;
        if (x - s[x] >= 1 && !e[x - s[x]])
        {
            e[x - s[x]] = 1;
            c.push(x - s[x]);
            k[x - s[x]] = k[x] + 1;
        }
        if (x + s[x] <= n && !e[x + s[x]])
        {
            e[x + s[x]] = 1;
            c.push(x + s[x]);
            k[x + s[x]] = k[x] + 1;
        }
        if (x == b)
        {
            cout << k[x] << endl;
            return 0;
        }
        c.pop();
    }
    cout << "-1" << endl;
}

// Problem1078:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>
using std::max;
namespace WildRage
{
bool comp(int a, int b)
{
    return a <= b;
}
bool comp1(int a, int b)
{
    return b <= a;
}
template <typename _Tp>
class data
{
  public:
    _Tp x;
    int i;
    data(_Tp xi, int ii)
    {
        x = xi;
        i = ii;
    }
};
template <typename _Tp>
class monotony_queue
{
    std::deque<data<_Tp>> Q;

  public:
    void push(_Tp x, int i)
    {
        while (!Q.empty() && Q.back().x < x)
            Q.pop_back();
        Q.push_back((data<_Tp>){x, i});
    }
    void cut(int i, bool (*p)(int, int))
    {
        while (!Q.empty() && p(Q.front().i, i))
            Q.pop_front();
    }
    _Tp front()
    {
        try
        {
            if (Q.empty())
                throw 0;
        }
        catch (int)
        {
            printf("monotony_queue is empty\n");
            while (getchar())
                ;
            getchar();
            exit(1);
        }
        return Q.front().x;
    }
    bool empty()
    {
        return Q.empty();
    }
    int size()
    {
        return Q.size();
    }
    void clear()
    {
        Q.clear();
    }
};
class times
{
  public:
    int S, E, D;
} Time[205];
int n, m, x, y, K;
int a[205][205];
void read()
{
    scanf("%d%d%d%d%d", &n, &m, &x, &y, &K);
    char s;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            std::cin >> s;
            if (s == '.')
                a[i][j] = 0;
            else
                a[i][j] = 1;
        }
    }
    for (int i = 1; i <= K; i++)
    {
        scanf("%d%d%d", &Time[i].S, &Time[i].E, &Time[i].D);
    }
    return;
}
int X[4] = {1, -1, 0, 0};
int Y[4] = {0, 0, 1, -1};
int dp[2][205][205];
int ans = 0;
void Up(int cut, int x)
{
    monotony_queue<int> Q;
    for (int j = 1; j <= m; j++)
    {
        Q.clear();
        for (int i = n; i >= 1; i--)
        {
            if (a[i][j])
            {
                Q.cut(i, comp1);
                continue;
            }
            Q.push(dp[cut ^ 1][i][j] + i, i);
            Q.cut(i + (Time[x].E - Time[x].S + 1) + 1, comp1);
            dp[cut][i][j] = Q.front() - i;
            //std::cout<<"T: "<<x<<" i:"<<i<<" j:"<<j<<"   "<<dp[cut][i][j]<<"\n";
            ans = max(ans, dp[cut][i][j]);
        }
    }
}
void Down(int cut, int x)
{
    monotony_queue<int> Q;
    for (int j = 1; j <= m; j++)
    {
        Q.clear();
        for (int i = 1; i <= n; i++)
        {
            if (a[i][j])
            {
                Q.cut(i, comp);
                continue;
            }
            Q.push(dp[cut ^ 1][i][j] - i, i);
            Q.cut(i - (Time[x].E - Time[x].S + 1) - 1, comp);
            dp[cut][i][j] = Q.front() + i;
            //std::cout<<"T: "<<x<<" i:"<<i<<" j:"<<j<<"   "<<dp[cut][i][j]<<"\n";
            ans = max(ans, dp[cut][i][j]);
        }
    }
}
void Left(int cut, int x)
{
    monotony_queue<int> Q;
    for (int i = 1; i <= n; i++)
    {
        Q.clear();
        for (int j = m; j >= 1; j--)
        {
            if (a[i][j])
            {
                Q.cut(j, comp1);
                continue;
            }
            Q.push(dp[cut ^ 1][i][j] + j, j);
            Q.cut(j + (Time[x].E - Time[x].S + 1) + 1, comp1);
            dp[cut][i][j] = Q.front() - j;
            //std::cout<<"T: "<<x<<" i:"<<i<<" j:"<<j<<"   "<<dp[cut][i][j]<<"\n";
            ans = max(ans, dp[cut][i][j]);
        }
    }
}
void Right(int cut, int x)
{
    monotony_queue<int> Q;
    for (int i = 1; i <= n; i++)
    {
        Q.clear();
        for (int j = 1; j <= m; j++)
        {
            if (a[i][j])
            {
                Q.cut(j, comp);
                continue;
            }
            Q.push(dp[cut ^ 1][i][j] - j, j);
            Q.cut(j - (Time[x].E - Time[x].S + 1) - 1, comp);
            dp[cut][i][j] = Q.front() + j;
            //std::cout<<"T: "<<x<<" i:"<<i<<" j:"<<j<<"   "<<dp[cut][i][j]<<"\n";
            ans = max(ans, dp[cut][i][j]);
        }
    }
}
void Dp()
{
    int cut = 0;
    memset(dp, 0x80, sizeof(dp));
    dp[0][x][y] = 0;
    for (int i = 1; i <= K; i++)
    {
        cut = cut ^ 1;
        if (Time[i].D == 1)
            Up(cut, i);
        else if (Time[i].D == 2)
            Down(cut, i);
        else if (Time[i].D == 3)
            Left(cut, i);
        else if (Time[i].D == 4)
            Right(cut, i);
    }
}
int Main()
{
    //freopen("adv1900.in","r",stdin);
    //freopen("adv1900.out","w",stdout);
    read();
    Dp();
    printf("%d", ans);
    //while(1);
    return 0;
}
}
int main() { WildRage::Main(); }
// Problem1079:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
int main()
{
    int n;
    cin >> n;
    string name[n + 1];
    int qi[n + 1], ban[n + 1], lun[n + 1], sum[n + 1];
    memset(sum, 0, sizeof(sum));
    char xi[n + 1], xue[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> name[i] >> qi[i] >> ban[i] >> xue[i] >> xi[i] >> lun[i];
        if (qi[i] > 80 && lun[i] >= 1)
            sum[i] += 8000;
        if (qi[i] > 85 && ban[i] > 80)
            sum[i] += 4000;
        if (qi[i] > 90)
            sum[i] += 2000;
        if (qi[i] > 85 && xi[i] == 'Y')
            sum[i] += 1000;
        if (ban[i] > 80 && xue[i] == 'Y')
            sum[i] += 850;
    }
    int maxn = 0, maxm = -INF, sumn = 0;
    for (int i = 1; i <= n; i++)
    {
        sumn += sum[i];
        if (sum[i] > maxm)
        {
            maxm = sum[i];
            maxn = i;
        }
    }
    cout << name[maxn] << endl
         << maxm << endl
         << sumn;
    getchar();
    getchar();
}

// Problem1086:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
int n, b[105][105], dis[105][105];
long long a[105];
void read();
int main()
{
    read();
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n; i++)
        dis[i][i] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (b[i][j])
                dis[i][j] = b[i][j];
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    long long minn = 0x7fffffff;
    //for(int i=1;i<=n;i++)
    //cout<<dis[3][i]<<" ";
    //while(1);
    for (int i = 1; i <= n; i++)
    {
        long long s = 0;
        for (int j = 1; j <= n; j++)
            s += a[j] * dis[i][j];
        minn = min(minn, s);
    }
    cout << minn;
    getchar();
    getchar();
}
void read()
{
    cin >> n;
    int s, x, y;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> x >> y;
        if (x != 0)
        {
            b[i][x] = b[x][i] = 1;
        }
        if (y != 0)
        {
            b[i][y] = b[y][i] = 1;
        }
    }
}

// Problem1086:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
struct node
{
    int v;
    int s, e, next;
} v[250];
int dis[150];
int first[105], n, p;
inline void add(int a, int b, int z);
inline void spfa(int lin);
long long a[105];
void read();
int main()
{
    read();
    //cout<<1<<endl;
    long long minn = 0x7fffffff;
    for (int i = 1; i <= n; i++)
    {
        long long s = 0;
        spfa(i);
        for (int j = 1; j <= n; j++)
            s += a[j] * dis[j];
        minn = min(minn, s);
    }
    cout << minn;
    getchar();
    getchar();
}
void read()
{
    cin >> n;
    int s, x, y;
    p = 1;
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> x >> y;
        if (x != 0)
        {
            add(i, x, 1);
            add(x, i, 1);
        }
        if (y != 0)
        {
            add(i, y, 1);
            add(y, i, 1);
        }
    }
}
inline void add(int a, int b, int z)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = z;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int lin)
{
    memset(dis, 0x3f, sizeof(dis));
    queue<int> p;
    bool flag[105] = {0};
    dis[lin] = 0;
    p.push(lin);
    flag[lin] = 1;
    while (!p.empty())
    {
        int k = p.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] > dis[k] + v[i].v)
            {
                dis[v[i].e] = dis[k] + v[i].v;
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    p.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        p.pop();
    }
}
// Problem1089:
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
struct node
{
    char a;
    int ch[2];
    int fa;
} tree[30];
void in()
{
    int n, r, k;
    cin >> n;
    char s;
    for (int i = 1; i <= n; i++)
    {
        cin >> s >> r >> k;
        tree[i].a = s;
        if (r)
            tree[i].ch[0] = r;
        if (k)
            tree[i].ch[1] = k;
    }
}
void q_graph(int i)
{
    if (tree[i].a == 0)
        return;
    cout << tree[i].a;
    q_graph(tree[i].ch[0]);
    q_graph(tree[i].ch[1]);
}
void h_graph(int i)
{
    if (tree[i].a == 0)
        return;
    h_graph(tree[i].ch[0]);
    h_graph(tree[i].ch[1]);
    cout << tree[i].a;
}
void z_graph(int i)
{
    if (tree[i].a == 0)
        return;
    z_graph(tree[i].ch[0]);
    cout << tree[i].a;
    z_graph(tree[i].ch[1]);
}
int main()
{
    in();
    q_graph(1);
    cout << endl;
    z_graph(1);
    cout << endl;
    h_graph(1);
    //while(1);
}

// Problem1091:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
bool f(int x);
int main()
{
    string a;
    cin >> a;
    int sum = 0, maxn = -INF, minn = INF;
    for (int i = 'a'; i <= 'z'; i++)
    {
        for (int j = 0; j < a.size(); j++)
        {
            if (a[j] == i)
                sum++;
        }
        if (sum == 0)
            continue;
        if (sum > maxn)
            maxn = sum;
        if (sum < minn)
            minn = sum;
        sum = 0;
    }
    if (f(maxn - minn))
        cout << "Lucky Word" << endl
             << maxn - minn;
    else
        cout << "No Answer" << endl
             << "0";
    getchar();
    getchar();
}
bool f(int x)
{
    if (x >= 2)
    {
        int i = 2;
        while ((x % i != 0) && i <= floor(sqrt(x)))
            i++;
        if (i > floor(sqrt(x)))
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

// Problem1093:
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define LL long long
using namespace std;
struct node
{
    LL a, s, ans;
    node *ch[2];
    node()
    {
        s = 0;
        ch[0] = NULL;
        ch[1] = NULL;
    }
};
int comp(const node *a, const node *b)
{
    if (a->a != b->a)
        return a->ans < b->ans;
    return a->s < b->s;
}
LL n, a;
LL max_huffman(vector<node *> p)
{
    vector<node *>::iterator it;
    for (LL i = 1; i < n; i++)
    {
        node *s1, *s2, *s3;
        it = min_element(p.begin(), p.end(), comp);
        s1 = *it;
        p.erase(it);
        //cout<<p.size()<<endl;
        it = min_element(p.begin(), p.end(), comp);
        s2 = *it;
        p.erase(it);
        s3 = new node;
        s3->ch[0] = s1;
        s3->ch[1] = s2;
        //cout<<"s1->a:"<<s1->a<<" s2->a:"<<s2->a;
        s3->a = s1->a + s2->a;
        //cout<<" s3->a:"<<s3->a;
        s3->ans = (s1->ans) * (s2->ans) + 1;
        s3->s = s1->s;
        p.push_back(s3);
        //cout<<endl;
    }
    //cout<<p.size();
    //while(1);
    return p[0]->ans;
}
LL min_huffman(vector<node *> p)
{
    vector<node *>::iterator it;
    for (LL i = 1; i < n; i++)
    {
        node *s1, *s2, *s3;
        it = max_element(p.begin(), p.end(), comp);
        s1 = *it;
        p.erase(it);
        //cout<<p.size()<<endl;
        it = max_element(p.begin(), p.end(), comp);
        s2 = *it;
        p.erase(it);
        s3 = new node;
        s3->ch[0] = s1;
        s3->ch[1] = s2;
        //cout<<"s1->a:"<<s1->a<<" s2->a:"<<s2->a;
        s3->a = s1->a + s2->a;
        //cout<<" s3->a:"<<s3->a;
        s3->ans = (s1->ans) * (s2->ans) + 1;
        s3->s = s1->s;
        p.push_back(s3);
        //cout<<endl;
    }
    //cout<<p.size();
    //while(1);
    return p[0]->ans;
}
int main()
{
    vector<node *> root1, root2;
    //node* s=new node;
    cin >> n;
    for (LL i = 1; i <= n; i++)
    {
        node *s = new node;
        cin >> a;
        s->a = a;
        s->ans = a;
        s->s = 1;
        root1.push_back(s);
        root2.push_back(s);
    }
    //cout<<root1[0]->a<<" "<<root1[1]->a;
    //while(1);
    LL maxn = max_huffman(root1), minn = min_huffman(root2);
    cout << maxn << endl;
    cout << minn << endl;
    cout << maxn - minn;
    //while(1);
}

// Problem1095:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;
char a[105] = "", b[105] = "", c[105] = "";
int main()
{
    gets(a);
    gets(b);
    gets(c);
    int l = strlen(a);
    bool d['Z' + 1] = {0};
    char s['Z' + 1];
    memset(s, 0, sizeof(s));
    for (int i = 0; i < l; i++)
    {
        d[b[i]] = 1;
    }
    for (int i = 'A'; i <= 'Z'; i++)
    {
        if (d[i] == 0)
        {
            cout << "Failed" << endl;
            return 0;
        }
    }
    for (int i = 0; i < l; i++)
    {
        if (s[a[i]] == 0 || s[a[i]] == b[i])
            s[a[i]] = b[i];
        else
        {
            cout << "Failed" << endl;
            return 0;
        }
    }
    for (int i = 0; i < strlen(c); i++)
    {
        c[i] = s[c[i]];
    }
    cout << c;
    //    while(1);
}

// Problem1096:
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
struct heap
{
    int a[20000], x;
    heap() { x = 0; }
    inline void push(int b)
    {
        a[++x] = b;
        int j = x;
        int i;
        while (j > 1)
        {
            i = j >> 1;
            if (a[i] > a[j])
            {
                swap(a[i], a[j]);
                j = i;
            }
            else
                break;
        }
    }
    inline int pop()
    {
        int y = a[1];
        a[1] = a[x--];
        int i = 1;
        while ((i << 1) <= x)
        {
            int j = i << 1;
            if (j + 1 <= x && a[j + 1] < a[j])
                j++;
            if (a[j] < a[i])
            {
                swap(a[j], a[i]);
                i = j;
            }
            else
                break;
        }
        return y;
    }
    inline bool empty() { return x == 0; }
    inline int size() { return x; }
};
int main()
{
    heap a;
    int n;
    ;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int m;
        cin >> m;
        a.push(m);
    }
    //while(!a.empty())
    //    {
    //         cout<<a.pop()<<endl;
    //         for(int i=1;i<=a.x;i++)
    //         {
    //                 cout<<a.a[i]<<" ";
    //         }
    //         cout<<endl;
    //    }
    //    while(1);
    int sum = 0, u = 0;
    while (a.size() != 1)
    {
        int p = a.pop();
        int q = a.pop();
        u = p + q;
        sum += u;
        a.push(u);
    }
    cout << sum << endl;
}

// Problem1101:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct node
{
    double v;
    int s, e, next;
} v[4005000];
double dis[2005];
int first[2005], n, p;
int x, y;
inline void add(int a, int b, int z);
inline void spfa(int lin);
inline void read();
int main()
{
    read();
    //cout<<v[1].v;
    //while(1);
    spfa(x);
    //cout<<dis[y]<<endl;
    printf("%.8lf\n", 100 / dis[y]);
    getchar();
    getchar();
    //while(1);
}
inline void read()
{
    p = 1;
    memset(first, -1, sizeof(first));
    int m, a, b, z;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b >> z;
        add(a, b, z);
        add(b, a, z);
    }
    cin >> x >> y;
}
inline void add(int a, int b, int z)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = (double)(100 - z) / 100;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int lin)
{
    queue<int> p;
    bool flag[2005] = {0};
    memset(dis, 0, sizeof(dis));
    dis[lin] = 1;
    p.push(lin);
    flag[lin] = 1;
    while (!p.empty())
    {
        int k = p.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] < dis[k] * v[i].v)
            {
                dis[v[i].e] = dis[k] * v[i].v;
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    p.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        p.pop();
    }
}
// Problem1103:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct node
{
    int v;
    int s, e, next;
} v[4005000];
int dis[2005];
int first[2005], n, p;
int x, y;
inline void add(int a, int b, int z);
inline void spfa(int lin);
inline void read();
int main()
{
    read();
    //cout<<v[1].v;
    //while(1);
    spfa(1);
    //cout<<dis[y]<<endl;
    //cout<<dis[3]<<endl;
    //while(1);
    cout << *max_element(dis + 1, dis + n + 1) << endl;
    getchar();
    getchar();
    //while(1);
}
inline void read()
{
    p = 1;
    memset(first, -1, sizeof(first));
    int m, a, b, z;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b >> z;
        add(a, b, z);
        add(b, a, z);
    }
    //cin>>x>>y;
}
inline void add(int a, int b, int z)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = z;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int lin)
{
    queue<int> p;
    bool flag[2005] = {0};
    memset(dis, 0x3f, sizeof(dis));
    dis[lin] = 0;
    p.push(lin);
    flag[lin] = 1;
    while (!p.empty())
    {
        int k = p.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] > dis[k] + v[i].v)
            {
                dis[v[i].e] = dis[k] + v[i].v;
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    p.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        p.pop();
    }
}
// Problem1103:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
inline void floyd();
inline void read();
int x, y, n;
int v[2005][2005], dis[2005][2005];
int main()
{
    read();
    //cout<<v[1].v;
    //while(1);
    //spfa(x);
    //cout<<dis[y]<<endl;
    floyd();
    //cout<<dis[x][y]<<endl;
    //while(1);

    cout << *max_element(dis[1] + 1, dis[1] + n + 1) << endl;
    getchar();
    getchar();
    //while(1);
}
inline void read()
{
    //p=1;
    //memset(first,-1,sizeof(first));
    int m, a, b, z;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b >> z;
        v[a][b] = z;
        v[b][a] = z;
    }
    //cout<<v[1][3]<<endl;
    //cin>>x>>y;
}
inline void floyd()
{
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (v[i][j])
                dis[i][j] = v[i][j];
    for (int i = 1; i <= n; i++)
        dis[i][i] = 0;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}

// Problem1106:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
struct data
{
    int x, y;
} a[105];
double v[105][105], dis[105][105];
int n;
inline double Floyd(int x, int y);
inline double mylong(data a, data b)
{
    return sqrt((pow((double)a.x - b.x, 2) + pow((double)a.y - b.y, 2)));
}
inline void read()
{
    int m;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    cin >> m;
    int i1, j1;
    while (m--)
    {
        cin >> i1 >> j1;
        v[i1][j1] = mylong(a[i1], a[j1]);
        v[j1][i1] = mylong(a[i1], a[j1]);
    }
}
int main()
{
    read();
    int s, t;
    cin >> s >> t;
    printf("%.2lf", Floyd(s, t));
    //	while(1);
}
inline double Floyd(int x, int y)
{
    memset(dis, 127, sizeof(dis));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (v[i][j])
                dis[i][j] = v[i][j];
    //	for(int i=1;i<=n;i++)
    //	{
    //	    for(int j=1;j<=n;j++)
    //			cout<<dis[i][j]<<" ";
    //		cout<<endl;
    //	}
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    return dis[x][y];
}

// Problem1106:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
struct data
{
    int x, y;
} a[105];
double v[105][105], /*dis[105][105]*/ dis[105];
int n;
//inline double Floyd(int x,int y);
inline double Dijstra(int x, int y);
inline double mylong(data a, data b)
{
    return sqrt((pow((double)a.x - b.x, 2) + pow((double)a.y - b.y, 2)));
}
inline void read()
{
    int m;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    cin >> m;
    int i1, j1;
    while (m--)
    {
        cin >> i1 >> j1;
        v[i1][j1] = mylong(a[i1], a[j1]);
        v[j1][i1] = mylong(a[i1], a[j1]);
    }
}
int main()
{
    read();
    int s, t;
    cin >> s >> t;
    printf("%.2lf", Dijstra(s, t));
    //while(1);
}
//{
//inline double Floyd(int x,int y){
//	memset(dis,127,sizeof(dis));
//	for(int i=1;i<=n;i++)
//	    for(int j=1;j<=n;j++)
//			if(v[i][j]) dis[i][j]=v[i][j];
//	for(int i=1;i<=n;i++)
//	{
//	    for(int j=1;j<=n;j++)
//			cout<<dis[i][j]<<" ";
//		cout<<endl;
//	}
//	for(int k=1;k<=n;k++)
//		for(int i=1;i<=n;i++)
//			for(int j=1;j<=n;j++)
//				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
//	return dis[x][y];
//}
//}
inline double Dijstra(int x, int y)
{
    bool mark[105] = {0};
    memset(dis, 127, sizeof(dis));
    dis[x] = 0;
    //mark[x]=1;
    for (int k = 1; k <= n; k++)
    {
        double min;
        memset(&min, 127, sizeof(min));
        int j = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!mark[i] && dis[i] < min)
            {
                min = dis[i];
                j = i;
            }
        }
        mark[j] = 1;
        for (int i = 1; i <= n; i++)
            if (v[j][i] && dis[j] + v[j][i] < dis[i])
                dis[i] = dis[j] + v[j][i];
    }
    return dis[y];
}

// Problem1106:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
struct data
{
    int x, y;
} a[105];
struct node
{
    double v;
    int next, s, e;
} v[2050];
int first[105];
//int n,p;
double dis[105];
inline void add(int a, int b);
inline double Dijstra(int x, int y);
inline double mylong(data a, data b);
inline void read();
int n, p;

int main()
{
    read();
    int s, t;
    cin >> s >> t;
    printf("%.2lf", Dijstra(s, t));
    getchar();
    getchar();
    //while(1);
}
inline double mylong(data a, data b)
{
    return sqrt((pow((double)a.x - b.x, 2) + pow((double)a.y - b.y, 2)));
}
inline void read()
{
    int m;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    cin >> m;
    p = 1;
    int i1, j1;
    memset(first, -1, sizeof(first));
    while (m--)
    {
        cin >> i1 >> j1;
        add(i1, j1);
        add(j1, i1);
    }
}
inline void add(int c, int b)
{
    v[p].s = c;
    v[p].e = b;
    v[p].v = mylong(a[c], a[b]);
    v[p].next = first[c];
    first[c] = p++;
}
inline double Dijstra(int x, int y)
{
    bool mark[105] = {0};
    memset(dis, 127, sizeof(dis));
    dis[x] = 0;
    //mark[x]=1;
    for (int k = 1; k <= n; k++)
    {
        double min;
        memset(&min, 127, sizeof(min));
        int j = -1;
        for (int i = 1; i <= n; i++)
        {
            if (!mark[i] && dis[i] <= min)
            {
                min = dis[i];
                j = i;
            }
        }
        mark[j] = 1;
        for (int i = first[j]; i != -1; i = v[i].next)
            if (!mark[v[i].e] && dis[j] + v[i].v < dis[v[i].e])
                dis[v[i].e] = dis[j] + v[i].v;
    }
    return dis[y];
}

// Problem1106:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
struct data1
{
    int x, y;
} a[105];
struct node
{
    double v;
    int next, s, e;
} v[2050];
struct data
{
    double v;
    int i;
    bool operator<(const data &a) const
    {
        return a.v < v;
    }
} cc;
priority_queue<data> dis1;
int first[105], mark[105];
//int n,p;
double dis[105];
inline void add(int a, int b);
inline double Dijkstra(int x, int y);
inline double mylong(data1 a, data1 b);
inline void read();
int n, p;

int main()
{
    read();
    int s, t;
    cin >> s >> t;
    printf("%.2lf", Dijkstra(s, t));
    getchar();
    getchar();
    //while(1);
}
inline double mylong(data1 a, data1 b)
{
    return sqrt((pow((double)a.x - b.x, 2) + pow((double)a.y - b.y, 2)));
}
inline void read()
{
    int m;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    cin >> m;
    p = 1;
    int i1, j1;
    memset(first, -1, sizeof(first));
    while (m--)
    {
        cin >> i1 >> j1;
        add(i1, j1);
        add(j1, i1);
    }
}
inline void add(int c, int b)
{
    v[p].s = c;
    v[p].e = b;
    v[p].v = mylong(a[c], a[b]);
    v[p].next = first[c];
    first[c] = p++;
}
// inline double Dijstra(int x,int y){
// bool mark[105]={0};
// memset(dis,127,sizeof(dis));
// dis[x]=0;
// //mark[x]=1;
// for(int k=1;k<=n;k++)
// {
// double min;
// memset(&min,127,sizeof(min));
// int j=-1;
// for(int i=1;i<=n;i++)
// {
// if(!mark[i]&&dis[i]<=min)
// {
// min=dis[i];
// j=i;
// }
// }
// mark[j]=1;
// for(int i=first[j];i!=-1;i=v[i].next)
// if(!mark[v[i].e]&&dis[j]+v[i].v<dis[v[i].e])
// dis[v[i].e]=dis[j]+v[i].v;
// }
// return dis[y];
// }
inline double Dijkstra(int x, int y)
{
    double n;
    int m;
    cc.v = 0;
    cc.i = x;
    dis1.push(cc);
    memset(dis, 127, sizeof(dis));
    memset(mark, 0, sizeof(mark));
    dis[x] = 0;
    while (!dis1.empty())
    {
        m = dis1.top().i;
        n = dis1.top().v;
        dis1.pop();
        if (!mark[m])
        {
            mark[m] = 1;
            for (int i = first[m]; i != -1; i = v[i].next)
            {
                cc.i = v[i].e;
                if (dis[cc.i] > n + v[i].v)
                {
                    dis[cc.i] = n + v[i].v;
                    cc.v = dis[cc.i];
                    dis1.push(cc);
                }
            }
        }
    }
    return dis[y];
}
// Problem1106:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct point
{
    int x, y;
} in[105];
struct node
{
    double v;
    int s, e, next;
} v[2005];
int first[105], x, y, p;
double dis[105];
inline double my_long(point a, point b);
inline void add(int a, int b);
int n;
inline void spfa(int u);
inline void read();
int main()
{
    read();
    spfa(x);
    printf("%.2lf\n", dis[y]);
    getchar();
    getchar();
}
inline void read()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> in[i].x >> in[i].y;
    int m, i1, i2;
    memset(first, -1, sizeof(first));
    cin >> m;
    p = 1;
    while (m--)
    {
        cin >> i1 >> i2;
        add(i1, i2);
        add(i2, i1);
    }
    cin >> x >> y;
}
inline double my_long(point a, point b)
{
    return sqrt(pow((double)a.x - b.x, 2) + pow((double)a.y - b.y, 2));
}
inline void add(int a, int b)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = my_long(in[a], in[b]);
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int u)
{
    queue<int> q;
    bool flag[105] = {0};
    memset(dis, 127, sizeof(dis));
    dis[u] = 0;
    q.push(u);
    flag[u] = 1;
    while (!q.empty())
    {
        int k = q.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] > dis[k] + v[i].v)
            {
                dis[v[i].e] = dis[k] + v[i].v;
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    q.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        q.pop();
    }
}
// Problem1107:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
struct node
{
    int v;
    int s, e, next;
} v[4005000];
int dis[3005];
int first[3005], n, p, d[3005];
int x, y;
inline void add(int a, int b, int z);
inline void spfa(int lin);
//inline void floyd();
inline void read();
int main()
{
    read();
    //cout<<v[1].v;
    //while(1);
    //floyd();
    spfa(1);
    for (int i = 2; i <= n; i++)
        cout << dis[i] << endl;
    getchar();
    getchar();
    //while(1);
}
inline void read()
{
    p = 1;
    memset(first, -1, sizeof(first));
    int m, a, b, z;
    cin >> n;
    while (1)
    {
        cin >> a >> b >> z;
        if (a == 0 && a == b && a == z)
            break;
        add(a, b, z);
        //add(b,a,z);
    }
    //cin>>x>>y;
}
inline void add(int a, int b, int z)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = z;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int lin)
{
    memset(dis, 0, sizeof(dis));
    queue<int> p;
    bool flag[3005] = {0};
    dis[lin] = 0x7fffffff;
    p.push(lin);
    flag[lin] = 1;
    while (!p.empty())
    {
        int k = p.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] < min(dis[k], v[i].v))
            {
                dis[v[i].e] = min(dis[k], v[i].v);
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    p.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        p.pop();
    }
}

// Problem1108:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct node
{
    double v;
    int s, e, next;
} v[55000];
struct data
{
    int x, y;
    int i;
};
struct city
{
    data a[5];
} c[100];
double dis[1550];
int x, y;
int first[2005], n, p, l;
inline void add(int a, int b, double z);
inline void addx(data *a, int t);
inline void addd(city a, city b, int t);
inline double my_long(data a, data b);
//inline double my_long(int a,int b);
inline data juxing(data a, data b, data c);
inline void spfa(int lin);
//inline void floyd();
inline void read();
int main()
{
    int h;
    cin >> h;
    while (h--)
    {
        read();
        double minn;
        memset(&minn, 127, sizeof(minn));
        for (int i = 1; i <= 4; i++)
        {
            spfa(c[x].a[i].i);
            for (int j = 1; j <= 4; j++)
                minn = min(minn, dis[c[y].a[j].i]);
        }
        printf("%.1lf", minn);
    }
    getchar();
    getchar();
    //while(1);
}
inline void read()
{
    p = 1;
    l = 1;
    memset(first, -1, sizeof(first));
    int m, b, ti, t;
    cin >> n >> t >> x >> y;
    //data a[5];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            cin >> c[i].a[j].x >> c[i].a[j].y;
            c[i].a[j].i = l++;
        }
        cin >> ti;
        c[i].a[4] = juxing(c[i].a[1], c[i].a[2], c[i].a[3]);
        c[i].a[4].i = l++;
        //cout<<c[i].a[4].x<<" "<<c[i].a[4].y<<endl;
        addx(c[i].a, ti);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            addd(c[i], c[j], t);
    //cin>>x>>y;
}
inline void add(int a, int b, double z)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = z;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int lin)
{
    memset(dis, 127, sizeof(dis));
    queue<int> p;
    bool flag[1505] = {0};
    dis[lin] = 0;
    p.push(lin);
    flag[lin] = 1;
    while (!p.empty())
    {
        int k = p.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] > dis[k] + v[i].v)
            {
                dis[v[i].e] = dis[k] + v[i].v;
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    p.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        p.pop();
    }
}
inline double my_long(data a, data b)
{
    return sqrt(pow((double)a.x - b.x, 2) + pow((double)a.y - b.y, 2));
}
inline data juxing(data a, data b, data c)
{
    if (abs(pow(my_long(a, b), 2) + pow(my_long(b, c), 2) - pow(my_long(a, c), 2)) <= 0.01)
    {
        int x = a.x + c.x - b.x;
        int y = a.y + c.y - b.y;
        return (data){x, y};
    }
    if (abs(pow(my_long(a, c), 2) + pow(my_long(c, b), 2) - pow(my_long(a, b), 2)) <= 0.01)
    {
        int x = a.x + b.x - c.x;
        ;
        int y = a.y + b.y - c.y;
        return (data){x, y};
    }
    if (abs(pow(my_long(b, a), 2) + pow(my_long(a, c), 2) - pow(my_long(b, c), 2)) <= 0.01)
    {
        int x = b.x + c.x - a.x;
        int y = b.y + c.y - a.y;
        return (data){x, y};
    }
}
inline void addx(data *a, int t)
{
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            add(a[i].i, a[j].i, t * my_long(a[i], a[j]));
            add(a[j].i, a[i].i, t * my_long(a[i], a[j]));
        }
}
inline void addd(city a, city b, int t)
{
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            add(a.a[i].i, b.a[j].i, t * my_long(a.a[i], b.a[j]));
            add(b.a[j].i, a.a[i].i, t * my_long(a.a[i], b.a[j]));
        }
}

// Problem1111:
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
struct node
{
    int c, u;
} v[105];
int d[105][105];
bool LIANTONG[105][105];
int ru_du[105];
int main()
{
    int n, m, a, b, c;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i].c >> v[i].u;
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b >> c;
        d[a][b] = c;
        ru_du[b]++;
        LIANTONG[a][b] = 1;
    }
    queue<int> q;
    priority_queue<int, vector<int>, greater<int>> p;
    for (int i = 1; i <= n; i++)
        if (ru_du[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int tmp = q.front();
        //v[tmp].c-=v[tmp].u;
        if (v[tmp].c < 0)
            v[tmp].c = 0;
        q.pop();
        bool SHUC = 1;
        for (int i = 1; i <= n; i++)
        {
            if (LIANTONG[tmp][i])
            {
                ru_du[i]--;
                SHUC = 0;
                v[i].c += d[tmp][i] * v[tmp].c;
                if (ru_du[i] == 0)
                {
                    v[i].c -= v[i].u;
                    q.push(i);
                }
            }
        }
        if (SHUC)
        {
            p.push(tmp);
        }
    }
    int s = 0;
    while (!p.empty())
    {
        int tmp = p.top();
        if (v[tmp].c > 0)
        {
            cout << tmp << " " << v[tmp].c << endl;
            s++;
        }
        p.pop();
    }
    if (s == 0)
    {
        cout << "NULL" << endl;
    }
    //while(1);
}

// Problem1113:
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int main()
{
    vector<int> a;
    priority_queue<int, vector<int>, greater<int>> b;
    vector<int>::iterator s1, s2;
    int m, s, c, w;
    cin >> m >> s >> c;
    for (int i = 1; i <= c; i++)
    {
        cin >> w;
        a.push_back(w);
        //cout<<a.size()<<" ";
    }
    sort(a.begin(), a.end());
    for (s1 = a.begin(); s1 != a.end() - 1; s1++)
    {
        s2 = s1 + 1;
        b.push(*s2 - *s1 - 1);
    }
    int ans = c;
    if (m >= c)
    {
        cout << c << endl;
        return 0;
    }
    while (m < c)
    {
        ans += b.top();
        b.pop();
        m++;
    }
    cout << ans;
    //while(1);
}

// Problem1114:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
void dfs(int);
int a[1000][1000], b[1000];
int n, e;
int main()
{

    cin >> n >> e;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= e; i++)
    {
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;
        a[y][x] = 1;
    }
    dfs(1);
    //while(1);
}
void dfs(int x)
{
    b[x] = 1;
    cout << x << ' ';
    for (int i = 1; i <= n; i++)
    {
        if (a[x][i] && b[i] == 0)
        {

            dfs(i);
        }
    }
}
// Problem1115:
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
bool a[2000][2000], c[2000] = {0};
queue<int> b;
int n, e;
void bfs(int);
int main()
{
    memset(a, 0, sizeof(a));
    cin >> n >> e;
    for (int i = 1; i <= e; i++)
    {
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;
        a[y][x] = 1;
    }
    b.push(1);
    c[1] = 1;
    bfs(1);
}
void bfs(int x)
{
    while (!b.empty())
    {
        int k = b.front();
        b.pop();
        cout << k << ' ';
        for (int i = 1; i <= n; i++)
        {
            if (a[k][i] && !c[i])
            {
                b.push(i);
                c[i] = 1;
            }
        }
    }
}

// Problem1116:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
int n, a[105][105], dis[105][105], b[105][105];
void read();
int main()
{
    read();
    memset(dis, 0, sizeof(dis));
    for (int i = 1; i <= n; i++)
        dis[i][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i][j])
                dis[i][j] = 1;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = dis[i][j] || (dis[i][k] && dis[k][j]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int sum = 0;
        for (int j = 1; j <= n; j++)
        {
            if (dis[i][j])
                sum++;
        }
        if (sum > ((n + 1) / 2))
            ans++;
    }
    memset(dis, 0, sizeof(dis));
    for (int i = 1; i <= n; i++)
        dis[i][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (b[i][j])
                dis[i][j] = 1;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = dis[i][j] || (dis[i][k] && dis[k][j]);
    for (int i = 1; i <= n; i++)
    {
        int sum = 0;
        for (int j = 1; j <= n; j++)
        {
            if (dis[i][j])
                sum++;
        }
        if (sum > ((n + 1) / 2))
            ans++;
    }
    cout << ans;
}
void read()
{
    int m;
    cin >> n >> m;
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        a[x][y] = 1;
        b[y][x] = 1;
    }
}

// Problem1118:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
int a[505][505];
int du[505], n, s;
void dfs(int i);
int main()
{
    memset(a, 0, sizeof(a));
    memset(du, 0, sizeof(du));
    //memset(b,1,sizeof(b));
    int x, y, minn = 0x7fffffff;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x >> y;
        minn = min(minn, x);
        minn = min(minn, y);
        a[x][y]++;
        a[y][x]++;
        du[x]++;
        du[y]++;
    }
    int first = minn;
    for (int i = 1; i <= 500; i++)
        if (du[i] & 1)
        {
            first = i;
            break;
        }
    dfs(first);
    //while(1);
}
void dfs(int i)
{
    cout << i << endl;
    //b[i]=0;
    //s++;
    //if(s==n) {while(1);exit(0);}
    for (int j = 1; j <= 500; j++)
    {
        if (a[i][j])
        {
            a[i][j]--;
            a[j][i]--;
            dfs(j);
            break;
        }
    }
}

// Problem1129:
#include <iostream>
#include <stack>
//#include<map>
using namespace std;
int top(char a, bool b);
int main()
{
    stack<char> a;
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(' || s[i] == '+' || s[i] == '/' || s[i] == '-' || s[i] == '*')
        {
            if (a.empty())
            {
                a.push(s[i]);
                continue;
            }
            if (top(a.top(), 1) < top(s[i], 0))
            {
                a.push(s[i]);
                continue;
            }
            while (!a.empty() && top(a.top(), 1) >= top(s[i], 0))
            {
                cout << a.top();
                a.pop();
            }
            a.push(s[i]);
            continue;
        }
        if (s[i] == ')')
        {
            while (a.top() != '(')
            {
                cout << a.top();
                a.pop();
            }
            a.pop();
            continue;
        }
        cout << s[i];
    }
    while (!a.empty())
    {
        cout << a.top();
        a.pop();
    }
    getchar();
    getchar();
}
int top(char a, bool b)
{
    if (a == '+' || a == '-')
        return 1;
    if (a == '*' || a == '/')
        return 2;
    if (a == '(' && b)
        return 0;
    if (a == '(' && !b)
        return 3;
}

// Problem1130:
#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;
int top(char a, bool b);
int n = 1;
bool check();
string s;
stack<char> a;
stack<int> c;
queue<char> b;
string l = "0";
void solve();
int trans(int);
int main()
{

    cin >> s;
    check();
    solve();
    getchar();
    getchar();
}
int top(char a, bool b)
{
    if (a == '+' || a == '-')
        return 1;
    if (a == '*' || a == '/')
        return 2;
    if (a == '(' && b)
        return 0;
    if (a == '(' && !b)
        return 3;
}
bool check()
{
    if (s[0] == '+' || s[0] == '-')
    {
        if (s[1] == '0')
        {
            cout << "NO";
            exit(0);
        }
        s = l + s;
    }
    if (s[0] == '*' || s[0] == '/')
    {
        cout << "NO";
        exit(0);
    }
    for (int i = 0; s[i] != '@'; i++)
    {
        if (s[i] == '(')
        {
            a.push(s[i]);
        }
        if (s[i] == ')')
        {
            if (a.empty())
            {
                cout << "NO";
                exit(0);
            }
            a.pop();
        }
    }
    if (!a.empty())
    {
        cout << "NO";
        exit(0);
    }
    for (int i = 0; s[i] != '@'; i++)
    {
        if (s[i] == '(' || s[i] == '+' || s[i] == '/' || s[i] == '*' || s[i] == '-')
        {
            if (s[i] == '(')
            {
                if (s[i - 1] >= '0' && s[i - 1] <= '9')
                {
                    cout << "NO";
                    exit(0);
                }
                n = 1;
                if (s[i + 1] == '-' || s[i + 1] == '+')
                {
                    if (s[i + 2] == '0')
                    {
                        cout << "NO";
                        exit(0);
                    }
                    b.push(0);
                }
                if (s[i + 1] == '*' || s[i + 1] == '/')
                {
                    cout << "NO";
                    exit(0);
                }
            }
            else
                n++;
            if (n > 2)
            {
                cout << "NO" << endl;
                exit(0);
            }
            if (a.empty() || top(a.top(), 1) < top(s[i], 0))
            {
                a.push(s[i]);
                continue;
            }
            while (!a.empty() && top(a.top(), 1) >= top(s[i], 0))
            {
                b.push(a.top());
                a.pop();
            }
            a.push(s[i]);
            continue;
        }
        if (s[i] == ')')
        {
            while (a.top() != '(')
            {
                b.push(a.top());
                a.pop();
            }
            a.pop();
            continue;
        }
        n = 1;
        i += trans(i);
    }
    if (n >= 2)
    {
        cout << "NO";
        exit(0);
    }
    while (!a.empty())
    {
        b.push(a.top());
        a.pop();
    }
}
void solve()
{
    while (!b.empty())
    {
        if (b.front() == '+' /*||b.front()=='-'||b.front()=='*'||b.front()=='/'*/)
        {
            int p, q;
            p = c.top();
            c.pop();
            q = c.top();
            c.pop();
            c.push(q + p);
            b.pop();
            continue;
        }
        if (b.front() == '-')
        {
            int p, q;
            p = c.top();
            c.pop();
            q = c.top();
            c.pop();
            c.push(q - p);
            b.pop();
            continue;
        }
        if (b.front() == '*')
        {
            int p, q;
            p = c.top();
            c.pop();
            q = c.top();
            c.pop();
            c.push(q * p);
            b.pop();
            continue;
        }
        if (b.front() == '/')
        {
            int p, q;
            p = c.top();
            c.pop();
            q = c.top();
            c.pop();
            if (p == 0)
            {
                cout << "NO";
                exit(0);
            }
            c.push(q / p);
            b.pop();
            continue;
        }
        c.push(b.front());
        b.pop();
        continue;
    }
    cout << c.top();
}
int trans(int i)
{
    int k = -1, o = 0, m = 1;
    while (s[i] >= '0' && s[i] <= '9')
    {
        o = o * 10 + s[i] - '0';
        k++;
        i++;
    }
    b.push(o);
    return k;
}

// Problem1133:
#include <iostream>
#include <cstdio>
using namespace std;
char a[100005];
int main()
{
    int m, t, u, f, d;
    cin >> m >> t >> u >> f >> d;
    for (int i = 1; i <= t; i++)
        cin >> a[i];
    int s = 0, out = 0;
    bool q = 0, p = 0;
    for (int i = 1; i <= t; i++)
    {
        q = 0;
        switch (a[i])
        {
        case 'u':
            s += (u + d);
            q = 1;
            break;
        case 'f':
            s += (2 * f);
            q = 0;
            break;
        case 'd':
            s += (u + d);
            q = 1;
            break;
        }
        if (s > m)
        {
            if (q)
            {
                s -= (u + d);
                out = i - 1;
                break;
            }
            else
            {
                s -= (2 * f);
                out = i - 1;
                break;
            }
        }
        else
        {
            if (s == m)
            {
                out = i;
                break;
            }
            else
            {
                if (i == t)
                    out = i;
            }
        }
    }
    cout << out;
    //while(1);
}

// Problem1137:
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
char a[2005], b[2005];
bool fc(int q, int p);
int main()
{
    //freopen("bcl.in","r",stdin);
    //freopen("bcl.out","w",stdout);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int m = n, l = 1, s = 1;
    for (int i = 1; i <= n; i++)
    {
        if (a[l] < a[m])
        {
            b[s] = a[l];
            s++;
            l++;
        }
        else
        {
            if (a[l] > a[m])
            {
                b[s] = a[m];
                s++;
                m--;
            }
            else
            {
                if (fc(l, m))
                {
                    b[s] = a[l];
                    s++;
                    l++;
                }
                else
                {
                    b[s] = a[m];
                    s++;
                    m--;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
        cout << b[i];
    //while(1);
}
bool fc(int q, int p)
{
    if (a[q + 1] < a[p - 1])
        return 1;
    else
    {
        if (a[q + 1] > a[p - 1])
            return 0;
        else
            return fc(q + 1, p - 1);
    }
}

// Problem1137:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 60005;
int buc[MAXN], wa[MAXN], wb[MAXN];
int r[MAXN], sa[MAXN], Rank[MAXN];
bool cmp(int *c, int a, int b, int d)
{
    return c[a] == c[b] && c[a + d] == c[b + d];
}
void da(int n, int m = 130)
{
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++)
        buc[i] = 0;
    for (i = 0; i < n; i++)
        buc[x[i] = r[i]]++;
    for (i = 1; i < m; i++)
        buc[i] += buc[i - 1];
    for (i = n - 1; ~i; i--)
        sa[--buc[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p)
    {
        for (i = n - j, p = 0; i < n; i++)
            y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                y[p++] = sa[i] - j;
        for (i = 0; i < m; i++)
            buc[i] = 0;
        for (i = 0; i < n; i++)
            buc[x[y[i]]]++;
        for (i = 1; i < m; i++)
            buc[i] += buc[i - 1];
        for (i = n - 1; ~i; i--)
            sa[--buc[x[y[i]]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
    for (i = 0; i < n; i++)
        Rank[sa[i]] = i;
}
int main()
{
    // freopen("bclgold.in", "r", stdin);
    // freopen("bclgold.out", "w", stdout);
    int n;
    char c[2];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", c);
        r[i] = r[2 * n - i - 1] = c[0];
    }
    da(2 * n + 1);
    int l = 0, R = n;
    for (int i = 1; i <= n; i++)
    {
        if (Rank[l] > Rank[R])
            printf("%c", r[R++]);
        else
            printf("%c", r[l++]);
    }
    //while(1);
}
// Problem1147:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;
char a[85] = "", b[85] = "";
int main()
{
    string c, d, e, f;
    int max = 0, l;
    cin >> c >> d;
    e = c;
    f = d;
    if (c.size() == 1 || d.size() == 1)
    {
        if (d[0] == c[0] || d[d.size() - 1] == c[0] || c[c.size() - 1] == d[0])
        {
            cout << "1";
            return 0;
        }
    }
    if (c.size() > d.size())
        l = d.size();
    else
        l = c.size();
    for (int i = 1; i <= l; i++)
    {
        e.erase(i, e.size() - i);
        f.erase(0, f.size() - i);
        // cout<<"e:"<<e<<endl;
        //        cout<<"f:"<<f<<endl<<endl;
        if (e == f)
        {
            if (i >= max)
                max = i;
        }
        else
        {
            e = c;
            f = d;
            //continue;
        }
        e = c;
        f = d;
        f.erase(i, f.size() - i);
        e.erase(0, e.size() - i);
        //cout<<"f:"<<f<<endl;
        //        cout<<"e:"<<e<<endl<<endl;
        if (e == f)
        {
            if (i >= max)
                max = i;
        }
        else
        {
            e = c;
            f = d;
            continue;
        }
        e = c;
        f = d;
    }
    cout << max;
    //while(1);
}

// Problem1148:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
int main()
{
    string a, b;
    string c = "";
    cin >> a >> b;
    int a1[a.size() + 1], b1[b.size() + 1], c1[b.size() + 1];
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] >= 'A' && a[i] <= 'Z')
            a1[i + 1] = a[i] - 'A';
        else
            a1[i + 1] = a[i] - 'a';
    }
    for (int i = 0; i < b.size(); i++)
    {
        if (b[i] >= 'A' && b[i] <= 'Z')
            b1[i + 1] = b[i] - 'A';
        else
            b1[i + 1] = b[i] - 'a';
    }
    int j = 1;
    for (int i = 1; i <= b.size(); i++)
    {
        c1[i] = b1[i] - a1[j];
        j++;
        if (j > a.size())
            j = 1;
    }
    for (int i = 0; i < b.size(); i++)
    {
        if (c1[i + 1] < 0)
            c1[i + 1] = 26 + c1[i + 1];
        if (b[i] >= 'A' && b[i] <= 'Z')
        {
            c += (char)(c1[i + 1] + 'A');
        }
        else
            c += (char)(c1[i + 1] + 'a');
    }
    c += '\n';
    cout << c;
    getchar();
    getchar();
}

// Problem1149:
#include <cstring>
//#include<cmath>
//#include<windows.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 100000000
#define LL long long
using namespace std;
bool d[100] = {0}, b[100] = {0}, c[100] = {0};
int sum = 0, a[10];
int search(int i);
int print();
int n;
int main()
{
    cin >> n;
    search(1);
    if (sum == 0)
        cout << "no solute!";
    //while(1);
}
int search(int i)
{
    int j;
    for (j = 1; j <= n; j++)
        if ((!b[j]) && (!c[i + j]) && (!d[i - j + n - 1]))
        {
            a[i] = j;
            b[j] = 1;
            c[i + j] = 1;
            d[i - j + n - 1] = 1;
            if (i == n)
            {
                print();
            }
            else
                search(i + 1);
            b[j] = 0;
            c[i + j] = 0;
            d[i - j + n - 1] = 0;
        }
}
int print()
{
    int i;
    sum++;
    for (i = 1; i <= n; i++)
        printf("%5d", a[i]);
    printf("\n");
}

// Problem1160:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <ctime>
#include <algorithm>
#define LL long long
using namespace std;
bool ff[1005][1005];
int father[1005];
int father_size[1005];
void merge(int a, int b);
int find(int a);
bool check(int a, int b);
int main()
{
    int n, m, a;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> m;
        for (int j = 1; j <= m; j++)
        {
            cin >> a;
            ff[i][a] = 1;
            ff[a][i] = 1;
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            father[i] = i;
            father_size[i] = 1;
        }
        for (int i = k + 1; i <= n; i++)
        {
            for (int j = k + 1; j <= n; j++)
            {
                if (ff[i][j])
                {
                    merge(i, j);
                }
            }
        }
        //cout<<*max_element(father_size,father_size+n+1)<<endl;
        if (*max_element(father_size, father_size + n + 1) <= n / 2)
        {
            cout << k << endl;
            break;
        }
    }
    //while(1);
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
    {
        father[y] = x;
        father_size[x] += father_size[y];
        father_size[y] = 0;
    }
}
int find(int a)
{
    if (a != father[a])
        father[a] = find(father[a]);
    return father[a];
}
bool check(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x == y)
        return 1;
    else
        return 0;
}

// Problem1160:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <ctime>
#include <algorithm>
#define LL long long
using namespace std;
bool ff[1005][1005];
int father[1005];
int father_size[1005];
void merge(int a, int b);
int find(int a);
bool check(int a, int b);
int main()
{
    int n, m, a;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> m;
        for (int j = 1; j <= m; j++)
        {
            cin >> a;
            ff[i][a] = 1;
            ff[a][i] = 1;
        }
    }
    for (int k = n - 1; k >= 0; k--)
    {
        for (int i = 1; i <= n; i++)
        {
            father[i] = i;
            father_size[i] = 1;
        }
        for (int i = k + 1; i <= n; i++)
        {
            for (int j = k + 1; j <= n; j++)
            {
                if (ff[i][j])
                {
                    merge(i, j);
                }
            }
        }
        //cout<<*max_element(father_size,father_size+n+1)<<endl;
        if (*max_element(father_size, father_size + n + 1) > n / 2)
        {
            cout << k + 1 << endl;
            break;
        }
    }
    //while(1);
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
    {
        father[y] = x;
        father_size[x] += father_size[y];
        father_size[y] = 0;
    }
}
int find(int a)
{
    if (a != father[a])
        father[a] = find(father[a]);
    return father[a];
}
bool check(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x == y)
        return 1;
    else
        return 0;
}
// Problem1161:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
int father[50500];
int n;
inline void Init();
int find(int a);
//bool check(int a,int b);
void merge(int a, int b);
//void read();
int main()
{
    char c;
    map<string, int> a;
    map<int, string> b;
    string s;
    Init();
    int p = 1, k, l;
    while (1)
    {
        c = getchar();
        if (c == '$')
            break;
        while (c == '#')
        {
            cin >> s;
            if (a.find(s) == a.end())
            {
                b[p] = s;
                a[s] = p++;
            }
            k = a[s];
            c = getchar();
            while (c != '+')
                c = getchar();
            while (c == '+')
            {
                cin >> s;
                if (a.find(s) == a.end())
                {
                    b[p] = s;
                    a[s] = p++;
                }
                l = a[s];
                merge(k, l);
                c = getchar();
                c = getchar();
                //cout<<father[l];
            }
        }
        while (c == '?')
        {
            cin >> s;
            cout << s << " " << b[father[a[s]]] << endl;
            c = getchar();
        }
    }
}
inline void Init()
{
    for (int i = 1; i <= 50000; i++)
        father[i] = i;
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x == y)
        return;
    else
        father[y] = x;
}
int find(int a)
{
    if (father[a] != a)
        father[a] = find(father[a]);
    return father[a];
}

// Problem1165:
#include <iostream>
#include <cstdio>
using namespace std;
struct node
{
    int i, a;
    node *ch[100];
    node *fa;
} tree[1005];
int main()
{
    int n, m, x, y;
    cin >> n >> m;
    while (m--)
    {
        cin >> x >> y;
        tree[x].ch[tree[x].i++] = &tree[y];
        tree[y].fa = &tree[x];
        tree[x].a = x;
        tree[y].a = y;
    }
    for (int i = 1; i <= 1000; i++)
    {
        if (tree[i].i == 0)
            continue;
        if (tree[i].fa == NULL)
        {
            cout << i << endl;
            break;
        }
    }
    int maxn = -1, j = 0;
    for (int i = 1; i <= 1000; i++)
    {
        if (tree[i].i == 0)
            continue;
        if (tree[i].i >= maxn)
        {
            maxn = tree[i].i;
            j = i;
        }
    }
    cout << j << endl;
    for (int i = 0; i < tree[j].i; i++)
    {
        cout << tree[j].ch[i]->a << " ";
    }
}

// Problem1166:
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
string a[10000];
int comp(const string &a, const string &b)
{
    return a < b;
}
int main()
{
    //freopen("1.txt","r",stdin);
    string s;
    int n = 0;
    while (cin >> a[n++])
        ;
    sort(a, a + n, comp);
    int ans = a[0].size();
    for (int i = 1; i < n; i++)
    {
        int j = 0;
        while (a[i][j] == a[i - 1][j] && j < a[i].size() && j < a[i - 1].size())
            j++;
        ans += a[i].size() - j;
    }
    cout << ans + 1;
    //while(1);
}

// Problem1167:
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
void work(string s1, string s2);
int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    work(s1, s2);
    //cout<<"1";
    //while(1);
}
void work(string s1, string s2)
{
    //cout<<*s1.begin();
    if (s1.size() == 1)
    {
        cout << s1[0];
        return;
    }
    int it = s2.find(s1[0]);
    if (it > 0)
    {
        string s3 = "", s4 = "";
        for (int i = 1; i <= it; i++)
            s3 += s1[i];
        //cout<<s3<<endl;
        for (int i = 0; i <= it - 1; i++)
            s4 += s2[i];
        //cout<<s4<<endl;
        work(s3, s4);
        //cout<<s1[0];
    }
    if (it < s2.size() - 1)
    {
        string s3 = "", s4 = "";
        for (int i = it + 1; i < s2.size(); i++)
            s3 += s1[i];
        // cout<<s3<<endl;
        for (int i = it + 1; i < s2.size(); i++)
            s4 += s2[i];
        // cout<<s4<<endl;
        work(s3, s4);
        //cout<<s1[0];
    }
    cout << s1[0];
}

// Problem1168:
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
struct node
{
    char a;
    int ch[2];
    int fa;
} tree[30];
void in()
{
    int n, r;
    cin >> n;
    char s;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        tree[i].a = s;
        cin >> r;
        if (r == 0)
            continue;
        tree[i].ch[0] = r;
        tree[r].fa = i;
        int p = r;
        while (r != 0)
        {
            cin >> r;
            if (r != 0)
            {
                tree[p].ch[1] = r;
                tree[r].fa = p;
                p = r;
            }
        }
    }
}
void q_graph(int i)
{
    if (tree[i].a == 0)
        return;
    cout << tree[i].a;
    q_graph(tree[i].ch[0]);
    q_graph(tree[i].ch[1]);
}
void h_graph(int i)
{
    if (tree[i].a == 0)
        return;
    h_graph(tree[i].ch[0]);
    h_graph(tree[i].ch[1]);
    cout << tree[i].a;
}
int main()
{
    in();
    q_graph(1);
    cout << endl;
    h_graph(1);
    //while(1);
}

// Problem1169:
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
void work(string s1, string s2);
int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    work(s2, s1);
    //cout<<"1";
    //while(1);
}
void work(string s1, string s2)
{
    cout << *(s1.end() - 1);
    if (s1.size() == 1)
    {
        //cout<<s1[0];
        return;
    }
    int it = s2.find(*(s1.end() - 1));
    if (it > 0)
    {
        string s3 = "", s4 = "";
        for (int i = 0; i < it; i++)
            s3 += s1[i];
        //cout<<s3<<endl;
        for (int i = 0; i < it; i++)
            s4 += s2[i];
        //cout<<s4<<endl;
        work(s3, s4);
        //cout<<s1[0];
    }
    if (it < s2.size() - 1)
    {
        string s3 = "", s4 = "";
        for (int i = it; i < s2.size() - 1; i++)
            s3 += s1[i];
        // cout<<s3<<endl;
        for (int i = it + 1; i < s2.size(); i++)
            s4 += s2[i];
        // cout<<s4<<endl;
        work(s3, s4);
        //cout<<s1[0];
    }
    //cout<<s1[0];
}

// Problem1170:
#include <iostream>
#include <cstdio>
using namespace std;
struct node
{
    int a;
    node *ch[2];
    node()
    {
        ch[0] = NULL;
        ch[1] = NULL;
    }
};
node *root;
void insert(int a, node *&p)
{
    if (p == NULL)
    {
        p = new node;
        p->a = a;
    }
    else
    {
        if (a >= p->a)
            insert(a, p->ch[1]);
        else
            insert(a, p->ch[0]);
    }
}
void z_graph(node *p)
{
    if (p == NULL)
        return;
    z_graph(p->ch[0]);
    cout << p->a << " ";
    z_graph(p->ch[1]);
}
void h_graph(node *p)
{
    if (p == NULL)
        return;
    h_graph(p->ch[0]);
    h_graph(p->ch[1]);
    cout << p->a << " ";
}
int main()
{
    int n, a;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        insert(a, root);
    }
    z_graph(root);
    cout << endl;
    h_graph(root);
    //while(1);
}

// Problem1171:
#include <iostream>
#include <cstdio>
using namespace std;
int c(int m, int n)
{
    if (m == n)
        return 1;
    if (n == 1)
        return m;
    return c(m - 1, n) + c(m - 1, n - 1);
}
int main()
{
    int m, n;
    cin >> m >> n;
    cout << c(m, n);
    //while(1);
}

// Problem1172:
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct edge
{
    int START, END, v;
    bool operator<(const edge &a) const
    {
        return v < a.v;
    }
} v[40005];
int father[205];
int find(int a)
{
    if (father[a] != a)
        father[a] = find(father[a]);
    return father[a];
}

int main()
{
    int n, a;
    cin >> n;
    int p = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a;
            if (a != 0)
            {
                v[p].START = i;
                v[p].END = j;
                v[p].v = a;
                p++;
            }
        }
    }
    sort(v + 1, v + p);
    int ans = 0;
    int k = 0;
    for (int i = 1; i <= n; i++)
        father[i] = i;
    for (int i = 1; i < p; i++)
    {
        int x = v[i].START;
        int y = v[i].END;
        if (find(x) != find(y))
        {
            father[find(y)] = find(x);
            ans += v[i].v;
            k++;
        }
        if (k == n - 1)
            break;
    }
    cout << ans << endl;
}

// Problem1172:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int a[105][105];
int minn[105];
bool INTREE[105];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    memset(minn, 0x3f, sizeof(minn));
    minn[1] = 0;
    int ans = 0;
    //memset(INTREE,1,sizeof(INTREE));
    for (int i = 1; i <= n; i++)
    {
        int k = 0;
        for (int j = 1; j <= n; j++)
        {
            if (!INTREE[j] && (minn[j] < minn[k]))
            {
                k = j;
            }
        }
        INTREE[k] = 1;
        ans += minn[k];
        for (int j = 1; j <= n; j++)
        {
            if (!INTREE[j] && (a[k][j] < minn[j]))
            {
                minn[j] = a[k][j];
            }
        }
    }
    //for(int i=1;i<=n;i++){
    //	ans+=minn[i];
    //}
    cout << ans << endl;
}
// Problem1174:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct edge
{
    int STRAT, END, v;
    bool operator<(const edge &a) const
    {
        return v < a.v;
    }
} v[2005];
int father[105];
int find(int x);
int main()
{
    int n, m;
    cin >> n >> m;
    int a, b, c;
    int p = 1, sum = 0;
    while (m--)
    {
        cin >> a >> b >> c;
        v[p].STRAT = a;
        v[p].END = b;
        v[p++].v = c;
        v[p].STRAT = b;
        v[p].END = a;
        v[p++].v = c;
        sum += c;
    }
    int ans = 0, k = 0;
    sort(v + 1, v + p);
    for (int i = 1; i <= n; i++)
        father[i] = i;
    for (int i = 1; i < p; i++)
    {
        int x = v[i].STRAT, y = v[i].END;
        if (find(x) != find(y))
        {
            father[find(y)] = find(x);
            ans += v[i].v;
            k++;
        }
        if (k == n - 1)
            break;
    }
    cout << sum - ans << endl;
}
int find(int x)
{
    if (x != father[x])
        father[x] = find(father[x]);
    return father[x];
}

// Problem1177:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct node
{
    int v;
    int s, e, next;
} v[4005000];
int dis[850];
int first[2005], n, p, d[2005];
int x, y;
inline void add(int a, int b, int z);
inline void spfa(int lin);
//inline void floyd();
inline void read();
int main()
{
    read();
    //cout<<v[1].v;
    //while(1);
    //floyd();
    int minn = 0x7fffffff;
    for (int i = 1; i <= n; i++)
    {
        int s = 0;
        spfa(i);
        for (int j = 1; j <= n; j++)
            s += d[j] * dis[j];
        minn = min(minn, s);
    }
    cout << minn << endl;
    getchar();
    getchar();
    //while(1);
}
inline void read()
{
    p = 1;
    memset(first, -1, sizeof(first));
    int m, a, b, z, p;
    cin >> p >> n >> m;
    for (int i = 1; i <= p; i++)
    {
        cin >> a;
        d[a]++;
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b >> z;
        add(a, b, z);
        add(b, a, z);
    }
    //cin>>x>>y;
}
inline void add(int a, int b, int z)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = z;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int lin)
{
    memset(dis, 0x3f, sizeof(dis));
    queue<int> p;
    bool flag[805] = {0};
    dis[lin] = 0;
    p.push(lin);
    flag[lin] = 1;
    while (!p.empty())
    {
        int k = p.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] > dis[k] + v[i].v)
            {
                dis[v[i].e] = dis[k] + v[i].v;
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    p.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        p.pop();
    }
}

// Problem1179:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct edge
{
    int STRAT, END, v;
    bool operator<(const edge &a) const
    {
        return v < a.v;
    }
} v[20005];
int father[3005];
int find(int x);
bool allcheck(int a);
void merge(int a, int b);
int main()
{
    int n, m;
    cin >> n >> m;
    int a, b, c, u;
    int p = 1, sum = 0;
    for (int i = 1; i <= n; i++)
        father[i] = i;
    while (m--)
    {
        cin >> u >> a >> b >> c;
        if (u == 1)
        {
            sum += c;
            merge(a, b);
        }
        else
        {
            v[p].STRAT = a;
            v[p].END = b;
            v[p++].v = c;
            v[p].STRAT = b;
            v[p].END = a;
            v[p++].v = c;
        }
    }
    int ans = 0, k = 0;
    int maxn = -1;
    sort(v + 1, v + p);
    //for(int i=1;i<=n;i++) father[i]=i;
    for (int i = 1; i < p; i++)
    {
        int x = v[i].STRAT, y = v[i].END;
        if (allcheck(n))
            break;
        if (find(x) != find(y))
        {
            father[find(y)] = find(x);
            //ans+=v[i].v;
            sum += v[i].v;
            //k++;
        }
    }
    cout << sum << endl;
}
int find(int x)
{
    if (x != father[x])
        father[x] = find(father[x]);
    return father[x];
}
bool allcheck(int a)
{
    int t = 0;
    for (int i = 1; i <= a; i++)
    {
        if (father[i] == i)
            t++;
        if (t > 1)
            return 0;
    }
    //if(t>1) return 0;
    if (t == 1)
        return 1;
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
        father[y] = x;
}
// Problem1180:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct edge
{
    int STRAT, END, v;
    bool operator<(const edge &a) const
    {
        return v < a.v;
    }
} v[20005];
int father[305];
int find(int x);
int main()
{
    int n, m;
    cin >> n >> m;
    int a, b, c;
    int p = 1, sum = 0;
    while (m--)
    {
        cin >> a >> b >> c;
        v[p].STRAT = a;
        v[p].END = b;
        v[p++].v = c;
        v[p].STRAT = b;
        v[p].END = a;
        v[p++].v = c;
    }
    int ans = 0, k = 0;
    int maxn = -1;
    sort(v + 1, v + p);
    for (int i = 1; i <= n; i++)
        father[i] = i;
    for (int i = 1; i < p; i++)
    {
        int x = v[i].STRAT, y = v[i].END;
        if (find(x) != find(y))
        {
            father[find(y)] = find(x);
            //ans+=v[i].v;
            maxn = max(maxn, v[i].v);
            k++;
        }
        if (k == n - 1)
            break;
    }
    cout << k << " " << maxn << endl;
}
int find(int x)
{
    if (x != father[x])
        father[x] = find(father[x]);
    return father[x];
}

// Problem1181:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[1005], f[1005];
//int f1[105];
int main()
{
    int n = 1;
    while (cin >> a[n])
        n++;
    n--;
    int maxl = 0x80000000;
    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (a[i] <= a[j] && f[i] < f[j] + 1)
            {
                f[i] = f[j] + 1;
            }
        }
        if (f[i] > maxl)
            maxl = f[i];
    }
    cout << maxl << endl;
    maxl = 0x80000000;
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (a[i] > a[j] && f[i] < f[j] + 1)
            {
                f[i] = f[j] + 1;
            }
        }
        if (f[i] > maxl)
            maxl = f[i];
    }
    cout << maxl << endl;
    //while(1);
}

// Problem1182:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[1005], f[1005], per[1005];
int c[1005];
int main()
{
    int n = 1;
    while (cin >> a[n])
        n++;
    f[1] = 1;
    //cout<<n<<endl;
    //while(1);
    n--;
    memset(per, -1, sizeof(per));
    int maxlen = 0x80000000;
    int h = 0;
    for (int i = 2; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (a[i] > a[j] && f[i] < f[j] + 1)
            {
                f[i] = f[j] + 1;
                per[i] = j;
            }
        }
        if (f[i] > maxlen)
        {
            maxlen = f[i];
            h = i;
        }
    }
    int j = 1;
    cout << "max=" << maxlen << endl;
    //cout<<h<<endl;
    for (int i = h; i != -1; i = per[i])
    {
        //cout<<a[i]<<" ";
        c[j] = a[i];
        j++;
    }
    for (int i = j - 1; i >= 1; i--)
    {
        cout << c[i] << " ";
    }
    //while(1);
}

// Problem1184:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct edge
{
    int END, v, next;
} v[20005];
int s[205], first[205];
int per[205];
int dis[205], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
int main()
{
    int n, x, y;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    memset(first, -1, sizeof(first));
    p = 1;
    while (1)
    {
        cin >> x >> y;
        if (x == 0 && y == 0)
            break;
        add(x, y, s[y]);
    }
    vector<int> l;
    int maxl = 0x80000000;
    //for(int i=1;i<=n;i++)
    //	add(i,i,dis[i]);
    for (int h = 1; h <= n; h++)
    {
        int maxl1 = 0x80000000;
        int flag[205] = {0};
        queue<int> q;
        memset(per, 0, sizeof(per));
        memset(dis, 0x80, sizeof(dis));
        q.push(h);
        per[h] = -1;
        dis[h] = s[h];
        while (!q.empty())
        {
            int k = q.front();
            flag[k] = 0;
            q.pop();
            for (int i = first[k]; i != -1; i = v[i].next)
            {
                if (dis[v[i].END] < dis[k] + v[i].v)
                {
                    dis[v[i].END] = dis[k] + v[i].v;
                    per[v[i].END] = k;
                    if (!flag[v[i].END])
                    {
                        flag[v[i].END] = 1;
                        q.push(v[i].END);
                    }
                }
            }
        }
        int o = -1;
        for (int i = 1; i <= n; i++)
            if (dis[i] > maxl1)
            {
                maxl1 = dis[i];
                o = i;
            }
        if (maxl1 > maxl)
        {
            maxl = maxl1;
            l.clear();
            for (int i = o; i != -1; i = per[i])
            {
                l.push_back(i);
            }
        }
    }
    for (int i = l.size() - 1; i > 0; i--)
        cout << l[i] << "-";
    cout << *l.begin() << endl;
    cout << maxl << endl;
    //while(1);
}

// Problem1185:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[105], f[105];
int f1[105];
int main()
{
    int n;
    int maxl1 = 0x80000000, maxl2 = 0x80000000,
        maxl = 0x80000000;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int k = 1; k <= n; k++)
    {
        memset(f, 0, sizeof(f));
        memset(f1, 0, sizeof(f1));
        for (int i = 1; i <= k; i++)
        {
            f[i] = 1;
            for (int j = 1; j <= i; j++)
            {
                if (a[i] > a[j] && f[i] < f[j] + 1)
                {
                    f[i] = f[j] + 1;
                }
            }
            //cout<<k<<" "<<i<<":"<<f[i]<<endl;
            if (i == k)
            {
                maxl1 = f[i]; /*cout<<"1:"<<maxl1<<endl;*/
            }
        }
        for (int i = k; i <= n; i++)
        {
            f1[i] = 1;
            for (int j = k; j <= i; j++)
            {
                if (a[i] < a[j] && f1[i] < f1[j] + 1)
                {
                    f1[i] = f1[j] + 1;
                }
            }
            if (f1[i] > maxl2)
            {
                maxl2 = f1[i]; /*cout<<"2:"<<maxl2<<endl;*/
            }
        }
        if (maxl1 + maxl2 - 1 > maxl)
        {
            maxl = maxl1 + maxl2 - 1; /*cout<<"l:"<<maxl<<endl;*/
        }
        maxl2 = 0x80000000;
        maxl1 = 0x80000000;
    }
    cout << n - maxl << endl;
    //while(1);
}

// Problem1186:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define LL long long
using namespace std;
int main()
{
    LL a[21][21];
    bool b[21][21];
    memset(b, 0, sizeof(b));
    memset(a, 0, sizeof(a));
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    //for(int i=0;i<21;i++)
    //           a[i][0]=1;
    //    for(int j=0;j<21;j++)
    //           a[0][j]=1;
    //for(int i=0;i<21;i++)
    //    {
    //        for(int j=0;j<21;j++)
    //             cout<<a[i][j]<<" ";
    //        cout<<endl;
    //    }
    //    cout<<endl<<endl;
    b[x][y] = 1;
    if ((x + 2 <= n) && (y + 1 <= m))
    {
        a[x + 2][y + 1] = 0;
        b[x + 2][y + 1] = 1;
    }
    if ((x + 1 <= n) && (y + 2 <= m))
    {
        a[x + 1][y + 2] = 0;
        b[x + 1][y + 2] = 1;
    }
    if ((x - 1 >= 0) && (y + 2 <= m))
    {
        a[x - 1][y + 2] = 0;
        b[x - 1][y + 2] = 1;
    }
    if ((x - 2 >= 0) && (y + 1 <= m))
    {
        a[x - 2][y + 1] = 0;
        b[x - 2][y + 1] = 1;
    }
    if ((x - 1 >= 0) && (y - 2 >= 0))
    {
        a[x - 1][y - 2] = 0;
        b[x - 1][y - 2] = 1;
    }
    if ((x - 2 >= 0) && (y - 1 >= 0))
    {
        a[x - 2][y - 1] = 0;
        b[x - 2][y - 1] = 1;
    }
    if ((x + 2 <= n) && (y - 1 >= 0))
    {
        a[x + 2][y - 1] = 0;
        b[x + 2][y - 1] = 1;
    }
    if ((x + 1 <= n) && (y - 2 >= 0))
    {
        a[x + 1][y - 2] = 0;
        b[x + 1][y - 2] = 1;
    }
    for (int i = 0; i < 21; i++)
    {
        if (!b[i][0])
            a[i][0] = 1;
        else
            break;
    }
    for (int j = 0; j < 21; j++)
    {
        if (!b[0][j])
            a[0][j] = 1;
        else
            break;
    }
    //a[0][j]=1;
    // if(x-1==0)
    //    {    int c=y+2;
    //         if(y-2>0)
    //            c=y-2;
    //         for(int j=c;j<=20;j++)
    //             a[0][j]=0;
    //    }
    //    if(x-2==0)
    //    {    int c=y+1;
    //         if(y-1>0)
    //            c=y-1;
    //         for(int j=c;j<=20;j++)
    //             a[0][j]=0;
    //    }
    //    if(y-2==0)
    //    {
    //         int c=x+1;
    //         if(x-1>0)
    //            c=x-1;
    //         for(int i=c;i<=20;i++)
    //             a[i][0]=0;
    //    }
    //    if(y-1==0)
    //    {
    //         int c=x+2;
    //         if(x-2>0)
    //            c=x-2;
    //         for(int i=c;i<=20;i++)
    //             a[i][0]=0;
    //    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!b[i][j])
            {
                a[i][j] = a[i][j - 1] + a[i - 1][j];
            }
    //for(int i=0;i<21;i++)
    //    {
    //        for(int j=0;j<21;j++)
    //             cout<<a[i][j]<<" ";
    //        cout<<endl;
    //    }
    cout << a[n][m];
    //while(1);
}

// Problem1186:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define LL long long
using namespace std;
int main()
{
    //do
    //{
    LL a[21][21];
    bool b[21][21];
    memset(b, 0, sizeof(b));
    memset(a, 0, sizeof(a));
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    for (int i = 0; i < 21; i++)
        a[i][0] = 1;
    for (int j = 0; j < 21; j++)
        a[0][j] = 1;
    //for(int i=0;i<21;i++)
    //    {
    //        for(int j=0;j<21;j++)
    //             cout<<a[i][j]<<" ";
    //        cout<<endl;
    //    }
    //    cout<<endl<<endl;
    b[x][y] = 1;
    if ((x + 2 <= n) && (y + 1 <= m))
    {
        a[x + 2][y + 1] = 0;
        b[x + 2][y + 1] = 1;
    }
    if ((x + 1 <= n) && (y + 2 <= m))
    {
        a[x + 1][y + 2] = 0;
        b[x + 1][y + 2] = 1;
    }
    if ((x - 1 >= 0) && (y + 2 <= m))
    {
        a[x - 1][y + 2] = 0;
        b[x - 1][y + 2] = 1;
    }
    if ((x - 2 >= 0) && (y + 1 <= m))
    {
        a[x - 2][y + 1] = 0;
        b[x - 2][y + 1] = 1;
    }
    if ((x - 1 >= 0) && (y - 2 >= 0))
    {
        a[x - 1][y - 2] = 0;
        b[x - 1][y - 2] = 1;
    }
    if ((x - 2 >= 0) && (y - 1 >= 0))
    {
        a[x - 2][y - 1] = 0;
        b[x - 2][y - 1] = 1;
    }
    if ((x + 2 <= n) && (y - 1 >= 0))
    {
        a[x + 2][y - 1] = 0;
        b[x + 2][y - 1] = 1;
    }
    if ((x + 1 <= n) && (y - 2 >= 0))
    {
        a[x + 1][y - 2] = 0;
        b[x + 1][y - 2] = 1;
    }
    // for(int i=0;i<21;i++)
    //    {
    //            if(!b[i][0])
    //               a[i][0]=1;
    //            else
    //               break;
    //    }
    //    for(int j=0;j<21;j++)
    //    {
    //            if(!b[0][j])
    //               a[0][j]=1;
    //            else
    //               break;
    //    }
    //a[0][j]=1;
    if (x - 1 == 0)
    {
        int c = y + 2;
        if (y - 2 > 0)
            c = y - 2;
        for (int j = c; j <= 20; j++)
            a[0][j] = 0;
    }
    if (x - 2 == 0)
    {
        int c = y + 1;
        if (y - 1 > 0)
            c = y - 1;
        for (int j = c; j <= 20; j++)
            a[0][j] = 0;
    }
    if (y - 2 == 0)
    {
        int c = x + 1;
        if (x - 1 > 0)
            c = x - 1;
        for (int i = c; i <= 20; i++)
            a[i][0] = 0;
    }
    if (y - 1 == 0)
    {
        int c = x + 2;
        if (x - 2 > 0)
            c = x - 2;
        for (int i = c; i <= 20; i++)
            a[i][0] = 0;
    }
    if (x == 0)
    {
        for (int j = y; j <= 20; j++)
            a[0][j] = 0;
    }
    if (y == 0)
    {
        for (int j = x; j <= 20; j++)
            a[j][0] = 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!b[i][j])
            {
                a[i][j] = a[i][j - 1] + a[i - 1][j];
            }
    //for(int i=0;i<21;i++)
    //    {
    //        for(int j=0;j<21;j++)
    //             cout<<a[i][j]<<" ";
    //        cout<<endl;
    //    }

    cout << a[n][m];
    //cout<<endl<<endl;
    // }while(1);
}

// Problem1187:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct city
{
    int s, e;
    bool operator<(const city &a) const
    {
        return s < a.s;
    }
} v[5005];
int f[5005];
int main()
{
    int n, a, b;
    cin >> n;
    int p = 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> a >> b;
        v[i].s = a;
        v[i].e = b;
    }
    sort(v + 1, v + n + 1);
    //cout<<v[1].s<<endl;
    int maxlen = 0x80000000;
    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (v[i].e > v[j].e && f[i] < f[j] + 1)
            {
                f[i] = f[j] + 1;
            }
        }
        if (f[i] > maxlen)
            maxlen = f[i];
    }
    cout << maxlen << endl;
}

// Problem1188:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[16][11];
int f[11], f1[11];
int maxl, n;
void dfs(int a, int b);
int main()
{
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i++)
        a[i][0] = 0;
    dfs(1, m);
    cout << maxl << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << i << " " << f1[i] << endl;
    }
    //while(1);
}
void dfs(int c, int b)
{
    if (c == n)
    {
        f[n] += b;
        int sum = 0;
        for (int i = 1; i <= n; i++)
            sum += a[i][f[i]];
        if (sum > maxl)
        {
            maxl = sum;
            //cout<<c<<":"<<maxl<<endl;
            for (int i = 1; i <= n; i++)
                f1[i] = f[i];
        }
        f[n] -= b;
        return;
    }
    if (b == 0)
    {
        int sum = 0;
        for (int i = 1; i <= n; i++)
            sum += a[i][f[i]];
        if (sum > maxl)
        {
            maxl = sum;
            //cout<<c<<":"<<maxl<<endl;
            for (int i = 1; i <= n; i++)
                f1[i] = f[i];
        }
        return;
    }
    for (int i = 0; i <= b; i++)
    {
        f[c] += i;
        dfs(c + 1, b - i);
        f[c] -= i;
    }
}

// Problem1190:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
struct edge
{
    int s, e;
    bool operator<(const edge &a) const
    {
        return s < a.s;
    }
} v[1005];
int f[1005];
int main()
{
    int m, n, k;
    cin >> n >> m;
    cin >> k;
    for (int i = 1; i <= k; i++)
        cin >> v[i].s >> v[i].e;
    sort(v + 1, v + k + 1);
    int maxl = 0;
    for (int i = 1; i <= k; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (v[j].e < v[i].e && f[i] < f[j] + 1)
            {
                f[i] = f[j] + 1;
            }
        }
        if (f[i] > maxl)
            maxl = f[i];
    }
    int s = (m + n - 2 * maxl) * 100;
    double q = (maxl * sqrt(2.0) * 100 + s);
    s = q;
    if (q - s >= 0.5)
        s++;
    cout << s << endl;
}

// Problem1192:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
string s[2005];
int f[2005];
bool check(string a, string b)
{
    if (b.size() >= a.size())
        return 0;
    for (int i = 0; i < b.size(); i++)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    int maxl = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (f[i] < f[j] + 1 && check(s[i], s[j]))
            {
                f[i] = f[j] + 1;
            }
        }
        if (f[i] > maxl)
            maxl = f[i];
    }
    cout << maxl;
}

// Problem1195:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
int a[1000][1000];
int f[1000][1000], g[1000][1000];
int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.out","w",stdout);
    int n;
    cin >> n;
    memset(a, 1, sizeof(a));
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= 2 * n - i; j++)
            scanf("%1d", &a[i][j]);
    int maxl = 0;
    for (int i = n; i >= 1; i--)
    {
        for (int j = i + 2; j <= n * 2 - i; j += 2)
        {
            if (a[i][j - 1] == 0 && a[i + 1][j - 1] == 0)
            {
                f[i][j] = min(f[i + 1][j - 1], f[i + 1][j + 1]) + 1;
                maxl = max(maxl, f[i][j]);
                continue;
            }
            if (a[i][j - 1] == 0)
                f[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= 2 * n - i + 1; j += 2)
        {
            if (a[i][j - 1] == 0 && a[i - 1][j - 1] == 0)
            {
                g[i][j] = min(g[i - 1][j - 1], g[i - 1][j + 1]) + 1;
                maxl = max(maxl, g[i][j]);
                continue;
            }
            if (a[i][j - 1] == 0)
                g[i][j] = 1;
        }
    }
    //	for(int i=0;i<=n;i++){
    //        for(int j=1;j<=i;j++)cout<<" ";
    //        for(int j=i+2;j<=2*n-i+1;j+=2){
    //            cout<<f[i][j]<<" ";
    //        }
    //        cout<<endl;
    //    }
    //    for(int i=1;i<=n;i++){
    //        for(int j=1;j<=i;j++)cout<<" ";
    //        for(int j=i+1;j<=2*n-i+1;j+=2){
    //            cout<<g[i][j]<<" ";
    //        }
    //        cout<<endl;
    //    }

    cout << maxl * maxl << endl;
    //while(1);
}

// Problem1196:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#define LL long long
#define FOR(i, s, e) for (int i = (s); i <= (e); i++)
using namespace std;
int a[35];
LL f[35][35];
int main()
{
    int n;
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
    FOR(l, 1, n)
    {
        FOR(i, 1, n + 1 - l)
        {
            f[i][i + l - 1] = max(2 * (a[i] + f[i + 1][i + l - 1]), 2 * (a[i + l - 1] + f[i][i + l - 2]));
        }
    }
    cout << f[1][n] << endl;
}

// Problem1197:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define LL long long
#define FOR(i, s, e) for (int i = (s); i <= (e); i++)
using namespace std;
struct number
{
    vector<LL> so;
    number() { ; }
    number(const int a) { *this = a; }
    number operator=(const int &a)
    {
        LL y = a / 1000000000;
        LL s = a % 1000000000;
        if (y != 0)
            so.push_back(y);
        so.push_back(s);
        return *this;
    }
    number operator+(const int &b)
    {
        number a;
        int y = b / 1000000000;
        int s = b % 1000000000;
        a.so.push_back(s);
        a.so.push_back(y);
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 1000000000;
            s = s % 1000000000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator*(const int &a)
    {
        number b = a;
        return *this * b;
    }
    number operator*(const number &a)
    {
        number c;
        for (int i = 0; i < a.so.size() + so.size() + 1; i++)
            c.so.push_back(0);
        for (int i = 0; i < so.size(); i++)
        {
            int y = 0;
            for (int j = 0; j < a.so.size(); j++)
            {
                c.so[i + j] += so[i] * a.so[j] + y;
                y = c.so[i + j] / 1000000000;
                c.so[i + j] %= 1000000000;
            }
            c.so[i + a.so.size()] = y;
        }
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    bool operator>(const number &a) const
    {
        if (so.size() > a.so.size())
            return 1;
        if (so.size() < a.so.size())
            return 0;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 0;
            }
            if (so[i] > a.so[i])
            {
                return 1;
            }
        }
        return 0;
    }
    bool operator<(const number &a) const
    {
        if (so.size() > a.so.size())
            return 0;
        if (so.size() < a.so.size())
            return 1;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 1;
            }
            if (so[i] > a.so[i])
            {
                return 0;
            }
        }
        return 0;
    }
};
ostream &operator<<(ostream &out, const number &a)
{
    printf("%d", a.so[a.so.size() - 1]);
    for (int i = a.so.size() - 2; i >= 0; i--)
        printf("%09d", a.so[i]);
    return out;
}
int a[105];
number f[105][105];
int main()
{
    int n;
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
    FOR(l, 1, n)
    {
        FOR(i, 1, n + 1 - l)
        {
            f[i][i + l - 1] = max((f[i + 1][i + l - 1] + a[i]) * 2, (f[i][i + l - 2] + a[i + l - 1]) * 2);
        }
    }
    cout << f[1][n] << endl;
}

// Problem1197:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define LL long long
#define FOR(i, s, e) for (int i = (s); i <= (e); i++)
using namespace std;
struct number
{
    vector<LL> so;
    number() { ; }
    number(const int a) { *this = a; }
    number operator=(const int &a)
    {
        LL x = a / 1000000000;
        LL y = a % 1000000000;
        if (x != 0)
            so.push_back(x);
        so.push_back(y);
        return *this;
    }
    number operator+(const int &b)
    {
        number a = b;
        if (so.size() > a.so.size())
        {
            FOR(i, a.so.size(), so.size() - 1)
            a.so.push_back(0);
        }
        else
        {
            FOR(i, so.size(), a.so.size() - 1)
            so.push_back(0);
        }
        int y = 0;
        number c;
        FOR(i, 0, max(so.size(), a.so.size()) - 1)
        {
            LL x = so[i] + a.so[i] + y;
            c.so.push_back(x % 1000000000);
            y = x / 1000000000;
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
            c.so.pop_back();
        return c;
    }
    number operator*(const int &b)
    {
        number a = b;
        number c;
        for (int i = 0; i < a.so.size() + so.size() + 1; i++)
            c.so.push_back(0);
        for (int i = 0; i < so.size(); i++)
        {
            int y = 0;
            for (int j = 0; j < a.so.size(); j++)
            {
                c.so[i + j] += so[i] * a.so[j] + y;
                y = c.so[i + j] / 1000000000;
                c.so[i + j] %= 1000000000;
            }
            c.so[i + a.so.size()] = y;
        }
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
            c.so.pop_back();
        return c;
    }
    bool operator<(const number &a) const
    {
        if (so.size() > a.so.size())
            return 0;
        if (so.size() < a.so.size())
            return 1;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 1;
            }
            if (so[i] > a.so[i])
            {
                return 0;
            }
        }
        return 0;
    }
};
ostream &operator<<(ostream &out, const number &a)
{
    printf("%d", a.so[a.so.size() - 1]);
    for (int i = a.so.size() - 2; i >= 0; i--)
        printf("%09d", a.so[i]);
    return out;
}
int a[105];
number f[105][105];
int main()
{
    int n;
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
    FOR(l, 1, n)
    {
        FOR(i, 1, n + 1 - l)
        {
            f[i][i + l - 1] = max((f[i + 1][i + l - 1] + a[i]) * 2, (f[i][i + l - 2] + a[i + l - 1]) * 2);
        }
    }
    cout << f[1][n] << endl;
}

// Problem1198:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct data
{
    int s, e;
} a[205];
int f[205][205];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].s;
        a[i - 1].e = a[i].s;
    }
    a[n].e = a[1].s;
    for (int i = n + 1; i <= 2 * n - 1; i++)
        a[i] = a[i - n];
    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= 2 * n - l; i++)
        {
            for (int k = i; k < i + l - 1; k++)
            {
                f[i][i + l - 1] = max(f[i][i + l - 1], f[i][k] + f[k + 1][i + l - 1] + a[i].s * a[k].e * a[i + l - 1].e);
            }
        }
    }
    int maxn = 1;
    for (int i = 1; i <= n; i++)
        maxn = max(maxn, f[i][i + n - 1]);
    cout << maxn << endl;
}

// Problem1199:
#include <iostream>
#include <cstdio>
#include <cstring>
#define LL long long
using namespace std;
int a[55];
LL f[55][55];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        f[i][i] = 0;
        f[i][i + 1] = 0;
    }
    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            for (int k = i; k <= i + l - 1; k++)
            {
                f[i][i + l - 1] = min(f[i][i + l - 1], f[i][k] + f[k][i + l - 1] + (LL)a[i] * a[i + l - 1] * a[k]);
            }
        }
    }
    cout << f[1][n] << endl;
    //while(1);
}

// Problem1203:
#include <iostream>
#include <string>
#include <queue>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
int main()
{
    LL n, m, k, x;
    cin >> n >> m >> k >> x;
    //LL b1=b,p1=p,k1=k;
    LL ans = 1;
    m %= n;
    LL l = 10 % n;
    while (k > 0)
    {
        if (k & 1)
            ans = (ans * l) % n;
        k = k >> 1;
        l = (l * l) % n;
    }
    cout << ((ans * m) % n + x) % n << endl;
    getchar();
    getchar();
    getchar();
    //getchar();
}

// Problem1207:
#include <iostream>
#include <cstdio>
#define LL long long
using namespace std;
int extgcd(LL a, LL b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int met = extgcd(b, a % b, x, y);
    int q = x;
    x = y;
    y = q - a / b * y;
    return met;
}
int main()
{
    //freopen("mod.in","r",stdin);
    //freopen("mod.out","w",stdout);
    LL a, b;
    int x, y;
    cin >> a >> b;
    int gcd = extgcd(a, b, x, y);
    int s = x / gcd;
    while (1)
    {
        if (s > 0)
            break;
        else
            s += b;
    }
    cout << s;
}

// Problem1240:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
struct data
{
    int number;
    int score;
};
int comp(const data &a, const data &b)
{
    if (a.score > b.score)
        return 1;
    if (a.score < b.score)
        return 0;
    if (a.number < b.number)
        return 1;
    return 0;
}

int main()
{
    int n, m;
    cin >> n >> m;
    data a[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].number >> a[i].score;
    }
    m *= 1.5;
    sort(a + 1, a + n + 1, comp);
    for (int i = 1;; i++)
    {
        if (a[m + 1].score == a[m].score)
            m = m + 1;
        else
            break;
    }
    cout << a[m].score << ' ' << m << endl;
    for (int i = 1; i <= m; i++)
    {
        cout << a[i].number << ' ' << a[i].score << endl;
    }
    //while(1);
}

// Problem1242:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
char a[30], b[30], c[30];
bool mark[30];
int map[300], n, ans;
void dfs(int pos, int y)
{
    ans++;
    //printf("%d\n", ans);
    if (pos == 0)
    {
        for (int i = 'A'; i < 'A' + n; i++)
            printf("%d ", map[i]);
        exit(0);
    }
    if (map[a[pos]] != -1 && map[b[pos]] != -1 && map[c[pos]] != -1)
    {
        if ((map[a[pos]] + map[b[pos]] + y) % n != map[c[pos]])
            return;
        else
            dfs(pos - 1, (map[a[pos]] + map[b[pos]] + y) / n);
    }
    else if (map[a[pos]] != -1 && map[b[pos]] != -1)
    {
        if (mark[(map[a[pos]] + map[b[pos]] + y) % n])
            return;
        else
        {
            map[c[pos]] = (map[a[pos]] + map[b[pos]] + y) % n;
            mark[(map[a[pos]] + map[b[pos]] + y) % n] = 1;
            dfs(pos - 1, (map[a[pos]] + map[b[pos]] + y) / n);
            mark[(map[a[pos]] + map[b[pos]] + y) % n] = 0;
            map[c[pos]] = -1;
        }
    }
    else if (map[a[pos]] != -1 && map[c[pos]] != -1)
    {
        int now = map[c[pos]] + n - y - map[a[pos]];
        if (mark[now % n])
            return;
        map[b[pos]] = now % n;
        mark[now % n] = 1;
        dfs(pos - 1, (now % n) == now ? 1 : 0);
        map[b[pos]] = -1;
        mark[now % n] = 0;
    }
    else if (map[b[pos]] != -1 && map[c[pos]] != -1)
    {
        int now = map[c[pos]] + n - y - map[b[pos]];
        if (mark[now % n])
            return;
        map[a[pos]] = now % n;
        mark[now % n] = 1;
        dfs(pos - 1, (now % n) == now ? 1 : 0);
        map[a[pos]] = -1;
        mark[now % n] = 0;
    }
    else if (map[a[pos]] != -1)
    {
        for (int i = 0; i < n; i++)
            if (!mark[i] && !mark[(map[a[pos]] + i + y) % n])
            {
                map[b[pos]] = i;
                map[c[pos]] = (map[a[pos]] + i + y) % n;
                mark[i] = 1;
                mark[(map[a[pos]] + i + y) % n] = 1;
                dfs(pos - 1, (map[a[pos]] + i + y) / n);
                map[b[pos]] = -1;
                map[c[pos]] = -1;
                mark[i] = 0;
                mark[(map[a[pos]] + i + y) % n] = 0;
            }
    }
    else if (map[b[pos]] != -1)
    {
        for (int i = 0; i < n; i++)
            if (!mark[i] && !mark[(map[b[pos]] + i + y) % n])
            {
                map[a[pos]] = i;
                map[c[pos]] = (map[b[pos]] + i + y) % n;
                mark[i] = 1;
                mark[(map[b[pos]] + i + y) % n] = 1;
                dfs(pos - 1, (map[b[pos]] + i + y) / n);
                map[a[pos]] = -1;
                map[c[pos]] = -1;
                mark[i] = 0;
                mark[(map[b[pos]] + i + y) % n] = 0;
            }
    }
    else if (map[c[pos]] != -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (!mark[i] && !mark[(map[c[pos]] + n - i - y) % n])
            {
                map[a[pos]] = i;
                map[b[pos]] = (map[c[pos]] + n - i - y) % n;
                mark[i] = 1;
                mark[(map[c[pos]] + n - i - y) % n] = 1;
                dfs(pos - 1, ((map[c[pos]] + n - i - y) % n == (map[c[pos]] + n - i - y)));
                map[a[pos]] = -1;
                map[b[pos]] = -1;
                mark[i] = 0;
                mark[(map[c[pos]] + n - i - y) % n] = 0;
            }
        }
    }
    else
    {
        // printf("\\\\\n");
        for (int i = n - 1; i >= 0; i--)
        {
            if (mark[i])
                continue;
            mark[i] = 1;
            map[a[pos]] = i;
            // printf("------__\n");
            for (int j = n - 1; j >= 0; j--)
            {
                if (!mark[j] && !mark[(i + j + y) % n])
                {
                    // printf("===\n");
                    mark[j] = mark[(i + j + y) % n] = 1;
                    map[b[pos]] = j;
                    map[c[pos]] = (i + j + y) % n;
                    dfs(pos - 1, (i + j + y) / n);
                    mark[j] = mark[(i + j + y) % n] = 0;
                    map[b[pos]] = -1;
                    map[c[pos]] = -1;
                }
                else if (mark[j] && mark[(i + j + y) % n] && (j == map[b[pos]]) && ((i + j + y) % n == map[c[pos]]))
                {
                    dfs(pos - 1, (i + j + y) / n);
                }
                else if (mark[j] && (j == map[b[pos]]) && !mark[(i + j + y) % n])
                {
                    // printf("----\n");
                    mark[(i + j + y) % n] = 1;
                    map[c[pos]] = (i + j + y) % n;
                    dfs(pos - 1, (i + j + y) / n);
                    map[c[pos]] = -1;
                    mark[(i + j + y) % n] = 0;
                }
            }
            map[a[pos]] = -1;
            mark[i] = 0;
        }
    }
}
int main()
{
    // freopen("alpha.in","r",stdin);
    // freopen("alpha.out","w",stdout);
    scanf("%d", &n);
    scanf("%s%s%s", a + 1, b + 1, c + 1);
    for (int i = 'A'; i < 'A' + n; i++)
        map[i] = -1;
    dfs(n, 0);
}
// Problem1250:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
struct data
{
    int a, b;
    bool operator>(const data &s) const
    {
        return a > s.a;
    }
    bool operator<(const data &s) const
    {
        return a < s.a;
    }
};
data a[100005], b[100005];
int e[100005], o[100005];
long long ans = 0;
void merge_sort(int *a, int r, int l)
{
    //memset(o,0,sizeof(o));
    if (r == l)
        return;
    int mid = (r + l) / 2;
    merge_sort(a, r, mid);
    merge_sort(a, mid + 1, l);
    int i = r, j = mid + 1, k = 0;
    while (i <= mid && j <= l)
    {
        if (a[i] > a[j])
        {
            ans += mid - i + 1;
            //ans%=99999997;
            o[k++] = a[j];
            j++;
        }
        else
        {
            o[k++] = a[i];
            i++;
        }
    }
    while (i <= mid)
        o[k++] = a[i++];
    while (j <= l)
        o[k++] = a[j++];
    for (int i = r, j = 0; j < k; j++, i++)
        a[i] = o[j];
}

int main()
{
    //freopen("1.txt","r",stdin);
    //freopen("3.txt","w",stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i].a);
        a[i].b = i;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i].a);
        b[i].b = i;
    }
    //return 0;
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    //for(int i=1;i<=n;i++) c[a[i].b]=i;
    //for(int i=1;i<=n;i++) d[b[i].b]=i;
    for (int i = 1; i <= n; i++)
        e[a[i].b] = b[i].b;
    //return 0;
    //for(int i=1;i<=n;i++)
    //    {
    //            cout<<e[i]<<" ";
    //    }
    //while(1);
    merge_sort(e, 1, n);
    cout << ans % 99999997;
}

// Problem1251:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define LL long long
using namespace std;
int a[55];
int shu[55];
char s[55], fuhao[55];
LL f[55][55], g[55][55];
int main()
{
    //freopen("polygon1.in","r",stdin);
    //freopen("polygon1.out","w",stdout);
    int n;
    vector<int> ans;
    int maxn = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i] >> a[i];
    for (int t = 1; t <= n; t++)
    {
        memset(shu, 0, sizeof(shu));
        memset(fuhao, 0, sizeof(fuhao));
        memset(f, 0x80, sizeof(f));
        memset(g, 0x3f, sizeof(g));
        int p = 1;
        for (int i = t; i <= n; i++)
            shu[p++] = a[i];
        for (int i = 1; i < t; i++)
            shu[p++] = a[i];
        //for(int i=1;i<=n;i++)cout<<shu[i]<<" ";
        //cout<<endl;
        //while(1);
        p = 1;
        for (int i = t + 1; i <= n; i++)
            fuhao[p++] = s[i];
        for (int i = 1; i < t; i++)
            fuhao[p++] = s[i];
        for (int i = 1; i <= n; i++)
            f[i][i] = shu[i];
        for (int i = 1; i <= n; i++)
            g[i][i] = shu[i];
        for (int l = 2; l <= n; l++)
        {
            for (int i = 1; i <= n - l + 1; i++)
            {
                for (int k = i; k < i + l - 1; k++)
                {
                    if (fuhao[k] == 't')
                    {
                        f[i][i + l - 1] = max(f[i][i + l - 1], f[i][k] + f[k + 1][i + l - 1]);
                        g[i][i + l - 1] = min(g[i][i + l - 1], g[i][k] + g[k + 1][i + l - 1]);
                    }
                    else
                    {
                        g[i][i + l - 1] = min(g[i][i + l - 1], g[i][k] * g[k + 1][i + l - 1]);
                        f[i][i + l - 1] = max(f[i][i + l - 1], f[i][k] * f[k + 1][i + l - 1]);
                        g[i][i + l - 1] = min(g[i][i + l - 1], f[i][k] * f[k + 1][i + l - 1]);
                        f[i][i + l - 1] = max(f[i][i + l - 1], g[i][k] * g[k + 1][i + l - 1]);
                    }
                }
            }
        }
        //getchar();
        //getchar();
        if (f[1][n] > maxn)
        {
            maxn = f[1][n];
            ans.clear();
            ans.push_back(t);
            continue;
        }
        if (f[1][n] == maxn)
        {
            ans.push_back(t);
        }
        //while(1);
        //getchar();
        //getchar();
    }
    cout << maxn << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    //while(1);
}

// Problem1252:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define LL long long
#define FOR(i, s, e) for (int i = (s); i <= (e); i++)
using namespace std;
struct number
{
    vector<LL> so;
    void clear()
    {
        so.clear();
    }
    number() { ; }
    number(const int a) { *this = a; }
    number operator=(const int &a)
    {
        LL x = a / 1000000000;
        LL y = a % 1000000000;
        if (x != 0)
            so.push_back(x);
        so.push_back(y);
        return *this;
    }
    number operator+(const int &b)
    {
        number a = b;
        if (so.size() > a.so.size())
        {
            FOR(i, a.so.size(), so.size() - 1)
            a.so.push_back(0);
        }
        else
        {
            FOR(i, so.size(), a.so.size() - 1)
            so.push_back(0);
        }
        int y = 0;
        number c;
        FOR(i, 0, max(so.size(), a.so.size()) - 1)
        {
            LL x = so[i] + a.so[i] + y;
            c.so.push_back(x % 1000000000);
            y = x / 1000000000;
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
            c.so.pop_back();
        return c;
    }
    number operator+(const number &b)
    {
        number a = b;
        if (so.size() > a.so.size())
        {
            FOR(i, a.so.size(), so.size() - 1)
            a.so.push_back(0);
        }
        else
        {
            FOR(i, so.size(), a.so.size() - 1)
            so.push_back(0);
        }
        int y = 0;
        number c;
        FOR(i, 0, max(so.size(), a.so.size()) - 1)
        {
            LL x = so[i] + a.so[i] + y;
            c.so.push_back(x % 1000000000);
            y = x / 1000000000;
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
            c.so.pop_back();
        return c;
    }
    number operator*(const int &b)
    {
        number c;
        for (int i = 1; i <= so.size() + 1; i++)
            c.so.push_back(0);
        int y = 0;
        for (int i = 0; i < so.size(); i++)
        {
            c.so[i] += so[i] * b + y;
            y = c.so[i] / 1000000000;
            c.so[i] %= 1000000000;
        }
        c.so[so.size()] = y;
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
            c.so.pop_back();
        return c;
    }
    bool operator<(const number &a) const
    {
        if (so.size() > a.so.size())
            return 0;
        if (so.size() < a.so.size())
            return 1;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 1;
            }
            if (so[i] > a.so[i])
            {
                return 0;
            }
        }
        return 0;
    }
};
ostream &operator<<(ostream &out, const number &a)
{
    printf("%d", a.so[a.so.size() - 1]);
    for (int i = a.so.size() - 2; i >= 0; i--)
        printf("%09d", a.so[i]);
    return out;
}
int a[105][105];
number f[105][105][105];
number sum;
int main()
{
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n)
        FOR(j, 1, m) cin >> a[i][j];
    FOR(j, 1, n)
    {
        //FOR(i,1,n)FOR(k,1,m)f[i][k].clear();
        FOR(l, 1, m)
        {
            FOR(i, 1, m + 1 - l)
            {
                f[j][i][i + l - 1] = max((f[j][i + 1][i + l - 1] + a[j][i]) * 2, (f[j][i][i + l - 2] + a[j][i + l - 1]) * 2);
            }
        }
        sum = sum + f[j][1][m];
    }
    cout << sum << endl;
}

// Problem1253:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define LL long long
#define FOR(i, s, e) for (int i = (s); i <= (e); i++)
using namespace std;
int max(int a, int b, int c, int d)
{
    int s[4] = {a, b, c, d};
    return *max_element(s, s + 4);
}
int f[51][51][51][51];
int a[51][51];
int main()
{
    //freopen("1.txt","w",stdout);
    int m, n;
    cin >> m >> n;
    FOR(i, 1, m)
        FOR(j, 1, n) cin >> a[i][j];
    FOR(i1, 1, m)
    {
        FOR(j1, 1, n)
        {
            FOR(i2, 1, m)
            {
                FOR(j2, 1, n)
                {
                    if (i1 == m && j1 == n && j2 == n && i2 == m)
                        f[i1][j1][i2][j2] = max(f[i1 - 1][j1][i2 - 1][j2],
                                                f[i1][j1 - 1][i2 - 1][j2],
                                                f[i1 - 1][j1][i2][j2 - 1],
                                                f[i1][j1 - 1][i2][j2 - 1]) +
                                            a[i1][j1] + a[i2][j2];
                    if (i1 != i2 || j1 != j2)
                        f[i1][j1][i2][j2] = max(f[i1 - 1][j1][i2 - 1][j2],
                                                f[i1][j1 - 1][i2 - 1][j2],
                                                f[i1 - 1][j1][i2][j2 - 1],
                                                f[i1][j1 - 1][i2][j2 - 1]) +
                                            a[i1][j1] + a[i2][j2];
                }
            }
        }
    }
    // for(int i=1;i<=m;i++){
    // cout<<i<<":"<<endl;
    // for(int j=1;j<=n;j++){
    // cout<<j<<":"<<endl;
    // for(int i1=1;i1<=m;i1++){
    // for(int j1=1;j1<=m;j1++){
    // cout<<f[i][j][i1][j1]<<" ";
    // }
    // cout<<endl;
    // }
    // cout<<endl;
    // }
    // cout<<endl;
    // }
    cout << f[m][n][m][n] << endl;
}

// Problem1253:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#define FOR(i, s, e) for (int i = (s); i <= (e); i++)
using namespace std;
int max(int a, int b, int c, int d)
{
    int s[4] = {a, b, c, d};
    return *max_element(s, s + 4);
}
int a[101][101];
int f[105][101][101];
int main()
{
    int m, n;
    cin >> m >> n;
    FOR(i, 1, m)
        FOR(j, 1, n) cin >> a[i][j];
    for (int k = 1; k <= m + n; k++)
    {
        for (int i = 1; i <= m; i++)
        {
            for (int i1 = 1; i1 <= m; i1++)
            {
                if (i != i1 || (k == m + n && i1 == m && i == m))
                {
                    f[k][i][i1] = max(f[k - 1][i][i1], f[k - 1][i - 1][i1], f[k - 1][i][i1 - 1], f[k - 1][i - 1][i1 - 1]) + a[i][k - i] + a[i1][k - i1];
                }
            }
        }
    }
    cout << f[m + n][m][m] << endl;
    //while(1);
}

// Problem1255:
#include <iostream>
#include <cstdio>
#include <cstring>
#define LL long long
using namespace std;
LL a[50][50];
LL f[50][10];
int main()
{
    int n, k;
    cin >> n >> k;
    k++;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++)
    {
        LL sum = 0;
        for (int j = i; j < n; j++)
        {
            sum = sum * 10 + s[j] - '0';
            a[i + 1][j + 1] = sum;
        }
    }
    memset(f, -1, sizeof(f));
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= min(i, k); j++)
        {
            for (int l = 0; l < i; l++)
            {
                f[i][j] = max(f[i][j], f[l][j - 1] * a[l + 1][i]);
            }
        }
    }
    cout << f[n][k] << endl;
}

// Problem1256:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define LL long long
void dfs(int l, int m);
LL a[21][21];
LL f[21][21];
int g[21][21];
string n;
int main()
{
    //freopen("cjzd.in","r",stdin);
    //freopen("cjzd.out","w",stdout);
    int t;
    cin >> t;
    while (t--)
    {
        int m;
        memset(f, -1, sizeof(f));
        memset(g, 0, sizeof(g));
        memset(a, 0, sizeof(a));
        cin >> n >> m;
        for (int i = 0; i < n.size(); i++)
        {
            LL sum = 0;
            for (int j = i; j < n.size(); j++)
            {
                sum = sum * 10 + n[j] - 48;
                a[i + 1][j + 1] = sum;
                //cout<<i<<":"<<j<<":"<<a[i][j]<<" ";
            }
            //cout<<endl;
        }

        //for(int i=1;i<=n.size();i++){
        //			for(int j=1;j<=n.size();j++){
        //				cout<<a[i][j]<<" ";
        //			}
        //			cout<<endl;
        //		}
        f[0][0] = 1;
        for (int i = 1; i <= n.size(); i++)
        {
            for (int j = 1; j <= min(i, m); j++)
            {
                for (int k = 1; k <= i; k++)
                {
                    if (f[k - 1][j - 1] * a[k][i] > f[i][j])
                    {
                        f[i][j] = f[k - 1][j - 1] * a[k][i];
                        g[i][j] = k - 1;
                    }
                }
            }
        }
        cout << f[n.size()][m] << endl;
        dfs(n.size(), m);
        cout << endl;
        //while(1);
    }
    getchar();
    getchar();
}
void dfs(int l, int m)
{
    if (m == 0)
        return;
    dfs(g[l][m], m - 1);
    for (int i = g[l][m]; i < l; i++)
        cout << n[i];
    cout << " ";
}

// Problem1257:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
int main()
{
    //freopen("codes.in","r",stdin);
    //freopen("codes.out","w",stdout);
    int t;
    cin >> t;
    int f[505][505], f1[505];
    int s1[505], s2[505];
    while (t--)
    {
        int n, m;
        memset(s1, 0, sizeof(s1));
        memset(f, 0, sizeof(f));
        memset(f1, 0, sizeof(f1));
        memset(s2, 0, sizeof(s2));
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> s1[i];
        }
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> s2[i];
        }
        int i, j;
        int maxl = 0;
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= m; j++)
            {
                if (s1[i] == s2[j])
                {
                    for (int k = 0; k < j; k++)
                    {
                        if (s2[k] < s2[j] || k == 0)
                        {
                            f[i][j] = max(f[i][j], f[i - 1][k] + 1);
                        }
                    }
                    maxl = max(maxl, f[i][j]);
                }
                else
                {
                    f[i][j] = f[i - 1][j];
                }
            }
        }
        //for(int i=1;i<=n;i++){
        //	for(int j=1;j<=m;j++){
        //		cout<<f[i][j]<<" ";
        //	}
        //	cout<<endl;
        //}
        cout << maxl << endl;
        //cout<<endl<<endl<<endl;
    }
    //while(1);
}

// Problem1258:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
int a[1005][1005];
int main()
{
    char s1[1005], s2[1005];
    gets(s1);
    gets(s2);
    int maxlen = 0;
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= strlen(s1); i++)
    {
        for (int j = 1; j <= strlen(s2); j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                a[i][j] = a[i - 1][j - 1] + 1;
                maxlen = max(maxlen, a[i][j]);
            }
        }
    }
    cout << maxlen << endl;
}

// Problem1258:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
int a[1005][1005];
int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    int maxlen = 0;
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= s1.size(); i++)
    {
        for (int j = 1; j <= s2.size(); j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                a[i][j] = a[i - 1][j - 1] + 1;
                maxlen = max(maxlen, a[i][j]);
            }
            else
            {
                a[i][j] = 0;
            }
        }
    }
    cout << maxlen << endl;
}
// Problem1259:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i, s, N) for (int i = (s); i <= (N); i++)
using namespace std;
int w[105][105];
int h[105];
int f[105][10005];
int main()
{
    int n;
    cin >> n;
    FOR(i, 1, n)
    FOR(j, 1, 101)
    {
        cin >> w[i][j];
        if (w[i][j] == -1)
            break;
        h[i] += w[i][j];
    }
    FOR(i, 1, n)
    f[i][0] = 1;
    FOR(i, 1, n)
    {
        for (int j = 1; w[i][j] != -1; j++)
        {
            for (int h1 = h[i]; h1 >= w[i][j]; h1--)
            {
                f[i][h1] = f[i][h1 - w[i][j]] || f[i][h1];
            }
        }
    }
    // FOR(i,1,n){
    // FOR(j,0,h[i]){
    // cout<<f[i][j]<<" ";
    // }
    // cout<<endl;
    // }
    int H = *min_element(h + 1, h + n + 1);
    for (int h1 = H; h1 >= 0; h1--)
    {
        int i;
        for (i = 1; i <= n; i++)
        {
            if (!f[i][h1])
                break;
        }
        if (i == n + 1)
        {
            cout << h1 << endl;
            break;
        }
    }
    //while(1);
}

// Problem1260:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int mi[2505];
int f[2505];
int main()
{
    int n, m;
    cin >> n >> mi[0];
    for (int i = 1; i <= n; i++)
    {
        cin >> mi[i];
        mi[i] += mi[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        f[i] = mi[i];
        for (int j = 1; j < i; j++)
        {
            f[i] = min(f[i], mi[0] + f[j] + f[i - j]);
        }
    }
    cout << f[n] << endl;
    //while(1);
}

// Problem1260:
#include <string.h>
#include <stdio.h>
int mi[2505];
int f[2505];
int min(int a, int b)
{
    if (a > b)
        return b;
    return a;
}
int main()
{
    int n, m;
    memset(f, 0, sizeof(f));
    memset(mi, 0, sizeof(mi));
    int i, j;
    scanf("%d%d", &n, &mi[0]);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &mi[i]);
        mi[i] += mi[i - 1];
    }
    for (i = 1; i <= n; i++)
    {
        f[i] = mi[i];
        for (j = 1; j < i; j++)
        {
            f[i] = min(f[i], mi[0] + f[j] + f[i - j]);
        }
    }
    printf("%d\n", f[n]);
}

// Problem1261:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
int a[30005];
int f[30005];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int maxl1 = 0;
    for (int i = 1; i <= n; i++)
    {
        int s = upper_bound(f + 1, f + maxl1 + 1, -a[i]) - f;
        if (s > maxl1)
            maxl1 = s;
        if (f[s] > -a[i])
            f[s] = -a[i];
    }
    int maxl2 = 0;
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        int s = upper_bound(f + 1, f + maxl2 + 1, a[i]) - f;
        if (s > maxl2)
            maxl2 = s;
        if (f[s] > a[i])
            f[s] = a[i];
    }
    cout << min(n - maxl1, n - maxl2);
}

// Problem1265:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[200];
int f[200][200];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        f[i][i] = 0;
    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            for (int k = i; k < i + l - 1; k++)
                f[i][i + l - 1] = min(f[i][i + l - 1], f[i][k] + f[k + 1][i + l - 1] + a[i + l - 1] - a[i - 1]);
        }
    }
    cout << f[1][n] << endl;
    memset(f, 0, sizeof(f));
    //cout<<a[3]-a[1]<<endl;
    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            for (int k = i; k < i + l - 1; k++)
                f[i][i + l - 1] = max(f[i][i + l - 1], f[i][k] + f[k + 1][i + l - 1] + a[i + l - 1] - a[i - 1]);
            //f[i][i+l-1]=max(f[i][i+1]+f[i+2][i+l-1],f[i][i+l-3]+f[i+l-2][i+l-1])+a[i+l-1]-a[i-1];
        }
    }
    cout << f[1][n] << endl;
    //while(1);
}

// Problem1265:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[200];
int f[200][200];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        f[i][i] = 0;
    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            for (int k = i; k < i + l - 1; k++)
                f[i][i + l - 1] = min(f[i][i + l - 1], f[i][k] + f[k + 1][i + l - 1] + a[i + l - 1] - a[i - 1]);
        }
    }
    cout << f[1][n] << endl;
    memset(f, 0, sizeof(f));
    //cout<<a[3]-a[1]<<endl;
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            f[i][i + l - 1] = max(f[i + 1][i + l - 1], f[i][i + l - 2]) + a[i + l - 1] - a[i - 1];
            //f[i][i+l-1]=max(f[i][i+1]+f[i+2][i+l-1],f[i][i+l-3]+f[i+l-2][i+l-1])+a[i+l-1]-a[i-1];
        }
    }
    cout << f[1][n] << endl;
    //while(1);
}

// Problem1266:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[2000];
int f[2000][2000];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        //a[i]+=a[i-1];
    }
    for (int i = n + 1; i <= 2 * n - 1; i++)
        a[i] = a[i - n];
    for (int i = 1; i <= 2 * n - 1; i++)
        a[i] += a[i - 1];
    ///for(int i=1;i<=2*n-1;i++)cout<<a[i]<<" ";
    //cout<<endl;
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= 2 * n - 1; i++)
        f[i][i] = 0;
    for (int l = 1; l <= 2 * n - 1; l++)
    {
        for (int i = 1; i <= 2 * n - l; i++)
        {
            for (int k = i; k < i + l - 1; k++)
                f[i][i + l - 1] = min(f[i][i + l - 1], f[i][k] + f[k + 1][i + l - 1] + a[i + l - 1] - a[i - 1]);
        }
    }
    int minn = 0x7fffffff;
    for (int i = 1; i <= n; i++)
    {
        minn = min(minn, f[i][i + n - 1]);
    }
    //cout<<endl;
    cout << minn << endl;
    memset(f, 0, sizeof(f));
    //cout<<a[3]-a[1]<<endl;
    for (int l = 2; l <= 2 * n - 1; l++)
    {
        for (int i = 1; i <= 2 * n - l; i++)
        {
            f[i][i + l - 1] = max(f[i + 1][i + l - 1], f[i][i + l - 2]) + a[i + l - 1] - a[i - 1];
            //f[i][i+l-1]=max(f[i][i+1]+f[i+2][i+l-1],f[i][i+l-3]+f[i+l-2][i+l-1])+a[i+l-1]-a[i-1];
        }
    }
    int maxn = -1;
    for (int i = 1; i <= n; i++)
    {
        maxn = max(maxn, f[i][i + n - 1]);
    }
    cout << maxn << endl;
    //while(1);
}

// Problem1268:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[4005];
int f[4005][4005];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = n + 1; i <= 2 * n - 1; i++)
        a[i] = a[i - n];
    for (int i = 1; i <= 2 * n - 1; i++)
        a[i] += a[i - 1];
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= 2 * n - l; i++)
        {
            f[i][i + l - 1] = max(f[i + 1][i + l - 1], f[i][i + l - 2]) + a[i + l - 1] - a[i - 1];
        }
    }
    int maxn = -1;
    for (int i = 1; i <= n; i++)
    {
        maxn = max(maxn, f[i][i + n - 1]);
    }
    cout << maxn << endl;
}

// Problem1270:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
char s[105];
int n;
int f[105][105];
int Judge(int i, int k, int l, int r)
{
    if ((r - i + 1) % (k - i + 1))
        return 0;
    int len = k - i + 1;
    for (int j = l; j <= r; j++)
    {
        int H = (j - l) % len;
        if (H == 0)
            H = len;
        if (s[i + H] != s[j])
            return 0;
    }
    return 1;
}
void DP()
{
    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            f[i][j] = l;
            for (int k = i; k < j; k++)
            {
                if (Judge(i, k, i, j))
                    f[i][j] = min(f[i][j], f[i][k] + 3 + (int)floor(log10(l / (k - i + 1))));
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
            }
        }
    }
}
int main()
{
    //freopen("1.out", "w", stdout);
    scanf("%s", s + 1);
    memset(f, 0x3f, sizeof(f));
    n = strlen(s + 1);
    DP();
    //printf("%d\n", f[6][14]);
    printf("%d\n", f[1][n]);
}
// Problem1277:
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
struct data
{
    int a;
    int ch[2];
    int fa;
} tree[35];
int a[35];
int f[35][35];
int b[35][35];
int dfs(int s, int e)
{
    if (s > e)
        return 0;
    if (s == e)
    {
        cout << s << " ";
        return 0;
    }
    cout << b[s][e] << " ";
    dfs(s, b[s][e] - 1);
    dfs(b[s][e] + 1, e);
}
int main()
{
    //freopen("jfecs.in","r",stdin);
    //freopen("jfecs.out","w",stdout);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= n + 1; j++)
            f[i][j] = 1;
    for (int i = 1; i <= n; i++)
        f[i][i] = a[i];
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            for (int k = i; k <= i + l - 1; k++)
            {
                if (f[i][i + l - 1] < f[i][k - 1] * f[k + 1][i + l - 1] + a[k])
                {
                    f[i][i + l - 1] = f[i][k - 1] * f[k + 1][i + l - 1] + a[k];
                    b[i][i + l - 1] = k;
                }
                //f[i][i+l-1]=max(f[i][i+l-1],f[i][k-1]*f[k+1][i+l-1]+a[i]);
            }
        }
    }
    cout << f[1][n] << endl;
    dfs(1, n);
    //q_graph(b[1][n]);
}

// Problem1278:
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 105;
bool flag[N];
int a[N][N], n, Q, f[N][N];
struct node
{
    int data;
    int ch[2];
} tree[N];
void buildtree(int x)
{
    flag[x] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (!flag[i] && a[x][i] != -1)
        {
            if (tree[x].ch[0] == 0)
                tree[x].ch[0] = i;
            else
                tree[x].ch[1] = i;
            tree[i].data = a[x][i];
            buildtree(i);
        }
    }
}
int dp(int x, int s)
{
    if (f[x][s] != -1)
        return f[x][s];
    f[x][s] = 0;
    if (x == 0 || s == 0)
        return f[x][s];
    for (int i = 0; i < s; i++)
    {
        f[x][s] = max(f[x][s], dp(tree[x].ch[0], i) + dp(tree[x].ch[1], s - i - 1));
    }
    f[x][s] += tree[x].data;
    return f[x][s];
}
int main()
{
    //freopen("ecappletree.in","r",stdin);
    //freopen("ecappletree.out","w",stdout);
    memset(a, -1, sizeof(a));
    memset(f, -1, sizeof(f));
    cin >> n >> Q;
    int s, e;
    for (int i = 1; i < n; i++)
    {
        cin >> s >> e;
        cin >> a[s][e];
        a[e][s] = a[s][e];
    }
    buildtree(1);
    cout << dp(1, Q + 1) << endl;
}

// Problem1279:
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 1005;
int a[N][N], w[N], f[N][N], m;
void dfs(int x)
{
    for (int i = 1; i <= m; i++)
        f[x][i] = w[x];
    for (int i = 1; i <= a[x][0]; i++)
    {
        dfs(a[x][i]);
        for (int v = m; v > 0; v--)
        {
            for (int j = 0; j < v; j++)
            {
                f[x][v] = max(f[x][v], f[a[x][i]][j] + f[x][v - j]);
            }
        }
    }
}
int main()
{
    int n;
    cin >> n >> m;
    int s;
    for (int i = 1; i <= n; i++)
    {
        cin >> s >> w[i];
        a[s][++a[s][0]] = i;
    }
    m++;
    dfs(0);
    cout << f[0][m] << endl;
}
// Problem1279:
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1005;
int a[N][N], w[N];
int f[N][N];
int n, m;
struct node
{
    int data;
    int ch[2];
    node() { ch[0] = ch[1] = -1; }
} tree[N];
void buildtree(void)
{
    for (int i = 1; i <= n; i++)
        tree[i].data = w[i];
    for (int i = 0; i <= n; i++)
    {
        if (a[i][0] == 0)
            continue;
        tree[i].ch[0] = a[i][1];
        int p = a[i][1];
        for (int j = 2; j <= a[i][0]; j++)
        {
            tree[p].ch[1] = a[i][j];
            p = a[i][j];
        }
    }
}
int dp(int x, int s)
{
    if (x == -1)
        return 0;
    if (f[x][s] != -1)
        return f[x][s];
    f[x][s] = 0;
    if (s == 0)
        return f[x][s];
    for (int i = 0; i < s; i++)
    {
        f[x][s] = max(f[x][s], dp(tree[x].ch[0], i) + dp(tree[x].ch[1], s - i - 1) + w[x]);
    }
    f[x][s] = max(f[x][s], dp(tree[x].ch[1], s));
    return f[x][s];
}
int main()
{
    cin >> n >> m;
    int s;
    memset(f, -1, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        cin >> s >> w[i];
        a[s][++a[s][0]] = i;
    }
    buildtree();
    m++;
    cout << dp(0, m) << endl;
}

// Problem1283:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
int n, a[305][305], dis[305][305], t;
void read();
int main()
{
    read();
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n; i++)
        dis[i][i] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i][j])
                dis[i][j] = a[i][j];
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], max(dis[i][k], dis[k][j]));
    for (int i = 1; i <= t; i++)
    {
        int i1, i2;
        cin >> i1 >> i2;
        if (dis[i1][i2] == 0x3f3f3f3f)
            cout << "-1" << endl;
        else
            cout << dis[i1][i2] << endl;
    }
}
void read()
{
    int m;
    cin >> n >> m >> t;
    int x, y, s;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y >> s;
        a[x][y] = s;
    }
}

// Problem1285:
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 6005;
struct edge
{
    int data;
    int ch[2];
    int fa;
} tree[N];
int n, f[N];
int w[N];
bool flag[N];
void buildtree()
{
    int s, e;
    while (cin >> s >> e && s && e)
    {
        if (tree[e].ch[0] == 0)
        {
            tree[e].ch[0] = s;
            tree[s].fa = e;
        }
        else
        {
            int p = tree[e].ch[0];
            while (tree[p].ch[1] != 0)
                p = tree[p].ch[1];
            //p=tree[p].fa;
            tree[p].ch[1] = s;
            tree[s].fa = p;
        }
    }
    for (int i = 1; i <= n; i++)
        tree[i].data = w[i];
}
int dp(int x)
{
    if (f[x] != 0x80808080)
        return f[x];
    if (x == 0)
    {
        f[x] = 0;
        return 0;
    }
    f[x] = tree[x].data;
    flag[x] = 1;
    for (int i = 0; i <= 1; i++)
        if (f[x] <= dp(tree[x].ch[i]))
        {
            f[x] = dp(tree[x].ch[i]);
            flag[x] = 0;
        } /*f[x]=max(f[x],dp(tree[x].ch[i]));*/
    if (f[x] < dp(tree[x].ch[1]) + tree[x].data)
    {
        f[x] = dp(tree[x].ch[1]) + tree[x].data;
        flag[x] = 1;
    }
    if (f[x] <= dp(tree[x].ch[0]) + dp(tree[x].ch[1]))
    {
        f[x] = dp(tree[x].ch[0]) + dp(tree[x].ch[1]);
        flag[x] = 0;
    }
    if (!flag[tree[x].ch[0]])
    {
        if (f[x] < dp(tree[x].ch[0]) + tree[x].data)
        {
            f[x] = dp(tree[x].ch[0]) + tree[x].data;
            flag[x] = 1;
        }
        if (f[x] < dp(tree[x].ch[0]) + dp(tree[x].ch[1]) + tree[x].data)
        {
            f[x] = dp(tree[x].ch[0]) + dp(tree[x].ch[1]) + tree[x].data;
            flag[x] = 1;
        }
    }
    return f[x];
}
void q_graph(int i)
{
    if (i == 0)
        return;
    cout << i << " ";
    q_graph(tree[i].ch[0]);
    q_graph(tree[i].ch[1]);
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    memset(f, 0x80, sizeof(f));
    buildtree();
    int root = 1;
    for (int i = 1; i <= n; i++)
        if (tree[i].fa == 0 && tree[i].ch[0] != 0)
        {
            root = i;
            break;
        }
    //q_graph(root);
    cout << dp(root) << endl;
}

// Problem1290:
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int f[105][65][65];
int cut[105], cnt = 0;
int stk[65], sum[65];
int N;
int get_num(int x)
{
    int cut = 0;
    while (x)
    {
        cut += x & 1;
        x >>= 1;
    }
    return cut;
}
void Init()
{
    for (int S = 0; S <= N; S++)
    {

        if (S & (S >> 1))
            continue;
        if (S & (S >> 2))
            continue;
        //if(S&(S<<1))continue;
        //if(S&(S<<2))continue;
        stk[++cnt] = S;
        sum[cnt] = get_num(S);
    }
}

int main()
{
#ifdef Wild
    freopen("cannon.in", "r", stdin);
    freopen("cannon.out", "w", stdout);
#endif
    int n, m;
    //memset(f,-1,sizeof(f));
    scanf("%d%d", &n, &m);
    char c;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> c;
            if (c == 'H')
            {
                cut[i] |= 1 << (m - j);
            }
        }
    }
    N = (1 << m) - 1;
    Init();
    int t;
    int tmps1, tmps2, tmps3;
    for (int i = 0; i <= cnt; i++)
        if (!(stk[i] & cut[1]))
            f[1][0][i] = sum[i];
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= cnt; j++)
        { //i
            if (stk[j] & cut[i])
                continue;
            for (int l = 0; l <= cnt; l++)
            { //i-1
                if (stk[j] & stk[l])
                    continue;
                for (int S = 0; S <= cnt; S++)
                { //i-2
                    if (stk[j] & stk[S])
                        continue;
                    //if(f[i-1][S][l]==-1)continue;
                    //if(tmps2&l)continue;
                    f[i][l][j] = max(f[i][l][j], f[i - 1][S][l] + sum[j]);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= cnt; i++)
    {
        for (int j = 0; j <= cnt; j++)
        {
            ans = max(ans, f[n][i][j]);
        }
    }
    printf("%d", ans);
}

// Problem1294:
#include <iostream>
#include <queue>
#define LL long long
using namespace std;
LL f(LL a, LL b, LL c, LL x)
{
    return a * x * x + b * x + c;
}
struct data
{
    LL a, b, c;
    bool operator<(const data &s) const
    {
        return f(s.a, s.b, s.c, 500000) < f(a, b, c, 500000);
    }
};
int main()
{
    //freopen("1.txt","r",stdin);
    priority_queue<data> b;
    priority_queue<LL> a;
    vector<LL> c;
    LL n, q;
    cin >> n >> q;
    for (LL i = 1; i <= n; i++)
    {
        data m;
        cin >> m.a >> m.b >> m.c;
        b.push(m);
    }
    data m = b.top();
    //cout<<m.a;
    //while(1);
    for (LL j = 1; j <= q; j++)
        a.push(f(m.a, m.b, m.c, j));
    b.pop();
    for (LL i = 1; i < n; i++)
    {
        data m = b.top();
        for (LL j = 1;; j++)
        {
            LL s = f(m.a, m.b, m.c, j);
            if (s > a.top())
                break;
            a.push(s);
            a.pop();
        }
        b.pop();
    }
    for (LL i = 1; i <= q; i++)
    {
        c.push_back(a.top());
        a.pop();
    }
    for (LL i = q - 1; i >= 0; i--)
    {
        cout << c[i] << " ";
    }
    //while(1);
}

// Problem1299:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int fix = 0, full = 20;
class Trie
{

  public:
    class Node
    {
      public:
        int size;
        Node *ch[2];
        Node()
        {
            ch[0] = ch[1] = NULL;
            size = 0;
        }
#define _size(_) ((_) ? (_)->size : 0)
    } * root;
    Trie()
    {
        root = new Node();
    }
    int size()
    {
        return _size(root);
    }
    void Insert(int x, int add)
    {
        x += fix;
        Node *rt = root;
        rt->size += add;
        for (int i = full; i >= 0; i--)
        {
            bool next = x >> i & 1;
            if (!rt->ch[next])
                rt->ch[next] = new Node;
            rt = rt->ch[next];
            rt->size += add;
        }
    }
    int rank(int x)
    {
        x += fix;
        int res = 0;
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            bool next = x >> i & 1;
            if (next)
                res += _size(rt->ch[0]);
            if (!rt->ch[next])
                break;
            rt = rt->ch[next];
        }
        return res;
    }
    int kth(int k)
    {
        int res = 0;
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            if (k > _size(rt->ch[0]))
            {
                k -= _size(rt->ch[0]);
                res |= 1 << i;
                if (!rt->ch[1])
                    break;
                rt = rt->ch[1];
            }
            else

                rt = rt->ch[0];
        }
        return res - fix;
    }
} root;
int n, m;
struct data
{
    int END, next, v;
} v[2000005];
int first[1000005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int L, R, maxn, Max;
void dfs(int x, int fa, int sum)
{
    if (sum > Max)
    {
        Max = sum;
        maxn = x;
    }
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa)
        {
            dfs(v[i].END, x, sum + v[i].v);
        }
    }
}
int len[1000005];
void dfs1(int x, int fa, int sum)
{
    len[x] = max(len[x], sum);
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa)
        {
            dfs1(v[i].END, x, sum + v[i].v);
        }
    }
}
int main()
{
    memset(first, -1, sizeof(first));
    int Fi, Di;
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d%d", &Fi, &Di);
        add(i, Fi, Di);
        add(Fi, i, Di);
    }
    dfs(1, 0, 0);
    L = maxn;
    dfs(L, 0, 0);
    R = maxn;
    dfs1(L, 0, 0);
    dfs1(R, 0, 0);
    int l = 1, r = 1;
    int ans = 0;
    int t = 0;
    while (r <= n)
    {
        root.Insert(len[r], 1);
        t++;
        while (root.kth(t) - root.kth(1) > m)
        {
            root.Insert(len[l], -1);
            t--;
            l++;
        }
        r++;
        ans = max(ans, t);
    }
    printf("%d\n", ans);
}
// Problem1310:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
int main()
{
    int n;
    cin >> n;
    string a[n + 1];
    string l1("cow"), l2("ow");
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i][0] == 'a' || a[i][0] == 'e' || a[i][0] == 'i' || a[i][0] == 'o' || a[i][0] == 'u')
        {
            a[i] = a[i] + l1;
        }
        else
        {
            char s = a[i][0];
            a[i].erase(0, 1);
            a[i] = a[i] + s + l2;
        }
    }
    for (int i = 1; i <= n; i++)
        cout << a[i] << endl;
    getchar();
    getchar();
}

// Problem1311:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 100000000
#define LL long long
using namespace std;
int f(const int &a, const int &b);
LL s[10000];
int main()
{
    //string n;
    //freopen("kblk.in","r",stdin);
    //freopen("kblk.out","w",stdout);
    char n[12], max[12], min[12];
    while (cin >> n)
    {
        int l = strlen(n);
        sscanf(n, "%lld", &s[0]);
        for (int j = 1; j != 0; j++)
        {
            LL maxn = 0, minn = 0;
            strcpy(max, n);
            strcpy(min, n);
            sort(min, min + strlen(min));
            sort(max, max + strlen(max), f);
            sscanf(max, "%lld", &maxn);
            sscanf(min, "%lld", &minn);
            //for(int i=0;i<strlen(n);i++)
            //            {
            //                maxn+=(max[i]-'0')*pow(10.0,(int)strlen(n)-i);
            //                minn+=(min[i]-'0')*pow(10.0,(int)strlen(n)-i);
            //            }
            s[j] = maxn - minn;
            //cout<<maxn<<"-"<<minn<<"=";
            //cout<<s[j]<<endl;
            for (int i = 0; i < j; i++)
            {
                if (s[j] == s[i])
                {
                    for (int c = i; c < j; c++)
                        cout << s[c] << " ";
                    cout << endl;
                    j = -1;
                    break;
                }
            }
            sprintf(n, "%lld", s[j]);
            while (strlen(n) < l)
                strcat(n, "0");
        }
    }
}
int f(const int &a, const int &b)
{
    return a > b;
}

// Problem1312:
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int a[2005], n, size;
int f[2005][2005];
int Hash[2005];
void Hash_init()
{
    sort(Hash + 1, Hash + n + 1);
    size = unique(Hash + 1, Hash + n + 1) - Hash - 1;
}
int main()
{
    // freopen("grading.in","r",stdin);
    // freopen("grading.out","w",stdout);
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i] = a[i];
    }
    Hash_init();
    int minn = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        minn = 0x3f3f3f3f;
        for (int j = 1; j <= size; j++)
        {
            minn = min(minn, f[i - 1][j]);
            f[i][j] = minn + abs(Hash[j] - a[i]);
        }
    }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= size; i++)
        ans = min(ans, f[n][i]);
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        minn = 0x3f3f3f3f;
        for (int j = 1; j <= size; j++)
        {
            minn = min(minn, f[i - 1][j]);
            f[i][j] = minn + abs(Hash[j] - a[i]);
        }
    }
    printf("%d\n", ans);
}
// Problem1312:
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int a[2005], n, size;
int f[2005][2005];
int Hash[2005];
inline void Hash_init()
{
    sort(Hash + 1, Hash + n + 1);
    size = unique(Hash + 1, Hash + n + 1) - Hash - 1;
}
int main()
{
    // freopen("grading.in","r",stdin);
    // freopen("grading.out","w",stdout);
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i] = a[i];
    }
    Hash_init();
    int minn = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        minn = 0x3f3f3f3f;
        for (int j = 1; j <= size; j++)
        {
            minn = min(minn, f[i - 1][j]);
            f[i][j] = minn + abs(Hash[j] - a[i]);
        }
    }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= size; i++)
        ans = min(ans, f[n][i]);
    // memset(f,0,sizeof(f));
    // for (int i = 1; i <= n; i++)
    // {
    //     minn = 0x3f3f3f3f;
    //     for (int j = 1; j <= size; j++)
    //     {
    //         minn = min(minn, f[i - 1][j]);
    //         f[i][j] = minn +abs(Hash[j] - a[i]);
    //     }
    // }
    printf("%d\n", ans);
}
// Problem1318:
#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    //freopen("cantor.in","r",stdin);
    //freopen("cantor.out","w",stdout);
    int n, s = 0, a;
    bool q = 0;
    cin >> n;
    for (int i = 1;; i++)
    {
        s += i;
        if (s > n)
        {
            s -= i;
            a = i;
            q = 0;
            break;
        }
        else
        {
            if (s == n)
            {
                a = i;
                q = 1;
                break;
            }
        }
    }
    if (q)
    {
        if (a % 2 == 0)
            cout << a << "/"
                 << "1";
        else
            cout << "1"
                 << "/" << a;
    }
    else
    {
        for (int i = 1; i <= a; i++)
        {
            s++;
            if (s == n)
                if (a % 2 == 0)
                    cout << i << "/" << (a + 1 - i);
                else
                    cout << (a + 1 - i) << "/" << i;
        }
    }
    //while(1);
}

// Problem1321:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
struct Data
{
    string name;
    int a, b, c, d, e;
    int s[10];
};
int main()
{
    int n;
    string p;
    cin >> n;
    Data q[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> q[i].name;
    }
    for (int i = 1; i <= n; i++)
    {
        int o, m;
        cin >> p;
        for (int j = 1; j <= n; j++)
        {
            if (p == q[j].name)
            {
                o = j;
                break;
            }
        }
        cin >> q[o].a >> q[o].b;
        q[o].c = q[o].a;
        q[o].d = 0;
        q[o].e = 0;
        for (int i = 1; i <= q[o].b; i++)
        {
            cin >> p;
            for (int j = 1; j <= n; j++)
            {
                if (p == q[j].name)
                {
                    m = j;
                    break;
                }
            }
            q[o].s[i] = m;
        }
    }
    for (int i = 1; i <= n; i++)
    {

        if (q[i].b == 0 || q[i].c <= 0)
            continue;
        int k = q[i].a / q[i].b;
        for (int j = 1; j <= q[i].b; j++)
        {
            q[q[i].s[j]].c += k;
            q[q[i].s[j]].e += k;
        }
        q[i].d += q[i].b * k;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << q[i].name << " " << q[i].e - q[i].d << endl;
    }
    //while(1);
}

// Problem1321:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
struct Data
{
    string name;
    int a, b, c, d, e;
    int s[10];
};
int main()
{
    int n;
    string p;
    cin >> n;
    Data q[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> q[i].name;
    }
    for (int i = 1; i <= n; i++)
    {
        int o, m;
        cin >> p;
        for (int j = 1; j <= n; j++)
        {
            if (p == q[j].name)
            {
                o = j;
                break;
            }
        }
        cin >> q[o].a >> q[o].b;
        q[o].c = q[o].a;
        q[o].d = 0;
        q[o].e = 0;
        for (int i = 1; i <= q[o].b; i++)
        {
            cin >> p;
            for (int j = 1; j <= n; j++)
            {
                if (p == q[j].name)
                {
                    m = j;
                    break;
                }
            }
            q[o].s[i] = m;
        }
    }
    for (int i = 1; i <= n; i++)
    {

        if (q[i].b == 0 || q[i].c <= 0)
            continue;
        int k = q[i].a / q[i].b;
        for (int j = 1; j <= q[i].b; j++)
        {
            q[q[i].s[j]].c += k;
            q[q[i].s[j]].e += k;
        }
        q[i].d += q[i].b * k;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << q[i].name << " " << q[i].e - q[i].d << endl;
    }
    //while(1);
}
// Problem1345:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define LL long long
#define Kruskal 1
//#define Prim 1
using namespace std;
#ifdef Kruskal
struct edge
{
    int STRAT, END, v;
    bool operator<(const edge &a) const
    {
        return v < a.v;
    }
} v[100005];
int father[10005];
int w[10005];
int find(int x);
bool allcheck(int a);
void merge(int a, int b);
#endif
#ifdef Prim
int w[10005];
bool INTREE[10005];
int minn[10005];
int first[10005], p;
// struct edge{
// int STRAT,END,v;
// int next;
// }v[200005];
int v[10005][10005];
#endif
//int add(int a,int b,int c);
int main()
{
    int n, m;
    cin >> n >> m;
    int a, b, c, u;
    LL sum = 0;
    int p = 1;
    int minw = 0x7fffffff;
    //memset(first,-1,sizeof(first));
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
        if (w[i] < minw)
        {
            u = i;
        }
    }
    while (m--)
    {
        cin >> a >> b >> c;
        //add(a,b,c+w[b]);
        //add(b,a,c+w[a]);
        //v[a][b]=2*c+w[b]+w[a];
        //v[b][a]=2*c+w[b]+w[a];
        v[p].STRAT = a;
        v[p].END = b;
        v[p++].v = 2 * c + w[b] + w[a];
    }
#ifdef Prim
    memset(minn, 0x7f, sizeof(minn));
    minn[u] = 0;
    for (int i = 1; i <= n; i++)
    {
        int k = 0;
        for (int j = 1; j <= n; j++)
        {
            if (!INTREE[j] && (minn[j] < minn[k]))
            {
                k = j;
            }
        }
        INTREE[k] = 1;
        sum += minn[k];
        //sum+=min(minn[k],w[k]);
        for (int j = 1; j <= n; j++)
        {
            if (!INTREE[j] && (v[k][j] < minn[j]))
            {
                minn[j] = v[k][j];
            }
        }
    }
#endif
#ifdef Kruskal
    //sum+=*min_element(w+1,w+n+1);
    for (int i = 1; i <= n; i++)
        father[i] = i;
    int k = 0;
    sort(v + 1, v + p);
    for (int i = 1; i <= n; i++)
        father[i] = i;
    for (int i = 1; i < p; i++)
    {
        int x = v[i].STRAT, y = v[i].END;
        //if(allcheck(n))break;
        if (find(x) != find(y))
        {
            father[find(y)] = find(x);
            sum += v[i].v;
            k++;
        }
        if (k == n - 1)
            break;
    }
#endif
    cout << sum + *min_element(w + 1, w + n + 1) << endl;
}
#ifdef Kruskal
int find(int x)
{
    if (x != father[x])
        father[x] = find(father[x]);
    return father[x];
}
bool allcheck(int a)
{
    int t = 0;
    for (int i = 1; i <= a; i++)
    {
        if (father[i] == i)
            t++;
        if (t > 1)
            return 0;
    }
    //if(t>1) return 0;
    if (t == 1)
        return 1;
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
        father[y] = x;
}
#endif
// int add(int a,int b,int c){
// v[p].STRAT=a;
// v[p].END=b;
// v[p].v=c;
// v[p].next=first[a];
// first[a]=p++;
// }

// Problem1362:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
struct node
{
    int v;
    int s, e, next;
} v[15000];
LL dis[3005];
int first[3005], n, p, d[3005];
int x, y;
inline void add(int a, int b, int z);
inline void spfa(int lin);
//inline void floyd();
inline void read();
int main()
{
    read();
    //cout<<v[1].v;
    //while(1);
    //floyd();
    spfa(x);
    cout << dis[y] << endl;
    getchar();
    getchar();
    //while(1);
}
inline void read()
{
    p = 1;
    memset(first, -1, sizeof(first));
    int m, a, b, z;
    cin >> n >> m >> x >> y;
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b >> z;
        add(a, b, z);
        add(b, a, z);
    }
    //cin>>x>>y;
}
inline void add(int a, int b, int z)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = z;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int lin)
{
    memset(dis, 0x3f, sizeof(dis));
    queue<int> p;
    bool flag[3005] = {0};
    dis[lin] = 0;
    p.push(lin);
    flag[lin] = 1;
    while (!p.empty())
    {
        int k = p.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] > dis[k] + v[i].v)
            {
                dis[v[i].e] = dis[k] + v[i].v;
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    p.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        p.pop();
    }
}

// Problem1371:
#include <iostream>
#include <cstring>
#include <cstdio>
#define lowbit(x) ((x) & (-x))
using namespace std;
int n, m;
int c[105][305][305];
int a[305][305];
void update(int k, int x, int y, int num)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            c[k][i][j] += num;
}
int sum(int k, int x, int y)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            sum += c[k][i][j];
    return sum;
}
int sum(int k, int x1, int y1, int x2, int y2) { return sum(k, x2, y2) + sum(k, x1 - 1, y1 - 1) - sum(k, x1 - 1, y2) - sum(k, x2, y1 - 1); }
int main()
{
    //freopen("mima.in","r",stdin);
    //freopen("mima.out","w",stdout);
    int Q;
    int x1, y1, A, x2, y2;
    int U;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
            update(a[i][j], i, j, 1);
        }
    }
    scanf("%d", &Q);
    while (Q--)
    {
        scanf("%d", &U);
        if (U == 1)
        {
            scanf("%d%d%d", &x1, &y1, &A);
            update(a[x1][y1], x1, y1, -1);
            update(A, x1, y1, 1);
            a[x1][y1] = A;
            continue;
        }
        if (U == 2)
        {
            scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &A);
            printf("%d\n", sum(A, x1, y1, x2, y2));
        }
    }
}

// Problem1375:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
class Treap1
{
  public:
    class Node
    {
      public:
        Node *ch[2];
        int v, key, s, Min, Max, C;
        Node(int x)
        {
            Min = x, Max = x, C = 1000000000;
            v = x, key = rand(), s = 1;
            ch[0] = ch[1] = NULL;
        }
#define Min(_) ((_) ? (_)->Min : 1000000000)
#define Max(_) ((_) ? (_)->Max : -1000000000)
#define C(_) ((_) ? (_)->C : 1000000000)
#define size(_) ((_) ? (_)->s : 0)
        void Pushup()
        {
            s = size(ch[0]) + size(ch[1]) + 1;
            Min = min(Min(ch[0]), v);
            Max = max(Max(ch[1]), v);
            C = min(C(ch[0]), C(ch[1]));
            C = min(C, min(Min(ch[1]) - v, v - Max(ch[0])));
        }
    } * root;
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
        if (A->key > B->key)
        {
            A->ch[1] = Merge(A->ch[1], B);
            A->Pushup();
            return A;
        }
        else
        {
            B->ch[0] = Merge(A, B->ch[0]);
            B->Pushup();
            return B;
        }
    }
    typedef pair<Node *, Node *> DNode;
    DNode Split(Node *rt, int k)
    {
        if (!rt)
            return DNode(NULL, NULL);
        DNode o;
        if (k <= size(rt->ch[0]))
        {
            o = Split(rt->ch[0], k);
            rt->ch[0] = o.second;
            rt->Pushup();
            o.second = rt;
        }
        else
        {
            o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
            rt->ch[1] = o.first;
            rt->Pushup();
            o.first = rt;
        }
        return o;
    }
    int Rank(Node *rt, int x)
    {
        if (!rt)
            return 0;
        return x <= rt->v ? Rank(rt->ch[0], x) : Rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
    }
    void Insert(int x)
    {
        int k = Rank(root, x);
        DNode y = Split(root, k);
        Node *n = new Node(x);
        root = Merge(y.first, Merge(n, y.second));
    }
} Rt1;
struct BIT
{
    long long sum[50005];
#define lowbit(_) ((_) & (-_))
    void add(int x, int c)
    {
        for (int i = x; i <= 50000; i += lowbit(i))
            sum[i] += c;
    }
    long long Query(int x)
    {
        long long ans = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ans += sum[i];
        return ans;
    }
} bit;
int Abs(int x)
{
    return x >= 0 ? x : -x;
}
class Treap2
{
  public:
    class Node
    {
      public:
        Node *ch[2];
        int v, key, s, l, r, C;
        Node(int x)
        {
            l = x, r = x, C = 1000000000;
            v = x, key = rand(), s = 1;
            ch[0] = ch[1] = NULL;
        }
#define l(_) ((_) ? (_)->l : 1000000000)
#define r(_) ((_) ? (_)->r : -1000000000)
        //#define C(_) ((_) ? (_)->C : 0x7fffffff)
        //#define size(_) ((_) ? (_)->s : 0)
        void Pushup()
        {
            s = size(ch[0]) + size(ch[1]) + 1;
            l = ch[0] ? ch[0]->l : v;
            r = ch[1] ? ch[1]->r : v;
            C = min(C(ch[0]), C(ch[1]));
            C = min(C, min(Abs(l(ch[1]) - v), Abs(v - r(ch[0]))));
        }
    } * root;
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
        if (A->key > B->key)
        {
            A->ch[1] = Merge(A->ch[1], B);
            A->Pushup();
            return A;
        }
        else
        {
            B->ch[0] = Merge(A, B->ch[0]);
            B->Pushup();
            return B;
        }
    }
    typedef pair<Node *, Node *> DNode;
    DNode Split(Node *rt, int k)
    {
        if (!rt)
            return DNode(NULL, NULL);
        DNode o;
        if (k <= size(rt->ch[0]))
        {
            o = Split(rt->ch[0], k);
            rt->ch[0] = o.second;
            rt->Pushup();
            o.second = rt;
        }
        else
        {
            o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
            rt->ch[1] = o.first;
            rt->Pushup();
            o.first = rt;
        }
        return o;
    }
    void Insert(int k, int x)
    {
        DNode y = Split(root, k);
        Node *n = new Node(x);
        root = Merge(y.first, Merge(n, y.second));
    }
} Rt2;
int main()
{
    //freopen("love.in","r",stdin);
    //freopen("love.out","w",stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    int a;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        bit.add(i, 1);
        Rt1.Insert(a);
        Rt2.Insert(i, a);
    }
    char s[20];
    int x, k;
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", s);
        if (s[0] == 'I')
        {
            scanf("%d%d", &x, &a);
            k = bit.Query(x);
            Rt1.Insert(a);
            Rt2.Insert(k, a);
            bit.add(x, 1);
        }
        else
        {
            if (s[5] == 'A')
            {
                printf("%d\n", C(Rt2.root));
            }
            else
            {
                printf("%d\n", C(Rt1.root));
            }
        }
    }
}

// Problem1385:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int START, END;
    int SPEED;
    bool operator<(const edge &a) const
    {
        return SPEED < a.SPEED;
    }
} v[10005];
int father[1005];
bool allcheck(int a);
int find(int a)
{
    if (a != father[a])
        father[a] = find(father[a]);
    return father[a];
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
        father[y] = x;
}
bool check(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
        return 0;
    return 1;
}
int main()
{
    int n, m, begin, end, speed;
    while (cin >> n >> m)
    {
        memset(v, 0, sizeof(v));
        memset(father, 0, sizeof(father));
        for (int i = 1; i <= m; i++)
        {
            cin >> begin >> end >> speed;
            v[i].SPEED = speed;
            v[i].START = begin;
            v[i].END = end;
            v[i + m].SPEED = speed;
            v[i + m].START = end;
            v[i + m].END = begin;
        }
        sort(v + 1, v + 2 * m + 1);
        v[2 * m + 1].SPEED = 0x7fffffff;
        int Q;
        //cin>>Q;
        int Start, End;
        //while(Q--){
        //  cin>>Start>>End;
        int minn = 0x3fffffff;
        for (int i = 1; i <= 2 * m; i++)
        {
            int k = 2 * m + 1;
            for (int j = 1; j <= n; j++)
                father[j] = j;
            merge(v[i].START, v[i].END);
            for (int j = i; j <= 2 * m; j++)
            {
                merge(v[j].START, v[j].END);
                if (allcheck(n))
                {
                    k = j;
                    break;
                }
            }
            minn = min(minn, abs(v[k].SPEED - v[i].SPEED));
        }
        if (minn >= 0x3fffffff)
            cout << "-1" << endl;
        else
            cout << minn << endl;
        //}
    }
}
bool allcheck(int a)
{
    int t = 0;
    for (int i = 1; i <= a; i++)
    {
        if (father[i] == i)
            t++;
        if (t > 1)
            return 0;
    }
    //if(t>1) return 0;
    if (t == 1)
        return 1;
}

// Problem1399:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
int a[30];
int f[2005][2005];
int main()
{
    int n, m, add, del;
    char c;
    string s;
    cin >> n >> m;
    cin >> s;
    for (int i = 1; i <= n; i++)
    {
        cin >> c >> add >> del;
        a[c - 'a'] = min(add, del);
    }
    for (int l = 2; l <= m; l++)
    {
        for (int i = 0; i <= m - l + 1; i++)
        {
            f[i][i + l - 1] = min(f[i + 1][i + l - 1] + a[s[i] - 'a'], f[i][i + l - 2] + a[s[i + l - 1] - 'a']);
            if (s[i] == s[i + l - 1])
                f[i][i + l - 1] = min(f[i][i + l - 1], f[i + 1][i + l - 2]);
        }
    }
    cout << f[0][m - 1] << endl;
}

// Problem1412:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
int max(int a, int b, int c)
{
    int s[3] = {a, b, c};
    return *max_element(s, s + 3);
}
struct data
{
    int i, j, v;
    data()
    {
        v = -1;
        i = -1;
    }
} v[105][105];
int a[105][105];
int f[105][105];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
        }
    }
    memset(f, 0x80, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= m; j++)
        {
            if (i == 1)
                f[i][j] = max(f[i][j], a[i][j], f[i][j - 1]);
            else
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + a[i][j], f[i][j - 1]);
        }
    }
    int maxl = 0x80000000, k = 0;
    for (int i = 1; i <= m; i++)
    {
        if (f[n][i] >= maxl)
        {
            maxl = f[n][i];
            k = i;
        }
    }
    stack<int> q;
    cout << maxl << endl;
    for (int i = n, j = k; i >= 1, j >= 1; j--)
    {
        if (f[i][j] != f[i][j - 1])
        {
            q.push(j);
            i--;
        }
    }
    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    //while(1);
}

// Problem1419:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define LL long long
using namespace std;
int a[10005];
int f[10005];
int g[10005];
vector<int> v, ans, ansn;
bool zhidx(vector<int> a, vector<int> b);
void dfs(int n);
int main()
{
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int maxn = 0, s = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (a[i] >= a[j] && f[i] < f[j] + 1)
            {
                f[i] = f[j] + 1;
                g[i] = j;
            }
        }
        if (f[i] > maxn)
        {
            maxn = f[i];
            ans.clear();
            ans.push_back(i);
        }
        else if (f[i] == maxn)
        {
            ans.push_back(i);
        }
    }
    cout << maxn << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        dfs(ans[i]);
        if (zhidx(ansn, v))
        {
            ansn = v;
        }
        v.clear();
    }
    for (int i = 0; i < ansn.size(); i++)
    {
        cout << ansn[i] << " ";
    }
    //while(1);
}
void dfs(int n)
{
    if (g[n] != 0)
        dfs(g[n]);
    v.push_back(a[n]);
}
bool zhidx(vector<int> a, vector<int> b)
{
    int i;
    for (i = 0; i < a.size() && i < b.size(); i++)
    {
        if (a[i] < b[i])
            return 1;
        else if (b[i] < a[i])
            return 0;
    }
    return (i == a.size() && i < b.size());
}

// Problem1420:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
using namespace std;
const int N = 100005;
int sum[N << 2];
void Pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        scanf("%d", &sum[rt]);
        return;
    }
    int m = (l + r) >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
void update(int p, int add, int l, int r, int rt)
{
    if (l == r)
    {
        sum[rt] += add;
        return;
    }
    int m = (l + r) >> 1;
    if (p <= m)
        update(p, add, lch);
    else
        update(p, add, rch);
    Pushup(rt);
}
int query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return sum[rt];
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m)
        ret += query(L, R, lch);
    if (R > m)
        ret += query(L, R, rch);
    return ret;
}
int main()
{
    //freopen("shulie.in","r",stdin);
    //freopen("shulie.out","w",stdout);
    int n, m, a, b;
    scanf("%d", &n);
    if (n == 0)
        return 0;
    buildtree(1, n, 1);
    scanf("%d", &m);
    char s[10];
    while (m--)
    {
        scanf("%s", s);
        scanf("%d%d", &a, &b);
        if (s[0] == 'S')
            printf("%d\n", query(a, b, 1, n, 1));
        else
            update(a, b, 1, n, 1);
    }
}

// Problem1422:
#include <iostream>
#include <cstring>
#include <cstdio>
#define LL long long
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
using namespace std;
const int N = 100005;
int sum[N << 2];
int add[N << 2];
void Pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void Pushdown(int rt, int m)
{
    if (add[rt])
    {
        add[rt << 1] += add[rt];
        add[rt << 1 | 1] += add[rt];
        sum[rt << 1] += add[rt] * (m - (m >> 1));
        sum[rt << 1 | 1] += add[rt] * (m >> 1);
        add[rt] = 0;
    }
}
void buildtree(int l, int r, int rt)
{
    add[rt] = 0;
    if (l == r)
    {
        scanf("%d", &sum[rt]);
        return;
    }
    int m = (l + r) >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        add[rt] += c;
        sum[rt] += c * (r - l + 1);
        return;
    }
    Pushdown(rt, r - l + 1);
    int m = (r + l) >> 1;
    if (L <= m)
        update(L, R, c, lch);
    if (R > m)
        update(L, R, c, rch);
    Pushup(rt);
}
int query(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        return sum[rt];
    }
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m)
        ret += query(L, R, lch);
    if (R > m)
        ret += query(L, R, rch);
    return ret;
}
int main()
{
    //freopen("shulieb.in","r",stdin);
    //freopen("shulieb.out","w",stdout);
    int n, a, b, c;
    scanf("%d", &n);
    buildtree(1, n, 1);
    int m;
    char s[6];
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", s);
        if (s[0] == 'Q')
        {
            scanf("%d", &a);
            printf("%d\n", query(a, a, 1, n, 1));
        }
        else
        {
            scanf("%d%d%d", &a, &b, &c);
            update(a, b, c, 1, n, 1);
        }
    }
}

// Problem1423:
#include <iostream>
#include <cstring>
#include <cstdio>
#define LL long long
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
using namespace std;
const int N = 100005;
LL sum[N << 2];
LL add[N << 2];
void Pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void Pushdown(int rt, int m)
{
    if (add[rt])
    {
        add[rt << 1] += add[rt];
        add[rt << 1 | 1] += add[rt];
        sum[rt << 1] += add[rt] * (m - (m >> 1));
        sum[rt << 1 | 1] += add[rt] * (m >> 1);
        add[rt] = 0;
    }
}
void buildtree(int l, int r, int rt)
{
    add[rt] = 0;
    if (l == r)
    {
        scanf("%lld", &sum[rt]);
        return;
    }
    int m = (l + r) >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        add[rt] += c;
        sum[rt] += (LL)c * (r - l + 1);
        return;
    }
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m)
        update(L, R, c, lch);
    if (m < R)
        update(L, R, c, rch);
    Pushup(rt);
}
LL query(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        return sum[rt];
    }
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    LL ret = 0;
    if (L <= m)
        ret += query(L, R, lch);
    if (m < R)
        ret += query(L, R, rch);
    return ret;
}
int main()
{
    //freopen("shuliec.in","r",stdin);
    //freopen("shuliec.out","w",stdout);
    int n;
    scanf("%d", &n);
    buildtree(1, n, 1);
    int m;
    scanf("%d", &m);
    char s[5];
    int a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", s);
        if (s[0] == 'S')
        {
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(a, b, 1, n, 1));
        }
        else
        {
            scanf("%d%d%d", &a, &b, &c);
            update(a, b, c, 1, n, 1);
        }
    }
    //while(1);
}
// Problem1424:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[1005][1005];
int f[1005][1005];
int maxl = 0;
int min(int a, int b, int c)
{
    int s[3] = {a, b, c};
    return *min_element(s, s + 3);
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    for (int i = n; i >= 1; i--)
    {
        for (int j = m; j >= 1; j--)
        {
            if (a[i][j] == 1)
            {
                f[i][j] = min(f[i + 1][j + 1], f[i][j + 1], f[i + 1][j]) + 1;
                maxl = max(maxl, f[i][j]);
            }
        }
    }
    // cout<<endl;
    // for(int i=1;i<=n;i++)
    // {
    // for(int j=1;j<=m;j++)
    // cout<<f[i][j]<<" ";
    // cout<<endl;
    // }
    cout << maxl << endl;
    //while(1);
}

// Problem1434:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 100;
struct Matrix
{
    int x, y;
    int a[MAXN][MAXN];
    Matrix()
    {
        memset(a, 0, sizeof(a));
        x = 0;
        y = 0;
    }
    void Init(int b[MAXN][MAXN], int m, int n)
    {
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = b[i][j];
        x = m, y = n;
    }

    Matrix operator*(const Matrix &h)
    {
        //try
        //              {
        //                   if(y!=b.x) throw 1;
        //              }
        //              catch(int i)
        //              {
        //                   exit(0);
        //              }
        //cout<<"1";
        //while(1);
        Matrix c;
        //int c[x+1][h.y+1];
        c.x = x, c.y = h.y;
        for (int i = 1; i <= c.x; i++)
            for (int j = 1; j <= c.y; j++)
            {
                for (int k = 1; k <= y; k++)
                    c.a[i][j] += (a[i][k] * h.a[k][j]) % 7;
                c.a[i][j] %= 7;
            }
        return c;
    }
};
ostream &operator<<(ostream &out, const Matrix &b)
{
    for (int i = 1; i <= b.x; i++)
    {
        for (int j = 1; j <= b.y; j++)
            cout << b.a[i][j] << " ";
        cout << '\n';
    }
    return out;
}
int f(int p, int r, int l)
{
    int c[MAXN][MAXN];
    int d[MAXN][MAXN];
    Matrix a, b, ans;
    c[1][1] = r;
    c[1][2] = l;
    c[2][1] = 1;
    c[2][2] = 0;
    d[1][1] = 1;
    d[2][1] = 1;
    a.Init(c, 2, 2);
    b.Init(d, 2, 1);
    //cout<<"11 ";
    ans.x = 2;
    ans.y = 2;
    ans.a[1][1] = 1;
    ans.a[2][2] = 1;
    p -= 2;
    while (p)
    {
        if (p & 1)
            ans = ans * a;
        p = p >> 1;
        a = a * a;
    }
    //cout<<ans<<endl;
    a = ans * b;
    return a.a[1][1];
}
int main()
{
    int b, a, p;
    cin >> a >> b >> p;
    cout << f(p, a, b) << endl;

    //while(1);
}

// Problem1439:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1505;
int n, f[N][4], a[N][N], w[N];
bool isnotroot[N];
void Init()
{
    cin >> n;
    int m, k, l;
    for (int i = 1; i <= n; i++)
    {
        cin >> l;
        cin >> w[l] >> a[l][0];
        for (int i = 1; i <= a[l][0]; i++)
        {
            cin >> k;
            a[l][i] = k;
            isnotroot[k] = 1;
        }
    }
}
int findroot()
{
    for (int i = 1; i <= n; i++)
        if (!isnotroot[i])
            return i;
}
int dp(int x, int s)
{
    if (f[x][s] != 0x80808080)
        return f[x][s];
    if (x == 0)
    {
        f[x][s] = 0;
        return 0;
    }
    if (s == 1)
    {
        f[x][1] = 0;
        for (int i = 1; i <= a[x][0]; i++)
        {
            f[x][1] += dp(a[x][i], 2);
        }
        return f[x][1];
    }
    if (s == 2)
    {
        f[x][2] = 0;
        //if(a[x][0]==0)return 0;
        int q = 0x7ffff;
        for (int i = 1; i <= a[x][0]; i++)
        {
            f[x][2] += min(dp(a[x][i], 2), dp(a[x][i], 3));
            q = min(q, dp(a[x][i], 3) - dp(a[x][i], 2));
        }
        if (q > 0)
            f[x][2] += q;
        return f[x][2];
    }
    if (s == 3)
    {
        f[x][3] = 0;
        for (int i = 1; i <= a[x][0]; i++)
        {
            f[x][3] += min(dp(a[x][i], 1), min(dp(a[x][i], 2), dp(a[x][i], 3)));
        }
        f[x][3] += w[x];
        return f[x][3];
    }
}
int main()
{
    memset(f, 0x80, sizeof(f));
    Init();
    int root = findroot();
    cout << min(dp(root, 2), dp(root, 3)) << endl;
}

// Problem1440:
#include <iostream>
#include <cstring>
#include <cstdio>
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
using namespace std;
const int N = 1000005;
int maxn[N << 2];
void Pushup(int rt)
{
    maxn[rt] = max(maxn[rt << 1], maxn[rt << 1 | 1]);
}
void buildtree(int l, int r, int rt)
{
    if (r == l)
    {
        scanf("%d", &maxn[rt]);
        return;
    }
    int m = (r + l) >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
int max(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return maxn[rt];
    int m = (r + l) >> 1;
    int ret = 0;
    if (L <= m)
        ret = max(ret, max(L, R, lch));
    if (R > m)
        ret = max(ret, max(L, R, rch));
    return ret;
}
int main()
{
    //freopen("climb.in","r",stdin);
    //freopen("climb.out","w",stdout);
    int n;
    //cin>>n;
    scanf("%d", &n);
    buildtree(0, n, 1);
    int m;
    int a, b;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        printf("%d\n", max(a, b, 1, n, 1));
    }
}

// Problem1458:
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#define LL long long
using namespace std;
int max(int a, int b) { return a > b ? a : b; }
struct number
{
    vector<LL> so;
    number() { ; }
    number(const int a) { *this = a; }
    number operator=(const int &a)
    {
        LL y = a / 1000000000;
        LL s = a % 1000000000;
        if (y != 0)
            so.push_back(y);
        so.push_back(s);
        return *this;
    }
    number operator+(const number &b)
    {
        number a = b;
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        int y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 1000000000;
            s = s % 1000000000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator+(const int &b)
    {
        number a;
        int y = b / 1000000000;
        int s = b % 1000000000;
        a.so.push_back(s);
        a.so.push_back(y);
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 1000000000;
            s = s % 1000000000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator+=(const number &a)
    {
        *this = *this + a;
        return *this;
    }
    number operator+=(const int &a)
    {
        *this = *this + a;
        return *this;
    }
    number operator*(const int &a)
    {
        number b = a;
        return *this * b;
    }
    number operator*=(const int &a)
    {
        *this = *this * a;
        return *this;
    }
    number operator*(const number &a)
    {
        number c;
        for (int i = 0; i < a.so.size() + so.size() + 1; i++)
            c.so.push_back(0);
        for (int i = 0; i < so.size(); i++)
        {
            int y = 0;
            for (int j = 0; j < a.so.size(); j++)
            {
                c.so[i + j] += so[i] * a.so[j] + y;
                y = c.so[i + j] / 1000000000;
                c.so[i + j] %= 1000000000;
            }
            c.so[i + a.so.size()] = y;
        }
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator*=(const number &a)
    {
        *this = *this * a;
        return *this;
    }
    bool operator>(const number &a) const
    {
        if (so.size() > a.so.size())
            return 1;
        if (so.size() < a.so.size())
            return 0;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 0;
            }
            if (so[i] > a.so[i])
            {
                return 1;
            }
        }
        return 0;
    }
    bool operator<(const number &a) const
    {
        if (so.size() > a.so.size())
            return 0;
        if (so.size() < a.so.size())
            return 1;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 1;
            }
            if (so[i] > a.so[i])
            {
                return 0;
            }
        }
        return 0;
    }
    bool operator==(const number &a) const { return (!(a < *this)) && (!(a > *this)); }
    bool operator>=(const number &a) const { return !(a > *this); }
    bool operator<=(const number &a) const { return !(a < *this); }
    bool operator!=(const number &a) const { return (a > *this) || (a < *this); }
};
void read(number &a)
{
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 1000000000)
        {
            a.so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || a.so.size() == 0)
    {
        a.so.push_back(sum);
    }
}
void print(number a)
{
    //if(fu) printf("-");
    printf("%d", a.so[a.so.size() - 1]);
    for (int i = a.so.size() - 2; i >= 0; i--)
        printf("%09d", a.so[i]);
    printf("\n");
}
int main()
{
    //freopen("best.in","r",stdin);
    //freopen("best.out","w",stdout);
    vector<int> s;
    number a, b;
    //print(a);
    int n;
    cin >> n;
    if (n == 1 || n == 2)
        cout << "0";
    if (n == 3)
    {
        cout << 2;
        return 0;
    }
    int i = 2;
    while (1)
    {
        s.push_back(i);
        n -= i;
        i++;
        if (n < i)
            break;
    }
    i = s.size() - 1;
    while (n--)
    {
        s[i]++;
        i--;
        if (i == -1)
            i = s.size() - 1;
    }
    i = 0;
    //cout<<s[i]<<endl;
    a = s[i];
    i++;
    //print(a);
    while (i < s.size())
    {
        a *= s[i++];
    }
    print(a);
    //while(1);
}

// Problem1467:
#include <iostream>
#include <cstdio>
#include <queue>
namespace WildRage
{
struct queue
{
    std::deque<int> queue;
    void push(unsigned long long *f, unsigned long long *sum, int i)
    {
        while (!queue.empty() && f[queue.back()] - sum[queue.back()] <= f[i] - sum[i])
            queue.pop_back();
        queue.push_back(i);
    }
    void cut(int i)
    {
        while (!queue.empty() && i > queue.front())
            queue.pop_front();
    }
    int front()
    {
        //if(queue.empty())return 0;
        return queue.front();
    }
    bool empty()
    {
        return queue.empty();
    }
};
}
using WildRage::queue;
unsigned long long sum[100005];
unsigned long long f[100005];
int main()
{
    //freopen("mowlawn.in","r",stdin);
    //freopen("mowlawn.out","w",stdout);
    queue Q;
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> sum[i];
        sum[i] += sum[i - 1];
    }
    sum[n + 1] = sum[n];
    for (int i = 1; i <= n + 1; i++)
    {
        Q.cut(i - k - 1);
        if (!Q.empty())
            f[i] = f[Q.front()] + sum[i - 1] - sum[Q.front()];
        if (i <= k + 1)
            f[i] = sum[i - 1];
        //std::cout<<i<<":"<<f[i]<<std::endl;
        Q.push(f, sum, i);
    }
    //Q.cut(n-k);
    //f[n+1]=Q.front()+sum[i-1]-
    std::cout << f[n + 1];
    //while(1);
}
// Problem1470:/******************************
[HAOI2010] è½¯ä»¶å®‰è£… design by WildRage
        ******************************* /
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
    using namespace std;
int n, m;
struct node
{
    int v, w;
    int ch[2];
    node()
    {
        ch[0] = ch[1] = -1;
    }
} v[105];
int use[105], cost[105], W[105], USE[105];
struct Edge
{
    int END, next;
} edge[105], tree[105];
int first[105], firsttree[105], p = 1, ptree = 1;
void add(int a, int b, int c)
{
    if (c == 0)
    {
        edge[p].END = b;
        edge[p].next = first[a];
        first[a] = p++;
    }
    else
    {
        tree[ptree].END = b;
        tree[ptree].next = firsttree[a];
        firsttree[a] = ptree++;
    }
}
void buildtree(int rt)
{
    v[rt].w = W[rt];
    v[rt].v = USE[rt];
    for (int i = firsttree[rt]; i != -1; i = tree[i].next)
    {
        if (v[rt].ch[0] == -1)
        {
            v[rt].ch[0] = tree[i].END;
            buildtree(tree[i].END);
        }
        else
        {
            int d = v[rt].ch[0];
            while (v[d].ch[1] != -1)
            {
                d = v[d].ch[1];
            }
            v[d].ch[1] = tree[i].END;
            buildtree(tree[i].END);
        }
    }
}
int low[105], dfsn[105], Index;
bool flag[105];
int T;
int belong[105];
stack<int> st;
void tarjan(int rt)
{
    low[rt] = dfsn[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    for (int i = first[rt]; i != -1; i = edge[i].next)
    {
        if (!dfsn[edge[i].END])
        {
            tarjan(edge[i].END);
            low[rt] = min(low[rt], low[edge[i].END]);
        }
        else if (flag[edge[i].END])
            low[rt] = min(low[rt], dfsn[edge[i].END]);
    }
    if (dfsn[rt] == low[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            flag[v] = 0;
            belong[v] = T;
            W[T] += cost[v];
            USE[T] += use[v];
        } while (dfsn[v] != low[v]);
    }
}
int father[105];
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
void read()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &cost[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &use[i]);
    int fa;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &fa);
        add(fa, i, 0);
    }
    for (int i = 0; i <= n; i++)
        if (!dfsn[i])
            tarjan(i);
    for (int i = 0; i <= n; i++)
        father[i] = i;
    bool root[105] = {0};
    for (int j = 0; j <= n; j++)
    {
        for (int i = first[j]; i != -1; i = edge[i].next)
        {
            if (find(belong[j]) != find(belong[edge[i].END]))
            {
                add(belong[j], belong[edge[i].END], 1);
                root[belong[edge[i].END]] = 1;
                father[belong[edge[i].END]] = belong[j];
            }
        }
    }
    for (int i = 1; i <= T; i++)
        if (!root[i])
            add(0, i, 1);
    buildtree(0);
}
int f[105][505];
int dp(int rt, int w)
{
    if (rt == -1)
        return 0;
    if (f[rt][w] != -1)
        return f[rt][w];
    f[rt][w] = 0;
    if (w == 0)
        return f[rt][w];
    for (int i = 0; i <= w - v[rt].w; i++)
    {
        f[rt][w] = max(f[rt][w], dp(v[rt].ch[0], i) + dp(v[rt].ch[1], w - i - v[rt].w) + v[rt].v);
    }
    f[rt][w] = max(f[rt][w], dp(v[rt].ch[1], w));
    return f[rt][w];
}
void dfs(int rt)
{
    if (rt != -1)
    {
        cout << rt << " {W:" << v[rt].w << " V:" << v[rt].v << "} " << endl;
        dfs(v[rt].ch[0]);
        dfs(v[rt].ch[1]);
    }
}
int main()
{
    //freopen("install.in","r",stdin);
    //freopen("install.out","w",stdout);
    memset(first, -1, sizeof(first));
    memset(firsttree, -1, sizeof(firsttree));
    read();
    //dfs(belong[0]);
    //	for(int i=0;i<=n;i++)cout<<i<<":"<<belong[i]<<endl;
    memset(f, -1, sizeof(f));
    printf("%d\n", dp(0, m));
}
// Problem1474:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int mod = 110100;
const int MAXN = 11;
struct Matrix
{
    int x, y;
    int a[MAXN][MAXN];
    Matrix()
    {
        memset(a, 0, sizeof(a));
        x = 0;
        y = 0;
    }
    void Init(int b[MAXN][MAXN], int m, int n)
    {
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = b[i][j];
        x = m, y = n;
    }

    Matrix operator*(const Matrix &h)
    {
        Matrix c;
        //int c[x+1][h.y+1];
        c.x = x, c.y = h.y;
        for (int i = 1; i <= c.x; i++)
            for (int j = 1; j <= c.y; j++)
            {
                for (int k = 1; k <= y; k++)
                    c.a[i][j] += (a[i][k] * h.a[k][j]) % mod;
                c.a[i][j] %= mod;
            }
        return c;
    }
};
ostream &operator<<(ostream &out, const Matrix &b)
{
    for (int i = 1; i <= b.x; i++)
    {
        for (int j = 1; j <= b.y; j++)
            cout << b.a[i][j] << " ";
        cout << '\n';
    }
    return out;
}
int c[MAXN][MAXN];
int d[MAXN][MAXN];
Matrix a, b, ans, u, o, an;
//cout<<"11 ";

int f(int p)
{
    u = a;
    o = b;
    an = ans;
    p--;
    while (p)
    {
        if (p & 1)
            an = an * u;
        p = p >> 1;
        u = u * u;
    }
    //cout<<ans<<endl;
    u = an * o;
    return u.a[1][1] % mod;
}
int main()
{
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    c[1][1] = 1;
    c[1][2] = 1;
    c[2][1] = 1;
    c[2][2] = 0;
    d[1][1] = 2;
    d[2][1] = 1;
    ans.x = 2;
    ans.y = 2;
    ans.a[1][1] = 1;
    ans.a[2][2] = 1;
    a.Init(c, 2, 2);
    b.Init(d, 2, 1);
    int p, t;
    scanf("%d%d", &t, &mod);
    while (t--)
    {
        scanf("%d", &p);
        //return 0;
        printf("%d\n", f(p));
    }
    //cout<<clock();
    //while(1);
}

// Problem1488:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 20005;
int f[1 << 21][22];
struct edge
{
    int END, v, next;
} v[400005];
int head[N];
int first[N], p = 1;
int w[22][22];
void addedge(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
int dis[N];
void spfa(int x)
{
    memset(dis, 0x3f, sizeof(dis));
    queue<int> Q;
    int flag[N] = {0};
    Q.push(x);
    flag[x] = 1;
    dis[x] = 0;
    while (!Q.empty())
    {
        int k = Q.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                if (!flag[v[i].END])
                {
                    Q.push(v[i].END);
                    flag[v[i].END] = 1;
                }
            }
        }
        Q.pop();
        flag[k] = 0;
    }
}
int main()
{
#ifdef DEBUG
    freopen("atr.in", "r", stdin);
    freopen("atr.out", "w", stdout);
#endif
    memset(first, -1, sizeof(first));
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        addedge(a, b, c);
        addedge(b, a, c);
    }
    int Q;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++)
    {
        scanf("%d%d", &a, &b);
        head[b] |= (1 << a - 1);
    }
    k++;
    int to_end[21];
    for (int i = 1; i <= k; i++)
    {
        spfa(i);
        for (int j = 1; j <= k; j++)
            w[i][j] = dis[j];
        to_end[i] = dis[n];
    }
    int M = (1 << k) - 1;
    memset(f, 0x3f, sizeof(f));
    f[1][1] = 0;
    for (int i = 1; i <= M; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (!(i & (1 << j - 1)))
                continue;
            for (int l = 1; l <= k; l++)
            {
                if (!(i & (1 << l - 1)) && ((head[l] & i) == head[l]))
                {
                    f[i | (1 << l - 1)][l] = min(f[i | (1 << l - 1)][l], f[i][j] + w[j][l]);
                }
            }
        }
    }
    //printf("%d\n",f[M][5]);
    int ans = 0x3f3f3f3f;

    for (int j = 1; j <= k; j++)
    {
        ans = min(ans, f[M][j] + to_end[j]);
    }
    printf("%d\n", ans);
}
// Problem1488:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 20005;
int f[1 << 21][22];
int two[22] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,
               32768, 65536, 131072, 262144, 524288, 1048576};
struct edge
{
    int END, v, next;
} v[400005];
int head[N];
int first[N], p = 1;
int w[22][22];
void addedge(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
int dis[N];
void spfa(int x)
{
    memset(dis, 0x3f, sizeof(dis));
    queue<int> Q;
    int flag[N] = {0};
    Q.push(x);
    flag[x] = 1;
    dis[x] = 0;
    while (!Q.empty())
    {
        int k = Q.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                if (!flag[v[i].END])
                {
                    Q.push(v[i].END);
                    flag[v[i].END] = 1;
                }
            }
        }
        Q.pop();
        flag[k] = 0;
    }
}
int main()
{
#ifdef DEBUG
    freopen("atr.in", "r", stdin);
    freopen("atr.out", "w", stdout);
#endif
    memset(first, -1, sizeof(first));
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        addedge(a, b, c);
        addedge(b, a, c);
    }
    int Q;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++)
    {
        scanf("%d%d", &a, &b);
        head[b] |= two[a];
    }
    k++;
    int to_end[21];
    for (int i = 1; i <= k; i++)
    {
        spfa(i);
        for (int j = 1; j <= k; j++)
            w[i][j] = dis[j];
        to_end[i] = dis[n];
    }
    int M = (1 << k) - 1;
    memset(f, 0x3f, sizeof(f));
    f[1][1] = 0;
    for (int i = 1; i <= M; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (!(i & two[j]))
                continue;
            for (int l = 1; l <= k; l++)
            {
                if (!(i & two[l]) && ((head[l] & i) == head[l]))
                {
                    f[i | two[l]][l] = min(f[i | two[l]][l], f[i][j] + w[j][l]);
                }
            }
        }
    }
    //printf("%d\n",f[M][5]);
    int ans = 0x3f3f3f3f;
    for (int j = 1; j <= k; j++)
    {
        ans = min(ans, f[M][j] + to_end[j]);
    }
    printf("%d\n", ans);
}
// Problem1497:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int a[10005], n;
int f[10005], g[10005];
int Maxlen = 0;
int find(int x)
{
    int l = 1, r = Maxlen, ans = 0;
    while (l <= r)
    {
        int m = l + r >> 1;
        if (g[m] > x)
            l = m + 1, ans = m;
        else
            r = m - 1;
    }
    return ans;
}
void printans(int x)
{
    int pre = 0x80808080;
    for (int i = 1; i <= n; i++)
    {
        if (f[i] >= x && a[i] > pre)
        {
            printf("%d ", a[i]);
            pre = a[i];
            x--;
            if (!x)
                break;
        }
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = n; i > 0; i--)
    {
        f[i] = find(a[i]) + 1;
        Maxlen = max(Maxlen, f[i]);
        g[f[i]] = max(g[f[i]], a[i]);
    }
    //printf("%d\n",Maxlen);
    int m;
    scanf("%d", &m);
    while (m--)
    {
        int len;
        scanf("%d", &len);
        if (len > Maxlen)
            printf("Impossible\n");
        else
            printans(len);
    }
    return 0;
}
// Problem1514:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
unsigned int base = 31;
unsigned int bin[100005];
struct Treap
{
    struct Node
    {
        Node *ch[2];
        int size, key, c;
        unsigned int Hash;
        Node(unsigned int x)
        {
            c = x;
            Hash = x;
            key = rand(), size = 1;
            ch[0] = ch[1] = NULL;
        }
#define size(_) ((_) ? (_)->size : 0)
#define Hash(_) ((_) ? (_)->Hash : 0)
        void PushUp()
        {
            size = size(ch[0]) + size(ch[1]) + 1;
            Hash = Hash(ch[0]) * bin[size(ch[1]) + 1] + c * bin[size(ch[1])] + Hash(ch[1]);
        }
    } * root;
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
        if (A->key < B->key)
        {
            A->ch[1] = Merge(A->ch[1], B);
            A->PushUp();
            return A;
        }
        else
        {
            B->ch[0] = Merge(A, B->ch[0]);
            B->PushUp();
            return B;
        }
    }
    typedef pair<Node *, Node *> DNode;
    DNode Split(Node *rt, int k)
    {
        if (!rt)
            return DNode(NULL, NULL);
        DNode o;
        if (size(rt->ch[0]) >= k)
        {
            o = Split(rt->ch[0], k);
            rt->ch[0] = o.second;
            rt->PushUp();
            o.second = rt;
        }
        else
        {
            o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
            rt->ch[1] = o.first;
            rt->PushUp();
            o.first = rt;
        }
        return o;
    }
    void Insert(char s, int k)
    {
        DNode x = Split(root, k);
        Node *n = new Node((int)s);
        root = Merge(Merge(x.first, n), x.second);
    }
    void dfs(Node *rt)
    {
        if (rt)
        {
            dfs(rt->ch[0]);
            printf("%c", rt->c);
            dfs(rt->ch[1]);
            // rt->PushUp();
        }
    }
    void print()
    {
        dfs(root);
    }
} root;
bool Judge(int a, int b, int mid)
{
    if (!mid)
        return 1;
    Treap::DNode x = root.Split(root.root, a);
    if (mid > size(x.second))
    {
        root.root = root.Merge(x.first, x.second);
        return 0;
    }
    Treap::DNode y = root.Split(x.second, mid);
    // printf("1: ");
    // root.dfs(y.first);
    // printf("\n");
    unsigned int Hash1 = y.first->Hash;
    // printf("%u\n", Hash1);
    root.root = root.Merge(x.first, root.Merge(y.first, y.second));
    x = root.Split(root.root, b);
    if (mid > size(x.second))
    {
        root.root = root.Merge(x.first, x.second);
        return 0;
    }
    y = root.Split(x.second, mid);
    // printf("2: ");
    // root.dfs(y.first);
    // printf("\n");
    unsigned int Hash2 = y.first->Hash;
    // printf("%u\n", Hash2);
    root.root = root.Merge(x.first, root.Merge(y.first, y.second));
    return Hash1 == Hash2;
}
void Get_ans(int a, int b)
{
    int l = 0, r = 100005;
    int ans = 0;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (Judge(a, b, mid))
            ans = mid, l = mid + 1;
        else
            r = mid;
    }
    printf("%d\n", ans);
}
int main()
{
    static char s[100005];
    bin[0] = 1;
    for (int i = 1; i <= 100000; i++)
        bin[i] = bin[i - 1] * base;
    scanf("%s", s);
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        root.Insert(s[i], i);
    // root.print();
    // while(1);
    int m;
    scanf("%d", &m);
    char c[10], ch[10];
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", c);
        if (c[0] == 'Q')
        {
            int l, r;
            scanf("%d%d", &l, &r);
            l--, r--;
            Get_ans(l, r);
        }
        else if (c[0] == 'R')
        {
            int l;
            scanf("%d%s", &l, ch);
            l--;
            Treap::DNode x = root.Split(root.root, l);
            Treap::DNode y = root.Split(x.second, 1);
            y.first->c = (int)ch[0];
            y.first->Hash = ch[0];
            root.root = root.Merge(x.first, root.Merge(y.first, y.second));
            //root.print();
        }
        else
        {
            int l;
            scanf("%d%s", &l, ch);
            Treap::DNode x = root.Split(root.root, l);
            Treap::Node *n = new Treap::Node(ch[0]);
            root.root = root.Merge(x.first, root.Merge(n, x.second));
        }
    }
}
// Problem1516:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct edge
{
    int S, E, v;
    bool operator<(const edge &b) const
    {
        return v < b.v;
    }
} v[2005];
struct data
{
    int l, r, v;
} a[2005];
int fa[105];
int find(int x)
{
    if (x != fa[x])
        return find(fa[x]);
    return fa[x];
}
int Sum;
void dfs(int s, int now, int t)
{
    if (now == a[s].r + 1)
    {
        if (t == a[s].v)
            Sum++;
        return;
    }
    int x = find(v[now].S), y = find(v[now].E);
    if (x != y)
    {
        fa[x] = y;
        dfs(s, now + 1, t + 1);
        fa[x] = x, fa[y] = y;
    }
    dfs(s, now + 1, t);
}
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= m; i++)
    {
        v[i].S = read(), v[i].E = read();
        v[i].v = read();
    }
    sort(v + 1, v + m + 1);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    int t = 0;
    int cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        if (v[i].v != v[i - 1].v)
        {
            a[++cnt].l = i;
            a[cnt - 1].r = i - 1;
        }
        int x = find(v[i].S), y = find(v[i].E);
        if (x != y)
        {
            fa[x] = y;
            a[cnt].v++;
            t++;
            // if(t == n - 1) break;
        }
    }
    a[cnt].r = m;
    if (t != n - 1)
        return printf("0\n"), 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        Sum = 0;
        dfs(i, a[i].l, 0);
        ans = ans * Sum % 31011;
        for (int j = a[i].l; j <= a[i].r; j++)
        {
            int x = find(v[j].S), y = find(v[j].E);
            if (x != y)
                fa[x] = y;
        }
    }
    printf("%d", ans);
}
// Problem1528:
#include <cstdio>
#include <cstring>
#include <cstring>
using namespace std;
int cnt[405], now[405], n;
int ans[405];
bool Check()
{
    memcpy(now, cnt, sizeof(now));
    for (int i = 1; i <= n; i++)
        while (now[i])
        {
            if (now[i] >= 3)
            {
                now[i] -= 3;
                continue;
            }
            if (i <= n - 2 && now[i + 1] && now[i + 2])
            {
                now[i]--;
                now[i + 1]--;
                now[i + 2]--;
                continue;
            }
            return 0;
        }
    return 1;
}
int main()
{
    int a, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 3 * m + 1; i++)
        scanf("%d", &a), cnt[a]++;
    for (int i = 1; i <= n; i++)
    {
        cnt[i]++;
        for (int j = 1; j <= n; j++)
        {
            if (cnt[j] >= 2)
            {
                cnt[j] -= 2;
                if (Check())
                {
                    ans[++ans[0]] = i;
                    cnt[j] += 2;
                    break;
                }
                cnt[j] += 2;
            }
        }
        cnt[i]--;
    }
    if (ans[0])
    {
        for (int i = 1; i <= ans[0]; i++)
            printf("%d%c", ans[i], " \n"[i == ans[0]]);
    }
    else
        printf("NO");
}
// Problem1540:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
int w[1000005];
struct edge
{
    int END, next;
} v[1000005];
int first[1000005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dfn[1000005], low[1000005], Index;
bool flag[1000005];
int size[1000005], belong[1000005], T;
stack<int> st;
void Tarjan(int rt)
{
    dfn[rt] = low[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!dfn[v[i].END])
        {
            Tarjan(v[i].END);
            low[rt] = min(low[rt], low[v[i].END]);
        }
        else if (flag[v[i].END])
            low[rt] = min(low[rt], dfn[v[i].END]);
    }
    if (low[rt] == dfn[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            belong[v] = T;
            size[T]++;
            flag[v] = 0;
        } while (low[v] != dfn[v]);
    }
}
long long f[1000005][2], g[1000005][2][2];
void DP(int x)
{
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (belong[v[i].END] == belong[x])
            continue;
        DP(v[i].END);
        f[x][0] += max(f[v[i].END][0], f[v[i].END][1]);
        f[x][1] += f[v[i].END][0];
    }
    f[x][1] += w[x];
}
long long DFS(int rt)
{
    int now = rt, pre;
    do
    {
        if (now == rt)
        {
            DP(now);
            g[rt][0][0] = f[rt][0];
            g[rt][1][1] = f[rt][1];
        }
        else
        {
            DP(now);
            g[now][0][0] = f[now][0] + max(g[pre][0][1], g[pre][0][0]);
            g[now][1][0] = f[now][0] + max(g[pre][1][1], g[pre][1][0]);
            g[now][0][1] = f[now][1] + g[pre][0][0];
            g[now][1][1] = f[now][1] + g[pre][1][0];
        }
        pre = now;
        for (int i = first[now]; i != -1; i = v[i].next)
        {
            if (belong[v[i].END] == belong[now])
            {
                now = v[i].END;
                break;
            }
        }
    } while (now != rt);
    return max(g[pre][0][0], max(g[pre][0][1], g[pre][1][0]));
}
int main()
{
    memset(first, -1, sizeof(first));
    int n;
    scanf("%d", &n);
    int b;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &w[i], &b);
        add(b, i);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (size[belong[i]] > 1 && !flag[belong[i]])
        {
            flag[belong[i]] = 1;
            ans += DFS(i);
        }
    }
    printf("%lld", ans);
}
// Problem1543:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double Pi = acos(-1);
struct Circle
{
    double x, y, r;
} a[1005];
struct line
{
    double l, r;
    bool operator<(const line &b) const
    {
        return l < b.l;
    }
} q[1005];
int n, t;
double dis(int a1, int a2)
{
    return sqrt((a[a1].x - a[a2].x) * (a[a1].x - a[a2].x) + (a[a1].y - a[a2].y) * (a[a1].y - a[a2].y));
}
bool In(int a1, int a2)
{
    if (a[a1].r >= a[a2].r + dis(a1, a2))
        return 1;
    return 0;
}
void add(int a1, int a2)
{
    double d = dis(a1, a2);
    double st = atan2(a[a1].x - a[a2].x, a[a1].y - a[a2].y);
    double l = acos(((a[a1].r * a[a1].r - a[a2].r * a[a2].r + d * d) / (2 * d)) / a[a1].r);
    q[++t] = (line){st - l, st + l};
}
double Get(int x)
{
    for (int i = x + 1; i <= n; i++)
        if (In(i, x))
            return 0;
    t = 0;
    for (int i = x + 1; i <= n; i++)
        if (!In(x, i) && a[x].r + a[i].r >= dis(x, i))
            add(x, i);
    for (int i = 1; i <= t; i++)
    {
        if (q[i].l < 0)
            q[i].l += 2 * Pi;
        if (q[i].r < 0)
            q[i].r += 2 * Pi;
        if (q[i].l > q[i].r)
        {
            q[++t] = (line){0, q[i].r};
            q[i].r = 2 * Pi;
        }
    }
    double tmp = 0, now = 0;
    sort(q + 1, q + t + 1);
    for (int i = 1; i <= t; i++)
        if (q[i].l > now)
        {
            tmp += q[i].l - now;
            now = q[i].r;
        }
        else
            now = max(now, q[i].r);
    tmp += 2 * Pi - now;
    return a[x].r * tmp;
}
int main()
{
    // freopen("disc.in", "r", stdin);
    // freopen("disc.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &a[i].r, &a[i].x, &a[i].y);
    double ans = 0;
    for (int i = 1; i <= n; i++)
        ans += Get(i);
    printf("%.3lf", ans);
}
// Problem1547:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define LL long long
using namespace std;
LL s[1005][1005];
struct data
{
    LL v, i;
};
deque<data> up[1005], down[1005];
deque<data> maxm, minm;
int main()
{
    //freopen("square.in","r",stdin);
    //freopen("square.out","w",stdout);
    int a, b, n;
    LL ans = 0x7fffffffffffffffLL;
    scanf("%d%d%d", &a, &b, &n);
    for (int i = 1; i <= a; i++)
        for (int j = 1; j <= b; j++) /*cin>>s[i][j];*/
            scanf("%d", &s[i][j]);
    for (int j = 1; j <= b; j++)
    {
        for (int i = 1; i <= a; i++)
        {
            while (!up[i].empty() && s[i][j] > up[i].back().v)
                up[i].pop_back();
            while (!down[i].empty() && s[i][j] < down[i].back().v)
                down[i].pop_back();
            up[i].push_back((data){s[i][j], j});
            down[i].push_back((data){s[i][j], j});
            while (up[i].begin()->i <= j - n)
                up[i].pop_front();
            while (down[i].begin()->i <= j - n)
                down[i].pop_front();
        }
        if (j >= n)
        {
            for (int i = 1; i <= a; i++)
            {
                while (!maxm.empty() && up[i].front().v > maxm.back().v)
                    maxm.pop_back();
                while (!minm.empty() && down[i].front().v < minm.back().v)
                    minm.pop_back();
                maxm.push_back((data){up[i].front().v, i});
                minm.push_back((data){down[i].front().v, i});
                while (maxm.begin()->i <= i - n)
                    maxm.pop_front();
                while (minm.begin()->i <= i - n)
                    minm.pop_front();
                if (i >= n)
                    ans = min(ans, maxm.begin()->v - minm.begin()->v);
            }
            maxm.clear();
            minm.clear();
        }
    }
    cout << ans << endl;
}

// Problem1554:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int a[5][5], b[5][5];
int Index;
int dis[20][20];
void find(int x, int y)
{
    int k = b[x][y];
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (a[i][j])
                dis[k][a[i][j]] = abs(i - x) + abs(j - y);
}
int get_num(int x)
{
    int ans = 0;
    while (x)
    {
        ans += (x & 1);
        x >>= 1;
    }
    return ans;
}
int f[17][(1 << 16) + 1];
int main()
{
    //freopen("movea.in","r",stdin);
    //freopen("movea.out","w",stdout);
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            scanf("%1d", &a[i][j]);
            if (a[i][j])
                a[i][j] = ++Index;
        }
    Index = 0;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            scanf("%1d", &b[i][j]);
            if (b[i][j])
                b[i][j] = ++Index;
        }
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    int N = (1 << Index) - 1;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (b[i][j])
                find(i, j);
    for (int i = 1; i <= Index; i++)
    {
        for (int S = 0; S <= N; S++)
        {
            if (get_num(S) == i - 1)
            {
                for (int j = 1; j <= Index; j++)
                {
                    if (!(S & (1 << (j - 1))))
                    {
                        f[i][S | (1 << (j - 1))] = min(f[i][S | (1 << (j - 1))], f[i - 1][S] + dis[i][j]);
                    }
                }
            }
        }
    }
    printf("%d\n", f[Index][N]);
}
// Problem1554:/*
*@Author : WildRage
               *@Date : 2017 -
    07 - 15 15 : 44 : 55 * @Last Modified by : WildRage *@Last Modified time : 2017 - 07 - 15 16 : 26 : 58 * /
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
                                                                                               using namespace std;
const int INF = 0x7fffffff;
int idx1[5][5], idx2[5][5];
int a[5][5], b[5][5];
struct edge
{
    int S, END, next, cap, cost;
} v[200];
int first[40], p;
void add(int a, int b, int f, int c)
{
    v[p].S = a, v[p].END = b, v[p].next = first[a], v[p].cap = f, v[p].cost = c, first[a] = p++;
    v[p].S = b, v[p].END = a, v[p].next = first[b], v[p].cap = 0, v[p].cost = -c, first[b] = p++;
}
int dis[40], pre[40];
bool vis[40];
bool Spfa(int S, int E)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(pre, -1, sizeof(pre));
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(S);
    vis[S] = 1;
    dis[S] = 0;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        vis[u] = 0;
        for (int i = first[u]; i != -1; i = v[i].next)
        {
            if (!v[i].cap)
                continue;
            if (dis[v[i].END] > dis[u] + v[i].cost)
            {
                dis[v[i].END] = dis[u] + v[i].cost;
                pre[v[i].END] = i;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
        }
    }
    return dis[E] != 0x3f3f3f3f;
}
int Max_Profit(int S, int T)
{
    int ans = 0, flow;
    while (Spfa(S, T))
    {
        flow = INF;
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            flow = min(flow, v[i].cap);
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            v[i].cap -= flow, v[i ^ 1].cap += flow;
        ans += dis[T] * flow;
    }
    return ans;
}
int Dis(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
int main()
{
    memset(first, -1, sizeof(first));
    int Index = 0;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            scanf("%1d", &a[i][j]);
            if (a[i][j])
                a[i][j] = ++Index;
        }
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            scanf("%1d", &b[i][j]);
            if (b[i][j])
                b[i][j] = ++Index;
        }
    int S = 0, T = 36;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (a[i][j] && !b[i][j])
            {
                add(S, a[i][j], 1, 0);
                for (int k = 1; k <= 4; k++)
                    for (int m = 1; m <= 4; m++)
                        if (!a[k][m] && b[k][m])
                            add(a[i][j], b[k][m], 1, Dis(i, j, k, m));
            }

    for (int k = 1; k <= 4; k++)
        for (int m = 1; m <= 4; m++)
            if (!a[k][m] && b[k][m])
                add(b[k][m], T, 1, 0);
    printf("%d", Max_Profit(S, T));
    //while(1);
}
// Problem1559:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next;
} v[40005];
int first[205], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int link[205];
bool vis[205];
int find(int x)
{
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END])
        {
            vis[v[i].END] = 1;
            if (link[v[i].END] == -1 || find(link[v[i].END]))
            {
                link[v[i].END] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    int T, a;
    scanf("%d", &T);
    while (T--)
    {
        memset(first, -1, sizeof(first));
        p = 0;
        memset(link, -1, sizeof(link));
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &a);
                if (a)
                    add(i, j);
            }
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            memset(vis, 0, sizeof(vis));
            if (find(i))
                ans++;
        }
        if (ans == n)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
// Problem1572:
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int f[1 << 10][1001];
int get_1(int x)
{
    int cnt = 0;
    while (x)
    {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}
int main()
{
    int T, n, N, d;
    char s[15];
    int a[15], num[10];
    scanf("%d", &T);
    while (T--)
    {
        memset(f, 0, sizeof(f));
        memset(num, 0, sizeof(num));
        scanf("%s", s);
        scanf("%d", &d);
        n = strlen(s);
        for (int i = 0; i < n; i++)
        {
            a[i + 1] = s[i] - '0';
            num[a[i + 1]]++;
        }
        N = (1 << n) - 1;
        f[0][0] = 1;
        for (int i = 0; i <= N; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if ((1 << j - 1) & i)
                    continue;
                for (int m = 0; m < d; m++)
                {
                    f[i | (1 << j - 1)][(m * 10 + a[j]) % d] += f[i][m];
                }
            }
        }
        for (int i = 0; i <= 9; i++)
        {
            for (int j = 1; j <= num[i]; j++)
            {
                f[N][0] /= j;
            }
        }
        printf("%d\n", f[N][0]);
    }
}
// Problem1579:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define ULL unsigned long long
int n, k;
const int MOD = 1e9 + 7;
// struct Hash_Table
// {
// 	struct data
// 	{
// 		ULL x;
// 		long long ans;
// 		int next;
// 	}v[1000005];
// 	int first[76545], p;
// 	Hash_Table()
// 	{
// 		memset (first, -1, sizeof(first));
// 		p = 0;
// 	}
// 	void add(int h, int x, int a)
// 	{
// 		v[p].x = x;
// 		v[p].ans = a;
// 		v[p].next = first[h];
// 		first[h] = p++;
// 	}
// 	bool count(ULL x)
// 	{
// 		int H = x % 76543;
// 		for (int i = first[H]; i != -1; i = v[i].next)
// 			if (v[H].x == x)
// 				return 1;
// 		return 0;
// 	}
// 	long long &operator [](ULL a)
// 	{
// 		int H = a % 76543;
// 		for (int i = first[H]; i != -1; i = v[i].next)
// 			if (v[H].x == a)
// 				return v[H].ans;
// 		add(H, a, 0);
// 		return v[first[H]].ans;
// 	}
// }mp;
int c[20];
int temp[20];
map<ULL, long long> mp;
const int base = 9091;
long long DFS(int Dep, int last)
{
    if (Dep == n)
        return 1;
    int h = 0;
    for (int i = 1; i <= k; i++)
        if (i != last)
            temp[++h] = c[i];
    sort(temp + 1, temp + h + 1);
    temp[++h] = c[last];
    ULL Hash = 0;
    for (int i = 1; i <= h; i++)
        Hash = Hash * base + temp[i];
    if (mp.count(Hash))
        return mp[Hash];
    long long ans = 0;
    for (int i = 1; i <= k; i++)
    {
        if (i != last && c[i])
        {
            c[i]--;
            (ans += DFS(Dep + 1, i)) %= MOD;
            c[i]++;
        }
    }
    mp[Hash] = ans;
    return ans;
}
int main()
{
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
        scanf("%d", &c[i]), n += c[i];
    printf("%lld", DFS(0, 0));
    // while (1);
}

// Problem1582:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[55], b[1025], m;
int Sum[1025];
bool OK;
int T, Wis, mid;
void dfs(int x, int now)
{
    if (!x)
    {
        OK = 1;
        return;
    }
    if (Sum[mid] + Wis > T)
        return;
    for (int i = now; i <= m; i++)
    {
        if (a[i] >= b[x])
        {
            a[i] -= b[x];
            if (a[i] < b[1])
                Wis += a[i];
            if (b[x] == b[x - 1])
                dfs(x - 1, i);
            else
                dfs(x - 1, 1);
            if (a[i] < b[1])
                Wis -= a[i];
            a[i] += b[x];
            if (OK)
                return;
        }
    }
}
bool Judge(int mid)
{
    OK = 0;
    dfs(mid, 1);
    return OK;
}
int main()
{
    // freopen("fence8.in","r",stdin);
    // freopen("fence8.out","w",stdout);
    int n;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", a + i);
        T += a[i];
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", b + i);
    }
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
        Sum[i] = Sum[i - 1] + b[i];
    while (Sum[n] > T)
        n--;
    sort(a + 1, a + m + 1);
    int l = 1, r = n + 1;
    int ans = 0;
    while (l < r)
    {
        Wis = 0;
        mid = l + r >> 1;
        //printf("%d\n", mid);
        if (Judge(mid))
            ans = mid, l = mid + 1;
        else
            r = mid;
    }
    printf("%d", ans);
}
// Problem1587:
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
long long f[10][90][1 << 10];
int map[1 << 10][1 << 10];
int able[1 << 10];
int get_num(int x)
{
    int cut = 0;
    while (x)
    {
        cut += x & 1;
        x >>= 1;
    }
    return cut;
}
int N;
void get_able()
{
    for (int S = 0; S <= N; S++)
    {
        if (S & (S >> 1))
            continue;
        if (S & (S << 1))
            continue;
        able[S] = 1;
    }
}
void get_map()
{
    for (int S = 0; S <= N; S++)
    {
        for (int L = 0; L <= N; L++)
        {
            if (S & L)
                continue;
            if (S & (L >> 1))
                continue;
            if (S & (L << 1))
                continue;
            map[S][L] = 1;
        }
    }
}
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    N = (1 << n) - 1;
    get_able();
    get_map();
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int S = 0; S <= N; S++)
        {
            if (!able[S])
                continue;
            int t = get_num(S);
            for (int j = t; j <= k; j++)
            {
                for (int l = 0; l <= N; l++)
                {
                    if (map[S][l] && able[l] && j >= t + get_num(l))
                    {
                        f[i][j][S] += f[i - 1][j - t][l];
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i <= N; i++)
        ans += f[n][k][i];
    printf("%lld", ans);
}
// Problem1598:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <list>
#include <queue>
using namespace std;
// class Node
// {
//   public:
//     int s, key, v;
//     Node *ch[2];
//     Node(int x)
//     {
//         v = x;
//         key = rand();
//         s = 1;
//         ch[0] = ch[1] = NULL;
//     }
// #define Size(_) ((_) ? (_)->s : 0)
//     void Pushup()
//     {
//         s = Size(ch[0]) + Size(ch[1]) + 1;
//     }
// };
// Node *Merge(Node *A, Node *B)
// {
//     if (!A)
//         return B;
//     if (!B)
//         return A;
//     if (A->key > B->key)
//     {
//         A->ch[1] = Merge(A->ch[1], B);
//         A->Pushup();
//         return A;
//     }
//     else
//     {
//         B->ch[0] = Merge(A, B->ch[0]);
//         B->Pushup();
//         return B;
//     }
// }
// Node *rt[100005];
struct edge
{
    int END, next;
} v[2000005 << 1];
bool unable[100005];
// int father[100005];
// int find(int x)
// {
//     if (father[x] != x)
//         father[x] = find(father[x]);
//     return father[x];
// }
int first[100005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
// int comp(Node *A, Node *B)
// {
//     return Size(A) < Size(B);
// }
// class list_node
// {
//   public:
//     list_node *next, *last;
//     int v;
//     list_node(int i)
//     {
//         v = i;
//         last = NULL;
//     }
// } * head;
// void insert(list_node *hd, int i){
//     while(hd->last) hd=hd->last;
//     hd->last=new list_node(i);
//     hd->last->next=hd;
// }
list<int> ls;
bool vis[100005];
int in[100005], n;
int ans = 0, size[100005];
void bfs(int x)
{
    queue<int> Q;
    Q.push(x);
    in[x] = ans;
    //size[ans]=1;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        // in[k] = ans;
        //size[ans]++;
        memset(vis, 1, sizeof(vis[0]) * n + 1);
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            vis[v[i].END] = 0;
        }
        list<int>::iterator s;
        for (list<int>::iterator it = ls.begin(); it != ls.end(); it = s)
        {
            s = it;
            s++;
            if (vis[*it])
            {
                Q.push(*it);
                in[*it] = ans;
                ls.erase(it);
                size[ans]++;
            }
        }
    }
}
// vector<Node *> ans;
int main()
{
    // freopen("biu.in", "r", stdin);
    // freopen("biu.out", "w", stdout);
    srand(0);
    int m;
    memset(first, -1, sizeof(first));
    scanf("%d%d", &n, &m);
    // for (int i = 1; i <= n; i++)
    //     rt[i] = new Node(i);
    // for (int i = 1; i <= n; i++)
    //     father[i] = i;
    int a, b;
    while (m--)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    for (int i = 1; i <= n; i++)
    {
        ls.push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        if (in[i])
            continue;
        ans++;
        bfs(i);
    }
    printf("%d\n", ans);
    sort(size + 1, size + ans + 1);
    for (int i = 1; i <= ans; i++)
        printf("%d ", size[i]);
    // for (int i = 1; i <= n; i++)
    // {
    //     memset(vis, 0, sizeof(vis[0]) * n + 1);
    //     for (int j = first[i]; j != -1; j = v[j].next)
    //     {
    //         vis[v[j].END] = 1;
    //     }
    //     for (int j = 1; j <= n; j++)
    //     {
    //         if (!vis[j])
    //         {
    //             if (find(i) != find(j))
    //             {
    //                 rt[find(i)] = Merge(rt[find(i)], rt[find(j)]);
    //                 unable[find(j)] = 1;
    //                 father[find(j)] = i;
    //             }
    //         }
    //     }
    // }
    // for (int i = 1; i <= n; i++)
    // {
    //     if (!unable[i])
    //         ans.push_back(rt[i]);
    // }
    // printf("%d\n", ans.size());
    // sort(ans.begin(), ans.end(), comp);
    // for (vector<Node *>::iterator i = ans.begin(); i != ans.end(); i++)
    // {
    //     printf("%d ", Size((*i)));
    // }
    //while(1);
}

// Problem1604:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
bool type[1005][1005];
int a[1005][1005];
struct Point
{
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};
vector<Point> c[1005];
int dx[4] = {0, 0, 1, -1},
    dy[4] = {-1, 1, 0, 0};
#define id(_) ((_).x * m + (_).y + 1)
int father[10000105];
bool s[10000105];
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
void merge(int a, int b)
{
    int x = find(a), y = find(b);
    if (x != y)
    {
        father[x] = y;
        s[y] |= s[x];
    }
}
int main()
{
    int n, m;
    int b;
    scanf("%d%d", &n, &m);
    int h = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &b);
            if (b >= 0)
                type[i][j] = 1;
            a[i][j] = (b > 0 ? b : -b);
            c[a[i][j]].push_back(Point(i, j));
            h = max(h, a[i][j]);
        }
    for (int i = 1; i <= (n + 1) * m; i++)
        father[i] = i, s[i] = 0;
    int ans = 0;
    for (int i = 0; i <= h; i++)
    {
        for (int j = 0; j < c[i].size(); j++)
        {
            Point now = c[i][j];
            for (int k = 0; k < 4; k++)
            {
                Point nex(now.x + dx[k], now.y + dy[k]);
                if (nex.x > 0 && nex.y > 0 && nex.x <= n && nex.y <= m)
                {
                    if (a[nex.x][nex.y] <= a[now.x][now.y])
                    {
                        merge(id(now), id(nex));
                    }
                }
            }
        }
        for (int j = 0; j < c[i].size(); j++)
        {
            Point now = c[i][j];
            if (type[now.x][now.y])
            {
                if (!s[find(id(now))])
                {
                    s[find(id(now))] = 1;
                    ans++;
                }
            }
        }
    }
    printf("%d\n", ans);
}

// Problem1623:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 100005;
#define int long long
struct edge
{
    int END, next;
} v[N * 10];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dfn[N], low[N], Index;
int size[N], ans[N], n;
bool iscut[N];
void Tarjan(int rt, int fa)
{
    dfn[rt] = low[rt] = ++Index;
    long long S = 0;
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!dfn[v[i].END])
        {
            Tarjan(v[i].END, rt);
            size[rt] += size[v[i].END];
            low[rt] = min(low[rt], low[v[i].END]);
            if (low[v[i].END] >= dfn[rt])
            {
                ans[rt] += S * size[v[i].END];
                S += size[v[i].END];
            }
        }
        else
            low[rt] = min(low[rt], dfn[v[i].END]);
    }
    ans[rt] += (n - S - 1) * (S);
}
signed main()
{
    int m;
    scanf("%lld%lld", &n, &m);
    memset(first, -1, sizeof(first));
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &a, &b);
        add(a, b);
        add(b, a);
    }
    Tarjan(1, -1);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", (ans[i] + (n - 1)) << 1);
    // while (1);
}
// Problem1624:
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int a[1000005], Maxn, t, Min, Max;
int times[1000005];
bool die[1000005], nodie[1000005];
int Q[1000005];
int main()
{
    //freopen("maf.in", "r", stdin);
    //freopen("maf.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        times[a[i]]++;
    }
    //Q.resize(1000001);
    for (int i = 1; i <= n; i++)
    {
        if (!times[i])
        {
            Max++;
            Q[++Min] = i;
        }
    }
    //printf("%d\n",Max);

    //for (vector<int>::iterator it = Q.begin(); it != Q.end(); it++)
    for (int i = 1; i <= Min; i++)
    {
        //printf("%d---------%d=======\n",it-Q.begin(),*it);
        int k = a[Q[i]];
        if (die[k])
            continue;
        die[k] = 1;
        nodie[a[k]] = 1;
        --times[a[k]];
        if (!times[a[k]])
        {
            Q[++Min] = a[k];
        }
    }
    int sum;
    bool All_NoDied;
    for (int i = 1; i <= n; i++)
    {
        if (times[i] && !die[i])
        {
            sum = 0;
            All_NoDied = 0;
            for (int j = i; !die[j]; j = a[j])
            {
                die[j] = 1;
                sum++;
                All_NoDied |= nodie[j];
            }
            if (!All_NoDied && sum > 1)
                Max++;
            Min += sum / 2;
        }
    }
    printf("%d %d\n", n - Min, n - Max);
}
// Problem1631:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1000005;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct edge
{
    int END, next;
} v[N << 1];
int first[N], p, n;
void add(int a, int b)
{
    v[p].next = first[a];
    v[p].END = b;
    first[a] = p++;
}
long long f[N];
long long size[N];
void DFS1(int rt, int fa)
{
    f[rt] = 0;
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        DFS1(v[i].END, rt);
        size[rt] += size[v[i].END];
        f[rt] += f[v[i].END] + size[v[i].END];
    }
}
void DFS2(int rt, int fa)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        f[v[i].END] += f[rt] - f[v[i].END] + n - 2 * size[v[i].END];
        DFS2(v[i].END, rt);
    }
}
int main()
{
    int a, b;
    n = read();
    memset(first, -1, sizeof(first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    DFS1(1, 0);
    DFS2(1, 0);
    long long Ans = 0;
    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        if (Ans < f[i])
        {
            Ans = f[i];
            ans = i;
        }
    }
    printf("%d", ans);
}
// Problem1650:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
#define LL long long
struct data
{
    LL Num;
    int pos;
    bool operator<(const data &a) const
    {
        return Num == a.Num ? pos < a.pos : Num < a.Num;
    }
};
int fre[100005], nxt[100005];
LL a[100005];
set<data> st;
LL merge()
{
    int A = st.begin()->pos;
    LL ans = a[A];
    a[A] = -a[A];
    a[A] += a[fre[A]], a[A] += a[nxt[A]];
    st.erase(st.begin());
    st.erase((data){a[fre[A]], fre[A]});
    st.erase((data){a[nxt[A]], nxt[A]});
    st.insert((data){a[A], A});
    if (fre[fre[A]])
        nxt[fre[fre[A]]] = A;
    if (nxt[nxt[A]])
        fre[nxt[nxt[A]]] = A;
    fre[A] = fre[fre[A]];
    nxt[A] = nxt[nxt[A]];
    return ans;
}
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    long long b, c;
    scanf("%lld", &b);
    for (int i = 1; i < n; i++)
    {
        scanf("%lld", &c);
        a[i] = c - b;
        b = c;
        fre[i] = i - 1;
        nxt[i] = i + 1;
        st.insert((data){a[i], i});
    }
    nxt[n - 1] = 0;
    a[0] = 0x3f3f3f3f3f3f3f3fll;
    LL ans = 0;
    while (k--)
    {
        ans += merge();
    }
    printf("%lld", ans);
}
// Problem1651:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
struct data
{
    int F, L, id;
    vector<int> X, Y;
    data() { ; }
    data(int a, int b, int c)
    {
        F = a, L = b, id = c;
    }
};
int dp[10005][1 << 5];
int g[10005][1 << 5];
int sum[10005][1 << 5];
vector<data> v[10005];
bool flag[50005][1 << 5] = {0};
int main()
{
    //freopen("apio_zoo.in","r",stdin);
    //freopen("apio_zoo.out","w",stdout);
    int n, C, e, f, l, p;
    scanf("%d%d", &n, &C);
    for (int i = 1; i <= C; i++)
    {
        scanf("%d%d%d", &e, &f, &l);
        v[e].push_back(data(f, l, i));
        for (int j = 1; j <= f; j++)
        {
            scanf("%d", &p);
            (v[e].end() - 1)->X.push_back(p);
        }
        for (int j = 1; j <= l; j++)
        {
            scanf("%d", &p);
            (v[e].end() - 1)->Y.push_back(p);
        }
    }
    vector<data>::iterator it1;
    vector<int>::iterator it2;

    int k = 0;
    for (int i = 1; i <= n; i++)
    {
        memset(flag, 0, sizeof(flag));
        for (int S = 0; S <= 31; S++)
        {
            for (int j = 0; j <= 4; j++)
            {
                k = (j + i) % n;
                if (k == 0)
                    k = n;
                if ((1 << j) & S)
                {
                    for (it1 = v[i].begin(); it1 != v[i].end(); it1++)
                    {
                        for (it2 = it1->X.begin(); it2 != it1->X.end(); it2++)
                        {
                            if (*it2 == k)
                            {
                                if (!flag[it1->id][S])
                                {
                                    g[i][S]++;
                                    flag[it1->id][S] = 1;
                                }
                            }
                        }
                    }
                }
                else
                {
                    for (it1 = v[i].begin(); it1 != v[i].end(); it1++)
                    {
                        for (it2 = it1->Y.begin(); it2 != it1->Y.end(); it2++)
                        {
                            if (*it2 == k)
                            {
                                if (!flag[it1->id][S])
                                {
                                    g[i][S]++;
                                    flag[it1->id][S] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //char s[30];
    //for(int i=1;i<=n;i++){
    //	for(int S=0;S<=31;S++){
    //		itoa(S,s,2);
    //		printf("i:%d %s %d\n",i,s,g[i][S]);
    //	}
    //}
    int ans = 0;
    for (int K = 0; K <= 15; K++)
    {
        memset(dp[0], 0x80, sizeof(dp[0]));
        dp[0][K << 1] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int S = 0; S <= 31; S++)
            {
                dp[i][S] = max(dp[i - 1][(S & 15) << 1], dp[i - 1][(S & 15) << 1 | 1]) + g[i][S];
            }
        }
        ans = max(ans, max(dp[n][K << 1], dp[n][K << 1 | 1]));
    }
    printf("%d", ans);
    //while(1);
}
/*
10 10
1 1 1 3 2
2 1 0 4
3 1 1 5 6
4 1 1 7 6
5 1 0 6
6 1 2 9 8 10
7 1 0 10
8 1 0 8
9 1 1 1 2
10 1 0 2
*/
// Problem1729:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
int Tc, N1, N2, C1, C2, n;
int a[100005];
deque<pair<int, int>> Q;
int Calc(int x)
{
    Q.clear();
    int ans = x * Tc;
    Q.push_front(pair<int, int>(-N2, x));
    for (int i = 1; i <= n; i++)
    {
        if (i - N1 > 0)
            Q.push_front(pair<int, int>(i - N1, a[i - N1]));
        int T = a[i];
        while (T)
        {
            if (Q.empty())
                return 0x3f3f3f3f;
            pair<int, int> tmp = Q.back();
            if (tmp.first + N2 <= i && C1 > C2)
            {
                int o = min(T, tmp.second);
                T -= o;
                tmp.second -= o;
                if (tmp.first != -N2)
                    ans += o * C2;
                Q.pop_back();
                if (tmp.second)
                    Q.push_back(tmp);
            }
            else
            {
                tmp = Q.front();
                int o = min(T, tmp.second);
                T -= o;
                tmp.second -= o;
                ans += o * C1;
                Q.pop_front();
                if (tmp.second)
                    Q.push_front(tmp);
            }
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d%d%d%d%d", &n, &N1, &N2, &C1, &C2, &Tc);
    if (N1 > N2)
        swap(N1, N2), swap(C1, C2);
    int r = 0, l = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), r += a[i];
    while (l + 2 < r)
    {
        int x = l + (r - l) / 3, y = l + 2 * (r - l) / 3;
        int fx = Calc(x), fy = Calc(y);
        if (fx < fy)
            r = y;
        else
            l = x;
    }
    int ans = 0x3f3f3f3f;
    for (int i = l; i <= r; i++)
        ans = min(ans, Calc(i));
    printf("%d", ans);
}
// Problem1761:
#include <iostream>
#include <cstring>
#include <cstdio>
#define lowbit(x) ((x) & (-x))
using namespace std;
int maxn[100005];
int n;
void update(int x, int num)
{
    maxn[x] = num;
    for (int i = x; i <= 5 * n; i += lowbit(i))
        maxn[i] = max(maxn[i], num);
}
int Max(int x)
{
    int Maxn = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        Maxn = max(maxn[i], Maxn);
    return Maxn;
}
int pos[20005][6];
int p[20005];
int s2[100005];
int main()
{
    cin >> n;
    int a;
    for (int i = 1; i <= 5 * n; i++)
    {
        scanf("%d", &a);
        pos[a][++p[a]] = i;
    }
    //for(int i=1;i<=n;i++)
    //{
    //for(int j=1;j<=5;j++)cout<<pos[i][j]<<" ";cout<<endl;}
    for (int i = 1; i <= 5 * n; i++)
        scanf("%d", &s2[i]);
    for (int i = 1; i <= 5 * n; i++)
    {
        for (int j = 5; j >= 1; j--)
        {
            int Q = Max(pos[s2[i]][j] - 1) + 1;
            update(pos[s2[i]][j], Q);
        }
    }
    cout << Max(5 * n) << endl;
}

// Problem1761:
#include <iostream>
#include <cstdio>
#include <cstring>
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
using namespace std;
const int N = 100005;
int maxn[N << 2];
int f[100005];
int add[N << 2];
void Pushup(int rt)
{
    maxn[rt] = max(maxn[rt << 1], maxn[rt << 1 | 1]);
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        maxn[rt] = 0;
        return;
    }
    int m = (l + r) >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
void update(int P, int c, int l, int r, int rt)
{
    if (l == r)
    {
        maxn[rt] = c;
        //f[P]=c;
        return;
    }
    int m = (l + r) >> 1;
    if (P <= m)
        update(P, c, lch);
    else
        update(P, c, rch);
    Pushup(rt);
}
void Pushdown(int rt)
{
    if (add[rt])
    {
        add[rt << 1] = add[rt << 1 | 1] = add[rt];
        maxn[rt << 1] += add[rt];
        maxn[rt << 1 | 1] += add[rt];
        add[rt] = 0;
    }
}
void add_1(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        add[rt] += 1;
        maxn[rt] += 1;
        return;
    }
    Pushdown(rt);
    int m = (l + r) >> 1;
    if (L <= m)
        add_1(L, R, lch);
    if (R > m)
        add_1(L, R, rch);
    Pushup(rt);
}
int Max(int L, int R, int l, int r, int rt)
{
    if (L > R)
        return 0;
    if (L <= l && R >= r)
    {
        return maxn[rt];
    }
    int m = (r + l) >> 1;
    int Maxn = 0;
    if (L <= m)
        Maxn = max(Maxn, Max(L, R, lch));
    if (R > m)
        Maxn = max(Maxn, Max(L, R, rch));
    return Maxn;
}
int pos[20005][6];
int p[20005];
int s2[100005];
int main()
{
    int n;
    cin >> n;
    //buildtree(1,5*n,1);
    int a;
    for (int i = 1; i <= 5 * n; i++)
    {
        scanf("%d", &a);
        pos[a][++p[a]] = i;
    }
    //scanf("%d",&a);
    //for(int i=1;i<=5;i++)update(pos[a][i],1,1,5*n,1);
    for (int i = 1; i <= 5 * n; i++)
    {
        scanf("%d", &s2[i]);
        //for(int j=1;j<=5;j++){
        //cout<<pos[a][j]<<endl;
        //int Q=Max(1,pos[a][j]-1,1,5*n,1);
        //if(f[pos[a][j]]<Q+1)
        //update(pos[a][j],Q+1,1,5*n,1);
        //cout<<f[pos[a][j]]<<endl;
        //}
    }
    for (int i = 1; i <= 5 * n; i++)
    {
        a = s2[i];
        for (int j = 5; j >= 1; j--)
        {
            int Q = Max(1, pos[a][j] - 1, 1, 5 * n, 1);
            //if(f[pos[a][j]]<Q+1)
            update(pos[a][j], Q + 1, 1, 5 * n, 1);
            //add_1(pos[a][j]+1,5*n,1,5*n,1);
        }
    }
    cout << Max(1, 5 * n, 1, 5 * n, 1) << endl;
}

// Problem1902:
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
bool isnprime[1000005];
int prime[200005], Idx;
void Get_Prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= 1000000; i++)
    {
        if (!isnprime[i])
        {
            prime[++Idx] = i;
        }
        for (int j = 1; j <= Idx; j++)
        {
            if (prime[j] * i > 1000000)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
long long Get_Phi(long long x)
{
    if (x == 1)
        return 0;
    int i = 1;
    int Sq = sqrt(x);
    long long ans = x;
    while (x != 1)
    {
        if (prime[i] > Sq)
        {
            ans = ans - ans / x;
            break;
        }
        if (x % prime[i] == 0)
        {
            ans = ans - ans / prime[i];
            while (x % prime[i] == 0)
                x /= prime[i];
        }
        ++i;
    }
    return ans;
}
long long phi;
class Martix
{
  public:
    int n, m;
    long long a[3][3];
    Martix(int n1, int m1)
    {
        n = n1, m = m1;
        memset(a, 0, sizeof(a));
    }
    Martix operator*(const Martix &A)
    {
        Martix ans(n, A.m);
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= A.m; k++)
            {
                for (int j = 1; j <= m; j++)
                    ans.a[i][k] += a[i][j] * A.a[j][k];
                if (ans.a[i][k] >= phi)
                    ans.a[i][k] = ans.a[i][k] % phi /* + phi*/;
            }
        return ans;
    }
    Martix operator^(const long long &b)
    {
        long long k = b;
        Martix ans(n, m);
        for (int i = 1; i <= n; i++)
        {
            ans.a[i][i] = 1;
        }
        Martix A = *this;
        while (k)
        {
            if (k & 1)
                ans = ans * A;
            k >>= 1;
            A = A * A;
        }
        return ans;
    }
};
long long pow_mod(long long a, long long b, long long mod)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}
int main()
{
    //freopen("password.in", "r", stdin);
    //freopen("password.out", "w", stdout);
    long long m, p;
    Get_Prime();
    Martix O(2, 2);
    O.a[1][1] = O.a[1][2] = O.a[2][1] = 1;
    Martix L(2, 1);
    L.a[1][1] = 1;
    scanf("%lld%lld", &m, &p);
    while (m--)
    {
        long long n, q;
        scanf("%lld%lld", &n, &q);
        if (q == 1)
        {
            printf("0\n");
            continue;
        }
        int t = p - q;
        if (t == 1)
        {
            printf("1\n");
            continue;
        }
        phi = Get_Phi(q);
        printf("%lld\n", pow_mod(p, ((O ^ n) * L).a[2][1], q));
    }
}

// Problem1919:
#include <iostream>
#include <cstdio>
using namespace std;
double f[10005], g[10005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = n - 1; i >= 0; i--)
        f[i] = f[i + 1] + (double)n / (n - i);
    for (int i = n - 1; i >= 0; i--)
        g[i] = (double)i / (n - i) * f[i] + g[i + 1] + f[i + 1] + (double)n / (n - i);
    printf("%.2f", g[0]);
}
// Problem2055:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int dis[10005][25];
bool vis[10005][25];
struct edge
{
    int END, next, v;
} v[50005 << 1];
int first[10005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
struct data
{
    int x, k;
    data(int a, int b)
    {
        x = a, k = b;
    }
    bool operator<(const data &a) const
    {
        return dis[x][k] > dis[a.x][a.k];
    }
};
priority_queue<data> Q;
int main()
{
    memset(first, -1, sizeof(first));
    memset(dis, 0x3f, sizeof(dis));
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    dis[1][0] = 0;
    vis[1][0] = 1;
    Q.push(data(1, 0));
    while (!Q.empty())
    {
        data u = Q.top();
        Q.pop();
        vis[u.x][u.k] = 0;
        for (int i = first[u.x]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END][u.k] > dis[u.x][u.k] + v[i].v)
            {
                dis[v[i].END][u.k] = dis[u.x][u.k] + v[i].v;
                if (!vis[v[i].END][u.k])
                {
                    Q.push(data(v[i].END, u.k));
                    vis[v[i].END][u.k] = 1;
                }
            }
            if (dis[v[i].END][u.k + 1] > dis[u.x][u.k] && u.k < k)
            {
                dis[v[i].END][u.k + 1] = dis[u.x][u.k];
                if (!vis[v[i].END][u.k + 1])
                {
                    Q.push(data(v[i].END, u.k + 1));
                    vis[v[i].END][u.k + 1] = 1;
                }
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= k; i++)
        ans = min(ans, dis[n][i]);
    printf("%d", ans);
}
// Problem2119:
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int n, m;
int b[17][17], a[17][17], op[17][17];
inline void DoChange(int x)
{
    for (int j = 1; j <= n; j++)
    {
        if (op[x][j])
        {
            a[x - 1][j] ^= 1;
            a[x][j - 1] ^= 1;
            a[x][j + 1] ^= 1;
            a[x + 1][j] ^= 1;
        }
    }
}
inline bool ok()
{
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j] == 1)
                return 0;
        }
    }
    return 1;
}
inline void print()
{
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", op[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    //freopen("fliptile.in", "r", stdin);
    //freopen("fliptile.out", "w", stdout);
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &b[i][j]);
        }
    int N = (1 << n) - 1;
    for (int i = 0; i <= N; i++)
    {
        memcpy(a, b, sizeof(a));
        memset(op, 0, sizeof(op));
        for (int j = 1; j <= n; j++)
        {
            if (i & (1 << (j - 1)))
            {
                op[1][j] = 1;
                a[1 - 1][j] ^= 1;
                a[1][j - 1] ^= 1;
                a[1][j] ^= 1;
                a[1][j + 1] ^= 1;
                a[1 + 1][j] ^= 1;
            }
        }
        for (int j = 1; j < m; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                if (a[j][k])
                {
                    op[j + 1][k] = 1;
                    a[j][k] ^= 1;
                    a[j + 1][k] ^= 1;
                    a[j + 1][k - 1] ^= 1;
                    a[j + 1][k + 1] ^= 1;
                    a[j + 2][k] ^= 1;
                }
            }
        }
        if (ok())
        {
            print();
            //while (1);
            exit(0);
        }
    }
    printf("IMPOSSIBLE\n");
}
// Problem2158:
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int f[1 << 15];
int a[1550];
int get_num(int x)
{
    int cnt = 0;
    while (x)
    {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}
int main()
{
    int n, d, k, t, r;
    scanf("%d%d%d", &n, &d, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &t);
        for (int j = 1; j <= t; j++)
        {
            scanf("%d", &r);
            a[i] |= (1 << r - 1);
        }
    }
    int ans = 0;
    int N = (1 << d) - 1;
    for (int S = 0; S <= N; S++)
    {
        if (get_num(S) != k)
            continue;
        for (int i = 1; i <= n; i++)
        {
            if ((a[i] & S) == a[i])
            {
                f[S]++;
            }
        }
        ans = max(ans, f[S]);
    }
    printf("%d", ans);
}
// Problem2201:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
struct edge
{
    int END, v, next;
} v[300005];
int n;
int times[10005];
int first[10005], p, dis[10005];
void add(int a, int b, int c);
bool spfa(int a);
int main()
{
    int ml, md, a, b, l;
    p = 1;
    memset(first, -1, sizeof(first));
    //freopen("1.txt","r",stdin);
    scanf("%d%d%d", &n, &ml, &md);
    for (int i = 1; i <= ml; i++)
    {
        scanf("%d%d%d", &a, &b, &l);
        add(a, b, l);
    }
    for (int i = 1; i <= md; i++)
    {
        scanf("%d%d%d", &a, &b, &l);
        add(b, a, -l);
    }
    //cout<<"#"<<endl;
    if (spfa(1))
    {
        cout << "-1" << endl;
    }
    else
    {
        if (dis[n] == 0x3f3f3f3f)
            cout << "-2" << endl;
        else
            cout << dis[n] << endl;
    }
}
bool spfa(int a)
{
    bool flag[10005] = {0};
    queue<int> q;
    //deque<int> q;
    //stack<int> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(times, 0, sizeof(times));
    //q.push_back(a);
    q.push(a);
    dis[a] = 0;
    times[a]++;
    flag[a] = 1;
    while (!q.empty())
    {
        int k = q.front();
        //q.pop_front();
        //int k=q.top();
        q.pop();
        flag[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                if (!flag[v[i].END])
                {
                    flag[v[i].END] = 1;
                    times[v[i].END]++;
                    if (times[v[i].END] > n + 1)
                        return 1;
                    //q.push_back(v[i].END);
                    q.push(v[i].END);
                }
            }
        }
    }
    return 0;
}
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}

// Problem2240:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
long long A[36], full, bin[37];
int Min = 0x3f, n, m;
map<long long, int> Mp;
void dfs1(int x, long long now, int k)
{
    if (x == m + 1)
    {
        if (now == full)
            Min = min(k, Min);
        int t = Mp[now];
        if (!t || t > k)
            Mp[now] = k;
        return;
    }
    dfs1(x + 1, now, k);
    dfs1(x + 1, now ^ A[x], k + 1);
}
void dfs2(int x, long long now, int k)
{
    if (x == n + 1)
    {
        if (now == full)
            Min = min(k, Min);
        int t = Mp[full - now];
        if (!t)
            return;
        Min = min(t + k, Min);
        return;
    }
    dfs2(x + 1, now, k);
    dfs2(x + 1, now ^ A[x], k + 1);
}
int main()
{
    // freopen("lights.in","r",stdin);
    // freopen("lights.out","w",stdout);
    int c;
    scanf("%d%d", &n, &c);
    bin[1] = 1;
    for (int i = 2; i < 37; i++)
        bin[i] = bin[i - 1] << 1;
    int a, b;
    for (int i = 1; i <= c; i++)
    {
        scanf("%d%d", &a, &b);
        A[a] += bin[b];
        A[b] += bin[a];
    }
    for (int i = 1; i <= n; i++)
        A[i] += bin[i];
    full = bin[n + 1] - 1;
    m = n >> 1;
    dfs1(1, 0, 0);
    dfs2(m + 1, 0, 0);
    printf("%d", Min);
}
// Problem2256:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, k;
int a[10005];
int c[2][10005];
#define lowbit(_) ((_) & (-_))
void add(int x, int add, int op)
{
    for (int i = x; i <= k; i += lowbit(i))
        c[op][i] += add;
}
int Query(int x, int op)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[op][i];
    return ans;
}
int Get_Num(int &s)
{
    int Min = 0x3f3f3f3f, ans;
    for (int i = 1; i <= k; i++)
    {
        int now = Query(i - 1, 0) + Query(k, 1) - Query(i, 1);
        if (now < Min)
            Min = now, ans = i;
    }
    s += Min;
    add(ans, 1, 1);
    return ans;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] != -1)
            add(a[i], 1, 0), ans += Query(k, 0) - Query(a[i], 0);
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > 0)
            add(a[i], -1, 0), add(a[i], 1, 1);
        else
            a[i] = Get_Num(ans);
    }
    printf("%d", ans);
}
// Problem2257:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next;
} v[1000005];
int first[500005], p;
int f[500005][20];
int Dep[500005];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
void dfs(int rt, int fa, int dep)
{
    f[rt][0] = fa;
    Dep[rt] = dep;
    for (int i = 1; i <= 19; i++)
        f[rt][i] = f[f[rt][i - 1]][i - 1];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa)
            dfs(v[i].END, rt, dep + 1);
    }
}
int Get_Lca(int a, int b)
{
    if (Dep[a] < Dep[b])
        swap(a, b);
    int d = Dep[a] - Dep[b];
    for (int i = 19; i >= 0; i--)
        if (d & (1 << i))
            d -= (1 << i), a = f[a][i];
    if (a == b)
        return a;
    for (int i = 19; i >= 0; i--)
        if (f[a][i] != f[b][i])
            a = f[a][i], b = f[b][i];
    return f[a][0];
}
int DIS(int a, int b)
{
    int S = Get_Lca(a, b);
    return Dep[a] - Dep[S] + Dep[b] - Dep[S];
}
int main()
{
    int n, m;
    memset(first, -1, sizeof(first));
    scanf("%d%d", &n, &m);
    int a, b;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    dfs(1, 0, 0);
    int c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        int LCA1 = Get_Lca(a, b);
        int LCA2 = Get_Lca(a, c);
        int LCA3 = Get_Lca(c, b);
        if (LCA1 == LCA2)
        {
            int a1 = DIS(a, LCA3);
            int b1 = DIS(b, LCA3);
            int c1 = DIS(c, LCA3);
            printf("%d %d\n", LCA3, a1 + b1 + c1);
        }
        else if (LCA1 == LCA3)
        {
            int a1 = DIS(a, LCA2);
            int b1 = DIS(b, LCA2);
            int c1 = DIS(c, LCA2);
            printf("%d %d\n", LCA2, a1 + b1 + c1);
        }
        else if (LCA2 == LCA3)
        {
            int a1 = DIS(a, LCA1);
            int b1 = DIS(b, LCA1);
            int c1 = DIS(c, LCA1);
            printf("%d %d\n", LCA1, a1 + b1 + c1);
        }
    }
}

// Problem2274:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
int c[100005];
struct edge
{
    int END, next, v;
} v[200005];
int first[100005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int size[100005];
int vi[100005];
void DFS(int rt, int fa)
{
    size[rt] = c[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        DFS(v[i].END, rt);
        size[rt] += size[v[i].END];
        vi[rt] += v[i].v * size[v[i].END] + vi[v[i].END];
    }
}
int ans = 0x3f3f3f3f3f3f3f3fll;
void DP(int rt, int fa, int S)
{
    ans = min(S, ans);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        DP(v[i].END, rt, S + v[i].v * (size[1] - size[v[i].END]) - v[i].v * size[v[i].END]);
    }
}
signed main()
{
    memset(first, -1, sizeof(first));
    int n, a, b, d;
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &c[i]);
    for (int i = 1; i < n; i++)
    {
        scanf("%lld%lld%lld", &a, &b, &d);
        add(a, b, d);
        add(b, a, d);
    }
    DFS(1, 0);
    DP(1, 0, vi[1]);
    printf("%lld", ans);
}
// Problem2305:
#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MOD = 45989;
struct Marmix
{
    long long a[205][205];
    int n, m;
    Marmix(int x = 0, int y = 0)
    {
        memset(a, 0, sizeof(a));
        n = x, m = y;
    }
    Marmix operator*(const Marmix &a)
    {
        if (a.n != m)
        {
            printf("ERROR\n");
            system("pause");
            exit(0);
        }
        Marmix ans(n, a.m);
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= a.m; i++)
            {
                for (int j = 1; j <= a.n; j++)
                {
                    ans.a[k][i] += (this->a[k][j]) * a.a[j][i];
                    //ans.a[k][i] = ans.a[k][i] % MOD;
                }
                ans.a[k][i] = ans.a[k][i] % MOD;
            }
        }
        return ans;
    }
};
struct edge
{
    int END, next, START;
} v[600];
int first[25], p;
void add(int a, int b)
{
    v[p].START = a;
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
#define LL long long
using namespace std;
int n, m;
Marmix pow_mod(Marmix a, LL b)
{
    Marmix ans(p, p);
    for (int i = 1; i <= p; i++)
        ans.a[i][i] = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a;
        b >>= 1;
        a = a * a;
    }
    return ans;
}
int main()
{
    memset(first, -1, sizeof(first));
    // freopen("walker.in", "r", stdin);
    // freopen("walker.out", "w", stdout);
    int A, B;
    long long t;
    scanf("%d%d%lld%d%d", &n, &m, &t, &A, &B);
    int s, e;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s, &e);
        add(s, e);
        add(e, s);
    }
    Marmix a(p, p);
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < p; j++)
        {
            if (v[i].END == v[j].START && (i ^ 1) != j)
                a.a[i + 1][j + 1] = 1;
        }
    }
    Marmix T(1, p);
    for (int i = first[A]; i != -1; i = v[i].next)
    {
        T.a[1][i + 1] = 1;
    }
    //for(int i=1;i<=n;i++)a.a[i][i]+=1;
    a = pow_mod(a, t - 1);
    Marmix ans;
    ans = T * a;
    LL sum = 0;
    for (int i = 0; i < p; i++)
    {
        if (v[i].END == B)
            sum += ans.a[1][i + 1];
    }
    printf("%lld\n", sum % MOD);
    //while (1)
    ;
}

// Problem2306:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int base = 100000000;
struct BigNum
{
    long long a[10010];
    int len;
    BigNum(const char *s = "")
    {
        int sum = 0, su = 1;
        int n = strlen(s);
        for (int j = n - 1; j >= 0; j--)
        {
            sum += (s[j] - '0') * su;
            su *= 10;
            if (su == base)
            {
                a[++len] = sum;
                sum = 0, su = 1;
            }
        }
        if (sum != 0 || len == 0)
            a[++len] = sum;
    }
    BigNum operator-(const BigNum &b) const
    {
        BigNum ans = *this;
        int m = max(len, b.len);
        for (int i = 1; i <= m; i++)
        {
            if (ans.a[i] < b.a[i])
                ans.a[i + 1] -= 1, ans.a[i] += base;
            ans.a[i] -= b.a[i];
        }
        while (ans.len > 1 && ans.a[ans.len] == 0)
            ans.len--;
        return ans;
    }
    bool operator<(const BigNum &b) const
    {
        if (b.len > len)
            return 1;
        if (len > b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] < b.a[i])
                return 1;
            else if (a[i] > b.a[i])
                return 0;
        return 0;
    }
    bool operator==(const BigNum &b) const
    {
        if (len != b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 0;
        return 1;
    }
    bool operator!=(const BigNum &b) const
    {
        if (len != b.len)
            return 1;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 1;
        return 0;
    }
};
BigNum GCD(const BigNum &a, const BigNum &b)
{
    if (a == b)
        return a;
    if (a < b)
        return GCD(a, b - a);
    else
        return GCD(b, a - b);
}
int main()
{
    static char s[10010];
    scanf("%s", s);
    static BigNum a(s);
    scanf("%s", s);
    static BigNum b(s);
    while (a != b)
    {
        if (b < a)
            a = a - b;
        else
            b = b - a;
    }
    printf("%lld", a.a[a.len]);
    for (int i = a.len - 1; i >= 1; i--)
        printf("%08lld", a.a[i]);
}
// Problem2306:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int base = 1000000000;
struct BigNum
{
    long long a[1505];
    int len;
    BigNum(const char *s = "")
    {
        int sum = 0, su = 1;
        int n = strlen(s);
        for (int j = n - 1; j >= 0; j--)
        {
            sum += (s[j] - '0') * su;
            su *= 10;
            if (su == base)
            {
                a[++len] = sum;
                sum = 0, su = 1;
            }
        }
        if (sum != 0 || len == 0)
            a[++len] = sum;
    }
    BigNum operator-(const BigNum &b) const
    {
        BigNum ans = *this;
        int m = max(len, b.len);
        for (int i = 1; i <= m; i++)
        {
            if (ans.a[i] < b.a[i])
                ans.a[i + 1] -= 1, ans.a[i] += base;
            ans.a[i] -= b.a[i];
        }
        while (ans.len > 1 && ans.a[ans.len] == 0)
            ans.len--;
        return ans;
    }
    bool operator<(const BigNum &b) const
    {
        if (b.len > len)
            return 1;
        if (len > b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] < b.a[i])
                return 1;
            else if (a[i] > b.a[i])
                return 0;
        return 0;
    }
    bool operator==(const BigNum &b) const
    {
        if (len != b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 0;
        return 1;
    }
    bool operator!=(const BigNum &b) const
    {
        if (len != b.len)
            return 1;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 1;
        return 0;
    }
};
int main()
{
    static char s[10010];
    scanf("%s", s);
    static BigNum a(s);
    scanf("%s", s);
    static BigNum b(s);
    while (a != b)
    {
        if (b < a)
            a = a - b;
        else
            b = b - a;
    }
    printf("%lld", a.a[a.len]);
    for (int i = a.len - 1; i >= 1; i--)
        printf("%09lld", a.a[i]);
}
// Problem2306:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long base = 10000000000000000;
struct BigNum
{
    long long a[1505];
    int len;
    BigNum(const char *s = "")
    {
        long long sum = 0, su = 1;
        int n = strlen(s);
        for (int j = n - 1; j >= 0; j--)
        {
            sum += (s[j] - '0') * su;
            su *= 10;
            if (su == base)
            {
                a[++len] = sum;
                sum = 0, su = 1;
            }
        }
        if (sum != 0 || len == 0)
            a[++len] = sum;
    }
    BigNum operator-(const BigNum &b) const
    {
        BigNum ans = *this;
        int m = max(len, b.len);
        for (int i = 1; i <= m; i++)
        {
            if (ans.a[i] < b.a[i])
                ans.a[i + 1] -= 1, ans.a[i] += base;
            ans.a[i] -= b.a[i];
        }
        while (ans.len > 1 && ans.a[ans.len] == 0)
            ans.len--;
        return ans;
    }
    bool operator<(const BigNum &b) const
    {
        if (b.len > len)
            return 1;
        if (len > b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] < b.a[i])
                return 1;
            else if (a[i] > b.a[i])
                return 0;
        return 0;
    }
    bool operator==(const BigNum &b) const
    {
        if (len != b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 0;
        return 1;
    }
    bool operator!=(const BigNum &b) const
    {
        if (len != b.len)
            return 1;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 1;
        return 0;
    }
};
int main()
{
    static char s[10010];
    scanf("%s", s);
    static BigNum a(s);
    scanf("%s", s);
    static BigNum b(s);
    while (a != b)
    {
        if (b < a)
            a = a - b;
        else
            b = b - a;
    }
    printf("%lld", a.a[a.len]);
    for (int i = a.len - 1; i >= 1; i--)
        printf("%016lld", a.a[i]);
}
// Problem2306:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long base = 1000000000000000000;
struct BigNum
{
    long long a[1505];
    int len;
    BigNum(const char *s = "")
    {
        long long sum = 0, su = 1;
        int n = strlen(s);
        for (int j = n - 1; j >= 0; j--)
        {
            sum += (s[j] - '0') * su;
            su *= 10;
            if (su == base)
            {
                a[++len] = sum;
                sum = 0, su = 1;
            }
        }
        if (sum != 0 || len == 0)
            a[++len] = sum;
    }
    BigNum operator-(const BigNum &b) const
    {
        BigNum ans = *this;
        int m = max(len, b.len);
        for (int i = 1; i <= m; i++)
        {
            if (ans.a[i] < b.a[i])
                ans.a[i + 1] -= 1, ans.a[i] += base;
            ans.a[i] -= b.a[i];
        }
        while (ans.len > 1 && ans.a[ans.len] == 0)
            ans.len--;
        return ans;
    }
    bool operator<(const BigNum &b) const
    {
        if (b.len > len)
            return 1;
        if (len > b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] < b.a[i])
                return 1;
            else if (a[i] > b.a[i])
                return 0;
        return 0;
    }
    bool operator==(const BigNum &b) const
    {
        if (len != b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 0;
        return 1;
    }
    bool operator!=(const BigNum &b) const
    {
        if (len != b.len)
            return 1;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 1;
        return 0;
    }
};
int main()
{
    static char s[10010];
    scanf("%s", s);
    static BigNum a(s);
    scanf("%s", s);
    static BigNum b(s);
    while (a != b)
    {
        if (b < a)
            a = a - b;
        else
            b = b - a;
    }
    printf("%lld", a.a[a.len]);
    for (int i = a.len - 1; i >= 1; i--)
        printf("%018lld", a.a[i]);
}
// Problem2309:
#include <iostream>
#include <cstring>
#include <cstdio>
#include "time.h"
using namespace std;
int f[51][1 << 15];
int g[55][27];
char s[16][55];
int find_1(int x)
{
    int cut = 0;
    while (x > 0)
    {
        cut++;
        x &= (x - 1);
    }
    return cut;
}
int main()
{
    //freopen("set.in","r",stdin);
    //freopen("set.out","w",stdout);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        int n, K;
        scanf("%d%d", &n, &K);
        for (int i = 1; i <= n; i++)
            scanf("%s", s[i]);
        int len = strlen(s[1]);
        //printf("%c %c",s[1][0],s[1][1]);
        for (int i = 0; i < len; i++)
            for (int j = 1; j <= 26; j++)
                for (int k = 1; k <= n; k++)
                    if ((s[k][i] - 'a' + 1) == j || s[k][i] == '?')
                        g[i][j] ^= (1 << k - 1);
        /*freopen("1.txt","w",stdout);
		for(int i=0;i<len;i++){
			for(int j=1;j<=26;j++){
				printf("%d ",g[i][j]);
			}
			printf("\n");
		}
		fclose(stdout);*/
        int N = (1 << n) - 1;
        f[0][N] = 1;
        for (int i = 0; i < len; i++)
        {
            for (int S = 0; S <= N; S++)
            {
                for (int k = 1; k <= 26; k++)
                {
                    f[i + 1][S & g[i][k]] += f[i][S];
                    f[i + 1][S & g[i][k]] %= 1000003;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i <= N; i++)
        {
            if (find_1(i) == K)
            {
                ans += f[len][i];
                ans %= 1000003;
            }
        }
        printf("%d\n", ans);
    }
    //printf("%lf",(double)clock()/CLOCKS_PER_SEC);
    //while(1);
}
// Problem2394:
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <list>
#include <cstdlib>
int n, m, T, D_F, Z_D_to_M;
char C[2005];
// #define Log 1
namespace Pig
{
bool Died[11];
struct Pig_data
{
    /*
        Id :
            1: ä¸»çŒª
            2: å¿ çŒª
            3: åçŒª
        */
    std::list<char> Card;
    std::list<char>::iterator it;
    int Identity, Strength;
    bool Equipped, Jump, Similar;
    void init(int Id, char *s)
    {
        Strength = 4, Similar = 0;
        Identity = Id;
        if (Id == 1)
            Jump = 1;
        for (int i = 1; i <= 4; i++)
            Card.push_back(s[i]);
    }
    void Print()
    {
        for (it = Card.begin(); it != Card.end(); it++)
            printf("%c ", *it);
        printf("\n");
    }
} Pig[11];
}
namespace Card
{
struct Card_Heap_data
{
    char Card_Heap[2005];
    int h, t;
    void init(char *s, int Num)
    {
        t = Num;
        h = 0;
        for (int i = 1; i <= Num; i++)
            Card_Heap[i] = s[i];
    }
    char Get_Card()
    {
        if (h == t)
            return Card_Heap[h];
        else
            return Card_Heap[++h];
    }
} Card;
}
namespace Main
{
void Read_init()
{
#ifdef Log
    printf("===========================================\n Read Start\n=================================\n");
#endif
    scanf("%d%d", &::n, &::m);
    char s[5], ID[4];
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", ID);
        for (int j = 1; j <= 4; j++)
            std::cin >> s[j];
        if (ID[0] == 'M')
            Pig::Pig[i].init(1, s);
        else if (ID[0] == 'Z')
            Pig::Pig[i].init(2, s);
        else
            Pig::Pig[i].init(3, s), T++;
    }
#ifdef Log
    printf("===========================================\n Read Pig Succeed\n=================================\n");
#endif
    memset(Pig::Died, 0, sizeof(Pig::Died));
    for (int i = 1; i <= m; i++)
        std::cin >> C[i];
#ifdef Log
    printf("===========================================\n Read Card Succeed\n=================================\n");
#endif
    Card::Card.init(C, m);
#ifdef Log
    printf("===========================================\nCard Init Succeed\n=================================\n");
#endif
}
void Get_Card(int x, int t)
{
#ifdef Log
    printf("Pig %d Get %d Card\n", x, t);
#endif
    while (t--)
    {
        Pig::Pig[x].Card.push_back(Card::Card.Get_Card());
    }
}
int nxt[11];
int next(int x)
{
    if (nxt[x] != 0)
        return nxt[x];
    for (int i = x + 1;; i++)
    {
        if (i == n + 1)
            i = 1;
        if (!Pig::Died[i])
            return nxt[x] = i;
    }
}
std::list<char>::iterator it, it2, searchit, eraseit;
bool Over(int &W)
{
    bool No_Fan = 1;
    int now = 0;
    if (Pig::Died[1])
        return W = 1, 1;
    else
        now = 1;
    int Next_Pig = now;
    do
    {
        if (Pig::Pig[Next_Pig].Identity == 3)
            No_Fan = 0;
        Next_Pig = next(Next_Pig);
    } while (Next_Pig != now);
    if (No_Fan)
        return W = 0, 1;
    else
        return 0;
}
bool Judge(int x, char c, int K_Num, int &t)
{
    if (c == 'P')
    {
        if (Pig::Pig[x].Strength != 4)
            return t = x, 1;
        else
            return 0;
    }
    else if (c == 'K')
    {
        if (K_Num && !Pig::Pig[x].Equipped)
            return 0;
        if (Pig::Pig[x].Identity == 1)
        {
            if (Pig::Pig[next(x)].Similar)
                return t = next(x), 1;
            if (Pig::Pig[next(x)].Identity == 3 && Pig::Pig[next(x)].Jump)
                return t = next(x), 1;
            else
                return 0;
        }
        else if (Pig::Pig[x].Identity == 2)
        {
            if (Pig::Pig[next(x)].Identity == 3 && Pig::Pig[next(x)].Jump)
                return t = next(x), 1;
            else
                return 0;
        }
        else if (Pig::Pig[x].Identity == 3)
        {
            if ((Pig::Pig[next(x)].Identity == 1 || Pig::Pig[next(x)].Identity == 2) && Pig::Pig[next(x)].Jump)
                return t = next(x), 1;
            else
                return 0;
        }
        else
        {
            printf("ERROR No Identity\n");
        }
    }
    else if (c == 'D')
        return 0;
    else if (c == 'F')
    {
        bool flag = 0;
        int Next_Pig = next(x);
        while (Next_Pig != x)
        {
            if (Pig::Pig[x].Identity == 1)
            {
                if (Pig::Pig[Next_Pig].Similar)
                    return t = Next_Pig, 1;
                if (Pig::Pig[Next_Pig].Identity == 3 && Pig::Pig[Next_Pig].Jump)
                    return t = Next_Pig, 1;
                else
                    goto Restart;
            }
            else if (Pig::Pig[x].Identity == 2)
            {
                if (Pig::Pig[Next_Pig].Identity == 3 && Pig::Pig[Next_Pig].Jump)
                    return t = Next_Pig, 1;
                else
                    goto Restart;
            }
            else if (Pig::Pig[x].Identity == 3)
            {
                if (Pig::Pig[Next_Pig].Identity == 1)
                    return t = Next_Pig, 1;
                else if (Pig::Pig[Next_Pig].Identity == 2 && Pig::Pig[Next_Pig].Jump)
                {
                    if (!flag)
                        flag = 1, t = Next_Pig;
                    goto Restart;
                }
                else
                    goto Restart;
            }
            else
            {
                printf("ERROR No Identity\n");
            }
        Restart:
            Next_Pig = next(Next_Pig);
        }
        if (Pig::Pig[x].Identity == 3 && flag)
            return 1;
        else
            return 0;
    }
    else if (c == 'N' || c == 'W')
    {
        return t = -1, 1;
    }
    else if (c == 'J')
        return 0;
    else if (c == 'Z')
        return t = x, 1;
    else
    {
        printf("ERROR in Card ID\n");
        exit(0);
        return 0;
    }
    return 0;
}
bool Have(char c, int t) // and erase
{
#ifdef Log
    printf("It's %d to return He have ", t);
    Pig::Pig[t].Print();
#endif
    for (searchit = Pig::Pig[t].Card.begin(); searchit != Pig::Pig[t].Card.end(); searchit++)
        if (*searchit == c)
        {
#ifdef Log
            printf("Pig %d Used %c\n", t, c);
#endif
            return Pig::Pig[t].Card.erase(searchit), 1;
        }
    return 0;
}
bool Need_Wuxie(int x)
{
    if (!Have('J', x))
        return 0;
    Pig::Pig[x].Jump = 1;
    Pig::Pig[x].Similar = 0;
    return 1;
}
bool Wuxie(int x, bool op)
{
    int Next_Pig = x;
    do
    {
        if ((op == 0 && Pig::Pig[Next_Pig].Identity == 3) || (op == 1 && Pig::Pig[Next_Pig].Identity != 3))
        {
            if (!Need_Wuxie(Next_Pig))
                goto again;
            if (!Wuxie(Next_Pig, op ^ 1))
                return 1;
            return 0;
        }
    again:
        Next_Pig = next(Next_Pig);
    } while (Next_Pig != x);
    return 0;
}
bool Okforwuxie(int x, int t)
{
    if (!Pig::Pig[t].Jump)
        return 0;
    if (Pig::Pig[t].Identity == 3)
        return Wuxie(x, 0);
    else
        return Wuxie(x, 1);
}
void UseM(int x, char c, int t)
{
    if (c == 'K')
    {
#ifdef Log
        printf("Pig %d use %c to %d\n", x, c, t);
#endif
        if (Pig::Pig[t].Jump)
            Pig::Pig[x].Jump = 1;
        if (!Have('D', t))
        {
#ifdef Log
            printf("Pig %d not have %c\n", t, 'D');
#endif // Log
            Pig::Pig[t].Strength--;
#ifdef Log
            printf("Pig %d HP = %d\n", t, Pig::Pig[t].Strength);
#endif // Log
            if (Pig::Pig[t].Strength == 0)
            {
                if (!Have('P', t))
                {
#ifdef Log
                    printf("Pig %d Died\n", t);
#endif // Log
                    Pig::Died[t] = 1;
                    memset(nxt, 0, sizeof(nxt));
                    if (Pig::Died[1] == 1)
                        return;
                    if (Pig::Pig[t].Identity == 2 && Pig::Pig[x].Identity == 1)
                    {
                        Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                        Z_D_to_M = 1;
                    }
                    if (Pig::Pig[t].Identity == 3)
                    {
                        D_F++;
                        if (D_F == T)
                            return;
                        Get_Card(x, 3);
                    }
                }
                else
                    Pig::Pig[t].Strength = 1;
            }
        }
        return;
    }
    else if (c == 'P')
        return Pig::Pig[x].Strength++, void(0);
    else if (c == 'F')
    {
#ifdef Log
        printf("Pig %d use %c to %d\n", x, c, t);
#endif
        Pig::Pig[x].Jump = 1, Pig::Pig[x].Similar = 0;
        if (Pig::Pig[x].Identity == 1 && Pig::Pig[t].Identity == 2)
        {
            Pig::Pig[t].Strength--;
#ifdef Log
            printf("Pig %d HP = %d\n", t, Pig::Pig[t].Strength);
#endif // Log
            if (Pig::Pig[t].Strength == 0)
            {
                if (!Have('P', t))
                {
#ifdef Log
                    printf("Pig %d Died\n", t);
#endif // Log
                    Pig::Died[t] = 1;
                    memset(nxt, 0, sizeof(nxt));
                    if (Pig::Died[1] == 1)
                        return;
                    if (Pig::Pig[t].Identity == 2 && Pig::Pig[x].Identity == 1)
                    {
                        Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                        Z_D_to_M = 1;
                    }
                    if (Pig::Pig[t].Identity == 3)
                    {
                        D_F++;
                        if (D_F == T)
                            return;
                        Get_Card(t, 3);
                    }
                }
                else
                    Pig::Pig[t].Strength = 1;
            }
            return;
        }
        if (Okforwuxie(x, t))
            return void(0);
        while (1)
        {
            if (!Have('K', t))
            {
                Pig::Pig[t].Strength--;
#ifdef Log
                printf("Pig %d HP = %d\n", t, Pig::Pig[t].Strength);
#endif // Log
                if (Pig::Pig[t].Strength == 0)
                {
                    if (!Have('P', t))
                    {
#ifdef Log
                        printf("Pig %d Died\n", t);
#endif // Log
                        Pig::Died[t] = 1;
                        memset(nxt, 0, sizeof(nxt));
                        if (Pig::Died[1] == 1)
                            return;
                        if (Pig::Pig[t].Identity == 2 && Pig::Pig[x].Identity == 1)
                        {
                            Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                            Z_D_to_M = 1;
                        }
                        if (Pig::Pig[t].Identity == 3)
                        {
                            D_F++;
                            if (D_F == T)
                                return;
                            Get_Card(x, 3);
                        }
                    }
                    else
                        Pig::Pig[t].Strength = 1;
                }
                return;
            }
            if (!Have('K', x))
            {
                Pig::Pig[x].Strength--;
#ifdef Log
                printf("Pig %d HP = %d\n", x, Pig::Pig[x].Strength);
#endif // Log
                if (Pig::Pig[x].Strength == 0)
                {
                    if (!Have('P', x))
                    {
#ifdef Log
                        printf("Pig %d Died\n", x);
#endif // Log
                        Pig::Died[x] = 1;
                        memset(nxt, 0, sizeof(nxt));
                        if (Pig::Died[1] == 1)
                            return;
                        if (Pig::Pig[x].Identity == 2 && Pig::Pig[t].Identity == 1)
                        {
                            Pig::Pig[t].Card.clear(), Pig::Pig[t].Equipped = 0;
                            Z_D_to_M = 1;
                        }
                        if (Pig::Pig[x].Identity == 3)
                        {
                            D_F++;
                            if (D_F == T)
                                return;
                            Get_Card(t, 3);
                            return;
                        }
                    }
                    else
                        Pig::Pig[x].Strength = 1;
                }
                return;
            }
        }
    }
    else if (c == 'N')
    {
#ifdef Log
        printf("Pig %d use %c to %d\n", x, c, t);
#endif
        int Next_Pig = next(x);
        do
        {
            if (Okforwuxie(x, Next_Pig))
                goto END1;
            if (!Have('K', Next_Pig))
            {
                Pig::Pig[Next_Pig].Strength--;
#ifdef Log
                printf("Pig %d HP = %d\n", Next_Pig, Pig::Pig[Next_Pig].Strength);
#endif // Log
                if (Pig::Pig[Next_Pig].Strength == 0)
                {
                    if (!Have('P', Next_Pig))
                    {
#ifdef Log
                        printf("Pig %d Died\n", Next_Pig);
#endif // Log
                        memset(nxt, 0, sizeof(nxt));
                        Pig::Died[Next_Pig] = 1;
                        if (Pig::Died[1] == 1)
                            return;
                        if (Pig::Pig[Next_Pig].Identity == 2 && Pig::Pig[x].Identity == 1)
                        {
                            Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                            Z_D_to_M = 1;
                        }
                        if (Pig::Pig[Next_Pig].Identity == 3)
                        {
                            D_F++;
                            if (D_F == T)
                                return;
                            Get_Card(x, 3);
                        }
                    }
                    else
                        Pig::Pig[Next_Pig].Strength = 1;
                }
                if (Pig::Pig[Next_Pig].Identity == 1 && Pig::Pig[x].Jump == 0)
                    Pig::Pig[x].Similar = 1;
            }
        END1:
            Next_Pig = next(Next_Pig);
        } while (Next_Pig != x);
        return;
    }
    else if (c == 'W')
    {
#ifdef Log
        printf("Pig %d use %c to %d\n", x, c, t);
#endif
        int Next_Pig = next(x);
        do
        {
            if (Okforwuxie(x, Next_Pig))
                goto END2;
            if (!Have('D', Next_Pig))
            {
                Pig::Pig[Next_Pig].Strength--;
#ifdef Log
                printf("Pig %d HP = %d\n", Next_Pig, Pig::Pig[Next_Pig].Strength);
#endif // Log
                if (Pig::Pig[Next_Pig].Strength == 0)
                {
                    if (!Have('P', Next_Pig))
                    {
#ifdef Log
                        printf("Pig %d Died\n", Next_Pig);
#endif // Log
                        Pig::Died[Next_Pig] = 1;
                        memset(nxt, 0, sizeof(nxt));
                        if (Pig::Died[1] == 1)
                            return;
                        if (Pig::Pig[Next_Pig].Identity == 2 && Pig::Pig[x].Identity == 1)
                        {
                            Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                            Z_D_to_M = 1;
                        }
                        if (Pig::Pig[Next_Pig].Identity == 3)
                        {
                            D_F++;
                            if (D_F == T)
                                return;
                            Get_Card(x, 3);
                        }
                    }
                    else
                        Pig::Pig[Next_Pig].Strength = 1;
                }
                if (Pig::Pig[Next_Pig].Identity == 1 && Pig::Pig[x].Jump == 0)
                    Pig::Pig[x].Similar = 1;
            }
        END2:
            Next_Pig = next(Next_Pig);
        } while (Next_Pig != x);
        return;
    }
    else if (c == 'Z')
        return Pig::Pig[x].Equipped = 1, void(0);
}
void Use(int x, char c, int t)
{
    UseM(x, c, t);
    // printf("ERROR in Use at Identity, There is no Id in the Pig\n");
}
void Play(int x)
{
    it = Pig::Pig[x].Card.begin();
    int K_Num = 0;
    int Y = D_F;
    for (; it != Pig::Pig[x].Card.end(); it = it2)
    {
        int t = 0;
        if (Judge(x, *it, K_Num, t))
        {
#ifdef Log
            printf("Pig %d Used %c to %d\n", x, *it, t);
#endif
            Use(x, *it, t);
            if (Z_D_to_M)
                return;
            if (*it == 'K')
                K_Num++;
            Pig::Pig[x].Card.erase(it);
            it2 = Pig::Pig[x].Card.begin();
            if (Pig::Died[1] == 1 || Pig::Died[x] == 1 || D_F == T)
                return;
        }
        else
        {
            it2 = it;
            it2++;
        }
    }
}
void Run()
{
    int now = 1, W = 0;
    while (!Over(W))
    {
#ifdef Log
        printf("It is %d Paly, It's Identity is %d ", now, Pig::Pig[now].Identity);
        if (Pig::Pig[now].Jump == 1)
            printf("He Jumped\n");
        else
            printf("He not Jumped\n");
#endif // Log
        Get_Card(now, 2);
#ifdef Log
        printf("He has ");
        Pig::Pig[now].Print();
#endif
        Play(now);
        Z_D_to_M = 0;
        now = next(now);
    }
    if (W == 0)
    {
        printf("MP\n");
        for (int i = 1; i <= n; i++)
        {
            if (Pig::Died[i])
                printf("DEAD\n");
            else
                Pig::Pig[i].Print();
        }
    }
    else
    {
        printf("FP\n");
        for (int i = 1; i <= n; i++)
        {
            if (Pig::Died[i])
                printf("DEAD\n");
            else
                Pig::Pig[i].Print();
        }
    }
}
}
int main()
{
// freopen("kopk10.in", "r", stdin);
// freopen("1.out", "w", stdout);
#ifdef Log
    printf("======================================\n Start\n======================================\n");
#endif
    Main::Read_init();
#ifdef Log
    printf("Read Success\n\n");
    printf("======================================\nGame Start\n\n");
#endif
    Main::Run();
}
// Problem2422:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, m, k[200005], block;
int in[200005], next[200005], times[200005], l[200005];
int main()
{
    //freopen("1.in","r",stdin);
    //scanf("%d", &n);
    n = read();
    block = sqrt(n);
    for (int i = 0; i < n; i++)
    {
        k[i] = read();
        //scanf("%d", k + i);
        in[i] = i / block + 1;
        l[i] = (in[i] - 1) * block;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (i + k[i] > n)
        {
            times[i] = 1;
            next[i] = n;
        }
        else if (in[i] == in[i + k[i]])
        {
            times[i] = times[i + k[i]] + 1;
            next[i] = next[i + k[i]];
        }
        else
        {
            times[i] = 1;
            next[i] = i + k[i];
        }
    }
    //scanf("%d", &m);
    m = read();
    int op, s;
    while (m--)
    {
        //scanf("%d", &op);
        op = read();
        if (op == 1)
        {
            //scanf("%d", &s);
            s = read();
            int ans = 0;
            for (int i = s; i < n; i = next[i])
            {
                ans += times[i];
            }
            printf("%d\n", ans);
        }
        else
        {
            //scanf("%d%d", &s, &c);
            //k[s] = c;
            s = read();
            k[s] = read();
            for (int i = s; i >= l[s]; i--)
            {
                if (i + k[i] > n)
                {
                    times[i] = 1;
                    next[i] = i + k[i];
                }
                if (in[i] == in[i + k[i]])
                {
                    times[i] = times[i + k[i]] + 1;
                    next[i] = next[i + k[i]];
                }
                else
                {
                    times[i] = 1;
                    next[i] = i + k[i];
                }
            }
        }
    }
    //printf("%lf", (double)clock() / CLOCKS_PER_SEC);
}
// Problem2424:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 30031;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct Matrix
{
    int a[150][150];
    int n, m;
    Matrix(int x = 0, int y = 0)
    {
        memset(a, 0, sizeof(a));
        n = x, m = y;
    }
    const int *operator[](const int &b) const
    {
        return a[b];
    }
    int *operator[](const int &b)
    {
        return a[b];
    }
    Matrix operator*(const Matrix &b)
    {
        Matrix ans(n, b.m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                if (a[i][j] == 0)
                    continue;
                for (int k = 1; k <= b.m; k++)
                    ans[i][k] += a[i][j] * b[j][k] % MOD;
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= b.m; j++)
                ans[i][j] %= MOD;
        return ans;
    }
    Matrix operator^(int b)
    {
        Matrix ans(n, n), a = *this;
        for (int i = 1; i <= n; i++)
            ans[i][i] = 1;
        while (b)
        {
            if (b & 1)
                ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
};
int mp[(1 << 10) + 1], Id[(1 << 10) + 1];
int n, k, p;
bool OK(int x)
{
    if (!(x & 1))
        return 0;
    int t = 0;
    for (int i = 0; i < p; i++)
        if (x & (1 << i))
            t++;
    return t == k;
}
int F[2][(1 << 10) + 1];
int main()
{
    n = read(), k = read(), p = read();
    int N = (1 << p) - 1;
    int cnt = 0;
    for (int i = 1; i <= N; i++)
        if (OK(i))
            mp[++cnt] = i, Id[i] = cnt;
    static Matrix T(cnt, cnt);
    for (int i = 1; i <= cnt; i++)
    {
        int x = mp[i] >> 1;
        for (int j = 0; j < p; j++)
        {
            if ((1 << j) & x)
                continue;
            if (!Id[x | (1 << j)])
                continue;
            T[i][Id[x | (1 << j)]] = 1;
        }
    }
    int s = 0;
    for (int i = 0; i < k; i++)
        s |= (1 << i);
    static Matrix A(1, cnt);
    A[1][Id[s]] = 1;
    A = A * (T ^ (n - k));
    T = T ^ (n - k);
    // for (int i = 1; i <= cnt; i++)
    //     F[0][mp[i]] = A[1][i];
    // int now = 0;
    // for (int i = 1; i <= p - k; i++)
    // {
    //     now ^= 1;
    //     for (int j = 1; j <= N; j++)
    //     {
    //         if (F[now ^ 1][j])
    //         {
    //             int x = j >> 1;
    //             for (int l = 0; l < p - i; l++)
    //                 if (!(x & (1 << l)))
    //                     (F[now][x | (1 << l)] += F[now ^ 1][j]) %= MOD;
    //         }
    //     }
    // }
    // printf ("%d\n", F[now][s]);
    printf("%d\n", A[1][Id[s]]);
}
// Problem2424:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 30031;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct Matrix
{
    int a[150][150];
    int n, m;
    Matrix(int x = 0, int y = 0)
    {
        memset(a, 0, sizeof(a));
        n = x, m = y;
    }
    const int *operator[](const int &b) const
    {
        return a[b];
    }
    int *operator[](const int &b)
    {
        return a[b];
    }
    Matrix operator*(const Matrix &b)
    {
        Matrix ans(n, b.m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                if (a[i][j] == 0)
                    continue;
                for (int k = 1; k <= b.m; k++)
                    ans[i][k] += a[i][j] * b[j][k] % MOD;
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= b.m; j++)
                ans[i][j] %= MOD;
        return ans;
    }
    Matrix operator^(int b)
    {
        Matrix ans(n, n), a = *this;
        for (int i = 1; i <= n; i++)
            ans[i][i] = 1;
        while (b)
        {
            if (b & 1)
                ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
};
int mp[(1 << 10) + 1], Id[(1 << 10) + 1];
int n, k, p;
bool OK(int x)
{
    if (!(x & 1))
        return 0;
    int t = 0;
    for (int i = 0; i < p; i++)
        if (x & (1 << i))
            t++;
    return t == k;
}
int F[2][(1 << 10) + 1];
int main()
{
    n = read(), k = read(), p = read();
    int N = (1 << p) - 1;
    int cnt = 0;
    for (int i = 1; i <= N; i++)
        if (OK(i))
            mp[++cnt] = i, Id[i] = cnt;
    static Matrix T(cnt, cnt);
    for (int i = 1; i <= cnt; i++)
    {
        int x = mp[i] >> 1;
        for (int j = 0; j < p; j++)
        {
            if ((1 << j) & x)
                continue;
            if (!Id[x | (1 << j)])
                continue;
            T[i][Id[x | (1 << j)]] = 1;
        }
    }
    int s = 0;
    for (int i = 0; i < k; i++)
        s |= (1 << i);
    static Matrix A(1, cnt);
    A[1][Id[s]] = 1;
    A = A * (T ^ (n - k));
    printf("%d\n", A[1][Id[s]]);
}
// Problem2433:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 620005;
const int MOD = 1e9 + 9;
int a[N];
int main()
{
    int n, d;
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    long long ans = 1;
    for (int i = 1, j = 1; i <= n; i++)
    {
        while (j <= n && a[j] < a[i] - d)
            j++;
        ans = ans * (i - j + 1) % MOD;
    }
    printf("%lld", ans);
}
// Problem2453:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int pos[5005], link[5005];
struct data
{
    int x, y, z, s;
} a[5005];
bool cmpx(const data &b, const data &c)
{
    return b.x < c.x;
}
bool cmpz(const data &b, const data &c)
{
    return b.z > c.z;
}
bool check(int k, int x)
{
    if (pos[x] > a[k].y)
        return 0;
    if (!link[x])
    {
        link[x] = k;
        return 1;
    }
    else
    {
        if (a[link[x]].y < a[k].y)
            return check(k, x + 1);
        else if (check(link[x], x + 1))
        {
            link[x] = k;
            return 1;
        }
        else
            return 0;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
    sort(a + 1, a + n + 1, cmpx);
    for (int i = 1; i <= n; i++)
        pos[i] = max(pos[i - 1] + 1, a[i].x);
    a[1].s = 1;
    for (int i = 2; i <= n; i++)
    {
        a[i].s = a[i - 1].s;
        while (pos[a[i].s] < a[i].x && a[i].s < n)
            a[i].s++;
    }
    sort(a + 1, a + n + 1, cmpz);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (check(i, a[i].s))
            ans += a[i].z;
    printf("%lld\n", ans);
}
// Problem2470:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int c[100005], n;
#define lowbit(_) ((_) & (-_))
void add(int x, int add)
{
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += add;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        ans += c[i];
    return ans;
}
int a[100005], pos[100005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        pos[a[i]] = i;
    }
    long long Sum = 0;
    for (int i = n; i >= 1; i--)
    {
        Sum += Query(a[i] - 1);
        add(a[i], 1);
    }
    long long ans = Sum;
    for (int i = 1; i < n; i++)
    {
        Sum = Sum - pos[i] + 1 + n - pos[i];
        ans = min(ans, Sum);
    }
    printf("%lld", ans);
}
// Problem2483:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int t[20], w[20];
int Sum[65537], T[65537];
int F[65537];
int main()
{
    int W = read(), n = read();
    for (int i = 1; i <= n; i++)
        t[i] = read(), w[i] = read();
    int N = (1 << n) - 1;
    for (int i = 1; i <= N; i++)
    {
        int j = 0;
        for (j = 1; j <= n; j++)
            if (i & (1 << (j - 1)))
                break;
        Sum[i] = Sum[i ^ (1 << (j - 1))] + w[j];
        T[i] = max(T[i ^ (1 << (j - 1))], t[j]);
    }
    memset(F, 0x3f, sizeof(F));
    F[0] = 0;
    for (int i = 1; i <= N; i++)
        for (int j = i; j; j = (j - 1) & i)
            if (Sum[j] <= W)
                F[i] = min(F[i], F[j ^ i] + T[j]);
    printf("%d\n", F[N]);
}
// Problem2500:
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MaxN = 1000000;
int Max1[MaxN + 5], Max2[MaxN + 5], Max3[MaxN + 5];
#define lowbit(_) ((_) & (-_))
void Update1(int a, int b)
{
    for (int i = a; i <= MaxN; i += lowbit(i))
    {
        Max1[i] = max(b, Max1[i]);
    }
}
void Update2(int a, int b)
{
    for (int i = a; i > 0; i -= lowbit(i))
    {
        Max2[i] = max(b, Max2[i]);
    }
}
int MAX1(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        ans = max(ans, Max1[i]);
    }
    return ans;
}
int MAX2(int x)
{
    int ans = 0;
    for (int i = x; i <= MaxN; i += lowbit(i))
    {
        ans = max(ans, Max2[i]);
    }
    return ans;
}
int a[500005], op[500005];
int f[500005][4], n, k;
void add(int len, int a)
{
    int W = (len - 1) % k + 1;
    switch (op[W])
    {
    case 1:
        Update1(a, len);
        break;
    case 2:
        Update2(a, len);
        break;
    case 3:
        Max3[a] = max(len, Max3[a]);
        break;
    default:
        printf("ERROR\n");
        exit(0);
        break;
    }
}
int main()
{
    //freopen("mot.in", "r", stdin);
    //freopen("mot.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    char c;
    for (int i = 1; i <= k; i++)
    {
        c = getchar();
        while (c != '<' && c != '>' && c != '=')
            c = getchar();
        switch (c)
        {
        case '<':
            op[i] = 1;
            break;
        case '>':
            op[i] = 2;
            break;
        case '=':
            op[i] = 3;
        }
    }
    int ans = 0;
    //f[1][1] = f[1][2] = f[1][3] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i][1] = MAX1(a[i] - 1) + 1;
        f[i][2] = MAX2(a[i] + 1) + 1;
        f[i][3] = Max3[a[i]] + 1;
        for (int j = 1; j <= 3; j++)
        {
            add(f[i][j], a[i]);
            ans = max(ans, f[i][j]);
        }
    }
    //for(int i=1;i<=n;i++)
    //    printf("%d %d %d\n",f[i][1],f[i][2],f[i][3]);
    // while(1);
    printf("%d", ans);
}

// Problem2507:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int son[100005], mid;
struct edge
{
    int END, next;
} v[200005];
int first[100005], p, f[100005], q[100005], tot;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
    v[p].END = a;
    v[p].next = first[b];
    first[b] = p++;
}
int cmp(const int a, const int b)
{
    return b < a;
}
void dfs(int rt, int fa)
{
    f[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
        if (v[i].END != fa)
            dfs(v[i].END, rt);
    int cnt = 0;
    q[0] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
        if (v[i].END != fa)
            q[++cnt] = f[v[i].END] + 1;
    sort(q + 1, q + cnt + 1, cmp);
    if (!cnt)
        return;
    if (cnt == 1)
    {
        if (q[1] > mid)
        {
            tot++;
            return;
        }
        else
        {
            f[rt] = q[1];
            return;
        }
    }
    int i = 2;
    while (q[i - 1] + q[i] > mid && i <= cnt)
    {
        tot++;
        i++;
    }
    if (i == cnt + 1 && q[i - 1] > mid)
        tot++;
    f[rt] = q[i - 1];
}
int main()
{
    memset(first, -1, sizeof(first));
    int n, m;
    scanf("%d%d", &n, &m);
    int a, b;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    //int ans=0;
    int l = 1, r = n;
    while (l < r)
    {
        mid = l + r >> 1;
        tot = 0;
        dfs(1, 0);
        if (tot <= m)
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d", l);
    //while(1);
}
// Problem2520:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int MOD;
long long f[1000005];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long C(int n, int m)
{
    if (m > n)
        return 0;
    return f[n] * pow_mod(f[m] * f[n - m] % MOD, MOD - 2) % MOD;
}
int n;
int size[1000005];
long long ans = 1;
void DFS(int x)
{
    if (x > n)
        return;
    size[x] = 1;
    DFS(x << 1 | 1)
    , DFS(x << 1);
    if ((x << 1) <= n)
        size[x] += size[x << 1];
    if ((x << 1 | 1) <= n)
        size[x] += size[x << 1 | 1];
}
void dfs(int x)
{
    if (x > n)
        return;
    if ((x << 1) > n)
        return;
    ans = ans * C(size[x] - 1, size[x << 1]) % MOD;
    dfs(x << 1);
    dfs(x << 1 | 1);
}
int main()
{
    scanf("%d%d", &n, &MOD);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        f[i] = f[i - 1] * i % MOD;
    DFS(1);
    dfs(1);
    printf("%lld", ans);
}
// Problem2529:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
int comp(int a, int b)
{
    return a > b;
}
using namespace std;
int pre[10005], front[1000005];
int in[10005];
int a[10005], b[10005];
int n, block;
void build(int x)
{
    for (int i = (x - 1) * block + 1; i <= min(x * block, n); i++)
    {
        pre[i] = b[i];
    }
    sort(pre + (x - 1) * block + 1, pre + min(x * block + 1, n + 1));
}
void rebuild(int k, int x)
{
    for (int i = 1; i <= n; i++)
        front[a[i]] = 0;
    a[k] = x;
    for (int i = 1; i <= n; i++)
    {
        int ls = b[i];
        b[i] = front[a[i]];
        if (ls != b[i])
            build(in[i]);
        front[a[i]] = i;
    }
}
int query(int c, int x)
{
    int l = (x - 1) * block + 1, r = min(n, x * block);
    int head = l;
    while (l <= r)
    {
        int m = (l + r) >> 1;
        if (pre[m] < c)
            l = m + 1;
        else
            r = m - 1;
    }
    return l - head;
}
int Query(int l, int r)
{
    int ans = 0;
    if (in[l] == in[r])
    {
        for (int i = l; i <= r; i++)
            if (b[i] < l)
                ans++;
    }
    else
    {
        for (int i = l; i <= min(block * in[l], n); i++)
            if (b[i] < l)
                ans++;
        for (int i = block * (in[r] - 1) + 1; i <= r; i++)
            if (b[i] < l)
                ans++;
    }
    for (int i = in [l] + 1; i < in[r]; i++)
        ans += query(l, i);
    return ans;
}
int main()
{
    //freopen("1.in", "r", stdin);
    int m;
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = front[a[i]];
        front[a[i]] = i;
        in[i] = (i - 1) / block + 1;
    }
    int tot = in[n];
    for (int i = 1; i <= tot; i++)
        build(i);
    char s[10];
    int l, r;
    while (m--)
    {
        scanf("%s", s);
        if (s[0] == 'Q')
        {
            scanf("%d%d", &l, &r);
            printf("%d\n", Query(l, r));
        }
        else
        {
            scanf("%d%d", &l, &r);
            rebuild(l, r);
        }
    }
}
// Problem2595:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
bool isnprime[10000005];
long long prime[2000005], Inv[10000005], F[10000005];
long long A[10000005];
int MOD, Idx;
void Get_Prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= 10000000; i++)
    {
        if (!isnprime[i])
        {
            prime[++Idx] = i;
        }
        for (int j = 1; j <= Idx; j++)
        {
            if (prime[j] * i > 10000000)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
void Get_Inv(int n)
{
    Inv[1] = 1;
    for (int i = 2; i <= n; i++)
        Inv[i] = (MOD - MOD / i) * Inv[MOD % i] % MOD;
}
int main()
{
    Get_Prime();
    int T;
    scanf("%d%d", &T, &MOD);
    Get_Inv(10000000);
    F[0] = 1;
    for (int i = 1; i <= 10000000; i++)
        F[i] = F[i - 1] * i % MOD;
    long long now = 1;
    for (int i = 0; i <= Idx; i++)
    {
        now = (MOD + 1 - Inv[prime[i]]) * now % MOD;
        for (int j = prime[i]; j < prime[i + 1] && j <= 10000000; j++)
            A[j] = now;
    }
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        long long ans = F[n] * A[m] % MOD;
        printf("%lld\n", ans);
    }
}
// Problem2595:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
bool isnprime[10000005];
long long Inv[10000005], F[10000005];
long long A[10000005];
int prime[2000005], MOD, Idx;
void Get_Prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= 10000000; i++)
    {
        if (!isnprime[i])
        {
            prime[++Idx] = i;
        }
        for (int j = 1; j <= Idx; j++)
        {
            if (prime[j] * i > 10000000)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int main()
{
    Get_Prime();
    int T;
    scanf("%d%d", &T, &MOD);
    Inv[1] = 1;
    for (int i = 2; i <= 10000000; i++)
        Inv[i] = (MOD - MOD / i) * Inv[MOD % i] % MOD;

    F[0] = 1;
    for (int i = 1; i <= 10000000; i++)
        F[i] = F[i - 1] * i % MOD;

    long long now = 1;
    for (int i = 0; i <= Idx; i++)
    {
        now = (MOD + 1 - Inv[prime[i]]) * now % MOD;
        for (int j = prime[i]; j < prime[i + 1] && j <= 10000000; j++)
            A[j] = now;
    }

    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        long long ans = F[n] * A[m] % MOD;
        printf("%lld\n", ans);
    }
}
// Problem2683:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct edge
{
    int next, END, v;
} v[300005 << 1];
int first[300005], p;
void add(int a, int b, int c)
{
    v[p].next = first[a];
    v[p].END = b;
    v[p].v = c;
    first[a] = p++;
}
int s, n;
int Max_len, P;
int f[300005], dis[300005];
void dfs(int rt, int fa, int len)
{
    f[rt] = fa;
    dis[rt] = len;
    if (len > Max_len)
        P = rt, Max_len = len;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        dfs(v[i].END, rt, len + v[i].v);
    }
}
bool vis[300005];
int st[300005], top;
queue<int> Q;
int L, R;
bool Judge(int mid)
{
    int l = 1, r = top;
    while (st[1] - st[l + 1] <= mid && l <= top)
        l++;
    while (st[r - 1] <= mid && r >= 1)
        r--;
    return st[l] - st[r] <= s;
}
int main()
{
    memset(first, -1, sizeof(first));
    scanf("%d%d", &n, &s);
    int a, b, c;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    dfs(1, 0, 0);
    L = P;
    P = 0, Max_len = 0;
    dfs(L, 0, 0);
    R = P;
    for (int i = R; i != f[L]; i = f[i])
    {
        st[++top] = dis[i], Q.push(i), vis[i] = 1;
    }
    memset(dis, 0x3f, sizeof(dis));
    for (int i = R; i != f[L]; i = f[i])
        dis[i] = 0;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
            if (dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
    }
    int l = 0, r = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        if (l < dis[i])
            l = dis[i];
    int ans = 0;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (Judge(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%d", ans);
}
// Problem2688:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int f[2005];
int ans[2005][2005];
int w[2005];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", w + i);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= w[i]; j--)
            f[j] = (f[j] + f[j - w[i]]) % 10;
    for (int i = 1; i <= n; i++)
    {
        ans[i][0] = 1;
        for (int j = 1; j <= m; j++)
        {
            if (j >= w[i])
                ans[i][j] = (f[j] - ans[i][j - w[i]] + 10) % 10;
            else
                ans[i][j] = f[j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            printf("%d", ans[i][j]);
        printf("\n");
    }
}
// Problem2689:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
struct data
{
    long long Num;
    int pos;
    bool operator<(const data &a) const
    {
        return Num == a.Num ? pos < a.pos : Num < a.Num;
    }
};
int fre[100005], nxt[100005];
long long a[100005], d[100005];
set<data> st;
long long merge()
{
    int A = st.begin()->pos;
    long long ans = a[A];
    a[A] = -a[A];
    a[A] += a[fre[A]], a[A] += a[nxt[A]];
    st.erase(st.begin());
    st.erase((data){a[fre[A]], fre[A]});
    st.erase((data){a[nxt[A]], nxt[A]});
    st.insert((data){a[A], A});
    if (fre[fre[A]])
        nxt[fre[fre[A]]] = A;
    if (nxt[nxt[A]])
        fre[nxt[nxt[A]]] = A;
    fre[A] = fre[fre[A]];
    nxt[A] = nxt[nxt[A]];
    return ans;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int j = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &d[++j]);
        if (d[j] == 0)
            j--;
    }
    bool flag = (d[1] > 0);
    int tot = 0;
    a[++tot] += d[1];
    for (int i = 2; i <= j; i++)
    {
        if ((d[i] > 0 && d[i - 1] > 0) || (d[i] < 0 && d[i - 1] < 0))
            a[tot] += d[i];
        else
        {
            if (tot == 1 && a[tot] < 0)
                tot--;
            a[++tot] = d[i];
        }
    }
    if (a[tot] < 0)
        tot--;
    long long ans = 0;
    int k = 0;
    for (int i = 1; i <= tot; i++)
    {
        if (a[i] > 0)
            ans += a[i], k++;
        a[i] = abs(a[i]);
        st.insert((data){a[i], i});
        nxt[i] = i + 1;
        fre[i] = i - 1;
    }
    if (k <= m)
        return printf("%d\n", ans), 0;
    nxt[tot] = 0;
    a[0] = 0x3f3f3f3f3f3f3f3fll;
    while (k > m)
    {
        ans -= merge();
        k--;
    }
    printf("%lld", ans);
}
// Problem2719:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
double f[200], g[200];
int main()
{
    int t = 0;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        double q, p;
        scanf("%d%lf%lf", &n, &p, &q);
        n = min(n, 100);
        f[0] = 0, g[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            if (f[i - 1] > g[i - 1])
                p = 1 - p, q = 1 - q;
            g[i] = (q * f[i - 1] + (1 - q) * p * g[i - 1]) / (q - q * p + p);
            f[i] = (p * g[i - 1] + (1 - p) * q * f[i - 1]) / (q - q * p + p);
            if (f[i - 1] > g[i - 1])
                p = 1 - p, q = 1 - q;
        }
        printf("%.6lf\n", f[n]);
    }
}
// Problem2727:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
long long MOD = 0;
struct Matrix
{
    int n, m;
    long long a[5][5];
    Matrix(int x, int y)
    {
        n = x, m = y;
        memset(a, 0, sizeof(a));
    }
    void Init()
    {
        for (int i = 1; i <= n; i++)
            a[i][i] = 1;
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ans(n, b.m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                for (int k = 1; k <= b.m; k++)
                {
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] % MOD * b.a[k][j] % MOD) % MOD;
                }
        return ans;
    }
    Matrix operator^(const long long &b) const
    {
        Matrix ans(n, m);
        ans.Init();
        Matrix c = *this;
        long long k = b;
        while (k)
        {
            if (k & 1)
                ans = c * ans;
            k >>= 1;
            c = c * c;
        }
        return ans;
    }
    void print()
    {
        printf("\n{n,m} = {%d,%d}\n", n, m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                printf("%lld ", a[i][j]);
            printf("\n");
        }
        printf("\n");
    }
};
long long pow(int a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans *= a;
        b >>= 1;
        a *= a;
    }
    return ans;
}

int main()
{
    //freopen("mathwork.in","r",stdin);
    //freopen("mathwork.out", "w", stdout);
    long long n;
    scanf("%lld%lld", &n, &MOD);
    Matrix A(3, 3);
    A.Init();
    long long M = 10;
    while (M <= n)
    {
        Matrix B(3, 3);
        B.a[1][1] = M % MOD;
        B.a[1][2] = B.a[1][3] = B.a[2][2] = B.a[2][3] = B.a[3][3] = 1;
        // printf("%lld\n",M - M / 10);
        B = B ^ (M - M / 10);
        A = B * A;
        //   printf("%lld\n",A.a[1][3]);
        M = M * 10;
    }
    //printf("%lld\n",A.a[1][3]);
    Matrix B(3, 3);
    B.a[1][1] = M % MOD;
    B.a[1][2] = B.a[1][3] = B.a[2][2] = B.a[2][3] = B.a[3][3] = 1;
    //printf("%lld\n",n - M / 10 + 1);
    B = B ^ (n - M / 10 + 1);
    A = B * A;
    printf("%lld", A.a[1][3]);
    //while (1) ;
}
// Problem2731:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
struct edge
{
    int END, v, next;
} v[300005];
int n;
int times[100005];
int first[100005], p, dis[100005];
void add(int a, int b, int c);
bool spfa(int a);
int main()
{
    //freopen("1.txt","r",stdin);
    int m, x, a, b;
    scanf("%d%d", &n, &m);
    //cout<<"&"<<endl;
    p = 1;
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &x, &a, &b);
        if (x == 1)
        {
            add(a, b, 0);
            add(b, a, 0);
        }
        if (x == 2)
            add(a, b, 1);
        if (x == 3)
            add(b, a, 0);
        if (x == 4)
            add(b, a, 1);
        if (x == 5)
            add(a, b, 0);
    }
    //cout<<"#"<<endl;
    //for(int i=n;i>=1;i--)
    //	add(n+1,i,0);
    for (int i = 1; i <= n; i++)
        add(n + 1, i, 1);
    //cout<<"@"<<endl;
    //spfa(0);
    if (spfa(n + 1))
        cout << "-1" << endl;
    else
    {
        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ans += dis[i];
        }
        cout << ans << endl;
    }
    //for(int i=1;i<=n;i++)
    //   cout<<dis[i]<<" ";
    //while(1);
}
bool spfa(int a)
{
    bool flag[100005] = {0};
    //queue<int> q;
    //deque<int> q;
    stack<int> q;
    memset(dis, 0, sizeof(dis));
    memset(times, 0, sizeof(times));
    //q.push_back(a);
    q.push(a);
    dis[a] = 0;
    times[a]++;
    flag[a] = 1;
    while (!q.empty())
    {
        //int k=q.front();
        //q.pop_front();
        int k = q.top();
        q.pop();
        flag[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] < dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                if (!flag[v[i].END])
                {
                    flag[v[i].END] = 1;
                    times[v[i].END]++;
                    if (times[v[i].END] > n + 1)
                        return 1;
                    //q.push_back(v[i].END);
                    q.push(v[i].END);
                }
            }
        }
    }
    return 0;
}
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}

// Problem2839:
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
struct edge
{
    int END, next;
} v[1000005], E[1000005];
int first[100005], Efirst[100005], p, Ep;
void add(int a, int c)
{
    v[p].END = c;
    v[p].next = first[a];
    first[a] = p++;
}
void add1(int a, int c)
{
    E[Ep].END = c;
    E[Ep].next = Efirst[a];
    Efirst[a] = Ep++;
}
int S[100005];
int low[100005], dfsn[100005], Index;
bool flag[100005];
int T;
int belong[100005];
stack<int> st;
void tarjan(int rt)
{
    low[rt] = dfsn[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!dfsn[v[i].END])
        {
            tarjan(v[i].END);
            low[rt] = min(low[rt], low[v[i].END]);
        }
        else if (flag[v[i].END])
            low[rt] = min(low[rt], dfsn[v[i].END]);
    }
    if (dfsn[rt] == low[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            flag[v] = 0;
            belong[v] = T;
            S[T]++;
        } while (dfsn[v] != low[v]);
    }
}
int isnroot[100005], ithason[100005];
int main()
{
    memset(first, -1, sizeof(first));
    memset(Efirst, -1, sizeof(Efirst));
    //freopen("killer.in", "r", stdin);
    //freopen("killer.out", "w", stdout);
    int n, m;
    int s, e;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s, &e);
        add(s, e);
    }
    for (int i = 1; i <= n; i++)
        if (!dfsn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
    {
        for (int j = first[i]; j != -1; j = v[j].next)
        {
            if (belong[i] != belong[v[j].END])
            {
                add1(belong[i], belong[v[j].END]);
                isnroot[belong[v[j].END]]++;
                ithason[belong[i]]++;
            }
        }
    }
    int ans = 0;
    bool flags = 0;
    for (int i = 1; i <= T; i++)
    {
        if (!isnroot[i])
        {
            ans++;
            if (flags)
                continue;
            //if (!ithason[i])
            //    flags = 1;
            if (S[i] == 1)
            {
                if (!ithason[i])
                    flags = 1;
                else
                {
                    bool e = 0;
                    for (int j = Efirst[i]; j != -1; j = E[j].next)
                    {
                        if (isnroot[E[j].END] == 1)
                            e = 1;
                    }
                    if (!e)
                        flags = 1;
                }
            }
        }
    }
    // if (!ans)
    //     ans = 1;
    if (flags)
        ans -= 1;
    printf("%.6lf", (double)(n - ans) / n);
}
// Problem2911:
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
struct Martix
{
    double a[1005];
    int n;
    Martix(int x)
    {
        n = x;
        memset(a, 0, sizeof(a));
    }
    Martix operator*(const Martix &b)
    {
        Martix ans(n);
        ans.a[1] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int k = 1; k <= n; k++)
            {
                int t = (i - k + n + 1) % n;
                if (!t)
                    t += n;
                ans.a[i] += a[k] * b.a[t];
            }
        }
        return ans;
    }
    Martix operator^(const int x)
    {
        Martix a = *this, ans(n);
        int k = x;
        ans.a[1] = 1;
        while (k)
        {
            if (k & 1)
                ans = ans * a;
            k >>= 1;
            a = a * a;
        }
        return ans;
    }
};
int a[1005];
double ans[1005];
int main(int argc, char const *argv[])
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    Martix K(n);
    K.a[1] = (double)1 - ((double)1 / m);
    K.a[2] = ((double)1 / m);
    K = K ^ k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int t = (i + j - 1) % n;
            if (!t)
                t += n;
            ans[t] += K.a[i] * a[j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%.3lf\n", ans[i]);
    }
    //while(1);
    return 0;
}

// Problem2954:
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int alphabet, Idx;
struct Trie_Node
{
    bool flag;
    int Id;
    Trie_Node *ch[27], *fail;
    Trie_Node()
    {
        flag = 0;
        Id = ++Idx;
        fail = NULL;
        memset(ch, 0, sizeof(ch));
    }
} * root, *point[100];
struct Matrix
{
    int n;
    long double a[100][100];
    Matrix(int b = 0)
    {
        n = b;
        memset(a, 0, sizeof(a));
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ans(n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    ans.a[i][j] += a[i][k] * b.a[k][j];
        return ans;
    }
    Matrix operator^(const int &k) const
    {
        Matrix a = *this, ans(n);
        for (int i = 1; i <= n; i++)
            ans.a[i][i] = 1;
        int b = k;
        while (b)
        {
            if (b & 1)
                ans = a * ans;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
};
void Insert(const char *s)
{
    Trie_Node *rt = root;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if (rt->ch[s[i] - 'a'] == NULL)
        {
            rt->ch[s[i] - 'a'] = new Trie_Node();
            point[Idx] = rt->ch[s[i] - 'a'];
        }
        else if (rt->ch[s[i] - 'a']->flag)
            return;
        rt = rt->ch[s[i] - 'a'];
    }
    rt->flag = 1;
}
queue<Trie_Node *> Q;
void Get_fail()
{
    for (int i = 0; i < alphabet; i++)
    {
        if (root->ch[i] != NULL)
        {
            root->ch[i]->fail = root;
            Q.push(root->ch[i]);
        }
    }
    while (!Q.empty())
    {
        Trie_Node *rt = Q.front();
        Q.pop();
        Trie_Node *p = NULL;
        for (int i = 0; i < alphabet; i++)
        {
            if (rt->ch[i] != NULL)
            {
                p = rt->fail;
                while (p != NULL)
                {
                    if (p->ch[i] != NULL)
                    {
                        rt->ch[i]->fail = p->ch[i];
                        break;
                    }
                    p = p->fail;
                }
                if (p == NULL)
                    rt->ch[i]->fail = root;
                Q.push(rt->ch[i]);
            }
            if (rt->ch[i] == NULL)
                rt->ch[i] = rt->fail->ch[i];
        }
    }
}
Matrix A;
long double P;
void Build()
{
    for (int i = 1; i <= Idx; i++)
        if (!point[i]->flag)
            for (int j = 0; j < alphabet; j++)
                if (point[i]->ch[j])
                    if (point[i]->ch[j]->flag)
                        A.a[i][Idx + 1] += P, A.a[i][1] += P;
                    else
                        A.a[i][point[i]->ch[j]->Id] += P;
                else
                    A.a[i][1] += P;
    A.a[Idx + 1][Idx + 1] = 1;
}
int main()
{
    root = new Trie_Node();
    point[1] = root;
    static char s[20];
    int n, len;
    scanf("%d%d%d", &n, &len, &alphabet);
    P = 1. / alphabet;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s);
        Insert(s);
    }
    Get_fail();
    //printf("1\n");
    A.n = Idx + 1;
    Build();
    A = A ^ len;
    printf("%.9lf", (double)A.a[1][Idx + 1]);
    //while (1);
}

// Problem3055:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int delta = 0;
struct edge
{
    int S, E, val, type;
    bool operator<(const edge &a) const
    {
        int v1 = val, v2 = a.val;
        if (!type)
            v1 += delta;
        if (!a.type)
            v2 += delta;
        return v1 == v2 ? type < a.type : v1 < v2;
    }
} v[100005 << 1];
int father[50005], n, m;
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
void init()
{
    for (int i = 0; i < n; i++)
        father[i] = i;
}
int Kruskal(int &num)
{
    int t = 0, sum = 0;
    for (int i = 1; i <= m; i++)
        if (find(v[i].S) != find(v[i].E))
        {
            father[find(v[i].S)] = find(v[i].E);
            if (!v[i].type)
                num++;
            sum += (v[i].type ? v[i].val : v[i].val + delta);
            t++;
            if (t == n - 1)
                break;
        }
    return sum;
}
int main()
{
    //freopen("nt2012_tree.in", "r", stdin);
    //freopen("nt2012_tree.out", "w", stdout);
    int need;
    scanf("%d%d%d", &n, &m, &need);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &v[i].S, &v[i].E, &v[i].val, &v[i].type);
    }
    int l = -105, r = 105;
    int ans = 0;
    while (l <= r)
    {
        delta = (l + r) / 2;
        init();
        sort(v + 1, v + m + 1);
        int ned = 0;
        int num = Kruskal(ned);
        if (ned >= need)
        {
            l = delta + 1;
            ans = num - need * delta;
        }
        else
            r = delta - 1;
    }
    printf("%d", ans);
}
// Problem3077:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Matrix
{
    double a[111][111];
    int n;
    Matrix(int x = 0)
    {
        memset(a, 0, sizeof(a));
        n = x;
    }
    void Init()
    {
        for (int i = 1; i <= n; i++)
            a[i][i] = 1;
    }
    double *operator[](const int x)
    {
        return a[x];
    }
    const double *operator[](const int x) const
    {
        return a[x];
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ans;
        ans.n = n;
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (a[i][j] < 1e-15)
                    continue;
                for (int k = 0; k <= n; k++)
                {
                    if (b[j][k] < 1e-15)
                        continue;
                    ans[i][k] += a[i][j] * b[j][k];
                }
            }
        }
        return ans;
    }
    Matrix operator^(int b) const
    {
        Matrix ans, a = *this;
        ans.n = n;
        ans.Init();
        while (b)
        {
            if (b & 1)
                ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
    void print()
    {
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
                printf("%.3lf ", a[i][j]);
            printf("\n");
        }
        printf("\n");
    }
};
int n, r, q;
int id[6][22], cnt;
bool Judge(double mid, int s)
{
    Matrix A;
    A.n = r * q;
    A[cnt][cnt] = 1;
    for (int i = 1; i <= q; i++)
    {
        for (int j = 1; j <= r; j++)
        {
            A[cnt][id[i][j]] = mid * j;
            if (i < q && j < r)
                A[id[i + 1][j + 1]][id[i][j]] += mid;
            else if (i < q)
                A[id[i + 1][j]][id[i][j]] += mid;
            else if (j < r)
                A[id[i][j + 1]][id[i][j]] += mid;
            else
                A[id[i][j]][id[i][j]] += mid;
            if (i > 1)
                A[id[i - 1][1]][id[i][j]] += (1 - mid);
        }
    }
    // A.print();
    A = A ^ n;
    return A[cnt][id[q][1]] <= s;
}
int main()
{
    int s;
    scanf("%d%d%d", &n, &r, &q);
    scanf("%d", &s);
    for (int i = 1; i <= q; i++)
        for (int j = 1; j <= r; j++)
            id[i][j] = cnt++;
    if (Judge(1, s))
        return printf("Impossible.\n"), 0;
    double l = 0, r = 1;
    while (l + 1e-8 < r)
    {
        double mid = (l + r) / 2;
        if (Judge(mid, s))
            l = mid;
        else
            r = mid;
    }
    printf("%.6lf", l);
}

// Problem3117:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
int n, m, block, tot;
int a[40005], Index, v[40005];
int in[40005];
int f[4000][4000], num[40005];
map<int, int> mp;
vector<int> x[40005];
void Init(int u)
{
    memset(num, 0, sizeof(num));
    int Max = 0, ans = 0;
    for (int i = (u - 1) * block + 1; i <= n; i++)
    {
        num[a[i]]++;
        if (num[a[i]] > Max || (num[a[i]] == Max && v[a[i]] < v[ans]))
            ans = a[i], Max = num[a[i]];
        f[u][in[i]] = ans;
    }
}
int Query(int l, int r, int u)
{
    return upper_bound(x[u].begin(), x[u].end(), r) - lower_bound(x[u].begin(), x[u].end(), l);
}
int Query(int l, int r)
{
    int ans, Max;
    ans = f[in[l] + 1][in[r] - 1];
    Max = Query(l, r, ans);
    for (int i = l; i <= min(in[l] * block, r); i++)
    {
        int now = Query(l, r, a[i]);
        if (now > Max || (now == Max && v[a[i]] < v[ans]))
            ans = a[i], Max = now;
    }
    if (in[l] != in[r])
    {
        for (int i = (in[r] - 1) * block + 1; i <= r; i++)
        {
            int now = Query(l, r, a[i]);
            if (now > Max || (now == Max && v[a[i]] < v[ans]))
                ans = a[i], Max = now;
        }
    }
    return ans;
}
int main()
{
    //freopen("input.in", "r", stdin);
    scanf("%d%d", &n, &m);
    block = 200;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if (!mp[a[i]])
        {
            mp[a[i]] = ++Index;
            v[Index] = a[i];
        }
        a[i] = mp[a[i]];
        x[a[i]].push_back(i);
        in[i] = (i - 1) / block + 1;
    }
    tot = in[n];
    for (int i = 1; i <= tot; i++)
        Init(i);
    int l, r, ans = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        l = (l + ans - 1) % n + 1, r = (r + ans - 1) % n + 1;
        if (l > r)
            swap(l, r);
        ans = v[Query(l, r)];
        printf("%d\n", ans);
    }
    //while (1)
    ;
}
// Problem3123:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next;
} v[10005];
int first[500], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dfn[500], low[500], Index;
bool iscut[500];
void Tarjan(int x, int fa)
{
    low[x] = dfn[x] = ++Index;
    int S = 0;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (!dfn[v[i].END])
        {
            S++;
            Tarjan(v[i].END, x);
            low[x] = min(low[v[i].END], low[x]);
            if (low[v[i].END] >= dfn[x])
                iscut[x] = 1;
        }
        else
            low[x] = min(low[x], dfn[v[i].END]);
    }
    if (fa < 0 && S == 1)
        iscut[x] = 0;
}
bool vis[500];
int T, size, num;
int color[500];
void dfs(int x)
{
    vis[x] = 1;
    size++;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END])
        {
            if (!iscut[v[i].END])
                dfs(v[i].END);
            else
            {
                if (color[v[i].END] != T)
                    color[v[i].END] = T, num++;
            }
        }
    }
}
int main()
{
    //freopen("bzoj_2730.in","r",stdin);
    //freopen("bzoj_2730.out","w",stdout);
    int P1 = 0;
    while (1)
    {
        memset(vis, 0, sizeof(vis));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(iscut, 0, sizeof(iscut));
        memset(first, -1, sizeof(first));
        memset(color, 0, sizeof(color));
        p = 0;
        Index = 0;
        P1++;
        int n = 0, a, b, m;
        scanf("%d", &m);
        if (m == 0)
            break;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            n = max(a, n);
            n = max(b, n);
            add(a, b);
            add(b, a);
        }
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                Tarjan(i, -1);
        int ans1 = 0;
        long long ans2 = 1;
        T = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i] && !iscut[i])
            {
                T++, size = 0, num = 0;
                dfs(i);
                if (num == 1)
                    ans1++, ans2 *= size;
            }
        }
        if (T == 1)
            ans1 = 2, ans2 = n * (n - 1) / 2;
        printf("Case %d: %d %lld\n", P1, ans1, ans2);
    }
}
// Problem3126:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Node
{
    int v, key, size;
    Node *ch[2];
    Node(int x)
    {
        v = x;
        key = rand();
        size = 1;
        ch[0] = ch[1] = NULL;
    }
#define size(_) ((_) ? (_)->size : (0))
    void Pushup()
    {
        size = 1 + size(ch[1]) + size(ch[0]);
    }
};
typedef pair<Node *, Node *> DNode;
Node *Merge(Node *A, Node *B)
{
    if (!A)
        return B;
    if (!B)
        return A;
    if (A->key < B->key)
    {
        A->ch[1] = Merge(A->ch[1], B);
        A->Pushup();
        return A;
    }
    else
    {
        B->ch[0] = Merge(A, B->ch[0]);
        B->Pushup();
        return B;
    }
}
DNode Split(Node *rt, int k)
{
    if (!rt)
        return DNode(NULL, NULL);
    DNode o;
    if (size(rt->ch[0]) >= k)
    {
        o = Split(rt->ch[0], k);
        rt->ch[0] = o.second;
        rt->Pushup();
        o.second = rt;
    }
    else
    {
        o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
        rt->ch[1] = o.first;
        rt->Pushup();
        o.first = rt;
    }
    return o;
}
Node *kth(Node *rt, int k)
{
    DNode x = Split(rt, k - 1);
    DNode y = Split(x.second, 1);
    Node *ans = y.first;
    rt = Merge(Merge(x.first, ans), y.second);
    return ans;
}
int Rank(Node *rt, int x)
{
    if (!rt)
        return 0;
    return x <= rt->v ? Rank(rt->ch[0], x) : Rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
}
Node *Insert(Node *rt, int x)
{
    int k = Rank(rt, x);
    DNode a = Split(rt, k);
    Node *n = new Node(x);
    return Merge(Merge(a.first, n), a.second);
}
Node *f[100005];
int father[100005];
int find(int x)
{
    if (x != father[x])
        father[x] = find(father[x]);
    return father[x];
}
void dfs(Node *&root, Node *rt)
{
    if (rt)
    {
        dfs(root, rt->ch[0]);
        root = Insert(root, rt->v);
        dfs(root, rt->ch[1]);
    }
}
int v[100005], s[100005];
int main()
{
    //freopen("bzoj_2733.in","r",stdin);
    //freopen("bzoj_2733.out","w",stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", v + i);
        s[v[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
        f[i] = Insert(f[i], v[i]);
    }
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        int x = find(a), y = find(b);
        if (x != y)
        {
            if (size(f[x]) < size(f[y]))
                swap(x, y);
            father[y] = x;
            dfs(f[x], f[y]);
        }
    }
    int Q;
    scanf("%d", &Q);
    char c[3];
    for (int i = 1; i <= Q; i++)
    {
        scanf("%s%d%d", c, &a, &b);
        if (c[0] == 'Q')
        {
            Node *ans = kth(f[find(a)], b);
            if (ans == NULL)
                printf("-1\n");
            else
                printf("%d\n", s[ans->v]);
        }
        else
        {
            int x = find(a), y = find(b);
            if (x != y)
            {
                if (size(f[x]) < size(f[y]))
                    swap(x, y);
                father[y] = x;
                dfs(f[x], f[y]);
            }
        }
    }
}
// Problem3131:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Quer
{
    int x1, y1, x2, y2, k;
} Q[60005], *q[60005], *nq[60005];
struct data
{
    int val, x, y;
    bool operator<(const data &a) const
    {
        return val < a.val;
    }
} a[505 * 505];
int Sum[505][505];
int cnt, ans[60005], n, now;
#define lowbit(_) ((_) & (-_))
void add(int x, int y, int c)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            Sum[i][j] += c;
}
int Query(int x, int y)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            ans += Sum[i][j];
    return ans;
}
int Query(int x_1, int y_1, int x_2, int y_2)
{
    return Query(x_2, y_2) - Query(x_2, y_1 - 1) - Query(x_1 - 1, y_2) + Query(x_1 - 1, y_1 - 1);
}
void Solve(int l, int r, int L, int R)
{
    if (l > r)
        return;
    int mid = L + R >> 1;
    if (L == R)
    {
        for (int i = l; i <= r; i++)
            ans[q[i] - Q] = mid;
        return;
    }
    while (now != cnt && a[now + 1].val <= mid)
    {
        now++;
        add(a[now].x, a[now].y, 1);
    }
    while (now && a[now].val > mid)
    {
        add(a[now].x, a[now].y, -1);
        now--;
    }
    int x = l, y = r;
    for (int i = l; i <= r; i++)
    {
        int K = Query(q[i]->x1, q[i]->y1, q[i]->x2, q[i]->y2);
        if (q[i]->k > K)
            nq[y--] = q[i];
        else
            nq[x++] = q[i];
    }
    memcpy(q + l, nq + l, sizeof(q[0]) * (r - l + 1));
    Solve(l, x - 1, L, mid);
    Solve(y + 1, r, mid + 1, R);
}
int main()
{
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[++cnt].val), a[cnt].x = i, a[cnt].y = j;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d%d", &Q[i].x1, &Q[i].y1, &Q[i].x2, &Q[i].y2, &Q[i].k);
        q[i] = &Q[i];
    }
    sort(a + 1, a + cnt + 1);
    Solve(1, m, 0, a[cnt].val);
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
}
// Problem3156:
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
struct edge
{
    int END, next, v;
} v[100005];
int first[10005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}

int dis[10005][11];
bool flag[10005][11];
int Top;
struct data
{
    int k, tmp;
    bool operator<(const data &a) const
    {
        return dis[k][tmp] > dis[a.k][a.tmp];
    }
};
int Spfa(int S, int T)
{
    memset(dis, 0x3f, sizeof(dis));
    flag[S][0] = 1;
    priority_queue<data> Q;
    Q.push((data){S, 0});
    dis[S][0] = 0;
    while (!Q.empty())
    {
        int k = Q.top().k;
        int tmp = Q.top().tmp;
        flag[k][tmp] = 0;
        Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END][tmp] > dis[k][tmp] + v[i].v)
            {
                dis[v[i].END][tmp] = dis[k][tmp] + v[i].v;
                if (!flag[v[i].END][tmp])
                {
                    flag[v[i].END][tmp] = 1;
                    Q.push((data){v[i].END, tmp});
                }
            }
            if (dis[v[i].END][tmp + 1] > dis[k][tmp] && tmp + 1 <= Top)
            {
                dis[v[i].END][tmp + 1] = dis[k][tmp];
                if (!flag[v[i].END][tmp + 1])
                {
                    flag[v[i].END][tmp + 1] = 1;
                    Q.push((data){v[i].END, tmp + 1});
                }
            }
        }
    }
    int ans = 0x7fffffff;
    for (int i = 0; i <= Top; i++)
        ans = min(ans, dis[T][i]);
    return ans;
}
int main(int argc, char const *argv[])
{
    memset(first, -1, sizeof(first));
    int n, m;
    scanf("%d%d%d", &n, &m, &Top);
    int S, T;
    scanf("%d%d", &S, &T);
    S++, T++;
    int a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a + 1, b + 1, c);
        add(b + 1, a + 1, c);
    }
    printf("%d", Spfa(S, T));
    return 0;
}

// Problem3156:
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
struct edge
{
    int END, next, v;
} v[100005];
int first[10005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}

int dis[10005][11];
bool flag[10005][11];
int Top;
struct data
{
    int k, tmp;
    bool operator<(const data &a) const
    {
        return dis[k][tmp] > dis[a.k][a.tmp];
    }
};
int Spfa(int S, int T)
{
    memset(dis, 0x3f, sizeof(dis));
    flag[S][0] = 1;
    deque<data> Q;
    Q.push_back((data){S, 0});
    dis[S][0] = 0;
    while (!Q.empty())
    {
        int k = Q.front().k;
        int tmp = Q.front().tmp;
        flag[k][tmp] = 0;
        Q.pop_front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END][tmp] > dis[k][tmp] + v[i].v)
            {
                dis[v[i].END][tmp] = dis[k][tmp] + v[i].v;
                if (!flag[v[i].END][tmp])
                {
                    flag[v[i].END][tmp] = 1;
                    if (dis[v[i].END][tmp] > dis[Q.front().k][Q.front().tmp])
                        Q.push_back((data){v[i].END, tmp});
                    else
                        Q.push_front((data){v[i].END, tmp});
                }
            }
            if (dis[v[i].END][tmp + 1] > dis[k][tmp] && tmp + 1 <= Top)
            {
                dis[v[i].END][tmp + 1] = dis[k][tmp];
                if (!flag[v[i].END][tmp + 1])
                {
                    flag[v[i].END][tmp + 1] = 1;
                    if (dis[v[i].END][tmp + 1] > dis[Q.front().k][Q.front().tmp])
                        Q.push_back((data){v[i].END, tmp + 1});
                    else
                        Q.push_front((data){v[i].END, tmp + 1});
                }
            }
        }
    }
    int ans = 0x7fffffff;
    for (int i = 0; i <= Top; i++)
        ans = min(ans, dis[T][i]);
    return ans;
}
int main(int argc, char const *argv[])
{
    memset(first, -1, sizeof(first));
    int n, m;
    scanf("%d%d%d", &n, &m, &Top);
    int S, T;
    scanf("%d%d", &S, &T);
    S++, T++;
    int a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a + 1, b + 1, c);
        add(b + 1, a + 1, c);
    }
    printf("%d", Spfa(S, T));
    return 0;
}
// Problem3181:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
struct edge
{
    int next, END, v;
} v[200005];
int first[605], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int low[605], dfn[605], Index;
bool flag[605];
stack<int> st;
int belong[605], T;
void tarjan(int rt)
{
    low[rt] = dfn[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!dfn[v[i].END])
        {
            tarjan(v[i].END);
            low[rt] = min(low[rt], low[v[i].END]);
        }
        else if (flag[v[i].END])
        {
            low[rt] = min(low[rt], dfn[v[i].END]);
        }
    }
    if (dfn[rt] == low[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            flag[v] = 0;
            belong[v] = T;
        } while (dfn[v] != low[v]);
    }
}
int INF;
int map[605][605];
int main()
{
    int ans = 0;
    memset(first, -1, sizeof(first));
    int n, m1, m2;
    scanf("%d%d%d", &n, &m1, &m2);
    int a, b;
    memset(map, 0xC3, sizeof(map));
    memset(&INF, 0xC3, sizeof(INF));
    for (int i = 1; i <= n; i++)
        map[i][i] = 0;
    for (int i = 1; i <= m1; i++)
    {
        scanf("%d%d", &a, &b);
        add(b, a, -1);
        add(a, b, 1);
        map[a][b] = max(map[a][b], 1);
        map[b][a] = max(map[b][a], -1);
    }
    for (int i = 1; i <= m2; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b, 0);
        map[a][b] = max(map[a][b], 0);
        //add(b, a, 0);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);

    for (int d = 1; d <= T; d++)
    {
        for (int k = 1; k <= n; k++)
        {
            if (belong[k] != d)
                continue;
            for (int i = 1; i <= n; i++)
            {
                if (belong[i] != d)
                    continue;
                if (map[i][k] == INF)
                    continue;
                for (int j = 1; j <= n; j++)
                {
                    if (belong[j] != d)
                        continue;
                    if (map[k][j] == INF)
                        continue;
                    map[i][j] = max(map[i][j], map[i][k] + map[k][j]);
                }
            }
        }
        int ret = 0;
        for (int i = 1; i <= n; i++)
        {
            if (belong[i] != d)
                continue;
            for (int j = 1; j <= n; j++)
            {
                if (belong[j] != d)
                    continue;
                ret = max(ret, abs(map[i][j]));
            }
        }
        ans += ret + 1;
    }
    for (int i = 1; i <= n; i++)
        if (map[i][i] != 0)
        {
            puts("NIE");
            return 0;
        }
    printf("%d\n", ans);
}
// Problem3211:
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 10000000;
int mu[N + 5], prime[N + 5], g[N + 5];
long long sum[N + 5], cnt;
bool isnprime[N + 5];
void get_g()
{
    mu[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!isnprime[i])
        {
            prime[++cnt] = i;
            mu[i] = -1;
            g[i] = 1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= N; j++)
        {
            isnprime[i * prime[j]] = 1;
            if (i % prime[j])
                mu[i * prime[j]] = -mu[i], g[i * prime[j]] = mu[i] - g[i];
            else
            {
                mu[i * prime[j]] = 0;
                g[i * prime[j]] = mu[i];
                break;
            }
        }
    }
    for (int i = 1; i <= N; i++)
    {
        sum[i] = sum[i - 1] + g[i];
    }
}
int main()
{
    get_g();
    int n;
    scanf("%d", &n);
    long long ans = 0, last;
    for (int i = 1; i <= n; i = last + 1)
    {
        last = n / (n / i);
        ans += (long long)(sum[last] - sum[i - 1]) * (n / i) * (n / i);
    }
    printf("%lld\n", ans);
}
// Problem3212:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 500005;
struct edge
{
    int next, END;
} v[N << 1];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dep[N], size[N], fa[N], id[N], son[N], top[N], Index;
void dfs1(int x, int f, int Dep)
{
    dep[x] = Dep;
    size[x] = 1;
    fa[x] = f;
    son[x] = 0;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END == f)
            continue;
        dfs1(v[i].END, x, Dep + 1);
        size[x] += size[v[i].END];
        if (size[v[i].END] > size[son[x]])
            son[x] = v[i].END;
    }
}
void dfs2(int rt, int tp)
{
    top[rt] = tp;
    id[rt] = ++Index;
    if (son[rt])
        dfs2(son[rt], tp);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt] || v[i].END == son[rt])
            continue;
        dfs2(v[i].END, v[i].END);
    }
}
#define lowbit(_) ((_) & (-_))
int Xor[N], n;
void change(int x, int a)
{
    for (int i = x; i <= n; i += lowbit(i))
        Xor[i] ^= a;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans ^= Xor[i];
    return ans;
}
int Query(int a, int b)
{
    return Query(b) ^ Query(a - 1);
}
bool LCA(int x, int y)
{
    int now = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        now ^= Query(id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    now ^= Query(id[x], id[y]);
    return now;
}
int val[N];
int main()
{
    scanf("%d", &n);
    memset(first, -1, sizeof(first));
    int a, b;
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    dfs1(1, 0, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++)
        change(id[i], val[i]);
    int Q;
    char s[5];
    scanf("%d", &Q);
    while (Q--)
    {
        scanf("%s", s);
        if (s[0] == 'C')
        {
            scanf("%d%d", &a, &b);
            change(id[a], b ^ val[a]);
            val[a] = b;
        }
        else
        {
            scanf("%d%d", &a, &b);
            if (LCA(a, b))
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
}
// Problem3215:
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
    const int operator[](const int x) const
    {
        return c[x];
    }
    int &operator[](const int x)
    {
        return c[x];
    }
    BigNum operator*(const int &b) const
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
        while (y)
        {
            ans[++ans.len] = y % base;
            y /= base;
        }
        return ans;
    }
    BigNum operator/(const int &b) const
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
        while (!ans[ans.len] && ans.len > 1)
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
// Problem3231:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;
int f[1000005];
int Inv[1000005];
int pow_mod(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int C(int n, int m)
{
    if (n < m)
        return 0;
    return f[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
signed main()
{
    int n, k;
    f[0] = 1;
    for (int i = 1; i <= 1000000; i++)
        f[i] = f[i - 1] * i % MOD;
    Inv[1000000] = pow_mod(f[1000000], MOD - 2) % MOD;
    for (int i = 1000000 - 1; i >= 0; i--)
        Inv[i] = Inv[i + 1] * (i + 1) % MOD;
    scanf("%lld%lld", &n, &k);
    int Ans = C(n, k);
    int Sum = 0;
    int m = n - k;
    int tmp = 2;
    for (int i = m; i >= 0; i--)
    {
        if (i & 1)
            Sum = (Sum - C(m, i) * tmp % MOD + MOD) % MOD;
        else
            Sum = (Sum + C(m, i) * tmp % MOD + MOD) % MOD;
        tmp = tmp * tmp % MOD;
    }
    Ans = Ans * Sum % MOD;
    printf("%lld", Ans);
}
// Problem3420:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define LL long long
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
const int N = 100005;
LL Min[N << 2], Max[N << 2], Sum[N << 2];
int Sqr[N << 2];
void Pushup(int rt)
{
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    if (Sum[rt << 1] != -1 && Sum[rt << 1 | 1] != -1)
        Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
    else
        Sum[rt] = -1;
}
void Pushdown(int rt, int s)
{
    if (Sqr[rt])
    {
        Sqr[rt << 1] += Sqr[rt];
        Sqr[rt << 1 | 1] += Sqr[rt];
        Sum[rt << 1] = Sum[rt << 1 | 1] = -1;
        if (Max[rt << 1] > 1)
            for (int i = 1; i <= Sqr[rt]; i++)
            {
                Max[rt << 1] = sqrt(Max[rt << 1]);
                Min[rt << 1] = sqrt(Min[rt << 1]);
                if (Max[rt << 1] == 1)
                    break;
            }
        if (Max[rt << 1 | 1] > 1)
            for (int i = 1; i <= Sqr[rt]; i++)
            {
                Max[rt << 1 | 1] = sqrt(Max[rt << 1 | 1]);
                Min[rt << 1 | 1] = sqrt(Min[rt << 1 | 1]);
                if (Max[rt << 1 | 1] == 1)
                    break;
            }
        if (Max[rt << 1 | 1] == Min[rt << 1 | 1])
            Sum[rt << 1 | 1] = Max[rt << 1 | 1] * (s >> 1);
        if (Max[rt << 1] == Min[rt << 1])
            Sum[rt << 1] = Max[rt << 1] * (s - (s >> 1));
        Sqr[rt] = 0;
    }
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        scanf("%lld", &Min[rt]);
        Sum[rt] = Max[rt] = Min[rt];
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
void Update(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        Sqr[rt] += 1;
        Max[rt] = sqrt(Max[rt]), Min[rt] = sqrt(Min[rt]);
        Sum[rt] = -1;
        if (Max[rt] == Min[rt])
            Sum[rt] = Max[rt] * (r - l + 1);
        return;
    }
    Sum[rt] = -1;
    Pushdown(rt, r - l + 1);
    int m = l + r >> 1;
    if (L <= m)
        Update(L, R, lch);
    if (R > m)
        Update(L, R, rch);
    Pushup(rt);
}
LL Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        if (Max[rt] == Min[rt])
        {
            return Sum[rt] = Max[rt] * (r - l + 1);
        }
        if (Sum[rt] != -1)
            return Sum[rt];
    }
    Pushdown(rt, r - l + 1);
    LL ans = 0;
    int m = l + r >> 1;
    if (L <= m)
        ans += Query(L, R, lch);
    if (R > m)
        ans += Query(L, R, rch);
    return ans;
    Pushup(rt);
}
void print(int l, int r, int rt)
{
    printf("l=%d,r=%d,rt=%d,Sum[rt]=%lld\n", l, r, rt, Sum[rt]);
    if (l == r)
        return;
    int m = l + r >> 1;
    print(lch);
    print(rch);
}
int main()
{
    int n, m;
    //freopen("god.in", "r", stdin);
    // freopen("god.out", "w", stdout);
    scanf("%d", &n);
    buildtree(1, n, 1);
    scanf("%d", &m);
    int op, l, r;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &op, &l, &r);
        if (l > r)
            swap(l, r);
        if (op)
        {
            printf("%lld\n", Query(l, r, 1, n, 1));
        }
        else
        {
            Update(l, r, 1, n, 1);
        }
    }
#ifdef Mine
    //while (1)
    ;
#endif
}

// Problem3485:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;
char s[50];
int Greater[10][10][10][10];
int In[10][10];
bool H[10][10], S[10][10], K[10][10];
int map[10][10];
bool OK(int x, int y, int i)
{
    if (H[x][i])
        return 0;
    if (S[y][i])
        return 0;
    if (K[In[x][y]][i])
        return 0;
    if (Greater[x][y][x - 1][y] == 1 && i < map[x - 1][y])
        return 0;
    if (Greater[x][y][x][y - 1] == 1 && i < map[x][y - 1])
        return 0;
    if (Greater[x][y][x - 1][y] == -1 && i > map[x - 1][y])
        return 0;
    if (Greater[x][y][x][y - 1] == -1 && i > map[x][y - 1])
        return 0;
    return 1;
}
int ans = 0;
void dfs(int x, int y)
{
    //ans++;
    //printf("%d %d\n", x, y);
    if (x == 10 && y == 1)
    {
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
                printf("%d ", map[i][j]);
            printf("\n");
        }
        exit(0);
    }
    for (int i = 9; i >= 1; i--)
    {
        if (OK(x, y, i))
        {
            K[In[x][y]][i] = 1;
            H[x][i] = 1;
            S[y][i] = 1;
            map[x][y] = i;
            if (y == 9)
                dfs(x + 1, 1);
            else
                dfs(x, y + 1);
            map[x][y] = 0;
            K[In[x][y]][i] = 0;
            H[x][i] = 0;
            S[y][i] = 0;
        }
    }
}
int main()
{
    for (int l = 0; l < 3; l++)
    {
        for (int i = 1; i <= 5; i++)
        {
            if (i & 1)
            {
                gets(s);
                int j = 0;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][1][((i + 1) >> 1) + l * 3][2] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][2][((i + 1) >> 1) + l * 3][1] = -Greater[((i + 1) >> 1) + l * 3][1][((i + 1) >> 1) + l * 3][2];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][2][((i + 1) >> 1) + l * 3][3] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][3][((i + 1) >> 1) + l * 3][2] = -Greater[((i + 1) >> 1) + l * 3][2][((i + 1) >> 1) + l * 3][3];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][4][((i + 1) >> 1) + l * 3][5] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][5][((i + 1) >> 1) + l * 3][4] = -Greater[((i + 1) >> 1) + l * 3][4][((i + 1) >> 1) + l * 3][5];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][5][((i + 1) >> 1) + l * 3][6] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][6][((i + 1) >> 1) + l * 3][5] = -Greater[((i + 1) >> 1) + l * 3][5][((i + 1) >> 1) + l * 3][6];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][7][((i + 1) >> 1) + l * 3][8] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][8][((i + 1) >> 1) + l * 3][7] = -Greater[((i + 1) >> 1) + l * 3][7][((i + 1) >> 1) + l * 3][8];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][8][((i + 1) >> 1) + l * 3][9] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][9][((i + 1) >> 1) + l * 3][8] = -Greater[((i + 1) >> 1) + l * 3][8][((i + 1) >> 1) + l * 3][9];
                j++;
            }
            else
            {
                gets(s);
                int j = 0;
                for (int k = 1; k <= 9; k++)
                {
                    while (s[j] != 'v' && s[j] != '^')
                        j++;
                    Greater[(i >> 1) + l * 3][k][(i >> 1) + 1 + l * 3][k] = (s[j] == 'v' ? 1 : -1);
                    Greater[(i >> 1) + 1 + l * 3][k][(i >> 1) + l * 3][k] = -Greater[(i >> 1) + l * 3][k][(i >> 1) + 1 + l * 3][k];
                    j++;
                }
            }
        }
    }
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            In[i][j] = 1;
    for (int i = 4; i <= 6; i++)
        for (int j = 1; j <= 3; j++)
            In[i][j] = 2;
    for (int i = 7; i <= 9; i++)
        for (int j = 1; j <= 3; j++)
            In[i][j] = 3;
    for (int i = 1; i <= 3; i++)
        for (int j = 4; j <= 6; j++)
            In[i][j] = 4;
    for (int i = 4; i <= 6; i++)
        for (int j = 4; j <= 6; j++)
            In[i][j] = 5;
    for (int i = 7; i <= 9; i++)
        for (int j = 4; j <= 6; j++)
            In[i][j] = 6;
    for (int i = 1; i <= 3; i++)
        for (int j = 7; j <= 9; j++)
            In[i][j] = 7;
    for (int i = 4; i <= 6; i++)
        for (int j = 7; j <= 9; j++)
            In[i][j] = 8;
    for (int i = 7; i <= 9; i++)
        for (int j = 7; j <= 9; j++)
            In[i][j] = 9;
    dfs(1, 1);
}
// Problem3485:
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;
char s[50];
int Greater[10][10][10][10];
int In[10][10];
bool H[10][10], S[10][10], K[10][10];
int map[10][10];
bool OK(int x, int y, int i)
{
    if (H[x][i])
        return 0;
    if (S[y][i])
        return 0;
    if (K[In[x][y]][i])
        return 0;
    if (Greater[x][y][x - 1][y] == 1 && i < map[x - 1][y])
        return 0;
    if (Greater[x][y][x][y - 1] == 1 && i < map[x][y - 1])
        return 0;
    if (Greater[x][y][x - 1][y] == -1 && i > map[x - 1][y])
        return 0;
    if (Greater[x][y][x][y - 1] == -1 && i > map[x][y - 1])
        return 0;
    return 1;
}
int ans = 0;
void dfs(int x, int y)
{
    //ans++;
    //printf("%d %d\n", x, y);
    if (x == 10 && y == 1)
    {
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
                printf("%d ", map[i][j]);
            printf("\n");
        }
        exit(0);
    }
    for (int i = 9; i >= 1; i--)
    {
        if (OK(x, y, i))
        {
            K[In[x][y]][i] = 1;
            H[x][i] = 1;
            S[y][i] = 1;
            map[x][y] = i;
            if (y == 9)
                dfs(x + 1, 1);
            else
                dfs(x, y + 1);
            map[x][y] = 0;
            K[In[x][y]][i] = 0;
            H[x][i] = 0;
            S[y][i] = 0;
        }
    }
}
int main()
{
    for (int l = 0; l < 3; l++)
    {
        for (int i = 1; i <= 5; i++)
        {
            if (i & 1)
            {
                gets(s);
                int j = 0;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][1][((i + 1) >> 1) + l * 3][2] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][2][((i + 1) >> 1) + l * 3][1] = -Greater[((i + 1) >> 1) + l * 3][1][((i + 1) >> 1) + l * 3][2];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][2][((i + 1) >> 1) + l * 3][3] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][3][((i + 1) >> 1) + l * 3][2] = -Greater[((i + 1) >> 1) + l * 3][2][((i + 1) >> 1) + l * 3][3];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][4][((i + 1) >> 1) + l * 3][5] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][5][((i + 1) >> 1) + l * 3][4] = -Greater[((i + 1) >> 1) + l * 3][4][((i + 1) >> 1) + l * 3][5];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][5][((i + 1) >> 1) + l * 3][6] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][6][((i + 1) >> 1) + l * 3][5] = -Greater[((i + 1) >> 1) + l * 3][5][((i + 1) >> 1) + l * 3][6];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][7][((i + 1) >> 1) + l * 3][8] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][8][((i + 1) >> 1) + l * 3][7] = -Greater[((i + 1) >> 1) + l * 3][7][((i + 1) >> 1) + l * 3][8];
                j++;
                while (s[j] != '<' && s[j] != '>')
                    j++;
                Greater[((i + 1) >> 1) + l * 3][8][((i + 1) >> 1) + l * 3][9] = (s[j] == '>' ? 1 : -1);
                Greater[((i + 1) >> 1) + l * 3][9][((i + 1) >> 1) + l * 3][8] = -Greater[((i + 1) >> 1) + l * 3][8][((i + 1) >> 1) + l * 3][9];
                j++;
            }
            else
            {
                gets(s);
                int j = 0;
                for (int k = 1; k <= 9; k++)
                {
                    while (s[j] != 'v' && s[j] != '^')
                        j++;
                    Greater[(i >> 1) + l * 3][k][(i >> 1) + 1 + l * 3][k] = (s[j] == 'v' ? 1 : -1);
                    Greater[(i >> 1) + 1 + l * 3][k][(i >> 1) + l * 3][k] = -Greater[(i >> 1) + l * 3][k][(i >> 1) + 1 + l * 3][k];
                    j++;
                }
            }
        }
    }
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            In[i][j] = 1;
    for (int i = 4; i <= 6; i++)
        for (int j = 1; j <= 3; j++)
            In[i][j] = 2;
    for (int i = 7; i <= 9; i++)
        for (int j = 1; j <= 3; j++)
            In[i][j] = 3;
    for (int i = 1; i <= 3; i++)
        for (int j = 4; j <= 6; j++)
            In[i][j] = 4;
    for (int i = 4; i <= 6; i++)
        for (int j = 4; j <= 6; j++)
            In[i][j] = 5;
    for (int i = 7; i <= 9; i++)
        for (int j = 4; j <= 6; j++)
            In[i][j] = 6;
    for (int i = 1; i <= 3; i++)
        for (int j = 7; j <= 9; j++)
            In[i][j] = 7;
    for (int i = 4; i <= 6; i++)
        for (int j = 7; j <= 9; j++)
            In[i][j] = 8;
    for (int i = 7; i <= 9; i++)
        for (int j = 7; j <= 9; j++)
            In[i][j] = 9;
    dfs(1, 1);
}
// Problem3500:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define int long long
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int MAXN = 200005;
struct edge
{
    int END, next, v;
} v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
vector<int> st;
int Max = 0, Size, Num;
int C1[MAXN], C2[MAXN], Sum1[MAXN], Sum2[MAXN];
void dfs(int rt, int fa, int dis)
{
    if (dis > Max)
    {
        Max = dis;
        Size = 1;
        Num = rt;
        st.clear();
        st.push_back(rt);
    }
    else if (dis == Max)
    {
        st.push_back(rt);
        Size++;
    }
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        dfs(v[i].END, rt, dis + v[i].v);
    }
}
int ans = 0, size1, size2;
void dfs(int rt, int fa)
{
    Sum1[rt] += C1[rt];
    Sum2[rt] += C2[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        dfs(v[i].END, rt);
        Sum1[rt] += Sum1[v[i].END];
        Sum2[rt] += Sum2[v[i].END];
    }
    if (Sum1[rt] == size1 && !Sum2[rt])
        ans++;
    if (Sum2[rt] == size2 && !Sum1[rt])
        ans++;
}
signed main()
{
    memset(first, -1, sizeof(first));
    int n = read();
    int a, b, c;
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read(), c = read();
        add(a, b, c);
        add(b, a, c);
    }
    dfs(1, 0, 0);
    for (int i = 0; i < st.size(); i++)
        C1[st[i]] = 1;
    st.clear();
    size1 = Size;
    Max = 0;
    dfs(Num, 0, 0);
    for (int i = 0; i < st.size(); i++)
        C2[st[i]] = 1;
    size2 = Size;
    printf("%lld\n", Max);
    dfs(1, 0);
    printf("%lld\n", ans);
}
// Problem3506:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
int a[15], len, cnt;
long long Num[300005], size[300005];
long long f[15][300005][2];
void dfs(int now, int Dep, long long ans)
{
    if (Dep == len)
    {
        Num[++cnt] = ans;
        return;
    }
    if (!ans)
        return;
    for (int i = now; i <= 9; i++)
        dfs(i, Dep + 1, ans * i);
}
struct Node
{
    int x, y;
    long long v;
    Node(int x1 = 0, int y1 = 0, long long v1 = 0)
    {
        x = x1, y = y1, v = v1;
    }
    bool operator<(const Node &a) const
    {
        return v < a.v;
    }
};
priority_queue<Node> Q;
int cmp(const int &a, const int &b)
{
    return a > b;
}
signed main()
{
    int k;
    long long n;
    scanf("%lld%lld", &n, &k);
    while (n)
        a[++len] = n % 10, n /= 10;
    Num[++cnt] = 0;
    dfs(0, 0, 1);
    sort(Num + 1, Num + cnt + 1);
    cnt = unique(Num + 1, Num + cnt + 1) - Num - 1;
    f[0][2][0] = 1;
    // for (int i = 1; i <= cnt; i++)
    // printf ("%d ", Num[i]);
    // while (1);
    for (int i = 0; i <= len; i++)
        for (int j = 1; j <= cnt; j++)
            for (int l = 0; l <= 1; l++)
                if (f[i][j][l])
                    for (int x = (i == 0 ? 0 : 1); x <= 9; x++)
                    {
                        int nxt = lower_bound(Num + 1, Num + cnt + 1, Num[j] * x) - Num;
                        f[i + 1][nxt][(x + l) > a[i + 1]] += f[i][j][l];
                    }
    for (int i = 1; i <= cnt; i++)
    {
        for (int j = 1; j <= len - 1; j++)
            size[i] += f[j][i][0] + f[j][i][1];
        size[i] += f[len][i][0];
    }
    // for (int i = 1; i <= cnt; i++)
    // printf ("%lld ", size[i]);
    // while (1);
    sort(size + 1, size + cnt + 1, cmp);
    Q.push(Node(2, 2, size[2] * size[2]));
    int ans = 0;
    while (!Q.empty() && k)
    {
        Node x = Q.top();
        Q.pop();
        ans = (ans + x.v) % MOD;
        if (!(--k))
            break;
        if (x.x != x.y)
        {
            ans = (ans + x.v) % MOD;
            if (!(--k))
                break;
            Q.push(Node(x.x + 1, x.y, size[x.x + 1] * size[x.y]));
        }
        if (x.x == 2)
            Q.push(Node(x.x, x.y + 1, size[x.x] * size[x.y + 1]));
    }
    printf("%lld", ans);
    // while (1);
}
// Problem3541:
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
const int INF = 1000000000;
const int full = 30;
int n;
struct data
{
    int val, i;
    bool operator<(const data &a) const
    {
        return val > a.val;
    }
} a[50005];
struct Trie
{
    struct Node
    {
        int s;
        Node *ch[2];
        Node()
        {
            ch[0] = ch[1] = NULL;
            s = 0;
        }
    } * root[100005], *null;
    Trie()
    {
        null = new Node();
        null->ch[0] = null->ch[1] = null;
        root[0] = new Node();
        root[0]->ch[0] = root[0]->ch[1] = null;
    }
    Node *NewNode()
    {
        Node *rt = new Node();
        rt->ch[0] = rt->ch[1] = null;
        return rt;
    }
    void copy(Node *&a, Node *b)
    {
        if (b == null)
            a = null;
        else
            a = NewNode(), *a = *b;
    }
    void insert(int x, int cnt)
    {
        copy(root[cnt], root[cnt - 1]);
        Node *rt1 = root[cnt], *rt2 = root[cnt - 1];
        for (int i = full; i >= 0; i--)
        {
            int k = (x >> i) & 1;
            copy(rt1->ch[k], rt2->ch[k]);
            if (rt1->ch[k] == null)
                rt1->ch[k] = NewNode();
            rt1 = rt1->ch[k], rt2 = rt2->ch[k];
            rt1->s++;
        }
    }
    int Query(int val, int l, int r)
    {
        int res = 0;
        Node *rt1 = root[r], *rt2 = root[l - 1];
        for (int i = full; i >= 0; i--)
        {
            int next = (val >> i) & 1;
            if (rt1->ch[next ^ 1]->s - rt2->ch[next ^ 1]->s)
            {
                rt1 = rt1->ch[next ^ 1], rt2 = rt2->ch[next ^ 1];
                res |= (1 << i);
            }
            else
            {
                rt1 = rt1->ch[next], rt2 = rt2->ch[next];
            }
        }
        return res;
    }
} root;
set<int> st;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i].val);
        a[i].i = i;
        root.insert(a[i].val, i);
    }
    st.insert(-1), st.insert(INF), st.insert(-2), st.insert(INF + 1);
    sort(a + 1, a + n + 1);
    st.insert(a[1].i);
    int ans = 0;
    for (int i = 2; i <= n; i++)
    {
        int l = a[i].i, r = a[i].i;
        set<int>::iterator T, P;
        P = st.lower_bound(a[i].i);
        T = P;
        r = *T;
        T++;
        r = *T - 1;
        l = *--P;
        P--;
        l = *P + 1;
        l = max(1, l), r = min(r, n);
        if (l != r)
            ans = max(ans, root.Query(a[i].val, l, r));
        st.insert(a[i].i);
    }
    printf("%d", ans);
}
// Problem3542:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
const int MOD = 1000000007;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct edge
{
    int END, next, v;
} v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
long long f[MAXN][MAXN];
long long g[MAXN];
long long Sum[MAXN][MAXN];
long long C[MAXN][MAXN];
int size[MAXN];
void dfs(int rt, int fa)
{
    size[rt] = f[rt][0] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        dfs(v[i].END, rt);
        for (int j = 0; j < size[rt] + size[v[i].END]; j++)
            g[j] = 0;
        if (v[i].v == 1)
            for (int j = 0; j < size[rt]; j++)
                for (int k = 0; k <= size[v[i].END]; k++)
                {
                    long long tmp = f[rt][j] * Sum[v[i].END][k - 1] % MOD;
                    long long rmp = C[j + k][j] * C[size[rt] + size[v[i].END] - k - j - 1][size[v[i].END] - k] % MOD;
                    (g[j + k] += tmp * rmp % MOD) %= MOD;
                }
        else
            for (int j = 0; j < size[rt]; j++)
                for (int k = 0; k <= size[v[i].END]; k++)
                {
                    long long tmp = f[rt][size[rt] - j - 1] * (Sum[v[i].END][size[v[i].END] - 1] - Sum[v[i].END][size[v[i].END] - k - 1] + MOD) % MOD;
                    long long rmp = C[j + k][j] % MOD * C[size[v[i].END] + size[rt] - k - j - 1][size[v[i].END] - k] % MOD;
                    (g[size[rt] + size[v[i].END] - j - k - 1] += tmp * rmp % MOD) %= MOD;
                }
        size[rt] += size[v[i].END];
        for (int j = 0; j < size[rt]; j++)
            f[rt][j] = g[j];
    }
    Sum[rt][0] = f[rt][0];
    for (int i = 1; i < size[rt]; i++)
        Sum[rt][i] = (Sum[rt][i - 1] + f[rt][i]) % MOD;
}
int main()
{
    int t = read();
    C[0][0] = 1;
    for (int i = 1; i <= 1000; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    while (t--)
    {
        memset(size, 0, sizeof(size));
        memset(Sum, 0, sizeof(Sum));
        memset(f, 0, sizeof(f));
        memset(first, -1, sizeof(first));
        p = 0;
        int n = read(), a, b;
        char c[3];
        for (int i = 1; i < n; i++)
        {
            scanf("%d%s%d", &a, c, &b);
            a++, b++;
            if (c[0] == '>')
                add(a, b, 1), add(b, a, -1);
            else
                add(a, b, -1), add(b, a, 1);
        }
        dfs(1, 0);
        printf("%lld\n", Sum[1][n - 1]);
    }
    // while (1);
}
// Problem3545:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct point
{
    long long x, y, ID;
    bool operator<(const point &a) const
    {
        return x < a.x;
    }
} a[100005];
bool cmp(const point a, const point b)
{
    return a.y < b.y;
}
long long Lx[100005], Rx[100005], Ly[100005], Ry[100005];
long long dis(int i, int j)
{
    return abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y);
}
int main()
{
    int n;
    scanf("%d", &n);
    int x, y;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &x, &y);
        a[i].x = x + y;
        a[i].y = x - y;
        a[i].ID = i;
    }
    sort(a + 1, a + n + 1);
    long long S = 0;
    for (int i = 1; i <= n; i++)
        S += a[i].x, Lx[a[i].ID] = abs(S - a[i].x * i);
    S = 0;
    for (int i = n; i >= 1; i--)
        S += a[i].x, Rx[a[i].ID] = abs(S - a[i].x * (n - i + 1));
    S = 0;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        S += a[i].y, Ly[a[i].ID] = abs(S - a[i].y * i);
    S = 0;
    for (int i = n; i >= 1; i--)
        S += a[i].y, Ry[a[i].ID] = abs(S - a[i].y * (n - i + 1));
    long long ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= n; i++)
        ans = min(ans, Lx[i] + Ly[i] + Rx[i] + Ry[i]);
    printf("%lld", ans / 2);
}
// Problem3548:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 100005;
struct Node
{
    Node *ch[2];
    int s, key, Max, v;
    Node(int x)
    {
        ch[0] = ch[1] = NULL;
        s = 1, key = rand(), v = Max = x;
    }
#define size(_) ((_) ? (_)->s : 0)
#define Max(_) ((_) ? (_)->Max : 0)
    void Pushup()
    {
        s = size(ch[0]) + size(ch[1]) + 1;
        Max = max(Max(ch[0]), max(Max(ch[1]), v));
    }
} * root;
Node *Merge(Node *A, Node *B)
{
    if (!A)
        return B;
    if (!B)
        return A;
    if (A->key > B->key)
    {
        A->ch[1] = Merge(A->ch[1], B);
        A->Pushup();
        return A;
    }
    else
    {
        B->ch[0] = Merge(A, B->ch[0]);
        B->Pushup();
        return B;
    }
}
typedef pair<Node *, Node *> DNode;
DNode Split(Node *rt, int k)
{
    if (!rt)
        return DNode(NULL, NULL);
    DNode o;
    if (k <= size(rt->ch[0]))
    {
        o = Split(rt->ch[0], k);
        rt->ch[0] = o.second;
        rt->Pushup();
        o.second = rt;
    }
    else
    {
        o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
        rt->ch[1] = o.first;
        rt->Pushup();
        o.first = rt;
    }
    return o;
}
int Ans[N], Max_Ans;
void Insert(int x, int k)
{
    DNode y = Split(root, k);
    Ans[x] = Max(y.first) + 1;
    Max_Ans = max(Max_Ans, Ans[x]);
    Node *n = new Node(Ans[x]);
    root = Merge(y.first, Merge(n, y.second));
}
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        Insert(i, read());
        printf("%d\n", Max_Ans);
    }
}
// Problem3595:
#include <cstdio>
// struct Trie{
//     vector<int> Q;
//     Trie *ch[26],*fail;
//     Trie(){
//         Q.clear();memset(ch,0,sizeof(ch));fail=NULL;
//     }
//     void* operator new(size_t size);
// }*root,*C,*num,*Q[100005];
// void* Trie::operator new(size_t size){
//     if(C==num){
//         C=new Trie[1<<15];
//         num=C+(1<<15);
//     }
//     return C++;
// }
using namespace std;
const int full = 24, fix = 1e7;
class Node
{
  public:
    int size;
    Node *ch[2];
    Node()
    {
        ch[0] = ch[1] = NULL;
        size = 0;
    }
#define size(_) ((_) ? (_)->size : 0)
    void *operator new(size_t size);
} * root, *C, *num;
void *Node::operator new(size_t size)
{
    if (C == num)
    {
        C = new Node[1 << 5];
        num = C + (1 << 5);
    }
    return C++;
}
void Insert(int x, int add)
{
    x += fix;
    Node *rt = root;
    for (int i = full; i >= 0; i--)
    {
        bool next = x >> i & 1;
        if (!rt->ch[next])
            rt->ch[next] = new Node;
        rt = rt->ch[next];
        rt->size += add;
    }
}
int rank(int x)
{
    x += fix;
    int res = 0;
    Node *rt = root;
    for (int i = full; i >= 0; i--)
    {
        bool next = x >> i & 1;
        if (next)
            res += size(rt->ch[0]);
        if (!rt->ch[next])
            break;
        rt = rt->ch[next];
    }
    return res;
}
int kth(int k)
{
    int res = 0;
    Node *rt = root;
    for (int i = full; i >= 0; i--)
    {
        if (k > size(rt->ch[0]))
        {
            k -= size(rt->ch[0]);
            res |= 1 << i;
            if (!rt->ch[1])
                break;
            rt = rt->ch[1];
        }
        else

            rt = rt->ch[0];
    }
    return res - fix;
}
int main()
{
    // freopen("phs.in", "r", stdin);
    // freopen("phs.out", "w", stdout);
    root = new Node();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        switch (op)
        {
        case 1:
            Insert(x, 1);
            break;
        case 2:
            Insert(x, -1);
            break;
        case 3:
            printf("%d\n", rank(x) + 1);
            break;
        case 4:
            printf("%d\n", kth(x));
            break;
        case 5:
            printf("%d\n", kth(rank(x)));
            break;
        case 6:
            printf("%d\n", kth(rank(x + 1) + 1));
        }
    }
}
// Problem3685:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
using std::max;
class data
{
  public:
    int x, v;
    bool operator<(const data &a) const
    {
        return x < a.x;
    }
} a[1005];
int dp[1005][1005];
int main()
{
    //freopen("pogocow.in","r",stdin);
    //freopen("pogocow.out","w",stdout);
    memset(dp, 0x80, sizeof(dp));
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].x, &a[i].v);
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
        dp[i][i] = dp[0][i] = a[i].v;
    int ans = -9999999;
    for (int i = 1; i <= n; i++)
    {
        int k = i - 1, var = a[i].v;
        for (int j = i + 1; j <= n; j++)
        {
            while (k >= 0 && a[j].x - a[i].x >= a[i].x - a[k].x)
                var = max(dp[k][i], var), k--;
            dp[i][j] = max(dp[i][j], var + a[j].v);
            ans = max(ans, dp[i][j]);
        }
    }

    //puts("");
    memset(dp, 0x80, sizeof(dp));
    std::reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
        dp[i][i] = a[i].v;
    for (int i = 1; i <= n; i++)
    {
        int k = i - 1, var = a[i].v;
        for (int j = i + 1; j <= n; j++)
        {
            while (k >= 0 && a[j].x - a[i].x <= a[i].x - a[k].x)
                var = max(dp[k][i], var), k--;
            dp[i][j] = max(dp[i][j], var + a[j].v);
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%d\n", ans);
    //while(1);
}
// Problem3686:
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int que[2][200005];
int h[2], t[2];
int a[200005], n, L, R, len;
long double sum[200005];
bool Judge(long double mid)
{
    for (int i = 1; i <= 2 * n; i++)
        sum[i] = sum[i - 1] + (long double)a[i] - mid;
    h[0] = h[1] = 1, t[0] = t[1] = 0;
    for (int i = L; i <= 2 * n; i++)
    {
        int j = i - L, now = i & 1;
        while (h[now] <= t[now] && sum[j] < sum[que[now][t[now]]])
            t[now]--;
        que[now][++t[now]] = j;
        if (i - que[now][h[now]] > R)
            h[now]++;
        if (sum[i] - sum[que[now][h[now]]] > 1e-9)
        {
            len = i - que[now][h[now]];
            return 1;
        }
    }
    return 0;
}
long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int main()
{
    long double l = 0, r = 0;
    scanf("%d%d%d", &n, &L, &R);
    L += (L & 1), R -= (R & 1);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        r = max((long double)a[i], r);
    }
    for (int i = 1; i <= n; i++)
        a[i + n] = a[i];
    r += 1;
    int d = 0;
    while (r - l > 1e-9)
    {
        long double mid = (l + r) / 2;
        if (Judge(mid))
            l = mid;
        else
            r = mid;
    }
    //cout<<l<<endl;
    long long Z = round(len * l);
    long long M = len;
    long long Gcd = gcd(Z, M);
    Z /= Gcd, M /= Gcd;
    if (M == 1)
        return printf("%lld\n", Z), 0;
    printf("%lld/%lld", Z, M);
}
// Problem3689:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
class edge
{
  public:
    int END, next;
} v[2000005];
int first[1000005], p = 1;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int fa[1000005], dep[1000005];
int Idx[1000005];
void dfs(int rt, int f, int Dep)
{
    fa[rt] = f;
    dep[rt] = Dep;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END != f)
        {
            Idx[v[i].END] = (i + 1) / 2;
            dfs(v[i].END, rt, Dep + 1);
        }
    }
}
bool mark[1000005];
void Mark(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);
    while (dep[a] > dep[b])
    {
        mark[Idx[a]] = 1;
        a = fa[a];
    }
    while (a != b)
    {
        mark[Idx[a]] = 1;
        mark[Idx[b]] = 1;
        a = fa[a];
        b = fa[b];
    }
}
int get_ans(int x)
{
    int ans = 0;
    while (x != 1)
    {
        if (mark[Idx[x]])
        {
            ans = Idx[x];
            break;
        }
        x = fa[x];
    }
    return ans;
}
int main()
{
    memset(first, -1, sizeof(first));
    int n, m, a, b;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs(1, 0, 1);
    int op, s, e;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d", &s);
            printf("%d\n", get_ans(s));
        }
        else
        {
            scanf("%d%d", &s, &e);
            Mark(s, e);
        }
    }
}

// Problem3710:
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int size;
bool comp(int a, int b)
{
    return a > b;
}
int r[1010], l[1010];
int a[1000005];
int b[1000005], belong[1000005];
int add[1005];
void rebuild(int x)
{
    for (int i = l[x]; i <= r[x]; i++)
        b[i] = a[i];
    sort(b + l[x], b + r[x] + 1, comp);
}
int solve(int L, int R, int c)
{
    int l = L, r = R, ans = R + 1;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (b[mid] < c)
            l = mid + 1;
        else
            ans = mid, r = mid - 1;
    }
    return R - ans + 1;
}
int main()
{
    int n, Q;
    scanf("%d%d", &n, &Q);
    size = sqrt(n);
    int tot = (n - 1) / size + 1;
    for (int i = 1; i <= n; i++)
    {
        if (!l[(i - 1) / size + 1])
            l[(i - 1) / size + 1] = i;
        r[(i - 1) / size + 1] = i;
        belong[i] = (i - 1) / size + 1;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        b[i] = a[i];
    }
    for (int i = 1; i <= tot; i++)
        sort(b + l[i], b + r[i] + 1, comp);
    char c[10];
    int s, e, m;
    while (Q--)
    {
        scanf("%s", c);
        scanf("%d%d%d", &s, &e, &m);
        if (c[0] == 'A')
        {
            int ans = 0;
            if (belong[s] == belong[e])
            {
                for (int i = s; i <= e; i++)
                    if (b[i] + add[belong[i]] >= m)
                        ans++;
                printf("%d\n", ans);
            }
            else
            {
                for (int i = belong[s] + 1; i <= belong[e] - 1; i++)
                    ans += upper_bound(b + l[i], b + r[i] + 1, m - add[i], comp) - (b + l[i]);
                for (int i = s; i <= r[belong[s]]; i++)
                    if (b[i] + add[belong[i]] >= m)
                        ans++;
                for (int i = l[belong[e]]; i <= e; i++)
                    if (b[i] + add[belong[i]] >= m)
                        ans++;
                printf("%d\n", ans);
            }
        }
        else
        {
            if (belong[s] == belong[e])
            {
                for (int i = s; i <= e; i++)
                    a[i] += m;
                rebuild(belong[s]);
            }
            else
            {
                for (int i = belong[s] + 1; i <= belong[e] - 1; i++)
                    add[i] += m;
                for (int i = s; i <= r[belong[s]]; i++)
                    a[i] += m;
                rebuild(belong[s]);
                for (int i = l[belong[e]]; i <= e; i++)
                    a[i] += m;
                rebuild(belong[e]);
            }
        }
    }
}
// Problem3743:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int fa[30005], size[30005], d[30005];
int find(int x)
{
    if (fa[x] == x)
        return x;
    int o = fa[x];
    fa[x] = find(fa[x]);
    d[x] += d[o];
    return fa[x];
}
void merge(int a, int b)
{
    int x = find(a), y = find(b);
    fa[y] = x;
    d[y] = size[x];
    size[x] += size[y];
}
int main()
{
    char s[10];
    int p;
    for (int i = 1; i <= 30000; i++)
        fa[i] = i, size[i] = 1;
    scanf("%d", &p);
    for (int i = 1; i <= p; i++)
    {
        int a, b;
        scanf("%s", s);
        if (s[0] == 'M')
        {
            scanf("%d%d", &a, &b);
            merge(a, b);
        }
        else
        {
            scanf("%d", &a);
            printf("%d\n", size[find(a)] - d[a] - 1);
        }
    }
}
// Problem3842:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
double ex = 1e-6;
int a[100005], Sum;
int n;
bool Judge(long double x)
{
    long double Max = -10000000, sum = 0;
    for (int i = 2; i <= n - 1; i++)
    {
        long double now = a[i] - x;
        sum += now;
        if (sum > Max)
            Max = sum;
        if (sum < 0)
            sum = 0;
    }
    // printf("%.6lf\n",Max);
    return Sum - n * x - Max >= 0;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Sum += a[i];
    }
    // printf("%d\n", Sum);
    // while(1);
    long double l = 0, r = 1000000;
    while (r - l > ex)
    {
        long double mid = (r + l) / 2;
        if (Judge(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%.3lf", (double)l);
}

// Problem3882:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[1005][1005];
int SumX[1005], SumY[1005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%1d", &a[i][j]);
            SumX[i] ^= a[i][j];
            SumY[j] ^= a[i][j];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            ans += SumX[i] ^ SumY[j] ^ a[i][j];
    printf("%d", min(ans, n * n - ans));
}

// Problem3930:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next, v;
} v[500005 << 1];
int first[500005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int q[500005];
double f[500005], g[500005];
void Get_F(int rt, int fa)
{
    f[rt] = 1.0 - q[rt] / 100.0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        Get_F(v[i].END, rt);
        f[rt] *= (f[v[i].END] + (1.0 - f[v[i].END]) * (1.0 - v[i].v / 100.0));
    }
}
void Get_G(int rt, int fa, int j)
{
    if (rt == 1)
        g[rt] = 1;
    else
    {
        double P = g[fa] * f[fa] / (f[rt] + (1.0 - f[rt]) * (1.0 - v[j].v / 100.0));
        g[rt] = P + (1.0 - P) * (1.0 - v[j].v / 100.0);
    }
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        Get_G(v[i].END, rt, i);
    }
}
int main()
{
    memset(first, -1, sizeof(first));
    int n;
    scanf("%d", &n);
    int a, b, c;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &q[i]);
    Get_F(1, 0);
    Get_G(1, 0, 0);
    double ans = 0;
    for (int i = 1; i <= n; i++)
        ans += (1 - f[i] * g[i]);
    printf("%.6lf", ans);
}
// Problem3945:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Seg_Node
{
    int Min;
    Seg_Node *ch[2];
    Seg_Node()
    {
        Min = 0;
    }
} * root[200005], *null;
Seg_Node *NewSeg_Node()
{
    Seg_Node *S = new Seg_Node();
    S->ch[0] = S->ch[1] = null;
    return S;
}
void copy(Seg_Node *&a, Seg_Node *b)
{
    if (b == null)
        a = null;
    else
        a = NewSeg_Node(), *a = *b;
}
void Update(int v, int c, int l, int r, Seg_Node *&rt1, Seg_Node *rt2)
{
    copy(rt1, rt2);
    if (rt1 == null)
        rt1 = NewSeg_Node();
    if (l == r)
    {
        rt1->Min = c;
        return;
    }
    int m = l + r >> 1;
    if (v <= m)
        Update(v, c, l, m, rt1->ch[0], rt2->ch[0]);
    else
        Update(v, c, m + 1, r, rt1->ch[1], rt2->ch[1]);
    rt1->Min = min(rt1->ch[0]->Min, rt1->ch[1]->Min);
}
int Query(int l, int r, Seg_Node *rt, int x)
{
    if (l == r)
        return l;
    int mid = l + r >> 1;
    if (rt->ch[0]->Min < x)
        return Query(l, mid, rt->ch[0], x);
    else
        return Query(mid + 1, r, rt->ch[1], x);
}
int main()
{
    null = new Seg_Node();
    null->ch[0] = null->ch[1] = null;
    root[0] = null;
    int n, a, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        Update(a, i, 0, 1e9, root[i], root[i - 1]);
    }
    int l, r;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", Query(0, 1e9, root[r], l));
    }
}
// Problem3954:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[10005];
int sum[505][5505];
int N = 501, M = 5501;
#define lowbit(_) ((_) & (-_))
void add(int x, int y, int ad)
{
    for (int i = x; i <= N; i += lowbit(i))
        for (int j = y; j <= M; j += lowbit(j))
            sum[i][j] = max(ad, sum[i][j]);
}
int Query(int x, int y)
{
    int Max = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            Max = max(Max, sum[i][j]);
    return Max;
}
int main()
{
    //freopen("data.in","r",stdin);
    //freopen("data.out","w",stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    int tmp;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = k; j >= 0; j--)
            tmp = Query(j + 1, a[i] + j) + 1, add(j + 1, a[i] + j, tmp), ans = max(tmp, ans);
    printf("%d", ans);
}

// Problem3958:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
long long K;
long long f[25][37000];
int a[25];
long long dfs(int now, int Sum, bool top)
{
    if (now == 0)
        return Sum;
    if (!top && f[now][Sum] != -1)
        return f[now][Sum];
    int n = top ? a[now] : K - 1;
    long long ans = 0;
    for (int i = 0; i <= n; i++)
        ans += dfs(now - 1, Sum + i * (now - 1), top && (i == n));
    if (!top)
        f[now][Sum] = ans;
    return ans;
}
long long dfs(int now, int Sum, int num, bool top)
{
    if (Sum < 0)
        return 0;
    if (!now)
        return Sum;
    if (!top && f[now][Sum] != -1)
        return f[now][Sum];
    int n = top ? a[now] : K - 1;
    long long ans = 0;
    for (int i = 0; i <= n; i++)
    {
        if (now >= num)
            ans += dfs(now - 1, i + Sum, num, top && (i == n));
        else
            ans += dfs(now - 1, Sum - i, num, top && (i == n));
    }
    if (!top)
        f[now][Sum] = ans;
    return ans;
}
long long Calc(long long x)
{
    int len = 0;
    while (x)
        a[++len] = x % K, x /= K;
    memset(f, -1, sizeof(f));
    long long ans = dfs(len, 0, 1);
    for (int i = 2; i <= len; i++)
    {
        memset(f, -1, sizeof(f));
        ans -= dfs(len, 0, i, 1);
    }
    return ans;
}
int main()
{
    long long L, R;
    scanf("%lld%lld%lld", &L, &R, &K);
    printf("%lld", Calc(R) - Calc(L - 1));
}
// Problem3970:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1000005;
const int INF = 0x7fffffff;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct edge
{
    int END, next, v;
} v[N << 1], e[N << 1];
int first[N], p, head[N], t;
struct funadd
{
    void operator()(int a, int b)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
    void operator()(int a, int b, int c)
    {
        e[t].END = b;
        e[t].v = c;
        e[t].next = head[a];
        head[a] = t++;
    }
} add;
int f[N << 1][21], dep[N], L[N], R[N], cnt;
void Init_Dfs(int rt, int fa, int Dep)
{
    L[rt] = ++cnt;
    f[rt][0] = fa;
    dep[rt] = Dep;
    for (int i = 1; i <= 20; i++)
        f[rt][i] = f[f[rt][i - 1]][i - 1];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        Init_Dfs(v[i].END, rt, Dep + 1);
    }
    R[rt] = cnt;
}
int LCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    int d = dep[x] - dep[y];
    for (int i = 20; i >= 0; i--)
        if (d & (1 << i))
            d -= (1 << i), x = f[x][i];
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
int pt[N], st[N], top, vis[N];
bool Query[N];
bool cmp(const int &a, const int &b)
{
    return L[a] < L[b];
}
#define In(a, b) (L[b] <= L[a] && R[a] <= R[b])
long long Min[N], Max[N], ans1, ans2, k;
long long size[N], Sum;
void dfs(int rt)
{
    size[rt] = Query[rt];
    Min[rt] = Query[rt] ? 0 : INF, Max[rt] = Query[rt] ? 0 : -INF;
    for (int i = head[rt]; i != -1; i = e[i].next)
    {
        dfs(e[i].END);
        size[rt] += size[e[i].END];
        Sum += size[e[i].END] * (k - size[e[i].END]) * e[i].v;
        ans1 = min(ans1, Min[rt] + Min[e[i].END] + e[i].v);
        Min[rt] = min(Min[rt], Min[e[i].END] + e[i].v);
        ans2 = max(ans2, Max[rt] + Max[e[i].END] + e[i].v);
        Max[rt] = max(Max[rt], Max[e[i].END] + e[i].v);
    }
}
signed main()
{
    // freopen ("tree1.in", "r", stdin);
    // freopen ("tree.out", "w", stdout);
    int n = read(), a, b;
    memset(first, -1, sizeof(first));
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b), add(b, a);
    }
    Init_Dfs(1, 0, 0);
    int Q = read();
    while (Q--)
    {
        k = read();
        int len = k;
        for (int i = 1; i <= k; i++)
            pt[i] = read(), Query[pt[i]] = true, vis[pt[i]] = Q + 1;
        sort(pt + 1, pt + len + 1, cmp);
        for (int i = 1; i < k; i++)
        {
            int lca = LCA(pt[i], pt[i + 1]);
            if (vis[lca] != Q + 1)
                pt[++len] = lca, vis[lca] = Q + 1;
        }
        sort(pt + 1, pt + len + 1, cmp);
        int root = pt[1];
        st[top = 1] = pt[1], t = 0;
        for (int i = 2; i <= len; i++)
        {
            while (top && !In(pt[i], st[top]))
                top--;
            st[++top] = pt[i];
            add(st[top - 1], st[top], dep[st[top]] - dep[st[top - 1]]);
        }
        Sum = 0, ans1 = INF, ans2 = -INF;
        dfs(root);
        printf("%lld %lld %lld\n", Sum, ans1, ans2);
        for (int i = 1; i <= len; i++)
            Query[pt[i]] = 0, head[pt[i]] = -1;
    }
    // while (1);
}
// Problem3972:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int MOD, Sa, Sb, Sc, Sd;
long long F(long long x)
{
    long long ans = 0;
    ans += ((Sa * x % MOD) * x % MOD) * x % MOD;
    (ans += (Sb * x % MOD) * x % MOD) %= MOD;
    (ans += Sc * x % MOD) %= MOD;
    (ans += Sd) %= MOD;
    return ans;
}
int A[5000005];
int main()
{
    int n;
    scanf("%d%d%d%d%d%d%d", &n, &Sa, &Sb, &Sc, &Sd, &A[1], &MOD);
    int Max = A[1], ans = 0;
    for (int i = 2; i <= n; i++)
    {
        A[i] = (F(A[i - 1]) + F(A[i - 2])) % MOD;
        ans = max(ans, (Max - A[i] + 1) >> 1);
        Max = max(Max, A[i]);
    }
    printf("%d", ans);
}
// Problem3983:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int E, S, type, use;
    bool operator<(const edge &a) const
    {
        return type > a.type;
    }
} v[100005];
int fa[20005];
int find(int x)
{
    if (fa[x] != x)
        fa[x] = find(fa[x]);
    return fa[x];
}
bool vis[100005];
int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &v[i].S, &v[i].E, &v[i].type), v[i].use = 0;
    sort(v + 1, v + m + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        if (find(v[i].S) != find(v[i].E))
        {
            fa[find(v[i].S)] = find(v[i].E);
            vis[i] = 1;
            cnt += (v[i].type ^ 1);
        }
    }
    if (cnt > k)
        return printf("no solution\n"), 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    int t = 0;
    for (int i = 1; i <= m; i++)
    {
        if (vis[i] && !v[i].type)
        {
            k--;
            t++;
            v[i].use = 1;
            fa[find(v[i].S)] = find(v[i].E);
        }
    }
    for (int i = 1; i <= m; i++)
    {
        if (k > 0 && !v[i].type && !vis[i] && find(v[i].S) != find(v[i].E))
        {
            k--;
            t++;
            v[i].use = 1;
            fa[find(v[i].S)] = find(v[i].E);
        }
    }
    if (k)
        return printf("no solution\n"), 0;
    for (int i = 1; i <= m; i++)
    {
        if (v[i].type && find(v[i].S) != find(v[i].E))
        {
            t++;
            v[i].use = 1;
            fa[find(v[i].S)] = find(v[i].E);
        }
    }
    if (t != n - 1)
        return printf("no solution\n"), 0;
    for (int i = 1; i <= m; i++)
    {
        if (v[i].use == 1)
            printf("%d %d %d\n", v[i].S, v[i].E, v[i].type);
    }
    // while (1);
}
// Problem3986:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;
const int Maxn = 44721;
int prime[4729], tot = 0;
bool isnprime[44722];
void get_prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= Maxn; i++)
    {
        if (!isnprime[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot; j++)
        {
            if (i * prime[j] > Maxn)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
bool judge(long long x)
{
    int p = sqrt(x);
    for (int i = 1; i <= tot && p >= prime[i]; i++)
        if (x % prime[i] == 0)
            return false;
    return true;
}

// int times = 10;
// unsigned long long pow_mod(unsigned long long x, unsigned long long y, unsigned long long mod)
// {
//     int ans = 1;
//     while (y)
//     {
//         if (y & 1)
//             ans = ans * x % mod;
//         y >>= 1;
//         x = x * x % mod;
//     }
//     return ans;
// }
// bool judge(int p)
// {
//     if (p == 2)
//         return true;
//     for (int i = 1; i <= times; i++)
//     {
//         int a = rand() % (p - 2) + 2;
//         if (pow_mod(a, p, p) != a)
//             return false;
//     }
//     return true;
// }
int allans[1000000];
void dfs(int p, int les, int ans)
{
    if (les == 1)
    {
        allans[++allans[0]] = ans;
        return;
    }
    if (p > tot)
    {
        return;
    }
    if (les - 1 >= prime[p] && judge(les - 1))
        allans[++allans[0]] = ans * (les - 1);
    for (int i = p; prime[i] * prime[i] <= les && i <= tot; i++)
    {
        for (int sum = prime[i] + 1, j = prime[i]; sum <= les; j *= prime[i], sum += j)
        {
            if (les % sum == 0)
            {
                dfs(i + 1, les / sum, ans * j);
            }
        }
    }
}
int main()
{
    srand(time(NULL));
    get_prime();
    int s;
    while (scanf("%d", &s) != EOF)
    {
        memset(allans, 0, sizeof(allans));
        dfs(1, s, 1);
        printf("%d\n", allans[0]);
        sort(allans + 1, allans + allans[0] + 1);
        for (int i = 1; i <= allans[0]; i++)
        {
            printf("%d ", allans[i]);
        }
        if (allans[0])
            printf("\n");
    }
    return 0;
}
// Problem3988:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 300005;
int a[N];
struct edge
{
    int v, next, END;
} v[N << 1];
int first[N], p = 1;
int n;
int dep[N], size[N], fa[N], id[N], son[N], val[N], top[N], num;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
void dfs1(int rt, int f, int Dep)
{
    dep[rt] = Dep;
    size[rt] = 1;
    son[rt] = 0;
    fa[rt] = f;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == f)
            continue;
        dfs1(v[i].END, rt, Dep + 1);
        size[rt] += size[v[i].END];
        if (size[son[rt]] < size[v[i].END])
            son[rt] = v[i].END;
    }
}
void dfs2(int rt, int tp)
{
    top[rt] = tp;
    id[rt] = ++num;
    if (son[rt])
        dfs2(son[rt], tp);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt] || v[i].END == son[rt])
            continue;
        dfs2(v[i].END, v[i].END);
    }
}
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int sum[N << 2], Add[N << 2];
void Pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void Pushdown(int rt, int m)
{
    if (Add[rt])
    {
        Add[rt << 1] += Add[rt];
        Add[rt << 1 | 1] += Add[rt];
        sum[rt << 1] += Add[rt] * (m - m / 2);
        sum[rt << 1 | 1] += Add[rt] * (m / 2);
        Add[rt] = 0;
    }
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        sum[rt] += (r - l + 1) * c;
        Add[rt] += c;
        return;
    }
    int m = (l + r) >> 1;
    Pushdown(rt, r - l + 1);
    if (L <= m)
        update(L, R, c, lch);
    if (R > m)
        update(L, R, c, rch);
    Pushup(rt);
}
int query(int x, int l, int r, int rt)
{
    if (l == r)
        return sum[rt];
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (x <= m)
        return query(x, lch);
    else
        return query(x, rch);
}
void LCA(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(id[top[x]], id[x], 1, 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    update(id[x], id[y], 1, 1, n, 1);
}
int main()
{
    memset(first, -1, sizeof(first));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int b, c;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &b, &c);
        add(b, c);
        add(c, b);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    int now = a[1];
    for (int i = 2; i <= n; i++)
    {
        LCA(now, a[i]);
        update(id[a[i]], id[a[i]], -1, 1, n, 1);
        now = a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int ans = query(id[i], 1, n, 1);
        printf("%d\n", ans);
    }
    //while(1);
}

// Problem4000:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;
int prime[500005];
bool isnprime[500005];
int tot, Max;
long long ans;
void Get_prime()
{
    isnprime[1] = 1;
    for (int i = 2; i <= 500000; i++)
    {
        if (!isnprime[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot; j++)
        {
            if (i * prime[j] > 500000)
                break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
bool IsPrime(int x)
{
    int m = sqrt(x);
    for (int i = 1; prime[i] <= m; i++)
        if (x % prime[i] == 0)
            return 0;
    return 1;
}
void dfs(int k, int now, long long sum)
{
    if (sum >= ans)
        return;
    if (now == 1)
    {
        ans = min(ans, sum);
        return;
    }
    if (now > Max && IsPrime(now + 1))
    {
        ans = min(ans, sum * (now + 1));
    }
    for (int i = k; prime[i] - 1 <= Max; i++)
    {
        if (prime[i] - 1 > now)
            break;
        if (now % (prime[i] - 1) == 0)
        {
            int x = now / (prime[i] - 1);
            long long y = sum * prime[i];
            dfs(i + 1, x, y);
            while (x % prime[i] == 0)
            {
                x /= prime[i];
                y *= prime[i];
                dfs(i + 1, x, y);
            }
        }
    }
}
int main()
{
    Get_prime();
    int n;
    scanf("%d", &n);
    Max = sqrt(n);
    ans = INT_MAX;
    dfs(1, n, 1);
    if (ans < INT_MAX)
        printf("%d", ans);
    else
        printf("-1");
    //while(1);
}
// Problem4025:
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
struct data
{
    int s, e, a, b;
    bool operator<(const data &c) const
    {
        return a < c.a;
    }
} a[100005];
struct edge
{
    int END, v, next;
} v[200005];
int first[50005], p;
void add(int s, int e, int c)
{
    v[p].END = e;
    v[p].v = c;
    v[p].next = first[s];
    first[s] = p++;
}
bool flag[50005];
queue<int> Q;
int dis[50005];
void spfa()
{
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        flag[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > max(dis[k], v[i].v))
            {
                dis[v[i].END] = max(dis[k], v[i].v);
                if (!flag[v[i].END])
                {
                    flag[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
        }
    }
}
int main()
{
    memset(first, -1, sizeof(first));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &a[i].s, &a[i].e, &a[i].a, &a[i].b);
    }
    sort(a + 1, a + m + 1);
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= m; i++)
    {
        add(a[i].s, a[i].e, a[i].b);
        add(a[i].e, a[i].s, a[i].b);
        if (!flag[a[i].s])
        {
            Q.push(a[i].s);
            flag[a[i].s] = 1;
        }
        if (!flag[a[i].e])
        {
            Q.push(a[i].e);
            flag[a[i].e] = 1;
        }
        if (a[i + 1].a != a[i].a)
            spfa();
        ans = min(ans, a[i].a + dis[n]);
    }
    if (ans == 0x3f3f3f3f)
        puts("-1");
    else
        printf("%d\n", ans);
}
// Problem4086:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int next, v, END;
} v[30005];
int first[15005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
struct data
{
    int a, b, v;
    bool operator<(const data &c) const
    {
        return v < c.v;
    }
} a[30005];
int father[15005];
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
int f[15005][17], Max[15005][17], dep[15005];
void dfs(int rt, int fa, int V, int Dep)
{
    f[rt][0] = fa;
    dep[rt] = Dep;
    Max[rt][0] = V;
    for (int i = 1; i <= 16; i++)
    {
        f[rt][i] = f[f[rt][i - 1]][i - 1];
        Max[rt][i] = max(Max[rt][i - 1], Max[f[rt][i - 1]][i - 1]);
    }
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa)
            continue;
        dfs(v[i].END, rt, v[i].v, Dep + 1);
    }
}
int Get(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    int d = dep[x] - dep[y], ans = 0;
    for (int i = 16; i >= 0; i--)
        if (d >= (1 << i))
        {
            d -= (1 << i);
            ans = max(ans, Max[x][i]);
            x = f[x][i];
        }
    if (x == y)
        return ans;
    for (int i = 16; i >= 0; i--)
        if (f[x][i] != f[y][i])
        {
            ans = max(ans, max(Max[x][i], Max[y][i]));
            x = f[x][i], y = f[y][i];
        }
    ans = max(ans, max(Max[x][0], Max[y][0]));
    return ans;
}
int main()
{
    int n, m, k;
    memset(first, -1, sizeof(first));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].v);
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= n; i++)
        father[i] = i;
    int t = 0;
    for (int i = 1; i <= m; i++)
    {
        if (find(a[i].a) != find(a[i].b))
        {
            father[find(a[i].a)] = find(a[i].b);
            add(a[i].a, a[i].b, a[i].v);
            add(a[i].b, a[i].a, a[i].v);
            t++;
            if (t == n - 1)
                break;
        }
    }
    dfs(1, 0, 0, 0);
    int s, e;
    while (k--)
    {
        scanf("%d%d", &s, &e);
        printf("%d\n", Get(s, e));
    }
}
// Problem4108:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct data
{
    int a, b, S;
    double v;
} v[2005];
int n, m;
bool cmp(const data &a, const data &b)
{
    return a.v < b.v;
}
bool cmp1(const data &a, const data &b)
{
    return a.S < b.S;
}
bool cmp2(const data &a, const data &b)
{
    return a.S > b.S;
}
int fa[305];
int find(int x)
{
    if (fa[x] != x)
        fa[x] = find(fa[x]);
    return fa[x];
}

double Calc(int mid)
{
    double ans = 0;
    double avg = (double)mid / (n - 1);
    for (int i = 1; i <= m; i++)
        v[i].v = (v[i].S - avg) * (v[i].S - avg);
    sort(v + 1, v + m + 1, cmp);
    int t = 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        if (find(v[i].a) != find(v[i].b))
        {
            fa[find(v[i].a)] = find(v[i].b);
            ans += v[i].v;
            t++;
            if (t == n - 1)
                break;
        }
    }
    return sqrt(ans / (n - 1));
}
int Kruskal(bool (*cp)(const data &a, const data &b))
{
    sort(v + 1, v + m + 1, cp);
    int ans = 0, t = 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        if (find(v[i].a) != find(v[i].b))
        {
            fa[find(v[i].a)] = find(v[i].b);
            ans += v[i].S;
            t++;
            if (t == n - 1)
                break;
        }
    }
    return ans;
}
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
        v[i].a = read(), v[i].b = read(), v[i].S = read();
    double ans = 1e300;
    int l = Kruskal(cmp1), r = Kruskal(cmp2);
    for (int i = l; i <= r; i++)
        ans = min(ans, Calc(i));
    printf("%.4lf", ans);
}
// Problem4167:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int MOD = 19961993;
const int prime[60] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281};
const int Inv[60] = {9980997, 13307996, 7984798, 11406854, 14517814, 18426456, 9393880, 5253157, 16490343, 8260136, 2575742, 18343454, 3895024, 17640832, 1698894, 3013132, 7443456, 4581442, 9236147, 18275065, 6562848, 2779519, 7936697, 4037258, 6379607, 19566707, 13566404, 4104336, 3662752, 13602421, 16661192, 1219054, 13259427, 9047523, 3751248, 8196316, 14621843, 1714528, 12192356, 11884887, 8029406, 13455046, 17976246, 13342473, 14084859, 15548287, 10217514, 9846724, 5364237, 3486812, 1627803, 14950615, 1076789, 12406658, 19340609, 8652728, 7791857, 7955334, 1657495, 8808852};
const int N = 100000;
long long Sum[(N + 5) << 2], bit[(N + 5) << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void Pushup(int rt)
{
    bit[rt] = bit[rt << 1] | bit[rt << 1 | 1];
    Sum[rt] = Sum[rt << 1] * Sum[rt << 1 | 1] % MOD;
}
void BuildTree(int l, int r, int rt)
{
    if (l == r)
    {
        Sum[rt] = 3;
        bit[rt] |= 2;
        return;
    }
    int m = l + r >> 1;
    BuildTree(lch);
    BuildTree(rch);
    Pushup(rt);
}
void Update(int x, long long a, long long c, int l, int r, int rt)
{
    if (l == r)
    {
        bit[rt] = 0, Sum[rt] = c % MOD;
        for (int i = 0; i < 60; i++)
            if (c % prime[i] == 0)
                bit[rt] ^= (1ll << i);
        return;
    }
    int m = l + r >> 1;
    if (x <= m)
        Update(x, a, c, lch);
    else
        Update(x, a, c, rch);
    Pushup(rt);
}
long long ans, p;
void Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        ans = ans * Sum[rt] % MOD;
        p |= bit[rt];
        return;
    }
    int m = l + r >> 1;
    if (L <= m)
        Query(L, R, lch);
    if (R > m)
        Query(L, R, rch);
}
int s[100005];
signed main()
{
    int n;
    for (int i = 1; i <= 100000; i++)
        s[i] = 3;
    scanf("%lld", &n);
    BuildTree(1, 100000, 1);
    int a, b, c;
    while (n--)
    {
        scanf("%lld%lld%lld", &a, &b, &c);
        if (a == 0)
        {
            ans = 1, p = 0;
            Query(b, c, 1, 100000, 1);
            // printf ("%lld : \n", ans);
            for (int i = 0; i < 60; i++)
                if (p & (1ll << i))
                    ans = ans * Inv[i] % MOD;
            printf("%lld\n", ans);
        }
        else
            Update(b, s[b], c, 1, 100000, 1), s[b] = c;
    }
    // while(1);
}
// Problem4182:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
struct edge
{
    int END, next;
} v[1000005];
int w[500005], first[500005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int f[500005];
int dfs(int x, int fa)
{
    int t = 0;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa)
        {
            f[v[i].END] = dfs(v[i].END, x);
            t += f[v[i].END] + 2;
        }
    }
    return t;
}
int t[500005];
int comp(const int &a, const int &b)
{
    return t[a] > t[b];
}
void DP(int x, int fa)
{
    vector<int> re;
    for (int i = first[x]; i != -1; i = v[i].next)
        if (v[i].END != fa)
        {
            DP(v[i].END, x);
            re.push_back(v[i].END);
        }
    sort(re.begin(), re.end(), comp);
    if (x != 1)
        t[x] = w[x] - f[x];
    int now = f[x];
    for (int i = 0; i < re.size(); i++)
    {
        now -= (f[re[i]] + 2);
        t[x] = max(t[x], t[re[i]] - now - 1);
    }
    t[x] = max(t[x], 0);
}
int main()
{
    //freopen("farmcraft.in", "r", stdin);
    //freopen("farmcraft.out", "w", stdout);
    //memset(f, -1, sizeof(f));
    memset(first, -1, sizeof(first));
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
    }
    int a, b;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    f[1] = dfs(1, 0);
    //for (int i = 1; i <= n; i++)
    // printf("%d ", f[i]);
    //printf("\n======================\n");
    DP(1, 0);
    //while(1);
    printf("%d\n", f[1] + max(w[1], t[1]));
}
// Problem4226:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct data
{
    long long p, s;
    bool no;
    bool operator<(const data &a) const
    {
        return s < a.s;
    }
} a[205], f[205];
long long m, k, n, cnt;
long long Get_day(long long mid)
{
    long long Last_Money = m - k * mid, Part_Now_day = 0, ret = 0;
    long long tmp;
    for (int i = 1; i <= n; i++)
    {
        if (Part_Now_day <= f[i].s)
        {
            tmp = f[i].s - Part_Now_day + 1;
            tmp = min(tmp, Last_Money / (f[i].p * mid));
            ret += tmp * mid;
            Last_Money -= f[i].p * mid * tmp;
            Part_Now_day += tmp;
        }
        if (Part_Now_day <= f[i].s)
        {
            tmp = min(mid, Last_Money / f[i].p);
            ret += tmp;
            Last_Money -= tmp * f[i].p;
            Part_Now_day++;
        }
    }
    return ret;
}
int main()
{
    scanf("%lld%lld%lld", &m, &k, &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &a[i].p, &a[i].s);
    for (int i = 1; i <= n; i++)
    {
        if (a[i].no)
            continue;
        for (int j = 1; j <= n; j++)
        {
            if (a[j].no)
                continue;
            if (a[i].p <= a[j].p && a[i].s >= a[j].s && i != j)
                a[j].no = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (!a[i].no)
            f[++cnt] = a[i];
    }
    sort(f + 1, f + cnt + 1);
    n = cnt;
    long long l = 1, r = m / (f[1].p + k), mid1, mid2, v1, v2, ans = 0;
    while (l <= r)
    {
        mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
        v1 = Get_day(mid1), v2 = Get_day(mid2);
        if (v1 < v2)
            ans = max(ans, v2), l = mid1 + 1;
        else if (v1 > v2)
            ans = max(ans, v1), r = mid2 - 1;
        else
            ans = max(ans, v1), l = mid1 + 1, r = mid2 - 1;
    }
    printf("%lld", ans);
}
// Problem4261:
#pragma GCC optimize("O3")
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
struct edge
{
    int END, next;
} v[500005 << 1];
int first[500005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dep[500005], size[500005], son[500005], fa[500005], ID[500005], top[500005];
int Index;
void dfs1(int rt, int faa, int Dep)
{
    size[rt] = 1;
    dep[rt] = Dep;
    fa[rt] = faa;
    son[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == faa)
            continue;
        dfs1(v[i].END, rt, Dep + 1);
        size[rt] += size[v[i].END];
        if (size[v[i].END] > size[son[rt]])
            son[rt] = v[i].END;
    }
}
void dfs2(int rt, int t)
{
    top[rt] = t;
    ID[rt] = ++Index;
    if (son[rt])
        dfs2(son[rt], t);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt] || v[i].END == son[rt])
            continue;
        dfs2(v[i].END, v[i].END);
    }
}
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
bool mark[500005 << 2], flag[500005 << 2];
void Pushdown(int rt)
{
    if (flag[rt])
    {
        flag[rt << 1] = flag[rt << 1 | 1] = flag[rt];
        mark[rt << 1] = mark[rt << 1 | 1] = 1;
        flag[rt] = 0;
    }
}
void Update(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        mark[rt] = 1;
        flag[rt] = 1;
        return;
    }
    Pushdown(rt);
    int m = l + r >> 1;
    if (L <= m)
        Update(L, R, lch);
    if (R > m)
        Update(L, R, rch);
}
bool Query(int x, int l, int r, int rt)
{
    if (l == r)
        return mark[rt];
    int m = l + r >> 1;
    Pushdown(rt);
    if (x <= m)
        return Query(x, lch);
    else
        return Query(x, rch);
}
int Update(int a, int b)
{
    while (top[a] != top[b])
    {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        Update(ID[top[a]], ID[a], 1, n, 1);
        a = fa[top[a]];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    Update(ID[a], ID[b], 1, n, 1);
    return a;
}
int main()
{
    memset(first, -1, sizeof(first));
    int m, s;
    scanf("%d%d%d", &n, &m, &s);
    int a, b;
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    dfs1(1, 0, 1);
    dfs2(1, 0);
    int d;
    long long ans = 0;
    ;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &d);
        if (!Query(ID[d], 1, n, 1))
        {
            int lca = Update(s, d);
            ans += (dep[s] + dep[d] - 2 * dep[lca]);
            s = d;
        }
    }
    printf("%lld\n", ans);
}
// Problem4275:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
struct edge
{
    int END, next;
} v[105];
int first[15], p;
struct func
{
    void operator()(int a, int b)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
} add;
#define lowbit(_) ((_) & (-_))
struct func2
{
    int operator()(int x)
    {
        int ans = 0;
        while (x)
            ans += (x & 1), x >>= 1;
        return ans;
    }
} Get_Num;
int cnt[(1 << 10) + 1];
long long C[55][55];
double f[(1 << 10) + 1][50];
double g[(1 << 10) + 1][50];
signed main()
{
    int n, m, a, b;
    scanf("%lld%lld", &n, &m);
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &a, &b);
        add(a, b);
        add(b, a);
    }
    int N = (1 << n) - 1;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= n; j++)
            if (i & (1 << (j - 1)))
                for (int k = first[j]; k != -1; k = v[k].next)
                    if (i & (1 << (v[k].END - 1)))
                        cnt[i]++;
        cnt[i] /= 2;
    }
    C[0][0] = 1;
    for (int i = 1; i <= 50; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    for (int i = 1; i <= N; i++)
    {
        if (Get_Num(i) == 1)
        {
            g[i][0] = 1;
            continue;
        }
        int j = lowbit(i);
        for (int S = (i - 1) & i; S; S = (S - 1) & i)
        {
            if (j & S)
                for (int l = 0; l <= cnt[S]; l++)
                    for (int k = 0; k <= cnt[S ^ i]; k++)
                        f[i][l + k] += g[S][l] * C[cnt[i ^ S]][k];
        }
        for (j = 0; j <= cnt[i]; j++)
            g[i][j] = C[cnt[i]][j] - f[i][j];
    }
    double H = 0;
    for (int i = 0; i <= m; i++)
        H += f[N][i] / C[cnt[N]][i];
    printf("%.6lf", H / (m + 1));
}
// Problem4350:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
int P, K, N;
int a[4][7];
unsigned int f[2][(1 << 6) + 1];
bool ok[65][65];
bool Ok[65];
struct Matrix
{
    int n, m;
    unsigned int a[65][65];
    Matrix(int x, int y)
    {
        n = x, m = y;
        memset(a, 0, sizeof(a));
    }
    void Init()
    {
        for (int i = 0; i <= n; i++)
            a[i][i] = 1;
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ans(n, b.m);
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                for (int k = 0; k <= b.m; k++)
                    ans.a[i][j] = ans.a[i][j] + a[i][k] * b.a[k][j];
        return ans;
    }
    Matrix operator^(const long long &b) const
    {
        Matrix ans(n, m);
        ans.Init();
        Matrix c = *this;
        long long k = b;
        while (k)
        {
            if (k & 1)
                ans = c * ans;
            k >>= 1;
            c = c * c;
        }
        return ans;
    }
    void print()
    {
        printf("\n{n,m} = {%d,%d}\n", n, m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                printf("%lld ", a[i][j]);
            printf("\n");
        }
        printf("\n");
    }
};
bool OK(int x)
{
    for (int i = 1; i < K; i++)
        if (a[2][i])
            if ((x << (K - i)) & x & N)
                return 0;
    for (int i = K + 1; i <= P; i++)
        if (a[2][i])
            if ((x >> (i - K)) & x & N)
                return 0;
    return 1;
}
bool OK(int x, int y)
{
    for (int i = 1; i < K; i++)
        if (a[1][i])
            if ((x << (K - i)) & y & N)
                return 0;
    for (int i = K; i <= P; i++)
        if (a[1][i])
            if ((x >> (i - K)) & y & N)
                return 0;
    for (int i = 1; i < K; i++)
        if (a[3][i])
            if ((y << (K - i)) & x & N)
                return 0;
    for (int i = K; i <= P; i++)
        if (a[3][i])
            if ((y >> (i - K)) & x & N)
                return 0;
    return 1;
}
int main()
{
    //freopen("tjoi2015_board.in","r",stdin);
    //freopen("tjoi2015_board.out","w",stdout);
    int n, m;
    scanf("%d%d%d%d", &n, &m, &P, &K);
    K++;
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= P; j++)
            scanf("%d", &a[i][j]);
    N = (1 << m) - 1;
    int now = 1;
    char S[10];
    Matrix A(N, N);
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++)
            A.a[i][j] = (OK(i, j) && OK(i) && OK(j));
    Matrix B(0, N);
    for (int i = 0; i <= N; i++)
        B.a[0][i] = OK(i);
    A = A ^ (n - 1);
    B = B * A;
    unsigned int ans = 0;
    for (int i = 0; i <= N; i++)
        ans += B.a[0][i];
    printf("%u", ans);
}
// Problem4360:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
struct edge
{
    int next, END;
} v[100005];
int p, first[100005];
int in[100005];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int main()
{
    //freopen("dishes.in","r",stdin);
    //freopen("dishes.out","w",stdout);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(first, -1, sizeof(first));
        memset(in, 0, sizeof(in));
        p = 0;
        int n, m;
        scanf("%d%d", &n, &m);
        int a, b;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            add(b, a);
            in[a]++;
        }
        priority_queue<int> Q;
        stack<int> st;
        for (int i = 1; i <= n; i++)
            if (!in[i])
                Q.push(i);
        while (!Q.empty())
        {
            int tmp = Q.top();
            st.push(tmp);
            Q.pop();
            for (int i = first[tmp]; i != -1; i = v[i].next)
            {
                in[v[i].END]--;
                if (in[v[i].END] == 0)
                    Q.push(v[i].END);
            }
        }
        int flag = 0;
        for (int i = 1; i <= n; i++)
            if (in[i] > 0)
                flag = 1;
        if (flag)
            puts("Impossible!");
        else
        {
            while (st.size() != 1)
            {
                printf("%d ", st.top());
                st.pop();
            }
            printf("%d\n", st.top());
        }
    }
}

// Problem4406:
#include <cstdio>
#include <cstring>
#include <algorithm>
int a[25][25];
bool ok[(1 << 20) + 1];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &a[i][j]);
        memset(ok, 0, sizeof(ok));
        int N = (1 << n) - 1;
        ok[N] = 1;
        for (int i = N; i >= 0; i--)
        {
            if (ok[i])
            {
                for (int j = 0; j < n; j++)
                    if (i & (1 << j))
                    {
                        int Sum = 0;
                        for (int k = 0; k < n; k++)
                            if (i & (1 << k))
                                Sum += a[j][k];
                        if (Sum > 0)
                            ok[i ^ (1 << j)] = 1;
                    }
            }
        }
        bool have = 0;
        for (int i = 0; i < n; i++)
            if (ok[1 << i])
            {
                printf("%d ", i + 1);
                have = 1;
            }
        if (have)
            printf("\n");
        else
            printf("0\n");
    }
}
// Problem4544:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <ctime>
#include <algorithm>
#define LL long long
using namespace std;
struct data
{
    int a, b;
};
int father[300000], father1[300000];
map<LL, int> p;
data l1[105000];
void Init();
int n, o, h;
int find(int a);
int find1(int a);
bool check(int a, int b);
bool check1(int a, int b);
void merge(int a, int b);
void q_read(int &a)
{
    char c = getchar();
    a = 0;
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        a = a * 10 + c - '0';
        c = getchar();
    }
}
void q_read(LL &a)
{
    char c = getchar();
    a = 0;
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        a = a * 10 + c - '0';
        c = getchar();
    }
}
void merge1(int a, int b);
int main()
{
    //freopen("prog.in","r",stdin);
    //freopen("prog.out","w",stdout);
    int t;
    q_read(t);
    while (t--)
    {
        Init();
        p.clear();
        q_read(n);
        LL i1, j1, e;
        o = 1;
        memset(l1, 0, sizeof(l1));
        h = 1;
        bool yes = 0;
        for (int i = 1; i <= n; i++)
        {
            q_read(i1);
            q_read(j1);
            q_read(e);
            if (yes == 1)
                continue;
            if (e)
            {
                if (p[i1] == 0)
                {
                    p[i1] = o++;
                }
                if (p[j1] == 0)
                {
                    p[j1] = o++;
                }
                merge(p[i1], p[j1]);
            }
            else
            {
                if (p[i1] == 0)
                {
                    p[i1] = o++;
                }
                if (p[j1] == 0)
                {
                    p[j1] = o++;
                }
                merge1(p[i1], p[j1]);
                if (i1 == j1 || check(p[i1], p[j1]))
                    yes = 1;
                l1[h++] = (data){p[i1], p[j1]};
            }
        }
        if (yes != 1)
        {
            for (int i = 1; i < h; i++)
            {
                if (check(l1[i].a, l1[i].b))
                {
                    yes = 1;
                    break;
                }
            }
        }
        if (yes)
            printf("NO\n");
        else
            printf("YES\n");
    }
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
        father[y] = x;
}
bool check(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x == y)
        return 1;
    else
        return 0;
}
int find(int a)
{
    if (a != father[a])
        father[a] = find(father[a]);
    return father[a];
}
void Init()
{
    for (int i = 1; i < 300000; i++)
    {
        father[i] = father1[i] = i;
    }
}
int find1(int a)
{
    if (a != father1[a])
        father1[a] = find1(father1[a]);
    return father1[a];
}
void merge1(int a, int b)
{
    int x = find1(a);
    int y = find1(b);
    if (x != y)
        father1[y] = x;
}
bool check1(int a, int b)
{
    int x = find1(a);
    int y = find1(b);
    if (x == y)
        return 1;
    else
        return 0;
}
template <class T>
void q_read(T &a)
{
    char c = getchar();
    a = 0;
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        a = a * 10 + c - '0';
        c = getchar();
    }
}

// Problem4668:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 7777777;
long long f[1005][1005][2];
int main()
{
    int n;
    scanf("%d", &n);
    f[1][0][0] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            f[i][j][1] = (f[i - 1][j][1] + (j > 0 ? (f[i - 1][j - 1][1] + f[i - 1][j - 1][0] * 2) % MOD : 0)) % MOD;
            f[i][j][0] = ((f[i - 1][j + 1][1] * j % MOD) + (f[i - 1][j + 1][0] * (j + 1)) % MOD + (f[i - 1][j][1] * (i - j - 1)) % MOD + (f[i - 1][j][0] * (i - j - 2)) % MOD) % MOD;
        }
    }
    printf("%lld", f[n][0][0]);
}
// Problem4668:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 7777777;
long long f[1005];
int main()
{
    int n;
    scanf("%d", &n);
    f[0] = 1, f[1] = 1, f[2] = 0, f[3] = 0;
    for (int i = 4; i <= n; i++)
        f[i] = ((f[i - 1] * (i + 1) % MOD - f[i - 2] * (i - 2) % MOD - f[i - 3] * (i - 5) % MOD + f[i - 4] * (i - 3) % MOD) % MOD + MOD) % MOD;
    printf("%lld", f[n]);
}
// Problem4668:
#include <cstdio>
using namespace std;
const int MOD = 7777777;
long long f[1001];
int main()
{
    int n;
    scanf("%d", &n);
    f[0] = 1, f[1] = 1, f[2] = 0, f[3] = 0;
    for (int i = 4; i <= n; i++)
        f[i] = ((f[i - 1] * (i + 1) % MOD - f[i - 2] * (i - 2) % MOD - f[i - 3] * (i - 5) % MOD + f[i - 4] * (i - 3) % MOD) % MOD + MOD) % MOD;
    printf("%lld", f[n]);
}
// Problem4668:
#include <stdio.h>
const int MOD = 7777777;
long long f[1001];
int main()
{
    int n;
    scanf("%d", &n);
    f[0] = 1, f[1] = 1, f[2] = 0, f[3] = 0;
    for (int i = 4; i <= n; i++)
        f[i] = ((f[i - 1] * (i + 1) % MOD - f[i - 2] * (i - 2) % MOD - f[i - 3] * (i - 5) % MOD + f[i - 4] * (i - 3) % MOD) % MOD + MOD) % MOD;
    printf("%lld", f[n]);
}
// Problem4672:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
struct data
{
    int t, l, r;
};
int cnt[16];
int backcnt[16];
vector<data> s;
int times[5];
int Query()
{
    memcpy(backcnt, cnt, sizeof(backcnt));
    memset(times, 0, sizeof(times));
    // int ans = s.size();
    // for (int i = 0; i < s.size(); i++)
    // {
    //     for (int j = s[i].l; j <= s[i].r; j++)
    //         backcnt[j] -= s[i].t;
    // }
    int ans = 0;
    for (int i = 1; i <= 14; i++)
    {
        times[backcnt[i]]++;
    }
    while (times[4] > 0 && times[2] > 1)
    {
        times[4]--;
        times[2] -= 2;
        ans++;
    }
    while (times[4] > 0 && times[1] > 1)
    {
        times[4]--;
        times[1] -= 2;
        ans++;
    }
    while (times[4] > 0 && times[2] > 0)
    {
        times[4]--;
        times[2]--;
        ans++;
    }
    while (times[3] > 0 && times[2] > 0)
    {
        times[3]--;
        times[2]--;
        ans++;
    }
    while (times[3] > 0 && times[1] > 0)
    {
        times[3]--;
        times[1]--;
        ans++;
    }
    while (times[4] > 0)
    {
        times[4]--;
        ans++;
    }
    while (times[3] > 0)
    {
        times[3]--;
        ans++;
    }
    while (times[2] > 0)
    {
        times[2]--;
        ans++;
    }
    while (times[1] > 0)
    {
        times[1]--;
        ans++;
    }
    return ans;
}
int DFS()
{
    //int ans = 0x3f3f3f3f;
    int ans = Query();
    for (int i = 1; i <= 12; i++)
    {
        if (cnt[i])
        {
            for (int j = i + 1; j <= 12; j++)
            {
                if (!cnt[j])
                    break;
                if (j - i + 1 >= 5)
                {
                    //s.push_back((data){1, i, j});
                    for (int k = i; k <= j; k++)
                        cnt[k] -= 1;
                    ans = min(ans, DFS() + 1);
                    for (int k = i; k <= j; k++)
                        cnt[k] += 1;
                    //ans = min(ans, Query(1));
                    //s.pop_back();
                }
            }
        }
        if (cnt[i] >= 2)
        {
            for (int j = i + 1; j <= 12; j++)
            {
                if (cnt[j] < 2)
                    break;
                if (j - i + 1 >= 3)
                {
                    for (int k = i; k <= j; k++)
                        cnt[k] -= 2;
                    ans = min(ans, DFS() + 1);
                    for (int k = i; k <= j; k++)
                        cnt[k] += 2;
                    // s.push_back((data){2, i, j});
                    // ans = min(ans, DFS(j + 1));
                    // ans = min(ans, Query(1));
                    // s.pop_back();
                }
            }
        }
        if (cnt[i] >= 3)
        {
            for (int j = i + 1; j <= 12; j++)
            {
                if (cnt[j] < 3)
                    break;
                if (j - i + 1 >= 2)
                {
                    for (int k = i; k <= j; k++)
                        cnt[k] -= 3;
                    ans = min(ans, DFS() + 1);
                    for (int k = i; k <= j; k++)
                        cnt[k] += 3;
                    // s.push_back((data){3, i, j});
                    // ans = min(ans, DFS(j + 1));
                    // ans = min(ans, Query(1));
                    // s.pop_back();
                }
            }
        }
    }
    //ans = min(ans, Query(1));
    return ans;
}
int main(int argc, char const *argv[])
{
    //freopen("landlords.in", "r", stdin);
    //freopen("landlords.out", "w", stdout);
    int T, n;
    //int C = 1;
    scanf("%d%d", &T, &n);
    while (T--)
    {
        int a, b;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &a, &b);
            if (a)
                if ((a + 11) % 13)
                    cnt[(a + 11) % 13]++;
                else
                    cnt[13]++;
            else
                cnt[14]++;
        }
        s.clear();
        printf("%d\n", DFS());
    }

    return 0;
}

// Problem4764:
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MOD = 30011;
struct Matrix
{
    int n, m;
    long long a[205][205];
    Matrix(int x, int y)
    {
        n = x, m = y;
        memset(a, 0, sizeof(a));
    }
    void Init()
    {
        for (int i = 0; i <= n; i++)
            a[i][i] = 1;
    }
    long long *operator[](const int c)
    {
        return a[c];
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ans(n, b.m);
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                for (int k = 0; k <= b.m; k++)
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] * b.a[k][j]) % MOD;
        return ans;
    }
    Matrix operator^(const long long &b) const
    {
        Matrix ans(n, m);
        ans.Init();
        Matrix c = *this;
        long long k = b;
        while (k)
        {
            if (k & 1)
                ans = c * ans;
            k >>= 1;
            c = c * c;
        }
        return ans;
    }
    void print()
    {
        printf("\n{n,m} = {%d,%d}\n", n, m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                printf("%lld ", a[i][j]);
            printf("\n");
        }
        printf("\n");
    }
};
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    static Matrix T1(n + n, n + n), T2(n + n, n + n);
    for (int i = 1; i <= n; i++)
    {
        T1[i][i] = 1;
        T2[i][i] = 1;
        T1[i + n][i] = 1;
        T2[i][i + n] = 1;
        if (i != 1)
        {
            T1[i - 1 + n][i] = 1;
            T2[i - 1][i + n] = 1;
        }
        if (i != n)
        {
            T1[i + 1 + n][i] = 1;
            T2[i + 1][i + n] = 1;
        }
        T1[i + n][i + n] = 1;
        T2[i + n][i + n] = 1;
    }
    // T1.print(), T2.print();
    Matrix T = T1 * T2;
    // T.print();
    // while(1);
    Matrix A(1, n + n);
    A[1][1] = 1;
    A[1][n + 1] = 1;
    if (n != 1)
        A[1][n + 2] = 1;
    int t = (m - 1) / 2;
    if (t == 0)
    {
        if (m == 1)
            printf("%lld", A[1][n]);
        else
            printf("%lld", A[1][n + n]);
        return 0;
    }
    t--;
    A = A * (T ^ t);
    Matrix B = A * T;
    if (m & 1)
        printf("%lld", ((B[1][n] - A[1][n]) % MOD + MOD) % MOD);
    else
        printf("%lld", ((B[1][n + n] - A[1][n + n]) % MOD + MOD) % MOD);
}
// Problem4766:
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;
const int N = 200005;
set<int> st[N];
int Sum[N];
int Ans[N];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    char s[5];
    int a, b;
    // for (int i = 1; i <= n; i++)
    // st[i].insert(i);
    while (m--)
    {
        scanf("%s", s);
        if (s[0] == '!')
        {
            scanf("%d", &a);
            Sum[a]++;
        }
        else if (s[0] == '+')
        {
            scanf("%d%d", &a, &b);
            Ans[a] -= Sum[b], Ans[b] -= Sum[a];
            st[b].insert(a);
            st[a].insert(b);
        }
        else
        {
            scanf("%d%d", &a, &b);
            Ans[a] += Sum[b], Ans[b] += Sum[a];
            st[b].erase(a);
            st[a].erase(b);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (set<int>::iterator it = st[i].begin(); it != st[i].end(); it++)
        {
            Ans[*it] += Sum[i];
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d%c", Ans[i], " \n"[i == n]);
}
// Problem4823:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

deque<int> Q;
int N, K, L, R;
int a[50005];

int Max[(50005 << 1) + 200][16], Min[(50005 << 1) + 200][16];

int QueryMax(int l, int r)
{
    if (l > N || r < 0)
        return -0x3f3f3f3f;
    if (l <= 0)
        l = 1;
    if (r > N)
        r = N;
    int k = 0;
    while ((1 << k) <= (r - l + 1))
        k++;
    k--;
    return max(Max[l][k], Max[r - (1 << k) + 1][k]);
}

int QueryMin(int l, int r)
{
    if (l > N || r < 0)
        return 0x3f3f3f3f;
    if (l <= 0)
        l = 1;
    if (r > N)
        r = N;
    int k = 0;
    while ((1 << k) <= (r - l + 1))
        k++;
    k--;
    return min(Min[l][k], Min[r - (1 << k) + 1][k]);
}

bool Judge(double mid)
{
    //	printf ("%.4lf\n", mid);
    Q.clear();
    for (int i = L + 1; i <= N; i++)
    {
        while (!Q.empty() && Q.front() < i - R + 1)
            Q.pop_front();
        while (!Q.empty() && a[Q.back()] - mid * Q.back() > a[i - L] - mid * (i - L))
            Q.pop_back();
        Q.push_back(i - L);
        //		printf ("1: %d %.4lf %.4lf\n", Q.front(), a[Q.empty() ? 0 : Q.front()] - mid * (Q.empty() ? 0 :Q.front()), (a[i] - mid * (i + K)) - a[Q.empty() ? 0 : Q.front()] - mid * (Q.empty() ? 0 :Q.front()));
        if ((a[i] - mid * (i + K)) > a[Q.empty() ? 0 : Q.front()] - mid * (Q.empty() ? 0 : Q.front()))
            return 1;
    }
    Q.clear();
    for (int i = N - L; i >= 1; i--)
    {
        while (!Q.empty() && Q.front() > i + R - 1)
            Q.pop_front();
        while (!Q.empty() && a[Q.back()] + mid * (Q.back() + K) > a[i + L] + mid * (i + L + K))
            Q.pop_back();
        Q.push_back(i + L);
        //		printf("2: %.4lf %.4lf\n", a[Q.empty() ? 0 : Q.front()] + ((Q.empty() ? 0 :Q.front()) + K) * mid, a[i] + mid * i - a[Q.empty() ? 0 : Q.front()] + ((Q.empty() ? 0 :Q.front()) + K) * mid);
        if (a[i] + mid * i > a[Q.empty() ? 0 : Q.front()] + ((Q.empty() ? 0 : Q.front()) + K) * mid)
            return 1;
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
        memset(Max, -0x3f, sizeof(Max));
        memset(Min, 0x3f, sizeof(Min));
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
            if (Judge(mid))
                l = mid;
            else
                r = mid;
        }
        printf("%.4lf\n", max(ans, l));
    }
}
// Problem4828:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct edge
{
    int END, next;
} v[500005];
int first[500005], p;
void add(int a, int b)
{
    v[p].next = first[a];
    v[p].END = b;
    first[a] = p++;
}
double P;
int n, m;
int tmp[500005];
double Sum[500005];
#define lowbit(_) ((_) & (-_))
void add(int a, double c)
{
    for (int i = a; i <= n; i += lowbit(i))
        Sum[i] += c;
}
double Query(int a)
{
    double ans = 0;
    for (int i = a; i > 0; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
double pow_db(double a, int b)
{
    double ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a;
        b >>= 1;
        a = a * a;
    }
    return ans;
}
int main()
{
    n = read(), m = read();
    scanf("%lf", &P);
    int a, b;
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= m; i++)
    {
        a = read(), b = read();
        add(a, b);
    }
    double ans = 0;
    for (int i = n; i >= 1; i--)
    {
        int cnt = 0;
        for (int j = first[i]; j != -1; j = v[j].next)
            tmp[++cnt] = v[j].END;
        if (cnt == 0)
            continue;
        sort(tmp + 1, tmp + cnt + 1);
        for (int j = 1; j <= cnt; j++)
            ans += pow_db((1 - P), j - 1) * P / (1 - pow_db(1 - P, cnt)) * Query(tmp[j] - 1);
        for (int j = 1; j <= cnt; j++)
            add(tmp[j], pow_db((1 - P), j - 1) * P / (1 - pow_db(1 - P, cnt)));
    }
    printf("%.2f", ans);
}

// Problem4864:
#include <cstdio>
#include <cstring>
using namespace std;
#define LL long long
const LL MOD = 1e9 + 7;
LL F[1000005], g[1000005];
LL pow_mod(LL a, LL b)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
LL C(LL n, LL m)
{
    if (n < m)
        return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
int main()
{
    //freopen("permutation.in","r",stdin);
    //freopen("permutation.out","w",stdout);
    F[0] = 1;
    memset(g, -1, sizeof(g));
    g[1] = 0;
    g[0] = 1;
    for (int i = 1; i <= 1000000; i++)
        F[i] = F[i - 1] * i % MOD;
    for (int i = 2; i <= 1000000; i++)
        g[i] = (g[i - 1] + g[i - 2]) * (i - 1) % MOD;
    int T;
    scanf("%d", &T);
    LL n, m;
    while (T--)
    {
        scanf("%lld%lld", &n, &m);
        printf("%lld\n", g[n - m] * C(n, m) % MOD);
    }
}

// Problem4909:
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
    const int operator[](const int x) const
    {
        return c[x];
    }
    int &operator[](const int x)
    {
        return c[x];
    }
    BigNum operator*(const int &b) const
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
        while (y)
        {
            ans[++ans.len] = y % base;
            y /= base;
        }
        return ans;
    }
    BigNum operator+(const BigNum &b) const
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
    scanf("%d", &n);
    f[1] = 0;
    f[2] = 1;
    for (int i = 3; i <= n; i++)
    {
        f[i % 3] = (f[(i - 1 + 3) % 3] + f[(i - 2 + 3) % 3]) * (i - 1);
    }
    f[n % 3].print();
}
// Problem4911:
#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;
int a[400], c;
int s[1 << 8];
long long w[1 << 8], f[305][305][1 << 8], INF, ans;
int main()
{
    // freopen("merge.in","r",stdin);
    // freopen("merge.out","w",stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%1d", &a[i]);
    for (int i = 0; i < (1 << k); i++)
        scanf("%d%lld", &s[i], &w[i]);
    memset(f, 0x80, sizeof(f));
    memset(&INF, 0x80, sizeof(INF));
    for (int i = 1; i <= n; i++)
        f[i][i][a[i]] = 0;
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            int len = j - i;
            while (len >= k)
                len -= k - 1;
            for (int m = j; m > i; m -= k - 1)
            {
                for (int S = 0; S < (1 << len); S++)
                {
                    if (f[i][m - 1][S] != INF)
                    {
                        if (f[m][j][0] != INF)
                            f[i][j][S << 1] = max(f[i][j][S << 1], f[i][m - 1][S] + f[m][j][0]);
                        if (f[m][j][1] != INF)
                            f[i][j][S << 1 | 1] = max(f[i][j][S << 1 | 1], f[i][m - 1][S] + f[m][j][1]);
                    }
                }
            }
            if (len == k - 1)
            {
                long long g[2];
                g[0] = g[1] = INF;
                for (int S = 0; S < (1 << k); S++)
                    if (f[i][j][S] != INF)
                        g[s[S]] = max(g[s[S]], f[i][j][S] + w[S]);
                f[i][j][0] = g[0];
                f[i][j][1] = g[1];
            }
        }
    }
    for (int i = 0; i < (1 << k); i++)
        ans = max(ans, f[1][n][i]);
    printf("%lld\n", ans);
    //while(1);
}
// Problem4928:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long a[50005], k;
int f[50005];
int main()
{
    int n;
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    sort(a + 1, a + n + 1);
    for (int i = n, j = n; i > 0; i--)
    {
        while (a[i] - a[j] <= k && j > 0)
            j--;
        f[i] = i - j;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, f[i] + f[i - f[i]]);
        f[i] = max(f[i - 1], f[i]);
    }
    printf("%d", ans);
}

// Problem4948:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
double eps = 1e-7;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct edge
{
    int END, next;
    double v;
} v[20010];
int first[1005], p;
void add(int a, int b, double c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
double dis[1005];
queue<int> Q;
int main()
{
    int T = read();
    int t = 0;
    while (T--)
    {
        int n = read(), m = read();
        for (int i = 1; i <= n; i++)
            dis[i] = 0;
        memset(first, -1, sizeof(first)), p = 0;
        for (int i = 1; i <= m; i++)
        {
            int a = read(), b = read(), c = read(), d = read();
            add(a, b, (double)d / c);
            add(b, a, (double)c / d);
        }
        dis[1] = 1;
        Q.push(1);
        while (!Q.empty())
        {
            int k = Q.front();
            Q.pop();
            for (int i = first[k]; i != -1; i = v[i].next)
            {
                if (!dis[v[i].END])
                {
                    dis[v[i].END] = dis[k] * v[i].v;
                    Q.push(v[i].END);
                }
                else if (abs(dis[v[i].END] - dis[k] * v[i].v) > eps)
                {
                    printf("Case #%d: No\n", ++t);
                    goto end;
                }
            }
        }
        printf("Case #%d: Yes\n", ++t);
    end:;
        while (!Q.empty())
            Q.pop();
    }
}

// Problem5109:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
struct data
{
    int x, y, pxy;
} s[405];
int comp(const data &a, const data &b)
{
    return a.pxy > b.pxy;
}
int main()
{
    int m, n, k, p = 0;
    cin >> m >> n >> k;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            p++;
            int pij;
            cin >> pij;
            s[p].x = i;
            s[p].y = j;
            s[p].pxy = pij;
        }
    }
    //cout<<p;
    int sum = 0, tep = 0;
    sort(s + 1, s + p + 1, comp);
    s[0].x = 0;
    s[0].y = s[1].y;
    for (int i = 1; i <= p; i++)
    {
        tep += (abs(s[i].x - s[i - 1].x) + abs(s[i].y - s[i - 1].y) + 1);
        if (tep + s[i].x > k)
            break;
        else
            sum += s[i].pxy;
    }
    cout << sum;
}

// Problem5111:
#include <cstring>
#include <cmath>
//#include<ctime>
//#include<windows.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 100000000
#define LL long long
using namespace std;
const double pi = 3.14159265;
double a[105], b[105];
double mylong(double x1, double y1, double x2, double y2);
void in();
int n;
double r;
int main()
{

    cin >> n >> r;
    in();
    double l = 0;
    for (int i = 2; i <= n; i++)
    {
        l += mylong(a[i], b[i], a[i - 1], b[i - 1]);
    }
    l += mylong(a[1], b[1], a[n], b[n]);
    l += 2 * pi * r;
    printf("%.2lf", l);
}
void in()
{
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];
}
double mylong(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Problem5112:
#include <cstring>
#include <cmath>
//#include<ctime>
//#include<windows.h>
//#include<algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 100000000
#define LL long long
using namespace std;
LL fn(LL x);
int main()
{
    LL n, s = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        s += fn(i);
    cout << s;
}
LL fn(LL x)
{
    return x == 1 ? 1 : x * fn(x - 1);
}

// Problem5113:
#include <cstring>
#include <cmath>
#include <ctime>
//#include<windows.h>
//#include<algorithm>
#include <iostream>
//#include<cstdlib>
#include <cstdio>
#include <string>
#define INF 4000005
#define LL long long
using namespace std;
int a, b, d, sum = 0, cnt = 0;
bool c[4000005];
void prime()
{
    memset(c, 1, sizeof(c));
    c[1] = 0;
    for (int i = 2; i <= INF; i++)
    {
        if (c[i])
        {
            for (int j = 2; j <= INF / i; j++)
                c[j * i] = 0;
        }
    }
    return;
}
int main()
{
    //freopen("qprime.in","r",stdin);
    //freopen("qprime.out","w",stdout);
    prime();
    char s[8];
    cin >> a >> b >> d;
    for (int i = a; i < b; i++)
    {
        if (c[i])
        {
            sprintf(s, "%d", i);
            for (int j = 0; j < strlen(s); j++)
            {
                if ((s[j] - '0') == d)
                {
                    sum++;
                    break;
                }
            }
        }
    }
    cout << sum;
}

// Problem5113:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
const int INF = 4000000;
bool isp[INF + 1];
int p[1000000], num = 0;
void prime()
{
    memset(isp, 1, sizeof(isp));
    p[0] = 0;
    p[1] = 0;
    for (int i = 2; i < INF; i++)
    {
        if (isp[i])
            p[num++] = i;
        for (int j = 0; j <= num && i * p[j] < INF; j++)
        {
            isp[i * p[j]] = 0;
            if (!(i % p[j]))
                break;
        }
    }
    return;
}
int main()
{
    int a, b, d, sum = 0;
    cin >> a >> b >> d;
    prime();
    char c[8];
    for (int i = a; i < b; i++)
    {
        if (isp[i])
        {
            sprintf(c, "%d", i);
            for (int j = 0; j < strlen(c); j++)
            {
                if ((c[j] - '0') == d)
                {
                    sum++;
                    break;
                }
            }
        }
    }
    cout << sum;
}

// Problem5113:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
const int INF = 4000000;
bool isp[INF + 1];
vector<int> p;
int num = 0;
void prime()
{
    memset(isp, 1, sizeof(isp));
    isp[0] = 0;
    isp[1] = 0;
    for (int i = 2; i < INF; i++)
    {
        if (isp[i])
        {
            p.push_back(i);
            //num++;
        }
        for (int j = 0; j <= p.size() && i * p[j] < INF; j++)
        {
            isp[i * p[j]] = 0;
            if (!(i % p[j]))
                break;
        }
    }
    return;
}
int main()
{
    int a, b, d, sum = 0;
    cin >> a >> b >> d;
    prime();
    //for(auto r : p)
    //cout<<r<<endl;
    char c[8];
    for (int i = a; i < b; i++)
    {
        if (isp[i])
        {
            sprintf(c, "%d", i);
            for (int j = 0; j < strlen(c); j++)
            {
                if ((c[j] - '0') == d)
                {
                    sum++;
                    break;
                }
            }
        }
    }
    cout << sum;
}

// Problem5115:
#include <cstring>
#include <cmath>
//#include<ctime>
//#include<windows.h>
//#include<algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 100000000
#define LL long long
using namespace std;
void in();
void maopao();
void print();
int n, a[2005], s;
int main()
{

    cin >> n;
    in();
    maopao();
    print();
}
void in()
{
    for (int i = 1; i <= n; i++)
        cin >> a[i];
}
void maopao()
{
    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= n - i; j++)
            if (a[j] > a[j + 1])
            {
                s = a[j];
                a[j] = a[j + 1];
                a[j + 1] = s;
            }
}
void print()
{
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
}

// Problem5115:
#include <cstring>
#include <cmath>
//#include<ctime>
//#include<windows.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 100000000
#define LL long long
using namespace std;
int n, a[2005];
void in();
void print();
int main()
{
    cin >> n;
    in();
    sort(a + 1, a + n + 1);
    print();
}
void in()
{
    for (int i = 1; i <= n; i++)
        cin >> a[i];
}
void print()
{
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
}

// Problem5116:
#include <cstring>
#include <cmath>
#include <ctime>
//#include<windows.h>
#include <algorithm>
#include <iostream>
//#include<cstdlib>
#include <cstdio>
#include <string>
#define INF 4000005
#define LL long long
using namespace std;
int mylong(int x, int y);
int a[50005];
int my(const int &a, const int &b);
int main()
{
    a[0] = 0;
    LL t, s = 0;
    int n, ci = 0;
    cin >> t >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1, my);
    for (int i = 0; i <= n; i++)
    {
        s += mylong(a[i], a[i + 1]);
        if (s <= t)
        {
            ci++;
        }
    }
    cout << ci;
}
int mylong(int x, int y)
{
    return abs(x - y);
}
int my(const int &a, const int &b)
{
    return abs(a) < abs(b);
}

// Problem5416:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
bool b[21] = {0}, p[41];
int a[21];
int n, c;
int search(int);
void print(int);
void prime();
int main()
{
    //freopen("2.txt","r",stdin);
    //freopen("1.txt","w",stdout);
    prime();
    a[1] = 1;
    b[1] = 1;
    int k = 0;
    while (scanf("%d", &n) == 1)
    {
        k++;
        //for(int i=1;i<=40;i++)
        //       if(p[i])cout<<i<<" ";
        printf("Case %d:\n", k);
        search(2);
        printf("\n");
    }
    //while(1);
}
int search(int i)
{
    for (int j = 1; j <= n; j++)
    {
        if (!b[j] && p[j + a[i - 1]])
        {
            b[j] = 1;
            a[i] = j;
            if (i == n && p[j + 1])
                print(i);
            else
                search(i + 1);
            b[j] = 0;
        }
    }
}
void print(int i)
{
    for (int j = 1; j < i; j++)
        printf("%d ", a[j]);
    printf("%d\n", a[i]);
    //printf("%d ",a[1]);
    //     for(int j=i;j>1;j--)
    //         printf("%d ",a[j]);
    //     printf("\n");
}
void prime()
{
    memset(p, 1, sizeof(p));
    p[1] = 0;
    for (int i = 2; i <= 40; i++)
    {
        if (p[i])
            for (int j = i * i; j <= 40; j += i)
                p[j] = 0;
    }
}

// Problem5516:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n;
int v[30][30];
int father[30];
int chu_du[30];
int ru_du[30];
//void floyd();
void merge(int a, int b);
bool check(int a, int b);
int find(int a);
void Init();
int main()
{
    int t;
    cin >> t;
    string s;
    while (t--)
    {
        //memset(v,0,sizeof(v));
        for (int i = 1; i < 30; i++)
            father[i] = i;
        memset(chu_du, 0, sizeof(chu_du));
        memset(ru_du, 0, sizeof(ru_du));
        cin >> n;
        bool NOT = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> s;
            //v[s[0]-'a'+1][s[s.size()-1]-'a'+1]++;
            merge(s[0] - 'a' + 1, s[s.size() - 1] - 'a' + 1);
            chu_du[s[0] - 'a' + 1]++;
            ru_du[s[s.size() - 1] - 'a' + 1]++;
        }
        int sum = 0, start = 0, end = 0;
        for (int i = 1; i <= 26; i++)
        {
            if (chu_du[i] != ru_du[i])
            {
                if (abs(chu_du[i] - ru_du[i]) > 1)
                {
                    NOT = 1;
                    break;
                }
                if (abs(chu_du[i] - ru_du[i]) == 1)
                {
                    sum++;
                    if (sum == 1)
                        start = i;
                    if (sum == 2)
                        end = i;
                }
                if (sum > 2)
                {
                    NOT = 1;
                    break;
                }
            }
        }
        //cout<<check(1,5)<<endl;
        for (int i = 1; i <= 26; i++)
            for (int j = 1; j <= 26; j++)
                if (j != i && (chu_du[i] || ru_du[i]) && (chu_du[j] || ru_du[j]) && !check(i, j))
                    NOT = 1;
        if (NOT)
        {
            cout << "The door cannot be opened." << endl;
            continue;
        }
        else
            cout << "Ordering is possible." << endl;
    }
    //while(1);
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (y != x)
        father[y] = x;
}
int find(int a)
{
    if (a != father[a])
        father[a] = find(father[a]);
    return father[a];
}
bool check(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x == y)
        return 1;
    else
        return 0;
}

// Problem5556:
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int N;
int c[50010], a[50010];
inline int lowbit(int x) { return x & (-x); }
void update(int x, int num)
{
    while (x <= N)
    {
        c[x] += num;
        x += lowbit(x);
    }
}
int sum(int x)
{
    int sum = 0;
    while (x > 0)
    {
        sum += c[x];
        x -= lowbit(x);
    }
    return sum;
}
inline int sum(int x1, int x2) { return sum(x2) - sum(x1 - 1); }
int main()
{
    int T;
    cin >> T;
    for (int ii = 1; ii <= T; ii++)
    {
        scanf("%d", &N);
        printf("Case %d:\n", ii);
        //cout<<"Case "<<ii<<":"<<endl;
        memset(c, 0, sizeof(c));
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= N; i++)
        {
            scanf("%d", &a[i]);
            //cin>>a[i];
            update(i, a[i]);
        }
        string s;
        int i, j;
        while (cin >> s)
        {
            if (s == "End")
                break;
            scanf("%d%d", &i, &j);
            //cin>>i>>j;
            if (s == "Add")
            {
                update(i, j);
                continue;
            }
            if (s == "Sub")
            {
                update(i, -j);
                continue;
            }
            if (s == "Query")
            {
                cout << sum(i, j) << endl;
                continue;
            }
        }
    }
}

// Problem5556:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 50005;
int sum[maxn << 2];
void Pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        scanf("%d", &sum[rt]);
        return;
    }
    int m = (l + r) >> 1;
    buildtree(l, m, rt << 1);
    buildtree(m + 1, r, rt << 1 | 1);
    Pushup(rt);
}
void updata(int p, int add, int l, int r, int rt)
{
    if (l == r)
    {
        sum[rt] += add;
        return;
    }
    int m = (l + r) >> 1;
    if (p <= m)
        updata(p, add, l, m, rt << 1);
    else
        updata(p, add, m + 1, r, rt << 1 | 1);
    Pushup(rt);
}
int query(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
        return sum[rt];
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m)
        ret += query(L, R, l, m, rt << 1);
    if (R > m)
        ret += query(L, R, m + 1, r, rt << 1 | 1);
    return ret;
}
int main()
{
    int T, n;
    int k = 1;
    scanf("%d", &T);
    while (T--)
    {
        memset(sum, 0, sizeof(sum));
        scanf("%d", &n);
        printf("Case %d:\n", k++);
        buildtree(1, n, 1);
        string s;
        while (cin >> s)
        {
            int i, j;
            if (s[0] == 'E')
                break;
            scanf("%d%d", &i, &j);
            if (s[0] == 'Q')
            {
                printf("%d\n", query(i, j, 1, n, 1));
            }
            else if (s[0] == 'S')
                updata(i, -j, 1, n, 1);
            else
                updata(i, j, 1, n, 1);
        }
    }
}

// Problem5556:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
namespace MineWorkSpace
{
int n;
class Block_Main
{
    int block, n;
    int a[50005], in[50005], sum[305];

  public:
    void Init(int N)
    {
        memset(in, 0, sizeof(in));
        memset(sum, 0, sizeof(sum));
        memset(a, 0, sizeof(a));
        n = N;
        block = sqrt(n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", a + i);
            in[i] = (i - 1) / block + 1;
            sum[in[i]] += a[i];
        }
    }
    void Updata(int i, int c)
    {
        a[i] += c;
        sum[in[i]] += c;
    }
    int Query(int l, int r)
    {
        int ans = 0;
        if (in[l] == in[r])
        {
            for (int i = l; i <= r; i++)
                ans += a[i];
            return ans;
        }
        else
        {
            for (int i = in [l] + 1; i <= in[r] - 1; i++)
                ans += sum[i];
            for (int i = l; i <= in[l] * block; i++)
                ans += a[i];
            for (int i = (in[r] - 1) * block + 1; i <= r; i++)
                ans += a[i];
            return ans;
        }
    }
} Block;
class Order_run
{
    int l, r;

  public:
    void Run(char c)
    {
        if (c == 'Q')
        {
            scanf("%d%d", &l, &r);
            if (l > r)
                printf("0\n");
            else
                printf("%d\n", Block.Query(l, r));
            return;
        }
        if (c == 'A')
        {
            scanf("%d%d", &l, &r);
            Block.Updata(l, r);
            return;
        }
        if (c == 'S')
        {
            scanf("%d%d", &l, &r);
            Block.Updata(l, -r);
            return;
        }
    }
} Order;
class Main
{
  public:
    Main()
    {
        int T;
        scanf("%d", &T);
        for (int L = 1; L <= T; L++)
        {
            printf("Case %d:\n", L);
            scanf("%d", &n);
            Block.Init(n);
            char s[10];
            while (1)
            {
                scanf("%s", s);
                if (s[0] == 'E')
                    break;
                Order.Run(s[0]);
            }
        }
    }
} run;
}
int main() { ; }
// Problem5613:
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define INF 1000000000
using namespace std;
struct student
{
    string number;
    int score;
} a[1005];
int mycomp(const student &a, const student &b)
{
    if (a.score > b.score)
        return 1;
    if (a.score < b.score)
        return 0;
    if (a.number < b.number)
        return 1;
    return 0;
}
int main()
{
    while (1)
    {
        int n, m, g;
        cin >> n;
        if (n == 0)
            break;
        cin >> m >> g;
        int s[m + 1];
        for (int i = 1; i <= m; i++)
        {
            //scanf("%d",s[i]);
            cin >> s[i];
        }
        //student a[n+1];
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].number;
            a[i].score = 0;
            int b;
            cin >> b;
            for (int j = 1; j <= b; j++)
            {
                int p;
                //scanf("%d",p);
                cin >> p;
                a[i].score += s[p];
            }
        }
        int q;
        bool qi = 1;
        sort(a + 1, a + n + 1, mycomp);
        for (int i = 1; i <= n; i++)
        {
            if (a[i].score < g)
            {
                q = i - 1;
                qi = 0;
                break;
            }
        }
        if (qi)
            q = n;
        //if(n==1)
        //        {
        //
        //                if(a[1].score>=g) q=1;
        //                else q=0;
        //        }
        //        else
        //        {
        //            sort(a+1,a+n+1,mycomp);
        //            int h=1,l=n;
        //            for(;;)
        //            {
        //                   //int h=1,l=n;
        //                   int mid=(h+l)/2;
        //                   if(a[mid].score>=g) h=mid;
        //                   else l=mid;
        //                   if(l-h==1)
        //                   {
        //                           q=h;
        //                           break;
        //                   }
        //            }
        //        }
        cout << q << endl;
        for (int i = 1; i <= q; i++)
        {
            cout << a[i].number << " " << a[i].score << endl;
        }
    }
}

// Problem5773:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define LL long long
using namespace std;
LL a[501][501][2];
int main()
{
    //LL a[501][501],b[501][501];
    memset(a, 0, sizeof(a));
    //memset(b,0,sizeof(b));
    for (int i = 1; i <= 500; i++)
    {
        for (int j = i; j <= 500; j++)
        {
            a[j][i][0] += a[j - 1][i][0] + j - i + 1;
        }
        for (int j = 2 * i; j <= 500; j++)
        {
            a[j][i][1] += a[j - 1][i][1] + j - (2 * i - 1);
        }
    }
    int n;
    while (cin >> n)
    {
        LL ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ans = ans + a[n][i][0] + a[n][i][1];
        }
        cout << ans << endl;
    }
}

// Problem5773:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define LL long long
using namespace std;
//LL a[501][501][2];
int main()
{
    LL a[501][501][2];
    //LL a[501][501],b[501][501];
    memset(a, 0, sizeof(a));
    //memset(b,0,sizeof(b));
    for (int i = 1; i <= 500; i++)
    {
        for (int j = i; j <= 500; j++)
        {
            a[j][i][0] += a[j - 1][i][0] + j - i + 1;
        }
        for (int j = 2 * i; j <= 500; j++)
        {
            a[j][i][1] += a[j - 1][i][1] + j - (2 * i - 1);
        }
    }
    int n;
    while (cin >> n)
    {
        LL ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ans = ans + a[n][i][0] + a[n][i][1];
        }
        cout << ans << endl;
    }
}
// Problem5946:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 100;
struct Matrix
{
    int x, y;
    int a[MAXN][MAXN];
    Matrix()
    {
        memset(a, 0, sizeof(a));
        x = 0;
        y = 0;
    }
    void Init(int b[MAXN][MAXN], int m, int n)
    {
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = b[i][j];
        x = m, y = n;
    }

    Matrix operator*(const Matrix &h)
    {
        //try
        //              {
        //                   if(y!=b.x) throw 1;
        //              }
        //              catch(int i)
        //              {
        //                   exit(0);
        //              }
        //cout<<"1";
        //while(1);
        Matrix c;
        //int c[x+1][h.y+1];
        c.x = x, c.y = h.y;
        for (int i = 1; i <= c.x; i++)
            for (int j = 1; j <= c.y; j++)
            {
                for (int k = 1; k <= y; k++)
                    c.a[i][j] += (a[i][k] * h.a[k][j]) % 9973;
                c.a[i][j] %= 9973;
            }
        return c;
    }
};
ostream &operator<<(ostream &out, const Matrix &b)
{
    for (int i = 1; i <= b.x; i++)
    {
        for (int j = 1; j <= b.y; j++)
            cout << b.a[i][j] << " ";
        cout << '\n';
    }
    return out;
}
Matrix pow(Matrix a, int p)
{
    Matrix ans;
    ans.x = a.x;
    ans.y = a.y;
    for (int i = 1; i < 100; i++)
        ans.a[i][i] = 1;
    while (p)
    {
        if (p & 1)
            ans = ans * a;
        p = p >> 1;
        a = a * a;
    }
    return ans;
}
int main()
{
    int t, n, k;
    cin >> t;
    while (t--)
    {
        int c[MAXN][MAXN], sum = 0;
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> c[i][j];
        Matrix a;
        a.Init(c, n, n);
        a = pow(a, k);
        for (int i = 1; i <= n; i++)
        {
            sum += a.a[i][i];
            sum %= 9973;
        }
        cout << sum << endl;
    }
}

// Problem5969:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int START, END;
    int SPEED;
    bool operator<(const edge &a) const
    {
        return SPEED < a.SPEED;
    }
} v[2005];
int father[1000];
int find(int a)
{
    if (a != father[a])
        father[a] = find(father[a]);
    return father[a];
}
void merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
        father[y] = x;
}
bool check(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
        return 0;
    return 1;
}
int main()
{
    int n, m, begin, end, speed;
    while (cin >> n >> m)
    {
        memset(v, 0, sizeof(v));
        memset(father, 0, sizeof(father));
        for (int i = 1; i <= m; i++)
        {
            cin >> begin >> end >> speed;
            v[i].SPEED = speed;
            v[i].START = begin;
            v[i].END = end;
            v[i + m].SPEED = speed;
            v[i + m].START = end;
            v[i + m].END = begin;
        }
        sort(v + 1, v + 2 * m + 1);
        v[2 * m + 1].SPEED = 0x7fffffff;
        int Q;
        cin >> Q;
        int Start, End;
        while (Q--)
        {
            cin >> Start >> End;
            int minn = 0x3fffffff;
            for (int i = 1; i <= 2 * m; i++)
            {
                int k = 2 * m + 1;
                for (int j = 1; j <= n; j++)
                    father[j] = j;
                merge(v[i].START, v[i].END);
                for (int j = i; j <= 2 * m; j++)
                {
                    merge(v[j].START, v[j].END);
                    if (check(Start, End))
                    {
                        k = j;
                        break;
                    }
                }
                minn = min(minn, abs(v[k].SPEED - v[i].SPEED));
            }
            if (minn >= 0x3fffffff)
                cout << "-1" << endl;
            else
                cout << minn << endl;
        }
    }
}

// Problem5970:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct node
{
    int v;
    int s, e, next;
} v[1050];
int /*first[105],*/ dis[105][105] /*,p*/, v1[105][105], ans, n;
inline void Init();
inline void add(int a, int b, int v);
inline void floyd();
int main()
{
    while (scanf("%d", &n) == 1)
    {
        Init();
        floyd();
        if (ans < 0xf0f0f0f)
            cout << ans << endl;
        else
            cout << "It's impossible." << endl;
    }
}
inline void Init()
{
    int m;
    cin >> m;
    //p=1;
    int a, b, c;
    memset(v1, 0xf, sizeof(v1));
    //memset(first,-1,sizeof(first));
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b >> c;
        if (v1[a][b] > c)
        {
            v1[a][b] = c;
            v1[b][a] = c;
        }
        //add(a,b,c);
        //add(b,a,c);
    }
}
// inline void add(int a,int b,int z){
// v[p].s=a;
// v[p].e=b;
// v[p].v=z;
// v[p].next=first[a];
// first[a]=p++;
// }
inline void floyd()
{
    memset(dis, 0xf, sizeof(dis));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dis[i][j] = v1[i][j];
    for (int i = 1; i <= n; i++)
        dis[i][i] = 0;
    ans = 0x7fffffff;
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= k - 1; i++)
            for (int j = i + 1; j <= k - 1; j++)
                ans = min(ans, dis[i][j] + v1[j][k] + v1[k][i]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
}

// Problem6063:
#include <iostream>
#include <cstring>
#include <cstdio>
#define LL long long
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
using namespace std;
const int N = 100005;
int sum[N << 2];
int change[N << 2];
void Pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void Pushdown(int rt, int m)
{
    if (change[rt])
    {
        change[rt << 1] = change[rt << 1 | 1] = change[rt];
        sum[rt << 1] = change[rt] * (m - (m >> 1));
        sum[rt << 1 | 1] = change[rt] * (m >> 1);
        change[rt] = 0;
    }
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        sum[rt] = 1;
        return;
    }
    int m = (l + r) >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        change[rt] = c;
        sum[rt] = c * (r - l + 1);
        return;
    }
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m)
        update(L, R, c, lch);
    if (R > m)
        update(L, R, c, rch);
    Pushup(rt);
}
int query(int L, int R, int l, int r, int rt)
{
    int ret = 0;
    //if(change[rt])return change[rt]*(min(R,r)-max(L,l)+1);
    if (L <= l && R >= r)
    {
        return sum[rt];
    }
    //Pushdown(rt,r-l+1);
    int m = (l + r) >> 1;
    if (L <= m)
        ret += query(L, R, lch);
    if (R > m)
        ret += query(L, R, rch);
    return ret;
}
int main()
{
    int T;
    scanf("%d", &T);
    for (int j = 1; j <= T; j++)
    {
        memset(sum, 0, sizeof(sum));
        memset(change, 0, sizeof(change));
        int n;
        scanf("%d", &n);
        buildtree(1, n, 1);
        int m;
        int a, b, c;
        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            update(a, b, c, 1, n, 1);
        }
        printf("Case %d: The total value of the hook is %d.\n", j, query(1, n, 1, n, 1));
    }
    //while(1);
}

// Problem6080:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <ctime>
#define LL long long
using namespace std;
bool fu = 0;
vector<int> read();
vector<int> read()
{
    vector<int> so;
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 10000)
        {
            so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || so.size() == 0)
    {
        so.push_back(sum);
    }
    return so;
}
void print(vector<int> y)
{
    if (fu)
        printf("-");
    printf("%d", y[y.size() - 1]);
    for (int i = y.size() - 2; i >= 0; i--)
        printf("%04d", y[i]);
    printf("\n");
}
//void print(vector<LL> y)
//{
//     if(fu) printf("-");
//     printf("%d",y[y.size()-1]);
//     for(int i=y.size()-2;i>=0;i--)
//             printf("%09d",y[i]);
//     printf("\n");
//}
vector<int> add(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
            b.push_back(0);
    }
    else
        for (int i = a.size(); i < b.size(); i++)
            a.push_back(0);
    int y = 0;
    vector<int> c;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        int s = a[i] + b[i] + y;
        y = s / 10000;
        s = s % 10000;
        c.push_back(s);
    }
    if (y != 0)
        c.push_back(y);
    while (c[c.size() - 1] == 0 && c.size() > 1)
    {
        c.pop_back();
    }
    return c;
}
vector<int> sub(vector<int> a, vector<int> b)
{
    vector<int> so;
    if (a.size() < b.size())
    {
        vector<int> c = a;
        a = b;
        b = c;
        fu = 1;
    }
    if (a.size() == b.size())
    {
        bool io = 0;
        int k;
        for (k = a.size() - 1; k >= 0; k--)
        {
            if (a[k] < b[k])
            {
                fu = 1;
                io = 1;
                break;
            }
            if (a[k] > b[k])
            {
                fu = 0;
                io = 1;
                break;
            }
        }
        if (!io)
        {
            so.push_back(0);
            return so;
        }
        if (fu)
        {
            vector<int> c = a;
            a = b;
            b = c;
        }
    }
    for (int i = b.size(); i < a.size(); i++)
        b.push_back(0);
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] < b[i])
        {
            a[i] += 10000;
            a[i + 1]--;
        }
        so.push_back(a[i] - b[i]);
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
vector<int> mult(vector<int> a, vector<int> b)
{
    vector<int> so(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        int y = 0;
        for (int j = 0; j < b.size(); j++)
        {
            so[i + j] += a[i] * b[j] + y;
            y = so[i + j] / 10000;
            so[i + j] %= 10000;
        }
        so[i + b.size()] = y;
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
bool compare(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
        return 1;
    if (a.size() < b.size())
        return 0;
    for (int i = a.size() - 1; i >= 0; i--)
    {
        if (a[i] < b[i])
        {
            return 0;
        }
        if (a[i] > b[i])
        {
            return 1;
        }
    }
    return 1;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
//vector<int> f(int x)
//{
//            if(x==1) {vector<int> so(1,1);return so;}
//            if(x==2) {vector<int> so(1,1);return so;}
//            return add(f(x-1),f(x-2));
//}
int main()
{
    vector<int> s1, s2, s3;
    s2.push_back(1);
    vector<vector<int>> s;
    s.push_back(s2);
    s.push_back(s2);
    for (int i = 2; i <= 1000; i++)
    {
        s.push_back(add(s[i - 1], s[i - 2]));
    }
    int n, m;
    cin >> n;
    while (n--)
    {
        cin >> m;
        print(s[m - 1]);
    }
    //s1=read();
    //    vector<int> i(1,1);
    //    s2.push_back(1);
    //    s3.push_back(1);
    //for(;compare(s1,i);i=add(i,s2))
    //    {
    //         s3=mult(s3,i);
    //    }
    //print(s1);
    //s2=read();
    //print(s2);
    //s3=add(s1,s2);
    //s3=sub(s1,s2);
    //s3=mult(s1,s2);
    //print(s3);
    //cout<<endl<<clock();
    //while(1);
}

// Problem6286:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
const double pi = acos(-1.0);
int m;
double q, sum;
int n, f, ri[10005];
vector<double> s;
double solve(double r, double l)
{
    if (abs(r - l) < 0.00001)
        return r;
    else
    {
        int u = 0;
        double mid = (r + l) / 2;
        for (int i = 0; i < n; i++)
            u += (int)(s[i] / mid);
        if (u >= f)
            return solve(mid, l);
        else
            return solve(r, mid);
    }
}
int main()
{
    cin >> m;
    while (m--)
    {
        scanf("%d%d", &n, &f);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", ri + i);
            s.push_back(ri[i] * ri[i] * pi);
            sum += ri[i] * ri[i] * pi;
        }
        f++;
        printf("%.4lf\n", solve(0, sum));
        sum = 0;
        s.clear();
    }
    getchar();
    getchar();
}

// Problem6329:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define LL long long
using namespace std;
int n;
LL f(int x)
{
    if (x == n)
        return 1;
    else
        return 2 * f(x + 1) + 2;
}
int main()
{

    while (cin >> n)
        cout << f(1) << endl;
    //while(1);
}

// Problem6362:
#include <iostream>
#include <cstdio>
#define LL long long
using namespace std;
int main()
{
    //freopen("2.txt","r",stdin);
    //	freopen("1.txt","w",stdout);
    LL a[42];
    a[1] = 3;
    a[2] = 8;
    for (int i = 3; i <= 41; i++)
    {
        a[i] = 2 * a[i - 1] + 2 * a[i - 2];
    }
    int c;
    while (cin >> c)
    {
        cout << a[c] << endl;
    }
}

// Problem6801:
#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
using namespace std;
long long f(int x)
{
    if (x == 1)
        return 1;
    if (x == 2)
        return 3;
    return f(x - 1) + 2 * f(x - 2);
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int m;
        cin >> m;
        cout << f(m) << endl;
        //m++;
        //            cout<<(pow(2.0,m)-pow(-1.0,m))/3<<endl;
    }
}

// Problem7321:
#include <iostream>
#include <cstring>
#include <cstdio>
#define LL long long
using namespace std;
LL f[100005];
LL pow_mod(LL a, LL b, LL p)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}
LL lucas(LL a, LL b, LL p)
{
    LL ans = 1;
    while (a && b)
    {
        LL m = a % p, n = b % p;
        if (m < n)
            return 0;
        ans = ans * f[m] * pow_mod(f[n] * f[m - n] % p, p - 2, p) % p;
        a /= p;
        b /= p;
    }
    return ans;
}
int main()
{
    LL t, n, m, p;
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> p;
        f[0] = 1;
        for (int i = 1; i <= p; i++)
            f[i] = f[i - 1] * i % p;
        cout << lucas(m + n, m, p) << endl;
    }
}

// Problem7625:
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
bool d[105][105];
int ru_du[105];
int main()
{
    int n, m;
    while (1)
    {
        cin >> n >> m;
        int a, b;
        memset(d, 0, sizeof(d));
        memset(ru_du, 0, sizeof(ru_du));
        if (n == 0)
            break;
        for (int i = 1; i <= m; i++)
        {
            cin >> a >> b;
            if (!d[a][b])
                ru_du[b]++;
            d[a][b] = 1;
        }
        int s = 0;
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (ru_du[i] == 0)
                q.push(i);
        while (!q.empty())
        {
            int tmp = q.front();
            s++;
            q.pop();
            for (int i = 0; i < n; i++)
            {
                if (d[tmp][i])
                {
                    ru_du[i]--;
                    if (ru_du[i] == 0)
                        q.push(i);
                }
            }
        }
        //int s=0;
        //for(int i=0;i<n;i++)
        //	if(ru_du[i]>0) s++;
        if (s == n)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}

// Problem10063:
#include <iostream>
#include <iostream>
using namespace std;
#define LL long long
const int p = 1000000007;
LL pow_mod(LL a, LL b)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        LL m, n;
        cin >> n >> m;
        if (n == 1 || m == 1)
            cout << n + m << endl;
        else
            cout << (pow_mod(m, n + 1) - 1) * pow_mod(m - 1, p - 2) % p << endl;
    }
}
// Problem10250:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;
bool fu = 0;
vector<int> read()
{
    vector<int> so;
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 10000)
        {
            so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || so.size() == 0)
    {
        so.push_back(sum);
    }
    return so;
}
void print(vector<int> y)
{
    if (fu)
        printf("-");
    printf("%d", y[y.size() - 1]);
    for (int i = y.size() - 2; i >= 0; i--)
        printf("%04d", y[i]);
    printf("\n");
}
vector<int> add(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
            b.push_back(0);
    }
    else
        for (int i = a.size(); i < b.size(); i++)
            a.push_back(0);
    int y = 0;
    vector<int> c;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        int s = a[i] + b[i] + y;
        y = s / 10000;
        s = s % 10000;
        c.push_back(s);
    }
    if (y != 0)
        c.push_back(y);
    while (c[c.size() - 1] == 0 && c.size() > 1)
    {
        c.pop_back();
    }
    return c;
}
vector<int> sub(vector<int> a, vector<int> b)
{
    vector<int> so;
    if (a.size() < b.size())
    {
        vector<int> c = a;
        a = b;
        b = c;
        fu = 1;
    }
    if (a.size() == b.size())
    {
        bool io = 0;
        int k;
        for (k = a.size() - 1; k >= 0; k--)
        {
            if (a[k] < b[k])
            {
                fu = 1;
                io = 1;
                break;
            }
            if (a[k] > b[k])
            {
                fu = 0;
                io = 1;
                break;
            }
        }
        if (!io)
        {
            so.push_back(0);
            return so;
        }
        if (fu)
        {
            vector<int> c = a;
            a = b;
            b = c;
        }
    }
    for (int i = b.size(); i < a.size(); i++)
        b.push_back(0);
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] < b[i])
        {
            a[i] += 10000;
            a[i + 1]--;
        }
        so.push_back(a[i] - b[i]);
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
vector<int> mult(vector<int> a, vector<int> b)
{
    vector<int> so(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        int y = 0;
        for (int j = 0; j < b.size(); j++)
        {
            so[i + j] += a[i] * b[j] + y;
            y = so[i + j] / 10000;
            so[i + j] %= 10000;
        }
        so[i + b.size()] = y;
    }
    while (so[so.size() - 1] == 0 && so.size() > 1)
    {
        so.pop_back();
    }
    return so;
}
bool compare(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
        return 1;
    if (a.size() < b.size())
        return 0;
    for (int i = a.size() - 1; i >= 0; i--)
    {
        if (a[i] < b[i])
        {
            return 0;
        }
        if (a[i] > b[i])
        {
            return 1;
        }
    }
    return 1;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int main()
{
    vector<int> s1, s2, s3;
    s1 = read();
    vector<int> i(1, 1);
    s2.push_back(1);
    s3.push_back(1);
    for (; compare(s1, i); i = add(i, s2))
    {
        s3 = mult(s3, i);
    }
    //print(s1);
    //s2=read();
    //print(s2);
    //s3=add(s1,s2);
    //s3=sub(s1,s2);
    //s3=mult(s1,s2);
    print(s3);
    //while(1);
}

// Problem10251:
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define LL long long
using namespace std;
LL f(int x)
{
    if (x == 1)
        return 0;
    if (x == 2)
        return 1;
    return f(x - 1) + f(x - 2);
}
int main()
{
    int n;
    cin >> n;
    cout << f(n) << endl;
}

// Problem10252:
#include <stdio.h>
int m;
int f(int n)
{
    if (n == 0)
        return 1;
    return (f(n - 1) + m) % n;
}
int main()
{
    int n, k = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        k = (k + m) % i;
    }
    printf("%d", k + 1);
    //while(1);
}

// Problem10254:
#include <iostream>
#include <stack>
//#include<map>
using namespace std;
//int top(char a,bool b);
int a[1005];
int main()
{
    int n;
    stack<int> b;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
    }
    int k = 1;
    for (int i = 1; i <= n; i++)
    {
        if (b.empty() || a[k] > b.top())
        {
            b.push(i);
            //continue;
        }
        while (!b.empty() && a[k] == b.top())
        {
            //cout<<b.top()<<" ";
            b.pop();
            k++;
        }
    }
    if (b.empty())
        cout << "YES";
    else
        cout << "NO";
}

// Problem10255:
#include <iostream>
#include <stack>
using namespace std;
int main()
{
    stack<char> a;
    string s;
    cin >> s;
    for (int i = 0; s[i] != '@'; i++)
    {
        if (s[i] == '(')
        {
            a.push(s[i]);
        }
        if (s[i] == ')')
        {
            if (a.empty())
                goto end;
            a.pop();
        }
    }
    if (a.empty())
        cout << "YES" << endl;
    else
    end:
        cout << "NO" << endl;
}

// Problem10256:
#include <iostream>
#include <stack>
//#include<map>
using namespace std;
int main()
{
    stack<char> a;
    string s;
    cin >> s;
    for (int i = 0; i <= s.size(); i++)
    {
        if (s[i] == '(' || s[i] == '[')
        {
            a.push(s[i]);
        }
        if (s[i] == ')')
        {
            if (a.empty())
                goto end;
            if (a.top() == '[')
                goto end;
            a.pop();
        }
        if (s[i] == ']')
        {
            if (a.empty())
                goto end;
            if (a.top() == '(')
                goto end;
            a.pop();
        }
    }
    if (a.empty())
        cout << "OK" << endl;
    else
    end:
        cout << "Wrong" << endl;
}

// Problem10258:
#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;
int top(char a, bool b);
int n = 1;
bool check();
string s;
stack<char> a;
stack<int> c;
queue<char> b;
string l = "0";
void solve();
int trans(int);
int main()
{

    cin >> s;
    check();
    solve();
    getchar();
    getchar();
}
int top(char a, bool b)
{
    if (a == '+' || a == '-')
        return 1;
    if (a == '*' || a == '/')
        return 2;
    if (a == '^')
        return 3;
    if (a == '(' && b)
        return 0;
    if (a == '(' && !b)
        return 4;
}
bool check()
{
    if (s[0] == '+' || s[0] == '-')
    {
        if (s[1] == '0')
        {
            cout << "NO";
            exit(0);
        }
        s = l + s;
    }
    if (s[0] == '*' || s[0] == '/')
    {
        cout << "NO";
        exit(0);
    }
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            a.push(s[i]);
        }
        if (s[i] == ')')
        {
            if (a.empty())
            {
                cout << "NO";
                exit(0);
            }
            a.pop();
        }
    }
    if (!a.empty())
    {
        cout << "NO";
        exit(0);
    }
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(' || s[i] == '+' || s[i] == '/' || s[i] == '*' || s[i] == '-' || s[i] == '^')
        {
            if (s[i] == '(')
            {
                if (s[i - 1] >= '0' && s[i - 1] <= '9')
                {
                    cout << "NO";
                    exit(0);
                }
                n = 1;
                if (s[i + 1] == '-' || s[i + 1] == '+')
                {
                    if (s[i + 2] == '0')
                    {
                        cout << "NO";
                        exit(0);
                    }
                    b.push(0);
                }
                if (s[i + 1] == '*' || s[i + 1] == '/')
                {
                    cout << "NO";
                    exit(0);
                }
            }
            else
                n++;
            if (n > 2)
            {
                cout << "NO" << endl;
                exit(0);
            }
            if (a.empty() || top(a.top(), 1) < top(s[i], 0))
            {
                a.push(s[i]);
                continue;
            }
            while (!a.empty() && top(a.top(), 1) >= top(s[i], 0))
            {
                b.push(a.top());
                a.pop();
            }
            a.push(s[i]);
            continue;
        }
        if (s[i] == ')')
        {
            while (a.top() != '(')
            {
                b.push(a.top());
                a.pop();
            }
            a.pop();
            continue;
        }
        n = 1;
        i += trans(i);
    }
    if (n >= 2)
    {
        cout << "NO";
        exit(0);
    }
    while (!a.empty())
    {
        b.push(a.top());
        a.pop();
    }
}
void solve()
{
    while (!b.empty())
    {
        if (b.front() == '+' /*||b.front()=='-'||b.front()=='*'||b.front()=='/'*/)
        {
            int p, q;
            p = c.top();
            c.pop();
            q = c.top();
            c.pop();
            c.push(q + p);
            b.pop();
            continue;
        }
        if (b.front() == '-')
        {
            int p, q;
            p = c.top();
            c.pop();
            q = c.top();
            c.pop();
            c.push(q - p);
            b.pop();
            continue;
        }
        if (b.front() == '*')
        {
            int p, q;
            p = c.top();
            c.pop();
            q = c.top();
            c.pop();
            c.push(q * p);
            b.pop();
            continue;
        }
        if (b.front() == '/')
        {
            int p, q;
            p = c.top();
            c.pop();
            q = c.top();
            c.pop();
            if (p == 0)
            {
                cout << "NO";
                exit(0);
            }
            c.push(q / p);
            b.pop();
            continue;
        }
        if (b.front() == '^')
        {
            int p, q;
            p = c.top();
            c.pop();
            q = c.top();
            c.pop();
            int y = q;
            for (int i = 1; i < p; i++)
            {
                q *= y;
            }
            c.push(q);
            b.pop();
            continue;
        }
        c.push(b.front());
        b.pop();
        continue;
    }
    cout << c.top();
}
int trans(int i)
{
    int k = -1, o = 0, m = 1;
    while (s[i] >= '0' && s[i] <= '9')
    {
        o = o * 10 + s[i] - '0';
        k++;
        i++;
    }
    b.push(o);
    return k;
}

// Problem10262:
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;
void print(vector<int> so);
int main()
{
    //freopen("madition.in","r",stdin);
    //freopen("madition.out","w",stdout);
    vector<int> s1, s2, s3;
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] >= '0' && s[i] <= '9')
            s1.push_back(s[i] - '0');
        if (s[i] >= 'a' && s[i] <= 'z')
            s1.push_back(s[i] - 'a' + 10);
    }
    cin >> s;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] >= '0' && s[i] <= '9')
            s2.push_back(s[i] - '0');
        if (s[i] >= 'a' && s[i] <= 'z')
            s2.push_back(s[i] - 'a' + 10);
    }
    if (s2.size() > s1.size())
    {
        for (int i = s1.size(); i < s2.size(); i++)
            s1.push_back(0);
    }
    if (s1.size() > s2.size())
    {
        for (int i = s2.size(); i < s1.size(); i++)
            s2.push_back(0);
    }
    int y = 0;
    for (int i = 0; i < s1.size(); i++)
    {
        int s = s1[i] + s2[i] + y;
        y = s / n;
        s %= n;
        s3.push_back(s);
    }
    if (y != 0)
    {
        s3.push_back(y);
    }
    while (s3[s3.size() - 1] == 0 && s3.size() > 1)
    {
        s3.pop_back();
    }
    print(s3);
    //while(1);
}
void print(vector<int> so)
{
    for (int i = so.size() - 1; i >= 0; i--)
    {
        if (so[i] >= 10)
            cout << char(so[i] - 10 + 'a');
        else
            cout << so[i];
    }
}

// Problem10264:
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int w[35], v[35], f[205];
int main()
{
    int n, m;
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];
    for (int i = 1; i <= n; i++)
        for (int vi = v[i]; vi <= m; vi++)
            f[vi] = max(f[vi], f[vi - v[i]] + w[i]);
    cout << "max=" << f[m] << endl;
}

// Problem10265:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[6005];
int w[505], c[505], s[505];
int n, m, maxl;
void ZOPack(int cost, int weight);
void CPack(int cost, int weight);
int main()
{

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> c[i] >> w[i] >> s[i];
    for (int i = 1; i <= n; i++)
    {
        int k = 1;
        while (k < s[i])
        {
            ZOPack(k * c[i], k * w[i]);
            s[i] = s[i] - k;
            k *= 2;
        }
        ZOPack(s[i] * c[i], s[i] * w[i]);
    }
    cout << f[m] << endl;
    //while(1);
}
void ZOPack(int cost, int weight)
{
    for (int v = m; v >= cost; v--)
    {
        f[v] = max(f[v], f[v - cost] + weight);
        //maxl=max(maxl,f[v]);
    }
}
void CPack(int cost, int weight)
{
    for (int v = cost; v <= m; v++)
    {
        f[v] = max(f[v], f[v - cost] + weight);
        //maxl=max(maxl,f[v]);
    }
}

// Problem10267:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int c[11][35], w[11][35];
int s[11];
int f[205];
int n, V, maxl, T;
void ZOPack(int cost, int weight);
void CPack(int cost, int weight);
int main()
{
    cin >> V >> n >> T;
    int wi, ci, ti;
    for (int i = 1; i <= n; i++)
    {
        cin >> ci >> wi >> ti;
        c[ti][++s[ti]] = ci;
        w[ti][s[ti]] = wi;
    }
    for (int t = 1; t <= T; t++)
    {
        for (int v = V; v >= 0; v--)
        {
            for (int i = 1; i <= s[t]; i++)
            {
                if (c[t][i] > v)
                    continue;
                f[v] = max(f[v], f[v - c[t][i]] + w[t][i]);
            }
        }
    }
    cout << f[V] << endl;
    //while(1);
}

// Problem10270:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[26], b[26][16], sum[26] = {0}, c[26], s[26];
int v, g, q = 1;
int mymin = 100;
bool d[16] = {0};
int search(int);
bool check();
bool comp(int);
int main()
{
    memset(s, 63, sizeof(s));
    scanf("%d", &v);
    for (int i = 1; i <= v; i++)
    {
        scanf("%d", &a[i]);
    }
    scanf("%d", &g);
    for (int i = 1; i <= g; i++)
        for (int j = 1; j <= v; j++)
            scanf("%d", &b[j][i]);
    //sort(q+1,q+g+1,comp);
    //for(int i=1;i<=g;i++)
    //       for(int j=1;j<=v;j++)
    //          printf("&d",b[j][i]);
    //while(1);
    search(1);
    printf("%d", mymin);
    for (int i = 1; i <= mymin; i++)
    {
        printf(" %d", s[i]);
    }
    //printf("%d",k+1);
    //while(1);
}
int search(int i)
{
    for (int j = q; j <= g; j++)
    {
        if (!d[j])
        {
            d[j] = 1;
            c[i] = j;
            for (int k = 1; k <= v; k++)
                sum[k] += b[k][j];
            if (check())
            {
                if (i < mymin)
                {
                    mymin = i;
                    for (int k = 1; k <= i; k++)
                        s[k] = c[k];
                }
                if (i == mymin)
                {
                    if (comp(i))
                        for (int k = 1; k <= i; k++)
                            s[k] = c[k];
                }
            }
            else if (i < mymin)
            {
                q = j;
                search(i + 1);
            }
            for (int k = 1; k <= v; k++)
                sum[k] -= b[k][j];
            d[j] = 0;
        }
    }
}
bool check()
{
    for (int i = 1; i <= v; i++)
    {
        if (sum[i] < a[i])
            return 0;
    }
    return 1;
}
bool comp(int i)
{
    for (int j = 1; j <= v; j++)
    {
        if (s[j] < c[j])
            return 0;
    }
    return 1;
}

// Problem10271:
#include <iostream>
#include <queue>
#define LL long long
using namespace std;
int main()
{
    queue<int> a;
    int n, k, m;
    cin >> n >> k;
    for (int i = 1; i <= k + 1; i++)
    {
        cin >> m;
        a.push(m);
    }
    int q = 0, sum = 0;
    while (!a.empty())
    {
        q += a.front();
        if (q <= n)
            a.pop();
        else
        {
            q -= a.front();
            if (q == 0)
            {
                cout << "No Solution" << endl;
                return 0;
            }
            q = 0;
            sum++;
        }
    }
    cout << sum << endl;
}

// Problem10272:
#include <iostream>
#include <queue>
#define LL long long
using namespace std;
struct data
{
    int n, m;
    bool operator<(const data &a) const
    {
        return a.n < n;
    }
};
int main()
{
    int n, m, c, d;
    priority_queue<data> a;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> c >> d;
        a.push((data){c, d});
    }
    int sum = 0;
    while (1)
    {
        if (n == 0)
            break;
        data s = a.top();
        a.pop();
        if (n >= s.m)
        {
            n -= s.m;
            sum += s.m * s.n;
        }
        else
        {
            sum += s.n * n;
            n -= n;
        }
    }
    cout << sum << endl;
}

// Problem10272:
#include <iostream>
#include <queue>
#define LL long long
using namespace std;
struct data
{
    int n, m;
    bool operator<(const data &a) const
    {
        return a.n < n;
    }
};
int main()
{
    int n, m, c, d;
    priority_queue<data> a;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> c >> d;
        a.push((data){c, d});
    }
    int sum = 0;
    while (1)
    {
        if (n == 0)
            break;
        data s = a.top();
        a.pop();
        if (n > s.m)
        {
            n -= s.m;
            sum += s.m * s.n;
        }
        else
        {
            sum += s.n * n;
            n -= n;
        }
    }
    cout << sum << endl;
}

// Problem10272:
#include <iostream>
#include <queue>
#define LL long long
using namespace std;
struct data
{
    int n, m;
    bool operator<(const data &a) const
    {
        return a.n < n;
    }
};
int main()
{
    int n, m, c, d;
    priority_queue<data> a;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> c >> d;
        a.push((data){c, d});
    }
    LL sum = 0;
    while (1)
    {
        if (n == 0)
            break;
        data s = a.top();
        a.pop();
        if (n > s.m)
        {
            n -= s.m;
            sum += s.m * s.n;
        }
        else
        {
            sum += s.n * n;
            n -= n;
        }
    }
    cout << sum << endl;
}

// Problem10272:
#include <iostream>
#include <queue>
#define LL long long
using namespace std;
struct data
{
    LL n, m;
    bool operator<(const data &a) const
    {
        return a.n < n;
    }
};
int main()
{
    LL n, m, c, d;
    priority_queue<data> a;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> c >> d;
        a.push((data){c, d});
    }
    LL sum = 0;
    while (1)
    {
        if (n == 0)
            break;
        data s = a.top();
        a.pop();
        if (n > s.m)
        {
            n -= s.m;
            sum += s.m * s.n;
        }
        else
        {
            sum += s.n * n;
            n -= n;
        }
    }
    cout << sum << endl;
}

// Problem10272:
#include <iostream>
#include <queue>
#define LL long long
using namespace std;
struct data
{
    LL n, m;
    bool operator<(const data &a) const
    {
        return a.n < n;
    }
};
int main()
{
    LL n, m, c, d;
    priority_queue<data> a;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> c >> d;
        a.push((data){c, d});
    }
    LL sum = 0;
    while (1)
    {
        if (n == 0)
            break;
        data s = a.top();
        a.pop();
        if (n >= s.m)
        {
            n -= s.m;
            sum += s.m * s.n;
        }
        else
        {
            sum += s.n * n;
            n -= n;
        }
    }
    cout << sum << endl;
}

// Problem10275:
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[10005];
int comp(const int &a, const int &b)
{
    return a < b;
}
int main()
{
    //freopen("waterj.in","r",stdin);
    //freopen("waterj.out","w",stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + m + 1, comp);
    for (int i = m + 1; i <= n; i++)
    {
        a[1] += a[i];
        if (a[1] > a[2])
            sort(a + 1, a + m + 1, comp);
    }
    printf("%d\n", a[m]);
}

// Problem10275:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
struct comp
{
    bool operator()(int &a, int &b)
    {
        return a > b;
    }
};
int main()
{
    //freopen("waterj.in","r",stdin);
    //freopen("waterj.out","w",stdout);
    priority_queue<int, vector<int>, comp> a;
    int n, m, c, d;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &c);
        a.push(c);
    }
    for (int i = m + 1; i <= n; i++)
    {
        scanf("%d", &c);
        d = a.top();
        a.pop();
        d += c;
        a.push(d);
    }
    while (a.size() > 1)
    {
        a.pop();
    }
    printf("%d", a.top());
}

// Problem10276:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[101][101], d[101], c[101];
bool b[101], e[101] = {0};
int n;
int search(int i);
int main()
{
    //freopen("concom.in","r",stdin);
    //freopen("concom.out","w",stdout);
    scanf("%d", &n);
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n; i++)
    {
        int p, s, q;
        scanf("%d%d%d", &p, &s, &q);
        a[p][s] = q;
        e[p] = 1;
    }
    for (int i = 1; i <= 100; i++)
    {
        memset(b, 0, sizeof(b));
        memset(d, 0, sizeof(d));
        memset(c, 0, sizeof(c));
        search(i);
        for (int j = 1; j <= 100; j++)
        {
            if (d[j] > 50 && j != i)
                printf("%d %d\n", i, j);
        }
    }
    //while(1);
}
int search(int i)
{
    if (!e[i] || b[i])
        return 0;
    b[i] = 1;
    for (int k = 1; k <= 100; k++)
    {
        d[k] += a[i][k];
        if (d[k] > 50)
        {
            c[k] = 1;
            search(k);
        }
    }
}

// Problem10277:
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

int s[200][200];
int dis[200][200];
//bool e[200][200]={0};
int main()
{
    memset(dis, 0xff, sizeof(dis));
    int k[210];
    int n, m, m1, m2, x1, y1, x2, y2;
    queue<int> a, b, c;
    cin >> m >> n >> m1 >> m2;
    const int dx[8] = {m1, -m1, m1, -m1, m2, m2, -m2, -m2},
              dy[8] = {m2, m2, -m2, -m2, m1, -m1, m1, -m1};
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
            if (s[i][j] == 3)
            {
                x1 = i;
                y1 = j;
            }
        }
    a.push(x1);
    b.push(y1);
    //c.push(0);
    dis[x1][y1] = 0;
    while (!a.empty())
    {
        int x = a.front(),
            y = b.front();
        //e[x][y]=1;
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || ny < 1 || nx > m || ny > n)
                continue;
            if (dis[nx][ny] == -1 && (s[nx][ny] == 1 || s[nx][ny] == 4))
            {
                a.push(nx);
                b.push(ny);
                dis[nx][ny] = dis[x][y] + 1;
            }
            if (s[nx][ny] == 4)
            {
                cout << dis[nx][ny] << endl;
                return 0;
            }
        }
        a.pop();
        b.pop();
    }
    //cout<<"-1"<<endl;
}

// Problem10281:
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int dx[8] = {1, -1, 1, -1, 2, 2, -2, -2},
          dy[8] = {2, 2, -2, -2, 1, -1, 1, -1};
char s[200][200];
int dis[200][200];
//bool e[200][200]={0};
int main()
{
    memset(dis, 0xff, sizeof(dis));
    int k[210];
    int n, m, x1, y1, x2, y2;
    queue<int> a, b, c;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
            if (s[i][j] == 'K')
            {
                x1 = i;
                y1 = j;
            }
            if (s[i][j] == 'H')
            {
                x2 = i;
                y2 = j;
            }
        }
    a.push(x1);
    b.push(y1);
    //c.push(0);
    dis[x1][y1] = 0;
    while (!a.empty())
    {
        int x = a.front(),
            y = b.front();
        //e[x][y]=1;
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || ny < 1 || nx > m || ny > n)
                continue;
            if (dis[nx][ny] == -1 && (s[nx][ny] == '.' || s[nx][ny] == 'H'))
            {
                a.push(nx);
                b.push(ny);
                dis[nx][ny] = dis[x][y] + 1;
            }
            if (s[nx][ny] == 'H')
            {
                cout << dis[nx][ny] << endl;
                return 0;
            }
        }
        a.pop();
        b.pop();
    }
    //cout<<"-1"<<endl;
}

// Problem10282:
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>
#define LL long long
using namespace std;
struct data
{
    LL pi, ci;
};
int com(const data &a, const data &b)
{
    return a.ci < b.ci;
}
int com1(const data &a, const data &b)
{
    return a.pi < b.pi;
}
int main()
{
    vector<data> a;
    LL n, k, m, pi, di;
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &pi, &di);
        a.push_back((data){pi, di});
    }
    sort(a.begin(), a.end(), com);
    vector<data>::iterator it = a.begin();
    int ans = 0;
    while (k--)
    {
        if (m < it->ci)
            break;
        m -= it->ci;
        it++;
        ans++;
        if (it == a.end())
            break;
    }
    if (it == a.end())
        goto end;
    sort(it, a.end(), com1);
    while (m >= it->pi)
    {
        m -= it->pi;
        it++;
        ans++;
        if (it == a.end())
            goto end;
    }
end:
    cout << ans << endl;
}

// Problem10283:
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>
#define LL long long
using namespace std;
struct data
{
    int a;
    bool b;
    //data(){b=1;}
};
int max(int a, int b) { return a > b ? a : b; }
struct number
{
    vector<LL> so;
    //bool fu;
    //number(){fu=0;}
    number() { ; }
    number(const int a) { *this = a; }
    number operator=(const int &a)
    {
        //if(b>=0) {fu=0;int a=b;}
        //else {fu=1;int a=-b;}
        LL y = a / 1000000000;
        LL s = a % 1000000000;
        if (y != 0)
            so.push_back(y);
        so.push_back(s);
        return *this;
    }
    number operator+(const number &b)
    {
        number a = b;
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        int y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 1000000000;
            s = s % 1000000000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator+(const int &b)
    {
        number a;
        int y = b / 1000000000;
        int s = b % 1000000000;
        a.so.push_back(s);
        a.so.push_back(y);
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 1000000000;
            s = s % 1000000000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator+=(const number &a)
    {
        *this = *this + a;
        return *this;
    }
    number operator+=(const int &a)
    {
        *this = *this + a;
        return *this;
    }
    number operator-(const int &a)
    {
        if (so[0] >= a)
            so[0] -= a;
        else
        {
            so[1]--;
            so[0] += 1000000000;
            so[0] -= a;
        }
        return *this;
    }
    number operator-=(const int &a)
    {
        *this = *this - a;
        return *this;
    }
    number operator*(const int &a)
    {
        number b = a;
        return *this * b;
    }
    number operator*=(const int &a)
    {
        *this = *this * a;
        return *this;
    }
    number operator*(const number &a)
    {
        number c;
        for (int i = 0; i < a.so.size() + so.size() + 1; i++)
            c.so.push_back(0);
        for (int i = 0; i < so.size(); i++)
        {
            int y = 0;
            for (int j = 0; j < a.so.size(); j++)
            {
                c.so[i + j] += so[i] * a.so[j] + y;
                y = c.so[i + j] / 1000000000;
                c.so[i + j] %= 1000000000;
            }
            c.so[i + a.so.size()] = y;
        }
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator*=(const number &a)
    {
        *this = *this * a;
        return *this;
    }
    bool operator>(const number &a) const
    {
        if (so.size() > a.so.size())
            return 1;
        if (so.size() < a.so.size())
            return 0;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 0;
            }
            if (so[i] > a.so[i])
            {
                return 1;
            }
        }
        return 0;
    }
    bool operator<(const number &a) const
    {
        if (so.size() > a.so.size())
            return 0;
        if (so.size() < a.so.size())
            return 1;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 1;
            }
            if (so[i] > a.so[i])
            {
                return 0;
            }
        }
        return 0;
    }
    bool operator==(const number &a) const { return (!(a < *this)) && (!(a > *this)); }
    bool operator>=(const number &a) const { return !(a > *this); }
    bool operator<=(const number &a) const { return !(a < *this); }
    bool operator!=(const number &a) const { return (a > *this) || (a < *this); }
};
void read(number &a)
{
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 1000000000)
        {
            a.so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || a.so.size() == 0)
    {
        a.so.push_back(sum);
    }
}
void print(number a)
{
    //if(fu) printf("-");
    printf("%d", a.so[a.so.size() - 1]);
    for (int i = a.so.size() - 2; i >= 0; i--)
        printf("%09d", a.so[i]);
    printf("\n");
}
map<int, vector<int>> a;
priority_queue<LL, vector<LL>, greater<LL>> b;
map<int, vector<int>>::iterator it;
LL n, di, pi, maxn = 0, tim = 0;
vector<int> tim1, v;
int find(int i)
{
    it = a.find(i);
    if (it == a.end())
    {
        if (i == maxn)
            return 0;
        return find(i + 1);
    }
    else
    {
        for (int k = 1; k < (it->second).size(); k++)
        {
            if (((it->second)[k]) == 1)
                return i;
        }
        if (i == maxn)
            return 0;
        return find(i + 1);
    }
}
int comp(const int &a, const int &b)
{
    return a > b;
}
int main()
{

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &di, &pi);
        (a[di]).push_back(pi);
        v.push_back(di);
        if (di > maxn)
            maxn = di;
    }
    sort(v.begin(), v.end());
    unique(v.begin(), v.end());
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        if (*it == maxn)
            v.erase(it + 1, v.end());
    }
    //for(vector<int>::iterator it=v.begin();it!=v.end();it++)
    //{
    //      cout<<*it<<" ";
    //}
    //while(1);
    number sum = 0;
    LL m = 0;
    m += v[0];
    sort(a[v[0]].begin(), a[v[0]].end(), comp);
    for (int j = 0; j < a[v[0]].size(); j++)
    {
        sum += a[v[0]][j];
        b.push(a[v[0]][j]);
        m--;
        if (m == 0)
            break;
    }
    for (int i = 1; i < v.size(); i++)
    {
        m += v[i] - v[i - 1];
        sort(a[v[i]].begin(), a[v[i]].end(), comp);
        int j;
        for (j = 0; j < a[v[i]].size(); j++)
        {
            sum += a[v[i]][j];
            b.push(a[v[i]][j]);
            m--;
            if (m == 0)
                break;
        }
        j++;
        while (m == 0 && j < a[v[i]].size())
        {
            if (a[v[i]][j] <= b.top())
                break;
            else
            {
                sum -= b.top();
                b.pop();
                sum += a[v[i]][j];
                b.push(a[v[i]][j]);
                j++;
            }
        }
    }
    print(sum);
    getchar();
    getchar();
}

// Problem10285:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
struct node
{
    int v;
    int s, e, next;
} v[100500];
int dis[3005], dis1[3005];
int first[3005], n, p, d[3005];
int x, y;
inline void add(int a, int b, int z);
inline void spfa(int lin);
//inline void floyd();
inline void read();
int main()
{
    read();
    //cout<<v[1].v;
    //while(1);
    //floyd();
    memset(dis1, 0, sizeof(dis1));
    spfa(x);
    for (int i = 1; i <= n; i++)
        dis1[i] = dis[i];
    //while(1);
    for (int i = 1; i <= n; i++)
    {
        if (i == x)
            continue;
        spfa(i);
        dis1[i] += dis[x];
    }
    cout << *max_element(dis1 + 1, dis1 + n + 1) << endl;
    getchar();
    getchar();
    //while(1);
}
inline void read()
{
    p = 1;
    memset(first, -1, sizeof(first));
    int m, a, b, z;
    cin >> n >> m >> x;
    while (m--)
    {
        cin >> a >> b >> z;
        //if(a==0&&a==b&&a==z) break;
        add(a, b, z);
        //add(b,a,z);
    }
    //cin>>x>>y;
}
inline void add(int a, int b, int z)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = z;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int lin)
{
    memset(dis, 0x3f, sizeof(dis));
    queue<int> p;
    bool flag[3005] = {0};
    dis[lin] = 0;
    p.push(lin);
    flag[lin] = 1;
    while (!p.empty())
    {
        int k = p.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] > dis[k] + v[i].v)
            {
                dis[v[i].e] = dis[k] + v[i].v;
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    p.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        p.pop();
    }
}

// Problem10286:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct node
{
    int v;
    int s, e, next;
} v[55000];
int dis[1550];
int first[2005], n, p;
inline void add(int a, int b, int z);
inline void spfa(int lin);
//inline void floyd();
inline void read();
int main()
{
    read();
    spfa(1);
    cout << dis[n] << endl;
    getchar();
    getchar();
    //while(1);
}
inline void read()
{
    p = 1;
    memset(first, -1, sizeof(first));
    int m, a, b, z, p;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b >> z;
        add(a, b, z);
        //add(b,a,z);
    }
    //cin>>x>>y;
}
inline void add(int a, int b, int z)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = z;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int lin)
{
    memset(dis, -1, sizeof(dis));
    queue<int> p;
    bool flag[1505] = {0};
    dis[lin] = 0;
    p.push(lin);
    flag[lin] = 1;
    while (!p.empty())
    {
        int k = p.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].e] < dis[k] + v[i].v)
            {
                dis[v[i].e] = dis[k] + v[i].v;
                if (!flag[v[i].e])
                {
                    flag[v[i].e] = 1;
                    p.push(v[i].e);
                }
            }
        }
        flag[k] = 0;
        p.pop();
    }
}

// Problem10287:
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
int dis[105][105];
int ans, n;
int v[105][105];
inline void floyd();
inline void read();
int main()
{
    while (cin >> n)
    {
        read();
        floyd();
        if (ans >= 0xf0f0f0f)
            cout << "No solution." << endl;
        else
            cout << ans << endl;
    }
    //getchar();
    //getchar();
    //while(1);
}
inline void read()
{
    //p=1;
    //memset(first,-1,sizeof(first));
    memset(v, 0xf, sizeof(v));
    int m, a, b, z;
    cin >> m;
    while (m--)
    {
        cin >> a >> b >> z;
        v[a][b] = z;
        v[b][a] = z;
    }
    //cin>>x>>y;
}
inline void floyd()
{
    memset(dis, 0xf, sizeof(dis));
    ans = 0x7fffffff;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (v[i][j] < 0xf0f0f0f)
                dis[i][j] = v[i][j];
    for (int i = 1; i <= n; i++)
        dis[i][i] = 0;
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= k - 1; i++)
            for (int j = i + 1; j <= k - 1; j++)
                ans = min(ans, dis[i][j] + v[j][k] + v[k][i]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
}

// Problem10288:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
// struct node{
// int v;
// int s,e,next;
// }v[1050];
int /*first[105],*/ ans, n;
bool dis[205][205] /*,p*/, v1[205][205];
inline void Init();
inline void add(int a, int b, int v);
inline void floyd();
int main()
{
    Init();
    //cout<<v1[5][11]<<endl;
    floyd();
    //cout<<dis[5][11]<<endl;
    bool flag[205];
    memset(flag, 1, sizeof(flag));
    int ans = n;
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (dis[i][i])
        {
            flag[i] = 0;
            for (int j = 1; j <= n; j++)
                if (dis[i][j] && i != j && flag[j])
                {
                    flag[j] = 0;
                    sum++;
                }
            //ans-=sum;
        }
    }
    cout << ans - sum;
}
inline void Init()
{
    int m;
    cin >> n;
    //p=1;
    int a;
    memset(v1, 0, sizeof(v1));
    //memset(first,-1,sizeof(first));
    for (int i = 1; i <= n; i++)
    {

        while (cin >> a)
        {
            if (a == 0)
                break;
            v1[i][a] = 1;
        }
        //add(a,b,c);
        //add(b,a,c);
    }
}
// inline void add(int a,int b,int z){
// v[p].s=a;
// v[p].e=b;
// v[p].v=z;
// v[p].next=first[a];
// first[a]=p++;
// }
inline void floyd()
{
    //memset(dis,0,sizeof(dis));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dis[i][j] = v1[i][j];
    //for(int i=1;i<=n;i++) dis[i][i]=1;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = dis[i][j] || (dis[i][k] && dis[k][j]);
}

// Problem10289:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
struct edge
{
    int v;
    int s, e, next;
} v[100050];
struct data
{
    int k;
    int tmp;
    bool operator<(const data &a) const
    {
        return a.k < k;
    }
};
int n, l, p, first[10050], dis[10050][25];
bool flag[10050][25] = {0};
priority_queue<data> q;
inline void Init();
inline void add(int a, int b, int c);
inline void spfa(int x);
int main()
{
    //freopen("doors.in","r",stdin);
    //freopen("doors.out","w",stdout);
    Init();
    spfa(1);
    //while(1);
}
inline void Init()
{
    int m;
    cin >> n >> m >> l;
    //scanf("%d%d%d",&n,&m,&l);
    int a, b, c;
    memset(first, -1, sizeof(first));
    p = 1;
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b >> c;
        //scanf("%d%d%d",&a,&b,&c);
        add(a, b, c);
        add(b, a, c);
    }
}
inline void add(int a, int b, int c)
{
    v[p].s = a;
    v[p].e = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
inline void spfa(int x)
{
    memset(dis, 0xf, sizeof(dis));
    //bool flag[10050][25]={0};
    ///*priority_*/queue<data> q;
    flag[x][0] = 1;
    q.push((data){x, 0});
    dis[x][0] = 0;
    while (!q.empty())
    {
        //int k=q.front().k;
        //int tmp=q.front().tmp;
        int k = q.top().k;
        int tmp = q.top().tmp;
        flag[k][tmp] = 0;
        q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[k][tmp] + v[i].v < dis[v[i].e][tmp])
            {
                dis[v[i].e][tmp] = dis[k][tmp] + v[i].v;
                if (!flag[v[i].e][tmp])
                {
                    flag[v[i].e][tmp] = 1;
                    q.push((data){v[i].e, tmp});
                }
            }
            if (dis[v[i].e][tmp + 1] > dis[k][tmp] && tmp + 1 <= l)
            {
                dis[v[i].e][tmp + 1] = dis[k][tmp];
                if (!flag[v[i].e][tmp + 1])
                {
                    flag[v[i].e][tmp + 1] = 1;
                    q.push((data){v[i].e, tmp + 1});
                }
            }
        }
    }
    int minn = 0x7fffffff;
    //cout<<dis[n][1]<<endl;
    for (int i = 1; i <= l; i++)
    {
        minn = min(minn, dis[n][i]);
    }
    cout << minn << endl;
}

// Problem10291:
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
struct edge
{
    int END;
    int v, next;
} v[30005];
int first[10005], dis[10005];
int times[10005];
int p, n, m;
bool spfa(int a);
void add(int a, int b, int c);
int main()
{
    //cin>>n>>m;
    //freopen("test.in","r",stdin);
    //freopen("test.out","w",stdout);
    scanf("%d%d", &n, &m);
    int a, b, c, d;
    p = 1;
    memset(first, -1, sizeof(first));
    while (m--)
    {
        //cin>>a;
        scanf("%d", &a);
        if (a == 3)
        {
            //cin>>b>>c;
            scanf("%d%d", &b, &c);
            add(b, c, 0);
            add(c, b, 0);
        }
        if (a == 2)
        {
            scanf("%d%d%d", &b, &c, &d);
            //cin>>b>>c>>d;
            add(b, c, -d);
        }
        if (a == 1)
        {
            scanf("%d%d%d", &b, &c, &d);
            //cin>>b>>c>>d;
            add(c, b, d);
        }
    }
    for (int i = 1; i <= n; i++)
        add(0, i, 0);
    if (spfa(0))
        puts("No\n");
    else
        puts("Yes\n");
}
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
bool spfa(int a)
{
    memset(dis, 0x3f, sizeof(dis));
    //memset(times,0,sizeof(times));
    queue<int> q;
    bool flag[10005] = {0};
    flag[a] = 1;
    dis[a] = 0;
    times[a]++;
    q.push(a);
    while (!q.empty())
    {
        int k = q.front();
        flag[k] = 0;
        q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > dis[k] + v[i].v)
            {
                if (flag[v[i].END])
                    return 1;
                dis[v[i].END] = dis[k] + v[i].v;
                //if(!flag[v[i].END]){
                flag[v[i].END] = 1;
                //times[v[i].END]++;
                //	if(times[v[i].END]>n+1) return 1;
                q.push(v[i].END);
                //}
            }
        }
    }
    return 0;
}

// Problem10292:
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
int a[105][105];
int ru_du[105];
int main()
{
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        while (1)
        {
            cin >> m;
            if (m == 0)
                break;
            a[i][m] = 1;
            ru_du[m]++;
        }
    }
    priority_queue<int, vector<int>, greater<int>> p;
    for (int i = 1; i <= n; i++)
    {
        if (ru_du[i] == 0)
            p.push(i);
    }
    while (!p.empty())
    {
        int tmp = p.top();
        cout << tmp << " ";
        p.pop();
        for (int i = 1; i <= n; i++)
        {
            if (a[tmp][i])
            {
                ru_du[i]--;
                if (ru_du[i] == 0)
                    p.push(i);
            }
        }
    }
    //while(1);
}

// Problem10293:
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
struct edge
{
    int START, END, next;
    bool v;
} v[20005];
int first[10005], p;
int ru_du[10005];
int my[10005];
void add(int a, int b)
{
    v[p].START = a;
    v[p].END = b;
    v[p].v = 1;
    v[p].next = first[a];
    first[a] = p++;
}
int main()
{
    int n, m;
    cin >> n >> m;
    int a, b;
    p = 1;
    int sum = 0;
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b;
        add(b, a);
        //my[b]=100;
        ru_du[a]++;
        //sum+=ru_du[b];
    }
    for (int i = 1; i <= n; i++)
        my[i] = 100;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (ru_du[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int tmp = q.front();
        sum += my[tmp];
        q.pop();
        for (int i = first[tmp]; i != -1; i = v[i].next)
        {
            ru_du[v[i].END]--;
            if (ru_du[v[i].END] == 0)
            {
                //sum++;
                my[v[i].END] = my[tmp] + 1;
                q.push(v[i].END);
            }
        }
    }
    int t = 0;
    for (int i = 1; i <= n; i++)
        if (ru_du[i] > 0)
            t++;
    if (t)
        cout << "Poor Xed" << endl;
    else
        cout << sum << endl;
    //while(1);
}

// Problem10294:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define LL long long
using namespace std;
LL v[305][305];
//int father[305];
LL w[305], minn[305];
bool INTREE[305];
//int find(int x);
//bool allcheck(int a);
//void merge(int a,int b);
int main()
{
    int n, m;
    cin >> n;
    int a, b, c, u;
    LL p = 1, sum = 0;
    int minw = 0x7fffffff;
    //for(int i=1;i<=n;i++) father[i]=i;
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
        if (w[i] < minw)
        {
            minw = w[i];
            u = i;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a;
            v[i][j] = a;
        }
    }
    sum += minw;
    memset(minn, 0x7f, sizeof(minn));
    minn[u] = 0;
    for (int i = 1; i <= n; i++)
    {
        int k = 0;
        for (int j = 1; j <= n; j++)
        {
            if (!INTREE[j] && (minn[j] < minn[k]))
            {
                k = j;
            }
        }
        INTREE[k] = 1;
        sum += min(minn[k], w[k]);
        for (int j = 1; j <= n; j++)
        {
            if (!INTREE[j] && (v[k][j] < minn[j]))
            {
                minn[j] = min(v[k][j], w[j]);
            }
        }
    }
    //sum+=*min_element(w+1,w+n+1);
    //int s=0,k=0;
    //int maxn=-1;
    //sum+=min_element()
    //sort(v+1,v+p);
    //for(int i=1;i<=n;i++) father[i]=i;
    // for(int i=1;i<p;i++){
    // int x=v[i].STRAT,y=v[i].END;
    // //if(allcheck(n))break;
    // if(find(x)!=find(y)){
    // father[find(y)]=find(x);
    // //ans+=v[i].v;
    // if(v[i].v<w[v[i].END])sum+=v[i].v;
    // else {sum+=w[v[i].END];s++;}
    // k++;
    // }
    // if(k==n)break;
    // }
    // if(s==0) sum+=*min_element(w+1,w+n+1);
    cout << sum << endl;
}
//int find(int x){
//	if(x!=father[x]) father[x]=find(father[x]);
//	return father[x];
//}
//bool allcheck(int a){
//	int t=0;
//	for(int i=1;i<=a;i++){
//		if(father[i]==i)t++;
//		if(t>1) return 0;
//	}
//	//if(t>1) return 0;
//	if(t==1) return 1;
//}
//void merge(int a,int b){
//	int x=find(a);
//	int y=find(b);
//	if(x!=y) father[y]=x;
//}

// Problem10299:
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
struct data
{
    int tmp, my;
    bool operator<(const data &a) const
    {
        return a.my < my;
    }
};
int b[1005];
bool b1[1005];
bool d[1005][1005];
int ru_du[1005];
int main()
{
    int n, m, a, c;
    scanf("%d%d", &n, &m);
    //cin>>n>>m;
    for (int i = 1; i <= m; i++)
    {
        //cin>>a;
        scanf("%d", &a);
        //memset(b,0,sizeof(b));
        memset(b1, 0, sizeof(b1));
        int first = 0, END;
        for (int j = 1; j <= a; j++)
        {
            //cin>>c;
            scanf("%d", &c);
            //if(!first) first=c;
            b1[c] = 1;
            b[j] = c;
            //END=c;
        }
        for (int j = b[1]; j <= b[a]; j++)
            if (!b1[j])
                for (int k = 1; k <= a; k++)
                    if (!d[j][b[k]])
                    {
                        d[j][b[k]] = 1;
                        ru_du[b[k]]++;
                    }
    }
    //for(int i=1;i<=n;i++) cout<<ru_du[i]<<endl;
    //cout<<ru_du[5]<<endl;
    //while(1);
    int sum = 0;
    priority_queue<data> q;
    //int my[1005];
    //memset(my,0,sizeof(my));
    //for(int i=1;i<=n;i++) [i]=1;
    for (int i = 1; i <= n; i++)
    {
        if (ru_du[i] == 0)
            q.push((data){i, 1});
    }
    while (!q.empty())
    {
        data s = q.top();
        data s1;
        q.pop();
        for (int i = 1; i <= n; i++)
        {
            if (d[s.tmp][i])
            {
                ru_du[i]--;
                sum = max(sum, s.my);
                s1.my = s.my + 1;
                if (ru_du[i] == 0)
                {
                    s1.tmp = i;
                    q.push(s1);
                }
            }
        }
    }
    cout << sum + 1 << endl;
    //while(1);
}

// Problem10301:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstring>
using namespace std;
int N;
int c[100010], a[100010];
inline int lowbit(int x) { return x & (-x); }
void update(int x, int num)
{
    for (int i = x; i <= N; i += lowbit(i))
        c[i] += num;
}
int sum(int x)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        sum += c[i];
    return sum;
}
int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &a[i]); /*update(i,a[i]);*/
    }
    int m;
    scanf("%d", &m);
    string s;
    int ai, aj, d;
    for (int i = 1; i <= m; i++)
    {
        cin >> s;
        if (s == "QUERY")
        {
            scanf("%d", &ai);
            printf("%d\n", sum(ai) + a[ai]);
        }
        if (s == "ADD")
        {
            scanf("%d%d%d", &ai, &aj, &d);
            update(ai, d);
            update(aj + 1, -d);
        }
    }
}

// Problem10302:
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n;
int c[100010], a[100010];
inline int lowbit(int x) { return x & (-x); }
void updata(int x, int num)
{
    for (int i = x; i <= n; i += lowbit(i))
        c[i] ^= num;
}
int sum(int x)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        sum ^= c[i];
    return sum;
}
inline int sum(int x1, int x2) { return sum(x2) ^ sum(x1 - 1); }
int main()
{
    int m;
    cin >> n >> m;
    int x, l, r;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        updata(i, a[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &x, &l, &r);
        if (x == 0)
        {
            updata(l, r ^ a[l]);
            a[l] = r;
        }
        if (x == 1)
        {
            cout << sum(l, r) << endl;
        }
    }
}

// Problem10303:
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
#define LL long long
using namespace std;
int max(int a, int b) { return a > b ? a : b; }
struct number
{
    vector<LL> so;
    number() { ; }
    number(const int a) { *this = a; }
    number operator=(const int &a)
    {
        LL y = a / 1000000000;
        LL s = a % 1000000000;
        if (y != 0)
            so.push_back(y);
        so.push_back(s);
        return *this;
    }
    number operator+(const number &b)
    {
        number a = b;
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        int y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 1000000000;
            s = s % 1000000000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator+(const int &b)
    {
        number a;
        int y = b / 1000000000;
        int s = b % 1000000000;
        a.so.push_back(s);
        a.so.push_back(y);
        if (so.size() > a.so.size())
        {
            for (int i = a.so.size(); i < so.size(); i++)
                a.so.push_back(0);
        }
        else
            for (int i = so.size(); i < a.so.size(); i++)
                so.push_back(0);
        y = 0;
        number c;
        for (int i = 0; i < max(so.size(), a.so.size()); i++)
        {
            int s = so[i] + a.so[i] + y;
            y = s / 1000000000;
            s = s % 1000000000;
            c.so.push_back(s);
        }
        if (y != 0)
            c.so.push_back(y);
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator+=(const number &a)
    {
        *this = *this + a;
        return *this;
    }
    number operator+=(const int &a)
    {
        *this = *this + a;
        return *this;
    }
    number operator*(const int &a)
    {
        number b = a;
        return *this * b;
    }
    number operator*=(const int &a)
    {
        *this = *this * a;
        return *this;
    }
    number operator*(const number &a)
    {
        number c;
        for (int i = 0; i < a.so.size() + so.size() + 1; i++)
            c.so.push_back(0);
        for (int i = 0; i < so.size(); i++)
        {
            int y = 0;
            for (int j = 0; j < a.so.size(); j++)
            {
                c.so[i + j] += so[i] * a.so[j] + y;
                y = c.so[i + j] / 1000000000;
                c.so[i + j] %= 1000000000;
            }
            c.so[i + a.so.size()] = y;
        }
        while (c.so[c.so.size() - 1] == 0 && c.so.size() > 1)
        {
            c.so.pop_back();
        }
        return c;
    }
    number operator*=(const number &a)
    {
        *this = *this * a;
        return *this;
    }
    bool operator>(const number &a) const
    {
        if (so.size() > a.so.size())
            return 1;
        if (so.size() < a.so.size())
            return 0;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 0;
            }
            if (so[i] > a.so[i])
            {
                return 1;
            }
        }
        return 0;
    }
    bool operator<(const number &a) const
    {
        if (so.size() > a.so.size())
            return 0;
        if (so.size() < a.so.size())
            return 1;
        for (int i = so.size() - 1; i >= 0; i--)
        {
            if (so[i] < a.so[i])
            {
                return 1;
            }
            if (so[i] > a.so[i])
            {
                return 0;
            }
        }
        return 0;
    }
    bool operator==(const number &a) const { return (!(a < *this)) && (!(a > *this)); }
    bool operator>=(const number &a) const { return !(a > *this); }
    bool operator<=(const number &a) const { return !(a < *this); }
    bool operator!=(const number &a) const { return (a > *this) || (a < *this); }
};
void read(number &a)
{
    string s;
    cin >> s;
    int sum = 0, su = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += (s[i] - '0') * su;
        su *= 10;
        if (su == 1000000000)
        {
            a.so.push_back(sum);
            sum = 0;
            su = 1;
        }
    }
    if (sum != 0 || a.so.size() == 0)
    {
        a.so.push_back(sum);
    }
}
void print(number a)
{
    //if(fu) printf("-");
    printf("%d", a.so[a.so.size() - 1]);
    for (int i = a.so.size() - 2; i >= 0; i--)
        printf("%09d", a.so[i]);
    printf("\n");
}
string s;
int k, a[11][11], c, n;
int b[40];
bool d[11] = {0};
int sum = 0;
void dfs(int i)
{
    for (int j = 1; j <= 10; j++)
    {
        if (a[i][j] && !d[j])
        {
            d[j] = 1;
            dfs(j);
            sum++;
        }
    }
}
int main()
{
    //freopen("build.in","r",stdin);
    //freopen("build.out","w",stdout);
    cin >> s >> k;
    for (int i = 1; i <= k; i++)
    {
        cin >> c >> n;
        a[c][n] = 1;
    }
    for (int i = 0; i < s.size(); i++)
    {
        memset(d, 0, sizeof(d));
        sum = 1;
        d[s[i] - '0'] = 1;
        dfs(s[i] - '0');
        b[i] = sum;
    }
    number h = b[0];
    for (int i = 1; i < s.size(); i++)
    {
        h *= b[i];
    }
    print(h);
}
// Problem10304:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
int main()
{
//#define lon
#ifdef lon
    freopen("escape.in", "r", stdin);
    freopen("escape.out", "w", stdout);
#endif // lon
    int m, s, t;
    cin >> m >> s >> t;
    int s1 = s, t1 = t;
    while (m >= 10 && s > 0 && t > 0)
    {
        if (s >= 17)
        {
            t--;
            s -= 60;
            m -= 10;
        }
        else
        {
            cout << "Yes\n"
                 << t - t1 + 1;
        }
    }
    while (s > 0 && t > 0)
    {
        if (m >= 2 && m <= 5 && t > 2 && s > 17)
        {
            t -= 3;
            m = m + 8 - 10;
            s -= 60;
            continue;
        }
        if (m >= 6 && t > 1 && s > 17)
        {
            t -= 2;
            m = m + 4 - 10;
            s -= 60;
            continue;
        }
        if (m < 2 && t >= 7 && s > 102)
        {
            t -= 7;
            s -= 120;
            continue;
        }
        else
        {
            s -= 17;
            t--;
        }
    }
    if (s > 0)
    {
        cout << "No\n"
             << s1 - s << endl;
        goto end;
    }
    if (t >= 0)
    {
        cout << "Yes\n"
             << t1 - t << endl;
        goto end;
    }

end:;
#ifdef lon
    while (1)
#endif // lon
        return 0;
}

// Problem10305:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
using namespace std;
struct data
{
    int a, b;
    bool operator<(const data &s) const
    {
        return s.a < a;
        //return s.b<b;
    }
    bool operator>(const data &s) const
    {
        return s.b < b;
    }
};
priority_queue<int, vector<int>, greater<int>> a;
priority_queue<data, vector<data>, greater<data>> c;
priority_queue<data> b;
int main()
{
    int n, m, p, t, l;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p);
        a.push(p);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &t, &l);
        b.push((data){t, l});
    }
    int k, sum = 0;
    while (!a.empty())
    {
        while (!b.empty())
        {
            if (a.top() < b.top().a)
                break;
            if (a.top() >= b.top().a)
            {
                c.push(b.top());
                b.pop();
            }
        }
        while (!c.empty())
        {
            if (a.top() <= c.top().b)
            {
                c.pop();
                sum++;
                break;
            }
            if (a.top() > c.top().a)
            {
                c.pop();
                continue;
            }
        }
        a.pop();
    }
    cout << sum;
    getchar();
    getchar();
}

// Problem10306:
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n;
int c[1050][1050];
inline int lowbit(int x) { return x & (-x); }
void update(int x, int y, int num)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            c[i][j] += num;
}
int sum(int x, int y)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            sum += c[i][j];
    return sum;
}
inline int sum(int x1, int y1, int x2, int y2) { return sum(x2 + 1, y2 + 1) + sum(x1, y1) - sum(x1, y2 + 1) - sum(x2 + 1, y1); }
int main()
{
    //freopen("mobilephones.in","r",stdin);
    //freopen("mobilephones.out","w",stdout);
    int Q;
    int x, y, l, b, r, t, A;
    //cin>>Q>>n;
    scanf("%d%d", &Q, &n);
    n++;
    while (scanf("%d", &Q) == 1)
    {
        if (Q == 3)
            break;
        if (Q == 1)
        {
            scanf("%d%d%d", &x, &y, &A);
            update(x + 1, y + 1, A);
            continue;
        }
        if (Q == 2)
        {
            scanf("%d%d%d%d", &l, &b, &r, &t);
            printf("%d\n", sum(l, b, r, t));
        }
    }
}
// Problem10307:
#include <iostream>
#include <cstring>
#include <cstdio>
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
using namespace std;
const int N = 100005;
int minn[N << 2];
void Pushup(int rt)
{
    minn[rt] = min(minn[rt << 1], minn[rt << 1 | 1]);
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        scanf("%d", &minn[rt]);
        return;
    }
    int m = (l + r) >> 1;
    buildtree(lch);
    buildtree(rch);
    Pushup(rt);
}
int min(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return minn[rt];
    int m = (l + r) >> 1;
    int ret = 0x7fffffff;
    if (L <= m)
        ret = min(ret, min(L, R, lch));
    if (R > m)
        ret = min(ret, min(L, R, rch));
    return ret;
}
int main()
{
    //freopen("faithful.in","r",stdin);
    //freopen("faithful.out","w",stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    buildtree(1, n, 1);
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        printf("%d ", min(a, b, 1, n, 1));
    }
    //while(1);
}

// Problem10308:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
//int comp(const int &a,const int &b)
//{
//    return a>b;
//}
int main()
{
    vector<int> s;
    int n, a, b, s1;
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &s1);
        s.push_back(s1);
    }
    sort(s.begin(), s.end());
    //cout<<s[0];
    int i = a, k;
    vector<int>::iterator it = s.begin(), it2, it1;
    while (s.size())
    {
        k = *(s.end() - 1) - b;
        it2 = upper_bound(it, s.end() - 1, k);
        it1 = s.end() - 1;
        while (it1 != it2)
        {
            *it1 = *(it1 - 1);
            it1--;
        }
        *it2 = k;
        it = upper_bound(it, s.end(), i);
        if (it == s.end())
            break;
        //sort(it+1,s.end());
        i += a;
    }
    cout << i / a;
}

// Problem10309:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 100;
struct Matrix
{
    int x, y;
    int a[MAXN][MAXN];
    Matrix()
    {
        memset(a, 0, sizeof(a));
        x = 0;
        y = 0;
    }
    void Init(int b[MAXN][MAXN], int m, int n)
    {
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = b[i][j];
        x = m, y = n;
    }

    Matrix operator*(const Matrix &h)
    {
        //try
        //              {
        //                   if(y!=b.x) throw 1;
        //              }
        //              catch(int i)
        //              {
        //                   exit(0);
        //              }
        //cout<<"1";
        //while(1);
        Matrix c;
        //int c[x+1][h.y+1];
        c.x = x, c.y = h.y;
        for (int i = 1; i <= c.x; i++)
            for (int j = 1; j <= c.y; j++)
            {
                for (int k = 1; k <= y; k++)
                    c.a[i][j] += (a[i][k] * h.a[k][j]) % 10000;
                c.a[i][j] %= 10000;
            }
        return c;
    }
};
ostream &operator<<(ostream &out, const Matrix &b)
{
    for (int i = 1; i <= b.x; i++)
    {
        for (int j = 1; j <= b.y; j++)
            cout << b.a[i][j] << " ";
        cout << '\n';
    }
    return out;
}
int f(int p)
{
    int c[MAXN][MAXN];
    int d[MAXN][MAXN];
    Matrix a, b, ans;
    c[1][1] = 1;
    c[1][2] = 1;
    c[2][1] = 1;
    c[2][2] = 0;
    d[1][1] = 0;
    d[2][1] = 1;
    a.Init(c, 2, 2);
    b.Init(d, 2, 1);
    //cout<<"11 ";
    ans.x = 2;
    ans.y = 2;
    ans.a[1][1] = 1;
    ans.a[2][2] = 1;
    while (p)
    {
        if (p & 1)
            ans = ans * a;
        p = p >> 1;
        a = a * a;
    }
    //cout<<ans<<endl;
    a = ans * b;
    return a.a[1][1];
}
int main()
{
    int p;
    while (cin >> p)
    {
        if (p == -1)
            break;
        cout << f(p) << endl;
    }

    //while(1);
}

// Problem10313:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const long long MAXN = 100;
long long mod = 100000000;
struct Matrix
{
    long long x, y;
    long long a[MAXN][MAXN];
    Matrix()
    {
        memset(a, 0, sizeof(a));
        //for(long long i=1;i<100;i++) a[i][i]=1;
        x = 0;
        y = 0;
    }
    void Init(long long b[MAXN][MAXN], long long m, long long n)
    {
        for (long long i = 1; i <= m; i++)
            for (long long j = 1; j <= n; j++)
                a[i][j] = b[i][j];
        x = m, y = n;
    }

    Matrix operator*(const Matrix &h)
    {
        try
        {
            if (y != h.x)
                throw 1;
        }
        catch (int i)
        {
            exit(0);
        }
        //cout<<"1";
        //while(1);
        Matrix c;
        //long long c[x+1][h.y+1];
        c.x = x, c.y = h.y;
        //cout<<mod<<endl;
        for (long long i = 1; i <= c.x; i++)
            for (long long j = 1; j <= c.y; j++)
            {
                for (long long k = 1; k <= y; k++)
                    c.a[i][j] += (a[i][k] * h.a[k][j]) % mod;
                c.a[i][j] %= mod;
            }
        return c;
    }
};
ostream &operator<<(ostream &out, const Matrix &b)
{
    for (long long i = 1; i <= b.x; i++)
    {
        for (long long j = 1; j <= b.y; j++)
            cout << b.a[i][j] << " ";
        cout << '\n';
    }
    return out;
}
int main()
{
    //freopen("recurrences1.in","r",stdin);
    //freopen("recurrences1.txt","w",stdout);
    long long d, n, m;
    while (cin >> d >> n >> mod)
    {
        if (d == n && d == mod && d == 0)
            break;
        Matrix a, b, ans;
        long long c[MAXN][MAXN];
        long long f[MAXN][MAXN];
        for (long long i = 1; i <= d; i++)
        {
            cin >> c[1][i];
            c[1][i] %= mod;
        }
        for (long long i = d; i >= 1; i--)
        {
            cin >> f[i][1];
            f[i][1] %= mod;
        }
        for (long long i = 2; i <= d; i++)
        {
            c[i][i - 1] = 1;
        }
        a.Init(c, d, d);
        //cout<<a;
        b.Init(f, d, 1);
        //cout<<b;
        ans.x = d;
        ans.y = d;
        for (long long i = 1; i < 100; i++)
            ans.a[i][i] = 1;
        n -= d;
        //n++;
        while (n)
        {
            if (n & 1)
                ans = ans * a;
            n = n >> 1;
            a = a * a;
        }
        //cout<<a;
        a = ans * b;
        //cout<<ans;
        //cout<<a;
        cout << a.a[1][1] % mod << endl;
    }

    //while(1);
}

// Problem10319:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cmath>
using namespace std;
struct edge
{
    int START, END;
    double v;
    bool operator<(const edge &a) const
    {
        return v < a.v;
    }
} v[2000005];
struct point
{
    int x, y;
} Point[1005];
int father[1005];
int LONG[505], p, n;
int find(int a);
bool allcheck();
void add(int a, int b, double c);
double my_long(point a, point b);
int merge(int a, int b);
int main()
{
    //freopen("monkey.in","r",stdin);
    //freopen("monkey.out","w",stdout);
    int m;
    p = 1;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", LONG + i);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &Point[i].x, &Point[i].y);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            add(i, j, my_long(Point[i], Point[j]));
    for (int i = 1; i <= n; i++)
        father[i] = i;
    sort(v + 1, v + n * n + 1);
    sort(LONG + 1, LONG + m + 1);
    double Max_long;
    memset(&Max_long, 127, sizeof(Max_long));
    for (int i = 1; i <= n * n; i++)
    {
        merge(v[i].START, v[i].END);
        if (allcheck())
        {
            Max_long = v[i].v;
            break;
        }
    }
    //cout<<Max_long<<endl;
    //while(1);
    int x = lower_bound(LONG + 1, LONG + m + 1, Max_long) - LONG;
    cout << m - x + 1 << endl;
    //cout<<clock()<<endl;
    //while(1);
}
double my_long(point a, point b)
{
    return sqrt(pow((double)a.x - b.x, 2) + pow((double)a.y - b.y, 2));
}
bool allcheck()
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (father[i] == i)
            sum++;
        if (sum > 1)
            return 0;
    }
    if (sum == 1)
        return 1;
}
void add(int a, int b, double c)
{
    v[p].START = a;
    v[p].END = b;
    v[p++].v = c;
}
int merge(int a, int b)
{
    int x = find(a);
    int y = find(b);
    if (x != y)
        father[y] = x;
}
int find(int a)
{
    if (a != father[a])
        father[a] = find(father[a]);
    return father[a];
}

// Problem10320:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <queue>
#include <cmath>
using namespace std;
struct edge
{
    int END, v, next;
} v[1000005];
int first[100005], dis[100005];
int n, m, p;
int M[100005];
void spfa(int a);
void add(int a, int b, int c);
int main()
{
    //freopen("trade.in","r",stdin);
    //freopen("trade.out","w",stdout);
    scanf("%d%d", &n, &m);
    memset(first, -1, sizeof(first));
    p = 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &M[i]);
    int x, y, z;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        if (z == 1)
            add(x, y, M[y] - M[x]);
        else
        {
            add(x, y, M[y] - M[x]);
            add(y, x, M[x] - M[y]);
        }
    }
    spfa(1);
    cout << dis[n] << endl;
    //while(1);
}
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
void spfa(int a)
{
    memset(dis, 0xaf, sizeof(dis));
    bool flag[100005] = {0};
    queue<int> q;
    flag[a] = 1;
    dis[a] = 0;
    q.push(a);
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        flag[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] < max(v[i].v, dis[k]))
            {
                dis[v[i].END] = max(v[i].v, dis[k]);
                if (!flag[v[i].END])
                {
                    flag[v[i].END] = 1;
                    q.push(v[i].END);
                }
            }
        }
    }
}

// Problem10321:
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <queue>
#include <cmath>
using namespace std;
int v[105][105];
int dis[105][105];
int first[105], P, n;
void add(int a, int b, int c);
void dfs(int a);
vector<int> xian, ans;
int ansn = 0x7fffffff;
bool flag[105] = {0};
int main()
{
    //freopen("djsc.in","r",stdin);
    //freopen("djsc.out","w",stdout);
    int m, a, b, c;
    memset(dis, 0x3f, sizeof(dis));
    scanf("%d%d%d", &n, &m, &P);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        v[a][b] = c;
        v[b][a] = c;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (v[i][j])
                dis[i][j] = v[i][j];
    for (int i = 0; i < n; i++)
        dis[i][i] = 0;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    //cout<<dis[0][2]<<endl;
    dfs(0);
    for (int i = 0; i < P; i++)
        cout << ans[i] << " ";
}
void dfs(int a)
{
    if (a == P)
    {
        int maxn = 0x80000000;
        for (int i = 0; i < n; i++)
        {
            int minn = 0x7fffffff;
            for (int j = 0; j < P; j++)
            {
                minn = min(minn, dis[xian[j]][i]);
            }
            maxn = max(maxn, minn);
        }
        if (maxn < ansn)
        {
            ansn = maxn;
            ans = xian;
        }
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (!flag[i])
        {
            flag[i] = 1;
            xian.push_back(i);
            dfs(a + 1);
            flag[i] = 0;
            xian.pop_back();
        }
    }
}

// Problem10322:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
struct data
{
    int v, i;
};
deque<data> s;
vector<int> a;
int len = 0;
int main()
{
    int n, b, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &b);
        a.push_back(b);
    }
    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && a[i] < s.back().v)
            s.pop_back();
        s.push_back((data){a[i], i});
        while (s.begin()->i < i - k + 1)
            s.pop_front();
        if (i >= k - 1)
            printf("%d ", s.begin()->v);
    }
    puts("");
    s.clear();
    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && a[i] > s.back().v)
            s.pop_back();
        s.push_back((data){a[i], i});
        while (s.begin()->i < i - k + 1)
            s.pop_front();
        if (i >= k - 1)
            printf("%d ", s.begin()->v);
    }
    //while(1);
}

// Problem10323:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define LL long long
using namespace std;
struct data
{
    int v, i;
} k;
vector<LL> a;
int l[100002], r[100002];
deque<data> s;
int main()
{
    int n, b;
    scanf("%d", &n);
    LL maxn = 0;
    for (int i = 1; i <= n; i++)
        l[i] = r[i] = i;
    a.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &b);
        a.push_back(b);
    }
    for (int i = 1; i <= n; i++)
    {
        k = (data){a[i], i};
        while (!s.empty() && a[i] <= (s.end() - 1)->v)
        {
            k = s.back();
            s.pop_back();
        }
        l[i] = l[k.i];
        s.push_back((data){a[i], i});
    }
    s.clear();
    for (int i = n; i >= 1; i--)
    {
        k = (data){a[i], i};
        while (!s.empty() && a[i] <= (s.end() - 1)->v)
        {
            k = s.back();
            s.pop_back();
        }
        r[i] = r[k.i];
        s.push_back((data){a[i], i});
    }
    LL sum;
    vector<LL> c = a;
    for (int i = 1; i <= n; i++)
        c[i] += c[i - 1];
    for (int i = 1; i <= n; i++)
    {
        sum = 0;
        maxn = max(maxn, (LL)a[i] * (c[r[i]] - c[l[i] - 1]));
    }
    cout << maxn << endl;
}

// Problem10324:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define FOR(i, s, e) for (int i = (s); i <= (e); i++)
using namespace std;
int min(int a, int b, int c, int d)
{
    int s[4] = {a, b, c, d};
    return *min_element(s, s + 4);
}
int min(int a, int b, int c, int d, int e, int f)
{
    int s[6] = {a, b, c, d, e, f};
    return *min_element(s, s + 6);
}
int f[1005][1005];
int a[1005][1005];
int main()
{
    int n;
    cin >> n;
    FOR(i, 1, n)
        FOR(j, 1, i) cin >> a[i][j];
    memset(f, 0x3f, sizeof(f));
    f[n][1] = a[n][1];
    for (int i = n; i >= 1; i--)
    {
        int flag = 0;
        for (int j = 1; j <= i; j++)
        {
            if (j != 1 && j != i)
            {
                int s = min(f[i][j - 1], f[i][j + 1], f[i + 1][j], f[i + 1][j + 1]) + a[i][j];
                if (f[i][j] > s)
                {
                    f[i][j] = s;
                    flag = 1;
                }
            }
            if (j == 1 && i != 1)
            {
                int s = min(f[i + 1][i + 1], f[i][i], f[i][j + 1], f[i][j - 1], f[i + 1][j], f[i + 1][j + 1]) + a[i][j];
                if (f[i][j] > s)
                {
                    f[i][j] = s;
                    flag = 1;
                }
            }
            if (j == i)
            {
                int s = min(f[i][1], f[i + 1][1], f[i][j - 1], f[i][j + 1], f[i + 1][j], f[i + 1][j + 1]) + a[i][j];
                if (f[i][j] > s)
                {
                    f[i][j] = s;
                    flag = 1;
                }
            }
        }
        if (flag == 1)
            i++;
    }
    cout << f[1][1];
}

// Problem10326:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[205];
int w[35], c[35], s[35];
int n, V, maxl;
void ZOPack(int cost, int weight);
void CPack(int cost, int weight);
int main()
{

    cin >> V >> n;
    for (int i = 1; i <= n; i++)
        cin >> c[i] >> w[i] >> s[i];
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 0)
        {
            CPack(c[i], w[i]);
        }
        else
        {
            int k = 1;
            while (k < s[i])
            {
                ZOPack(k * c[i], k * w[i]);
                s[i] = s[i] - k;
                k *= 2;
            }
            ZOPack(s[i] * c[i], s[i] * w[i]);
        }
    }
    cout << f[V] << endl;
    //while(1);
}
void ZOPack(int cost, int weight)
{
    for (int v = V; v >= cost; v--)
        f[v] = max(f[v], f[v - cost] + weight);
}
void CPack(int cost, int weight)
{
    for (int v = cost; v <= V; v++)
        f[v] = max(f[v], f[v - cost] + weight);
}

// Problem10328:
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
int a[3000];
int f[3000];
bool g[3000][3000];
int abs(int i)
{
    return i < 0 ? -i : i;
}
int main()
{
    int n, d;
    int s1 = 0, t = 0, e1, s2 = 0, e2;
    char c;
    cin >> n >> d;
    for (int i = 1; i <= n; i++)
    {
        cin >> c;
        if (c == 'H')
            a[i] = 1;
        else
            a[i] = -1;
        a[i] += a[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        f[i] = i;
        for (int j = 0; j <= i; j++)
        {
            if ((abs(a[i] - a[j]) <= d || abs(a[i] - a[j]) == i - j))
                f[i] = min(f[i], f[j] + 1);
        }
    }

    cout << f[n] << endl;
    //while(1);
}
// Problem10329:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
int f[5005][5005];
int main()
{
    //freopen("palin.in","r",stdin);
    //freopen("palin.out","w",stdout);
    int n;
    string s;
    cin >> n;
    cin >> s;
    for (int l = 2; l <= n; l++)
    {
        for (int i = 0; i < n - l + 1; i++)
        {
            f[i][i + l - 1] = min(f[i + 1][i + l - 1], f[i][i + l - 2]) + 1;
            if (s[i] == s[i + l - 1])
                f[i][i + l - 1] = min(f[i][i + l - 1], f[i + 1][i + l - 2]);
        }
    }
    //for(int i=0;i<n;i++){
    //		for(int j=0;j<i;j++)cout<<"  ";
    //		for(int j=i;j<n;j++)
    //			cout<<f[i][j]<<" ";
    //		cout<<endl;
    //	}
    cout << f[0][n - 1] << endl;
    //while(1);
}

// Problem10332:
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int max(int a, int b, int c, int d)
{
    int s[4] = {a, b, c, d};
    return *max_element(s, s + 4);
}
int a[21][21];
int f[21][21][21];
int main()
{
    int n, x, y, s;
    cin >> n;
    while (1)
    {
        cin >> x >> y >> s;
        if (x == 0 && y == 0 && s == 0)
            break;
        a[x][y] = s;
    }
    f[1][0][0] = a[0][0];
    for (int k = 1; k <= 2 * n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j || (k == 2 * n && j == n && i == n))
                {
                    f[k][i][j] = max(f[k - 1][i][j], f[k - 1][i - 1][j], f[k - 1][i][j - 1], f[k - 1][i - 1][j - 1]) + a[i][k - i] + a[j][k - j];
                }
            }
        }
    }
    cout << f[2 * n][n][n] - a[n][n] << endl;
    //while(1);
}

// Problem10333:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
struct data
{
    int w, p;
};
int a[70], f[32500], p[70], q[70];
int main()
{
    //freopen("budget.in","r",stdin);
    //freopen("budget.out","w",stdout);
    int n, V;
    vector<int> s[70], zhu;
    vector<data> c[70];
    cin >> V >> n;
    zhu.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> p[i] >> q[i];
        if (q[i] == 0)
            zhu.push_back(i);
        else
            s[q[i]].push_back(i);
    }
    for (int i = 1; i < zhu.size(); i++)
    {
        c[zhu[i]].push_back((data){a[zhu[i]], a[zhu[i]] * p[zhu[i]]});
        for (int j = 0; j < s[zhu[i]].size(); j++)
        {
            c[zhu[i]].push_back((data){a[zhu[i]] + a[s[zhu[i]][j]], a[zhu[i]] * p[zhu[i]] + a[s[zhu[i]][j]] * p[s[zhu[i]][j]]});
        }
        if (s[zhu[i]].size() == 2)
        {
            c[zhu[i]].push_back((data){a[zhu[i]] + a[s[zhu[i]][0]] + a[s[zhu[i]][1]], a[zhu[i]] * p[zhu[i]] + a[s[zhu[i]][0]] * p[s[zhu[i]][0]] + a[s[zhu[i]][1]] * p[s[zhu[i]][1]]});
        }
    }
    for (int i = 1; i < zhu.size(); i++)
    {
        for (int v = V; v >= 0; v--)
        {
            for (int j = 0; j < c[zhu[i]].size(); j++)
            {
                if (v >= c[zhu[i]][j].w)
                    f[v] = max(f[v], f[v - c[zhu[i]][j].w] + c[zhu[i]][j].p);
            }
        }
    }
    cout << f[V] << endl;
    //while(1);
}

// Problem10334:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 10005;
struct node
{
    int root;
    int ch[2];
} tree[N * 2];
int f[N][4]; //1:red,2:green,3:blue;
int q[N][4];
int p = 2;
int buildtree(int x)
{
    char c;
    c = getchar();
    while (c < '0' || c > '2')
        c = getchar();
    if (c >= '0' && c <= '2')
    {
        if (c == '0')
        {
            return 0;
        }
        if (c == '1')
        {
            tree[x].ch[0] = p++;
            buildtree(tree[x].ch[0]);
            return 0;
        }
        if (c == '2')
        {
            tree[x].ch[0] = p++;
            tree[x].ch[1] = p++;
            buildtree(tree[x].ch[0]);
            buildtree(tree[x].ch[1]);
            return 0;
        }
    }
}
int dp(int x, int s)
{
    if (f[x][s] != -1)
        return f[x][s];
    f[x][s] = 0;
    if (x == 0)
        return f[x][s];
    if (s == 1)
    {
        f[x][s] = max(dp(tree[x].ch[0], 2) + dp(tree[x].ch[1], 3), dp(tree[x].ch[0], 3) + dp(tree[x].ch[1], 2));
        return f[x][s];
    }
    if (s == 2)
    {
        f[x][s] = max(dp(tree[x].ch[0], 1) + dp(tree[x].ch[1], 3), dp(tree[x].ch[0], 3) + dp(tree[x].ch[1], 1)) + 1;
        return f[x][s];
    }
    if (s == 3)
    {
        f[x][s] = max(dp(tree[x].ch[0], 1) + dp(tree[x].ch[1], 2), dp(tree[x].ch[0], 2) + dp(tree[x].ch[1], 1));
        return f[x][s];
    }
}
int dp1(int x, int s)
{
    if (q[x][s] != -1)
        return q[x][s];
    q[x][s] = 0;
    if (x == 0)
        return q[x][s];
    if (s == 1)
    {
        q[x][s] = min(dp1(tree[x].ch[0], 2) + dp1(tree[x].ch[1], 3), dp1(tree[x].ch[0], 3) + dp1(tree[x].ch[1], 2));
        return q[x][s];
    }
    if (s == 2)
    {
        q[x][s] = min(dp1(tree[x].ch[0], 1) + dp1(tree[x].ch[1], 3), dp1(tree[x].ch[0], 3) + dp1(tree[x].ch[1], 2)) + 1;
        return q[x][s];
    }
    if (s == 3)
    {
        q[x][s] = min(dp1(tree[x].ch[0], 1) + dp1(tree[x].ch[1], 2), dp1(tree[x].ch[0], 2) + dp1(tree[x].ch[1], 1));
        return q[x][s];
    }
}
int main()
{
    //freopen("trot.in","r",stdin);
    //freopen("trot.out","w",stdout);
    memset(f, -1, sizeof(f));
    memset(q, -1, sizeof(q));
    buildtree(1);
    cout << max(dp(1, 1), max(dp(1, 2), dp(1, 3))) << " ";
    cout << min(dp1(1, 1), min(dp1(1, 2), dp1(1, 3))) << endl;
}

// Problem10337:
#include <iostream>
#include <cstdio>
#include <cstring>
#define LL long long
using namespace std;
int n;
struct node
{
    int data;
    int ch[2];
    bool isting;
} v[400];
LL w[50];
int c[50];
int p = 2;
LL f[400][700];
void buildtree(int x)
{
    int data, r;
    scanf("%d%d", &data, &r);
    v[x].data = data * 2;
    if (r == 0)
    {
        v[x].ch[0] = p++;
        v[x].ch[1] = p++;
        buildtree(v[x].ch[0]);
        buildtree(v[x].ch[1]);
    }
    else
    {
        v[x].isting = 1;
        for (int i = 1; i <= r; i++)
            scanf("%d%d", &w[i], &c[i]);
        for (int v = 0; v <= n; v++)
            f[x][v] = 0;
        for (int i = 1; i <= r; i++)
        {
            for (int v = n; v >= c[i]; v--)
            {
                f[x][v] = max(f[x][v], f[x][v - c[i]] + w[i]);
            }
        }
    }
}
LL dp(int root, int W)
{
    if (W < 0)
        return 0;
    if (f[root][W] != -1)
        return f[root][W];
    f[root][W] = 0;
    if (!v[root].isting)
    {
        for (int i = 0; i <= W; i++)
        {
            f[root][W] = max(f[root][W], dp(v[root].ch[1], W - i - v[v[root].ch[1]].data) + dp(v[root].ch[0], i - v[v[root].ch[0]].data));
        }
        return f[root][W];
    }
}
int main()
{
    //freopen("steal.in","r",stdin);
    //freopen("steal.out","w",stdout);
    memset(f, -1, sizeof(f));
    scanf("%d", &n);
    buildtree(1);
    cout << dp(1, n - v[1].data - 1) << endl;
    //while(1);
}

// Problem10347:
#include <iostream>
#include <cstdio>
#include <cstring>
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
using namespace std;
const int N = 50005;
int maxn[N << 2], change[N << 2], Z[N << 2], S[N << 2], Y[N << 2];
void Pushup(int rt, int m)
{
    if (Z[rt << 1] == m - (m >> 1))
        Z[rt] = Z[rt << 1] + Z[rt << 1 | 1];
    else
        Z[rt] = Z[rt << 1];
    if (Y[rt << 1 | 1] == (m >> 1))
        Y[rt] = Y[rt << 1 | 1] + Y[rt << 1];
    else
        Y[rt] = Y[rt << 1 | 1];
    S[rt] = max(S[rt << 1], max(S[rt << 1 | 1], Y[rt << 1] + Z[rt << 1 | 1]));
}
void buildtree(int l, int r, int rt)
{
    //if(r<l)return;
    Y[rt] = S[rt] = Z[rt] = r - l + 1;
    change[rt] = -1;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    buildtree(lch);
    buildtree(rch);
    //Pushup(rt,r-l+1);
}
void Pushdown(int rt, int m)
{
    if (change[rt] != -1)
    {
        change[rt << 1] = change[rt << 1 | 1] = change[rt];
        if (change[rt] == 0)
        {
            Z[rt << 1] = Y[rt << 1] = S[rt << 1] = m - (m >> 1);
            Z[rt << 1 | 1] = Y[rt << 1 | 1] = S[rt << 1 | 1] = m >> 1;
            change[rt] = -1;
        }
        if (change[rt] == 1)
        {
            Z[rt << 1] = Y[rt << 1] = S[rt << 1] = Z[rt << 1 | 1] = Y[rt << 1 | 1] = S[rt << 1 | 1] = 0;
            change[rt] = -1;
        }
    }
}
void updata(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        change[rt] = c;
        if (c == 0)
        {
            S[rt] = Y[rt] = Z[rt] = r - l + 1;
        }
        else
            S[rt] = Y[rt] = Z[rt] = 0;
        return;
    }
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m)
        updata(L, R, c, lch);
    if (R > m)
        updata(L, R, c, rch);
    Pushup(rt, r - l + 1);
}
int check(int c, int l, int r, int rt)
{
    if (l == r)
        return l;
    if (S[rt] < c)
        return 0;
    //if(l==r) return l;
    Pushdown(rt, r - l + 1);
    //if(S[rt]<c)return 0;
    int m = (l + r) >> 1;
    if (S[rt << 1] >= c)
        return check(c, lch);
    else if (Y[rt << 1] + Z[rt << 1 | 1] >= c)
        return m - Y[rt << 1] + 1;
    else
        return check(c, rch);
}
int main()
{
    //freopen("hotel.in","r",stdin);
    //freopen("hotel.out","w",stdout);
    //cout<<"1\n4\n7\n0\n";
    memset(change, -1, sizeof(change));
    int n, m;
    scanf("%d%d", &n, &m);
    buildtree(1, n, 1);
    int k, p, ans, x;
    while (m--)
    {
        scanf("%d", &k);
        if (k == 1)
        {
            scanf("%d", &p);
            if (S[1] < p)
                puts("0");
            else
            {
                ans = check(p, 1, n, 1);
                //if(ans==n)printf("0\n");
                printf("%d\n", ans);
                updata(ans, ans + p - 1, 1, 1, n, 1);
            }
        }
        else
        {
            scanf("%d%d", &x, &p);
            updata(x, x + p - 1, 0, 1, n, 1);
        }
    }
}

// Problem10348:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int START, END, next, v;
    bool operator<(const edge a) const
    {
        return v < a.v;
    }
} v[600005], re[600005];
int first[100005], p = 1, father[100005], Deep[100005];
bool vis[100005];
int f[100005][25], maxn[100005][25];
int find(int a)
{
    if (father[a] != a)
        father[a] = find(father[a]);
    return father[a];
}
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
void dfs(int x, int dep)
{
    vis[x] = 1;
    Deep[x] = dep;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END])
        {
            f[v[i].END][0] = x;
            maxn[v[i].END][0] = v[i].v;
            dfs(v[i].END, dep + 1);
        }
    }
}
int LCA(int x, int y)
{
    int lca = -1;
    int i = 0;
    if (Deep[x] < Deep[y])
        swap(x, y);
    //for(i=0;(1<<i)<=Deep[x];i++);
    //i--;
    for (int j = 24; j >= 0; j--)
    {
        if (Deep[x] - (1 << j) >= Deep[y])
        {
            lca = max(lca, maxn[x][j]);
            x = f[x][j];
        }
    }
    if (x == y)
        return lca;
    for (int j = 24; j >= 0; j--)
    {
        if (f[x][j] != f[y][j])
        {
            lca = max(lca, max(maxn[x][j], maxn[y][j]));
            x = f[x][j];
            y = f[y][j];
        }
    }
    lca = max(lca, max(maxn[x][0], maxn[y][0]));
    if (x == 1 || y == 1 || lca == 0)
        return -1;
    return lca;
}
int main()
{
    //freopen("1.txt","r",stdin);
    //freopen("3.txt","w",stdout);
    int n, m, t = 1;
    memset(first, -1, sizeof(first));
    scanf("%d%d", &n, &m);
    int a, b, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        re[t].START = a;
        re[t].END = b;
        re[t].v = c;
        t++;
    }
    sort(re + 1, re + t);
    int k = 0;
    for (int i = 1; i <= n; i++)
        father[i] = i;
    for (int i = 1; i < t; i++)
    {
        int x = re[i].START;
        int y = re[i].END;
        if (find(x) != find(y))
        {
            father[find(x)] = find(y);
            add(x, y, re[i].v);
            add(y, x, re[i].v);
            k++;
        }
        if (k == n - 1)
            break;
    }
    f[1][0] = 0;
    maxn[1][0] = 0;
    dfs(1, 0);
    for (int j = 1; j <= 24; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            f[i][j] = f[f[i][j - 1]][j - 1];
            maxn[i][j] = max(maxn[i][j - 1], maxn[f[i][j - 1]][j - 1]);
        }
    }
    int Q;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++)
    {
        scanf("%d%d", &a, &b);
        int ans = LCA(a, b);
        if (ans != -1)
            printf("%d\n", ans);
        else
            puts("impossible");
    }
}

// Problem10358:
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using std::max;
namespace WildRage
{
template <typename _Tp>
class data
{
  public:
    _Tp x;
    int i;
    data(_Tp xi, int ii)
    {
        x = xi;
        i = ii;
    }
};
template <typename _Tp>
class monotony_queue
{
    std::deque<data<_Tp>> Q;

  public:
    void push(_Tp x, int i)
    {
        while (!Q.empty() && Q.back().x < x)
            Q.pop_back();
        Q.push_back((data<_Tp>){x, i});
    }
    void cut(int i, bool (*p)(int, int))
    {
        while (!Q.empty() && p(Q.front().i, i))
            Q.pop_front();
    }
    _Tp front()
    {
        try
        {
            if (Q.empty())
                throw 0;
        }
        catch (int)
        {
            printf("monotony_queue is empty\n");
            while (getchar())
                ;
            getchar();
            exit(1);
        }
        return Q.front().x;
    }
    bool empty()
    {
        return Q.empty();
    }
    int size()
    {
        return Q.size();
    }
    void clear()
    {
        Q.clear();
    }
};
}
bool comp(int a, int b)
{
    return a < b;
}
bool comp1(int a, int b)
{
    return b < a;
}
using WildRage::monotony_queue;
int dp[2005][2005];
int main()
{
    //int t;
    //scanf("%d",&t);
    //while(t--){
    memset(dp, 0x80, sizeof(dp));
    int T, MaxP, W;
    scanf("%d%d%d", &T, &MaxP, &W);
    int APi, BPi, ASi, BSi;
    dp[0][0] = 0;
    for (int i = 1; i <= T; i++)
    {
        scanf("%d%d%d%d", &APi, &BPi, &ASi, &BSi);
        int f;
        for (int j = 0; j <= std::min(MaxP, ASi); j++)
            dp[i][j] = -APi * j;
        for (int j = 0; j <= MaxP; j++)
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        if (i <= W + 1)
            continue;
        monotony_queue<int> Q;
        for (int j = 0; j <= MaxP; j++)
        {
            f = dp[i - W - 1][j] + j * APi;
            Q.push(f, j);
            Q.cut(j - ASi, comp);
            dp[i][j] = max(dp[i][j], Q.front() - j * APi);
        }
        Q.clear();
        for (int j = MaxP; j >= 0; j--)
        {
            f = dp[i - W - 1][j] + j * BPi;
            Q.push(f, j);
            Q.cut(j + BSi, comp1);
            dp[i][j] = max(dp[i][j], Q.front() - j * BPi);
        }
    }
    int ans = 0x80808080;
    for (int i = 0; i <= MaxP; i++)
        ans = max(ans, dp[T][i]);
    printf("%d\n", ans);
    //}
    //while(1);
}
// Problem10360:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 100005;
struct egde
{
    int v, next, END;
} v[N * 2];
int first[N], p = 1;
int dis[N];
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}
void spfa(int x)
{
    memset(dis, 0x3f, sizeof(dis));
    queue<int> Q;
    bool flag[N] = {0};
    flag[x] = 1;
    Q.push(x);
    dis[x] = 0;
    while (!Q.empty())
    {
        int k = Q.front();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                if (!flag[v[i].END])
                {
                    flag[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
        }
        Q.pop();
        flag[k] = 0;
    }
}
int id[N], dep[N], val[N], fa[N], size[N], son[N], top[N], num;
void dfs1(int rt, int f, int dp)
{
    fa[rt] = f;
    size[rt] = 1;
    dep[rt] = dp;
    son[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == f)
            continue;
        dfs1(v[i].END, rt, dp + 1);
        size[rt] += size[v[i].END];
        val[v[i].END] = v[i].v;
        son[rt] = size[son[rt]] > size[v[i].END] ? son[rt] : v[i].END;
    }
}
void dfs2(int rt, int tp)
{
    top[rt] = tp;
    id[rt] = ++num;
    if (son[rt])
        dfs2(son[rt], tp);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa[rt] || v[i].END == son[rt])
            continue;
        dfs2(v[i].END, v[i].END);
    }
}
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int sum1[N << 2], sum2[N << 2];
void Pushup1(int rt)
{
    sum1[rt] = sum1[rt << 1] + sum1[rt << 1 | 1];
}
void update1(int i, int c, int l, int r, int rt)
{
    if (l == r)
    {
        sum1[rt] = c;
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m)
        update1(i, c, lch);
    else
        update1(i, c, rch);
    Pushup1(rt);
}
int Query1(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return sum1[rt];
    int m = (l + r) >> 1;
    int ans = 0;
    if (L <= m)
        ans += Query1(L, R, lch);
    if (R > m)
        ans += Query1(L, R, rch);
    return ans;
}
void Pushup2(int rt)
{
    sum2[rt] = sum2[rt << 1] + sum2[rt << 1 | 1];
}
void update2(int i, int c, int l, int r, int rt)
{
    if (l == r)
    {
        sum2[rt] = c;
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m)
        update2(i, c, lch);
    else
        update2(i, c, rch);
    Pushup2(rt);
}
int Query2(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return sum2[rt];
    int m = (l + r) >> 1;
    int ans = 0;
    if (L <= m)
        ans += Query2(L, R, lch);
    if (R > m)
        ans += Query2(L, R, rch);
    return ans;
}
int n;
int LCA(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] > dep[top[y]])
        {
            ans += Query2(id[top[x]], id[x], 1, n, 1);
            x = fa[top[x]];
        }
        else
        {
            ans += Query1(id[top[y]], id[y], 1, n, 1);
            y = fa[top[y]];
        }
    }
    if (x != y)
    {
        if (dep[x] < dep[y])
        {
            ans += Query1(id[x] + 1, id[y], 1, n, 1);
        }
        else
        {
            ans += Query2(id[y] + 1, id[x], 1, n, 1);
        }
    }
    return ans;
}
int main()
{
    //freopen("magnus.in","r",stdin);
    //freopen("magnus.out","w",stdout);
    int t;
    scanf("%d", &t);
    memset(first, -1, sizeof(first));
    if (t <= 14)
    {
        int m, q, a, b;
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            add(a, b, 0);
            add(b, a, 1);
        }
        scanf("%d%d", &a, &b);
        //cout<<a<<" "<<b<<endl;
        //while(1);
        spfa(a);
        if (dis[b] > 10000000)
            puts("-1");
        else
            printf("%d\n", dis[b]);
    }
    else
    {
        int m, q, a, b;
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            add(a, b, 0);
            add(b, a, 1);
        }
        dfs1(1, 0, 1);
        dfs2(1, 1);
        for (int i = 2; i <= n; i++)
        {
            update1(id[i], val[i], 1, n, 1);
            update2(id[i], val[i] ^ 1, 1, n, 1);
        }
        while (q--)
        {
            scanf("%d%d", &a, &b);
            printf("%d\n", LCA(a, b));
        }
    }
}

// Problem10361:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;
double eps = 1e-10;
class pig
{
  public:
    double x, y;
} a[20];
class Parabola
{
  public:
    double a, b;
    int S;
    void get_ab(pig x1, pig x2)
    {
        a = (x2.y * x1.x - x1.y * x2.x) / (x2.x * x2.x * x1.x - x1.x * x1.x * x2.x);
        b = (x1.y * x2.x - x1.x * x2.y) / (x2.x * x2.x - x1.x * x2.x) + x1.y / x1.x;
        //if(abs(a)<eps) b=0;
        //if(a>eps)a=0,b=0;
    }
    void get_ab2(pig x1)
    {
        a = -x1.y / x1.x;
        b = -2 * a * x1.x;
    }
} v[20][20];
int f[1 << 20];
int main()
{
    //freopen("angrybirds.in","r",stdin);
    //freopen("angrybirds.out","w",stdout);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(v, 0, sizeof(v));
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf", &a[i].x, &a[i].y);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                v[i][j].get_ab(a[i], a[j]);
                if (v[i][j].a > -eps || abs(v[i][j].a) < eps || i == j)
                {
                    v[i][j].get_ab2(a[j]);
                    v[i][j].S |= 1 << j - 1;
                    continue;
                }
                for (int k = 1; k <= n; k++)
                {
                    if (abs((a[k].x * a[k].x * v[i][j].a + a[k].x * v[i][j].b - a[k].y)) < eps)
                    {
                        v[i][j].S |= 1 << k - 1;
                    }
                }
            }
        }
        // char s[20];
        // for(int i=1;i<=n;i++){
        // for(int j=1;j<=n;j++){
        // printf("A:%lf B:%lf\n",v[i][j].a,v[i][j].b);
        // itoa(v[i][j].S,s,2);
        // printf("%s\n",s);
        // }
        // }
        int N = (1 << n) - 1;
        memset(f, 0x3f, sizeof(f));
        f[0] = 0;
        int l = 0;
        for (int S = 1; S <= N; S++)
        {
            for (int i = 1; i <= n; i++)
            {
                if (S & (1 << i - 1))
                {
                    l = i;
                    break;
                }
            }
            f[S] = f[S - (S & (1 << l - 1))] + 1;
            for (int j = l + 1; j <= n; j++)
            {
                f[S] = min(f[S], f[S - (S & v[l][j].S)] + 1);
            }
        }
        printf("%d\n", f[N]);
    }
    //printf("%lf",(double)clock()/CLOCKS_PER_SEC);
    //while(1);
}

/*************************
a=(y2*x1-y1*x2.x)/(x2*x2*x1-x1*x1*x2)
b=(y1*x2-x1*y2)/(x2*x2-x1*x2)+y1/x1
*************************/
// Problem10362:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
long long f[1 << 20];
int cur[21];
int find_line(int x)
{
    int cut = 0;
    while (x > 0)
    {
        cut++;
        x &= (x - 1);
    }
    return cut;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int N = (1 << n) - 1;
    int a, b;
    for (int i = 0; i <= n; i++)
        cur[i] = N;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        cur[a] ^= 1 << (b - 1);
    }
    f[0] = 1;
    for (int S = 1; S <= N; S++)
    {
        int line = find_line(S);
        int tmps = S & cur[line];
        for (int i = 1; i <= n; i++)
        {
            if ((tmps & 1 << (i - 1)) > 0)
            {
                f[S] += f[(S ^ (1 << (i - 1)))];
            }
        }
    }
    printf("%lld", f[N]);
}
// Problem10362:
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
long long f[1 << 20];
int cur[21];
int find_line(int x)
{
    int cut = 0;
    while (x > 0)
    {
        cut++;
        x &= (x - 1);
    }
    return cut;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int N = (1 << n) - 1;
    int a, b;
    for (int i = 1; i <= n; i++)
        cur[i] = N;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        cur[a] ^= 1 << n - b;
    }
    f[0] = 1;
    for (int S = 1; S <= N; S++)
    {
        int line = find_line(S);
        int tmps = S & cur[line];
        for (int i = 1; i <= n; i++)
        {
            if ((tmps & (1 << n - i)) > 0)
            {
                f[S] += f[S ^ (1 << n - i)];
            }
        }
    }
    printf("%lld", f[N]);
}
// Problem10363:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define LL long long
int n, m;
struct data
{
    int w, v;
} a[200005];
struct Data
{
    int l, r;
} Q[200005];
int Sumn[200005];
LL Sumv[200005];
LL check(int w)
{
    Sumn[0] = 0;
    Sumv[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        Sumn[i] = Sumn[i - 1] + (a[i].w > w);
        Sumv[i] = Sumv[i - 1] + (a[i].w > w ? a[i].v : 0);
    }
    LL Y = 0;
    for (int i = 1; i <= m; i++)
    {
        Y += (Sumn[Q[i].r] - Sumn[Q[i].l - 1]) * (Sumv[Q[i].r] - Sumv[Q[i].l - 1]);
    }
    return Y;
}
int main()
{
    //freopen("qc.in", "r", stdin);
    //freopen("qc.out", "w", stdout);
    LL S;
    scanf("%d%d%lld", &n, &m, &S);
    int Max = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i].w, &a[i].v);
        Max = max(Max, a[i].w);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &Q[i].l, &Q[i].r);
    }
    LL l = 0, r = Max;
    LL ans = 0x3fffffffffffffffLL;
    while (l < r)
    {
        LL mid = l + r >> 1;
        LL t = check(mid);
        if (t < S)
        {
            ans = min(ans, abs(t - S));
            r = mid;
        }
        else
        {
            ans = min(ans, abs(t - S));
            l = mid + 1;
        }
    }
    printf("%lld", ans);

    //while (1);
}

// Problem10396:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#include <cstdlib>
using namespace std;
//#define WILDRAGE 1
int a[6][8];
bool over[6][8];
void print(const int c[6][8])
{
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 7; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
    printf("\n");
}
bool ok(const int c[6][8])
{
    //return 0;
    for (int i = 1; i <= 5; i++)
    {
        if (c[i][1])
            return 0;
    }
    return 1;
}
bool remove(int c[6][8])
{
    int it1, it2;
    for (int i = 1; i <= 5; i++)
    {
        it1 = it2 = 1;
        while (1)
        {
            while (c[i][it1] != 0 && it1 <= 7)
                it1++;
            it2 = it1;
            while (c[i][it2] == 0 && it2 <= 7)
                it2++;
            if (it2 != 8)
                swap(c[i][it2], c[i][it1]);
            else
                break;
        }
    }
    // memset(over,0,sizeof(over));
    int times = 1;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
        {
            if (c[i][j] && c[i][j] == c[i][j - 1])
            {
                times++;
                if (times >= 3 && times < 4)
                {
                    over[i][j - 2] = over[i][j - 1] = over[i][j] = 1;
                }
                if (times >= 4)
                    over[i][j] = 1;
            }
            else
                times = 1;
        }
    times = 1;
    for (int j = 1; j <= 7; j++)
        for (int i = 1; i <= 5; i++)
        {
            if (c[i][j] && c[i][j] == c[i - 1][j])
            {
                times++;
                if (times >= 3 && times < 4)
                {
                    over[i - 2][j] = over[i - 1][j] = over[i][j] = 1;
                }
                if (times >= 4)
                    over[i][j] = 1;
            }
            else
                times = 1;
        }
    bool yes = 0;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
            if (over[i][j])
                yes = 1, over[i][j] = 0, c[i][j] = 0;
    if (!yes)
        return 0;
    //int it1, it2;
    for (int i = 1; i <= 5; i++)
    {
        it1 = it2 = 1;
        while (1)
        {
            while (c[i][it1] != 0 && it1 <= 7)
                it1++;
            it2 = it1;
            while (c[i][it2] == 0 && it2 <= 7)
                it2++;
            if (it2 != 8)
                swap(c[i][it2], c[i][it1]);
            else
                break;
        }
    }
    return 1;
}
struct data
{
    int x, y, t;
};
stack<data> op;
stack<data> ans;
int n;
void dfs(int t, const int c[6][8])
{
    if (t == n)
    {
#ifdef WILDRAGE
        print(c);
#endif
        if (ok(c))
        {
            while (!op.empty())
            {
                ans.push(op.top());
                op.pop();
            }
            while (!ans.empty())
            {
                printf("%d %d %d\n", ans.top().x - 1, ans.top().y - 1, ans.top().t);
                ans.pop();
            }
            exit(0);
        }
        return;
    }
    else
    {
        int s[6][8];
        for (int i = 1; i <= 5; i++)
        {
            for (int j = 1; j <= 7; j++)
            {
                if (c[i][j] && i + 1 <= 5)
                {
                    op.push((data){i, j, 1});
                    memcpy(s, c, sizeof(s));
                    swap(s[i][j], s[i + 1][j]);
#ifdef WILDRAGE
//print(s);
#endif
                    while (remove(s))
                        ;
#ifdef WILDRAGE
                    printf("%d %d %d\n", i, j, 1);
                    print(s);
#endif
                    dfs(t + 1, s);
                    op.pop();
                }
                if (c[i][j] && i - 1 > 0 && !c[i - 1][j])
                {
                    op.push((data){i, j, -1});
                    memcpy(s, c, sizeof(s));
                    swap(s[i][j], s[i - 1][j]);
#ifdef WILDRAGE
//print(s);
#endif
                    while (remove(s))
                        ;
#ifdef WILDRAGE
                    printf("%d %d %d\n", i, j, -1);
                    print(s);
#endif
                    dfs(t + 1, s);
                    op.pop();
                }
                //                 else if (c[i][j] && i + 1 <= 5 && !c[i + 1][j])
                //                 {
                //                     op.push((data){i, j, 1});
                //                     memcpy(s, c, sizeof(s));
                //                     swap(s[i][j], s[i + 1][j]);
                // #ifdef WILDRAGE
                // //print(s);
                // #endif
                //                     while (remove(s))
                //                         ;
                // #ifdef WILDRAGE
                //                     printf("%d %d %d\n", i, j, 1);
                //                     print(s);
                // #endif
                //                     dfs(t + 1, s);
                //                     op.pop();
                //                 }
            }
        }
    }
}
int main()
{
#ifdef WILDRAGE
    freopen("mayan.in", "r", stdin);
    freopen("mayan.out", "w", stdout);
#endif
    int s;
    scanf("%d", &n);
    for (int i = 1; i <= 5; i++)
    {
        int j = 0;
        while (scanf("%d", &s))
        {
            if (s == 0)
                break;
            a[i][++j] = s;
        }
        //a[i][0] = j;
    }
#ifdef WILDRAGE
    print(a);
#endif
    dfs(0, a);
    printf("-1\n");
}

// Problem10399:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct edge
{
    int END, next;
} E[200005], v[200005];
int first[100005], head[100005], p, h, dis[100005];
bool vis[100005], ok[100005];
void add(int a, int b, int op)
{
    if (op)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
    else
    {
        E[h].END = b;
        E[h].next = head[a];
        head[a] = h++;
    }
}
void dfs(int x)
{
    vis[x] = 1;
    for (int i = head[x]; i != -1; i = E[i].next)
    {
        if (!vis[E[i].END])
            dfs(E[i].END);
    }
}
int main()
{
    // freopen("roadb.in","r",stdin);
    // freopen("roadb.out","w",stdout);
    memset(head, -1, sizeof(head));
    memset(first, -1, sizeof(first));
    int n, m;
    scanf("%d%d", &n, &m);
    int s, e;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s, &e);
        add(e, s, 0);
        add(s, e, 1);
    }
    scanf("%d%d", &s, &e);
    dfs(e);
    for (int i = 1; i <= n; i++)
    {
        ok[i] = 1;
        for (int j = first[i]; j != -1; j = v[j].next)
            if (!vis[v[j].END])
            {
                ok[i] = 0;
                break;
            }
    }
    if (!ok[s])
    {
        printf("-1\n");
        return 0;
    }
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
            if (ok[v[i].END] && dis[v[i].END] > dis[k] + 1)
            {
                dis[v[i].END] = dis[k] + 1;
                if (!vis[v[i].END])
                {
                    Q.push(v[i].END);
                    vis[v[i].END] = 1;
                }
            }
    }
    if (dis[e] > 100000000)
        dis[e] = -1;
    printf("%d\n", dis[e]);
}
// Problem10401:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
int c[105];
int a[105][105], map[105][105], link[105][105];
bool flag[105];
int t, ans = 0x3f3f3f3f, n;
stack<int> Q;
//std::vector<int> dis;
void dfs(int x, int len)
{
    if (x == t)
    {
        ans = min(ans, len);
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (link[x][i] && !flag[c[i]] && map[x][i] + len < ans && !a[c[i]][c[i]])
        {
            flag[c[i]] = 1;
            int t = 0;
            for (int j = 1; j <= n; j++)
                if (a[c[j]][c[i]] && !flag[c[j]])
                    Q.push(c[j]), t++, flag[c[j]] = 1;
            //dis.push_back(i);
            dfs(i, len + map[x][i]);
            //dis.pop_back();
            while (t--)
                flag[Q.top()] = 0, Q.pop();
        }
    }
}
int main()
{
    //freopen("culture.in", "r", stdin);
    //freopen("culture.out", "w", stdout);
    int k, m, S;
    scanf("%d%d%d%d%d", &n, &k, &m, &S, &t);
    for (int i = 1; i <= n; i++)
        scanf("%d", &c[i]);
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            scanf("%d", &a[i][j]);
    int s, e;
    memset(map, 0x3f, sizeof(map));
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s, &e);
        scanf("%d", &map[s][e]);
        map[e][s] = map[s][e];
        link[s][e] = link[e][s] = 1;
    }
    for (int i = 1; i <= n; i++)
        map[i][i] = 0;
    for (int l = 1; l <= n; l++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                map[i][j] = min(map[i][j], map[i][l] + map[l][j]);
    flag[c[S]] = 1;
    for (int i = 1; i <= n; i++)
        if (a[c[i]][c[S]])
            flag[c[i]] = 1;
    //dis.push_back(S);
    dfs(S, 0);
    if (ans > 10000000)
        ans = -1;
    printf("%d\n", ans);
}
// Problem10405:/*
*@Author : WildRage
               *@Date : 2017 -
    07 - 01 10 : 17 : 47 * @Last Modified by : WildRage *@Last Modified time : 2017 - 07 - 01 11 : 08 : 00 * /
#include <iostream>
#include <cstdio>
#include <cstring>
                                                                                               namespace MineWorkSpace
{
    char s[10005][80];
    int next[10005][80];
    int next2[80][10005];
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    int lcm(int a, int b)
    {
        return a / gcd(a, b) * b;
    }
    int Main()
    {
#ifdef Mine
        freopen("mgrid.in", "r", stdin);
        freopen("mgrid.out", "w", stdout);
#endif
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s[i]);
        }
        int ans1 = 1, ans2 = 1;
        for (int i = 0; i < n; i++)
        {
            int j = 0, k = -1;
            next[i][0] = -1;
            while (j < m)
            {
                if (k == -1 || s[i][j] == s[i][k])
                {
                    next[i][++j] = ++k;
                }
                else
                    k = next[i][k];
            }
            if (m - next[i][m])
                ans1 = lcm(ans1, m - next[i][m]);
            if (ans1 > m)
                ans1 = m;
        }
        for (int i = 0; i < m; i++)
        {
            int j = 0, k = -1;
            next2[i][0] = -1;
            while (j < n)
            {
                if (k == -1 || s[j][i] == s[k][i])
                {
                    next2[i][++j] = ++k;
                }
                else
                    k = next2[i][k];
            }
            if (n - next2[i][n])
                ans2 = lcm(ans2, n - next2[i][n]);
            if (ans2 > n)
                ans2 = n;
        }
        return printf("%d", ans1 * ans2);
    }
}
int main()
{
    MineWorkSpace::Main();
    //while(1);
}

// Problem10406:/*
*@Author : WildRage
               *@Date : 2017 -
    07 - 02 16 : 07 : 15 * @Last Modified by : WildRage *@Last Modified time : 2017 - 07 - 02 17 : 58 : 06 * /
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
                                                                                               using namespace std;
int a[1005], sum[10][1005], n;
int DP[1005][300];
bool had[10];
int N = (1 << 8) - 1;
vector<int> in[10];
int get_num(int p, int len)
{
    int now = lower_bound(in[a[p]].begin(), in[a[p]].end(), p) - in[a[p]].begin();
    int ans = now + len - 1;
    if (in[a[p]].size() - 1 < ans)
        return -1;
    return in[a[p]][ans];
}
int Judge(int len)
{
    memset(DP, 0, sizeof(DP));
    for (int i = 0; i < n; i++)
    {
        int to = get_num(i + 1, len);
        if (to != -1)
            DP[to][(1 << (a[i + 1] - 1))] = max(DP[i][0] + len, DP[to][1 << (a[i + 1] - 1)]);
        to = get_num(i + 1, len + 1);
        if (to != -1)
            DP[to][(1 << (a[i + 1] - 1))] = max(DP[i][0] + len + 1, DP[to][(1 << (a[i + 1] - 1))]);
        for (int j = 1; j < N; j++)
        {
            if (DP[i][j])
            {
                DP[i + 1][j] = max(DP[i + 1][j], DP[i][j]);
                if (j & (1 << (a[i + 1] - 1)))
                    continue;
                to = get_num(i + 1, len);
                if (to != -1)
                    DP[to][j | (1 << (a[i + 1] - 1))] = max(DP[i][j] + len, DP[to][j | (1 << (a[i + 1] - 1))]);
                to = get_num(i + 1, len + 1);
                if (to != -1)
                    DP[to][j | (1 << (a[i + 1] - 1))] = max(DP[i][j] + len + 1, DP[to][j | (1 << (a[i + 1] - 1))]);
            }
            DP[i + 1][N] = max(DP[i + 1][N], DP[i][N]);
        }
    }
    return DP[n][N];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        had[a[i]] = 1;
        in[a[i]].push_back(i);
    }
    int ans = 0;
    for (int i = 1; i <= 8; i++)
        if (had[i])
            ans++;
    int l = 1, r = 256;
    while (l <= r)
    {
        int mid = l + r >> 1;
        int x = Judge(mid);
        ans = max(x, ans);
        if (x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d", ans);
}

// Problem10408:
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
const long long base = 10000000000000000ll;
struct bignumber
{
    long long a[3];
    bignumber()
    {
        memset(a, 0, sizeof(a));
    }
    bignumber(unsigned long long s)
    {
        *this = s;
    }
    bignumber operator=(const unsigned long long s)
    {
        a[1] = s % base;
        a[2] = s / base;
        return *this;
    }
    bignumber operator+(const bignumber &s)
    {
        bignumber ans;
        ans = *this;
        ans.a[1] += s.a[1];
        int k = a[1] / base;
        a[1] %= base;
        a[2] += s.a[2] + k;
        return ans;
    }
    bignumber operator+(const long long &s)
    {
        bignumber S = (unsigned long long)s;
        return *this + S;
    }
    bignumber operator+(const int &s)
    {
        bignumber ans;
        ans = *this;
        ans.a[1] += s;
        int k = a[1] / base;
        a[1] %= base;
        a[2] += k;
        return ans;
    }
    bignumber operator*(const int &s)
    {
        bignumber ans;
        ans = *this;
        ans.a[1] *= s;
        int k = a[1] / base;
        a[1] %= base;
        ans.a[2] *= s;
        ans.a[2] += k;
        return ans;
    }
    bool operator==(const bignumber &s) const
    {
        return a[1] == s.a[1] && a[2] == s.a[2];
    }
    bool operator<(const bignumber &s) const
    {
        return a[2] < s.a[2] ? 1 : a[1] < s.a[1];
    }
    bool operator>(const bignumber &s) const
    {
        return a[2] > s.a[2] ? 1 : a[1] > s.a[1];
    }
    bignumber operator-(const bignumber &s)
    {
        bignumber ans;
        if (*this == s)
            return ans;
        ans = *this;
        if (ans.a[1] < s.a[1])
            ans.a[1] += base, ans.a[2] -= 1;
        ans.a[1] -= s.a[1];
        ans.a[2] -= s.a[2];
        return ans;
    }
    bignumber operator-(const long long &s)
    {
        bignumber S = (unsigned long long)s;
        return *this - S;
    }
} f[19];
void Init()
{
    f[1] = 9;
    f[2] = 180;
    f[3] = 2700;
    f[4] = 36000;
    f[5] = 450000;
    f[6] = 5400000;
    f[7] = 63000000;
    f[8] = 720000000;
    f[9] = 8100000000ull;
    f[10] = 90000000000ull;
    f[11] = 990000000000ull;
    f[12] = 10800000000000ull;
    f[13] = 117000000000000ull;
    f[14] = 1260000000000000ull;
    f[15] = 13500000000000000ull;
    f[16] = 144000000000000000ull;
    f[17] = 1530000000000000000ull;
    f[18] = 16200000000000000000ull;
}
void print(bignumber a)
{
    if (a.a[2] != 0)
    {
        printf("%lld", a.a[2]);
        printf("%016lld", a.a[1]);
    }
    else
    {
        printf("%lld", a.a[1]);
    }
}
int main()
{
    Init();
    //print(f[18]);
    string a, b;
    bignumber ans1, ans2;
    cin >> a >> b;
    int t = 0;
    for (int j = 0, i = a.size(); i >= 2; j++, i--)
    {
        if (a[j] == '0')
            continue;
        ans1 = ans1 + f[i - 1] * (a[j] - '0') + (long long)pow(10, i - 1) * (a[j] - '0' - 1) + (long long)(a[j] - '0') * (long long)pow(10, i - 1) * t;
        t++;
    }
    ans1 = ans1 + (t + 1) * (int)(a[a.size() - 1] - '0');
    if (a[a.size() - 1] != '0')
        ans1 = ans1 - 1;
    t = 0;
    for (int j = 0, i = b.size(); i >= 2; j++, i--)
    {
        if (b[j] == '0')
            continue;
        ans2 = ans2 + f[i - 1] * (b[j] - '0') + (long long)pow(10, i - 1) * (b[j] - '0' - 1) + (long long)(b[j] - '0') * (long long)pow(10, i - 1) * t;
        t++;
    }
    ans2 = ans2 + (t + 1) * (int)(b[b.size() - 1] - '0');
    for (int i = 0; i < b.size() - 1; i++)
        if (b[i] != '0')
            ans2 = ans2 + 1;

    print(ans2 - ans1);
    //while (1)
    ;
}
// Problem10410:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <ctime>
using namespace std;
vector<int> l;
struct Improtant
{
    int i, Imp;
    bool operator<(const Improtant &a) const
    {
        return Imp == a.Imp ? i < a.i : Imp < a.Imp;
    }
} number[50005];
struct Trie
{
    map<int, Trie *> mp;
    set<Improtant> mark;
} * root;
void insert(int x)
{
    Trie *rt = root;
    rt->mark.insert(number[x]);
    for (int i = 0; i < l.size(); i++)
    {
        if (!rt->mp[l[i]])
            rt->mp[l[i]] = new Trie;
        rt = rt->mp[l[i]];
        rt->mark.insert(number[x]);
    }
}
void Query(int k)
{
    Trie *rt = root;
    for (int i = 0; i < l.size(); i++)
    {
        if (rt->mp[l[i]] == NULL)
        {
            printf("0\n");
            return;
        }
        rt = rt->mp[l[i]];
    }
    set<Improtant>::iterator it = rt->mark.begin();
    printf("%d ", rt->mark.size());
    for (int i = 1; i <= k && it != rt->mark.end(); i++, it++)
    {
        printf("%d ", it->i);
    }
    printf("\n");
    return;
}
int main()
{
#ifdef Mine
    freopen("1.in", "r", stdin);
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
#endif
    int n, m;
    root = new Trie;
    scanf("%d%d", &n, &m);
    int t, s, a;
    for (int i = 1; i <= n; i++)
    {
        number[i].i = i;
        scanf("%d%d", &t, &number[i].Imp);
        while (t--)
        {
            scanf("%d", &s);
            l.clear();
            for (int j = 1; j <= s; j++)
            {
                scanf("%d", &a);
                l.push_back(a);
            }
            insert(i);
        }
    }
    int k;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &k, &s);
        l.clear();
        for (int j = 1; j <= s; j++)
        {
            scanf("%d", &a);
            l.push_back(a);
        }
        Query(k);
    }
    //printf("%lf",(double)clock()/CLOCKS_PER_SEC);
}
// Problem10412:
#include <cstdio>
#include <cstring>
int P;
class frac
{
  public:
    long long a, b;
    long long gcd(long long A, long long B)
    {
        return B == 0 ? A : gcd(B, A % B);
    }
    frac Update(frac s)
    {
        if (s.a == 0)
            return s;
        int GCD = s.gcd(s.a, s.b);
        return (frac){s.a / GCD, s.b / GCD};
    }
    frac operator*(const frac A)
    {
        return (frac){a * A.a % P, b * A.b % P};
    }
    frac operator*(const int A)
    {
        return (frac){a * A % P, b % P};
    }
};
frac ans[1000001];
// 0 b, 1 r
// 0 = ,1 b>r ,2,b<r
int main()
{
    //freopen("brtree.in", "r", stdin);
    //freopen("brtree.out", "w", stdout);
    int p, q, T;
    scanf("%d%d%d%d", &p, &q, &T, &P);
    p %= P;
    q %= P;
    frac B = (frac){q - p, q};
    frac R = (frac){p, q};
    frac BR = B * R * 2;
    frac BBRR = (frac){p * p + (q - p) * (q - p), q * q};
    BR = BR.Update(BR);
    BBRR = BBRR.Update(BBRR);
    ans[2] = BBRR;
    for (int i = 4; i <= 1000000; i += 2)
    {
        ans[i] = ans[i - 2] * BR;
    }
    int k = 0, r = 0;
    while (T--)
    {
        scanf("%d", &k);
        k -= r;
        //int Gcd = ans[k].gcd(ans[k].a, ans[k].b);
        r = 0;
        printf("%lld %lld\n", ans[k].a % P, ans[k].b % P);
        r = ans[k].a % P;
    }
}

// Problem10413:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    long long END, next, v;
} v[5005];
long long first[2505], p;
void add(long long a, long long b, long long c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
long long a[2505][2505];
long long b[2505][2505];
long long minn[2505], head[2505];
bool intree[2505];
void dfs(long long s, long long x, long long fa, long long dis)
{
    b[s][x] = dis;
    for (long long i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa)
        {
            dfs(s, v[i].END, x, dis + v[i].v);
        }
    }
}
int main()
{
    //memset(first, -1, sizeof(first));
    //freopen("treas.in", "r", stdin);
    //freopen("treas.out", "w", stdout);
    long long T;
    scanf("%lld", &T);
    while (T--)
    {
        memset(first, -1, sizeof(first));
        memset(head, 0, sizeof(head));
        p = 0;
        long long n;
        scanf("%lld", &n);
        for (long long i = 1; i <= n; i++)
        {
            for (long long j = 1; j <= n; j++)
            {
                scanf("%lld", &a[i][j]);
            }
        }
        if (n == 1)
        {
            printf("Yes\n1\n");
            continue;
        }
        memset(minn, 0x3f, sizeof(minn));
        memset(intree, 0, sizeof(intree));
        minn[1] = 0;
        for (long long i = 1; i <= n; i++)
        {
            long long k = 0;
            for (long long j = 1; j <= n; j++)
            {
                if (!intree[j] && (minn[j] < minn[k]))
                {
                    k = j;
                }
            }
            intree[k] = 1;
            // add(i, k, minn[k]);
            // add(k, i, minn[k]);
            for (long long j = 1; j <= n; j++)
            {
                if (!intree[j] && j != k && (a[k][j] < minn[j]))
                {
                    minn[j] = a[k][j];
                    head[j] = k;
                }
            }
        }
        for (long long i = 2; i <= n; i++)
        {
            add(i, head[i], minn[i]);
            add(head[i], i, minn[i]);
        }
        for (long long i = 1; i <= n; i++)
        {
            dfs(i, i, 0, 0);
        }
        bool flag = 0;
        for (long long i = 1; i <= n; i++)
        {
            for (long long j = 1; j <= n; j++)
            {
                if (a[i][j] != b[i][j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
        if (flag)
        {
            printf("No\n");
            continue;
        }
        else
        {
            printf("Yes\n");
            double ans = 0;
            long long d = 0;
            for (long long i = 1; i <= n; i++)
            {
                long long sum = 0, t = 0;
                for (long long j = first[i]; j != -1; j = v[j].next)
                {
                    sum += v[j].v;
                    t++;
                }
                if (ans < (double)sum / t)
                {
                    ans = (double)sum / t;
                    d = i;
                }
            }
            printf("%lld\n", d);
        }
    }
    // while (1)
    ;
}
// Problem10414:
#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
struct data
{
    int l, r, id;
    bool operator<(const data &a) const
    {
        return l == a.l ? r > a.r : l < a.l;
    }
} a[1000001];
int main(int argc, char const *argv[])
{
    stack<data> st;
    int n, s, r;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &s, &r);
        a[i].l = s - r, a[i].id = i, a[i].r = s + r;
    }
    sort(a, a + n);
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d %d %d\n", a[i].l, a[i].r, a[i].id);
    // }
    //while (1)
    ;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i].l == a[i + 1].l && i + 1 != n - 1)
        {
            st.push(a[i]);
            continue;
        }
        if (!st.empty() && a[i].r == st.top().r)
        {
            st.pop();
            ans++;
        }
        if (a[i].r != a[i + 1].l)
        {
            if (!st.empty())
                st.pop();
        }
    }
    printf("%d", ans + n + 1);
    return 0;
}
// Problem10415:
#include <cstdio>
#include <cstring>
using namespace std;
double f[55][8][8][8];
int main(int argc, char const *argv[])
{
    int T, a, b, c, k;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &k, &a, &b, &c);
        // for (int i = 0; i < k + 1; i++)
        // {
        //     for (int j = 0; j < 8; j++)
        //     {
        //         for (int l = 0; l < 8; l++)
        //         {
        //             for (int m = 0; m < 8; m++)
        //             {
        //                 f[i][j][l][m] = 0;
        //             }
        //         }
        //     }
        // }
        memset(f, 0, sizeof(f));
        f[1][a][b][c] = 1;
        double ans = 0;
        for (int i = 1; i <= k; i++)
        {
            for (int j = 0; j <= 7; j++)
                for (int l = 0; l <= 7; l++)
                    for (int m = 0; m <= 7; m++)
                    {
                        if (l + j + m <= 7)
                        {
                            if (j > 0)
                                f[i + 1][j - 1][l][m] += f[i][j][l][m] * j * 1.0 / (l + j + m + 1);
                            if (l > 0)
                            {
                                if (l + j + m <= 6)
                                    f[i + 1][j + 1][l - 1][m + 1] += f[i][j][l][m] * l * 1.0 / (l + j + m + 1);
                                else
                                    f[i + 1][j + 1][l - 1][m] += f[i][j][l][m] * l * 1.0 / (l + j + m + 1);
                            }
                            if (m > 0)
                            {
                                if (l + j + m <= 6)
                                    f[i + 1][j][l + 1][m] += f[i][j][l][m] * m * 1.0 / (l + j + m + 1);
                                else
                                    f[i + 1][j][l + 1][m - 1] += f[i][j][l][m] * m * 1.0 / (l + j + m + 1);
                            }
                            f[i + 1][j][l][m] += f[i][j][l][m] * 1.0 / (l + j + m + 1);
                            ans += f[i][j][l][m] * 1.0 / (l + j + m + 1);
                        }
                    }
        }
        printf("%.2lf\n", ans);
    }
    //while (1)
    ;
    return 0;
}

// Problem10416:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == 1 || n == 2)
    {
        if ((m - 1) % 3)
        {
            printf("impossible\n");
            return 0;
        }
        else
        {
            printf("%d", (m - 1) / 3 * 2 + 1);
            return 0;
        }
    }
    if (m == 1 || m == 2)
    {
        if ((n - 1) % 3)
        {
            printf("impossible\n");
            return 0;
        }
        else
        {
            printf("%d", (n - 1) / 3 * 2 + 1);
            return 0;
        }
    }
    if (n == 3 && m == 3)
    {
        printf("8");
        return 0;
    }
    if (m == 3)
    {
        int ans = 0;
        int k = (n - 1) % 3;
        if (k == 1)
        {
            ans += 5;
        }
        if (k == 2)
        {
            ans += 6;
        }
        printf("%d\n", (n - 1) / 3 * 2 + ans);
        return 0;
    }
    if (n == 3)
    {
        int ans = 0;
        int k = (m - 1) % 3;
        if (k == 1)
        {
            ans += 5;
        }
        if (k == 2)
        {
            ans += 6;
        }
        printf("%d\n", (m - 1) / 3 * 2 + ans);
        return 0;
    }
    printf("%d", (n - 1) / 3 * 2 + (m - 1) / 3 * 2 + (n - 1) % 3 + (m - 1) % 3);
}

// Problem10417:
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
const int MOD = 1000000007;
int a[100005], num, k;
int bin[10];
long long F[100005];
long long f[1050][1050];
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long C(int n, int m)
{
    if (m == 0)
        return 1;
    if (m > n || m < 0 || n < 0)
        return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
map<int, int> Mp, Now;
void DFS(int x, int Dep)
{
    if (Dep >= 9)
        return;
    Mp[x * 10 + 4] = 0;
    DFS(x * 10 + 4, Dep + 1);
    Mp[x * 10 + 7] = 0;
    DFS(x * 10 + 7, Dep + 1);
}
int main()
{
    //freopen("lucky.in", "r", stdin);
    //freopen("lucky.out", "w", stdout);
    bin[0] = 1;
    for (int i = 1; i <= 9; i++)
        bin[i] = bin[i - 1] * 10;
    DFS(0, 0);
    F[0] = 1;
    for (int i = 1; i <= 100000; i++)
    {
        F[i] = F[i - 1] * i % MOD;
    }
    int n, num = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if (Mp.count(a[i]))
        {
            Mp[a[i]]++;
        }
        else
            num++;
    }
    map<int, int>::iterator it;
    for (it = Mp.begin(); it != Mp.end(); it++)
    {
        if (it->second == 1)
            num++;
        if (it->second > 1)
            Now[it->first] = it->second;
    }
    int N = min((int)Now.size(), k);
    long long ans = 0;
    f[0][0] = 1;
    it = Now.begin();
    for (int i = 1; i <= N; it++, i++)
    {
        f[i][0] = 1;
        for (int j = 1; j <= N; j++)
        {
            f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * (it->second)) % MOD;
        }
    }
    for (int i = 0; i <= N; i++)
    {
        ans = (ans + C(num, k - i) * f[N][i]) % MOD;
    }
    printf("%lld\n", ans);
}

// Problem10423:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
bool map[1505][1505];
int dis[1505][1505];
struct Point
{
    int x, y;
} S, E, Q[20000000];
int R, C;
int movex[5] = {0, 0, 0, 1, -1},
    movey[5] = {0, 1, -1, 0, 0};
bool flag[1505][1505];
void bfs_init()
{
    //memset(flag,0,sizeof(flag));
    int l = 1, r = 0;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            if (!map[i][j])
            {
                Q[++r] = (Point){i, j};
                dis[i][j] = 0;
            }
        }
    }
    while (l <= r)
    {
        Point k = Q[l++];
        for (int i = 1; i <= 4; i++)
        {
            if (k.x + movex[i] > R || k.x + movex[i] < 1)
                continue;
            if (k.y + movey[i] > C || k.y + movey[i] < 1)
                continue;
            if (dis[k.x + movex[i]][k.y + movey[i]] > dis[k.x][k.y] + 1)
            {
                dis[k.x + movex[i]][k.y + movey[i]] = dis[k.x][k.y] + 1;
                Q[++r] = (Point){k.x + movex[i], k.y + movey[i]};
            }
        }
    }
}
int d[1505][1505];

int SPFA()
{
    memset(d, 0x3f, sizeof(d));
    d[S.x][S.y] = 0;
    int l = 1, r = 0;
    Q[++r] = S;
    //flag[S.x][S.y] = 1;
    while (l <= r)
    {
        Point k = Q[l++];
        //flag[k.x][k.y] = 0;
        for (int i = 1; i <= 4; i++)
        {
            if (k.x + movex[i] > R || k.x + movex[i] < 1)
                continue;
            if (k.y + movey[i] > C || k.y + movey[i] < 1)
                continue;
            if (d[k.x + movex[i]][k.y + movey[i]] > max(d[k.x][k.y], dis[k.x + movex[i]][k.y + movey[i]]))
            {
                d[k.x + movex[i]][k.y + movey[i]] = max(d[k.x][k.y], dis[k.x + movex[i]][k.y + movey[i]]);
                //if (!flag[k.x + movex[i]][k.y + movey[i]])
                //{
                Q[++r] = (Point){k.x + movex[i], k.y + movey[i]};
                //flag[k.x + movex[i]][k.y + movey[i]] = 1;
                //}
            }
        }
    }
    return d[E.x][E.y];
}
int main()
{
    //freopen("swan.in", "r", stdin);
    // freopen("swan.out", "w", stdout);
    char c;
    scanf("%d%d", &R, &C);
    bool flag = 0;
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            c = getchar();
            while (c != '.' && c != 'X' && c != 'L')
                c = getchar();
            if (c == 'X')
                map[i][j] = 1;
            else if (c == 'L')
            {
                if (flag)
                    E = (Point){i, j};
                else
                {
                    S = (Point){i, j};
                    flag = 1;
                }
            }
        }
    }
    bfs_init();
    printf("%d", SPFA());
    //while (1)
    ;
}

// Problem10424:/*
*@Author : WildRage
               *@Date : 2017 -
    08 - 06 17 : 57 : 21 * @Last Modified by : WildRage *@Last Modified time : 2017 - 08 - 06 18 : 07 : 40 * /
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
                                                                                               using namespace std;
struct data
{
    int h, w;
} a[2005], b[2005];
int n, A, B, C, m;
int comp(const data &a, const data &b)
{
    return a.h < b.h;
}
int cmp(const data &a, const data &b)
{
    return a.w < b.w;
}
int c[2005];
int lowbit(int x)
{
    return x & (-x);
}
void add(int x, int w)
{
    for (int i = x; i <= m; i += lowbit(i))
        c[i] += w;
}
int sum(int x)
{
    int s = 0;
    for (int i = x; i; i -= lowbit(i))
        s += c[i];
    return s;
}
int ans = 0;
void solve(int from)
{
    int h_min = a[from].h, w_min;
    int all;
    memcpy(b, a, sizeof(b));
    memset(c, 0, sizeof(c));
    sort(b + from, b + n + 1, cmp);
    int Sum[2005], Hash[2005];
    for (int i = from; i <= n; i++)
        Hash[i] = Sum[i] = b[i].h * A + b[i].w * B;
    sort(Hash + from, Hash + n + 1);
    m = unique(Hash + from, Hash + n + 1) - Hash - 1;
    for (int i = from; i <= n; i++)
    {
        int x = upper_bound(Hash + from, Hash + m + 1, Sum[i]) - Hash - 1;
        add(x, 1);
    }
    for (int i = from; i <= n; i++)
    {
        w_min = b[i].w;
        all = C + A * h_min + B * w_min;
        int x = upper_bound(Hash + from, Hash + m + 1, all) - Hash - 1;
        ans = max(ans, sum(x));
        add(upper_bound(Hash + from, Hash + m + 1, Sum[i]) - Hash - 1, -1);
    }
}
int main()
{
    //freopen("beauty.in", "r", stdin);
    //freopen("beauty.out", "w", stdout);
    scanf("%d", &n);
    scanf("%d%d%d", &A, &B, &C);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i].h, &a[i].w);
    }
    sort(a + 1, a + n + 1, comp);
    for (int i = 1; i <= n; i++)
        solve(i);
    printf("%d", ans);
}

// Problem10425:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int F[52][(1 << 8) + 1][(1 << 8) + 1], G[52][(1 << 8) + 1][(1 << 8) + 1];
int a[55][55], n, m, N;
int check(int x, int S)
{
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        if (((1 << (i - 1)) & S))
            ans += a[x][i];
    }
    return ans;
}
int Get_num(int x)
{
    int ans = 0;
    while (x)
    {
        if (x & 1)
            ans++;
        x >>= 1;
    }
    return ans;
}
int main()
{
    //freopen("proj.in", "r", stdin);
    //freopen("proj.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    memset(F, 0x3f, sizeof(F));
    N = (1 << m) - 1;
    for (int i = 0; i <= N; i++)
    {
        //if ((((i >> 1) | (i << 1) | i) & N) == N)
        //{
        int ans = check(1, i);
        F[1][0][i] = ans;
        G[1][0][i] = Get_num(i);
        //}
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= N; j++)
            for (int k = 0; k <= N; k++)
                for (int m = 0; m <= N; m++)
                    if (((j | k | m | (k << 1) | (k >> 1)) & (N)) == N)
                    {
                        if (F[i][j][k] + check(i + 1, m) < F[i + 1][k][m])
                        {
                            F[i + 1][k][m] = F[i][j][k] + check(i + 1, m);
                            G[i + 1][k][m] = G[i][j][k] + Get_num(m);
                        }
                    }
    int ans = 0x3f3f3f4f, num = 0;
    for (int i = 0; i <= N; i++)
    {
        if (F[n + 1][i][0] < ans)
        {
            ans = F[n + 1][i][0];
            num = G[n + 1][i][0];
        }
        else if (F[n + 1][i][0] == ans)
        {
            if (num > G[n + 1][i][0])
                num = G[n + 1][i][0];
        }
    }
    printf("%d %d", num, ans);
    //while (1)
    ;
}
// Problem10426:
#include <cstdio>
#include <cstring>
using namespace std;
char s[1000005];
unsigned long long base = 31;
unsigned long long has[1000005];
unsigned long long Pow(unsigned long long b, int i)
{
    unsigned long long ans = 1;
    while (i)
    {
        if (i & 1)
            ans = ans * b;
        i >>= 1;
        b = b * b;
    }
    return ans;
}
int main()
{
    //freopen("1.txt","r",stdin);
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; i++)
    {
        has[i] = has[i - 1] * base + s[i];
    }
    int ans = 0;
    for (int i = 1; i <= len; i++)
    {
        unsigned long long T = Pow(base, i);
        if (has[i] == has[len] - has[len - i] * T)
        {
            for (int j = 2; j < len - i; j++)
            {
                if (has[j + i] - has[j] * T == has[i])
                {
                    ans = i;
                    break;
                }
            }
            if (ans != i)
                break;
        }
    }
    if (ans)
    {
        for (int i = 1; i <= ans; i++)
        {
            printf("%c", s[i]);
        }
        printf("\n");
    }
    else
        puts("Just a legend");
}

// Problem10427:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <list>

using namespace std;

#define LL long long

struct data
{
    LL Num;
    int pos;
    bool operator<(const data &a) const
    {
        return Num == a.Num ? pos < a.pos : Num > a.Num;
    }
};

set<data> st;

LL a[100005];
int nex[100005], fre[100005];

LL Merge()
{
    int A = st.begin()->pos;
    LL ans = a[A];
    a[A] = -a[A];
    a[A] += a[fre[A]], a[A] += a[nex[A]];
    st.erase(st.begin());
    st.erase((data){a[fre[A]], fre[A]});
    st.erase((data){a[nex[A]], nex[A]});
    st.insert((data){a[A], A});
    if (fre[fre[A]])
        nex[fre[fre[A]]] = A;
    if (nex[nex[A]])
        fre[nex[nex[A]]] = A;
    fre[A] = fre[fre[A]];
    nex[A] = nex[nex[A]];
    return ans;
}
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        fre[i] = i - 1;
        nex[i] = i + 1;
        st.insert((data){a[i], i});
    }
    nex[n] = 0;
    a[0] = 0x8080808080808080ll;
    LL ans = 0;
    while (k--)
    {
        ans += Merge();
    }
    printf("%lld", ans);
}

// Problem10428:
#include <cstdio>
#include <cstring>
using namespace std;
#define LL long long
const LL P = 1e9 + 7;
LL pow_mod(LL a, int b)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % P;
        b >>= 1;
        a = a * a % P;
    }
    return ans;
}
LL q[1005];
int main()
{
    int n;
    scanf("%d", &n);
    LL a, b;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &a, &b);
        q[i] = a * pow_mod(b, P - 2) % P;
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++)
    {
        LL sum = 0;
        for (int j = 1; j <= n; j++)
        {
            if (j == i)
                continue;
            sum = (sum + q[j] * pow_mod(q[i] + q[j], P - 2) % P) % P;
        }
        ans = (ans + (1 + sum) * q[i]) % P;
    }
    printf("%lld", ans);
}

// Problem10429:
#include <cstdio>
#include <algorithm>
using namespace std;
int in[1000005], out[1000005];
long long Sum = 0;
int main()
{
    int n, m, a, b, c;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        out[a] += c;
        in[b] += c;
        Sum += c;
    }
    for (int i = 1; i <= n; i++)
    {
        Sum -= min(out[i], in[i]);
    }
    printf("%lld\n", Sum);
    //while (1)
}
// Problem10430:
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
struct Node
{
    Node *ch[2];
    int s, id, key;
    Node(int x)
    {
        key = rand();
        id = x;
        s = 1;
        ch[0] = ch[1] = NULL;
    }
#define size(_) ((_) ? (_)->s : 0)
    void Update()
    {
        s = size(ch[1]) + size(ch[0]) + 1;
    }
} * root;
Node *Merge(Node *A, Node *B)
{
    if (!A)
        return B;
    if (!B)
        return A;
    if (A->key < B->key)
    {
        A->ch[1] = Merge(A->ch[1], B);
        A->Update();
        return A;
    }
    else
    {
        B->ch[0] = Merge(A, B->ch[0]);
        B->Update();
        return B;
    }
}
typedef pair<Node *, Node *> DNode;
DNode Split(Node *rt, int k)
{
    if (!rt)
        return DNode(NULL, NULL);
    DNode o;
    if (size(rt->ch[0]) >= k)
    {
        o = Split(rt->ch[0], k);
        rt->ch[0] = o.second;
        rt->Update();
        o.second = rt;
    }
    else
    {
        o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
        rt->ch[1] = o.first;
        rt->Update();
        o.first = rt;
    }
    return o;
}
void Insert(int x, int k)
{
    DNode y = Split(root, k);
    Node *n = new Node(x);
    root = Merge(y.first, Merge(n, y.second));
}
int Ind = 0;
int a[100005];
void DFS(Node *rt)
{
    if (rt)
    {
        DFS(rt->ch[0]);
        a[rt->id] = ++Ind;
        DFS(rt->ch[1]);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int c;
    Insert(1, 0);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &c);
        Insert(i, c);
    }
    DFS(root);
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", a[i]);
    }
    //while(1);
}
// Problem10431:
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
inline int read()
{
    int s = 0, k = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        k = ch == '-' ? -1 : k, ch = getchar();
    while (ch >= '0' && ch <= '9')
        s = s * 10 + (ch ^ 48), ch = getchar();
    return s * k;
}
int n;
bool Sum[4000005];
bool f[4000005];
bool a[4000005];
int main()
{
    n = read();
    int t = 0, op, l, r;
    int lastans = 0;
    while (n--)
    {
        op = read();
        if (op == 1)
        {
            l = read() ^ lastans;
            t++;
            a[t] = l;
            if (t == 1)
                f[t] = a[t];
            else
                f[t] = !(f[t - 1] & l);
            Sum[t] = Sum[t - 1] ^ f[t];
        }
        else
        {
            l = read(), r = read();
            if (lastans)
            {
                l = t - l + 1;
                r = t - r + 1;
                swap(l, r);
            }
            lastans = a[l];
            int i = l, now = !(a[l] & a[l + 1]);
            while (now != f[i + 1] && i < r)
            {
                lastans ^= now;
                i++;
                now = !(now & a[i + 1]);
            }
            if (i < r)
            {
                lastans ^= Sum[r] ^ Sum[i];
            }
            printf("%d\n", lastans);
        }
    }
    //while (1);
}

// Problem10432:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long Sum[2][300005];
#define lowbit(_) ((_) & (-_))
int n;
void add(int p, int x, int w)
{
    for (int i = x; i <= n; i += lowbit(i))
        Sum[p][i] += w;
}
long long Gsum(int p, int x)
{
    long long ans = 0;
    for (int i = x; i; i -= lowbit(i))
        ans += Sum[p][i];
    return ans;
}
int a[300005], Hash[300005];
int main()
{
    scanf("%d", &n);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i] = a[i];
    }
    sort(Hash + 1, Hash + n + 1);
    int tot = unique(Hash + 1, Hash + n + 1) - Hash - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(Hash + 1, Hash + tot + 1, a[i]) - Hash;
    for (int i = 1; i <= n; i++)
    {
        int x = Gsum(0, a[i] - 1);
        add(0, a[i], 1);
        ans += Gsum(1, a[i] - 1);
        add(1, a[i], x);
    }
    printf("%lld\n", ans);
}
// Problem10433:
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
struct data
{
    int a, pos;
    bool operator<(const data &b) const
    {
        return a == b.a ? pos < b.pos : a < b.a;
    }
} a[2005];
int comp(const data &a, const data &b)
{
    return a.pos < b.pos;
}
int full = 13;
struct Trie
{
    struct Trie_Node
    {
        Trie_Node *ch[2];
        int s;
        Trie_Node()
        {
            ch[0] = ch[1] = NULL;
            s = 0;
        }
    } * root[2005], *null;
    Trie()
    {
        null = new Trie_Node();
        null->ch[0] = null->ch[1] = null;
        root[0] = new Trie_Node();
        root[0]->ch[1] = root[0]->ch[0] = null;
    }
    Trie_Node *NewNode()
    {
        Trie_Node *rt = new Trie_Node();
        rt->ch[0] = rt->ch[1] = null;
        return rt;
    }
    void copy(Trie_Node *&a, Trie_Node *b)
    {
        if (b == null)
            a = null;
        else
            a = NewNode(), *a = *b;
    }
    void Insert(int x, int cnt)
    {
        copy(root[cnt], root[cnt - 1]);
        Trie_Node *rt1 = root[cnt], *rt2 = root[cnt - 1];
        for (int i = full; i >= 0; i--)
        {
            int k = (x >> i) & 1;
            copy(rt1->ch[k], rt2->ch[k]);
            if (rt1->ch[k] == null)
                rt1->ch[k] = NewNode();
            rt1 = rt1->ch[k], rt2 = rt2->ch[k];
            rt1->s++;
        }
    }
    int kth(int k, int l, int r)
    {
        int res = 0;
        Trie_Node *rt1 = root[r], *rt2 = root[l - 1];
        for (int i = full; i >= 0; i--)
        {
            if (k > rt1->ch[0]->s - rt2->ch[0]->s)
            {
                k -= (rt1->ch[0]->s - rt2->ch[0]->s);
                res |= (1 << i);
                rt1 = rt1->ch[1], rt2 = rt2->ch[1];
            }
            else
            {
                rt1 = rt1->ch[0], rt2 = rt2->ch[0];
            }
        }
        return res;
    }
} root;
int pos[2005];
int Maxn[2005 << 2];
int Max[2005 << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void Update(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        Max[rt] = Maxn[l];
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    Update(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Max[rt];
    int m = l + r >> 1;
    int MAX = 0;
    if (L <= m)
        MAX = max(MAX, Query(L, R, lch));
    if (R > m)
        MAX = max(MAX, Query(L, R, rch));
    return MAX;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i].a);
        a[i].pos = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    {
        a[i].a = i;
        pos[a[i].a] = a[i].pos;
    }
    sort(a + 1, a + n + 1, comp);
    for (int i = 1; i <= n; i++)
        root.Insert(a[i].a, i);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if ((i - j + 1) & 1)
            {
                int k = pos[root.kth((i - j + 1) / 2 + 1, j, i)];
                Maxn[k] = max(Maxn[k], (i - j + 1));
            }
        }
    }
    buildtree(1, n, 1);
    int Q, l, r;
    scanf("%d", &Q);
    while (Q--)
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", Query(l, r, 1, n, 1));
    }
}

// Problem10434:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
#define LL long long
LL f[55], Sum[55];
int a[55];
bool mark[55];
int main()
{
    LL n, k;
    scanf("%lld%lld", &n, &k);
    f[0] = f[1] = f[2] = 1;
    Sum[0] = 1, Sum[1] = 2, Sum[2] = 3;
    for (int i = 3; i <= n; i++)
    {
        f[i] = f[i - 1] + f[i - 2];
        Sum[i] = Sum[i - 1] + f[i];
    }
    for (int i = 1; i <= n; i++)
        a[i] = i;
    while (k > 1)
    {
        int j = lower_bound(Sum, Sum + n + 1, k) - Sum - 1;
        k -= Sum[j];
        mark[n - j - 1] = mark[n - j] = 1;
    }
    for (int i = 1; i <= n; i++)
        if (mark[i] && mark[i + 1])
            mark[i] = mark[i + 1] = 0, swap(a[i], a[i + 1]);
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    //while (1)
    ;
}

// Problem10435:/**
*******************************************************************************@file Evensgn
                                                                                  *@author WildRage
                                                                                      *@version v 1.0 *
        @date 2017 -
    5 - 10 10 : 55 : 23 * @brief ******************************************************************************* /
#include <cstdio>
#include <cstring>
#include <vector>
            const int P = 1e9 + 7;
namespace Mine_WorkSpace
{
struct data
{
    struct edge
    {
        int END, next;
    } v[200005];
    int first[100005], p;
    data()
    {
        memset(first, -1, sizeof(first));
        p = 0;
    }
    void add(int a, int b)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
} Edge;
bool color[100005];
long long f[100005][2];
void DP(int rt, int fa)
{
    f[rt][0] = 1;
    f[rt][1] = 0;
    for (int i = Edge.first[rt]; i != -1; i = Edge.v[i].next)
    {
        if (fa != Edge.v[i].END)
        {
            DP(Edge.v[i].END, rt);
            f[rt][1] = (f[rt][1] * f[Edge.v[i].END][0]) % P;
            f[rt][1] = (f[rt][1] + f[Edge.v[i].END][1] * f[rt][0]) % P;
            f[rt][0] = (f[rt][0] * f[Edge.v[i].END][0]) % P;
        }
    }
    if (color[rt])
        f[rt][1] = f[rt][0];
    else
        f[rt][0] = (f[rt][1] + f[rt][0]) % P;
}
int Main()
{
    int n;
    scanf("%d", &n);
    int a, b;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &b);
        Edge.add(i + 1, b + 1), Edge.add(b + 1, i + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        if (a)
            color[i] = 1;
    }
    DP(1, 0);
    printf("%lld\n", f[1][1]);
    // Print_tree(1);
    // while(1);
}
}
int main() { Mine_WorkSpace::Main(); }

// Problem10436:/**
*******************************************************************************@file Wulala
                                                                                  *@author WildRage
                                                                                      *@version v 0.9 *
        @date 2017 -
    8 - 10 10 : 58 : 12 * @brief ******************************************************************************* /
#include <cstdio>
#include <cstring>
#include <algorithm>
            using namespace std;
const int N = 100001, M = 301;
int a[N], in[N], n, m;
int Sum[500][305], Change[500];
int block;
int lp[500], rp[500];
int Query(int l, int r)
{
    int L = in[l], R = in[r];
    int ans = 0;
    bool flag = 0;
    if (L == R)
    {
        if (Change[L])
            return r - l;
        for (int i = l + 1; i <= r; i++)
        {
            if (a[i] == a[l])
                ans++;
            a[i] = a[l];
        }
        for (int i = lp[L]; i < l; i++)
            if (a[i] != a[l])
            {
                flag = 1;
                break;
            }
        if (flag == 1)
            return ans;
        for (int i = r + 1; i <= rp[R]; i++)
        {
            if (a[i] != a[l])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            Change[L] = a[l];
        return ans;
    }
    else
    {
        if (Change[L] == a[l])
            ans += (rp[L] - l);
        else
        {
            flag = 0;
            for (int i = l + 1; i <= rp[L]; i++)
            {
                if (a[i] == a[l])
                    ans++;
                a[i] = a[l];
            }
            for (int i = lp[L]; i < l; i++)
                if (a[i] != a[l])
                {
                    flag = 1;
                    break;
                }
            if (!flag)
                Change[L] = a[l];
        }
        if (Change[R])
        {
            if (Change[R] == a[l])
                ans += (r - lp[R] + 1);
            else
            {
                for (int i = lp[R]; i <= r; i++)
                    a[i] = a[l];
                Change[R] = 0;
            }
        }
        else
        {
            flag = 0;
            for (int i = lp[R]; i <= r; i++)
            {
                if (a[i] == a[l])
                    ans++;
                a[i] = a[l];
            }
            for (int i = r + 1; i <= rp[R]; i++)
                if (a[i] != a[l])
                {
                    flag = 1;
                    break;
                }
            if (!flag)
                Change[R] = a[l];
        }
        for (int i = L + 1; i < R; i++)
        {
            if (Change[i])
            {
                if (Change[i] == a[l])
                    ans += block;
                else
                {
                    for (int j = lp[i]; j <= rp[i]; j++)
                        a[j] = a[l];
                    Change[i] = a[l];
                }
            }
            else
            {
                for (int j = lp[i]; j <= rp[i]; j++)
                {
                    if (a[j] == a[l])
                        ans++;
                    a[j] = a[l];
                }
                Change[i] = a[l];
            }
        }
        return ans;
    }
}
int main()
{
    int c, b;
    scanf("%d%d", &n, &m);
    block = 316;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        in[i] = (i - 1) / block + 1;
        Sum[in[i]][a[i]]++;
    }
    for (int i = 1; i <= in[n]; i++)
        lp[i] = (i - 1) * block + 1, rp[i] = min(n, i * block);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &c, &b);
        int ans = Query(c, b);
        printf("%d\n", ans);
    }
}
// Problem10437:/**
*******************************************************************************@file Function
                                                                                  *@author WildRage
                                                                                      *@version v 1.0 *
        @date 2017 -
    8 - 10 10 : 57 : 28 * @brief ******************************************************************************* /
#include <cstdio>
#include <cstring>
#include <algorithm>
            using namespace std;
#define LL long long
LL a[1005], b[1005], c[1005];
LL Max[200005];
int fix = 100001;
int main()
{
    memset(Max, 0x80, sizeof(Max));
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
    }
    LL u;
    for (int i = -100000; i <= 100000; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            Max[i + fix] = max(Max[i + fix], a[j] * i * i + b[j] * i + c[j]);
        }
    }
    while (q--)
    {
        scanf("%lld", &u);
        printf("%lld\n", Max[u + fix]);
    }
    return 0;
}

// Problem10438:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct data
{
    int s, e, v, op;
    bool operator<(const data &a) const
    {
        return v == a.v ? op < a.op : v < a.v;
    }
} a[300005];
int father[100005];
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
int size[100005], ans[200005];
int main()
{
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a[i].s, &a[i].e, &a[i].v);
        a[i].op = 0;
    }
    for (int i = m + 1; i <= q + m; i++)
    {
        scanf("%d%d", &a[i].s, &a[i].v);
        a[i].op = 1;
        a[i].e = i - m;
    }
    for (int i = 1; i <= n; i++)
        father[i] = i, size[i] = 1;
    sort(a + 1, a + q + m + 1);
    for (int i = 1; i <= m + q; i++)
    {
        if (a[i].op == 1)
        {
            ans[a[i].e] = size[find(a[i].s)];
        }
        else
        {
            if (find(a[i].e) != find(a[i].s))
            {
                size[find(a[i].e)] += size[find(a[i].s)];
                father[find(a[i].s)] = find(a[i].e);
            }
        }
    }
    for (int i = 1; i <= q; i++)
    {
        printf("%d\n", ans[i]);
    }
}
// Problem10439:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int v[305][305];
int a[1000005];
int pre[1000005], nxt[1000005];
bool die[1000005];
int n, c;
int val[1000005];
inline bool Judge()
{
    int last = -1;
    for (int i = nxt[0]; i <= n; i = nxt[i])
    {
        if (last == -1)
            last = a[i];
        if (last != a[i])
            return 1;
    }
    return 0;
}
inline void Delete(int x)
{
    pre[nxt[x]] = pre[x];
    nxt[pre[x]] = nxt[x];
}
int main()
{
    scanf("%d%d", &c, &n);
    for (int i = 1; i <= c; i++)
        for (int j = 1; j <= c; j++)
            scanf("%d", &v[i][j]);
    for (int i = 1; i <= n; i++)
        val[i] = 1;
    nxt[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        pre[i] = i - 1;
        nxt[i] = i + 1;
    }
    while (Judge())
    {
        for (int i = nxt[0]; i <= n; i = nxt[i])
            val[i] += v[a[i]][a[nxt[i]]] + v[a[i]][a[pre[i]]];
        for (int i = nxt[0]; i <= n; i = nxt[i])
            if (val[i] <= 0)
                Delete(i);
    }
    printf("%d\n", a[nxt[0]]);
    //while (1)
    ;
}

// Problem10440:
#include <cstdio>
#include <cstring>
using namespace std;
const int full = 20;
int a[2005];
int kth[2005], Sum[2005][2005];
int main(int argc, char const *argv[])
{
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            kth[j] = 1;
            for (int k = i; k < j; k++)
            {
                if (a[k] < a[j])
                    kth[k]++;
                else
                    kth[j]++;
                ++Sum[a[k]][kth[k]];
            }
            ++Sum[a[j]][kth[j]];
        }
    }
    int k, x;
    while (q--)
    {
        scanf("%d%d", &k, &x);
        printf("%d\n", Sum[x][k]);
    }
    return 0;
}

// Problem10441:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = (int)1e6 + 5;
int ord[maxn], n;
long long x;
bool used[maxn];
int haha()
{
    scanf("%d%lld", &n, &x);
    long long res = 1ll * (n - 1) * (n - 2) / 2;
    if (res < x)
    {
        puts("-1");
        return 0;
    }
    int cur = 1, cn = 1, nn = 1;
    while (res > x)
    {
        long long tmp = res - x;
        if (tmp >= n - 1 - cn)
        {
            ord[cur] = cn;
            used[cn] = 1;
            res -= n - 1 - cn;
            cn++;
            cur++;
            nn = cn;
        }
        else
            for (; nn < n - 1; nn++)
            {
                if (!used[nn] && n - 1 - nn <= tmp)
                {
                    ord[cur] = nn;
                    used[nn] = 1;
                    res -= n - 1 - nn;
                    cur++;
                    break;
                }
            }
    }
    ord[cur] = n;
    ord[n] = n - 1;
    cur++;
    used[n] = used[n - 1] = 1;
    int now = 1;
    while (cur < n)
        for (; now <= n; now++)
            if (!used[now])
            {
                used[now] = 1;
                ord[cur] = now;
                cur++;
                break;
            }
    for (int i = 1; i <= n; i++)
        printf("%d ", ord[i]);
}
int sb = haha();
int main() { ; }
// Problem10441:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
LL Sum[1000005];
LL x;
int ans[1000005];
int main()
{
    int n;
    scanf("%d%lld", &n, &x);
    for (int i = n - 2; i >= 0; i--)
        Sum[i] = Sum[i + 1] + i;
    if (Sum[0] < x)
    {
        puts("-1");
        return 0;
    }
    int k, i, j;
    for (k = 1; k <= n - 2; k++)
        if (x > Sum[k])
            break;
    x = x - Sum[k];
    for (i = n - k, j = 1; i <= n - 1; i++, j++)
        ans[j] = i;
    for (i = 1; i <= n - k - 1; i++, j++)
        ans[j] = i;
    ans[n] = n;
    i = 1;
    while (x--)
    {
        swap(ans[i], ans[i + 1]);
        i++;
    }
    for (i = 1; i < n; i++)
        printf("%d ", ans[i]);
    printf("%d\n", ans[n]);
}

// Problem10442:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
const LL P = 1e9 + 7;
LL F[100005];
void Init()
{
    F[0] = 1;
    for (int i = 1; i <= 100000; i++)
        F[i] = i * F[i - 1] % P;
}
LL pow_mod(LL a, int b)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % P;
        b >>= 1;
        a = a * a % P;
    }
    return ans;
}
LL C(int n, int m)
{
    if (m > n || m < 0)
        return 0;
    return F[n] * pow_mod(F[m] * F[n - m] % P, P - 2) % P;
}
LL a[100005], Has[100005];
int Sum[100005], n;

#define lowbit(_) ((_) & (-_))

void add(int x, int c)
{
    for (int i = x; i <= n; i += lowbit(i))
        Sum[i] += c;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
int fron[100005], nxt[100005];
int main()
{
    Init();
    int K;
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    sort(a + 1, a + n + 1);
    LL ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = (ans + a[i] * C(i - 1, K - 1)) % P;
    }
    printf("%lld\n", ans);
}

// Problem10443:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Tree
{
    int ch[2];
    int v;
} Node[100005];
int a[100005], Ind, val[100005], c[100005];
void dfs(int rt)
{
    if (rt)
    {
        dfs(Node[rt].ch[0]);
        a[++Ind] = Node[rt].v;
        dfs(Node[rt].ch[1]);
    }
}
int f[100005], Max[100005];
int tot;
inline int lowbit(int x) { return x & (-x); }
void Update(int x, int val)
{
    for (int i = x; i <= tot; i += lowbit(i))
        Max[i] = max(Max[i], val);
    return;
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i; i -= lowbit(i))
        ans = max(ans, Max[i]);
    return ans;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &Node[i].v);
    }
    int fa, d;
    for (int i = 2; i <= n; i++)
    {
        scanf("%d%d", &fa, &d);
        Node[fa].ch[d] = i;
    }
    dfs(1);
    //memset(f, 0x7f, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        a[i] = a[i] - i;
        c[i] = a[i];
    }
    int ans = 0;
    sort(a + 1, a + n + 1);
    tot = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= n; i++)
    {
        int now = lower_bound(a + 1, a + tot + 1, c[i]) - a;
        f[i] = Query(now) + 1;
        Update(now, f[i]);
        ans = max(ans, f[i]);
    }
    printf("%d", n - ans);
    //while(1);
}
// Problem10444:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[300005][2][2], a[300005];
bool change[300005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    a[0] = -1;
    int ans = 0;
    f[1][0][0] = 1;
    f[1][0][1] = 0;
    f[1][1][1] = 1;
    f[1][1][0] = 0;
    for (int i = 2; i <= n; i++)
    {
        f[i][0][0] = 1;
        f[i][0][1] = 1;
        f[i][1][1] = 1;
        f[i][1][0] = 0;
        if (a[i] > a[i - 1])
        {
            f[i][0][0] = f[i - 1][0][0] + 1;
            f[i][0][1] = f[i - 1][0][1] + 1;
        }
        if (f[i - 1][1][1] == f[i - 2][0][0] + 1)
        {
            if (a[i] > a[i - 2] + 1)
            {
                f[i][0][1] = max(f[i][0][1], f[i - 1][1][1] + 1);
            }
        }
        else
        {
            f[i][0][1] = max(f[i][0][1], f[i - 1][1][1]);
        }
        f[i][1][1] = max(f[i][1][1], f[i - 1][0][0] + 1);
        ans = max(ans, max(f[i][0][0], max(f[i][0][1], f[i][1][1])));
    }
    printf("%d", ans);
}

// Problem10445:
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int a[500005], b[500005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    a[n + 1] = a[n];
    int i = 1, l, r;
    int ans = 0;
    while (i <= n)
    {
        while (i <= n && a[i] == a[i + 1])
        {
            b[i] = a[i];
            i++;
        }
        l = i;
        while (i <= n && a[i] != a[i + 1])
            i++;
        r = i;
        int len = (r - l + 1);
        if (len & 1)
            for (int j = l; j <= r; j++)
                b[j] = a[l];
        else
            for (int j = 1; j * 2 <= len; j++)
                b[l + j - 1] = a[l], b[r - j + 1] = a[r];
        ans = max(ans, (len - 1) / 2);
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        printf("%d ", b[i]);
    //while(1);
}

// Problem10448:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int fa1[1000005], fa2[1000005];
long long w1[1000005], w2[1000005];
long long Min1[1000005], Min2[1000005];
struct Point
{
    int x, y, v;
} a[1000005];
bool cmpx(const Point &A, const Point &B)
{
    return A.x < B.x;
}
bool cmpy(const Point &A, const Point &B)
{
    return A.y < B.y;
}
int find1(int x)
{
    if (x == fa1[x])
        return x;
    int rt = find1(fa1[x]);
    w1[x] += w1[fa1[x]];
    return fa1[x] = rt;
}
int find2(int x)
{
    if (x == fa2[x])
        return x;
    int rt = find2(fa2[x]);
    w2[x] += w2[fa2[x]];
    return fa2[x] = rt;
}
bool link1(int a, int b, int w)
{
    if (find1(a) != find1(b))
    {
        int fa = find1(a), fb = find1(b);
        fa1[fa] = fa1[fb];
        w1[fa] = w + w1[b] - w1[a];
        return 1;
    }
    else
        return w1[a] == w + w1[b];
}
bool link2(int a, int b, int w)
{
    if (find2(a) != find2(b))
    {
        int fa = find2(a), fb = find2(b);
        fa2[fa] = fa2[fb];
        w2[fa] = w + w2[b] - w2[a];
        return 1;
    }
    else
        return w2[a] == w + w2[b];
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        bool flag = 1;
        int R, C;
        scanf("%d%d", &R, &C);
        for (int i = 1; i <= R; i++)
        {
            fa1[i] = i;
            w1[i] = 0;
        }
        for (int i = 1; i <= C; i++)
        {
            fa2[i] = i;
            w2[i] = 0;
        }
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].v);
        for (int i = 1; i <= n; i++)
            if (a[i].v < 0)
                flag = 0;
        sort(a + 1, a + n + 1, cmpx);
        for (int i = 1; i < n; i++)
            if (a[i].x == a[i + 1].x)
                if (!link2(a[i].y, a[i + 1].y, a[i + 1].v - a[i].v))
                    flag = false;

        sort(a + 1, a + n + 1, cmpy);
        for (int i = 1; i < n; i++)
            if (a[i].y == a[i + 1].y)
                if (!link1(a[i].x, a[i + 1].x, a[i + 1].v - a[i].v))
                    flag = false;

        memset(Min1, 0x3f, sizeof(Min1));
        memset(Min2, 0x3f, sizeof(Min2));
        for (int i = 1; i <= n; i++)
        {
            int rt = find1(a[i].x);
            Min1[rt] = min(Min1[rt], a[i].v + w1[a[i].x]);
        }
        for (int i = 1; i <= R; i++)
        {
            int rt = find1(i);
            Min2[rt] = min(Min2[rt], -w1[i]);
        }
        for (int i = 1; i <= R; i++)
        {
            if (fa1[i] == i && Min1[i] + Min2[i] < 0)
                flag = 0;
        }
        if (flag)
            puts("Yes");
        else
            puts("No");
    }
}
// Problem10449:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int Dis(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
void change(int &dx, int &dy)
{
    int x1 = 2 * (dx + dy) - 2, x2 = 4 * dx - 4, x3 = 4 * dy - 4;
    int Max = max(x1, max(x2, x3));
    if (x1 == Max)
        dx--, dy--;
    else if (x2 == Max)
        dx -= 2;
    else
        dy -= 2;
    return;
}
int main()
{
    int T;
    int a, b;
    scanf("%d", &T);
    scanf("%d%d", &a, &b);
    while (T--)
    {
        int x1, x2, y1, y2, c, d;
        scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &c, &d);
        int dis = Dis(x1, y1, x2, y2);
        int dx = abs(x2 - x1), dy = abs(y1 - y2);
        int flag = 0;
        for (; dis > 0; dis -= 2)
        {
            if (c >= a)
            {
                d -= dx * dx + dy * dy;
                c -= a;
            }
            else
                c += b;
            change(dx, dy);
            if (d <= 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag)
            printf("NAIVE\n");
        else
            printf("SIMPLE\n");
    }
}
// Problem10450:
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
char c[] = {0, 'e', 'r', 'e', 'w', 'r', 'w', 'e', 'r', 'w', 'e', 'r', '\0'};
char s[100005];
long long MOD = 1e9 + 7;
long long f[100005][15];
int m = 11, n;
int main()
{
    //freopen("ere.in","r",stdin);
    // freopen("ere.out","w",stdout);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i][0] = 1;
        for (int j = 1; j <= m; j++)
            if (s[i] == c[j])
                f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % MOD;
            else
                f[i][j] = f[i - 1][j];
    }
    printf("%lld\n", f[n][m]);
    //while (1);
}

// Problem10452:
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int a[55][55];
int sum[55][55];
int f[55][55][505];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n - i + 1; j++)
        {
            scanf("%d", &a[i][j]);
            sum[j][i] = sum[j][i - 1] + a[i][j];
        }
    int ans = 0;
    for (int i = n; i >= 1; i--)
    {
        for (int j = 0; j <= n - i + 1; j++)
        {
            for (int k = max(0, j - 1); k <= n - i; k++)
            {
                for (int s = j * (j + 1) / 2; s <= m; s++)
                {
                    f[i][j][s] = max(f[i][j][s], f[i + 1][k][s - j] + sum[i][j]);
                }
            }
            ans = max(f[i][j][m], ans);
        }
    }
    printf("%d", ans);
}
// Problem10454:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long a[10005];
long long f[10005][(1 << 10) + 1];
int Get_Num(int x)
{
    int ans = 0;
    while (x)
    {
        if (x & 1)
            ans++;
        x >>= 1;
    }
    return ans;
}
long long all;
int main()
{
    //freopen("1.in","r",stdin);
    int n, k, Min, Max;
    scanf("%d%d%d%d", &n, &k, &Min, &Max);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        all += a[i];
    }
    //printf("%lld\n",all);
    memset(f, 0xF0, sizeof(f));
    int N = (1 << k) - 1;
    for (int i = 0; i <= N; i++)
    {
        int Num = Get_Num(i);
        if (Num >= Min && Num <= Max)
        {
            f[k][i] = 0;
            for (int j = 1; j <= k; j++)
            {
                if (i & (1 << (j - 1)))
                    f[k][i] += a[k - j + 1];
            }
        }
    }
    for (int i = k + 1; i <= n; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            int Num = Get_Num(j);
            if (Num >= Min && Num <= Max)
            {
                f[i][j] = f[i - 1][j >> 1] + ((j & 1) ? a[i] : 0);
                f[i][j] = max(f[i][j], f[i - 1][(j >> 1) | (1 << (k - 1))] + ((j & 1) ? a[i] : 0));
            }
        }
    }
    long long Maxans = 0xf0f0f0f0f0f0f0f0ll;
    for (int i = 0; i <= N; i++)
        if (Get_Num(i) >= Min && Get_Num(i) <= Max)
            Maxans = max(Maxans, f[n][i]);
    printf("%lld", Maxans - (all - Maxans));
    //while(1);
}

// Problem10456:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next;
} v[2000005];
int first[1000005], p;
int vis[1000005], links[1000005];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
bool find(int x, int k)
{
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END] != k)
        {
            vis[v[i].END] = k;
            if (links[v[i].END] == -1 || find(links[v[i].END], k))
            {
                links[v[i].END] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    memset(first, -1, sizeof(first));
    memset(links, -1, sizeof(links));
    int n;
    scanf("%d", &n);
    int a, b;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, i);
        add(b, i);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (find(i, i))
            ans++;
        else
            break;
    }
    printf("%d", ans);
}
// Problem10457:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100005][5], ans;
int N, D, K;
bool mark[100005];
int ansl;
bool check(int x)
{
    for (int i = 1; i <= D; i++)
        if (mark[a[x][i]])
            return 1;
    return 0;
}
void dfs(int L, int R, int l, int r, int k)
{
    while (r < R && check(r + 1))
        r++;
    while (l > L && check(l - 1))
        l--;
    if (ans < r - l + 1 || (ans == r - l + 1 && ansl > l))
    {
        ans = r - l + 1;
        ansl = l;
    }
    if (k == K)
        return;
    if (r + 1 <= R)
    {
        for (int i = 1; i <= D; i++)
        {
            if (!mark[a[r + 1][i]])
            {
                mark[a[r + 1][i]] = 1;
                dfs(L, R, l, r + 1, k + 1);
                mark[a[r + 1][i]] = 0;
            }
        }
    }
    if (l - 1 >= L)
    {
        for (int i = 1; i <= D; i++)
        {
            if (!mark[a[l - 1][i]])
            {
                mark[a[l - 1][i]] = 1;
                dfs(L, R, l - 1, r, k + 1);
                mark[a[l - 1][i]] = 0;
            }
        }
    }
}
void Binary_Search(int l, int r)
{
    if (l > r)
        return;
    int mid = l + r >> 1;
    for (int i = 1; i <= D; i++)
    {
        mark[a[mid][i]] = 1;
        dfs(l, r, mid, mid, 1);
        mark[a[mid][i]] = 0;
    }
    Binary_Search(l, mid - 1);
    Binary_Search(mid + 1, r);
}
int main()
{
    int T;
    scanf("%d", &T);
    int num = 0;
    while (T--)
    {
        num++;
        scanf("%d%d%d", &N, &D, &K);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= D; j++)
                scanf("%d", &a[i][j]);
        ans = 0, ansl = 0x3f3f3f;
        Binary_Search(1, N);
        printf("Case #%d: %d %d\n", num, ansl - 1, ans + ansl - 2);
    }
}
// Problem10457:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100005][5], ans;
int N, D, K;
bool mark[100005];
int ansl;
bool check(int x)
{
    for (int i = 1; i <= D; i++)
        if (mark[a[x][i]])
            return 1;
    return 0;
}
void dfs(int L, int R, int l, int r, int k)
{
    while (r < R && check(r + 1))
        r++;
    while (l > L && check(l - 1))
        l--;
    if (ans < r - l + 1 || (ans == r - l + 1 && ansl > l))
    {
        ans = r - l + 1;
        ansl = l;
    }
    if (k == K)
        return;
    if (r + 1 <= R)
    {
        for (int i = 1; i <= D; i++)
        {
            if (!mark[a[r + 1][i]])
            {
                mark[a[r + 1][i]] = 1;
                dfs(L, R, l, r + 1, k + 1);
                mark[a[r + 1][i]] = 0;
            }
        }
    }
    if (l - 1 >= L)
    {
        for (int i = 1; i <= D; i++)
        {
            if (!mark[a[l - 1][i]])
            {
                mark[a[l - 1][i]] = 1;
                dfs(L, R, l - 1, r, k + 1);
                mark[a[l - 1][i]] = 0;
            }
        }
    }
}
void Binary_Search(int l, int r)
{
    int mid = l + r >> 1;
    for (int i = 1; i <= D; i++)
    {
        mark[a[mid][i]] = 1;
        dfs(l, r, mid, mid, 1);
        mark[a[mid][i]] = 0;
    }
    if (l == r)
        return;
    Binary_Search(l, mid);
    Binary_Search(mid + 1, r);
}
int main()
{
    int T;
    scanf("%d", &T);
    int num = 0;
    while (T--)
    {
        num++;
        scanf("%d%d%d", &N, &D, &K);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= D; j++)
                scanf("%d", &a[i][j]);
        ans = 0, ansl = 0x3f3f3f;
        Binary_Search(1, N);
        printf("Case #%d: %d %d\n", num, ansl - 1, ans + ansl - 2);
    }
}
// Problem10459:
#pragma GCC optimize("O3")
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int Max_Morale[30005], Max_Solidarity[30005];
struct Point
{
    int x, y;
    Point(int a = 0, int b = 0)
    {
        x = a, y = b;
    }
    bool operator==(const Point &a) const
    {
        return x == a.x && y == a.y;
    }
};
struct data
{
    int x, ID;
    data(int a = 0, int b = 0)
    {
        x = a, ID = b;
    }
    bool operator>(const data &a) const
    {
        return x == a.x ? ID > a.ID : x > a.x;
    }
    bool operator<=(const data &a) const
    {
        return !(*this > a);
    }
};
struct Treap
{
    struct Node
    {
        int s, key, Max_Num, Max_Size;
        data x;
        Node *ch[2];
        Node(data sa)
        {
            ch[0] = ch[1] = NULL;
            s = 1, x = sa, key = rand();
            Max_Num = Max_Size = 0;
        }
#define size(_) ((_) ? (_)->s : 0)
        void Pushup()
        {
            s = size(ch[0]) + size(ch[1]) + 1;
        }
        void Pushdown()
        {
            if (ch[0])
            {
                ch[0]->Max_Num = max(ch[0]->Max_Num, Max_Num);
                ch[0]->Max_Size = max(ch[0]->Max_Size, Max_Size);
                Max_Morale[ch[0]->x.ID] = max(Max_Morale[ch[0]->x.ID], ch[0]->Max_Num);
                Max_Solidarity[ch[0]->x.ID] = max(Max_Solidarity[ch[0]->x.ID], ch[0]->Max_Size);
            }
            if (ch[1])
            {
                ch[1]->Max_Num = max(ch[1]->Max_Num, Max_Num);
                ch[1]->Max_Size = max(ch[1]->Max_Size, Max_Size);
                Max_Morale[ch[1]->x.ID] = max(Max_Morale[ch[1]->x.ID], ch[1]->Max_Num);
                Max_Solidarity[ch[1]->x.ID] = max(Max_Solidarity[ch[1]->x.ID], ch[1]->Max_Size);
            }
            Max_Num = Max_Size = 0;
        }
    } * root;
    Treap()
    {
        root = NULL;
    }
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
        if (A->key < B->key)
        {
            A->Pushdown();
            A->ch[1] = Merge(A->ch[1], B);
            A->Pushup();
            return A;
        }
        else
        {
            B->Pushdown();
            B->ch[0] = Merge(A, B->ch[0]);
            B->Pushup();
            return B;
        }
    }
    typedef pair<Node *, Node *> DNode;
    DNode Split(Node *rt, int k)
    {
        if (!rt)
            return DNode(NULL, NULL);
        DNode o;
        rt->Pushdown();
        if (size(rt->ch[0]) >= k)
        {
            o = Split(rt->ch[0], k);
            rt->ch[0] = o.second;
            rt->Pushup();
            o.second = rt;
        }
        else
        {
            o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
            rt->ch[1] = o.first;
            rt->Pushup();
            o.first = rt;
        }
        return o;
    }
    Node *kth(int k)
    {
        DNode x = Split(root, k - 1);
        DNode y = Split(x.second, 1);
        Node *ans = y.first;
        root = Merge(Merge(x.first, ans), y.second);
        return ans;
    }
    int Rank(Node *rt, data x)
    {
        if (!rt)
            return 0;
        return x <= rt->x ? Rank(rt->ch[0], x) : Rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
    }
    void Insert(data x)
    {
        int k = Rank(root, x);
        if (root)
        {
            root->Max_Size = max(root->Max_Size, size(root));
            root->Max_Num = max(root->Max_Num, x.x);
            Max_Morale[root->x.ID] = max(root->Max_Num, Max_Morale[root->x.ID]);
            Max_Solidarity[root->x.ID] = max(root->Max_Size, Max_Solidarity[root->x.ID]);
        }
        DNode y = Split(root, k);
        Node *n = new Node(x);
        root = Merge(Merge(y.first, n), y.second);
    }
    void remove(data x)
    {
        int k = Rank(root, x);
        DNode a = Split(root, k);
        DNode b = Split(a.second, 1);
        delete b.first;
        root = Merge(a.first, b.second);
    }
};
#define Hash_MOD 76543
#define Hash_MOD_x 9991
#define Hash_MOD_y 7307
int p = 0;
struct Hash_Table
{
    int first[76545];
    struct Link
    {
        Treap *rt;
        Point t;
        int next;
    } v[400000];
    Hash_Table()
    {
        memset(first, -1, sizeof(first));
    }
    void Push(int u, Point now, Treap *x)
    {
        v[p].rt = x;
        v[p].t = now;
        v[p].next = first[u];
        first[u] = p++;
    }
    Treap *&operator[](Point x)
    {
        int Hash = (((x.x % Hash_MOD_x) + Hash_MOD_x) % Hash_MOD_x) * (((x.y % Hash_MOD_y) + Hash_MOD_y) % Hash_MOD_y) % Hash_MOD;
        for (int i = first[Hash]; i != -1; i = v[i].next)
            if (v[i].t == x)
                return v[i].rt;
        Push(Hash, x, new Treap);
        return v[first[Hash]].rt;
    }
} Hash;
#define X(_) ((_) ? (_)->x : 0)

Point bird[30005];
int Num[30005];
int main()
{
    int n;
    scanf("%d", &n);
    int a, b, c;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        Max_Morale[i] = max(Max_Morale[i], X(Hash[Point(b, c)]->kth(size(Hash[Point(b, c)]->root))).x);
        Max_Solidarity[i] = max(Max_Solidarity[i], size(Hash[Point(b, c)]->root));
        Hash[Point(b, c)]->Insert(data(a, i));
        bird[i] = Point(b, c);
        Num[i] = a;
    }
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        Hash[bird[a]]->remove(data(Num[a], a));
        Max_Morale[a] = max(Max_Morale[a], X(Hash[Point(b, c)]->kth(size(Hash[Point(b, c)]->root))).x);
        Max_Solidarity[a] = max(Max_Solidarity[a], size(Hash[Point(b, c)]->root));
        Hash[Point(b, c)]->Insert(data(Num[a], a));
        bird[a] = Point(b, c);
    }
    for (int i = 1; i <= n; i++)
        Hash[bird[i]]->remove(data(Num[i], i));
    for (int i = 1; i <= n; i++)
        printf("%lld\n", (long long)Max_Morale[i] * Max_Solidarity[i]);
    // while(1);
}
// Problem10467:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#ifndef LL
#define LL long long
#endif
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
const int N = 100005;
LL Sum[N << 2];
bool flag[N << 2];
void PushUp(int rt)
{
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
    flag[rt] = flag[rt << 1] & flag[rt << 1 | 1];
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        scanf("%lld", &Sum[rt]);
        if (Sum[rt] <= 1)
            flag[rt] = 1;
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    PushUp(rt);
}
void Update(int L, int R, int l, int r, int rt)
{
    if (flag[rt])
        return;
    if (l == r)
    {
        Sum[rt] = sqrt(Sum[rt]);
        if (Sum[rt] <= 1)
            flag[rt] = 1;
        return;
    }
    int m = l + r >> 1;
    if (L <= m)
        Update(L, R, lch);
    if (R > m)
        Update(L, R, rch);
    PushUp(rt);
}
LL Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Sum[rt];
    int m = l + r >> 1;
    LL ans = 0;
    if (L <= m)
        ans += Query(L, R, lch);
    if (R > m)
        ans += Query(L, R, rch);
    return ans;
}
int main()
{
    int n;
    scanf("%d", &n);
    buildtree(1, n, 1);
    int m;
    scanf("%d", &m);
    while (m--)
    {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (l > r)
            swap(l, r);
        if (op == 1)
        {
            printf("%lld\n", Query(l, r, 1, n, 1));
        }
        else
            Update(l, r, 1, n, 1);
    }
}
// Problem10468:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100];
int S[(1 << 20) + 1], f[(1 << 20) + 1];
int main()
{
    int n, m;
    int cnt = 0;
    scanf("%d", &n);
    for (cnt = 1; cnt <= n; cnt++)
        scanf("%d", &a[cnt]);
    scanf("%d", &m);
    n += m;
    for (; cnt <= n; cnt++)
        scanf("%d", &a[cnt]), a[cnt] = -a[cnt];
    int N = (1 << n) - 1;
    for (int i = 1; i <= N; i++)
    {
        int j = 0;
        for (j = 1; j <= n; j++)
            if (i & (1 << (j - 1)))
                break;
        S[i] = S[i ^ (1 << (j - 1))] + a[j];
        for (j = 1; j <= n; j++)
            if (i & (1 << (j - 1)))
                f[i] = max(f[i], f[i ^ (1 << (j - 1))] + (!S[i]));
    }
    printf("%d", n - f[N] * 2);
}
// Problem10471:
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 50005;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct edge
{
    int END, next;
} v[N];
int first[N], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
struct data
{
    int x, z;
    int flag, id;
    bool operator<(const data &b) const
    {
        return x < b.x;
    }
} Q[N << 1];
int cnt = 0;
int dep[N], top[N], size[N], fa[N], son[N], id[N], Index;
void dfs1(int rt, int f, int Dep)
{
    dep[rt] = Dep;
    size[rt] = 1;
    fa[rt] = f;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        dfs1(v[i].END, rt, Dep + 1);
        size[rt] += size[v[i].END];
        if (size[v[i].END] > size[son[rt]])
            son[rt] = v[i].END;
    }
}
void dfs2(int rt, int tp)
{
    top[rt] = tp;
    id[rt] = ++Index;
    if (son[rt])
        dfs2(son[rt], tp);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == son[rt])
            continue;
        dfs2(v[i].END, v[i].END);
    }
}
int ans[N];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
int Sum[N << 2], lazy[N << 2];
void Pushup(int rt)
{
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}
void Pushdown(int rt, int m)
{
    if (lazy[rt])
    {
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        Sum[rt << 1] += (m - (m >> 1)) * lazy[rt];
        Sum[rt << 1 | 1] += (m >> 1) * lazy[rt];
        lazy[rt] = 0;
    }
}
void Update(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        Sum[rt] += (r - l + 1);
        lazy[rt] += 1;
        return;
    }
    Pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m)
        Update(L, R, lch);
    if (R > m)
        Update(L, R, rch);
    Pushup(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Sum[rt];
    int m = (l + r) >> 1;
    Pushdown(rt, r - l + 1);
    int ans = 0;
    if (L <= m)
        ans += Query(L, R, lch);
    if (R > m)
        ans += Query(L, R, rch);
    return ans;
}
int n, q;
void Update(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        Update(id[top[x]], id[x], 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    Update(id[x], id[y], 1, n, 1);
}
int Query(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ans += Query(id[top[x]], id[x], 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ans += Query(id[x], id[y], 1, n, 1);
    return ans;
}
int main()
{
    n = read(), q = read();
    memset(first, -1, sizeof(first));
    int a = 0;
    for (int i = 2; i <= n; i++)
    {
        a = read();
        add(a + 1, i);
    }
    int b, c;
    for (int i = 1; i <= q; i++)
    {
        a = read(), b = read(), c = read();
        a++, b++, c++;
        Q[++cnt].x = a - 1, Q[cnt].z = c, Q[cnt].flag = -1, Q[cnt].id = i;
        Q[++cnt].x = b, Q[cnt].z = c, Q[cnt].flag = 1, Q[cnt].id = i;
    }
    dfs1(1, 0, 0);
    dfs2(1, 0);
    sort(Q + 1, Q + cnt + 1);
    int Now = 0;
    for (int i = 1; i <= cnt; i++)
    {
        while (Now < Q[i].x)
        {
            Now++,
                Update(1, Now);
        }
        ans[Q[i].id] += Q[i].flag * Query(1, Q[i].z);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i] % 201314);
}
