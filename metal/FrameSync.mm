// NEW FILE: split from pcsx2/GS/Renderers/Metal/GSDeviceMTL.mm — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 4.2, 13.4
// STATUS: NEW — Frame buffer synchronization using MTLFence

#import <Metal/Metal.h>
#import <Foundation/Foundation.h>

#include <cstdint>
#include <atomic>

// AUDIT REFERENCE: Section 4.2 — Frame synchronization primitives
// MTLFence, MTLCommandBuffer completion handlers, draw ID tracking
// Separated from device creation for iOS clarity (Audit Section 13.4)

class FrameSync {
public:
    FrameSync() {}
    ~FrameSync() { Destroy(); }

    bool Initialize(id<MTLDevice> device)
    {
        m_device = device;

        // AUDIT REFERENCE: Section 4.2 — MTLFence for GPU-CPU synchronization
        m_drawFence = [device newFence];
        if (!m_drawFence)
        {
            NSLog(@"[BionicSX2] FrameSync: failed to create MTLFence (Audit Sec 4.2)");
            return false;
        }

        m_initialized = true;
        NSLog(@"[BionicSX2] FrameSync initialized (Audit Sec 4.2)");
        return true;
    }

    void Destroy()
    {
        m_drawFence = nil;
        m_device = nil;
        m_initialized = false;
    }

    // AUDIT REFERENCE: Section 4.2 — Get current draw ID
    uint64_t GetCurrentDraw() const { return m_currentDraw; }

    // AUDIT REFERENCE: Section 4.2 — Advance draw ID after commit
    void AdvanceDraw() { m_currentDraw++; }

    // AUDIT REFERENCE: Section 4.2 — Last finished draw ID (set via completion handler)
    uint64_t GetLastFinishedDraw() const
    {
        return m_lastFinishedDraw.load(std::memory_order_acquire);
    }

    // AUDIT REFERENCE: Section 4.2 — Called from command buffer completion handler
    void OnCommandBufferCompleted(uint64_t draw)
    {
        uint64_t newval = std::max(draw, m_lastFinishedDraw.load(std::memory_order_relaxed));
        m_lastFinishedDraw.store(newval, std::memory_order_release);
    }

    // AUDIT REFERENCE: Section 4.2 — Add completion handler to command buffer
    void AddCompletionHandler(id<MTLCommandBuffer> cmdBuf, uint64_t draw)
    {
        __block FrameSync* sync = this;
        __block uint64_t drawID = draw;
        [cmdBuf addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
            sync->OnCommandBufferCompleted(drawID);
        }];
    }

    // AUDIT REFERENCE: Section 4.2 — Get draw sync fence
    id<MTLFence> GetDrawFence() const { return m_drawFence; }

    bool IsInitialized() const { return m_initialized; }

private:
    id<MTLDevice> m_device = nil;
    id<MTLFence> m_drawFence = nil;
    uint64_t m_currentDraw = 1;
    std::atomic<uint64_t> m_lastFinishedDraw{0};
    bool m_initialized = false;
};
