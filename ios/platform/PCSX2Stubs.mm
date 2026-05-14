// BionicSX2 iOS — batch stubs for all uncategorized undefined symbols
// Import-export foundation
#import <Foundation/Foundation.h>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <cstring>

// ── Forward declarations ──────────────────────────────────────
class V_Core;
struct StereoOut32 { int32_t L, R; };
struct SpdifOut { uint32_t data[2]; };
using ReverbBuffer = float[2][2][2];

// ── SPU2 globals ──────────────────────────────────────────────
StereoOut32 Cores[2] = {};
SpdifOut Spdif = {};
void TimeUpdate(u32 cClocks) {}
void SPU2_FastWrite(u32 rmem, u16 value) {}
namespace isa_native {
    void ReverbUpsample(V_Core& core) {}
    void ReverbDownsample(V_Core& core, bool mix) {}
    void spu2Mix() {}
}

// ── VIF stubs ─────────────────────────────────────────────────
extern void VifUnpackSSE_Init() {}
extern void dVifReset(int idx) {}
extern void dVifRelease(int idx) {}

// ── vtlb stubs ────────────────────────────────────────────────
void vtlb_DynBackpatchLoadStore(uptr code_address, u32 guest_pc,
    u32 gpr_bitmask, u32 fpr_bitmask, u8 address_register,
    u8 data_register, u8 size_in_bits, bool is_signed,
    bool is_load, bool is_vector) {}

// ── GS debug/perf stubs ──────────────────────────────────────
extern u32 g_first_free_vertex = 0;
extern void GSCaptureSyncPoint(int) {}

// ── ImGui stubs ──────────────────────────────────────────────
#include "imgui.h"
namespace ImGuiManager {
    bool Initialize() { return true; }
    void Shutdown(bool clear_state) {}
    bool HasSoftwareCursor(u32 index) { return false; }
    void ProcessHostKeyEvent(void* key, float value) {}
    void UpdateMousePosition(float x, float y) {}
    void InitializeFullscreenUI() {}
}
namespace ImGuiFullscreen {
    ImFont* g_large_font = nullptr;
    ImFont* g_medium_font = nullptr;
    float g_layout_scale = 1.0f;
    float g_rcp_layout_scale = 1.0f;
    uint32_t UIPrimaryColor = 0;
    uint32_t UISecondaryColor = 0;
}
namespace FullscreenUI {
    bool IsInitialized() { return false; }
    void ReturnToMainWindow() {}
    bool IsAchievementsWindowOpen() { return false; }
}
namespace Host {
    void OnVMStarted() {}
    void OnVMDestroyed() {}
    void SetMouseMode(bool relative, bool hide) {}
}

// ── GSDumpReplayer stubs ─────────────────────────────────────
namespace GSDumpReplayer {
    bool Initialize(const char*, void*) { return false; }
    void ChangeDump(const char*) {}
}

// ── SaveState stubs ──────────────────────────────────────────
void SaveState_ZipToDisk(void*, void*, const char*, void*) {}
void SaveState_ReportLoadErrorOSD(const std::string&, std::optional<int>, bool) {}
void SaveState_ReportSaveErrorOSD(const std::string&, std::optional<int>) {}

// ── CBreakPoints stubs ───────────────────────────────────────
namespace CBreakPoints {
    void AddBreakPoint(int, uint32_t, bool, bool, bool) {}
    bool IsAddressBreakPoint(int, uint32_t) { return false; }
    std::vector<uint32_t> GetMemChecks(int) { return {}; }
    uint32_t GetBreakpointCause(int) { return 0; }
}

// ── InputRecording stubs ──────────────────────────────────────
namespace InputRecording {
    bool IsActive() { return false; }
    void IncFrameCounter() {}
}
namespace InputRecordingControls {
    bool IsRecording() { return false; }
}
InputRecording g_InputRecording = {};

// ── SymbolGuardian stubs ─────────────────────────────────────
void* R3000SymbolGuardian = nullptr;
void* R5900SymbolImporter = nullptr;

// ── DarwinMisc stubs (CoreGraphics/IOKit not on iOS) ────────
bool HostSys::IsPerformanceCore(int cpu) { return cpu < 4; }

// ── SysMemory_Reset wrapper ────────────────────────────────────
#include "Memory.h"
void SysMemory_Reset() { SysMemory::Reset(); }

// ── CocoaTools iOS additions ──────────────────────────────────
namespace CocoaTools {
    std::string GetNonTranslocatedBundlePath() {
        return std::string([[[NSBundle mainBundle] bundlePath] UTF8String]);
    }
}

// ── Misc ──────────────────────────────────────────────────────
#include "GS/GS.h"
#include "GSDumpReplayer.h"
GSDumpReplayerCpu::GSDumpReplayerCpu() = default;
GSDumpReplayerCpu::~GSDumpReplayerCpu() = default;

// GetMetalAdapterList (called from GS.cpp when Metal backend)


#include <string>
std::vector<std::string> GetMetalAdapterList() { return {}; }
