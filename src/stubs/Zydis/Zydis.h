// ARM64 iOS stub — Zydis is x86-only disassembler
#pragma once
typedef unsigned int ZyanU32;
typedef unsigned long long ZyanU64;
typedef struct { int unused; } ZydisDecoder;
typedef struct { int unused; } ZydisFormatter;
typedef struct { int unused; } ZydisDecodedInstruction;
typedef struct { int unused; } ZydisDecodedOperand;
static inline int ZydisDecoderInit(...) { return 0; }
static inline int ZydisDecoderDecodeFull(...) { return 0; }
static inline int ZydisFormatterInit(...) { return 0; }
static inline int ZydisFormatterFormatInstruction(...) { return 0; }
