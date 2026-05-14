// iOS stub
#include <string>
namespace FullscreenUI {
  bool Initialize() { return false; }
  void Shutdown() {}
  void Render() {}
  bool IsInitialized() { return false; }
  void OpenPauseMenu() {}
  void GameChanged(std::string path, std::string serial,
    std::string title, std::string region, float crc) {}
}
