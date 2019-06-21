#ifdef __cplusplus
extern "C" {
#endif
	int query();
	void manipulate(double A[][2], int i, int op = 0);
	void arbitary_manipulate(double A[][2], int i, int op = 0);
	double arbitary_query(int x);
	int query_xor(int n, int t);
#ifdef __cplusplus
}
#endif

