#pragma once
// iOS build stub — WebP handled via ImageIO.framework (iOS 14+)
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct { int width,height; } WebPBitstreamFeatures;
typedef enum { VP8_STATUS_OK=0, VP8_STATUS_BITSTREAM_ERROR=2 } VP8StatusCode;

static inline uint8_t* WebPDecodeRGBA(const uint8_t*d,size_t s,int*w,int*h){(void)d;(void)s;if(w)*w=0;if(h)*h=0;return (uint8_t*)0;}
static inline uint8_t* WebPDecodeRGB(const uint8_t*d,size_t s,int*w,int*h){(void)d;(void)s;if(w)*w=0;if(h)*h=0;return (uint8_t*)0;}
static inline void     WebPFree(void*p){}
static inline VP8StatusCode WebPGetFeatures(const uint8_t*d,size_t s,WebPBitstreamFeatures*f){return VP8_STATUS_BITSTREAM_ERROR;}
#ifdef __cplusplus
}
#endif
