// iOS stub — Discord RPC not available on iOS
#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct DiscordRichPresence { const char* state; const char* details; int64_t startTimestamp; int64_t endTimestamp; const char* largeImageKey; const char* largeImageText; const char* smallImageKey; const char* smallImageText; const char* partyId; int partySize; int partyMax; const char* matchSecret; const char* joinSecret; const char* spectateSecret; int instance; } DiscordRichPresence;
static inline void Discord_Initialize(const char* a, void* b, void* c, const char* d, void* e) {}
static inline void Discord_Shutdown(void) {}
static inline void Discord_UpdatePresence(const DiscordRichPresence* p) {}
static inline void Discord_ClearPresence(void) {}
static inline void Discord_RunCallbacks(void) {}
#ifdef __cplusplus
}
#endif
