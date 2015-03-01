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
#include <stdlib.h>
#include <string.h>

#include <libnanc/log.h>

void gen_str(char buf[], int n)
{
	int i;
	for (i = 0; i < n; i++) {
		buf[i] = (char)('a' + rand() % 26);
	}
}

int main(int argc, char* argv[])
{

	char buf[2048] = {'\0'};
	int i = 0;

	int ret = log_init("log", LOG_LV_TRACE, 10240000, 100, "master");
	if (ret == -1) {
		fprintf(stderr, "log init failed");
		return 0;
	}

	for (i = 0; i < 10000000; ++i) {
		memset(buf, 0, sizeof(buf));
		gen_str(buf, rand() % 100 + 1);
		DEBUG(i, "debug %s", buf);
		TRACE(i, "trace %s", buf);
		INFO(i, "info %s", buf);
		CRIT(i, "crit %s", buf);
		BOOT(i, "boot %s", buf);
	}

	log_fini();

	return 0;
}
