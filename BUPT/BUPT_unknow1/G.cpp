#include<cstdio>

long long a,b,c,d,e,f,g,i,m,n;
long long xa[2000000],xb[2000000],xc[2000000];
long long w[2000000];
long long h;
char z[2000000];

int main()
{
scanf("%lld",&a);
for(n=1;n<=a;n++)
{
	scanf("%lld%s",&b,z);
	c=0;
	d=0;
	for(i=0;i<b;i++)
	{
		xa[i]=z[i]-'0';
		xb[i]=0;
		w[i]=0;
		if(xa[i]==c)
		{
			d++;
			xc[d]=i;
		}
		if(xa[i]>c)
		{
			c=xa[i];
			d=1;
			xc[d]=i;
		}
	}
	w[1]=c;
	for(i=2;i<=b;i++)
	{
		//printf("%d %d %d\n",c,d,xc[1]);
		e=d;
		c=0;
		d=0;
		for(m=1;m<=e;m++)
		{
			f=(xc[m]*xc[m]+1)%b;
			//printf("%d %d\n",xc[m],f);
			if(xb[f]!=i)
			{
				xb[f]=i;
				if(xa[f]==c)
				{
					d++;
					xc[d]=f;
				}
				if(xa[f]>c)
				{
					c=xa[f];
					d=1;
					xc[d]=f;
				}
			}
		}
		w[i]=c;
		
	}
	printf("Case #%lld: ",n);
	for(i=1;i<=b;i++)
	{
		printf("%lld",w[i]);
	}
	printf("\n");
}
}