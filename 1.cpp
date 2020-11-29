#include<stdio.h>
void bubbleSort(int a[],int n)
{
	int loc,i,temp;
	for(loc = n-1;loc >= 1;loc--){
		for(i = 0;i <= loc-1;i++)    
			if(a[i] > a[i+1]){
			 temp = a[i];
		     a[i] = a[i+1];
		     a[i+1] = temp;
		 }	    
	} 
	return ;
 }
 
int main ()
{
	int i,n,k=0,sum=0,l=0,p;
	int book[100]={0};
	int a[100]={0};
	scanf("%d",&n);
	getchar();
	for(p=0;p<n;p++)
	{	scanf("%d",&book[i]);
		
	}
	bubbleSort(book,n);
	for(i=0;i<100;i++)
	{
        printf ("%d\n", book[i]);
		sum=sum+book[i];
		k=k+1;
		l=k-1;
		if(sum>1000) {
            printf("%d",l);
            {break;}
        }
	}	
	return 0;
}
