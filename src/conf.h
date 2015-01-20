#ifndef CONF_H_
#define CONf_H_

/* @brief 加载配置文件 可调用多次
 */
int load_conf(const char *name);

/* @brief 释放空间 只调用一次
 */
void free_conf();

/* @brief 获取字符串
 */
char* conf_get_str(const char *key);

/* @brief 获取字符串 默认值
 */
const char* conf_get_str_def(const char *key, const char *def);

/* @brief 获取整型
 */
int conf_get_int(const char *key);

/* @brief 获取整型 默认值
 */
int conf_get_int_def(const char *key, int def);

/* @brief 打印出所有变量，打印到标准输出上
 */
void print_simple_conf();

#endif
