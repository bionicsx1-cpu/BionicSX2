// BionicSX2 iOS — batch stubs for all uncategorized undefined symbols
#import <Foundation/Foundation.h>
#include "common/Pcsx2Defs.h"
#include "common/Assertions.h"
#include "common/Console.h"
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
#include "Vif_Dynarec.h"
#include "GS/GSDump.h"
#include "SaveState.h"
#include "Memory.h"
#include "Config.h"
#include "GSDumpReplayer.h"

// ── dVifUnpack template specializations (no-op stubs for iOS) ──
template<> void dVifUnpack<0>(const u8*, bool) {}
template<> void dVifUnpack<1>(const u8*, bool) {}

// ── SPU2 globals ──────────────────────────────────────────────
class V_Core;
struct StereoOut32 { int32_t Left = 0, Right = 0; };
struct SpdifOut { uint32_t data[2] = {}; };
StereoOut32 Cores[2] = {};
SpdifOut Spdif = {};
void TimeUpdate(u32) {}
void SPU2_FastWrite(u32, u16) {}
namespace isa_native {
    void ReverbUpsample(void*) {}
    void ReverbDownsample(void*, bool) {}
    void spu2Mix() {}
}

// ── VIF stubs ─────────────────────────────────────────────────
void VifUnpackSSE_Init() {}
void dVifReset(int) {}
void dVifRelease(int) {}

// ── vtlb stubs ────────────────────────────────────────────────
void vtlb_DynBackpatchLoadStore(uptr, u32, u32, u32, u32, u32, u8, u8, u8, bool, bool, bool) {}

// ── GS debug stubs ────────────────────────────────────────────
u32 g_first_free_vertex = 0;
void GSCaptureSyncPoint(int) {}

// ── ImGui globals ────────────────────────────────────────────
ImGuiContext* GImGui = nullptr;

// ── GSDumpReplayer stubs ────────────────────────────────────
R5900cpu GSDumpReplayerCpu;
bool GSDumpReplayer::Initialize(const char*, Error*) { return false; }
bool GSDumpReplayer::ChangeDump(const char*) { return false; }
std::string GSDumpReplayer::GetDumpSerial() { return {}; }
u32 GSDumpReplayer::GetDumpCRC() { return 0; }
void GSDumpReplayer::RenderUI() {}

// ── isa_native GS SW rasterizer stubs (MULTI_ISA dispatch) ──
class GSRasterizerData { public: static int s_counter; };
class GSRasterizerList { public: static GSRasterizerList* Create(int) { return nullptr; } };
int GSRasterizerData::s_counter = 0;
namespace isa_native {
    using ::GSRasterizerData;
    using ::GSRasterizerList;
}

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
struct USBPort;
struct OHCIState;
struct USBDevice;
void usb_attach(USBPort*) {}
void usb_reattach(USBPort*) {}
u32  ohci_create(u32, int) { return 0; }
void ohci_hard_reset(OHCIState*) {}
u32  ohci_mem_read(OHCIState*, u32) { return 0; }
void ohci_mem_write(OHCIState*, u32, u32) {}
void ohci_frame_boundary(void*) {}
void usb_desc_set_config(USBDevice*, int) {}
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
void ReconfigureLiveNet(const Pcsx2Config&) {}

// ── GSDumpBase stubs ───────────────────────────────────────
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
std::unique_ptr<SaveStateScreenshotData> SaveState_SaveScreenshot() { return nullptr; }
std::unique_ptr<ArchiveEntryList> SaveState_DownloadState(Error*) { return nullptr; }
bool SaveState_UnzipFromDisk(const std::string&, Error*) { return false; }
bool SaveState_ZipToDisk(std::unique_ptr<ArchiveEntryList>, std::unique_ptr<SaveStateScreenshotData>, const char*, Error*) { return false; }

// ── SaveStateBase stubs ─────────────────────────────────────
bool SaveStateBase::FreezeTag(const char*) { return false; }
void SaveStateBase::PrepBlock(int) {}

// ── HTTPDownloader stub ─────────────────────────────────────
#include "common/HTTPDownloader.h"
std::unique_ptr<HTTPDownloader> HTTPDownloader::Create(std::string) { return nullptr; }

// ── Host callbacks ────────────────────────────────────────────
namespace Host {
    void AddKeyedOSDMessage(std::string, std::string, float) {}
    void RemoveKeyedOSDMessage(std::string) {}
    void AddIconOSDMessage(std::string, const char*, std::string_view, float) {}
    void OnGameChanged(const std::string&, const std::string&, const std::string&, const std::string&, u32, u32) {}
    void CancelGameListRefresh() {}
}

// ── InputRecording stubs ──────────────────────────────────────
class InputRecording {
    static InputRecording s_instance;
public:
    static InputRecording& getControls() { return s_instance; }
    void handleReset() {}
    void incFrameCounter() {}
    void processRecordQueue() {}
    void handleLoadingSavestate() {}
    void handleControllerDataUpdate() {}
    void handleExceededFrameCounter() {}
    void stop() {}
};
InputRecording InputRecording::s_instance;

// ── CsoFileReader stub ────────────────────────────────────
class CsoFileReader { public: CsoFileReader() {} };

// ── ImGuiFreeType stub ────────────────────────────────────
namespace ImGuiFreeType { void* GetFontLoader() { return nullptr; } }

// ── MipsStackWalk stub ────────────────────────────────────
class DebugInterface;
namespace MipsStackWalk { bool Walk(DebugInterface*, u32, u32, u32, u32) { return false; } }

// ── InputManager keyboard stubs ────────────────────────────
namespace InputManager {
    std::optional<u32> ConvertHostKeyboardStringToCode(std::string_view) { return std::nullopt; }
    std::string ConvertHostKeyboardCodeToString(u32) { return {}; }
    const char* ConvertHostKeyboardCodeToIcon(u32) { return nullptr; }
}

// ── RegisterDevice stub ───────────────────────────────────
namespace RegisterDevice { void registerDevice() {} }

// ── DarwinMisc stubs ────────────────────────────────────────
struct CPUClass { std::string name; u32 physical, logical; };
namespace DarwinMisc { std::vector<CPUClass> GetCPUClasses() { return {}; } }

// ── GameDatabase stubs ──────────────────────────────────────
namespace GameDatabase { const void* findGame(std::string_view) { return nullptr; } }

// ── MIPSAnalyst stubs ──────────────────────────────────────
namespace ccc { class SymbolDatabase; }
namespace MIPSAnalyst { void ScanForFunctions(ccc::SymbolDatabase&, class MemoryInterface&, u32, u32, bool) {} }

// ── SysMemory_Reset wrapper ────────────────────────────────────
void SysMemory_Reset() { SysMemory::Reset(); }

// ── CocoaTools iOS additions ──────────────────────────────────
namespace CocoaTools {
    std::string GetNonTranslocatedBundlePath() {
        return std::string([[[NSBundle mainBundle] bundlePath] UTF8String]);
    }
}

// ── AudioStream backend stubs ─────────────────────────────────
std::unique_ptr<AudioStream> AudioStream::CreateCubebAudioStream(
    u32, const AudioStreamParameters&, const char*, const char*, bool, Error*) { return nullptr; }
std::unique_ptr<AudioStream> AudioStream::CreateSDLAudioStream(
    u32, const AudioStreamParameters&, bool, Error*) { return nullptr; }
std::vector<std::pair<std::string, std::string>> AudioStream::GetCubebDriverNames() { return {}; }
std::vector<AudioStream::DeviceInfo> AudioStream::GetCubebOutputDevices(const char*) { return {}; }

// ── Misc ──────────────────────────────────────────────────────
std::vector<std::string> GetMetalAdapterList() { return {}; }

// ── SaveState OSD report stubs ────────────────────────────────
void SaveState_ReportLoadErrorOSD(const std::string&, std::optional<int>, bool) {}
void SaveState_ReportSaveErrorOSD(const std::string&, std::optional<int>) {}

// ── PageFaultHandler stubs ──────────────────────────────────
namespace PageFaultHandler {
    bool Install() { return false; }
    bool InstallSecondaryThread() { return false; }
}

// ── FolderMemoryCardAggregator stubs ────────────────────────
class FolderMemoryCardAggregator {
public:
    bool Open() { return false; }
    void Close() {}
    bool Read(u32, u8*, u32, u32) { return false; }
    bool Save() { return false; }
    bool EraseBlock(u32) { return false; }
    u32 GetSizeInfo() { return 0; }
    void SetFiltering(bool) {}
    bool IsPSX() { return false; }
    u32 GetCRC() { return 0; }
    void NextFrame() {}
    void ReIndex() {}
    bool IsPresent() { return false; }
};
class FolderMemoryCard {
public:
    bool Open() { return false; }
    void Close() {}
    FolderMemoryCard() = default;
};

// ── ATA stubs ────────────────────────────────────────────
namespace ATA {
    void ATA_HardReset() {}
    bool Open() { return false; }
    void Close() {}
    bool Read(u32, u8*, u32) { return false; }
    bool Write(u32, const u8*, u32) { return false; }
    void Async() {}
    void ReadDMAToFIFO(u32) {}
    void WriteDMAFromFIFO(u32) {}
}

// ── GSSingleRasterizer stubs ─────────────────────────────
namespace isa_native {
    class GSSingleRasterizer {
    public:
        GSSingleRasterizer() = default;
        void Draw(void*) {}
    };
}

// ── FreeSurroundDecoder static member ────────────────────
#include <array>
#include "FreeSurroundDecoder.h"
const std::array<ChannelMap, static_cast<size_t>(ChannelSetup::MaxCount)> FreeSurroundDecoder::s_channel_maps = {};

// ── Host additional callbacks ────────────────────────────
namespace Host {
    void OnVMPaused() {}
    void OnVMResumed() {}
    void OnVMStarted() {}
    void LoadSettings(SettingsInterface&) {}
}

// ── InputRecordingControls stub ──────────────────────────
namespace InputRecordingControls {
    void processControlQueue() {}
}

// ── GS TextureReplacements stubs ─────────────────────────
#include "GS/GS.h"
namespace GSTextureReplacements {
    void DumpTexture(void*, void*, void*, void*, void*, int) {}
    void UpdateConfig() {}
    void* LookupReplacementTexture(void*, bool, bool) { return nullptr; }
    bool HasAnyReplacementTextures() { return false; }
    bool HasReplacementTextureWithOtherPalette(void*) { return false; }
}
