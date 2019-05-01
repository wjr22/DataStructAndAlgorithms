//
// Created by wangj on 2019/5/1.
//

#include "../include/LinerStruct.h"
#include "../include/Tools.h"
#include "../Header.h"
/**
 * 删除线性表种s-e之间所有数
 * 思路：去掉多少个后面就往前移动多少个
 */
bool DeleteFLTE(LinerList<int> &L,int s,int e){
    int k=0;
    for(int i=0; i<L.length; i++){
        if(L.Data[i]<=e &&L.Data[i]>=s){
            k++;//记录去掉个数
        }else if(k != 0){
            L.Data[i-k] = L.Data[i];
        }
    }
    // 去掉尾部
    L.length = L.length - k;
    return true;
}

/**
  * 发现主元素，即相同元素出现超过半数的元素
  * 思路：找候选元素，因为要求超过半数，所以假设当前元素为最多，计数，如果不是则减1，
  * 到0换元素，最后留下的元素一定是最多的，再统计该元素个数即可，时间复杂度O(2N)
  */
int foundMajor(const LinerList<int> &L){
    int count = 1; // 计数器怎么可能从0开始呢
    int major = L.Data[0];
    for(int i=1; i<L.length;i++) {
        if (L.Data[i] == major)
            count++;
        else {
            count--;
            if (count == 0) {
                count = 1;
                major = L.Data[i];
            }
        }
    }
    count = 0;
    for(int i=0; i<L.length; i++){
        if(L.Data[i] == major){
            count ++;
        }
    }
    if(count > L.length/2){
        return major;
    }
    else
        return -1;
}


/**
 * 合并两个相同类型的（无序）线性表
 * @tparam T
 * @param a
 * @param b
 */
template<typename T>
LinerList<T> marge(LinerList<T> &a, LinerList<T> &b, bool (*compare)(T ea, T eb)){
    a.Sort(0,a.length,compare);
    b.Sort(0,a.length,compare);
    margeByOrder(a,b);
}
