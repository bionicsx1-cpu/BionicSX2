#ifndef _HAD_ZIPCONF_H
#define _HAD_ZIPCONF_H
#define LIBZIP_VERSION "1.10.1"
#define LIBZIP_VERSION_MAJOR 1
#define LIBZIP_VERSION_MINOR 10
#define LIBZIP_VERSION_MICRO 1
#define ZIP_STATIC
typedef long long zip_int64_t;
typedef unsigned long long zip_uint64_t;
typedef int zip_int32_t;
typedef unsigned int zip_uint32_t;
typedef unsigned short zip_uint16_t;
typedef short zip_int16_t;
typedef unsigned char zip_uint8_t;
typedef signed char zip_int8_t;
#define ZIP_INT64_MIN (-9223372036854775807LL - 1)
#define ZIP_INT64_MAX 9223372036854775807LL
#define ZIP_UINT64_MAX 18446744073709551615ULL
#define ZIP_INT32_MIN (-2147483647 - 1)
#define ZIP_INT32_MAX 2147483647
#define ZIP_UINT32_MAX 4294967295U
#endif
