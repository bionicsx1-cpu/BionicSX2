// PORTED FROM: pcsx2/GS/Renderers/Metal/GSTextureMTL.mm — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 3.5, 4.2
// STATUS: GREEN — MTLResourceStorageModeShared works on iOS Apple Silicon

#import <Metal/Metal.h>
#include <cstdint>

// AUDIT REFERENCE: Section 3.5 — MTLTexture wrapper for iOS
// MTLResourceStorageModeShared is the default on Apple Silicon iOS devices
// No platform-specific changes needed

class MetalTexture {
public:
    MetalTexture() {}
    ~MetalTexture() { Release(); }

    bool Create(id<MTLDevice> device, uint32_t width, uint32_t height,
                MTLPixelFormat format, MTLTextureUsage usage, bool renderTarget)
    {
        MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:format
                                                                                        width:width
                                                                                       height:height
                                                                                    mipmapped:NO];
        desc.usage = usage;
        desc.storageMode = MTLStorageModeShared;  // Portable — Audit Sec 3.5
        desc.cpuCacheMode = MTLCPUCacheModeWriteCombined;

        if (renderTarget)
        {
            desc.usage |= MTLTextureUsageRenderTarget;
        }

        m_texture = [device newTextureWithDescriptor:desc];
        if (!m_texture) return false;

        m_width = width;
        m_height = height;
        m_format = format;
        m_device = device;
        return true;
    }

    void Release()
    {
        m_texture = nil;
    }

    id<MTLTexture> GetTexture() const { return m_texture; }
    uint32_t GetWidth() const { return m_width; }
    uint32_t GetHeight() const { return m_height; }
    MTLPixelFormat GetFormat() const { return m_format; }

    // AUDIT REFERENCE: Section 3.5 — Upload via blit encoder (identical on iOS)
    bool UpdateFromCPU(id<MTLCommandBuffer> cmdBuf, const void* data, uint32_t bytesPerRow)
    {
        if (!m_texture || !data) return false;

        id<MTLBlitCommandEncoder> blit = [cmdBuf blitCommandEncoder];
        [blit copyFromBuffer:(__bridge id<MTLBuffer>)data
               sourceOffset:0
          sourceBytesPerRow:bytesPerRow
        sourceBytesPerImage:bytesPerRow * m_height
                 sourceSize:MTLSizeMake(m_width, m_height, 1)
                  toTexture:m_texture
           destinationSlice:0
           destinationLevel:0
          destinationOrigin:MTLOriginMake(0, 0, 0)];
        [blit endEncoding];
        return true;
    }

private:
    id<MTLTexture> m_texture = nil;
    id<MTLDevice> m_device = nil;
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    MTLPixelFormat m_format = MTLPixelFormatInvalid;
};
