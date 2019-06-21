#include "quantumbreak.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef long long LL;
static int cnt = 0;
static int n, m, a, t[10];
static double sq2;
static double amp[(1 << 17) + 7];
static char msg[110];
static int score = 1;
static double eps = 1e-8;

void new_round() {
	int x = rand() % m, i;
	for(i = 0; i < m; i++) amp[i] = 0;
	amp[x] = amp[x ^ a] = sq2;
}


double rd() {
	int x0 = rand(), x1 = rand();
	double t = 1LL * x0 * RAND_MAX + x1;
	return t / RAND_MAX / RAND_MAX;
}

int query() {
	cnt++;
	if (cnt > 400) { 
		score = 0; strcpy(msg, "more than 400 operations used"); 	
	}
	if (!score) return 0;
	int i;
	double sum = 0;
	for(i = 0; i < m; i++) sum += amp[i] * amp[i];
	double s = rd() * sum;
	int ans = m - 1;
	for(i = 0; i < m; i++) {
		s -= amp[i] * amp[i];
		if (s <= 0) { ans = i; break; }
	}
	new_round();
	return ans;
}

int check(double a[][2]) {
	int i, j, k;
	for(i = 0; i < 2; i++) for(j = 0; j < 2; j++) {
		double tot = 0;
		for(k = 0; k < 2; k++) tot += a[i][k] * a[j][k];
		double t = tot - (i == j); if (t < 0) t = -t;
		if (t > eps) return 0;
	}
	return 1;
}

void manipulate(double a[][2], int x, int op) {
	cnt++; 
	if (cnt > 400) { score = 0; strcpy(msg, "more than 400 operations used"); }
	if (!score) return;
	if (x < 0 || x >= n) {
		if (score) {
			strcpy(msg, "function 2 : x outof range");
			score = 0;
		}
		return;
	}
	if (!t[2]) { 
		if (score) {
			strcpy(msg, "function 2 banned");
			score = 0;
		}
		return;
	}
	if (!check(a)) {
		if (score) {
			strcpy(msg, "function 2 : AA^t != I");
			score = 0;
		}
		return;
	}

	int j;
	for(j = 0; j < m; j++) if (j >> x & 1) {
		int i = j ^ (1 << x);
		double t1 = a[0][0] * amp[i] + a[1][0] * amp[j];
		double t2 = a[0][1] * amp[i] + a[1][1] * amp[j];
		amp[i] = t1, amp[j] = t2;
	}
	if (op == 1)
	{
		for (int i = 0; i < m; i++)
			printf ("%.2f ", amp[i]);
		printf ("\n");
	}
}

void arbitary_manipulate(double a[][2], int x, int op) {
	cnt++; 
	if (cnt > 400) { score = 0; strcpy(msg, "more than 400 operations used"); }
	if (!score) return;
	if (!t[3]) { 
		if (score) {
			strcpy(msg, "function 3 banned");
			score = 0;
		}
		return;
	}

	int j;
	for(j = 0; j < m; j++) if (j >> x & 1) {
		int i = j ^ (1 << x);
		double t1 = a[0][0] * amp[i] + a[1][0] * amp[j];
		double t2 = a[0][1] * amp[i] + a[1][1] * amp[j];
		amp[i] = t1, amp[j] = t2;
	}
	if (op == 1)
	{
		for (int i = 0; i < m; i++)
			printf ("%.2f ", amp[i]);
		printf ("\n");
	}
}

double arbitary_query(int x) {
	cnt++; 
	if (cnt > 400) { score = 0; strcpy(msg, "more than 400 operations used"); }
	if (!score) return 0;
	if (!t[4]) {
		if (score) {
			strcpy(msg, "function 4 banned");
			score = 0;
		}
		return 0;
	} 
	if (x < 0 || x >= m) {
		if (score) {
			strcpy(msg, "function 4 : index out of range");
			score = 0;
		}
		return 0;
	}
	return amp[x];
} 

int main()
{
	sq2 = 1.0 / sqrt(2);
	int seed, t_id;
	scanf("%d%d%d",&n,&seed,&t_id); m = 1 << n;
	scanf("%d %d %d %d",t + 1, t + 2, t + 3, t + 4);
	srand(seed); a = 1ll * rand() * rand() % (m - 1) + 1;
	new_round();
	int ans = query_xor(n, t_id);
	if (score && ans != a) {
		score = 0;
		sprintf(msg, "wrong answer : %d expected but %d found", a, ans);
	}
	printf("%d %d\n", score, cnt);
	printf ("%d\n", a);
	printf("%s\n",msg);
	return 0;
}
