//
// Created by wangj on 2019/4/30.
// 线性表
// 常用操作：CURD、排序、去重、合并
//

#ifndef DATASTRUCT_LINERSTRUCT_H
#define DATASTRUCT_LINERSTRUCT_H

#include <stdint-gcc.h>
#include "Tools.h"
#include <algorithm>

template <typename DataType>
class LinerList {
public:
    int64_t             length;
    int                 typeSize;
    DataType        *   Data;       //数据域，模板编程大大的好

    /**
     * 根据类型与长度生成
     * @param length
     */
    LinerList(int length){
        Data = new DataType[length];
    }
    /**
     * 根据已有数组生成
     * @param data
     * @param len sizeof(data)
     */
    LinerList(DataType data[], int64_t len){
        typeSize = sizeof(DataType);
        length = len/typeSize;
        Data = data;
    }
    ~LinerList(){}
    /**
      * 反转数组，from start to end.
      * @tparam DataType
      * @param start
      * @param end
      */
    void Reverse(int64_t start,int64_t end);

    /**
     * 在index上插入元素,如果超过最大限度返回false
     * @param element
     * @param index
     * @return
     */
    bool Insert(DataType element, int64_t index);

    bool Delete(int64_t index);
    /**
     * 排序，采用快排，O(nlog(n))
     * ----原址排序,排序规则为compare函数，下标从0开始
     * @param start     开始下标（包含）
     * @param end       结束下标（包含）
     * @param compare if this function return true, it's means a < b.
     */
    void Sort(int64_t start, int64_t end, bool (*compare)(DataType a,DataType b));

    void Sort();

    LinerList<DataType> margeByOrder(LinerList<DataType> &a, LinerList<DataType> &b, bool (*compare)(DataType ea,DataType eb));


private:
    int portion(int64_t l, int64_t r, bool (*compare)(DataType a,DataType b));
};

template<typename DataType>
void LinerList<DataType>::Reverse(int64_t start,int64_t end) {
    Tools::Reverce(this->Data, static_cast<int>(start), static_cast<int>(end));
}

/* -----------------------------------------
 * 重新生成空间，拷贝，插入。
 * -----------------------------------------
 */
template<typename DataType>
bool LinerList<DataType>::Insert(DataType element, int64_t index) {
    if((this->length+1)>= INT64_MAX || index < 0){
        return false;
    }
    DataType * T= new DataType[this->length+1];
    std::copy(this->Data,T);
    this->Data = T;
    for(int i= static_cast<int>(this->length); i > index; i--){
        this->Data[i] = this->Data[i-1];
    }
    this->length = this->length+1;
    this->Data[index] = element;
    return true;
}

template<typename DataType>
void LinerList<DataType>::Sort(int64_t start, int64_t end, bool (*compare)(DataType a, DataType b)) {
    if(start < end){
        int p = portion(start,end, compare);
        Sort(start,p-1,compare);
        Sort(p+1,end,compare);
    }
}

template<typename DataType>
void LinerList<DataType>::Sort() {
    // 实现方法1 递归
    // Sort(0,this->length);
    // 法2

}
/*-----------------------------------------
 * 采用选择右端为标杆
 * @tparam DataType
 * @param l
 * @param r
 * @return
 * ----------------------------------------
 */
template<typename DataType>
int LinerList<DataType>::portion(int64_t l, int64_t r, bool (*compare)(DataType a,DataType b)) {
    DataType temp = this->Data[r];
    int j = static_cast<int>(l - 1);
    for(int i= static_cast<int>(l); i < r; i++){
        if(compare(this->Data[i],temp)) {
            j++;
            if (i != j) {
                Tools::swap(this->Data[i],this->Data[j]);
            }
        }
    }
    j++;
    Tools::swap(this->Data[j], this->Data[r]);
    return j;
}
/*---------------------------------
 * 实现思路与Insert一致，过程相反
 *----------------------------------
 */
template<typename DataType>
bool LinerList<DataType>::Delete(int64_t index) {

    return false;
}
/**
 * 合并两个相同类型的（有序）线性表
 * 返回也是有序的，所以要传一个比较函数
 * @tparam T
 * @param a
 * @param b
 */
template<typename DataType>
LinerList<DataType> LinerList<DataType>::margeByOrder(LinerList<DataType> &a, LinerList<DataType> &b, bool (*compare)(DataType ea,DataType eb)){
    LinerList<DataType> r(static_cast<int>(a.length + b.length));
    int i=0, j=0;
    int k=0;
    while(i<a.length && j < b.length){
        if(compare(a.Data[i],b.Data[j])){
            i++;
            r.Data[k] = a.Data[i];
        }else{
            j++;
            r.Data[k] = a.Data[j];
        }
        k++;
    }
    if(i == a.length){
        //把b剩下的合并
        while(j < b.length){
            r.Data[k] = b.Data[j];
            k++;j++;
        }
    }else{
        //把a剩下的合并
        while(i < a.length){
            r.Data[k] = a.Data[i];
            i++;k++;
        }
    }
    delete a;
    delete b;   //别忘了删掉多的
    return r;
}

#endif //DATASTRUCT_LINERSTRUCT_H
