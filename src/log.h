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
	LOG_DEST_STDOUT = 0, 
	LOG_DEST_FILE = 1, 
	LOG_DEST_FILE_AND_STDOUT = 2
};

/* @brief init log system
 */
int log_init(char *dirname, LOG_LV lv, uint32_t filesize, uint32_t maxfiles, const char* prename);


void do_log(int llv, uint32_t key, const char* fmt, ...);

#define BOOT(key, fmt, arg...) printf("%d "fmt, key, ##arg)
#define TRACE(key, fmt, arg...) slog(LOG_LV_TRACE, key, fmt, ##arg)
#define DEBUG(key, fmt, arg...) slog(LOG_LV_DEBUG, key, fmt, ##arg)
#define INFO(key, fmt, arg...) slog(LOG_LV_INFO, key, fmt, ##arg)
#define ERROR(key, fmt, arg...) slog(LOG_LV_ERROR, key, fmt, ##arg)
#define CRIT(key, fmt, arg...) slog(LOG_LV_CRIT, key, fmt, ##arg)

#endif
