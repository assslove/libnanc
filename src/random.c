/*
 * =====================================================================================
 *
 *       Filename:  random.c
 *
 *    Description:  随机数定义
 *
 *        Version:  1.0
 *        Created:  2015年03月16日 20时27分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "random.h"

int random_range(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
