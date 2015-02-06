#ifndef _POISX_LOCK_H
#define _POISX_LOCK_H

#include <semaphore.h> /* POISX  lock*/

#include "log.h"

/* @brief 打开一个sem供使用
 * @param name sem名称
 * @param init_val 初始化值，如果不是初始化值，则需要post
 */
inline sem_t* safe_semopen(const char* name, int init_val);

/* @brief 对sem执行P操作
 */
inline int safe_semwait(sem_t *sem);

/* @brief 对sem执行V操作
 */
inline int safe_sempost(sem_t *sem);

/* @brief 对sem执行关闭操作，并执行清除信号操作
 * @param name: sem name
 * @param sem sem info
 */
void safe_semclose(sem_t *sem, const char* name);

#endif
