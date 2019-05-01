/*
 *	扫雷关键部分（无雷区自动拓展）（伪代码）
 *	原来写的格磁盘忘保存了
 *	write time : 12/17/2017 
 */
 /* data structure */
#define TRUE   1
#define FALSE  0
struct Point
{
	int x;
	int y;
};
struct _Mine{
	struct Point 	it;
	_bool   		isPass;
	_bool			isMine;
};
typedef int _bool;
typedef struct _Mine Mine[MAXSIZE_ROW][MAXSIZE_LINE];
int direction_vector[2][2]={0,1,-1,1};
/* 
 *	use breath first search to expand
 */
/*
 * 	Need Supput :
 *  _bool isExist(struct Mine it) :
 *		if exist : return true,else : return false;
 *	_bool CanExpand(struct Mine it) : 
 *		if there is no mine arround this point return true,else return false;
 * void Print(struct Mine it) :
 *		Show this Point;
 * ----------------------------queue operate
 * void InitQueue(_type,queue Q); 
 * void enqueue(Queue Q,struct Mine);
 * struct Mine dequeue(Queue Q);
 * _bool Empty();
 */

void Expand(struct _Mine it){
	if(it.isMine==TRUE){
		End();
	}else{
		if(!CanExpand(it)){
			Print(it);
		}else{
			InitQueue(Q);
			enqueue(Q,it);
			while(!Q.Empty()){
				u=dequeue(Q);
				u.isPass=TRUE;
				for each Point v arround u (v isExist and Not isPass) 
					//------case 1
					if CanExpand v 
						enqueue(Q,v);
					v.isPass=TRUE;
					Print(v);
				Print(u);
			}
		}

	}
}
/*
 *	case 1 : it can use vertor to solve the problem faster
 *		for(int x=-1;x<2;x++){
 *			for(int y=-1;y<2;y++){
 *				v=Mine[u.it.x-x][u.it.y-y];	
 *				if(v.isExist&&!v.isPass){
 *					if(CanExpand(v))
 *						enqueue(Q,v);
 *					v.isPass=TRUE;
 *					Print(v);
 *				}
 *			}
 *      }
 */