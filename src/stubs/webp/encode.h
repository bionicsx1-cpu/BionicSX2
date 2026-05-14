#pragma once
// iOS build stub — WebP encode not needed on iOS
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
static inline size_t WebPEncodeRGBA(const uint8_t*r,int w,int h,int s,float q,uint8_t**out){(void)r;(void)w;(void)h;(void)s;(void)q;if(out)*out=(uint8_t*)0;return 0;}
static inline size_t WebPEncodeRGB(const uint8_t*r,int w,int h,int s,float q,uint8_t**out){(void)r;(void)w;(void)h;(void)s;(void)q;if(out)*out=(uint8_t*)0;return 0;}
static inline void   WebPFree(void*p){}
#ifdef __cplusplus
}
#endif
