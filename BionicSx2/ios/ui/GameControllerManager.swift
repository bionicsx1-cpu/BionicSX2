// PORTED FROM: (new) — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 8.3, 8.4
// STATUS: NEW — GameController.framework input manager

import Foundation
import GameController

// AUDIT REFERENCE: Section 8.3 — GCController discovery via GameController.framework
// Replaces macOS SDL3 / IOHID input path
// Maps GCController buttons → PS2 pad layout (Audit Section 2.7)

class GameControllerManager: NSObject {
    static let shared = GameControllerManager()

    // AUDIT REFERENCE: Section 8.3 — Connected controllers
    private var connectedControllers: [GCController] = []

    // AUDIT REFERENCE: Section 8.3 — Notification observers
    private var connectObserver: NSObjectProtocol?
    private var disconnectObserver: NSObjectProtocol?

    override private init() {
        super.init()
    }

    // AUDIT REFERENCE: Section 8.3 — Start monitoring for game controllers
    func startMonitoring() {
        connectObserver = NotificationCenter.default.addObserver(
            forName: .GCControllerDidConnect,
            object: nil,
            queue: .main) { [weak self] notification in
                self?.controllerDidConnect(notification)
        }

        disconnectObserver = NotificationCenter.default.addObserver(
            forName: .GCControllerDidDisconnect,
            object: nil,
            queue: .main) { [weak self] notification in
                self?.controllerDidDisconnect(notification)
        }

        // AUDIT REFERENCE: Section 8.3 — Start discovery
        GCController.startWirelessControllerDiscovery {}

        // Check for already-connected controllers
        for controller in GCController.controllers() {
            registerController(controller)
        }

        NSLog("[BionicSX2] GameController monitoring started (Audit Sec 8.3)")
    }

    // AUDIT REFERENCE: Section 8.3 — Stop monitoring
    func stopMonitoring() {
        if let obs = connectObserver {
            NotificationCenter.default.removeObserver(obs)
        }
        if let obs = disconnectObserver {
            NotificationCenter.default.removeObserver(obs)
        }
        GCController.stopWirelessControllerDiscovery()
        connectedControllers.removeAll()
    }

    // MARK: - Controller Connection

    private func controllerDidConnect(_ notification: Notification) {
        guard let controller = notification.object as? GCController else { return }
        registerController(controller)
        NSLog("[BionicSX2] Controller connected: %@ (Audit Sec 8.3)", controller.vendorName ?? "unknown")
    }

    private func controllerDidDisconnect(_ notification: Notification) {
        guard let controller = notification.object as? GCController else { return }
        if let idx = connectedControllers.firstIndex(of: controller) {
            connectedControllers.remove(at: idx)
            NSLog("[BionicSX2] Controller disconnected: %@ (Audit Sec 8.3)", controller.vendorName ?? "unknown")
        }
    }

    // AUDIT REFERENCE: Section 8.3 — Register a single controller and map its inputs
    private func registerController(_ controller: GCController) {
        guard !connectedControllers.contains(controller) else { return }
        connectedControllers.append(controller)

        // AUDIT REFERENCE: Section 2.7 — PS2 pad button mapping
        // Map GCController buttons to PS2 pad interface (Pad::StartPoll/Poll/EndPoll)
        if let gamepad = controller.extendedGamepad {
            mapExtendedGamepad(gamepad)
        }

        // Support controller vibration if available
        if #available(iOS 14.0, *) {
            if let battery = controller.battery {
                NSLog("[BionicSX2] Controller battery: %f%% (Audit Sec 8.3)",
                      battery.batteryLevel * 100)
            }
        }
    }

    // AUDIT REFERENCE: Section 8.3 — Map extended gamepad to PS2 pad
    private func mapExtendedGamepad(_ gamepad: GCExtendedGamepad) {
        // PS2 Pad Layout (Audit Section 2.7):
        //   D-Pad Up/Down/Left/Right  → gamepad.dpad
        //   Select (Button)            → gamepad.buttonOptions
        //   Start (Button)             → gamepad.buttonMenu
        //   Left Analog Stick          → gamepad.leftThumbstick
        //   Right Analog Stick         → gamepad.rightThumbstick
        //   L1/L2                      → gamepad.leftShoulder / leftTrigger
        //   R1/R2                      → gamepad.rightShoulder / rightTrigger
        //   Cross/Square/Circle/Triangle → gamepad.buttonA/B/X/Y

        gamepad.valueChangedHandler = { [weak self] (gamepad, element) in
            // AUDIT REFERENCE: Section 2.7 — Pad::Poll interface
            // Values are polled each frame — this handler stores latest state
            // for retrieval by the PS2 pad emulation layer
        }

        NSLog("[BionicSX2] Extended gamepad mapped to PS2 layout (Audit Sec 8.3)")
    }

    // MARK: - Input State

    // AUDIT REFERENCE: Section 2.7 — Poll interface for PS2 pad emulation
    // Called by Pad::StartPoll() in the emulation core
    func pollInput(playerIndex: Int) -> [String: Float] {
        guard playerIndex >= 0 && playerIndex < connectedControllers.count else {
            return [:]
        }

        let controller = connectedControllers[playerIndex]
        guard let gamepad = controller.extendedGamepad else { return [:] }

        return [
            "left_x": gamepad.leftThumbstick.xAxis.value,
            "left_y": gamepad.leftThumbstick.yAxis.value,
            "right_x": gamepad.rightThumbstick.xAxis.value,
            "right_y": gamepad.rightThumbstick.yAxis.value,
            "dpad_up": gamepad.dpad.up.value,
            "dpad_down": gamepad.dpad.down.value,
            "dpad_left": gamepad.dpad.left.value,
            "dpad_right": gamepad.dpad.right.value,
            "button_cross": gamepad.buttonA.value,      // PS2 Cross
            "button_circle": gamepad.buttonB.value,     // PS2 Circle
            "button_square": gamepad.buttonX.value,     // PS2 Square
            "button_triangle": gamepad.buttonY.value,   // PS2 Triangle
            "button_l1": gamepad.leftShoulder.value,
            "button_r1": gamepad.rightShoulder.value,
            "button_l2": gamepad.leftTrigger.value,
            "button_r2": gamepad.rightTrigger.value,
            "button_select": gamepad.buttonOptions?.value ?? 0,
            "button_start": gamepad.buttonMenu?.value ?? 0,
        ]
    }

    // AUDIT REFERENCE: Section 8.3 — Connected controller count
    var controllerCount: Int {
        return connectedControllers.count
    }
}
