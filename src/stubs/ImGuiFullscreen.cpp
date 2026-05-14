// iOS stub — matches ImGuiFullscreen.h signatures
#include <string>
#include <utility>
#include <span>
#include "common/Pcsx2Defs.h"
#include "imgui.h"
struct ImFont;
class GSTexture;
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
    void SetNotificationPosition(float, float, float) {}
    bool MenuButtonFrame(const char*, bool, float, bool*, bool*, ImVec2*, ImVec2*, bool) { return false; }
    bool MenuHeadingButton(const char*, const char*, bool, bool) { return false; }
    bool BeginFullscreenWindow(float, float, float, float, const char*, float, ImVec4*, float) { return false; }
    bool BeginFullscreenWindow(const ImVec2&, const ImVec2&, const char*, float, ImVec4*, float) { return false; }
    void EndFullscreenWindow() {}
    void BeginMenuButtons(u32, float, float, float, float) {}
    bool NavTab(const char*, bool, bool, float, float, const ImVec4&, bool) { return false; }
    GSTexture* GetCachedTextureAsync(std::string_view) { return nullptr; }
    bool InvalidateCachedTexture(const std::string&) { return false; }
    bool IsGamepadInputSource() { return false; }
    int GetGamepadGlyphs() { return 0; }
    bool WantsToCloseMenu() { return false; }
    void OpenProgressDialog(const char*, std::string, s32, s32, s32) {}
    void CloseProgressDialog(const char*) {}
    void RenderTextClippedWithShadow(const ImVec2&, const ImVec2&, const char*, const char*, const ImVec2*, const ImVec4*, float) {}
    void SetFullscreenFooterText(std::string_view) {}
    void ResetMenuButtonFrame() {}
    void DrawMenuButtonFrame(const ImVec2&, const ImVec2&, ImU32, bool, float) {}
    void GetMenuButtonFrameBounds(float, ImVec2*, ImVec2*) {}
}
