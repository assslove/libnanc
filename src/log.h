#ifndef _LOG_H_
#define _LOG_H_

#include <stdint.h>
#include <stdio.h>


/* @brief log lv
*/
enum LOG_LV {
	LOG_LV_CRIT = 0,
	LOG_LV_ERROR = 1, 
	LOG_LV_INFO = 2, 
	LOG_LV_DEBUG = 3, 
	LOG_LV_TRACE = 4,
	LOG_LV_BOOT = 5,
	LOG_LV_MAX
};

/* @brief log dest
*/
enum LOG_DEST {
	LOG_DEST_STDOUT = 1, 
	LOG_DEST_FILE = 2, 
	LOG_DEST_FILE_AND_STDOUT = 3
};

/* @brief 日志配置定义
*/
struct struct log_conf {
	uint32_t max_files;		//最大文件个数
	uint32_t per_logsize;	//每个文件大小
	char dirname[128];		//目录名字
	char prename[16];	//日志前缀
	LOG_LV log_lv;		//日志级别
	LOG_DEST log_dest;		//日志输出
} __attribute__((packed)) log_conf_t;

/* @brief 不同级别的日志fd定义
*/
typedef struct log_fd {
	int fd;
	int day;
	int seq;
	int basename[64];
	int baselen;
} __attribute__((packed)) log_fd_t;

/* @brief init log system
 *
 * @param dirname 目录名字
 * @param lv 日志级别
 * @param filesize 文件最大大小
 * @param maxfiles 最大文件个数
 * @prename 文件名前缀
 */
int log_init(char *dirname, LOG_LV lv, uint32_t filesize, uint32_t maxfiles, const char* prename);

/* @brief 日志执行文件
 *
 * @param llv 日志级别
 * @param key 日志主键 一般为用户编号
 */
void do_log(int llv, uint32_t key, const char* fmt, ...);


/* @brief 输出到stdout
 */
void do_std_log(int llv, uint32_t key, const char* fmt, ...);

#define BOOT(key, fmt, arg...)  sprintf(stdout, "%d "fmt, key, ##arg)
#define TRACE(key, fmt, arg...) do_log(LOG_LV_TRACE, key, fmt, ##arg)
#define DEBUG(key, fmt, arg...) do_log(LOG_LV_DEBUG, key, fmt, ##arg)
#define INFO(key, fmt, arg...) do_log(LOG_LV_INFO, key, fmt, ##arg)
#define ERROR(key, fmt, arg...) do_log(LOG_LV_ERROR, key, fmt, ##arg)
#define CRIT(key, fmt, arg...) do_log(LOG_LV_CRIT, key, fmt, ##arg)

#endif
