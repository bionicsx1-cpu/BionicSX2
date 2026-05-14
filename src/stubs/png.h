#pragma once
// Full libpng stub for iOS ARM64 build
#include <stdint.h>
#include <stddef.h>

typedef unsigned char  png_byte;
typedef unsigned short png_uint_16;
typedef unsigned int   png_uint_32;
typedef int            png_int_32;
typedef size_t         png_size_t;
typedef png_byte*      png_bytep;
typedef png_bytep*     png_bytepp;
typedef const png_byte* png_const_bytep;
typedef void*          png_voidp;
typedef char*          png_charp;

typedef struct png_struct_def png_struct;
typedef png_struct*  png_structp;
typedef png_struct** png_structpp;
typedef const png_struct* png_const_structp;

typedef struct png_info_def png_info;
typedef png_info*  png_infop;
typedef png_info** png_infopp;

typedef void (*png_error_ptr)(png_structp, const char*);
typedef void (*png_rw_ptr)(png_structp, png_bytep, size_t);
typedef void (*png_flush_ptr)(png_structp);

#define PNG_COLOR_TYPE_GRAY        0
#define PNG_COLOR_TYPE_PALETTE     3
#define PNG_COLOR_TYPE_RGB         2
#define PNG_COLOR_TYPE_RGB_ALPHA   6
#define PNG_COLOR_TYPE_RGBA        6
#define PNG_COLOR_TYPE_GRAY_ALPHA  4
#define PNG_INTERLACE_NONE         0
#define PNG_COMPRESSION_TYPE_BASE  0
#define PNG_FILTER_TYPE_BASE       0
#define PNG_LIBPNG_VER_STRING      "1.6.0"
#define PNG_HEADER_VERSION_STRING  "libpng stub"

struct png_struct_def  { int unused; };
struct png_info_def    { int unused; };

static inline png_structp png_create_read_struct(
    const char* v, png_voidp e, png_error_ptr ef, png_error_ptr wf)
{ return nullptr; }

static inline png_structp png_create_write_struct(
    const char* v, png_voidp e, png_error_ptr ef, png_error_ptr wf)
{ return nullptr; }

static inline png_infop  png_create_info_struct(png_structp p)
{ return nullptr; }

static inline void png_destroy_read_struct(
    png_structpp p, png_infopp i, png_infopp e) {}
static inline void png_destroy_write_struct(
    png_structpp p, png_infopp i) {}

static inline void png_set_read_fn(
    png_structp p, png_voidp io, png_rw_ptr fn) {}
static inline void png_set_write_fn(
    png_structp p, png_voidp io, png_rw_ptr wfn, png_flush_ptr ffn) {}

static inline void png_read_info(png_structp p, png_infop i) {}
static inline void png_write_info(png_structp p, png_infop i) {}
static inline void png_read_row(
    png_structp p, png_bytep row, png_bytep disp) {}
static inline void png_write_row(png_structp p, png_const_bytep row) {}
static inline void png_read_end(png_structp p, png_infop i) {}
static inline void png_write_end(png_structp p, png_infop i) {}

static inline png_uint_32 png_get_image_width(
    png_const_structp p, const png_info* i) { return 0; }
static inline png_uint_32 png_get_image_height(
    png_const_structp p, const png_info* i) { return 0; }
static inline png_uint_32 png_get_rowbytes(
    png_const_structp p, const png_info* i) { return 0; }
static inline png_byte    png_get_bit_depth(
    png_const_structp p, const png_info* i) { return 0; }
static inline png_byte    png_get_color_type(
    png_const_structp p, const png_info* i) { return 0; }
static inline png_voidp   png_get_io_ptr(png_const_structp p)
{ return nullptr; }
static inline png_bytepp  png_get_rows(
    png_const_structp p, const png_info* i) { return nullptr; }

static inline void png_set_IHDR(png_structp p, png_infop i,
    png_uint_32 w, png_uint_32 h, int bd, int ct, int it,
    int comp, int ft) {}
static inline void png_set_rows(
    png_structp p, png_infop i, png_bytepp rows) {}
static inline void png_set_swap(png_structp p) {}
static inline void png_set_expand(png_structp p) {}
static inline void png_set_gray_to_rgb(png_structp p) {}
static inline void png_set_filler(
    png_structp p, png_uint_32 f, int flags) {}
static inline void png_set_bgr(png_structp p) {}
static inline void png_set_interlace_handling(png_structp p) {}
static inline void png_set_compression_level(png_structp p, int l) {}

static inline int png_sig_cmp(
    png_const_bytep s, size_t start, size_t num) { return 1; }

// Remove conflicting setjmp macro if already defined
#ifdef setjmp
#undef setjmp
#endif
static inline int png_setjmp_stub() { return 0; }
#define png_jmpbuf(p) (*((int*)nullptr))
