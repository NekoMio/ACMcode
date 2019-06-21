#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
namespace Data
{
class Treap
{
  public:
    class Node
    {
      public:
        int key, s;
        char c;
        Node *ch[2];
        Node(char x)
        {
            ch[0] = ch[1] = NULL;
            key = rand(), s = 1;
            c = x;
        }
#define size(_) ((_) ? (_)->s : 0);
        void Pushup()
        {
            s = size(ch[0]) + size(ch[1]) + 1;
        }
    };
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
        if (A->key > B->key)
        {
            A->ch[1] = Merge(A->ch[1], B);
            A->Pushup();
            return A:
        }
        else
        {
            B->ch[0] = Merge(A, B->ch[0]);
            B->Pushup();
            return B;
        }
    }
    typedef pair<Node *, Node *> DNode;
    DNode Split(Node *rt)
    {
        if (!rt)
            return DNode(NULL, NULL);
        if ()
    }
};
}