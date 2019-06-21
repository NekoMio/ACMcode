#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;
char s[50];
int Greater[10][10][10][10];
int In[10][10];
bool H[10][10], S[10][10], K[10][10];
int map[10][10];
bool OK(int x, int y, int i)
{
	if(H[x][i])
		return 0;
	if(S[y][i])
		return 0;
	if(K[In[x][y]][i])
		return 0;
	if(Greater[x][y][x - 1][y] == 1 && i < map[x - 1][y])
		return 0;
	if(Greater[x][y][x][y - 1] == 1 && i < map[x][y - 1])
		return 0;
	if(Greater[x][y][x - 1][y] == -1 && i > map[x - 1][y])
		return 0;
	if(Greater[x][y][x][y - 1] == -1 && i > map[x][y - 1])
		return 0;
	return 1;
}
int ans = 0;
void dfs(int x, int y)
{
	//ans++;
	//printf("%d %d\n", x, y);
	if(x == 10 && y == 1)
	{
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 8; j++)
				printf("%d ", map[i][j]);
			printf("%d\n",map[i][9]);
		}
		exit(0);
	}
	for (int i = 9; i >= 1; i--)
	{
		if(OK(x, y, i))
		{
			K[In[x][y]][i] = 1;
			H[x][i] = 1;
			S[y][i] = 1;
			map[x][y] = i;
			if(y == 9)
				dfs(x + 1, 1);
			else
				dfs(x, y + 1);
			map[x][y] = 0;
			K[In[x][y]][i] = 0;
			H[x][i] = 0;
			S[y][i] = 0;
		}
	}
}
int main()
{
	for (int l = 0; l < 3; l++)
	{
		for (int i = 1; i <= 5; i++)
		{
			if(i & 1)
			{
				gets(s);
				int j = 0;
				while(s[j]!='<'&&s[j]!='>') j++;
				Greater[((i + 1) >> 1) + l * 3][1][((i + 1) >> 1) + l * 3][2] = (s[j]=='>' ? 1 : -1);
				Greater[((i + 1) >> 1) + l * 3][2][((i + 1) >> 1) + l * 3][1] = -Greater[((i + 1) >> 1) + l * 3][1][((i + 1) >> 1) + l * 3][2];
				j++;
				while(s[j]!='<'&&s[j]!='>') j++;
				Greater[((i + 1) >> 1) + l * 3][2][((i + 1) >> 1) + l * 3][3] = (s[j]=='>' ? 1 : -1);
				Greater[((i + 1) >> 1) + l * 3][3][((i + 1) >> 1) + l * 3][2] = -Greater[((i + 1) >> 1) + l * 3][2][((i + 1) >> 1) + l * 3][3];
				j++;
				while(s[j]!='<'&&s[j]!='>') j++;
				Greater[((i + 1) >> 1) + l * 3][4][((i + 1) >> 1) + l * 3][5] = (s[j]=='>' ? 1 : -1);
				Greater[((i + 1) >> 1) + l * 3][5][((i + 1) >> 1) + l * 3][4] = -Greater[((i + 1) >> 1) + l * 3][4][((i + 1) >> 1) + l * 3][5];
				j++;
				while(s[j]!='<'&&s[j]!='>') j++;
				Greater[((i + 1) >> 1) + l * 3][5][((i + 1) >> 1) + l * 3][6] = (s[j]=='>' ? 1 : -1);
				Greater[((i + 1) >> 1) + l * 3][6][((i + 1) >> 1) + l * 3][5] = -Greater[((i + 1) >> 1) + l * 3][5][((i + 1) >> 1) + l * 3][6];
				j++;
				while(s[j]!='<'&&s[j]!='>') j++;
				Greater[((i + 1) >> 1) + l * 3][7][((i + 1) >> 1) + l * 3][8] = (s[j]=='>' ? 1 : -1);
				Greater[((i + 1) >> 1) + l * 3][8][((i + 1) >> 1) + l * 3][7] = -Greater[((i + 1) >> 1) + l * 3][7][((i + 1) >> 1) + l * 3][8];
				j++;
				while(s[j]!='<'&&s[j]!='>') j++;
				Greater[((i + 1) >> 1) + l * 3][8][((i + 1) >> 1) + l * 3][9] = (s[j]=='>' ? 1 : -1);
				Greater[((i + 1) >> 1) + l * 3][9][((i + 1) >> 1) + l * 3][8] = -Greater[((i + 1) >> 1) + l * 3][8][((i + 1) >> 1) + l * 3][9];
				j++;
			}
			else
			{
				gets(s);
				int j = 0;
				for (int k = 1; k <= 9; k++)
				{
					while(s[j]!='v'&&s[j]!='^') j++;
					Greater[(i >> 1) + l * 3][k][(i >> 1) + 1 + l * 3][k] = (s[j] == 'v' ? 1 : -1);
					Greater[(i >> 1) + 1 + l * 3][k][(i >> 1) + l * 3][k] = -Greater[(i >> 1) + l * 3][k][(i >> 1) + 1 + l * 3][k];
					j++;
				}
			}
		}
	}
	for(int i = 1; i <= 3; i++) for (int j = 1; j <= 3; j++) In[i][j] = 1;
	for(int i = 4; i <= 6; i++) for (int j = 1; j <= 3; j++) In[i][j] = 2;
	for(int i = 7; i <= 9; i++) for (int j = 1; j <= 3; j++) In[i][j] = 3;
	for(int i = 1; i <= 3; i++) for (int j = 4; j <= 6; j++) In[i][j] = 4;
	for(int i = 4; i <= 6; i++) for (int j = 4; j <= 6; j++) In[i][j] = 5;
	for(int i = 7; i <= 9; i++) for (int j = 4; j <= 6; j++) In[i][j] = 6;
	for(int i = 1; i <= 3; i++) for (int j = 7; j <= 9; j++) In[i][j] = 7;
	for(int i = 4; i <= 6; i++) for (int j = 7; j <= 9; j++) In[i][j] = 8;
	for(int i = 7; i <= 9; i++) for (int j = 7; j <= 9; j++) In[i][j] = 9;
	dfs(1, 1);
}