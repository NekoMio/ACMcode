namespace __TREAP_TREE{
	using std::pair;
	template<typename _Tp>
	class Treap{
		class __Treap_Node{
		public:
			_Tp __value;
			int key,size;
			__Treap_Node* _ch[2];
			__Treap_Node(_Tp _x){
				__value=_x;key=rand();size=1;
				_ch[0]=_ch[1]=NULL;
			}
			#define _size(_) ((_)?(_)->size:0)
			void _Pushup(){
				size=_size(_ch[0])+_size(_ch[1])+1;
			}
		}*_root;
		typedef pair<__Treap_Node*,__Treap_Node*> __DNode;
		__Treap_Node *__Merge(__Treap_Node* _A,__Treap_Node* _B){
			if(!_A)return _B;
			if(!_B)return _A;
			if(_A->key<_B->key){
				_A->_ch[1]=__Merge(_A->_ch[1],_B);
				_A->_Pushup();
				return _A;
			}else{
				_B->_ch[0]=__Merge(_A,_B->_ch[0]);
				_B->_Pushup();
				return _B;
			}
		}
		__DNode __Split(__Treap_Node* _rt,int _k){
			if(!_rt)return __DNode(NULL,NULL);
			__DNode _o;
			if(_size(_rt->_ch[0])>=_k){
				_o=__Split(_rt->_ch[0],_k);
				_rt->_ch[0]=_o.second;
				_rt->_Pushup();
				_o.second=_rt;
			}
			else{
				_o=__Split(_rt->_ch[1],_k-_size(_rt->_ch[0])-1);
				_rt->_ch[1]=_o.first;
				_rt->_Pushup();
				_o.first=_rt;
			}
			return _o;
		}
	public:	
		Treap(){
			_root=NULL;
		} 
		_Tp kth(int _k){
			__DNode _x=__Split(_root,_k-1);
			__DNode _y=__Split(_x.second,1);
			__Treap_Node *_ans=_y.first;
			_root=__Merge(__Merge(_x.first,_ans),_y.second);
			return _ans->__value;
		}
		int rank(_Tp x){
			return _rank(_root,x);
		}
		int _rank(__Treap_Node* _rt,_Tp _x){
			if(!_rt)return 0;
			return _x<=_rt->__value ? _rank(_rt->_ch[0],_x):_rank(_rt->_ch[1],_x)+_size(_rt->_ch[0])+1;
		}
		void Insert(_Tp _x){
			int _k=_rank(_root,_x);
			__DNode _y=__Split(_root,_k);
			__Treap_Node* _n=new __Treap_Node(_x);
			_root=__Merge(__Merge(_y.first,_n),_y.second);
		}
		void remove(_Tp _x){
			int _k=_rank(_root,_x);
			__DNode _a=__Split(_root,_k);
			__DNode _b=__Split(_a.second,1);
			_root=__Merge(_a.first,_b.second);
		}
	};
}
#endif