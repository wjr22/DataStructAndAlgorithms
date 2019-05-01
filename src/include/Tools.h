//
// Created by wangj on 2019/5/1.
//

#ifndef DATASTRUCT_TOOLS_H
#define DATASTRUCT_TOOLS_H


class Tools {
public:
    template<typename TYPE>
    static void swap(TYPE &a, TYPE &b);    //  交换

    template<typename TYPE>
    static void Reverce(TYPE *A, int start, int end);          //  翻转数组
private:
};
/**
 *
 * @tparam TYPE
 * @param a
 * @param b
 */
template<typename TYPE>
void Tools::swap(TYPE &a, TYPE &b) {
    TYPE c = b;
    b = a;
    a = c;
}
/**
 *
 * @tparam TYPE
 * @param A
 * @param start 开始下标
 * @param end   结束下标
 */
template<typename TYPE>
void Tools::Reverce(TYPE *A, int start, int end) {
    for(int i=start; i<(start + (end-start+1)/2); i++){
        swap(A[i],A[end-i+start]);
    }
}


#endif //DATASTRUCT_TOOLS_H
