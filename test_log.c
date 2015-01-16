/*
 * =====================================================================================
 *
 *       Filename:  test_log.c
 *
 *    Description:  测试新日志系统
 *
 *        Version:  1.0
 *        Created:  2015年01月16日 10时37分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>

#include "log.h"

int main(int argc, char* argv[])
{
	const char* buf = "hello,world";
	int i = 0;

	int ret = log_init("log", LOG_LV_TRACE, 100, 100, "master");
	if (ret == -1) {
		fprintf(stderr, "log init failed");
		return 0;
	}

	for (i = 0; i < 100000; ++i) {
		DEBUG(i, "%s", buf);
	}

	log_fini();

	return 0;
}
