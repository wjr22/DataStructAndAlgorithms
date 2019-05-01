//
// Created by wangj on 2019/4/30.
//  主要有单链表(1)、单循环链表(2)、双向链表(3)、双向循环链表(4)。全部按双向循环链表实现
//  主要操作：CURD、翻转、排序、合并等

#ifndef DATASTRUCT_LINKEDLIST_H
#define DATASTRUCT_LINKEDLIST_H
/**
 *
 * @tparam T：数据类型
 */
template<typename T>
class DoubleLinkedList {
public:
    int length ;
    struct Node {
        struct Node *nextptr;
        T           *Dataptr;
        struct Node *prevptr;
    };
    struct Node     *Headptr;  // 头指针

    /**
     * 默认单链表
     */
    DoubleLinkedList(){
        Init();
    }

    ~DoubleLinkedList();

    /**
     * 头插法
     * @param element
     * @return
     */
    bool InsertInHead(T *element);

    bool InsertInLast(T *element);
private:
    void Init();
};

template<typename T>
void DoubleLinkedList<T>::Init() {
    struct Node head;
    Headptr = &head;
    Headptr->Dataptr = nullptr;
    Headptr->nextptr = Headptr;
    Headptr->prevptr = Headptr;
    length = 0;
}

/*--------------------------------------------------
 *
 * -------------------------------------------------
 */
template<typename T>
bool DoubleLinkedList<T>::InsertInHead(T *element) {
    if(Headptr->Dataptr == nullptr){
        //空表
        Headptr->Dataptr = element;
    }else {
        struct Node newNode;
        newNode.Dataptr = element;

        newNode.nextptr = Headptr->nextptr;     //新结点的后继
        newNode.prevptr = Headptr->prevptr;     //新结点的前驱为尾节点
        Headptr = &newNode;
        newNode.nextptr->prevptr = newNode;     //原头节点的前驱
        newNode.prevptr->nextptr = &newNode;    //尾节点的前驱为头节点
    }
    return false;
}
/*---------------------------------------------------
 *  尾插法，先找到结束再插
 * --------------------------------------------------
 */
template<typename T>
bool DoubleLinkedList<T>::InsertInLast(T *) {

    return false;
}


#endif //DATASTRUCT_LINKEDLIST_H
