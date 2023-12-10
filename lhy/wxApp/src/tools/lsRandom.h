#ifndef LS_RANDOM_H
#define LS_RANDOM_H

/**
 * @brief 随机数生成算法
 * 
 * Ref : http://robotics.stanford.edu/users/sahami/cs121/code/random.c
 * 
 */

void InitRandom(void);

double RandomReal(double low, double high);

int RandomInteger(int low, int high);

#endif // LS_RANDOM_H
