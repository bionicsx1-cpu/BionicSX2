# PORTED FROM: (new) — BionicSX2 iOS Port
# AUDIT REFERENCE: Sections 10.2, 13.5
# STATUS: NEW — iOS cross-compilation toolchain configuration
#
# NOTE: CMAKE_SYSTEM_NAME, CMAKE_OSX_SYSROOT, and compiler target are
# passed via -D flags in build-ipa.yml workflow (resolved via xcrun).
# This file exists only for local reference — do not set sysroot/target
# here as toolchain files execute before compiler initialization.

set(CMAKE_SYSTEM_NAME iOS)
set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_OSX_DEPLOYMENT_TARGET 15.0)
set(CMAKE_CXX_STANDARD 20)
