//
// Created by wangj on 2019/5/1.
//  暂时不考虑继承
//  单向链表(循环)
//  有头结点、头指针

#ifndef DATASTRUCT_LINKEDLIST_H
#define DATASTRUCT_LINKEDLIST_H

#include <cstdint>
#include <cstdlib>

template<typename T>
class LinkedList{
public:
    bool    circle = false; //是否循环（即尾指针是不是空）
    int64_t length = 0;     //长度
    struct Node{
        T   * dataPtr;
        struct Node * nextPtr;
    };

    struct Node * headPtr = nullptr;

    LinkedList(){
        //Node n;
        //headPtr = &n;
        //headPtr->nextPtr= nullptr;
    }
    LinkedList(bool isCircle){
        this->circle = true;
        //Node n;
        //headPtr = &n;
        //headPtr->nextPtr=headPtr;
    }
    /**
     * 头插法
     * @param Element
     * @return
     */
    bool InsertH(T *Element);

    /**
     * 尾插法
     * @param Element
     * @return
     */
    bool InsertL(T *Element);

    /**
     * 按顺序插
     * @param Element
     * @return
     */
    bool InsertInOrder(T *Element, bool (*compare)(T E1, T E2));
    // 内联直接比较法
    bool InsertInOrder(T *Element);

    /**
     * 查
     * @param Element
     * @return
     */
    Node * Search(T Element) {
        if(length == 0){
            return nullptr;
        }
        Node *ptr = headPtr;
        while(ptr->nextPtr != nullptr || ptr->nextPtr != headPtr){
            if(*(ptr->dataPtr) == Element){
                return ptr;
            }
            ptr = ptr->nextPtr;
        }
        return nullptr;
    }

    /**
     * 删除
     * @param Element
     * @return
     */
    bool Delete(T Element);
    /**
     * 翻转链表
     */
    LinkedList<T> Reverse();

    /**
     * 归并两个链表
     * @param A
     * @param B
     * @return
     */
    LinkedList<T> MergeOrder(LinkedList<T> A,LinkedList<T> B);

private:
    inline static bool compare(T E1, T E2){
        return E1<E2;
    }
};

template<typename T>
bool LinkedList<T>::InsertH(T *Element) {
    Node node;
    node.dataPtr = Element;
    if(headPtr == nullptr){
        headPtr = &node;
        if(this->circle)
            headPtr->nextPtr = headPtr;
        else
            headPtr->nextPtr = nullptr;
    }else{
        if(this->circle){
            //循环链表
            Node *ptr = headPtr;
            while(ptr->nextPtr != headPtr){
                //找到尾指针
                ptr = ptr->nextPtr;
            }
            node.nextPtr = headPtr;
            ptr->nextPtr = node;
        }
        headPtr = &node;

    }
    this->length++;

    return true;
}

template<typename T>
bool LinkedList<T>::InsertL(T *Element) {
    Node node;
    node.dataPtr = Element;
    Node *ptr = headPtr;
    while(ptr != nullptr || ptr != headPtr){
        //循环或者不循环，找到尾部
        ptr = ptr->nextPtr;
    }
    ptr->nextPtr = &node;
    node.nextPtr = headPtr;
    length++;
    return true;
}

template<typename T>
bool LinkedList<T>::Delete(T Element) {
    if(length == 0){
        return false;
    }
    Node * current = headPtr->nextPtr;  //当前结点pointer，从第二个开始。。
    Node * prev = headPtr;        //前驱结点pointer
    while((current != nullptr || current != headPtr) && *(current->dataPtr) != Element){
        current = current->nextPtr;prev = prev->nextPtr;
    }
    if(current == nullptr || current == headPtr){
        // 没找到
        return false;
    }
    prev->nextPtr = current->nextPtr;
    delete current;
    length--;
    return true;

}
//顺序插入
template<typename T>
bool LinkedList<T>::InsertInOrder(T *Element, bool (*compare)(T, T)) {
    Node *current,*prev;
    Node node;
    node.dataPtr = Element;
    if(this->length == 0)
        headPtr = &node;
    else{
        current = headPtr->nextPtr;
        prev = headPtr;
        if(this->circle) {
            while (current->nextPtr != headPtr) {
                if (compare(current->dataPtr, Element)) {
                    current = current->nextPtr;
                    prev = prev->nextPtr;
                }else
                    break;
            }
            prev->nextPtr = &node;
            if(current->nextPtr == headPtr){
                node.nextPtr = headPtr;
            }
        }
        else {
            while (current != nullptr) {
                if (compare(current->dataPtr, Element)) {
                    current = current->nextPtr;
                    prev = prev->nextPtr;
                }else
                    break;
            }
            prev->nextPtr = &node;
            node.nextPtr = current;
        }
    }
    return false;
}
//默认比较方法
template<typename T>
bool LinkedList<T>::InsertInOrder(T *Element) {
    InsertInOrder(Element,compare);
    return true;
}
/*------------------------------------------------
 * 翻转链表，从新构建一个链表，然后头插法即可,狸猫换太子
 *------------------------------------------------
 */
template<typename T>
LinkedList<T> LinkedList<T>::Reverse() {
    LinkedList<T> N;
    N.circle = this->circle;
    Node * ptr = this->headPtr;
    if(this->length == 0){
        return N;
    }
    if(circle)
        while (ptr->nextPtr != headPtr) {
            N.InsertH(ptr->dataPtr);
            Node * temp = ptr;
            ptr = ptr->nextPtr;
            delete temp;
        }
    else
        while(ptr != nullptr){
            N.InsertH(ptr->dataPtr);
            Node * temp = ptr;
            ptr = ptr->nextPtr;
            delete temp;
        }
        delete this;
    return N;
}

/*-----------------------------------------------
 *
 * 合并两个有序列表，并取交集
 *
 * ----------------------------------------------
 */
template<typename T>
LinkedList<T> LinkedList<T>::MergeOrder(LinkedList<T> A, LinkedList<T> B) {
    LinkedList<T> L;
    int i=abs(static_cast<int>(A.length - B.length));
    Node * aptr = A.headPtr;
    Node * bptr = B.headPtr;
    if(A.length < B.length){
        while(i >= 0){
            i--;
            L.Inser
            bptr = bptr->nextPtr;
        }
    }
    return L;
}


#endif //DATASTRUCT_LINKEDLIST_H
