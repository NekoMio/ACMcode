#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,c,m;
int a[100005];
int Times[100005];
int main()
{
    freopen("Poetize.in","r",stdin);
    freopen("Poetize.out","w",stdout);
	scanf("%d%d%d",&n,&c,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	int ans=0,sum=0;
	int l,r,R,L;
	while(m--){
		memset(Times,0,sizeof(Times));
		scanf("%d%d",&l,&r);
		L=(l+ans)%n+1,R=(r+ans)%n+1;
		if(L>R)swap(L,R);
		for(int i=L;i<=R;i++){
			Times[a[i]]++;
		}
        sum=0;
		for(int i=1;i<=c;i++)sum+=((Times[i]^1)&&Times[i]);
		printf("%d\n",sum);
		ans=sum;
	}
	//while(1);
}
