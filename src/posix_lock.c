/*
 * =====================================================================================
 *
 *       Filename:  poisx_lock.c
 *
 *    Description:  posix 信号量 封装
 *
 *        Version:  1.0
 *        Created:  2015年02月06日 17时12分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>           /*  For O_* constants */ 

#include "posix_lock.h"

sem_t* safe_semopen(const char* name, int init_val)
{
	sem_t *sem = sem_open(name, O_CREAT, 0666, init_val);
	if (sem == SEM_FAILED) {
		ERROR(0, "sem open failed [%s:%s]", name, strerror(errno));
		return sem;
	}

	int val;
	if (sem_getvalue(sem, &val) == 0) { //获取信号量
		int i;
		for (i = val; i < init_val; ++i) {
			sem_post(sem);
		}
	}

	return sem;
}

void safe_semclose(sem_t *sem, const char* name)
{
	sem_close(sem);	
	sem_unlink(name);
}

int safe_sempost(sem_t *sem)
{
sem_post_again:
	if (sem_post(sem) == -1) {
		if (errno == EINTR) {
			goto sem_post_again;	
		}
		ERROR(0, "sem_wait failed [%s]", strerror(errno));
		return -1;
	}

	return 0;
}

inline int safe_semwait(sem_t *sem)
{
sem_wait_again:
	if (sem_wait(sem) == -1) {
		if (errno == EINTR) {
			goto sem_wait_again;	
		}
		ERROR(0, "sem_wait failed [%s]", strerror(errno));
		return -1;
	}

	return 0;
}
