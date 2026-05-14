// PORTED FROM: pcsx2/GS/Renderers/Metal/GSDeviceMTL.mm — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 4.1, 4.2, 4.3
// STATUS: YELLOW — NSView→UIView, AppKit→UIKit, CAMetalLayer unchanged

#import "MetalRenderer.h"
// PORTED: #import <AppKit/AppKit.h> removed (Audit Section 4.3)
#import <UIKit/UIKit.h>
// PORTED: CAMetalLayer is fully portable — no changes needed (Audit Section 4.3)

#import <simd/simd.h>
#include <cassert>

// AUDIT REFERENCE: Section 4.2 — MTLDevice, MTLCommandQueue setup
// All Metal API calls used here are identical on iOS and macOS

MetalRenderer::MetalRenderer()
{
}

MetalRenderer::~MetalRenderer()
{
    Shutdown();
}

// AUDIT REFERENCE: Section 4.3 — Surface management
// PORTED: NSView* → UIView* for surface handle
// CAMetalLayer creation is identical per Audit Section 4.3
bool MetalRenderer::Initialize(void* uiView)
{
    if (m_initialized)
        return true;

    // PORTED: UIView* instead of NSView* (Audit Section 4.3)
    m_view = (__bridge UIView*)uiView;
    if (!m_view)
    {
        NSLog(@"[BionicSX2] MetalRenderer: no UIView provided (Audit Sec 4.3)");
        return false;
    }

    // AUDIT REFERENCE: Section 4.2 — MTLDevice creation (identical on iOS)
    m_device = MTLCreateSystemDefaultDevice();
    if (!m_device)
    {
        NSLog(@"[BionicSX2] MetalRenderer: failed to create MTLDevice (Audit Sec 4.2)");
        return false;
    }

    NSLog(@"[BionicSX2] MetalRenderer: device = %@ (Audit Sec 4.2)", [m_device name]);

    // AUDIT REFERENCE: Section 4.2 — MTLCommandQueue creation (identical on iOS)
    m_commandQueue = [m_device newCommandQueue];
    if (!m_commandQueue)
    {
        NSLog(@"[BionicSX2] MetalRenderer: failed to create command queue (Audit Sec 4.2)");
        return false;
    }

    // AUDIT REFERENCE: Section 4.3 — CAMetalLayer creation (identical on iOS and macOS)
    m_layer = [CAMetalLayer layer];
    m_layer.device = m_device;
    m_layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    m_layer.framebufferOnly = YES;
    m_layer.drawsAsynchronously = YES;

    // AUDIT REFERENCE: Section 4.2 — Scale and frame
    CGFloat scale = [UIScreen mainScreen].nativeScale;
    m_layer.contentsScale = scale;
    m_layer.frame = m_view.bounds;

    [m_view.layer addSublayer:m_layer];

    m_width = (uint32_t)(m_view.bounds.size.width * scale);
    m_height = (uint32_t)(m_view.bounds.size.height * scale);
    m_scale = scale;

    m_initialized = true;
    NSLog(@"[BionicSX2] MetalRenderer initialized: %dx%d @%.0f scale (Audit Sec 4.3)",
          m_width, m_height, m_scale);
    return true;
}

// AUDIT REFERENCE: Section 4.2 — Shutdown
void MetalRenderer::Shutdown()
{
    if (m_layer)
    {
        [m_layer removeFromSuperlayer];
        m_layer = nil;
    }
    m_commandQueue = nil;
    m_device = nil;
    m_view = nil;
    m_initialized = false;
    NSLog(@"[BionicSX2] MetalRenderer shutdown (Audit Sec 4.2)");
}

// AUDIT REFERENCE: Section 4.2 — Frame begin (identical on iOS)
bool MetalRenderer::BeginFrame()
{
    if (!m_initialized) return false;

    // AUDIT REFERENCE: Section 4.2 — Get next drawable from CAMetalLayer
    // This is identical on iOS and macOS
    m_currentDrawable = [m_layer nextDrawable];
    if (!m_currentDrawable)
    {
        NSLog(@"[BionicSX2] MetalRenderer: nextDrawable returned nil (Audit Sec 4.2)");
        return false;
    }

    // AUDIT REFERENCE: Section 4.2 — Create command buffer
    m_currentCommandBuffer = [m_commandQueue commandBuffer];
    if (!m_currentCommandBuffer)
    {
        NSLog(@"[BionicSX2] MetalRenderer: failed to create command buffer (Audit Sec 4.2)");
        return false;
    }

    return true;
}

// AUDIT REFERENCE: Section 4.2 — Frame end and commit
void MetalRenderer::EndFrame()
{
    if (m_currentCommandBuffer)
    {
        [m_currentCommandBuffer commit];
    }
}

// AUDIT REFERENCE: Section 4.2 — Present to screen (identical on iOS)
void MetalRenderer::Present()
{
    if (m_currentCommandBuffer && m_currentDrawable)
    {
        [m_currentCommandBuffer presentDrawable:m_currentDrawable];
        [m_currentCommandBuffer waitUntilCompleted];
    }
    m_currentCommandBuffer = nil;
    m_currentDrawable = nil;
}

// AUDIT REFERENCE: Section 4.3 — Resize with UIView bounds (port of NSView resize)
void MetalRenderer::Resize(uint32_t width, uint32_t height, float scale)
{
    if (!m_layer || !m_view) return;

    CGFloat s = (scale > 0) ? scale : [UIScreen mainScreen].nativeScale;
    m_layer.frame = m_view.bounds;
    m_layer.contentsScale = s;
    m_layer.drawableSize = CGSizeMake(m_view.bounds.size.width * s,
                                       m_view.bounds.size.height * s);

    m_width = (uint32_t)(m_view.bounds.size.width * s);
    m_height = (uint32_t)(m_view.bounds.size.height * s);
    m_scale = s;

    NSLog(@"[BionicSX2] MetalRenderer resized: %dx%d @%.0f scale (Audit Sec 4.3)",
          m_width, m_height, m_scale);
}

// iOS stub — MakeGSDeviceMTL from original PCSX2 Metal backend
// Uses AppKit/NSView which is not available on iOS.
// Returns nullptr — GS.cpp will fall back to SW/null renderer.
// Full Metal integration requires wrapping our MetalRenderer into GSDevice API.
class GSDevice;
GSDevice* MakeGSDeviceMTL() { return nullptr; }
