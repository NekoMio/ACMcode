#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
typedef unsigned long long ll;
const ll base = 977;
ll h[maxn],bs[maxn];
struct trie{
    int id;
    int ch[26];
}tr[maxn];
int f[maxn][26];
string s;
int x;
char c;
int len;
map<ll,int>mp;
int n,m,q,t;
int ql,qr;
void init(){
    bs[0] = 1;
    for(int i = 1;i < maxn;++i)
	{
        bs[i] = bs[i-1] * base;
    }
    return;
}
ll get_hash(int l,int r)
{
    return h[r] - h[l] * bs[r - l];
}
void dfs(int now,ll hash)
{
    mp[hash] = now;
    for(int i = 1;i <= 26;++i){
        if(tr[now].ch[i-1] == 0)
            continue;
        dfs(tr[now].ch[i-1],hash * base + i);
    }
    return;
}
int main(){
    init();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while(t--){
        scanf("%d%d%d",&n,&m,&q);
        for(int i = 0;i <= n;++i)
		{
            for(int j = 0;j < 26;++j)
                tr[i].ch[j] = 0;
        }
        for(int i = 0;i <= m;++i)
            for(int j = 0;j < 26;++j)
                f[i][j] = 0;
        mp.clear();
        for(int i = 1;i <= n;++i)
		{
            cin >> x;cin >> c;
            tr[x].ch[c - 'a'] = i;
        }
        dfs(0,0);
        cin >> s;
        for(int i = m;i >= 1;--i)
		{
            s[i] = s[i-1];
        }
        h[0] = 0;
        for(int i = 1;i <= m;++i)
		{
            h[i] = h[i-1] * base + s[i] - 'a' + 1;
        }
        int log_m = 0;
        while((1<<log_m) <= m)
		{
            log_m++;
        }
        for(int i = 0;i <= m;++i)
		{
            int l = 0,r = m - i;
            int ans = 0;
            while(l <= r)
			{
                int mid = (l + r) >> 1;
                ll p = get_hash(i,i + mid);
                if(!mp.count(p))
				{
                    r = mid - 1;
                }
                else l = mid + 1;
            }
            f[i][0] = i + l;
        }
        f[m+1][0] = m+1;
        for(int i = 1;i < log_m;++i)
		{
            for(int j = 0;j <= m+1;++j)
			{
                f[j][i] = f[f[j][i-1]][i-1];
            }
        }
        while(q--)
		{
            cin >> ql >> qr;
            ql -= 1;
            int ans = 0;
            for(int i = log_m - 1;i >= 0;--i)
			{
                if(f[ql][i] <= qr)
				{
                    ql = f[ql][i];
                    ans += (1 << i);
                }
            }
            int id = mp[get_hash(ql,qr)];
            printf("%d %d\n",ans,id);
        }
    }
    return 0;
}