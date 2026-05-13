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

    # GS Core (Audit Sec 2.4 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/GS.cpp
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
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/HW/GSTextureReplacementLoaders.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/HW/GSTextureReplacements.cpp

    # GS Renderer SW (Audit Sec 2.4 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSDrawScanline.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSDrawScanlineCodeGenerator.all.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSDrawScanlineCodeGenerator.arm64.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSRasterizer.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSRendererSW.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSSetupPrimCodeGenerator.all.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSSetupPrimCodeGenerator.arm64.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/SW/GSTextureCacheSW.cpp

    # GS Renderer Null (Audit Sec 2.4 — GREEN)
    ${CMAKE_SOURCE_DIR}/pcsx2/pcsx2/GS/Renderers/Null/GSRendererNull.cpp

    # Common Library (cross-platform subset)
    ${CMAKE_SOURCE_DIR}/pcsx2/common/AlignedMalloc.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Assertions.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Console.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Error.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/FileSystem.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/HostSys.cpp
    ${CMAKE_SOURCE_DIR}/pcsx2/common/Image.cpp
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
    ${CMAKE_SOURCE_DIR}/pcsx2/common/YAML.cpp

    # iOS Platform (Audit Sec 12.2 — Phase 1-4)
    ios/platform/iOSVMManager.mm
    ios/platform/HostSys_iOS.cpp
    ios/platform/CocoaTools.mm
    ios/platform/AudioStream_iOS.cpp
    ios/platform/Filesystem_iOS.cpp
    ios/platform/Threading_iOS.cpp
    ios/platform/PageFaultHandler.cpp

    # Metal Renderer (Audit Sec 4.1-4.3 — YELLOW)
    metal/MetalRenderer.mm
    metal/MetalDeviceInfo.mm
    metal/MetalTexture.mm
    metal/FrameSync.mm
)

# AUDIT REFERENCE: Section 10.2 — Find system packages
find_package(PNG REQUIRED)

# AUDIT REFERENCE: Section 10.2 — iOS frameworks
target_link_libraries(bionicsx2_core PUBLIC
    "-framework Metal"          # Audit Sec 3, 4
    "-framework MetalKit"       # Audit Sec 4.2
    "-framework UIKit"          # Audit Sec 4.3
    "-framework QuartzCore"     # Audit Sec 4.3 (CAMetalLayer)
    "-framework AVFoundation"   # Audit Sec 9.2
    "-framework GameController" # Audit Sec 8.3
    "-framework Foundation"     # Audit Sec 1.3
)

# AUDIT REFERENCE: Section 10.2 — Compile options
target_compile_options(bionicsx2_core PRIVATE
    -fobjc-arc
    -fno-strict-aliasing
    -Wno-unknown-pragmas
)

# AUDIT REFERENCE: Fix 2 — Disable x86 recompiler includes at preprocessor level
target_compile_definitions(bionicsx2_core PRIVATE
    DISABLE_PCSX2_RECOMPILER=1
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
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/xxhash
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/zlib
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/imgui
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/imgui/include
    ${CMAKE_SOURCE_DIR}/pcsx2/3rdparty/vixl/include
)

# AUDIT REFERENCE: Section 10.2 — Swift UI frontend target
add_library(bionicsx2_ui SHARED
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
add_executable(BionicSX2
    ios/Info.plist
)
target_link_libraries(BionicSX2 PRIVATE bionicsx2_ui bionicsx2_core)
set_target_properties(BionicSX2 PROPERTIES
    PRODUCT_BUNDLE_IDENTIFIER "com.bionicsx2.app"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
)

# AUDIT REFERENCE: Section 10.2 — Copy entitlements (Xcode only)
if(CMAKE_GENERATOR MATCHES "Xcode")
    target_entitlements(BionicSX2
        ENTITLEMENTS ios/entitlements/BionicSX2.entitlements)
endif()
