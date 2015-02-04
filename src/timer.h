#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>
#include <time.h>

#include "min_heap.h"
#include "log.h"

extern struct timeval g_now; //保存当前时间戳
extern struct tm g_cur_tm; //保存当前tm结构
extern min_heap_t g_base_heap;

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

/* @brief 处理定时事件
 */
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
//				min_heap_pop(&g_base_heap);
//				free(item);
//				item = NULL;
				continue;
			} 
			break;
		}
	}
}


inline void timer_init()
{
	min_heap_ctor(&g_base_heap);
}

inline void timer_fini()
{
	min_heap_dtor(&g_base_heap);
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

#define ADD_TIMER_EVENT(timerid_, expire_, func_, owner_, data_) \
	if (add_timer_event(timerid_, expire_, func_, owner_, data_)) { \
		ERROR(0, "add timer event error [id=%u]", timerid_);\
		return -1;\
	}

#define MODIFY_TIMER_EVENT(item_, expire_) \
	item_->expire = expire_; \
	min_heap_shift_down_(&g_base_heap, item_->min_heap_idx, item_);

#define REMOVE_TIMER_EVENT(item_) \
	min_heap_pop(&g_base_heap); \
	free(item_);\
	item_ = NULL;


#endif
