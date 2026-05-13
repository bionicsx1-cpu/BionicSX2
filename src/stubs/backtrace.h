// iOS stub — backtrace not available on iOS
#pragma once
static inline int backtrace(void** buffer, int size) { return 0; }
static inline char** backtrace_symbols(void* const* buffer, int size) { return nullptr; }
static inline void backtrace_symbols_fd(void* const* buffer, int size, int fd) {}
