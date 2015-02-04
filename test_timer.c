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
#include <libnanc/util.h>
#include <glib.h>
#include <unistd.h>
#include <stdlib.h>

GHashTable *sim_data;

int count = 1;

void print_count(void **owner, void** data)
{
	heap_timer_t *item = container_of(owner, heap_timer_t, owner);
	printf("id = %u, count= %u\n", item->timer_id, ++count);
	MODIFY_TIMER_EVENT(item, get_now_tv() + 1);
	//REMOVE_TIMER_EVENT(item);
}

int main(int argc, char* argv[])
{
	timer_init();
	int i = 0;
	for (i = 0; i < 10; ++i) {
		ADD_TIMER_EVENT(i, time(NULL) + i + 1, print_count, NULL, NULL);
	}

	while (1) {
		timer_handle();
		usleep(1000 * 100);
	}

	timer_fini();

	return 0;
}
