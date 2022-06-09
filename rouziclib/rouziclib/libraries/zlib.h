#ifdef RL_ZLIB

#pragma comment(lib,"zlib.lib")
#include <zlib.h>

#else

#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#ifndef RL_DONT_ASSUME_LITTLE_ENDIAN
#define MINIZ_LITTLE_ENDIAN 1
#endif
#define MINIZ_UNALIGNED_USE_MEMCPY
#include "orig/miniz.h"

#endif

extern int gz_decompress(const uint8_t *src, const size_t src_len, uint8_t **dst, size_t *dst_alloc);
extern buffer_t gz_decompress_to_buffer(const uint8_t *src, const size_t src_len);
extern buffer_t gz_compress_to_buffer(const uint8_t *data, const size_t data_size, const int comp_level);
extern uint8_t *gz_decompress_file(const char *path, size_t *data_size);
