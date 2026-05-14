// iOS stub — shadows pcsx2/pcsx2/Input/SDLInputSource.h
// SDL3 not available on iOS. iOS uses GameController.framework.
#pragma once
#include <memory>
#include <mutex>
#include <string>
#include <vector>

class SettingsInterface;
enum class InputSourceType : unsigned int;

class SDLInputSource {
public:
  SDLInputSource() {}
  ~SDLInputSource() {}
  bool Initialize(SettingsInterface& si, std::unique_lock<std::mutex>& settings_lock) { return false; }
  void UpdateSettings(SettingsInterface& si, std::unique_lock<std::mutex>& settings_lock) {}
  bool ReloadDevices() { return false; }
  void Shutdown() {}
  bool IsInitialized() { return false; }
  static void ResetRGBForAllPlayers(SettingsInterface& si) {}
};
