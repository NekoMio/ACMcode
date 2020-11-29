#include<stdio.h>
#include<stdlib.h>
void bubbleSort(float a[],int s[],int l,int r)
{
	int loc,i,temp,n,c,v;
	n=r-l+1;
	for(loc = n-1;loc >= 1;loc--){
		for(i = 0;i <= loc-1;i++)    
			if(a[s[i]] > a[s[i + 1]]){
				 temp = s[i];
		     s[i] = s[i+1];
		     s[i+1] = temp;
		 }	    
	} 

	return ;
 }
int main()
{
	int n,line,col,i,p,q,count;
	scanf("%d",&n);
	getchar();
	int mata[n][n];
	int matb[n][n];
	int sum[n];
	float a[n];
	int b[n];
	for(line=0;line<n;line++)
	{
		for(col=0;col<n;col++)
		{
			mata[line][col]=0;
			matb[line][col]=0;
		}
	}
	for(i=0;i<n;i++)
	{
		sum[i]=0;
		a[i]=0;
		b[i]=0;
	}
	for(line=0;line<n;line++)
	{
		for(col=0;col<n;col++)
		{
			scanf("%d",&mata[line][col]);
		}
	}
	for(line=0;line<n;line++)
	{
		for(col=0;col<n;col++)
		{
			sum[line]+=mata[line][col];
		}
	}
	for(i=0;i<n;i++)
	{a[i]=(float)sum[i]/n;
	b[i]=i;
	}
	bubbleSort(a,b,0,n-1);
  
  for(q=0;q<n;q++)
  {	
    for(col=0;col<n;col++)
    {
      if(col!=n-1)printf("%d ",mata[b[q]][col]); 
      else printf("%d\n",mata[b[q]][col]);
    }
  }

	return 0;
}
