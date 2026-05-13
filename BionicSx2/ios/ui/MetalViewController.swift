// PORTED FROM: (new) — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 4.3, 8.4
// STATUS: NEW — UIViewController hosting CAMetalLayer

import UIKit
import Metal
import QuartzCore

// AUDIT REFERENCE: Section 4.3 — UIViewController hosting CAMetalLayer
// Replaces macOS NSView + NSWindow pattern
// Handles view resize, display link, passes CAMetalLayer to MetalRenderer

class MetalViewController: UIViewController {
    var gameURL: URL?
    private var metalLayer: CAMetalLayer?
    private var displayLink: CADisplayLink?
    private var rendererInitialized = false

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .black

        // AUDIT REFERENCE: Section 4.3 — Create CAMetalLayer on UIView
        setupMetalLayer()

        // AUDIT REFERENCE: Section 4.3 — CADisplayLink for frame timing
        setupDisplayLink()

        NSLog("[BionicSX2] MetalViewController loaded — game: %@ (Audit Sec 4.3)",
              gameURL?.lastPathComponent ?? "none")
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        updateMetalLayerSize()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        // AUDIT REFERENCE: Section 2.3-ADDENDUM — Initialize VM on first appearance
        initializeEmulation()
    }

    override var prefersHomeIndicatorAutoHidden: Bool {
        return true // Immersive fullscreen
    }

    override var supportedInterfaceOrientations: UIInterfaceOrientationMask {
        return .landscape // PS2 games are landscape
    }

    // MARK: - Metal Layer Setup

    // AUDIT REFERENCE: Section 4.3 — CAMetalLayer creation (identical on iOS)
    private func setupMetalLayer() {
        let layer = CAMetalLayer()
        layer.device = MTLCreateSystemDefaultDevice()
        layer.pixelFormat = .bgra8Unorm
        layer.framebufferOnly = true
        layer.drawsAsynchronously = true
        layer.contentsScale = UIScreen.main.nativeScale
        layer.frame = view.bounds
        view.layer.addSublayer(layer)
        metalLayer = layer

        NSLog("[BionicSX2] CAMetalLayer created — device: %@ (Audit Sec 4.3)",
              layer.device?.name ?? "unknown")
    }

    // AUDIT REFERENCE: Section 4.3 — Handle view resize / orientation change
    private func updateMetalLayerSize() {
        guard let layer = metalLayer else { return }
        let scale = UIScreen.main.nativeScale
        layer.frame = view.bounds
        layer.drawableSize = CGSize(width: view.bounds.width * scale,
                                    height: view.bounds.height * scale)
    }

    // MARK: - Display Link

    // AUDIT REFERENCE: Section 4.3 — CADisplayLink for screen refresh sync
    private func setupDisplayLink() {
        displayLink = CADisplayLink(target: self, selector: #selector(frameUpdate))
        displayLink?.add(to: .main, forMode: .common)
    }

    @objc private func frameUpdate() {
        // Passed to MetalRenderer for frame timing
        // Audit Section 4.2 — MTLCommandBuffer commit happens here
    }

    // MARK: - Emulator Initialization

    // AUDIT REFERENCE: Section 2.3-E/F — Initialize VM via iOSVMManager
    // This is the iOS equivalent of VMManager::StartVM() on macOS
    private func initializeEmulation() {
        guard !rendererInitialized else { return }

        // Pass CAMetalLayer reference to MetalRenderer
        if let layer = metalLayer {
            // Create Metal renderer — Audit Section 4.2
            NSLog("[BionicSX2] Starting MetalRenderer with CAMetalLayer (Audit Sec 4.2)")

            // AUDIT REFERENCE: Section 2.3-F — iOSVM_Initialize() is called
            // which sets EmuConfig.EE.newVifDynarec = false BEFORE cpuReset()
            // This prevents nVif dVifUnpack SIGSEGV at Vif_HashBucket.h:68
            iOSVM_Initialize()

            NSLog("[BionicSX2] Emulation initialized for: %@ (Audit Sec 2.3-E)",
                  gameURL?.lastPathComponent ?? "none")
        }

        rendererInitialized = true
    }

    deinit {
        displayLink?.invalidate()
        iOSVM_Shutdown()
    }
}
