// iOS stub
#include <string>
class InputRecording {
public:
  void RecordingLoadSaveState() {}
  void GoToFirstFrame(bool is_loading) {}
  bool IsActive() const { return false; }
  void Init() {}
  bool IsReplaying() const { return false; }
  void processWithUpdate(int pad_data) {}
};
InputRecording g_InputRecording;

namespace InputRecordingControls {
  void Record() {}
  void Stop() {}
  void TogglePause() {}
}
