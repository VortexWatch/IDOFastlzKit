//
// Created by VortexWatch on 2026/7/22.
//

#ifndef IDO_FASTLZ_KIT_H
#define IDO_FASTLZ_KIT_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================= */
/*                          FASTLZ 宏定义与版本信息                          */
/* ========================================================================= */

#define FASTLZ_VERSION                 0x000100
#define FASTLZ_VERSION_MAJOR           0
#define FASTLZ_VERSION_MINOR           0
#define FASTLZ_VERSION_REVISION        0
#define FASTLZ_VERSION_STRING          "0.1.0"

/**
 * 输出缓冲区至少要比输入缓冲区大 5%
 * 且不能小于 66 字节。
 */
#define FASTLZ_BUFFER_PADDING(x)       (66 + (x) * 5 / 100)

/* ========================================================================= */
/*                           错误码定义                                      */
/* ========================================================================= */

#define SUCCESS                        0
#define ERROR_NO_MEM                   4
#define ERROR_NOT_FIND                 5
#define ERROR_NOT_SUPPORTED            6
#define ERROR_INVALID_PARAM            7
#define ERROR_INVALID_STATE            8
#define ERROR_INVALID_LENGTH           9
#define ERROR_INVALID_FLAGS            10
#define ERROR_INVALID_DATA             11
#define ERROR_DATA_SIZE                12
#define ERROR_TIMEOUT                  13
#define ERROR_NULL                     14
#define ERROR_FORBIDDEN                15
#define ERROR_BUSY                     17
#define ERROR_LOW_BATT                 18
#define ERROR_SERIAL                   19
#define ERROR_TIME_OUT_RECONNECT       20
#define ERROR_APP_TEST                 21
#define ERROR_MAX_TIME                 22
#define ERROR_SPACE_ORGANIZATION       24
#define ERROR_SPACE_ORGANIZATION_ING   25
#define TASK_TERMINATION               26
#define ERROR_INVAILD_FILE             27
#define ERROR_CODE_REPEAT_REQUEST      31

/* ========================================================================= */
/*                           调试与日志类型                                  */
/* ========================================================================= */

typedef enum {
    DEBUG_LEVEL_ERROR,
    DEBUG_LEVEL_WARN,
    DEBUG_LEVEL_INFO
} DEBUG_LEVEL;

extern int cur_debug_level;

void debug_log_init(bool is_print_console, bool is_write_file, const char *file_path);
void debug_log(DEBUG_LEVEL level, const char *tag, const char *func_name, int line, const char *fmt, ...);
void set_log_save_day(int save_day);

/* ========================================================================= */
/*                         FASTLZ 核心 C 接口                               */
/* ========================================================================= */

/**
 * 压缩输入缓冲区中的数据块。
 */
int fastlz_compress(const void* input, int length, void* output);

/**
 * 解压压缩后的数据块。
 */
int fastlz_decompress(const void* input, int length, void* output, int maxout);

/**
 * 使用指定的压缩级别（1 或 2）压缩数据块。
 */
int fastlz_compress_level(int level, const void* input, int length, void* output);

/* ========================================================================= */
/*                        FASTLZ 工具函数                                    */
/* ========================================================================= */

/**
 * 按块压缩文件句柄输入到文件句柄输出。
 */
int fastlz_util_compress_file(FILE* fd_in, FILE* fd_out, uint32_t compress_block_size);

/**
 * 将源内存缓冲区中的数据压缩到目标内存缓冲区。
 */
int fastlz_util_compress_buff(const void* src_buff, void* dst_buff, int src_buff_len, uint32_t compress_block_size);

/**
 * 按块解压文件句柄输入到文件句柄输出。
 */
int fastlz_util_decompress_file(FILE* fd_in, FILE* fd_out, uint32_t compress_block_size);

/**
 * 命令行工具入口函数。
 */
int fastlz_util_main(int argc, char** argv);

#ifdef __cplusplus
}
#endif

#endif /* IDO_FASTLZ_KIT_H */