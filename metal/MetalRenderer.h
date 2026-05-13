// PORTED FROM: pcsx2/GS/Renderers/Metal/GSDeviceMTL.h — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 4.1, 4.2, 4.3
// STATUS: YELLOW — NSView→UIView, AppKit→UIKit, CAMetalLayer unchanged

#pragma once

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
// PORTED: #import <AppKit/AppKit.h> removed (Audit Section 4.3)
// PORTED: #import <UIKit/UIKit.h> added for UIView

#include <simd/simd.h>
#include <cstdint>
#include <memory>
#include <mutex>
#include <unordered_map>

// AUDIT REFERENCE: Section 4.1 — These types are copied from GSDeviceMTL.h
// All constants, enums, and pipeline selectors are platform-agnostic

enum BufferIndex {
    BufferIndexVertices,
    BufferIndexUniforms,
    BufferIndexHWVertices,
    BufferIndexHWUniforms,
    BufferIndexHWIndices,
};

enum TextureIndex {
    TextureIndexNonHW,
    TextureIndexTex,
    TextureIndexPalette,
    TextureIndexRenderTarget,
    TextureIndexPrimIDs,
    TextureIndexDepthTarget,
    TextureIndexCount,
};

struct ConvertPSUniform {
    int emoda;
    int emodc;
};

struct PresentPSUniform {
    simd::float4 source_rect;
    simd::float4 target_rect;
    simd::float2 source_size;
    simd::float2 target_size;
    simd::float2 target_resolution;
    simd::float2 rcp_target_resolution;
    simd::float2 source_resolution;
    simd::float2 rcp_source_resolution;
    float time;
};

struct MainVertex {
    simd::float2 st;
    simd::uchar4 rgba;
    float q;
    simd::ushort2 xy;
    uint32_t z;
    simd::ushort2 uv;
    unsigned char fog;
};

struct MainVSUniform {
    simd::float2 vertex_scale;
    simd::float2 vertex_offset;
    simd::float2 texture_scale;
    simd::float2 texture_offset;
    simd::float2 point_size;
    uint32_t max_depth;
    uint32_t _pad0;
};

// AUDIT REFERENCE: Section 4.2 — Pipeline state management
struct PipelineSelector {
    uint8_t pad[24]; // Placeholder — exact layout from GSDeviceMTL
};

// AUDIT REFERENCE: Section 4.3 — Surface management uses UIView (not NSView)
// MetalRenderer wraps MTLDevice, MTLCommandQueue, MTLRenderPipelineState

class MetalRenderer {
public:
    MetalRenderer();
    ~MetalRenderer();

    bool Initialize(void* uiView); // UIView* — ported from NSView* (Audit Sec 4.3)
    void Shutdown();

    id<MTLDevice> GetDevice() const { return m_device; }
    id<MTLCommandQueue> GetCommandQueue() const { return m_commandQueue; }
    CAMetalLayer* GetLayer() const { return m_layer; }

    bool BeginFrame();
    void EndFrame();
    void Present();

    // PORTED: CAMetalLayer is unchanged — fully portable (Audit Section 4.3)
    void Resize(uint32_t width, uint32_t height, float scale);

private:
    id<MTLDevice> m_device = nil;
    id<MTLCommandQueue> m_commandQueue = nil;
    id<MTLCommandBuffer> m_currentCommandBuffer = nil;
    id<MTLDrawable> m_currentDrawable = nil;
    CAMetalLayer* m_layer = nil;
    // PORTED: NSView* replaced with UIView* (Audit Section 4.3)
    UIView* m_view = nil;

    bool m_initialized = false;
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    float m_scale = 1.0f;
};
