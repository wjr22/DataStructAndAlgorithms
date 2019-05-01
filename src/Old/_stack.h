#pragma once
/*
	*--造个轮子玩玩
	*--writer  :  wjr
	*--last varsion fix time : 11/30/2017
	*--connect : wangjiaruo22@hotmail.com
	*--			 https://github.com/wjr22/
	*--attention : 模板不能定义实现分离，至于为什么自己百度
	*--	test 1 finished, when Elem is int it work;  --12/4/2017
*/
#ifndef _STACK_H
#define _STACK_H
#define		MAXSIZE		1024 
#define		LINESIZE	128

using namespace std;
template<class Elem>
class Stack {
	public:
		Elem		Top()const;		/*		不改变对象		*/	
		Elem		Pop();
		void		Push(Elem const &elem);
		bool		isEmpty()const;
		Stack();	
	private:
		Elem		*database[MAXSIZE];
		unsigned    tail;
		bool		Expension();	/*		动态创建			*/	
		bool		Destroy();		/*		 销毁			*/
		bool		isLineFull()const;/*     行满            */
		bool		isRowFull()const;/*      列满            */
		unsigned	flag;			/*	  保存database指针   */
};

#include"STACK.h"
#include<iostream>
/*
	*	method : Expendsion()
	*	description :	expends space
	*	
	*
*/
template<class Elem>
bool Stack<Elem>::Expension() {
	Elem	*NewSpace = new	Elem[LINESIZE];
	if (this->isLineFull()) {
		return false;
	}
	else {
		this->database[this->flag] = NewSpace;
		this->flag++; this->tail = 0;
		return true;
	}
}

/*
	*	method : Stack()
	*	description :	construtor
	*	
	*
*/
template<class Elem>
Stack<Elem>::Stack() {
	this->flag = 0;
	this->tail = 0;
	if(this->Expension());
}


/*
	*	method : Destroy()
	*	description :
	*	
	*
*/
template<class Elem>
bool Stack<Elem>::Destroy() {
	if (flag == 0) {
		return false;
	}
	else {
		delete[] database[this->flag];
                return true;
	}
}


/*
	*	method : isEmpty()
	*	description :
	*	
	*
*/
template<class Elem>
bool Stack<Elem>::isEmpty()const {
	if (flag == 0 && tail == 0) {
		return true;
	}
	return false;
}


/*
	*	method : isFull()
	*	description :
	*	
	*
*/
template<class Elem>
bool Stack<Elem>::isLineFull()const {
	if (flag == MAXSIZE ) {
		return true;
	}
	return false;
}

/*
	*	method : isFull()
	*	description :
	*	
	*
*/
template<class Elem>
bool Stack<Elem>::isRowFull()const {
	if (tail == LINESIZE)  {
		return true;
	}
	return false;
}

/*
	*	method : isEmpty()
	*	description :
	*	
	*
*/
template<class Elem>
void Stack<Elem>::Push(Elem const &elem) {
	if (this->isLineFull() && this->isRowFull())  {
		perror("满");
	}
	else {
		if (this->isRowFull()) {
			this->Expension();
		}
		this->database[flag-1][tail] = elem;
		tail++;
	}
}

/*
	*	method : Pop()
	*	description :
	*	
	*
*/
template<class Elem>
Elem Stack<Elem>::Pop() {
	Elem re;
	if (isEmpty()) {
		perror("空");
	}
	else if (tail == 0) {
		this->flag--; this->tail = LINESIZE-1 ;
	}
	else {
		this->tail--;
	}
	re = this->database[this->flag-1][this->tail];
	return re;
}

/*
	*	method : Top()
	*	description :
	*	
	*
*/
template<class Elem>
Elem Stack<Elem>::Top()const {
	Elem re;
	if (isEmpty()) {
		cerr >> "栈为空";
	}
	else if (tail == 0) {
		re = this->database[flag-1][LINESIZE-1];
	}
	else {
		re = this->database[flag][tail-1];
	}
	return re;
}
#endif
