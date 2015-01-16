/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  test 
 *
 *        Version:  1.0
 *        Created:  11/22/2014 08:26:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	xiaohou, houbin-12@163.com
 *   Organization:  XiaoHou, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int fd = open("test", O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd == -1) {
		fprintf(stderr, "open err");
		return 1;
	}

	return 0;
}
