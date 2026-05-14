// iOS stub — matches ImGuiFullscreen.h signatures
#include <string>
#include <utility>
#include "common/Pcsx2Defs.h"
struct ImFont;
namespace ImGuiFullscreen {
    ImFont* g_large_font = nullptr;
    ImFont* g_medium_font = nullptr;
    float g_layout_scale = 1.0f;
    float g_rcp_layout_scale = 1.0f;
    u32 UIPrimaryColor = 0;
    u32 UISecondaryColor = 0;
    u32 UIPrimaryDarkColor = 0;
    u32 UIPrimaryTextColor = 0;
    void SetTheme(bool) {}
    bool Initialize() { return true; }
    void Shutdown() {}
    void NewFrame() {}
    void Render() {}
    bool IsInitialized() { return false; }
    void OpenPauseMenu() {}
    bool BeginNavBar(float, float) { return false; }
    void EndMenuButtons() {}
    bool FloatingButton(const char*, float, float, float, float, float, float, bool, std::pair<ImFont*, float>, void*, bool) { return false; }
    void AddNotification(std::string, float, std::string, std::string, std::string) {}
}
