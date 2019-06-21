#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
void Get_String(char *s)
{
    char a[55];
    a[0] = '\0';
    while (a[0] == '\0') 
        gets(a);
    int len = strlen(a);
    for (int i = 0; i < len; i++)
        s[i] = a[i];
    s[len] = '\0';
}
bool oper(char c)
{
    return (c == '+' || c == '-' || c == '/' || c == '*');
}
int n;
char s[55];
bool Judge(int l, int r)
{
    if (s[l] == ')' && s[r] == '(') return 0;
    if (l > r) return 1;
    if (oper(s[l]) || oper(s[r])) return 0;
    int L = -1, R = -1;
    int top = 0;
    for (int i = l; i <= r; i++)
        if (s[i] == '(') top++;
        else if (s[i] == ')') top--;
    if (top) return 0;
    for (int i = l; i <= r; i++)
    {
        if (s[i] == '(')
        {
            top++;
            if (top == 1) 
                L = i;
        }
        else if (s[i] == ')')
        {
            top--;
            if (top == 0)
            {
                R = i;
                break;
            }
        }
    }
    if (L != -1 && R != -1)
    {
        if (L - 1 >= 0 && !oper(s[L - 1]) && s[L - 1] != '(') return 0;
        if (R + 1 < n && !oper(s[R + 1]) && s[R + 1] != ')') return 0;
        return Judge(l, L - 2) && Judge(L + 1, R - 1) && Judge(R + 2, r);
    }
    else if (L != -1 || R != -1)
        return 0;
    else
    {
        for (int i = l; i <= r; i++) if (oper(s[i])) {L = i; break;}
        if (L != -1)
            return Judge(l, L - 1) && Judge(L + 1, r);
        else
        {
            for (int i = l; i <= r; i++)
                if (s[i] < '0' || s[i] > '9') 
                    return 0;
            return 1;
        }
    }
}
int main()
{
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        memset(s, 0, sizeof (s));
        char a[100];
        Get_String(a);
        int n1 = strlen(a);
        bool flag = 0;
        int i, p;
        for (i = 0, p = 0; i < n1; i++)
        {
            if (a[i] == ' ')
                flag = 1;
            else
            {
                if (s[p - 1] >= '0' && s[p - 1] <= '9' && a[i] >= '0' && a[i] <= '9' && flag) 
                    s[p++] = '.', s[p++] = a[i];
                else s[p++] = a[i];
                flag = 0;
            }
        }
        s[p] = '\0';
        n = strlen(s);
        if (n != 0 && Judge(0, n - 1)) printf ("Yes\n");
        else printf ("No\n");
    }
}
