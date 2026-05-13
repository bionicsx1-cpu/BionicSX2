// PORTED FROM: pcsx2/GS/Renderers/Metal/GSMTLSharedHeader.h — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 3.2, 4.2
// STATUS: GREEN — pure C types, no platform dependency

#pragma once
#include <simd/simd.h>
#include <cstdint>

// AUDIT REFERENCE: Section 3.2 — Buffer indices for vertex/uniform binding
// These are shared between C++ and .metal shader code — identical on iOS

enum GSMTLBufferIndices {
    GSMTLBufferIndexVertices,
    GSMTLBufferIndexUniforms,
    GSMTLBufferIndexHWVertices,
    GSMTLBufferIndexHWUniforms,
    GSMTLBufferIndexHWIndices,
};

enum GSMTLTextureIndex {
    GSMTLTextureIndexNonHW,
    GSMTLTextureIndexTex,
    GSMTLTextureIndexPalette,
    GSMTLTextureIndexRenderTarget,
    GSMTLTextureIndexPrimIDs,
    GSMTLTextureIndexDepthTarget,
    GSMTLTextureIndexCount,
};

// AUDIT REFERENCE: Section 3.2 — Shader uniform structs
// These are shared between C++ and .metal shader files — no platform dependency

struct GSMTLConvertPSUniform {
    int emoda;
    int emodc;
};

struct GSMTLPresentPSUniform {
    vector_float4 source_rect;
    vector_float4 target_rect;
    vector_float2 source_size;
    vector_float2 target_size;
    vector_float2 target_resolution;
    vector_float2 rcp_target_resolution;
    vector_float2 source_resolution;
    vector_float2 rcp_source_resolution;
    float time;
};

struct GSMTLInterlacePSUniform {
    vector_float4 ZrH;
};

struct GSMTLCASPSUniform {
    vector_uint4 const0;
    vector_uint4 const1;
    vector_int2 srcOffset;
};

struct GSMTLCLUTConvertPSUniform {
    float scale;
    vector_uint2 offset;
    uint doffset;
};

struct GSMTLIndexedConvertPSUniform {
    float scale;
    uint sbw;
    uint dbw;
    uint psm;
};

struct GSMTLDownsamplePSUniform {
    vector_uint2 clamp_min;
    uint downsample_factor;
    float weight;
    float step_multiplier;
};

// AUDIT REFERENCE: Section 3.2 — Main vertex format shared with shaders

struct GSMTLMainVertex {
    vector_float2 st;
    vector_uchar4 rgba;
    float q;
    vector_ushort2 xy;
    uint z;
    vector_ushort2 uv;
    unsigned char fog;
};

struct GSMTLMainVSUniform {
    vector_float2 vertex_scale;
    vector_float2 vertex_offset;
    vector_float2 texture_scale;
    vector_float2 texture_offset;
    vector_float2 point_size;
    uint max_depth;
    uint _pad0;
};

struct GSMTLMainPSUniform {
    union {
        vector_float4 fog_color_aref;
        vector_float3 fog_color;
        struct { float pad0[3]; float aref; };
    };
    vector_float4 wh;
    vector_float2 ta;
    float max_depth;
    float alpha_fix;
    vector_uint4 fbmask;
    vector_float4 half_texel;
    union {
        vector_float4 uv_min_max;
        vector_uint4 uv_msk_fix;
    };
    vector_float4 lod_params;
    vector_float4 st_range;
    struct {
        unsigned int blue_mask;
        unsigned int blue_shift;
        unsigned int green_mask;
        unsigned int green_shift;
    } channel_shuffle;
    vector_float2 channel_shuffle_offset;
    vector_float2 tc_offset;
    vector_float2 st_scale;
    matrix_float4x4 dither_matrix;
    vector_float4 scale_factor;
};

// AUDIT REFERENCE: Section 3.2 — Attribute and function constant indices

enum GSMTLAttributes {
    GSMTLAttributeIndexST,
    GSMTLAttributeIndexC,
    GSMTLAttributeIndexQ,
    GSMTLAttributeIndexXY,
    GSMTLAttributeIndexZ,
    GSMTLAttributeIndexUV,
    GSMTLAttributeIndexF,
};
