#ifndef _PROTO_HEADER_H
#define _PROTO_HEADER_H

#include <stdint.h>

/* @brief 包头类型
 */
enum PROTO_HEAD_TYPE {
	PROTO_ONE_SERV = 0,   //单服
	PROTO_MULTI_SERV = 1, //多服
};

/* @brief 协议头
 */
typedef struct proto_head {
	int len; 		//包长度
	uint16_t cmd;	//命令
	uint32_t id;	//包id
#ifdef SERV_MULTI
	uint16_t svr_id; //服id
#endif
	int seq;		//包序列号
	int ret;		//返回
} __attribute__((packed)) proto_head_t;

#endif
