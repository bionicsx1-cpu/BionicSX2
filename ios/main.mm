// BionicSX2 — iOS App Entry Point
// Audit Reference: Section 13.2 — BionicSX2App.swift is SwiftUI entry
// For CMake builds, UIApplicationMain is the C entry point.

#import <UIKit/UIKit.h>

int main(int argc, char* argv[])
{
    @autoreleasepool {
        return UIApplicationMain(
            argc,
            argv,
            nil,
            @"BionicSX2AppDelegate"
        );
    }
}
