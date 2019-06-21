#include <bits/stdc++.h>
using namespace std;
struct Skew_Heap
{
    struct Node
    {
        int v;
        Node *ch[2];
        Node(int x)
        {
            v = x;
            ch[0] = ch[1] = NULL;
        }
		//void* operator new (size_t)
    }*root;
	Skew_Heap()
    {
        root = NULL;
    }
    Node *Merge(Node *&A, Node *&B)
    {
        if (!A) return B;
        if (!B) return A;
        if (A->v > B->v)
            swap(A, B);
        A->ch[1] = Merge(A->ch[1], B);
        swap(A->ch[0], A->ch[1]);
        return A;
    }
    Node *push(int x)
    {
        Node *n = new Node(x);
        return root = Merge(root, n);
    }
    int pop()
    {
        Node *A = root->ch[0], *B = root->ch[1];
        int ret = root->v;
        delete root;
        root = Merge(A, B);
        return ret;
    }
    int top()
    {
        return root->v;
    }
	bool empty()
	{
		return root == NULL;
	}
}Q;
//priority_queue<int> Q;
int main()
{
    int n = 10000000;
    std::random_device rd;
    std::mt19937 mt(rd());
    for (int i = 1; i <= n; i++)
        Q.push(mt());
    while (!Q.empty())
		Q.pop();
	printf ("%d", clock());
}