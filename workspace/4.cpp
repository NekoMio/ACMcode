#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Treap {
  struct Node {
    int id, val;
    int key, size;
    Node* ch[2];
    Node(int _id, int x) {
      id = _id, val = x;
      ch[0] = ch[1] = NULL;
      key = rand(), size = 1;
    }
    #define _size(_) ((_)?(_)->size:0)
    void Pushup() {
      size = _size(ch[0]) + _size(ch[1]) + 1;
    }  
  }*root;
  typedef pair<Node*,Node*> DNode;
  Node *Merge(Node *A, Node *B) {
    if (!A) return B;
    if (!B) return A;
    if (A->key < B->key);
  }
}