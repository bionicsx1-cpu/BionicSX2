# PORTED FROM: pcsx2/CMakeLists.txt — BionicSX2 iOS Port
# AUDIT REFERENCE: Sections 10.1, 10.2, 1.4, 1.5
# STATUS: YELLOW — iOS-specific framework and exclusion configuration

cmake_minimum_required(VERSION 3.20)
project(BionicSX2)

# AUDIT REFERENCE: Section 13.5 — iOS toolchain and deployment target
include(cmake/ios.toolchain.cmake)
set(CMAKE_OSX_DEPLOYMENT_TARGET 15.0)
set(CMAKE_OSX_ARCHITECTURES arm64)

# AUDIT REFERENCE: Section 10.2 — Enable Objective-C++ for .mm files
enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# cannot be linked into iOS targets.

# AUDIT REFERENCE: Section 1.5 — Core emulator target
add_library(bionicsx2_core STATIC
    # EE Core (Audit Sec 2.1 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/R5900.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/R5900OpcodeImpl.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/R5900OpcodeTables.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Interpreter.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Memory.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/MMI.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/COP0.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/COP2.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Counters.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Dmac.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/FPU.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Gif.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Gif_Unit.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Hw.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/HwRead.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/HwWrite.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SPR.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Vif.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Vif_Codes.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Vif_Transfer.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Vif_Unpack.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Vif0_Dma.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Vif1_Dma.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Vif1_MFIFO.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/vtlb.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Cache.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/FW.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Mdec.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Sif0.cpp

    # VU Units (Audit Sec 2.2 — GREEN, interpreter paths only)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VU0.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VU0micro.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VU0microInterp.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VU1micro.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VU1microInterp.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VUmicro.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VUmicroMem.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VUflags.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VUops.cpp

    # IOP (Audit Sec 2.3 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/R3000A.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/R3000AInterpreter.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/R3000AOpcodeTables.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IopBios.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IopCounters.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IopDma.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IopGte.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IopHw.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IopMem.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IopIrq.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/ps2/Iop/IopHwRead.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/ps2/Iop/IopHwWrite.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/ps2/Iop/PsxBios.cpp

    # CDVD (Audit Sec 2.6 — GREEN, ISO-only path)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/CDVD.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/CDVDdiscReader.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/CDVDcommon.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/ChdFileReader.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/CDVDisoReader.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/InputIsoFile.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/OutputIsoFile.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/ThreadedFileReader.cpp
    # EXCLUDED: CDVD/CsoFileReader.cpp — requires lz4 (not available on iOS)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/FlatFileReader.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/IsoReader.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/BlockdumpFileReader.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/GzippedFileReader.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/IsoHasher.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/CDVDdiscThread.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/CDVD/Ps1CD.cpp
    # EXCLUDED: CDVD/Darwin/, CDVD/Linux/, CDVD/Windows/ — platform-specific optical drive I/O

    # IPU (Audit Sec 2.4 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IPU/IPU.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IPU/IPU_Fifo.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IPU/IPU_MultiISA.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IPU/IPUdither.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IPU/IPUdma.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/IPU/yuv2rgb.cpp

    # GS Core (Audit Sec 2.4 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GS.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSBlock.cpp
    # EXCLUDED: GS/GSCapture.cpp — depends on ffmpeg (not available on iOS)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSClut.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSDrawingContext.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSDrawingEnvironment.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSLocalMemory.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSLocalMemoryMultiISA.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSPerfMon.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSRingHeap.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSState.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSTables.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSUtil.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSVector.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GSXXH.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/MultiISA.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/MTGS.cpp

    # GS Renderer Common (Audit Sec 2.4 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/Common/GSDevice.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/Common/GSDirtyRect.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/Common/GSFunctionMap.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/Common/GSRenderer.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/Common/GSTexture.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/Common/GSVertexTrace.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/Common/GSVertexTraceFMM.cpp

    # GS Renderer HW (Audit Sec 2.4 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/HW/GSHwHack.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/HW/GSRendererHW.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/HW/GSRendererHWMultiISA.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/HW/GSTextureCache.cpp
    # EXCLUDED: GSTextureReplacementLoaders/Replacements — HD texture packs
    # require libpng/libjpeg/libwebp. Non-critical for core emulation.

    # GS Renderer SW (Audit Sec 2.4 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSDrawScanline.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSDrawScanlineCodeGenerator.arm64.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSRasterizer.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSRendererSW.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSSetupPrimCodeGenerator.arm64.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSTextureCacheSW.cpp

    # GS Renderer Null (Audit Sec 2.4 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/Null/GSRendererNull.cpp

    # SPU2 (Audit Sec 2.5 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SPU2/spu2.cpp

    # SIO / PAD / Memcard (Audit Sec 2.7 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SIO/Sio.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SIO/Sio0.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SIO/Sio2.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SIO/Pad/Pad.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SIO/Pad/PadBase.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SIO/Pad/PadDualshock2.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SIO/Memcard/MemoryCardFile.cpp
    # EXCLUDED: SIO/Memcard/MemoryCardFolder.cpp — requires rapidyaml (ryml), not in 3rdparty
    # Core save/load still works via MemoryCardFile + MemoryCardProtocol
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SIO/Memcard/MemoryCardProtocol.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SIO/Multitap/MultitapProtocol.cpp

    # DEV9 (Audit Sec 2.4 — platform backends excluded, requires net/route.h/pcap)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/DEV9/DEV9.cpp
    # EXCLUDED: All DEV9 sub-files — require macOS net/route.h and pcap (not on iOS)

    # USB (Audit Sec 2.4 — platform backends excluded, depends on libusb/hidapi)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/USB/USB.cpp
    # EXCLUDED: All USB sub-files — require platform USB backend APIs (not on iOS)

    # Core management
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/SaveState.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/VMManager.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/Host.cpp

    # Common Library (cross-platform subset)
    ${CMAKE_SOURCE_DIR}/pcsx2/common/AlignedMalloc.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Assertions.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Console.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Error.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/FileSystem.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/HostSys.cpp
    # EXCLUDED: common/Image.cpp — requires libjpeg/libpng/libwebp
    # Non-critical for core emulation. Stub provides linker-safe no-ops.
    src/stubs/ImageStub.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/MD5Digest.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/MemoryInterface.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/MemorySettingsInterface.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Perf.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/ProgressCallback.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/ReadbackSpinManager.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/SettingsWrapper.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/SmallString.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/StringUtil.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/TextureDecompress.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Timer.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/WAVWriter.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/WindowInfo.cpp
    # EXCLUDED: common/YAML.cpp — requires rapidyaml (ryml), not in 3rdparty
    # Non-critical for core emulation (game DB, memcard folder).
    ${CMAKE_SOURCE_DIR}/pcsx2/common/DynamicLibrary.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Semaphore.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/FastJmp.cpp


    # iOS Platform (Audit Sec 12.2 — Phase 1-4)
    ios/platform/iOSVMManager.mm
    ios/platform/HostSys_iOS.mm
    ios/platform/CocoaTools.mm
    ios/platform/AudioStream_iOS.mm
    ios/platform/Filesystem_iOS.mm
    ios/platform/Threading_iOS.cpp
    ios/platform/PageFaultHandler.cpp

    # Metal Renderer (Audit Sec 4.1-4.3 — YELLOW)
    metal/MetalRenderer.mm
    metal/MetalDeviceInfo.mm
    metal/MetalTexture.mm
    metal/FrameSync.mm
)

# All dependencies use iOS native frameworks or 3rdparty source builds.
target_link_libraries(bionicsx2_core PUBLIC
    "-framework Foundation"
    "-framework UIKit"
    "-framework Metal"
    "-framework MetalKit"
    "-framework QuartzCore"
    "-framework AVFoundation"
    "-framework AudioToolbox"
    "-framework GameController"
    "-framework ImageIO"
    "-framework CoreFoundation"
    "-framework CoreGraphics"
    "-framework CoreVideo"
    "-framework CFNetwork"
    "-framework SystemConfiguration"
    "-lz"
)

# AUDIT REFERENCE: Section 10.2 — Compile options
target_compile_options(bionicsx2_core PRIVATE
    -fobjc-arc
    -fno-strict-aliasing
    -Wno-unknown-pragmas
)

# AUDIT REFERENCE: Fix 2 — Disable x86 recompiler + ffmpeg includes at preprocessor level
target_compile_definitions(bionicsx2_core PRIVATE
    DISABLE_PCSX2_RECOMPILER=1
    PCSX2_DISABLE_GSCAPTURE=1
    PCSX2_CORE=1
    __POSIX__=1
)

# AUDIT REFERENCE: Section 10.2 — Exclude source files
# EXCLUDED per audit (RED/N/A):
#   pcsx2-qt/           — Qt frontend (RED — Audit Sec 1.2)
#   GS/Renderers/Vulkan — Vulkan not used (N/A — Audit Sec 3.3)
#   GS/Renderers/DX11   — DirectX not used (N/A — Audit Sec 1.2)
#   GS/Renderers/DX12   — DirectX not used (N/A — Audit Sec 1.2)
#   x86/ recompiler     — Not ARM64 (N/A — Audit Sec 1.2)
#   CDVD/Darwin/        — Physical drive (RED — Audit Sec 2.6)
#   GS/GSCapture        — ffmpeg dependency (N/A — Audit Sec 2.4)
#   arm64/Vif_Dynarec   — nVif JIT disabled (N/A — Audit Sec 2.3-F, 13.7)

# AUDIT REFERENCE: Section 10.2 — Metal shader compilation (Xcode/iOS only)
if(CMAKE_GENERATOR MATCHES "Xcode")
    set(METAL_SHADERS metal/Shaders.metal)
    set_source_files_properties(${METAL_SHADERS} PROPERTIES LANGUAGE METAL)
    target_sources(bionicsx2_core PRIVATE ${METAL_SHADERS})
endif()

# AUDIT REFERENCE: Section 10.2 — Include paths
# src/ is the root for all PCSX2 quoted includes (#include "Common.h", etc.)
target_include_directories(bionicsx2_core PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/x86
    ${CMAKE_SOURCE_DIR}/metal
    ${CMAKE_SOURCE_DIR}/pcsx2
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/fast_float/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/fmt/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/ccc/src
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/imgui
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/imgui/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/vixl/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/lzma/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/cubeb/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/libchdr/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/soundtouch
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/cpuinfo/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/libzip
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/rcheevos/include
    ${CMAKE_SOURCE_DIR}/src/stubs
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/demangler/include
)

# AUDIT REFERENCE: Section 10.2 — Swift UI frontend target (EXCLUDE_FROM_ALL)
# Swift files require Xcode generator — not compiled with Ninja.
# The ObjC main.mm + AppDelegate.mm in the executable target provides the entry point.
add_library(bionicsx2_ui SHARED EXCLUDE_FROM_ALL
    ios/ui/BionicSX2App.swift
    ios/ui/ContentView.swift
    ios/ui/MetalViewController.swift
    ios/ui/GameControllerManager.swift
)
target_link_libraries(bionicsx2_ui PRIVATE bionicsx2_core)
set_target_properties(bionicsx2_ui PROPERTIES
    SWIFT_VERSION 5.0
)

# AUDIT REFERENCE: Section 10.2 — Main executable
add_executable(BionicSX2 MACOSX_BUNDLE
    ios/main.mm
    ios/ui/AppDelegate.mm
)
target_link_libraries(BionicSX2 PRIVATE bionicsx2_core)
set_target_properties(BionicSX2 PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/ios/Info.plist
    PRODUCT_BUNDLE_IDENTIFIER "com.bionicsx2.app"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
)

# Prevent linker from stripping PCSX2 core symbols.
# Without this, -dead_strip removes the entire 4.3 MB static lib
# since main.mm doesn't directly reference any PCSX2 symbol.
target_link_options(BionicSX2 PRIVATE
    -Wl,-all_load
)

# AUDIT REFERENCE: Section 10.2 — Copy entitlements (Xcode only)
if(CMAKE_GENERATOR MATCHES "Xcode")
    target_entitlements(BionicSX2
        ENTITLEMENTS ios/entitlements/BionicSX2.entitlements)
endif()
