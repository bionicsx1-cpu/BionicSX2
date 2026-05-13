// PORTED FROM: pcsx2/GS/Renderers/Metal/GSMTLDeviceInfo.mm — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 3.2, 4.2, 13.4
// STATUS: GREEN — no platform changes needed

#import <Metal/Metal.h>
#include <cstdint>

// AUDIT REFERENCE: Section 4.2 — Metal device feature detection
// All features queried here are available on iOS Metal 2.0+

struct MetalDeviceFeatures {
    bool unified_memory         : 1;  // Always true on Apple Silicon iOS
    bool texture_swizzle        : 1;  // Available on A13+ / M1+
    bool framebuffer_fetch      : 1;  // Available on A8+
    bool primid                 : 1;  // Available on A13+
    bool memoryless_textures    : 1;  // Available on A13+ (TBDR)
    bool depth_feedback         : 1;  // Available on A13+
    uint32_t max_texsize;
};

// AUDIT REFERENCE: Section 13.4 — AMD slow_color_compression heuristic removed
// This is specific to AMD GPUs on macOS and has no relevance to Apple Silicon iOS

MetalDeviceFeatures MetalDevice_GetFeatures(id<MTLDevice> device)
{
    MetalDeviceFeatures features = {};
    features.unified_memory = true;  // All iOS devices have unified memory (Audit Sec 4.3)
    features.texture_swizzle = [device supportsFamily:MTLGPUFamilyApple3];
    features.framebuffer_fetch = [device supportsFamily:MTLGPUFamilyApple1];
    features.primid = [device supportsFamily:MTLGPUFamilyApple3];
    features.memoryless_textures = [device supportsFamily:MTLGPUFamilyApple3];
    features.depth_feedback = [device supportsFamily:MTLGPUFamilyApple3];
    features.max_texsize = [device supportsFamily:MTLGPUFamilyApple4] ? 16384 : 8192;

    return features;
}

uint32_t MetalDevice_GetMaxTextureSize(id<MTLDevice> device)
{
    if ([device supportsFamily:MTLGPUFamilyApple4])
        return 16384;
    return 8192;
}
