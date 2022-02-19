#ifndef TEST_H
#define TEST_H
#include "stddef.h"
#include "stdint.h"
/**
 * @brief 分配一块内存空间
 * 
 * @param sz 所分配的内存空间大小不可小于sz
 * @return void* 分配的空间的首地址
 */
void* my_malloc(size_t sz);
/**
 * @brief 回收一块内存空间
 * 
 * @param ptr 回收的内存空间的首地址，保证为my_malloc的返回值，你需要自行确定该内存块的大小
 */
void my_free(void*ptr);
/**
 * @brief 将一个字符串传输到上位机
 * 
 * @param str 需要传输的字符串
 * @param sz 字符串长度
 */
void my_transmit(const char *str,size_t sz);
/**
 * @brief 延时函数
 * 
 * @param delay 单位：毫秒
 */
void my_delay(uint32_t delay);
/**
 * @brief 开始测试分配算法，用于面试时展示成果，实现在start_test.c中，不需要自行编写
 * 
 * @param ptr 你所管理的内存空间的首地址
 * @param sz 你所管理的内存空间的大小
 */
void start_test(void *ptr,size_t sz);
#endif
