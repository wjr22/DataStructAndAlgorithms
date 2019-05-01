//
// Created by wangj on 2019/5/1.
//

#ifndef DATASTRUCT_HEADER_H
#define DATASTRUCT_HEADER_H

#pragma once

#include "include/LinerStruct.h"

/**
 *
 * @param L
 * @param s
 * @param e
 * @return
 */
bool DeleteFLTE(LinerList<int> &L, int s, int e);
/**
 *
 * @param L
 * @return
 */
int foundMajor(const LinerList<int> &L);
/**
 *
 * @tparam T
 * @param a
 * @param b
 * @param compare
 * @return
 */
template<typename T>
LinerList<T> margeByOrder(LinerList<T> &a, LinerList<T> &b, bool (*compare)(T ea,T eb);

#endif //DATASTRUCT_HEADER_H
