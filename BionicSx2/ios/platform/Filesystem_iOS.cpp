// PORTED FROM: (new) — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 6.4, 10.3
// STATUS: NEW — iOS sandbox-aware path management

#import <Foundation/Foundation.h>

#include <string>
#include <cstdlib>

// Audit Section 6.4: All paths resolved via NSSearchPathForDirectoriesInDomains
// No hardcoded absolute paths — iOS sandbox requires dynamic resolution

// Audit Section 6.4: Get app documents directory (user-visible via iTunes File Sharing)
static std::string GetDocumentsDir(void)
{
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString* docsDir = [paths firstObject];
    if (!docsDir) return std::string();
    return std::string([docsDir UTF8String]);
}

// Audit Section 6.4: Get app caches directory (not backed up, purged under pressure)
static std::string GetCachesDir(void)
{
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString* cachesDir = [paths firstObject];
    if (!cachesDir) return std::string();
    return std::string([cachesDir UTF8String]);
}

// Audit Section 10.3: BIOS directory under Documents/BIOS/
// User places BIOS files here via iTunes File Sharing
std::string GetBIOSPath(void)
{
    std::string path = GetDocumentsDir() + "/BIOS";
    // Create directory if needed
    NSString* nsPath = [NSString stringWithUTF8String:path.c_str()];
    NSError* error = nil;
    [[NSFileManager defaultManager] createDirectoryAtPath:nsPath
                              withIntermediateDirectories:YES
                                               attributes:nil
                                                    error:&error];
    if (error)
    {
        NSLog(@"[BionicSX2] Failed to create BIOS directory: %@ (Audit Sec 10.3)", error.localizedDescription);
    }
    return path;
}

// Audit Section 2.6: ISO/CHD game files under Documents/Games/
// iOS uses file-based game loading only (no optical drive — RED per Audit Sec 2.6)
std::string GetGamesPath(void)
{
    std::string path = GetDocumentsDir() + "/Games";
    NSString* nsPath = [NSString stringWithUTF8String:path.c_str()];
    NSError* error = nil;
    [[NSFileManager defaultManager] createDirectoryAtPath:nsPath
                              withIntermediateDirectories:YES
                                               attributes:nil
                                                    error:&error];
    if (error)
    {
        NSLog(@"[BionicSX2] Failed to create Games directory: %@ (Audit Sec 2.6)", error.localizedDescription);
    }
    return path;
}

// Audit Section 10.3: Memory card saves under Documents/Memcards/
std::string GetMemcardPath(void)
{
    std::string path = GetDocumentsDir() + "/Memcards";
    NSString* nsPath = [NSString stringWithUTF8String:path.c_str()];
    NSError* error = nil;
    [[NSFileManager defaultManager] createDirectoryAtPath:nsPath
                              withIntermediateDirectories:YES
                                               attributes:nil
                                                    error:&error];
    if (error)
    {
        NSLog(@"[BionicSX2] Failed to create Memcards directory: %@ (Audit Sec 10.3)", error.localizedDescription);
    }
    return path;
}

// Audit Section 6.4: App data directory (cache)
std::string GetAppDataPath(void)
{
    return GetCachesDir();
}

// Audit Section 6.4: Save states directory
std::string GetSavestatePath(void)
{
    std::string path = GetDocumentsDir() + "/Savestates";
    NSString* nsPath = [NSString stringWithUTF8String:path.c_str()];
    NSError* error = nil;
    [[NSFileManager defaultManager] createDirectoryAtPath:nsPath
                              withIntermediateDirectories:YES
                                               attributes:nil
                                                    error:&error];
    if (error)
    {
        NSLog(@"[BionicSX2] Failed to create Savestates directory: %@ (Audit Sec 6.4)", error.localizedDescription);
    }
    return path;
}

// Audit Section 6.4: Shader cache directory (caches, can be purged)
std::string GetShaderCachePath(void)
{
    return GetCachesDir() + "/ShaderCache";
}
