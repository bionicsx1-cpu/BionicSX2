#pragma once
// iOS stub — shadows pcsx2/pcsx2/Input/SDLInputSource.h
// SDL3 not available on iOS. iOS uses GameController.framework.
#include "Input/InputSource.h"

class SDLInputSource final : public InputSource {
public:
  SDLInputSource() = default;
  ~SDLInputSource() override = default;

  bool Initialize(SettingsInterface& si,
    std::unique_lock<std::mutex>& settings_lock) override
  { return false; }

  void UpdateSettings(SettingsInterface& si,
    std::unique_lock<std::mutex>& settings_lock) override {}

  bool ReloadDevices() override { return false; }
  void Shutdown() override {}
  bool IsInitialized() override { return false; }
  void PollEvents() override {}

  std::optional<InputBindingKey> ParseKeyString(
    const std::string_view device,
    const std::string_view binding) override
  { return std::nullopt; }

  TinyString ConvertKeyToString(InputBindingKey key,
    bool display = false, bool migration = false) override
  { return {}; }

  TinyString ConvertKeyToIcon(InputBindingKey key) override
  { return {}; }

  std::vector<std::pair<std::string, std::string>>
    EnumerateDevices() override
  { return {}; }

  std::vector<InputBindingKey> EnumerateMotors() override
  { return {}; }

  bool GetGenericBindingMapping(
    const std::string_view device,
    InputManager::GenericInputBindingMapping* mapping) override
  { return false; }

  InputLayout GetControllerLayout(u32 index) override
  { return {}; }

  void UpdateMotorState(InputBindingKey key, float intensity) override {}
  void UpdateMotorState(InputBindingKey large,
    InputBindingKey small,
    float large_intensity,
    float small_intensity) override {}

  static void ResetRGBForAllPlayers(SettingsInterface& si) {}
};
