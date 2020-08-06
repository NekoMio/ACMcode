#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5+10;
LL f[maxn<<1];
void dfs(LL st,LL delta,LL mx)
{
	if(st>maxn) return;
	f[st]++;
	for(int i=delta;i<=mx;i++){
		dfs(st+i,i,mx);
	}
}
int main()
{
	for(LL n=6;n<=maxn;n++){
    if (n % 1000 == 0) printf ("%d\n", n);
		// cout<<"1st:"<<n<<'\n';
		LL tmp=n-6;
		f[n]+=1;//只有1 
		f[n]+=tmp/2;//只有2；只有1,2 
		for(LL i=1;i<=tmp;i++){//只有2,3；只有1,2,3 
			if(tmp-3*i<0) continue;
			f[n]+=(tmp-3*i)/2;
		}
		if(tmp&&tmp%3==0) f[n]++;//只有3 
		for(LL i=1;i<=tmp;i++){//只有1,3 
			if(tmp-3*i<=0) continue;
			f[n]++;
		}
	}
	for(LL st=2;st<=maxn/3+1;st++){
    if (st % 1000 == 0) printf ("%d\n", st);
		// cout<<"2st:"<<st<<endl;
		dfs(3*st+3,st,st+2);
	}
	// cout<<"{";
	// for(int i=1;i<=maxn;i++) cout<<","<<f[i];
	// cout<<"}";
	FILE *fs;
	fs = fopen("1.txt", "r");
	// if(!fs) return 0;
	fprintf (fs, "{");
	for(int i=1;i<=maxn;i++) fprintf (fs, ",%d",f[i]);
	fprintf (fs, "}");
}