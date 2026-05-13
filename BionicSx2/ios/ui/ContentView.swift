// PORTED FROM: (new) — BionicSX2 iOS Port
// AUDIT REFERENCE: Sections 2.6, 8.4
// STATUS: NEW — Main UI with game list browser

import SwiftUI
import UniformTypeIdentifiers

// AUDIT REFERENCE: Section 8.4 — Main user interface
// Game list browser followed by MetalViewController on game selection
// File picker for ISO/CHD selection from Documents/Games/
// Audit Section 2.6: iOS uses file-based game loading only (no optical drive)

struct ContentView: View {
    @State private var games: [URL] = []
    @State private var selectedGame: URL? = nil
    @State private var showFilePicker = false
    @State private var showEmulator = false

    var body: some View {
        NavigationStack {
            List {
                if games.isEmpty {
                    VStack(spacing: 20) {
                        Image(systemName: "gamecontroller")
                            .font(.system(size: 60))
                            .foregroundColor(.gray)
                        Text("No Games Found")
                            .font(.title2)
                        Text("Add PS2 ROMs (.iso, .chd, .cso) to Documents/Games/")
                            .font(.subheadline)
                            .foregroundColor(.secondary)
                            .multilineTextAlignment(.center)
                        Button("Browse Files") {
                            showFilePicker = true
                        }
                        .buttonStyle(.borderedProminent)
                    }
                    .frame(maxWidth: .infinity)
                    .padding()
                } else {
                    ForEach(games, id: \.self) { game in
                        Button(action: {
                            selectedGame = game
                            showEmulator = true
                        }) {
                            HStack {
                                Image(systemName: "opticaldisc")
                                    .foregroundColor(.accentColor)
                                Text(game.lastPathComponent)
                                    .lineLimit(1)
                                Spacer()
                                Image(systemName: "chevron.right")
                                    .font(.caption)
                                    .foregroundColor(.secondary)
                            }
                        }
                    }
                    .onDelete { indexSet in
                        games.remove(atOffsets: indexSet)
                    }
                }
            }
            .navigationTitle("BionicSX2")
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button(action: { showFilePicker = true }) {
                        Image(systemName: "plus")
                    }
                }
            }
            .sheet(isPresented: $showFilePicker) {
                FilePickerView { url in
                    if !games.contains(url) {
                        games.append(url)
                    }
                    showFilePicker = false
                }
            }
            .fullScreenCover(isPresented: $showEmulator) {
                if let game = selectedGame {
                    MetalViewControllerRepresentable(gameURL: game)
                        .ignoresSafeArea()
                }
            }
            .onAppear {
                loadGames()
            }
        }
    }

    // AUDIT REFERENCE: Section 2.6 — Load games from Documents/Games/
    private func loadGames() {
        let paths = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)
        guard let docsPath = paths.first else { return }
        let gamesPath = docsPath + "/Games"

        let fm = FileManager.default
        guard fm.fileExists(atPath: gamesPath) else { return }

        do {
            let files = try fm.contentsOfDirectory(at: URL(fileURLWithPath: gamesPath),
                                                    includingPropertiesForKeys: nil)
            let supportedExts = ["iso", "cso", "chd", "zso"]
            games = files.filter { supportedExts.contains($0.pathExtension.lowercased()) }
                         .sorted { $0.lastPathComponent < $1.lastPathComponent }
        } catch {
            NSLog("[BionicSX2] Failed to load games: \(error) (Audit Sec 2.6)")
        }
    }
}

// AUDIT REFERENCE: Section 2.6 — File picker for ISO/CHD selection
struct FilePickerView: UIViewControllerRepresentable {
    var onPick: (URL) -> Void

    func makeUIViewController(context: Context) -> UIDocumentPickerViewController {
        let types: [UTType] = [
            .init(filenameExtension: "iso") ?? .data,
            .init(filenameExtension: "cso") ?? .data,
            .init(filenameExtension: "chd") ?? .data,
            .init(filenameExtension: "zso") ?? .data,
        ]
        let picker = UIDocumentPickerViewController(forOpeningContentTypes: types)
        picker.delegate = context.coordinator
        picker.allowsMultipleSelection = false
        return picker
    }

    func updateUIViewController(_ uiViewController: UIDocumentPickerViewController, context: Context) {}

    func makeCoordinator() -> Coordinator {
        Coordinator(onPick: onPick)
    }

    class Coordinator: NSObject, UIDocumentPickerDelegate {
        let onPick: (URL) -> Void
        init(onPick: @escaping (URL) -> Void) { self.onPick = onPick }

        func documentPicker(_ controller: UIDocumentPickerViewController,
                           didPickDocumentsAt urls: [URL]) {
            if let url = urls.first {
                // Start accessing security-scoped resource
                let didStart = url.startAccessingSecurityScopedResource()
                if !didStart {
                    NSLog("[BionicSX2] Failed to access security-scoped resource (Audit Sec 2.6)")
                }
                // Copy to Documents/Games/ for persistent access
                let paths = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)
                if let docsPath = paths.first {
                    let destPath = docsPath + "/Games/" + url.lastPathComponent
                    let destURL = URL(fileURLWithPath: destPath)
                    if !FileManager.default.fileExists(atPath: destPath) {
                        try? FileManager.default.copyItem(at: url, to: destURL)
                    }
                }
                url.stopAccessingSecurityScopedResource()
                onPick(url)
            }
        }
    }
}

// AUDIT REFERENCE: Section 8.4 — Bridge MetalViewController to SwiftUI
struct MetalViewControllerRepresentable: UIViewControllerRepresentable {
    let gameURL: URL

    func makeUIViewController(context: Context) -> MetalViewController {
        let vc = MetalViewController()
        vc.gameURL = gameURL
        return vc
    }

    func updateUIViewController(_ uiViewController: MetalViewController, context: Context) {}
}
