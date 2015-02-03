#ifndef _UTIL_H
#define _UTIL_H

/* @brief 获得cpu个数
 */
inline int get_cpu_num();

#define offsetof(type, member) ((size_t) &((type *)0)->member)

#define container_of(ptr, type, member) ({ \
		const typeof( ((type *)0)->member ) *__mptr = (ptr);\
		(type *)( (char *)__mptr - offsetof(type,member) );})

#endif
