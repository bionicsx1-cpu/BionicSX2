#pragma once
// iOS stub — Discord RPC not available on iOS
typedef struct { void* unused; } DiscordEventHandlers;
typedef struct { void* unused; } DiscordRichPresence;
static inline void Discord_Initialize(const char*, DiscordEventHandlers*, int, const char*) {}
static inline void Discord_Shutdown() {}
static inline void Discord_UpdatePresence(const DiscordRichPresence*) {}
static inline void Discord_RunCallbacks() {}
static inline void Discord_ClearPresence() {}
