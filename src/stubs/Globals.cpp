// iOS stub — global variables required by PCSX2 core
#include <string>

bool AllowParams1    = false;
bool AllowParams2    = false;
bool ParamsRead      = false;
bool NoOSD           = false;
bool ConsoleLogging  = false;
bool TraceLogging    = false;
bool EnableFMV       = true;
bool FMVstarted      = false;

std::string BiosPath;
std::string BiosSerial;
std::string BiosVersion;
std::string BiosZone;
int BiosRegion = 0;

// Missing globals reported by linker
int _Cores = 1;
void* _CurrentBiosInformation = nullptr;
void* _GImGui = nullptr;
void* _GSDumpReplayerCpu = nullptr;
void* _R3000SymbolGuardian = nullptr;
void* _R5900SymbolImporter = nullptr;
void* _ReverbDownsample = nullptr;
void* _ReverbUpsample = nullptr;
void* _Spdif = nullptr;

// CPU/misc stubs
#include <string>
std::string GetCPUInfo() { return "Apple ARM64"; }
void detectCPUextensions() {}
std::string GetOSVersionString() { return "iOS 15.0"; }
void GetValidDrive(std::string& drive) { drive.clear(); }

// Device registration
namespace RegisterDevice {
  void Register() {}
  void Unregister() {}
}

// AudioStream backend stubs
#include <memory>
#include <vector>
#include <string>
#include <utility>
class AudioStream;
using AudioStreamCallback = void(*)(void*, float*, unsigned int);
std::unique_ptr<AudioStream> AudioStream_CreateCubeb(
    unsigned int sr, unsigned int ch, unsigned int bms,
    unsigned int lms, AudioStreamCallback cb, void* ud)
{ return nullptr; }
std::unique_ptr<AudioStream> AudioStream_CreateSDL(
    unsigned int sr, unsigned int ch, unsigned int bms,
    unsigned int lms, AudioStreamCallback cb, void* ud)
{ return nullptr; }
std::vector<std::pair<std::string,std::string>> AudioStream_GetCubebDrivers()
{ return {}; }
std::vector<std::pair<std::string,std::string>> AudioStream_GetCubebDevices(const char* d)
{ return {}; }

// Input conversion stubs
namespace InputManager {
  int ConvertHostKeyboardStringToCode(const std::string& str) { return 0; }
  std::string ConvertHostKeyboardCodeToString(int code) { return {}; }
  std::string ConvertHostKeyboardCodeToIcon(int code) { return {}; }
}
