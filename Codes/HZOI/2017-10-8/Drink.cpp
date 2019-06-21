#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline void read(int &a)
{
    int f = 1;
    a = 0;
    char ch = getchar();
    while (ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while (ch<='9'&&ch>='0'){a=a*10+ch-'0';ch=getchar();}
    a *= f;
}
int id[2005][2005];
struct data
{
    int nxt[4], t, v;
}v[2005 * 2005];
int p;
int move0(int x)
{
    int nxt = v[x].nxt[(v[x].t + 0) % 4];
    for (int i = 0; i <= 3; i++)
    {
        if (v[nxt].nxt[i] == x)
        {
            v[nxt].t = (v[x].t - ((v[x].t + 2) % 4) + i + 4) % 4;
            return nxt;
        }
    }
    return 0;
}
int move1(int x)
{
    int nxt = v[x].nxt[(v[x].t + 1) % 4];
    for (int i = 0; i <= 3; i++)
    {
        if (v[nxt].nxt[i] == x)
        {
            v[nxt].t = (v[x].t - ((v[x].t + 3) % 4) + i + 4) % 4;
            return nxt;
        }
    }
    return 0;
}
int move2(int x)
{
    int nxt = v[x].nxt[(v[x].t + 2) % 4];
    for (int i = 0; i <= 3; i++)
    {
        if (v[nxt].nxt[i] == x)
        {
            v[nxt].t = i;
            return nxt;
        }
    }
    return 0;
}
int move3(int x)
{
    int nxt = v[x].nxt[(v[x].t + 3) % 4];
    for (int i = 0; i <= 3; i++)
    {
        if (v[nxt].nxt[i] == x)
        {
            v[nxt].t = (v[x].t - ((v[x].t + 1) % 4) + i + 4) % 4;
            return nxt;
        }
    }
    return 0;
}
int Move(int x, int y)
{
    int now = id[0][0];
    for (int i = 1; i <= y; i++)
        now = move1(now);
    for (int i = 1; i <= x; i++)
        now = move2(now);
    return now;
}
int main()
{
    // freopen("drink.in","r",stdin);
    // freopen("1.out","w", stdout);
    int n, m, q;
    read(n), read(m), read(q);
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++)
            id[i][j] = ++p;
    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= m + 1; j++)
        {
            if (i != 0) v[id[i][j]].nxt[0] = id[i - 1][j];
            if (j != 0) v[id[i][j]].nxt[3] = id[i][j - 1];
            v[id[i][j]].nxt[1] = id[i][j + 1];
            v[id[i][j]].nxt[2] = id[i + 1][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &v[id[i][j]].v);
        }
    }
    int x, y, c;
    while (q--)
    {
        read(x), read(y), read(c);
        if (c == 1) continue;
        int s = Move(x, y);
        static int st[2005], Center[5], H[2005], Y[2005];
        {
            for (int i = 1; i < c; i++)
            {
                s = move1(s);
                Y[i] = s;
                if (i != c - 1)
                {
                    H[i] = v[s].nxt[v[s].t];
                    st[i] = s;
                }
            }
            for (int i = 1; i < c; i++) 
            {
                s = move2(s);
                if (i != c - 1)
                {
                    int R = v[s].nxt[(v[s].t + 1) % 4];
                    for (int j = 0; j <= 3; j++)
                    {
                        if (s == v[R].nxt[j])
                        {
                            v[R].nxt[j] = st[i];
                            v[st[i]].nxt[v[st[i]].t] = R;
                            break;
                        }
                    }
                    st[i] = s;
                }
                else Center[1] = s;
            }
            for (int i = 1; i < c; i++)
            {
                s = move3(s);
                if (i != c - 1)
                {
                    int R = v[s].nxt[(v[s].t + 2) % 4];
                    for (int j = 0; j <= 3; j++)
                    {
                        if (s == v[R].nxt[j])
                        {
                            v[R].nxt[j] = st[i];
                            v[st[i]].nxt[(v[st[i]].t + 1) % 4] = R;
                            break;
                        }
                    }
                    st[i] = s;
                }
                else Center[2] = s;
            }
            for (int i = 1; i < c; i++)
            {
                s = move0(s);
                if (i != c - 1)
                {
                    int R = v[s].nxt[(v[s].t + 3) % 4];
                    for (int j = 0; j <= 3; j++)
                    {
                        if (s == v[R].nxt[j])
                        {
                            v[R].nxt[j] = st[i];
                            v[st[i]].nxt[(v[st[i]].t + 2) % 4] = R;
                            break;
                        }
                    }
                    st[i] = s;
                }
                else Center[3] = s;
            }
            for (int i = 1; i < c; i++)
            {
                if (i != c - 1)
                {
                    int R = H[i];
                    for (int j = 0; j <= 3; j++)
                    {
                        if (Y[i] == v[R].nxt[j])
                        {
                            v[R].nxt[j] = st[i];
                            v[st[i]].nxt[(v[st[i]].t + 3) % 4] = R;
                            break;
                        }
                    }
                }
                else Center[4] = Y[i];
            }
        }
        {
            int B1 = v[Center[4]].nxt[(v[Center[4]].t + 1) % 4];
            int B2 = v[Center[4]].nxt[v[Center[4]].t];
            int R = v[Center[1]].nxt[(v[Center[1]].t + 1) % 4];
            int D = v[Center[1]].nxt[(v[Center[1]].t + 2) % 4];
            for (int i = 0; i <= 3; i++)
            {
                if (v[R].nxt[i] == Center[1])
                {
                    v[R].nxt[i] = Center[4];
                    v[Center[4]].nxt[(v[Center[4]].t) % 4] = R;
                    break;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[D].nxt[i] == Center[1])
                {
                    v[D].nxt[i] = Center[4];
                    v[Center[4]].nxt[(v[Center[4]].t + 1) % 4] = D;
                    break;
                }
            }

            int L = v[Center[2]].nxt[(v[Center[2]].t + 3) % 4];
            D = v[Center[2]].nxt[(v[Center[2]].t + 2) % 4];
            for (int i = 0; i <= 3; i++)
            {
                if (v[L].nxt[i] == Center[2])
                {
                    v[L].nxt[i] = Center[1];
                    v[Center[1]].nxt[(v[Center[1]].t + 2) % 4] = L;
                    break;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[D].nxt[i] == Center[2])
                {
                    v[D].nxt[i] = Center[1];
                    v[Center[1]].nxt[(v[Center[1]].t + 1) % 4] = D;
                }
            }
            L = v[Center[3]].nxt[(v[Center[3]].t + 3) % 4];
            int U = v[Center[3]].nxt[v[Center[3]].t];
            for (int i = 0; i <= 3; i++)
            {
                if (v[L].nxt[i] == Center[3])
                {
                    v[L].nxt[i] = Center[2];
                    v[Center[2]].nxt[(v[Center[2]].t + 2) % 4] = L;
                    break;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[U].nxt[i] == Center[3])
                {
                    v[U].nxt[i] = Center[2];
                    v[Center[2]].nxt[(v[Center[2]].t + 3) % 4] = U;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[B1].nxt[i] == Center[4])
                {
                    v[B1].nxt[i] = Center[3];
                    v[Center[3]].nxt[(v[Center[3]].t) % 4] = B1;
                    break;
                }
            }
            for (int i = 0; i <= 3; i++)
            {
                if (v[B2].nxt[i] == Center[4])
                {
                    v[B2].nxt[i] = Center[3];
                    v[Center[3]].nxt[(v[Center[3]].t + 3) % 4] = B2;
                    break;
                }
            }
        }
        // for (int i = 1; i <= n; i++)
        // {
        //     int s = move1(id[i][0]);
        //     for (int j = 1; j <= m; j++, s = move1(s))
        //         printf("%d ", v[s].v);
        //     printf("\n");
        // }
        // printf ("\n\n");
    }
    for (int i = 1; i <= n; i++)
    {
        int s = move1(id[i][0]);
        for (int j = 1; j <= m; j++, s = move1(s))
            printf("%d ", v[s].v);
        printf("\n");
    }
    // while (1);
}