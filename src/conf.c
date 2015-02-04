/*
 * =====================================================================================
 *
 *       Filename:  conf.c
 *
 *    Description:  配置文件读取 参考openssl
 *
 *        Version:  1.0
 *        Created:  12/10/2014 04:15:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>

#include "conf.h"

//主框架定义,或者自己定义
GHashTable *sim_data;

static void do_free_item(void* item)
{
	g_free(item);
	item = NULL;
}


static int load_simple_data(const char *name)
{
	sim_data = g_hash_table_new_full(g_str_hash, g_str_equal, do_free_item, do_free_item);
	int fd = open(name, O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "simple.conf not existed : %s", strerror(errno));
		return -1;
	}

	char line[1024];
	char key[64];
	char value[128];
	char *ptr = (char *)mmap((void *)-1, 1024 * 10, PROT_READ, MAP_SHARED, fd, 0);
	if (ptr == NULL) {
		fprintf(stderr, "error mmap");
		return -1;
	}

	int start = 0;
	int end = 0;
	int i = 0;
	int is_note = 0;
	for (; ptr[i] != '\0'; i++) {
		if (ptr[i] == '#') {
			is_note = 1;
		} else if (ptr[i] == '\n') {
			end = i - 1;
			if (is_note) {
				start = i + 1;
				i = start - 1;
				is_note = 0;
				continue;
			} else {
				int len = end - start + 1;
				memcpy(line, ptr + start, len);
				if (len == 0) {
					start = i + 1;
					is_note = 0;
					continue;
				}
				line[len] = '\0';
				sscanf(line, "%s %s\n", key, value);
				g_hash_table_insert(sim_data, strdup(key), strdup(value));
				//清下个状态
				memset(key, 0, 64);
				memset(value, 0, 128);
				start = i + 1;
				is_note = 0;
			}
		}
	}

	munmap(ptr, 1024 * 10);
	close(fd);

	return 0;
}

void free_sim_data()
{
	g_hash_table_destroy(sim_data);
}


static void print(void *key, void *value, void *userdata)
{
	printf("%s-%s\n", (char *)key, (char *)value);
}

void print_simple_conf()
{
	g_hash_table_foreach(sim_data, print, NULL);	
}

char* conf_get_str(const char *key)
{
	char *value = g_hash_table_lookup(sim_data, key);
	if (value == NULL) {
		return "";
	}

	return value;
}

const char* conf_get_str_def(const char *key, const char *def)
{
	char *value = g_hash_table_lookup(sim_data, key);
	if (value == NULL) {
		return def;
	}

	return value;
}

int conf_get_int(const char *key)
{
	char *value = g_hash_table_lookup(sim_data, key);
	if (value == NULL) {
		return 0;
	}

	return atoi(value);
}

int conf_get_int_def(const char *key, int def)
{
	char *value = g_hash_table_lookup(sim_data, key);
	if (value == NULL) {
		return def;
	}

	return atoi(value);
}


int load_conf(const char *name)
{
	if (load_simple_data(name)) {
		return -1;
	}

	return 0;
}

void free_conf()
{
	free_sim_data();
}

