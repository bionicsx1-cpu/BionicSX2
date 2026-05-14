// BionicSX2 iOS — batch stubs for all uncategorized undefined symbols
#import <Foundation/Foundation.h>
#include "common/Pcsx2Defs.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <cstring>
#include <utility>
#include <optional>
#include <imgui.h>
#include "R5900.h"
#include "Host/AudioStream.h"

// ── Forward declarations ──────────────────────────────────────
class V_Core;
struct StereoOut32 { int32_t L, R; };
struct SpdifOut { uint32_t data[2]; };
using ReverbBuffer = float[2][2][2];
struct USBPort;
struct OHCIState;
struct USBDevice;

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
void vtlb_DynBackpatchLoadStore(uptr, u32, u32, u32, u32, u32, u8, u8, u8, bool, bool, bool) {}

// ── GS debug stubs ────────────────────────────────────────────
u32 g_first_free_vertex = 0;
void GSCaptureSyncPoint(int) {}

// ── ImGui globals ────────────────────────────────────────────
ImGuiContext* GImGui = nullptr;

// ── GSDumpReplayer ────────────────────────────────────────────
R5900cpu GSDumpReplayerCpu = {};

// ── PGIF stubs ──────────────────────────────────────────────
void PGIFrQword(u32, void*) {}
void PGIFwQword(u32, void*) {}
u32 PGIFr(int) { return 0; }
void PGIFw(int, u32) {}
void pgifInit() {}

// ── smap stubs ──────────────────────────────────────────────
void smap_async(u32) {}
u8  smap_read8(u32) { return 0; }
u16 smap_read16(u32) { return 0; }
u32 smap_read32(u32) { return 0; }
void smap_write8(u32, u8) {}
void smap_write16(u32, u16) {}
void smap_write32(u32, u32) {}
void smap_readDMA8Mem(u32*, int) {}
void smap_writeDMA8Mem(u32*, int) {}

// ── FLASH stubs ────────────────────────────────────────────
u32 FLASHread32(u32, int) { return 0; }
void FLASHwrite32(u32, u32, int) {}
void FLASHinit() {}

// ── USB/OHCI stubs ─────────────────────────────────────────
void usb_attach(USBPort*) {}
void usb_reattach(USBPort*) {}
u32  ohci_create(u32, int) { return 0; }
void ohci_hard_reset(OHCIState*) {}
u32  ohci_mem_read(OHCIState*, u32) { return 0; }
void ohci_mem_write(OHCIState*, u32, u32) {}
void ohci_frame_boundary(void*) {}
void usb_desc_set_config(USBDevice*, int, int) {}
void usb_desc_set_interface(USBDevice*, int, int) {}

// ── PS2 GPU DMA stubs ──────────────────────────────────────
void psxDma2GpuR(u32) {}
void psxDma2GpuW(u32, u32) {}
u32 psxGPUr(int) { return 0; }
void psxGPUw(int, u32) {}

// ── SIF stubs ──────────────────────────────────────────────
void sifReset() {}
void SIF1Dma() {}
void dmaSIF1() {}
void dmaSIF2() {}
void EEsif1Interrupt() {}
void sif1Interrupt() {}
void sif2Interrupt() {}

// ── FIFO stubs ─────────────────────────────────────────────
void ReadFIFO_VIF1(u128*) {}
void WriteFIFO_VIF0(const u128*) {}
void WriteFIFO_VIF1(const u128*) {}
void WriteFIFO_GIF(const u128*) {}
void ReadFifoSingleWord() {}

// ── NET stubs ──────────────────────────────────────────────
void InitNet() {}
void TermNet() {}
void ReconfigureLiveNet(const void*) {}

// ── GSDumpBase stubs ───────────────────────────────────────
#include "GS/GSDump.h"
std::unique_ptr<GSDumpBase> GSDumpBase::CreateUncompressedDump(
    const std::string&, const std::string&, u32, u32, u32, const u32*, const freezeData&, const GSPrivRegSet*) { return nullptr; }
std::unique_ptr<GSDumpBase> GSDumpBase::CreateXzDump(
    const std::string&, const std::string&, u32, u32, u32, const u32*, const freezeData&, const GSPrivRegSet*) { return nullptr; }
std::unique_ptr<GSDumpBase> GSDumpBase::CreateZstDump(
    const std::string&, const std::string&, u32, u32, u32, const u32*, const freezeData&, const GSPrivRegSet*) { return nullptr; }
bool GSDumpBase::VSync(int, bool, const GSPrivRegSet*) { return false; }
void GSDumpBase::ReadFIFO(u32) {}
void GSDumpBase::Transfer(int, const u8*, size_t) {}

// ── SaveState stubs ──────────────────────────────────────────
#include "SaveState.h"
std::unique_ptr<SaveStateScreenshotData> SaveState_SaveScreenshot() { return nullptr; }
std::unique_ptr<ArchiveEntryList> SaveState_DownloadState(Error*) { return nullptr; }
bool SaveState_UnzipFromDisk(const std::string&, Error*) { return false; }
bool SaveState_ZipToDisk(std::unique_ptr<ArchiveEntryList>, std::unique_ptr<SaveStateScreenshotData>, const char*, Error*) { return false; }

// ── Host callbacks (only functions NOT in Host.cpp/iOSVMManager) ──
namespace Host {
    void AddKeyedOSDMessage(std::string key, std::string msg, float duration) {}
    void RemoveKeyedOSDMessage(std::string key) {}
    void AddIconOSDMessage(std::string key, const char* icon, std::string_view msg, float duration) {}
    void OnGameChanged(const std::string&, const std::string&, const std::string&, const std::string&, u32, u32) {}
    void CancelGameListRefresh() {}
}

// ── DarwinMisc stubs (DarwinMisc.cpp excluded — uses CoreGraphics) ──
#include <string>
struct CPUClass { std::string name; u32 physical, logical; };
std::vector<CPUClass> GetCPUClasses() { return {}; }

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
