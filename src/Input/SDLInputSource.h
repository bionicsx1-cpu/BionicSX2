// iOS stub — shadows pcsx2/pcsx2/Input/SDLInputSource.h
// SDL3 is not available on iOS. iOS uses GameController.framework.
#pragma once
#include <memory>
#include <string>
#include <vector>

class SettingsInterface;
struct WindowInfo;

class SDLInputSource {
public:
  SDLInputSource() {}
  virtual ~SDLInputSource() {}
  bool Initialize(const WindowInfo& wi) { return false; }
  void Reload() {}
  void PollEvents() {}
  int GetInputID(const std::string& key) { return -1; }
};
