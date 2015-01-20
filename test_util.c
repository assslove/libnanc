/*
 * =====================================================================================
 *
 *       Filename:  test_util.c
 *
 *    Description:  测试常用函数
 *
 *        Version:  1.0
 *        Created:  2015年01月20日 09时56分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	houbin , houbin-12@163.com
 *   Organization:  Houbin, Inc. ShangHai CN. All rights reserved.
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <util.h>

int main(int argc, char* argv[])
{
	printf("%d", get_cpu_num());
	return 0;
}
