#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>
#include <time.h>

#include "min_heap.h"
#include "log.h"

extern struct timeval g_now; //保存当前时间戳
extern struct tm g_cur_tm; //保存当前tm结构
extern min_heap_t g_base_heap;

inline void refresh_time();

inline time_t get_now_tv();

inline struct tm* get_now_tm();

/* @brief 处理定时事件
 */
inline void timer_handle();

inline int add_timer_event(int timerid_, time_t expire_, timer_callback_t func_, void *owner_, void *data_);

/* @brief 增加定时器
*/
#define ADD_TIMER_EVENT(timerid_, expire_, func_, owner_, data_) \
	if (add_timer_event(timerid_, expire_, func_, owner_, data_)) { \
		ERROR(0, "add timer event error [id=%u]", timerid_);\
		return -1;\
	}

/* @brief 修改定时器
*/
#define MODIFY_TIMER_EVENT(item_, expire_) \
	item_->expire = expire_; \
min_heap_shift_down_(&g_base_heap, item_->min_heap_idx, item_);

/* @brief 移除定时器
*/
#define REMOVE_TIMER_EVENT(item_) \
	min_heap_pop(&g_base_heap); \
	free(item_);\
	item_ = NULL;

/* @brief 定时器初始化
 */
inline void timer_init();

/* @brief 定时器销毁
 */
inline void timer_fini();

#endif
