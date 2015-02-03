/*
 * =====================================================================================
 *
 *       Filename:  test_timer.c
 *
 *    Description:  测试定时器
 *
 *        Version:  1.0
 *        Created:  2015年02月03日 17时54分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <libnanc/timer.h>
#include <libnanc/log.h>
#include <glib.h>
#include <unistd.h>

GHashTable *sim_data;

int count = 1;

void print_count(void *owner, void* data)
{
	printf("%u\n", ++count);
	ADD_TIMER_EVENT(1, get_now_tv() + 1, print_count, NULL, NULL);
}

int main(int argc, char* argv[])
{
	timer_init();
	ADD_TIMER_EVENT(1, time(NULL) + 1, print_count, NULL, NULL);
	while (1) {
		timer_handle();
		mssleep(10);
	}

	timer_fini();

	return 0;
}
