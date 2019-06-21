#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;
string O[10] = {"commit", "push", "add", "pull"};
void DO(string S)
{
	if(S == O[0])
	{
		system("git add -A & git commit -m \"no message\"");
		printf("commit Done\n");
		return;
	}
	else if(S == O[1])
	{
		system("git add -A & git commit -m \"no message\" & git push");
		printf("push Done\n");
		return;
	}
	else if(S == O[2])
	{
		system("git add -A");
		printf("add Done\n");
		return;
	}
	else if(S == O[3])
	{
		system("git pull");
		return;
	}
}
bool file()
{
	string S;
	cout<<"OP ? :\n";
	cin>>S;
	if(S[0] == 'Q' || S[0] == 'q')
		return 0;
	DO(S);
	return 1;
}
int main(int argc, char const *argv[])
{
	system("git config --global user.email \"wangxiaohui0821@gmail.com\"");
	system("git config --global user.name \"hzoi-wildrage\"");
	printf("Init done\n");
	if(argc == 1)
	{
		printf("ERROR\n");
		system("pause");
		system("cls");
		while(file());
		return 0;
	}
	string S(argv[1]);
	cout<<"Doing "<<S<<endl;
	DO(S);
	return 0;
}