// ARM64 iOS stub — xbyak is x86-only
#pragma once
#include <cstdint>
namespace Xbyak {
    struct Operand {};
    struct Address : Operand {};
    struct Label {};
    struct Reg {};
    struct Xmm : Operand {};
    struct Ymm : Operand {};
    struct Zmm : Operand {};
    struct Reg32 : Operand {};
    struct Reg64 : Operand {};
    struct CodeGenerator {
        void ready() {}
        const uint8_t* getCode() const { return nullptr; }
        size_t getSize() const { return 0; }
    };
}
