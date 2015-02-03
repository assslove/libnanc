/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:	时间回调
 *
 *        Version:  1.0
 *        Created:  2014年12月04日 23时07分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  XiaoNan, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */


#include "timer.h"

struct tm g_cur_tm;
struct timeval g_now;
min_heap_t g_base_heap;
