// iOS stub
#include <string>
namespace SaveStateSelectorUI {
  void Open(int open_for_slot) {}
  void Close() {}
  void RefreshList() {}
  void Draw() {}
  bool IsOpen() { return false; }
  void Clear() {}
  void FileSaveStateCompleted(const std::string& path, bool was_error) {}
}
