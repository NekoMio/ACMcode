#include<cstdio>
#include<algorithm>
using namespace std;

long long a,b,c,d,e,f,g,i,m,n;
long long x[5000000]={0};

int main()
{
while(scanf("%lld%lld",&a,&b)!=EOF)
{
	c=0;
	for(i=1;i<=a;i++)
	{
		scanf("%lld",&x[i]);
		c+=x[i];
	}
	sort(x+1,x+a+1);
	d=x[1];
	f=0;
	for(i=1;i<a;i++)
	{
		g=(x[i+1]-x[i])*i;
		if(f+g<=b)
		{
			f+=g;
			d=x[i+1];
		}
		else
		{
			g=b-f;
			d+=g/i;
			f=b;
		}
		if(f==b) i=a+10;
	}
	e=x[a];
	f=0;
	for(i=a;i>1;i--)
	{
		g=(x[i]-x[i-1])*(a-i+1);
		if(f+g<=b)
		{
			f+=g;
			e=x[i-1];
		}
		else
		{
			g=b-f;
			e-=g/(a-i+1);
			f=b;
		}
		if(f==b) i=-1;
	}
	//printf("%lld %lld\n",d,e);
	if(d+1<e) printf("%lld\n",e-d);
	else
	{
		if(c%a==0) printf("0\n");
		else printf("1\n");
	}
}
}