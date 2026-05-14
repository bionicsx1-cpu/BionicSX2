#pragma once
// iOS build stub — JPEG handled via ImageIO.framework
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned char  JSAMPLE;
typedef JSAMPLE       *JSAMPROW;
typedef JSAMPROW      *JSAMPARRAY;
typedef unsigned int   JDIMENSION;
typedef int            boolean;
typedef enum { JCS_UNKNOWN,JCS_GRAYSCALE,JCS_RGB,JCS_YCbCr,JCS_CMYK,JCS_YCCK,JCS_EXT_RGB } J_COLOR_SPACE;

#define JPEG_LIB_VERSION  90
#define TRUE  1
#define FALSE 0

struct jpeg_error_mgr { void(*error_exit)(struct jpeg_common_struct*); char jpeg_message_table[1][1]; int msg_code; int last_jpeg_message; int trace_level; void(*output_message)(struct jpeg_common_struct*); };
struct jpeg_common_struct { struct jpeg_error_mgr *err; };
struct jpeg_compress_struct   { struct jpeg_error_mgr *err; JDIMENSION image_width,image_height,input_scanline; int input_components; J_COLOR_SPACE in_color_space; double X_density,Y_density; int density_unit; int quality; };
struct jpeg_decompress_struct { struct jpeg_error_mgr *err; JDIMENSION image_width,image_height,output_scanline; int num_components,output_components; J_COLOR_SPACE jpeg_color_space,out_color_space; JDIMENSION output_width,output_height; };

static inline struct jpeg_error_mgr* jpeg_std_error(struct jpeg_error_mgr*e){return e;}
static inline void jpeg_create_compress(struct jpeg_compress_struct*c){}
static inline void jpeg_create_decompress(struct jpeg_decompress_struct*d){}
static inline void jpeg_destroy_compress(struct jpeg_compress_struct*c){}
static inline void jpeg_destroy_decompress(struct jpeg_decompress_struct*d){}
static inline void jpeg_stdio_dest(struct jpeg_compress_struct*c,void*f){}
static inline void jpeg_stdio_src(struct jpeg_decompress_struct*d,void*f){}
static inline void jpeg_set_defaults(struct jpeg_compress_struct*c){}
static inline void jpeg_set_quality(struct jpeg_compress_struct*c,int q,boolean f){}
static inline void jpeg_start_compress(struct jpeg_compress_struct*c,boolean f){}
static inline void jpeg_finish_compress(struct jpeg_compress_struct*c){}
static inline int  jpeg_read_header(struct jpeg_decompress_struct*d,boolean r){return 0;}
static inline int  jpeg_start_decompress(struct jpeg_decompress_struct*d){return 0;}
static inline int  jpeg_finish_decompress(struct jpeg_decompress_struct*d){return 0;}
static inline JDIMENSION jpeg_write_scanlines(struct jpeg_compress_struct*c,JSAMPARRAY s,JDIMENSION n){return 0;}
static inline JDIMENSION jpeg_read_scanlines(struct jpeg_decompress_struct*d,JSAMPARRAY s,JDIMENSION n){return 0;}
#ifdef __cplusplus
}
#endif
