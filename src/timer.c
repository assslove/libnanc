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

inline void refresh_time()
{
	gettimeofday(&g_now, 0);
	localtime_r(&g_now.tv_sec, &g_cur_tm);
}

inline time_t get_now_tv() 
{
	return g_now.tv_sec;
}

inline struct tm* get_now_tm() 
{
	return &g_cur_tm;
}


inline void timer_handle()
{
	refresh_time();

	static time_t last; //最后一次时间
	if (last != g_now.tv_sec) {
		last = g_now.tv_sec;

		heap_timer_t *item;
		while ((item = min_heap_top(&g_base_heap)) != NULL) {
			if (item && item->expire <= last && item->func) { //如果时间到
				item->func(&(item->owner), &(item->data)); //调用函数
				continue;
			} 
			break;
		}
	}
}

inline int add_timer_event(int timerid_, time_t expire_, timer_callback_t func_, void *owner_, void *data_)
{
	heap_timer_t* item = (heap_timer_t *)malloc(sizeof(heap_timer_t));
	item->expire = expire_;
	item->owner = owner_;
	item->data = data_;
	item->func = func_;
	item->timer_id = timerid_;

	return min_heap_push(&g_base_heap, item);
}


/* @brief 定时器初始化
 */
inline void timer_init()
{
	min_heap_ctor(&g_base_heap);
}

/* @brief 定时器销毁
 */
inline void timer_fini()
{
	heap_timer_t *item;
	while ((item = min_heap_top(&g_base_heap)) != NULL) {
		if (item) {
			REMOVE_TIMER_EVENT(item);
		}
	}
	min_heap_dtor(&g_base_heap);
}

