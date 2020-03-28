#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#include<windows.h>
using namespace std;
int main()
{
	int js=0;
	while(js<1000)
	{
		js++;
		cout<<js<<endl;
		system("maker.exe >L.in");
		system("L.exe <L.in >L.out");
		system("LL.exe <L.in >L.ans");
		if(system("FC L.ans L.out"))break;
	}
	return 0;
}
