// iOS stub — rapidyaml not available
// YAML parsing non-critical for core emulation
#pragma once
#include <string>
#include <string_view>
namespace ryml {
    using csubstr = std::string_view;
    struct NodeRef { bool valid() const { return false; } };
    struct ConstNodeRef { bool valid() const { return false; } };
    struct Tree {
        ConstNodeRef rootref() const { return {}; }
        NodeRef rootref() { return {}; }
    };
    inline Tree parse_in_arena(std::string_view) { return {}; }
    inline Tree parse_in_place(std::string&) { return {}; }
}
namespace c4 {
    namespace yml = ryml;
}
