// iOS stub
#include <string>
namespace ImGuiManager {
  bool Initialize(float scale, bool fullscreen_ui) { return true; }
  void Shutdown() {}
  void NewFrame() {}
  void RenderOSD() {}
  void SkipFrame() {}
  void WindowResized(float width, float height) {}
  void RequestScaleUpdate() {}
  void ReloadFonts() {}
  void SetShowOSDMessages(bool show) {}
  float GetGlobalScale() { return 1.0f; }
}
