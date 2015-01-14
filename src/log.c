/*
 * =====================================================================================
 *
 *       Filename:  log.c
 *
 *    Description:  log System 
 *    日志轮转，按级别统计日志，支持线程安全
 *
 *	  日志文件命名  X_LV_YYYYMMDD_XXXXXX(1_debug_20150110_00001)
 *        Version:  1.0
 *        Created:  2014年11月24日 21时43分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	xiaohou , houbin-12@163.com
 *   Organization:  XiaoHou, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#include "log.h"

#define FILENAM_LEN 128

extern char log_file[64];



static log_fd_t logfds[LOG_LV_MAX];
static log_conf_t logconf;
static const char *LOG_LV_NAME[LOG_LV_MAX] = {
	"crit", 
	"error", 
	"info", 
	"debug", 
	"trace", 
	"boot"
};

static int gen_log_seq(int lv) 
{
	char filename[FILENAME_LEN] = {0};
	DIR *dir = opendir(logconf.dirname);
	if (!dir) {
		fprintf(stderr, "open dir %s failed", logconf.dirname);
		return -1;
	}

	struct dirent *file;
	while ((file = readdir(dir))) { //找出文件相等比较大的序号
		if (strncmp(dir->d_name, log_fds[lv].
	}

	closedir(dir);
}

int log_init(const char *dirname, LOG_LV lv, uint32_t filesize, uint32_t maxfiles, const char* prename)
{
	int ret = -1;
	assert(lv >= LOG_LV_BOOT && lv < LOG_LV_MAX);
	assert(max_files >= 100 maxfiles <= 1000000);
	assert(filesize >= 10 * 1024 * 1024 && filesize <= 100 * 1024 * 1024); //10M - 100M

	logconf.max_files = maxfiles;
	logconf.pre_logsize = filesize;
	logconf.log_lv = lv;
	logconf.log_dest = LOG_DEST_FILE;

	//检测输入条件
	if (!dirname || strlen(dirname) == 0) {
		return ret;
	}
	
	if (access(dirname, W_OK)) { //test write
		fprintf(stderr, "access %s failed\n", dirname);
		return ret;
	}

	memset(logconf.dirname, 0, sizeof(logconf.dirname));
	strcpy(logconf.dirname, dirname);

	if (!log_pre) {
		memset(logconf.log_prename, 0, sizeof(logconf.log_prename));
		strcpy(logconf.log_prename, log_pre);
	}

	int i;
	for (i = LOG_LV_BOOT; i < LOG_LV_MAX; ++i) {
		sprintf(log_fds[i].filename, "%s_%s_", logconf.log_prename, LOG_LV_NAME[i]);
		log_fds[i].fd = -1;
		log_fds[i].seq = gen_log_seq(i);
	}

	ret = 0;

	return ret;
}

void slog(int llv, uint32_t key, const char* fmt, ...)
{
	time_t now = time(NULL);
	struct tm tm;
	localtime_r(&now, &tm);
	
	
	va_list ap;
//	strcat(logfile, LOG_LV_NAME[llv]);
	
	FILE *file = fopen(log_file, "a+");

	va_start(ap, fmt);
	fprintf(file, "[%02u:%02u:%02u] %u ", tm.tm_hour, tm.tm_min, tm.tm_sec, key);
	vfprintf(file, fmt, ap);
	fprintf(file, "\n");
	fflush(file);

	va_end(ap);
	fclose(file);
}
