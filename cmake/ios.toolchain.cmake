# PORTED FROM: (new) — BionicSX2 iOS Port
# AUDIT REFERENCE: Sections 10.2, 13.5
# STATUS: NEW — iOS cross-compilation toolchain configuration

# AUDIT REFERENCE: Section 13.5 — iOS system name and architecture
set(CMAKE_SYSTEM_NAME iOS)
set(CMAKE_SYSTEM_VERSION 15.0)
set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_OSX_DEPLOYMENT_TARGET 15.0)
# Force target triple via flags — CMAKE_C_COMPILER_TARGET is ignored by Ninja generator
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target arm64-apple-ios15.0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target arm64-apple-ios15.0")
execute_process(
    COMMAND xcrun --sdk iphoneos --show-sdk-path
    OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# AUDIT REFERENCE: Section 10.2 — Metal compiler flags for .metal → .metallib
set(CMAKE_METAL_COMPILER xcrun -sdk iphoneos metal)
set(CMAKE_METAL_COMPILER_FLAGS -std=ios-metal2.3)
set(CMAKE_METALLIB_COMPILER xcrun -sdk iphoneos metallib)

# AUDIT REFERENCE: Section 10.2 — Disable simulator builds
set(CMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH YES)
set(CMAKE_XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2") # iPhone + iPad

# AUDIT REFERENCE: Section 10.2 — Code signing (unsigned for dev builds)
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO")
set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "")

# AUDIT REFERENCE: Section 10.2 — C++ standard library
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_MODULES "YES")

# AUDIT REFERENCE: Section 10.2 — Objective-C++ configuration
set(CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC "YES")
set(CMAKE_XCODE_ATTRIBUTE_GCC_ENABLE_OBJC_EXCEPTIONS "YES")

# AUDIT REFERENCE: Section 10.2 — Metal shader compilation in Xcode
set(CMAKE_XCODE_ATTRIBUTE_MTL_ENABLE_DEBUG_INFO "NO")
set(CMAKE_XCODE_ATTRIBUTE_MTL_FAST_MATH "YES")

# Find required Apple frameworks
find_library(UIKIT_LIBRARY UIKit)
find_library(METAL_LIBRARY Metal)
find_library(METALKIT_LIBRARY MetalKit)
find_library(QUARTZCORE_LIBRARY QuartzCore)
find_library(AVFOUNDATION_LIBRARY AVFoundation)
find_library(GAMECONTROLLER_LIBRARY GameController)
find_library(FOUNDATION_LIBRARY Foundation)
