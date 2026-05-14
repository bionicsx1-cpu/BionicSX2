// iOS stub
#include <string>
namespace GSDumpReplayer {
  bool IsReplayingDump() { return false; }
  bool IsRunner() { return false; }
  void RenderUI() {}
  void Shutdown() {}
}
class GSDumpBase {
public:
  GSDumpBase(std::string fn) : m_filename(std::move(fn)) {}
  virtual ~GSDumpBase() {}
private:
  std::string m_filename;
};
