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

static int gen_log_seq(int llv, struct tm *tm) 
{
char filename[FILENAME_LEN] = {0};
DIR *dir = opendir(logconf.dirname);
if (!dir) {
	fprintf(stderr, "open dir %s failed", logconf.dirname);
	return -1;
}

struct dirent *file;
int init_seq = logfds[llv].seq;
int tmp_seq = 0;
char seq_str[10] = {'\0'};
while ((file = readdir(dir))) { //找出文件相等比较大的序号
	if (strcmp(dir->d_name, log_fds[llv].basename, logfds[llv].baselen) == 0) {
		sprintf(seq_str, "%s", dir->d_name + logfds[llv].baselen);
		tmp_seq = atoi(seq_str);
		if (init_seq < tmp_seq) {
			init_seq = tmp_seq;
		}
	}
}

if (init_seq >= logconf.maxfiles) { //大于最大文件 不写了
	logfds[llv].seq = -1;
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

time_t cur = time(0);
struct tm tm;
localtime_r(&cur, &tm);
int i;
char day_str[16] = {'\0'};
sprintf(day_str, "%04d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
for (i = LOG_LV_BOOT; i < LOG_LV_MAX; ++i) {
	log_fds[i].baselen = snprintf(log_fds[i].basename, 64, "%s_%s_%s", logconf.log_prename, LOG_LV_NAME[i], day_str);
	log_fds[i].fd = -1;
	log_fds[i].seq = 1;
	log_fds[i].seq = gen_log_seq(i, &tm);
	log_fds[i].day = atoi(day_str);
}

ret = 0;

return ret;
}


void log_fini()
{

}

/* @brief 打开当前级别的日志文件
 */
static open_file(int llv, struct tm *tm) 
{
	static char filename[256] = {'\0'};
	if (unlikely(logfds[llv].fd == -1)) { //打开文件
		if (gen_log_seq(llv, tm) == -1) {
			return -1;
		}
		sprintf(filename, "%s/%s%06d", logconf.prename, logfds[llv].basename, logfds[llv].seq);
	} else { //判断当前文件是否合法

	}

	logfds[llv].fd = open(filename, O_APPEND | O_CREAT | O_CLOEXEC);
	if (logfds[llv].fd == -1) {
		fprintf(stderr, "open %s failed [%s]", filename, strerror(errno));
		return -1;
	}
}

void do_log(int llv, uint32_t key, const char* fmt, ...)
{
	time_t now = time(NULL);	
	struct tm tm;
	localtime_r(&now, &tm);

	if (open_file(llv, tm) == -1) {
		return ;
	}
	
	va_list ap;
	va_start(ap, fmt);
	fprintf(logfds[llv].fd, "%02u:%02u%02u %u ", tm->tm_hour, tm->tm_min, tm->tm_sec, key);
	vfprintf(logfds[llv].fd, fmt, ap);
	fprintf(logfds[llv].fd, "\n");
	fflush(logfds[llv].fd);
	va_end(ap);
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
