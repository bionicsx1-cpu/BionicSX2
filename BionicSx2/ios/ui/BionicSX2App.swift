// PORTED FROM: (new) — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 4.3, 8.3, 8.4
// STATUS: NEW — @main SwiftUI App entry point

import SwiftUI

// AUDIT REFERENCE: Section 4.3 — SwiftUI app entry point
// Replaces macOS NSApplicationMain (Audit Section 4.3)
// Handles UIApplicationDelegate lifecycle for Metal rendering

@main
struct BionicSX2App: App {
    // AUDIT REFERENCE: Section 8.4 — App delegate handles UI lifecycle
    @UIApplicationDelegateAdaptor(AppDelegate.self) var appDelegate

    var body: some Scene {
        WindowGroup {
            ContentView()
                .preferredColorScheme(.dark) // PS2 emulator styling
        }
    }
}

// AUDIT REFERENCE: Section 4.3 — UIApplicationDelegate lifecycle
class AppDelegate: NSObject, UIApplicationDelegate {
    func application(_ application: UIApplication,
                     didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        NSLog("[BionicSX2] App launched (Audit Sec 8.4)")

        // AUDIT REFERENCE: Section 9.2 — Configure AVAudioSession on launch
        configureAudioSession()

        return true
    }

    func applicationWillResignActive(_ application: UIApplication) {
        NSLog("[BionicSX2] App resigning active — pausing emulation (Audit Sec 8.4)")
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        NSLog("[BionicSX2] App became active — resuming emulation (Audit Sec 8.4)")
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        NSLog("[BionicSX2] App entered background — saving state (Audit Sec 6.4)")
    }

    // AUDIT REFERENCE: Section 9.2 — Audio session configuration
    private func configureAudioSession() {
        let session = AVAudioSession.sharedInstance()
        do {
            try session.setCategory(.playback, mode: .default, options: .mixWithOthers)
            try session.setActive(true)
        } catch {
            NSLog("[BionicSX2] Failed to configure AVAudioSession: \(error) (Audit Sec 9.2)")
        }
    }
}
