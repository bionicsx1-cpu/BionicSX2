// Minimal libpng stub for iOS save state screenshot support
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <csetjmp>

typedef void* png_structp;
typedef void* png_infop;
typedef unsigned char png_byte;
typedef png_byte* png_bytep;
typedef png_byte** png_bytepp;
typedef size_t png_size_t;
typedef uint32_t png_uint_32;
typedef void (*png_error_ptr)(png_structp, const char*);
typedef void (*png_rw_ptr)(png_structp, png_bytep, png_size_t);
typedef void (*png_flush_ptr)(png_structp);

#define PNG_LIBPNG_VER_STRING "1.6.0"
#define PNG_COLOR_TYPE_RGBA 6
#define PNG_COLOR_TYPE_RGB 2
#define PNG_COLOR_TYPE_PALETTE 3
#define PNG_COLOR_TYPE_GRAY 0
#define PNG_COLOR_TYPE_GRAY_ALPHA 4
#define PNG_INTERLACE_NONE 0
#define PNG_COMPRESSION_TYPE_DEFAULT 0
#define PNG_FILTER_TYPE_DEFAULT 0
#define PNG_TRANSFORM_IDENTITY 0
#define PNG_FILLER_AFTER 1
#define PNG_INFO_tRNS 16

#define png_jmpbuf(p) ((jmp_buf*)p)

static inline png_structp png_create_write_struct(const char* v, void* e, png_error_ptr ef, png_error_ptr wf) { return (png_structp)1; }
static inline png_structp png_create_read_struct(const char* v, void* e, png_error_ptr ef, png_error_ptr wf) { return (png_structp)1; }
static inline png_infop png_create_info_struct(png_structp p) { return (png_infop)1; }
static inline void png_destroy_write_struct(png_structp* p, png_infop* i) {}
static inline void png_destroy_read_struct(png_structp* p, png_infop* i, png_infop* e) {}
static inline void png_set_write_fn(png_structp p, void* io, png_rw_ptr w, png_flush_ptr f) {}
static inline void png_set_read_fn(png_structp p, void* io, png_rw_ptr r) {}
static inline void png_set_compression_level(png_structp p, int l) {}
static inline void png_set_IHDR(png_structp p, png_infop i, png_uint_32 w, png_uint_32 h, int bd, int ct, int it, int cm, int ft) {}
static inline void png_write_info(png_structp p, png_infop i) {}
static inline void png_write_image(png_structp p, png_bytepp rows) {}
static inline void png_write_end(png_structp p, png_infop i) {}
static inline void png_read_info(png_structp p, png_infop i) {}
static inline void png_get_IHDR(png_structp p, png_infop i, png_uint_32* w, png_uint_32* h, int* bd, int* ct, int* it, int* cm, int* ft) { *w = 0; *h = 0; *bd = 8; *ct = 6; }
static inline png_uint_32 png_get_valid(png_structp p, png_infop i, png_uint_32 f) { return 0; }
static inline void png_set_strip_16(png_structp p) {}
static inline void png_set_palette_to_rgb(png_structp p) {}
static inline void png_set_expand_gray_1_2_4_to_8(png_structp p) {}
static inline void png_set_tRNS_to_alpha(png_structp p) {}
static inline void png_set_filler(png_structp p, png_uint_32 f, int flags) {}
static inline void png_set_gray_to_rgb(png_structp p) {}
static inline void png_read_update_info(png_structp p, png_infop i) {}
static inline void png_read_image(png_structp p, png_bytepp rows) {}
static inline void* png_get_io_ptr(png_structp p) { return nullptr; }
static inline png_uint_32 png_get_rowbytes(png_structp p, png_infop i) { return 0; }
static inline png_byte png_get_bit_depth(png_structp p, png_infop i) { return 8; }
static inline png_byte png_get_color_type(png_structp p, png_infop i) { return 6; }
