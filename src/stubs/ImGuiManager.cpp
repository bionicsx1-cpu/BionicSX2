// iOS stub — matches ImGuiManager.h signatures
#include <string>
#include <vector>
#include "common/Pcsx2Defs.h"
union InputBindingKey { uint64_t bits = 0; };
enum class GenericInputBinding : u8;
enum class InputLayout : u8;

namespace ImGuiManager {
    bool Initialize() { return true; }
    bool InitializeFullscreenUI() { return false; }
    void Shutdown(bool) {}
    void WindowResized() {}
    void RequestScaleUpdate() {}
    void ReloadFonts() {}
    void NewFrame() {}
    void SkipFrame() {}
    void RenderOSD() {}
    float GetGlobalScale() { return 1.0f; }
    bool HasSoftwareCursor(u32) { return false; }
    bool ProcessHostKeyEvent(InputBindingKey, float) { return false; }
    void UpdateMousePosition(float, float) {}
    bool ProcessPointerButtonEvent(InputBindingKey, float) { return false; }
    bool ProcessPointerAxisEvent(InputBindingKey, float) { return false; }
    bool ProcessGenericInputEvent(GenericInputBinding, InputLayout, float) { return false; }
    void AddTextInput(std::string) {}
    bool WantsTextInput() { return false; }
    bool WantsMouseInput() { return false; }
    float GetWindowWidth() { return 0.0f; }
    float GetWindowHeight() { return 0.0f; }
    void SetSoftwareCursor(u32, std::string, float, u32) {}
    void ClearSoftwareCursor(u32) {}
    void SetSoftwareCursorPosition(u32, float, float) {}
    std::string StripIconCharacters(std::string_view s) { return std::string(s); }
}
