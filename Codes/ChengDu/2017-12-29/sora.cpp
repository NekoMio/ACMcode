#ifndef LEMON_JUDGE
#include "grader.h"
#endif
using namespace std;
//Do not declare any global variables
namespace sora{
	//declare your variables here
	int id = 0;
	//implement these functions
	void initSora(int caseno){
		id = caseno;
	}

	void sora(int x, int y, vector<int> v){
		if (id == 1)
		{
			while (v.size() != 0)
			{
				// for (int i = 0; i <= 3; i++) printf ("%d ", v[i]);
				// printf ("\n");
				for (int i = 0; i <= 3; i++)
					if (v[i] == v[4] - 1)
					{
						v = move(i, 1);
						break;
					}
			}
		}
		else if (id == 2)
		{
			int nx = x, ny = y;
			while (v.size() != 0)
			{
				if (v[4] != 2)
				{
					if (((nx & 1) ^ (ny & 1)))
					{
						if (v[4] == 1) v = move(2, 1), ny++;
						else v = move(3, 1), ny--;
					}
					else
					{
						if (v[4] == 1) v = move(0, 1), nx++;
						else v = move(1, 1), nx--;
					}
				}
				else
				{
					if (((nx & 1) ^ (ny & 1)))
					{
						if (v[3] == 1) v = move(0, 1), nx++;
						else v = move(1, 1), nx--;
					}
					else 
					{
						if (v[1] == 1) v = move(2, 1), ny++;
						else v = move(3, 1), ny--;
					}
				}
			}
		}
	}
}