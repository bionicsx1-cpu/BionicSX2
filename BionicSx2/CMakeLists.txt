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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# AUDIT REFERENCE: Section 1.5 — Core emulator target
add_library(bionicsx2_core STATIC
    # EE Core (Audit Sec 2.1 — GREEN)
    src/R5900.cpp
    src/R5900OpcodeImpl.cpp
    src/R5900OpcodeTables.cpp
    src/Interpreter.cpp
    src/Memory.cpp
    src/MMI.cpp
    src/COP0.cpp
    src/COP2.cpp
    src/Counters.cpp
    src/Dmac.cpp
    src/FPU.cpp
    src/Gif.cpp
    src/Gif_Unit.cpp
    src/Hw.cpp
    src/HwRead.cpp
    src/HwWrite.cpp
    src/SPR.cpp
    src/Vif.cpp
    src/Vif_Codes.cpp
    src/Vif_Transfer.cpp
    src/Vif_Unpack.cpp
    src/Vif0_Dma.cpp
    src/Vif1_Dma.cpp
    src/Vif1_MFIFO.cpp
    src/vtlb.cpp

    # VU Units (Audit Sec 2.2 — GREEN, interpreter paths only)
    src/VU0.cpp
    src/VU0micro.cpp
    src/VU0microInterp.cpp
    src/VU1micro.cpp
    src/VU1microInterp.cpp
    src/VUmicro.cpp
    src/VUmicroMem.cpp
    src/VUflags.cpp
    src/VUops.cpp

    # IOP (Audit Sec 2.3 — GREEN)
    src/R3000A.cpp
    src/R3000AInterpreter.cpp
    src/R3000AOpcodeTables.cpp
    src/IopBios.cpp
    src/IopCounters.cpp
    src/IopDma.cpp
    src/IopGte.cpp
    src/IopHw.cpp
    src/IopMem.cpp
    src/IopIrq.cpp
    src/ps2/Iop/IopHwRead.cpp
    src/ps2/Iop/IopHwWrite.cpp
    src/ps2/Iop/PsxBios.cpp

    # GS Core (Audit Sec 2.4 — GREEN)
    src/GS/GS.cpp
    src/MTGS.cpp

    # SPU2 (Audit Sec 2.5 — GREEN)
    src/SPU2/spu2.cpp
    src/SPU2/spu2sys.cpp
    src/SPU2/spu2freeze.cpp
    src/SPU2/ADSR.cpp
    src/SPU2/Dma.cpp
    src/SPU2/Mixer.cpp
    src/SPU2/ReadInput.cpp
    src/SPU2/RegTable.cpp
    src/SPU2/Reverb.cpp
    src/SPU2/ReverbResample.cpp

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
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common
    ${CMAKE_CURRENT_SOURCE_DIR}/metal
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
