// BionicSX2 iOS — batch stubs for all uncategorized undefined symbols
#import <Foundation/Foundation.h>
#include "common/Pcsx2Defs.h"
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
void TimeUpdate(u32 clocks) {}
void SPU2_FastWrite(u32 rmem, u16 value) {}
namespace isa_native {
    void ReverbUpsample(V_Core& core) {}
    void ReverbDownsample(V_Core& core, bool mix) {}
    void spu2Mix() {}
}

// ── VIF stubs ─────────────────────────────────────────────────
void VifUnpackSSE_Init() {}
void dVifReset(int idx) {}
void dVifRelease(int idx) {}

// ── vtlb stubs ────────────────────────────────────────────────
void vtlb_DynBackpatchLoadStore(uptr code_address, u32 guest_pc,
    u32 gpr_bitmask, u32 fpr_bitmask, u8 address_register,
    u8 data_register, u8 size_in_bits, bool is_signed,
    bool is_load, bool is_vector) {}

// ── GS debug stubs ────────────────────────────────────────────
u32 g_first_free_vertex = 0;
void GSCaptureSyncPoint(int) {}

// ── ImGui stubs ──────────────────────────────────────────────
namespace ImGuiManager {
    bool Initialize() { return true; }
    void Shutdown(bool clear_state) {}
    bool HasSoftwareCursor(u32 index) { return false; }
    void ProcessHostKeyEvent(void* key, float value) {}
    void UpdateMousePosition(float x, float y) {}
    void InitializeFullscreenUI() {}
}
namespace ImGuiFullscreen {
    void* g_large_font = nullptr;
    void* g_medium_font = nullptr;
    float g_layout_scale = 1.0f;
    float g_rcp_layout_scale = 1.0f;
    u32 UIPrimaryColor = 0;
    u32 UISecondaryColor = 0;
}
namespace FullscreenUI {
    bool IsInitialized() { return false; }
    void ReturnToMainWindow() {}
    bool IsAchievementsWindowOpen() { return false; }
}

// ── GSDumpReplayer stubs ─────────────────────────────────────
namespace GSDumpReplayer {
    bool Initialize(const char*, void*) { return false; }
    bool ChangeDump(const char*) { return false; }
}

// ── SaveState stubs ──────────────────────────────────────────
void SaveState_ZipToDisk(void*, void*, const char*, void*) {}
void SaveState_ReportLoadErrorOSD(const std::string&, std::optional<int>, bool) {}
void SaveState_ReportSaveErrorOSD(const std::string&, std::optional<int>) {}

// ── CBreakPoints stubs ───────────────────────────────────────
namespace CBreakPoints {
    void AddBreakPoint(int, u32, bool, bool, bool) {}
    bool IsAddressBreakPoint(int, u32) { return false; }
    std::vector<u32> GetMemChecks(int) { return {}; }
    u32 GetBreakpointCause(int) { return 0; }
}

// ── DarwinMisc stubs (CoreGraphics/IOKit not on iOS) ────────

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
std::vector<std::string> GetMetalAdapterList() { return {}; }

// ── Host callbacks ────────────────────────────────────────────
namespace Host {
    void OnVMStarted() {}
    void OnVMDestroyed() {}
    void SetMouseMode(bool relative, bool hide) {}
    void AddKeyedOSDMessage(std::string key, std::string msg, float duration) {}
    void RemoveKeyedOSDMessage(std::string key) {}
    void AddIconOSDMessage(std::string key, const char* icon, std::string_view msg, float duration) {}
    void OnGameChanged(const std::string&, const std::string&, const std::string&, const std::string&, u32, u32) {}
    void RequestResizeHostDisplay(s32 w, s32 h) {}
    void OnPerformanceMetricsUpdated() {}
    void CheckForSettingsChanges(const void* old) {}
    void CommitBaseSettingChanges() {}
    bool BeginPresentFrame() { return true; }
    void CancelGameListRefresh() {}
}

// ── AudioStream backend stubs ─────────────────────────────────
#include "Host/AudioStream.h"
std::unique_ptr<AudioStream> AudioStream::CreateCubebAudioStream(
    u32 sr, const AudioStreamParameters& p, const char* drv, const char* dev, bool ss, Error* e)
{ return nullptr; }
std::unique_ptr<AudioStream> AudioStream::CreateSDLAudioStream(
    u32 sr, const AudioStreamParameters& p, bool ss, Error* e)
{ return nullptr; }
std::vector<std::string> AudioStream::GetCubebDriverNames() { return {}; }
std::vector<AudioStream::DeviceInfo> AudioStream::GetCubebOutputDevices(const char* drv) { return {}; }
