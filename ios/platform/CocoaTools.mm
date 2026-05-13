// PORTED FROM: common/CocoaTools.mm — BionicSX2 iOS Port
// AUDIT REFERENCE: Section 4.3
// STATUS: YELLOW — NSView→UIView, NSWindow→UIWindow, CAMetalLayer unchanged

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
// PORTED: AppKit removed, UIKit added (Audit Section 4.3)
// CAMetalLayer is portable — no changes needed (Audit Section 4.3)

#include <string>
#include <optional>

struct WindowInfo;

namespace CocoaTools
{

// PORTED: NSView → UIView (Audit Section 4.3)
bool CreateMetalLayer(WindowInfo* wi)
{
    // UIView hosting CAMetalLayer — identical to NSView pattern
    // CAMetalLayer is fully portable per Audit Section 4.3
    UIView* view = (__bridge UIView*)wi->window_handle;
    if (!view)
    {
        NSLog(@"[BionicSX2] CreateMetalLayer: no UIView handle (Audit Sec 4.3)");
        return false;
    }

    CAMetalLayer* layer = [CAMetalLayer layer];
    // PORTED: CAMetalLayer usage identical on iOS (Audit Section 4.3)
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    layer.framebufferOnly = YES;
    layer.drawsAsynchronously = YES;

    CGFloat scale = [UIScreen mainScreen].nativeScale;
    layer.contentsScale = scale;
    layer.frame = view.bounds;

    [view.layer addSublayer:layer];
    wi->surface_handle = (__bridge void*)layer;
    wi->surface_scale = scale;

    return true;
}

// PORTED: NSView → UIView (Audit Section 4.3)
void DestroyMetalLayer(WindowInfo* wi)
{
    if (wi->surface_handle)
    {
        CAMetalLayer* layer = (__bridge CAMetalLayer*)wi->surface_handle;
        [layer removeFromSuperlayer];
        wi->surface_handle = nullptr;
    }
}

// PORTED: NSView refresh rate → UIScreen (Audit Section 4.3)
std::optional<float> GetViewRefreshRate(const WindowInfo& wi)
{
    // iOS: UIScreen.maximumFramesPerSecond maps to refresh rate
    float maxFPS = (float)[UIScreen mainScreen].maximumFramesPerSecond;
    if (maxFPS > 0)
        return maxFPS;
    return 60.0f; // Default fallback
}

// PORTED: NSMenu → no iOS equivalent (Audit Section 4.3)
void MarkHelpMenu(void* menu)
{
    // No-op — NSMenu does not exist on iOS (Audit Section 4.3)
}

// PORTED: NSBundle path resolution works identically on iOS (Audit Section 1.3)
std::optional<std::string> GetBundlePath()
{
    NSString* path = [[NSBundle mainBundle] bundlePath];
    if (path)
        return std::string([path UTF8String]);
    return std::nullopt;
}

// PORTED: NSBundle resource path (Audit Section 1.3)
std::optional<std::string> GetResourcePath()
{
    NSString* path = [[NSBundle mainBundle] resourcePath];
    if (path)
        return std::string([path UTF8String]);
    return std::nullopt;
}

// PORTED: NSWorkspace → UIDocumentInteractionController (Audit Section 4.3)
bool ShowInFinder(std::string_view file)
{
    // iOS equivalent: UIDocumentInteractionController
    NSString* nsPath = [NSString stringWithUTF8String:file.data()];
    NSURL* url = [NSURL fileURLWithPath:nsPath];
    // Presenting a document controller requires a UIViewController context
    // This is a no-op in the platform layer — caller must present via UI
    NSLog(@"[BionicSX2] ShowInFinder requested for: %s (delegated to UI layer — Audit Sec 4.3)", file.data());
    (void)url;
    return true;
}

// PORTED: CreateWindow → UIWindow/UIViewController (Audit Section 4.3)
void* CreateWindow(std::string_view title, uint32_t width, uint32_t height)
{
    // iOS: windows are managed via UIWindowScene — create container view
    UIViewController* vc = [[UIViewController alloc] init];
    vc.view.frame = CGRectMake(0, 0, width, height);
    vc.view.backgroundColor = [UIColor blackColor];
    return (__bridge_retained void*)vc;
}

// PORTED: NSView destroy → UIViewController (Audit Section 4.3)
void DestroyWindow(void* window)
{
    if (window)
    {
        UIViewController* vc = (__bridge_transfer UIViewController*)window;
        vc = nil;
    }
}

// PORTED: WindowInfo → UIView (Audit Section 4.3)
void GetWindowInfoFromWindow(WindowInfo* wi, void* window)
{
    if (!wi || !window) return;
    UIViewController* vc = (__bridge UIViewController*)window;
    wi->window_handle = (__bridge void*)vc.view;
    wi->surface_width = (u32)vc.view.bounds.size.width;
    wi->surface_height = (u32)vc.view.bounds.size.height;
    wi->surface_scale = [UIScreen mainScreen].nativeScale;
}

// PORTED: CFRunLoop (Audit Section 4.3)
void RunCocoaEventLoop(bool wait_forever)
{
    // iOS: standard CFRunLoop is the main run loop
    // UIApplicationMain handles this — only call for secondary contexts
    CFRunLoopRunResult result = CFRunLoopRunInMode(
        kCFRunLoopDefaultMode,
        wait_forever ? 60.0 : 0.0,
        false);
    if (result == kCFRunLoopRunTimedOut && wait_forever)
    {
        // Re-invoke to keep running
        RunCocoaEventLoop(true);
    }
}

// PORTED: CFRunLoop stop (Audit Section 4.3)
void StopMainThreadEventLoop()
{
    CFRunLoopStop(CFRunLoopGetMain());
}

// PORTED: No Finder/Trash on iOS — stub (Audit Section 4.3)
std::optional<std::string> MoveToTrash(std::string_view file)
{
    NSLog(@"[BionicSX2] MoveToTrash: %s — no Finder on iOS, delete manually (Audit Sec 4.3)", file.data());
    return std::nullopt;
}

// PORTED: No relaunch mechanism on iOS — stub (Audit Section 4.3)
bool DelayedLaunch(std::string_view file)
{
    NSLog(@"[BionicSX2] DelayedLaunch: %s — not supported on iOS (Audit Sec 4.3)", file.data());
    return false;
}

} // namespace CocoaTools
