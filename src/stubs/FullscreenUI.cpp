// iOS stub — matches FullscreenUI.h signatures
#include <string>
#include "common/Pcsx2Defs.h"
struct Pcsx2Config;
namespace FullscreenUI {
    bool Initialize() { return false; }
    void Shutdown() {}
    void Render() {}
    bool IsInitialized() { return false; }
    void OpenPauseMenu() {}
    void GameChanged(std::string, std::string, std::string, u32, u32) {}
    void OnVMStarted() {}
    void OnVMDestroyed() {}
    void ReturnToMainWindow() {}
    void CheckForConfigChanges(const Pcsx2Config&) {}
    std::string TimeToPrintableString(time_t) { return {}; }
    void ReturnToPreviousWindow() {}
    bool IsAchievementsWindowOpen() { return false; }
    bool IsLeaderboardsWindowOpen() { return false; }
    void SetStandardSelectionFooterText(bool) {}
}
