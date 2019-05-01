/*
	*--writer  :  wjr
	*--last varsion fix time : 12/4/2017
	*--connect : wangjiaruo22@hotmail.com
	*--			 https://github.com/wjr22/
	*--remark  : I used NIL to replace nullptr because it will reduce computing node`s height errors
	*--		version :				description :
	*--			1.0.1 : 12/4/2017		definition data-struction
	*--									finish insert\delete\search operation and they`re fixup method
	*--									test : No
	*--			1.0.2 : 12/12/2017		test : fail;
	*--									fixup insert_fixup function but It make a new pointer error
*/
#ifndef _AVL_TREE_H
#define _AVL_TREE_H
#define _max(a,b) (a)>(b)?(a):(b)
#define _height(a) (a)->height
#define _abs(a) ((a)>0?(a):(-a))
#include<iostream>
using namespace std;
template<class Elem,typename Key>
class _avl_node {
	public:
		Elem			elem;
		Key				key;
		_avl_node		*left;
		_avl_node		*right;
		_avl_node		*parent;
		int				height;											//左右子树最高高度加一
};
template<class Elem,typename Key>
class _avltree {
	private:
		_avl_node<Elem,Key>*		Root;
		_avl_node<Elem,Key>*		NIL;								//叶节点 高度为0
		_avl_node<Elem,Key>*        LLRotate(_avl_node<Elem, Key> *x);
		_avl_node<Elem,Key>*		RLRotate(_avl_node<Elem, Key> *x);
		_avl_node<Elem,Key>*		LRRotate(_avl_node<Elem, Key> *x);
		_avl_node<Elem,Key>*		RRRotate( _avl_node<Elem, Key> *x);
		unsigned					Height(_avl_node<Elem, Key>*x);
		_avl_node<Elem,Key>*		_avl_insert(_avl_node<Elem, Key> *&tree, _avl_node<Elem, Key> *&x);
		_avl_node<Elem,Key>*		_avl_delete(_avl_node<Elem, Key> *&tree, _avl_node<Elem, Key> *&x);
	public:
	_avltree();
		void						Insert(Key key, Elem elem);
		_avl_node<Elem,Key> *       Search(Key key)const;
		void						Delete(Key key);
};
template<class Elem,typename Key>
_avltree<Elem,Key>::_avltree() {
	NIL = new _avl_node<Elem, Key>;
	this->NIL->height = 0;
	NIL->key = NULL;
	this->Root = NIL;
}
/*
	||
	||	search method
	||	@param  : key (type : Key) which will search
	||  @return : which node`s key == @param key 
*/
template<class Elem, typename Key>
_avl_node<Elem,Key> * _avltree<Elem, Key>::Search(Key key) const{
	_avl_node<Elem,Key> *_search_node=this->Root;
	while (_search_node != NIL && _search_node->key != key)  {
		if (_search_node->key < key) {
			_search_node = _search_node->right;
		}
		else {
			_search_node = _search_node->left;
		}
	}
	if (_search_node == NIL) {
		return nullptr;
	}
	else
		return _search_node;
}
/*
	|| insert port
	||
*/
template<class Elem,typename Key>
void _avltree<Elem, Key>::Insert(Key key,Elem elem) {
	_avl_node<Elem, Key> *_insert_node = new _avl_node<Elem, Key>;
	_insert_node->elem = elem; _insert_node->key = key;
	_insert_node->height = 0;
	_insert_node->left = _insert_node->right = NIL;
	if(this->_avl_insert(this->Root, _insert_node)!=NIL);
	else perror("insert error");
}
/*
    ||
	||  four rotate
	||  RRRotate :    A       B
	||               B 1 ==> 2  A
	||              2 3        3 1
*/
template<class Elem,typename Key>
_avl_node<Elem, Key>* _avltree<Elem, Key>::RRRotate(_avl_node<Elem,Key>*x) {
	_avl_node<Elem, Key> *leftchild = x->left;
	x->left = leftchild->right;
	leftchild->right = x;
	x->height = _max(_height(x->left), _height(x->right)) + 1;
	leftchild->height = _max(_height(leftchild->left), _height(leftchild->right)) + 1;
	return leftchild;
}
/*
    ||
	||  four rotate
	||  LLRotate :    A       B
	||               1 B ==> A  3
	||                2 3   1 2
*/
template<class Elem,typename Key>
_avl_node<Elem, Key>* _avltree<Elem, Key>::LLRotate(_avl_node<Elem,Key>*x) {
	_avl_node<Elem, Key> *rightchild = x->right;
	x->right = rightchild->left;
	rightchild->left = x;
	x->height = _max(_height(x->left), _height(x->right)) + 1;
	rightchild->height = _max(_height(rightchild->left), _height(rightchild->right)) + 1;
	return rightchild;
}
/*
    ||
	||  four rotate
	||  LRRotate :    A       A        C
	||               B 1 ==> C 1 ==> B   A
	||              2 C     B 4     2 3 4 1
	||               3 4   2 3
	||	first LLRotate B
	||  then  RRRotate A
*/
template<class Elem,typename Key>
_avl_node<Elem, Key>* _avltree<Elem, Key>::LRRotate(_avl_node<Elem,Key>*x) {
	x->left = LLRotate(x->left);
	return RRRotate(x);
}
/*
    ||
	||  four rotate
	||  RRRotate :    A       A        C
	||               1 B ==> 1 C ==> A   B
	||                C 2     3 B   1 3 4 2
	||               3 4       4 2
	||  firet RRRotate B
	||  then  LLRotate A
*/
template<class Elem,typename Key>
_avl_node<Elem, Key>* _avltree<Elem, Key>::RLRotate(_avl_node<Elem,Key>*x) {
	x->right = RRRotate(x->right);
	return LLRotate(x);
}
/*
	|| description:
	||		this operation maybe change Root
	||	so we return pointer to fixup Root pointer
	|| Insert operation
	||
*/
template<class Elem,typename Key>
_avl_node<Elem,Key>* _avltree<Elem, Key>::_avl_insert(_avl_node<Elem,Key> *&tree,_avl_node<Elem,Key> *&x) {
	if (tree == NIL) {
		tree = x;
	}
	else {
		if (tree->key > x->key) {
			tree->left = _avl_insert(tree->left, x);
			if (_height(tree->left) - _height(tree->right) == 2) {
				if (x->key<tree->left->left->key) {
					tree = RRRotate(tree);
				}
				else
					tree = LRRotate(tree);
			}
		}
		else if (tree->key < x->key) {
			tree->right = _avl_insert(tree->right, x);
			if ( _height( tree->right ) - _height(tree->left) == 2) {
				if (x->key>tree->right->right->key) {
					tree = LLRotate(tree);
				}
				else
					tree = RLRotate(tree);
			}
		}
		else {
			return NIL;
		}
	}
	tree->height = _max(_height(tree->left), _height(tree->right)) + 1;
	return tree;
}
/*
	||
	||	delete port
	||
*/
template<class Elem,typename Key>
void _avltree<Elem, Key>::Delete(Key key) {
	_avl_node<Elem, Key> *delete_node;
	delete_node = Search(key);
	if (delete_node == nullptr) {
		perror("this key don`t exists");
	}
	else {
		_avl_delete(Root,delete_node);
	}
}
/*
	|| @param : tree : tree`s root
	||			   x : to be deleted node
*/
template<class Elem,typename Key>
_avl_node<Elem,Key>* _avltree<Elem, Key>::_avl_delete(_avl_node<Elem,Key> *&tree,_avl_node<Elem, Key> *&x) {
	if (tree == NIL) {
		return NIL;
	}
	if (x->key < tree->key) {
		//删除左树节点--如果失衡--则旋右树
		tree->left = _avl_delete(tree->left, x);
		if (_abs(_height(tree->left) - _height(tree->right)) == 2) {
			_avl_node<Elem, Key> *r = tree->right;
			if (_height(r->left) < _height(r->right)) {
				tree = LLRotate(tree);
			}
			else
				tree = RLRotate(tree);
		}
	}
	else if (x->key > tree->key) {
		//删除右树节点--如果失衡--则旋左树
		tree->right = _avl_delete(tree->right, x);
		if (_abs(_height(tree->left) - _height(tree->right)) == 2) {
			_avl_node<Elem, Key> *r = tree->left;
			if (_height(r->left) > _height(r->right)) {
				tree = RRRotate(tree);
			}
			else
				tree = LRRotate(tree);
		}
	}
	else {
		//删除当前节点--链接
		if (tree->left != NIL&&tree->right != NIL) {
			//左右都不为空
			//找后继节点(或者前驱节点)代替(内容替换)
			//这取决于高度
			if (_height(tree->left) > _height(tree->right)) {
				//前驱
				_avl_node<Elem, Key> *Pre = tree->left;
				while (Pre->right != NIL) {
					Pre = Pre->right;
				}
				tree->key = Pre->key;
				tree->elem = Pre->elem;
				//移除Pre
				tree->left = _avl_delete(tree->left, Pre);
			}
			else {
				//后继
				_avl_node<Elem, Key> *Suc = tree->right;
				while (Suc->left != NIL) {
					Suc = Suc->left;
				}
				tree->key = Suc->key;
				tree->elem = Suc->elem;
				tree->right = _avl_delete(tree->right, Suc);
			}
		}
		else {
			_avl_node<Elem, Key>* temp = tree;
			if (tree->left != NIL) {
				tree = tree->left;
			}
			else
				tree = tree->right;
			delete temp;
		}
	}
	//tree->height = _max(_height(tree->left), _height(tree->right)) + 1;//update height althought i don`t know is it necessary
	if (tree->left->height > tree->right->height) {
		tree->height = tree->left->height + 1;
	}
	else tree->height = tree->right->height + 1;
	return tree;
}
#endif
