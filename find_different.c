/*
 * ==============================================================================
 *
 *       Filename:  @(#)find_different.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Sun May 26 03:35:10 2013
 *        Changed:  < >
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xwhuang
 *          Email:  huangxiaoweigx@gmail.com
 *
 * ==============================================================================
 */


#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef enum {
    DO_WEIGHT_STATUS_EQ = 0,    /**< left == right */
    DO_WEIGHT_STATUS_LE = 1,    /**< left <  right */
    DO_WEIGHT_STATUS_GT = 2,    /**< left >  right */
    DO_WEIGHT_STATUS_EXCEED_LIMIT_TIME = 3, /**< cnt > 3 */
}DO_WEIGHT_STATUS;

#define ASSERT_NO_EXCEED_LIMIT_TIME(flag) assert((flag) != DO_WEIGHT_STATUS_EXCEED_LIMIT_TIME)

const char* msg[] = {
    "left == right",
    "left <  right",
    "left >  right",
    "exceed limit time",
     NULL,
};


int cnt = 1;

static int __do_weight(int left, int right)
{
    if (cnt > 3) { //最多能调用这个函数3次，
        return DO_WEIGHT_STATUS_EXCEED_LIMIT_TIME;
    }
    cnt++;
    if (left == right) {
        return DO_WEIGHT_STATUS_EQ;
    } else if (left > right) {
        return DO_WEIGHT_STATUS_GT;
    } else {
        return DO_WEIGHT_STATUS_LE;
    }
}

/** 
 * @brief 
 * 
 * @param array 
 * @param n 
 * 
 * @return 
 */
int get_difference(int *array, int n)
{
    
    int left = 0, right = 0, other;
    int i = 0;
    int flag;

    assert(n == 12);
    for (i = 0; i < 4; i++) {
        left += array[i];       /**< 0-3 */
        right += array[4+i];    /**< 4-7 */
    }

    flag = __do_weight(left, right);
    ASSERT_NO_EXCEED_LIMIT_TIME(flag);

    if (flag == DO_WEIGHT_STATUS_EQ) { /**< the different bobble is in 8-11. */        
        left = left - array[3];        /**< 0-2 */
        right = array[8] + array[9] + array[10]; /**< 8-10 */
        flag = __do_weight(left, right);
        ASSERT_NO_EXCEED_LIMIT_TIME(flag);

        if (flag == DO_WEIGHT_STATUS_EQ) { /**< the different bobble is 11*/
            return 11;
        }
        int tmp_flag = __do_weight(array[8], array[9]);
        ASSERT_NO_EXCEED_LIMIT_TIME(tmp_flag);
        if (tmp_flag == DO_WEIGHT_STATUS_EQ) {
            return 10;
        } else if (tmp_flag == DO_WEIGHT_STATUS_LE) {
            if (flag == DO_WEIGHT_STATUS_LE) {
                return 9;
            }
            return 8;
        } else {
            if (flag == DO_WEIGHT_STATUS_LE) {
                return 8;
            }
            return 9;
        }
    } else {                    /**< the different bobble is in 0-7 */
        int sec_flag;
        int third_flag;

        left = array[8] + array[9] + array[10] + array[4]; /**< 8-10, 4 */
        right = array[5] + array[6] + array[7] + array[3]; /**< 5-7, 3 */
        sec_flag = __do_weight(left, right);
        ASSERT_NO_EXCEED_LIMIT_TIME(sec_flag);

        if (sec_flag == DO_WEIGHT_STATUS_EQ) { /**< the different bobble is in 0-2 */
            third_flag = __do_weight(array[0], array[1]);
            ASSERT_NO_EXCEED_LIMIT_TIME(third_flag);

            if (third_flag == DO_WEIGHT_STATUS_EQ) {
                return 2;
            } 

            if (flag == DO_WEIGHT_STATUS_LE) { /**< the different bobble is lighter than others */
                if (third_flag == DO_WEIGHT_STATUS_LE) {
                    return 0;
                }
                return 1;
            } else {                    /**<the different bobble is weighter than others */
                if (third_flag == DO_WEIGHT_STATUS_LE) {
                    return 1;
                }
                return 0;
            }
        }

        if (sec_flag == flag) { /**< the different bobble is in 5-7, do you know why ? */
            third_flag = __do_weight(array[5], array[6]);
            ASSERT_NO_EXCEED_LIMIT_TIME(third_flag);

            if (third_flag == DO_WEIGHT_STATUS_EQ) {
                return 7;
            }
            if (flag == DO_WEIGHT_STATUS_GT) { /**< the difference is lighter than others */
                if (third_flag == DO_WEIGHT_STATUS_LE) {
                    return 5;
                }
                return 6;
            } else { /**< the difference is weighter than others */
                if (third_flag == DO_WEIGHT_STATUS_LE) {
                    return 6;
                }
                return 5;
            }
        } else {                /**< the differenc is 3 or 4 */
            third_flag = __do_weight(array[11], array[3]);
            ASSERT_NO_EXCEED_LIMIT_TIME(third_flag);

            if (third_flag == DO_WEIGHT_STATUS_EQ) {
                return 4;
            }
            return 3;
        }
    }

    return -1;
}


int main()
{
    int array[12] = {0};
    int i;
    int w;
    int diff;

    while(1) {
        cnt = 1;
        printf("set bobble's weight ="); scanf("%d", &w);
        for (i = 0; i < 12; i++) {
            array[i] = w;
        }
        printf("set the difference position(1-12):");scanf("%d", &i);
        if ((i > 12) || (i < 0)) {
            printf("***************new input*****************\n\n");
            continue;
        }
        printf("input the different value:");scanf("%d", &diff);
        array[i-1] = diff;

        for (i = 0; i < 12; i++) {
            printf("%d  ", array[i]);
        }        
        printf("\n");
        
        printf("the different is %d\n", get_difference(array, 12) + 1);

        printf("***************new input*****************\n\n");
    }

    return 0;
}
