#pragma once
// iOS build stub — PNG handled via ImageIO.framework
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct png_struct_s *png_structp;
typedef struct png_info_s  *png_infop;
typedef unsigned char       png_byte;
typedef png_byte           *png_bytep;
typedef png_bytep          *png_bytepp;
typedef uint32_t            png_uint_32;
typedef void (*png_error_ptr)(png_structp, const char*);
typedef void (*png_rw_ptr)(png_structp, png_bytep, size_t);

#define PNG_LIBPNG_VER_STRING        "1.6.0-ios-stub"
#define PNG_COLOR_TYPE_RGB           2
#define PNG_COLOR_TYPE_RGB_ALPHA     6
#define PNG_COLOR_TYPE_GRAY          0
#define PNG_INTERLACE_NONE           0
#define PNG_FILTER_TYPE_DEFAULT      0
#define PNG_COMPRESSION_TYPE_DEFAULT 0
#define PNG_TRANSFORM_IDENTITY       0
#define PNG_INFO_IDAT                0x0008
#define PNG_IMAGE_VERSION            1
#define setjmp(x)                    0

static inline png_structp png_create_read_struct(const char*v,void*e,png_error_ptr f,png_error_ptr w){return (png_structp)0;}
static inline png_structp png_create_write_struct(const char*v,void*e,png_error_ptr f,png_error_ptr w){return (png_structp)0;}
static inline png_infop   png_create_info_struct(png_structp s){return (png_infop)0;}
static inline void png_destroy_read_struct(png_structp*s,png_infop*i,png_infop*e){}
static inline void png_destroy_write_struct(png_structp*s,png_infop*i){}
static inline void png_set_error_fn(png_structp s,void*p,png_error_ptr e,png_error_ptr w){}
static inline void png_set_read_fn(png_structp s,void*p,png_rw_ptr r){}
static inline void png_set_write_fn(png_structp s,void*p,png_rw_ptr w,png_rw_ptr f){}
static inline void png_read_png(png_structp s,png_infop i,int t,void*p){}
static inline void png_write_png(png_structp s,png_infop i,int t,void*p){}
static inline void png_set_IHDR(png_structp s,png_infop i,png_uint_32 w,png_uint_32 h,int bd,int ct,int it,int cmt,int fm){}
static inline png_uint_32 png_get_IHDR(png_structp s,png_infop i,png_uint_32*w,png_uint_32*h,int*bd,int*ct,int*it,int*cmt,int*fm){return 0;}
static inline png_bytepp  png_get_rows(png_structp s,png_infop i){return (png_bytepp)0;}
static inline void        png_set_rows(png_structp s,png_infop i,png_bytepp r){}
static inline png_uint_32 png_get_valid(png_structp s,png_infop i,png_uint_32 f){return 0;}
static inline void        png_set_expand(png_structp s){}
static inline void        png_set_strip_16(png_structp s){}
static inline void        png_set_gray_to_rgb(png_structp s){}
static inline void        png_set_filler(png_structp s,png_uint_32 f,int fl){}
static inline void        png_read_update_info(png_structp s,png_infop i){}
static inline void*       png_get_error_ptr(png_structp s){return (void*)0;}
static inline void        png_error(png_structp s,const char*m){}
static inline void        png_set_compression_level(png_structp s,int l){}
static inline void        png_init_io(png_structp s,void*f){}
static inline void        png_write_info(png_structp s,png_infop i){}
static inline void        png_write_row(png_structp s,png_bytep r){}
static inline void        png_write_end(png_structp s,png_infop i){}
static inline void        png_read_info(png_structp s,png_infop i){}
#ifdef __cplusplus
}
#endif
