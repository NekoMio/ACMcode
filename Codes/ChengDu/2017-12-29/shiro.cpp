#ifdef LEMON_JUDGE
#include "../../data/board/grader.cpp"
#include "../../source/your_name/sora.cpp"
//Please relpace "your_name" with your id.
//It should not contain spaces or chinese characters.
#else
#include "grader.h"
#endif
#include <algorithm>
using namespace std;
//Do not declare any global variables
namespace shiro{
	//declare your variables here
	int id = 0;
	int Log[20];
	//implement these functions
	void initShiro(int caseno){
		id = caseno;
		Log[0] = -1;
		for (int i = 1; i <= 128; i++) Log[i] = Log[i >> 1] + 1;
	}
	void shiro(int x, int y){
		
	}
}