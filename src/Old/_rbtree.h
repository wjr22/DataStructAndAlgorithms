/*
	*--description
	*--		_rbtree.h : 红黑树字典操作
	*--writer  :  wjr
	*--last varsion fix time : 12/4/2017
	*--connect : wangjiaruo22@hotmail.com
	*--			 https://github.com/wjr22/
	*--		version :				descritpion :
	*--			1.0.1 : 12/1/2017                 	definition data-struction 
	*--							   	finish insert\search and they`re port
	*--									private operation : right-rotate and left-rotate 
	*--																rbtree-insert-fixup
	*--								test :		insert and search test finished
	*--			1.0.2 : 12/3/2017		   	finish delete and rbtree-delete-fixup but there has some bug
	*--								test :      	failed;
*/
#ifndef		_RBTREE_H
#define		_RBTREE_H
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
/*
	||	数据结构定义
	||
*/
enum Color {
	Red, Black
};
template<class elem,typename Key>
class RBNode {
	public:
		elem		data;
		Key			key;
		RBNode		*left;
		RBNode		*right;
		RBNode		*parent;
		Color		color;
};

template<class elem,typename Key>
class RBTree {
	public:
		/*----字段----*/
		RBNode<elem, Key>   *NIL;
		RBNode<elem, Key>   *Root;
		/*----方法----*/
		RBTree();
		RBNode<elem, Key>*	Search(Key const key)const;
		void				Insert( elem const data, Key const key);
		bool				Delete(Key key);
		void				PreorderPrint(RBNode<elem, Key>*Root)const; /*--for test--*/
	private:
		void				LeftRotate(RBNode<elem,Key>* &Root,RBNode<elem,Key>*x);
		void				RightRotate(RBNode<elem,Key>* &Root,RBNode<elem,Key>*x);
		void				rbtree_insert_fixup(RBNode<elem, Key>* &Root, RBNode<elem, Key>*x);
		bool				Insert(RBNode<elem, Key>*&Root, elem const data, Key const key);
		void				rbtree_delete(RBNode<elem, Key>*&Root, RBNode<elem, Key>*x);
		void				rbtree_delete_fixup(RBNode<elem, Key>*&Root, RBNode<elem, Key>*x);
		void				rb_transplant(RBNode<elem, Key>*&u, RBNode<elem, Key>*&v);

};
/*
	||构造函数
*/
template<class elem,typename Key>
RBTree<elem,Key>::RBTree() {
	Root = nullptr;
	NIL = nullptr;
}
/*
	||
	||
*/
template<class elem,typename Key>
void RBTree<elem, Key>::LeftRotate(RBNode<elem, Key>*&Root, RBNode<elem, Key> * x) {
	RBNode<elem, Key>*y=x->right;	//set y
	
	x->right = y->left;				//turn y`s left subtree into x`s right subtree	

	if (y->left != NIL) {		
		y->left->parent = x;
	}
	y->parent = x->parent;			

	if (x->parent == NIL) {
		Root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}


template<class elem,typename Key>
void RBTree<elem,Key>::RightRotate(RBNode<elem, Key>*&Root, RBNode<elem, Key>* x) {
	RBNode<elem, Key>*y = x->left;
	x->left = y->right;
	
	if (y->right!=NIL) {
		y->right->parent = x;
	}
	
	y->parent = x->parent;
	if (x->parent == NIL) {
		Root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else x->parent->right = y;

	y->right = x;
	x->parent = y;
}


template<class elem,typename Key>
bool RBTree<elem, Key>::Insert(RBNode<elem, Key>* &Root, elem const data, Key key) {
	RBNode<elem, Key> *npt = new RBNode<elem, Key>;
	RBNode<elem, Key> *parent = Root;
	RBNode<elem, Key> *current = Root;
	while (current != nullptr) {
		parent = current;
		if (key < current->key) {
			current = current->left;
		}
		else if (key != current->key)  {
			current = current->right;
		}
		else {
			perror("this key already exists");
		}
	}
	npt->data = data; npt->key = key;
	npt->color = Red;
	npt->left = npt->right = NIL; npt->parent = parent;
	if (Root == nullptr) {
		Root = npt;
	}
	else if (npt->key < parent->key)  {
		parent->left = npt;
	}else{
		parent->right = npt;
	}
	rbtree_insert_fixup(Root,npt);
	return true;
}


template<class elem,typename Key>
void RBTree<elem, Key>::rbtree_insert_fixup(RBNode<elem, Key>*&Root, RBNode<elem, Key>*x) {
	RBNode<elem, Key>*p, *gp;
	RBNode<elem, Key>*uncle;
	while ((p = x->parent) && p->color == Red)  {
		gp = x->parent->parent;
		if (p == gp->left) {
			uncle = gp->right;
			if (uncle != NIL&&uncle->color == Red)  {
				p->color = Black;
				uncle->color = Black;
				gp->color = Red;
				x = gp;
			}
			else {
				if (x == p->left) {
					x->parent->color = Black;
					gp->color = Red;
					RightRotate(Root, gp);
				}
				else {
					x = p;
					LeftRotate(Root, x);
				}
			}
		}
		else {
			uncle = gp->left;
			if (uncle != NIL&&uncle->color == Red) {
				p->color = Black;
				gp->color = Red;
				uncle->color = Black;
				x = gp;
			}
			else {
				if (x == p->left) {
					x = p;
					RightRotate(Root, x);
				}
				else {
					p->color = Black;
					gp->color = Red;
					LeftRotate(Root, gp);
				}
			}
		}
	}
	Root->color = Black;
}


template<class elem,typename Key>
void RBTree<elem, Key>::Insert(elem data, Key key) {
	if(Insert((this->Root), data, key));


}


template<class elem,typename Key>
void RBTree<elem,Key>::PreorderPrint(RBNode<elem, Key>*Root)const {
	if (Root == nullptr) {
		return;
	}
	else {
		cout << Root->key;
		if (Root->color == Red) {
			printf("\t Red");
		}
		else {
			printf("\t Black");
		}
		if (Root->left) {
			printf("left: %3d ", Root->left->key);
		}
		if (Root->right) {
			printf("    right: %3d", Root->right->key);
		}
		printf("\n");
		PreorderPrint(Root->left);
		PreorderPrint(Root->right);
	}
	
}


template<class elem,typename Key>
RBNode<elem, Key>*	RBTree<elem,Key>::Search(Key const key)const {
	RBNode<elem, Key>* res;
	RBNode<elem, Key>* rpt = Root;
	while (rpt != nullptr&&rpt->key != key)  {
		if (rpt->key < key) {
			rpt = rpt->right;
		}
		else {
			rpt = rpt->left;
		}
	}
	if (rpt == nullptr) {
		return nullptr;
	}
	return rpt;
}

template<class elem,typename Key>
bool RBTree<elem, Key>::Delete(Key key) {
	RBNode<elem, Key>* deptr;
	deptr = Search(key);
	if (deptr == nullptr) {
		return false;
	}
	rbtree_delete(this->Root, deptr);
	return true;
}
/*
	||
	|| compare to binary-search-tree`s delete,this only add a color-recorder
	||  and only when replace-node(y)`s color is Black ,this tree need fixup
	||  to maintain red-black-tree`s nature   
	||
	|| ! ! ! ! !
	||    this method and fixup method are wrong method,it needs debug
	|| ! ! ! ! !
*/
template<class elem,typename Key>
void RBTree<elem, Key>::rbtree_delete(RBNode<elem,Key>*&Root,RBNode<elem,Key>*x) {
	RBNode<elem, Key>*y, *z;
	Color follow_color = x->color;					//following element`s color
	if (x->left == NIL) {
		z = x->right;
		if (z != NIL) {
			rb_transplant(z, z->right);
		}
		else x = NIL;
	}
	else if (x->right == NIL) {
		z = x->left;
		if (z != NIL) {
			rb_transplant(z, z->left);
		}
		else x = NIL;
	}
	else {
		// search x`s following element and assigned to y;
		y = x->right;
		while (y->left != NIL) {
			y = y->left;
		}
		z = y->right;				//y Only have right-subtree;
		follow_color = y->color;
		if (y->parent == x) {
			z->parent = y;
		}else{
			rb_transplant(y, y->right);	//make y`s right-subtree to replace y;
			y->right = x->right;			//link x`s right-subtree to y`s right-pointer;
			y->right->parent = y;
		}
		rb_transplant(x, y);
		y->left = x->left;
		x->left->parent = y;
		y->color = x->color;
	}
	if (follow_color == Black) {
		rbtree_delete_fixup(Root, x);
	}
}
template<class elem, typename Key>
inline void RBTree<elem, Key>::rbtree_delete_fixup(RBNode<elem, Key>*& Root, RBNode<elem, Key>* x){
	RBNode<elem, Key> *w;
	while (x != Root&&x->color == Black)  {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == Red) {
				w->color = Black;
				x->parent->color = Red;
				LeftRotate(Root, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == Black&&w->right->color == Black) {
				w->color = Red;
				x = x->parent;
			}
			else if (w->right->color == Black) {
				w->left->color = Black;
				w->color = Red;
				RightRotate(Root, w);
				w = x->parent->right;
			}
			else {
				w->color = x->parent->color;
				x->parent->color = Black;
				w->right->color = Black;
				LeftRotate(Root,x->parent);
				x = Root;
			}
		}
		else {
			w = x->parent->left;
			if (w->color == Red) {
				w->color = Black;
				x->parent->color = Red;
				RightRotate(Root,x->parent);
				w = x->parent->right;
			}
			if (w->right->color == Black&&w->left->color == Black) {
				w->color = Red;
				x = x->parent;
			}
			else if (w->left->color == Black) {
				w->right->color = Black;
				w->color = Red;
				LeftRotate(Root, w);
				w = x->parent->right;
			}
			else {
				w->color = x->parent->color;
				x->parent->color = Black;
				w->left->color = Black;
				RightRotate(Root, x->parent);
				x = Root;
			}
		}
	}
	x->color = Black;
}
/*
	||
	|| to use subtree-v replace u(Node)
	||
	||
*/
template<class elem, typename Key>
inline void RBTree<elem, Key>::rb_transplant(RBNode<elem, Key>*& u, RBNode<elem, Key>*& v){
	if (u->parent == Root) {
		Root = v;
	}
	else if (u == u->parent->left)  {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}
#endif
