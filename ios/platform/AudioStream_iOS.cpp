// PORTED FROM: pcsx2/Host/CubebAudioStream.cpp — BionicSX2 iOS Port
// AUDIT REFERENCE: Section 9.2
// STATUS: YELLOW — cubeb replaced with native AVAudioEngine for iOS

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

#include <cstdint>
#include <cstring>

// Audit Section 9.2: AVAudioEngine stereo PCM audio backend for iOS
// cubeb has an iOS AudioUnit backend, but native AVAudioEngine provides
// simpler integration with iOS lifecycle and session management.

// Buffer configuration — Audit Section 9.3
#define AUDIO_SAMPLE_RATE 44100
#define AUDIO_CHANNELS 2
#define AUDIO_BUFFER_SIZE 2048 // safe mobile latency (Audit Sec 9.3)
#define AUDIO_BITS_PER_SAMPLE 16

static AVAudioEngine* s_audioEngine = nil;
static AVAudioPlayerNode* s_audioPlayer = nil;
static AVAudioFormat* s_audioFormat = nil;
static float s_audioBuffer[AUDIO_BUFFER_SIZE * AUDIO_CHANNELS];
static bool s_audioRunning = false;

// Audit Section 9.2: Init AVAudioEngine with stereo PCM
bool AudioStream_Init(void)
{
    if (s_audioEngine)
    {
        NSLog(@"[BionicSX2] AudioStream already initialized (Audit Sec 9.2)");
        return true;
    }

    NSError* error = nil;

    // Audit Section 9.3: Configure AVAudioSession for low-latency playback
    AVAudioSession* session = [AVAudioSession sharedInstance];
    [session setCategory:AVAudioSessionCategoryPlayback withOptions:AVAudioSessionCategoryOptionMixWithOthers error:&error];
    if (error)
    {
        NSLog(@"[BionicSX2] AVAudioSession setCategory failed: %@ (Audit Sec 9.2)", error.localizedDescription);
    }

    // Audit Section 9.3: Set preferred buffer duration for low latency (5ms)
    [session setPreferredIOBufferDuration:0.005 error:&error];
    if (error)
    {
        NSLog(@"[BionicSX2] setPreferredIOBufferDuration failed: %@ (Audit Sec 9.3)", error.localizedDescription);
    }

    [session setActive:YES error:&error];
    if (error)
    {
        NSLog(@"[BionicSX2] AVAudioSession setActive failed: %@ (Audit Sec 9.2)", error.localizedDescription);
        return false;
    }

    // Audit Section 9.2: Create AVAudioEngine with stereo PCM format
    s_audioEngine = [[AVAudioEngine alloc] init];
    s_audioPlayer = [[AVAudioPlayerNode alloc] init];
    [s_audioEngine attachNode:s_audioPlayer];

    // Stereo PCM float format at 44100Hz (Audit Sec 9.2)
    s_audioFormat = [[AVAudioFormat alloc] initWithCommonFormat:AVAudioPCMFormatFloat32
                                                     sampleRate:AUDIO_SAMPLE_RATE
                                                       channels:AUDIO_CHANNELS
                                                    interleaved:NO];
    if (!s_audioFormat)
    {
        NSLog(@"[BionicSX2] Failed to create AVAudioFormat (Audit Sec 9.2)");
        return false;
    }

    [s_audioEngine connect:s_audioPlayer to:[s_audioEngine mainMixerNode] format:s_audioFormat];

    // Start engine
    [s_audioEngine startAndReturnError:&error];
    if (error)
    {
        NSLog(@"[BionicSX2] AVAudioEngine start failed: %@ (Audit Sec 9.2)", error.localizedDescription);
        return false;
    }

    s_audioRunning = false;
    NSLog(@"[BionicSX2] AudioStream initialized: %dHz %dch stereo PCM (Audit Sec 9.2)",
          AUDIO_SAMPLE_RATE, AUDIO_CHANNELS);
    return true;
}

// Audit Section 9.2: Start audio playback
bool AudioStream_Start(void)
{
    if (!s_audioPlayer || s_audioRunning) return false;

    NSError* error = nil;
    [s_audioPlayer play];
    s_audioRunning = true;

    NSLog(@"[BionicSX2] AudioStream started (Audit Sec 9.2)");
    return true;
}

// Audit Section 9.2: Stop audio playback
void AudioStream_Stop(void)
{
    if (s_audioPlayer && s_audioRunning)
    {
        [s_audioPlayer stop];
        s_audioRunning = false;
        NSLog(@"[BionicSX2] AudioStream stopped (Audit Sec 9.2)");
    }
}

// Audit Section 9.2: Write PCM samples to audio output
// Matches SPU2::CreateOutputStream() interface (Audit Sec 2.5)
void AudioStream_Write(const float* samples, uint32_t numFrames)
{
    if (!s_audioPlayer || !s_audioRunning) return;

    uint32_t totalSamples = numFrames * AUDIO_CHANNELS;
    if (totalSamples > AUDIO_BUFFER_SIZE * AUDIO_CHANNELS)
    {
        NSLog(@"[BionicSX2] AudioStream_Write: buffer overflow — %u frames (max %d) (Audit Sec 9.3)",
              numFrames, AUDIO_BUFFER_SIZE);
        return;
    }

    // Copy samples into AVAudioPCMBuffer
    AVAudioFrameCount frameCount = (AVAudioFrameCount)numFrames;
    AVAudioPCMBuffer* buffer = [[AVAudioPCMBuffer alloc] initWithPCMFormat:s_audioFormat
                                                             frameCapacity:frameCount];
    buffer.frameLength = frameCount;

    // Interleave stereo float samples into the buffer
    float* leftChannel = buffer.floatChannelData[0];
    float* rightChannel = buffer.floatChannelData[1];
    for (AVAudioFrameCount i = 0; i < frameCount; i++)
    {
        leftChannel[i] = samples[i * 2];
        rightChannel[i] = samples[i * 2 + 1];
    }

    [s_audioPlayer scheduleBuffer:buffer
                    completionHandler:nil];
}

// Audit Section 9.2: Close audio engine
void AudioStream_Close(void)
{
    AudioStream_Stop();

    if (s_audioEngine)
    {
        [s_audioEngine stop];
        [s_audioEngine detachNode:s_audioPlayer];
        s_audioEngine = nil;
        s_audioPlayer = nil;
        s_audioFormat = nil;
    }

    AVAudioSession* session = [AVAudioSession sharedInstance];
    [session setActive:NO error:nil];

    s_audioRunning = false;
    NSLog(@"[BionicSX2] AudioStream closed (Audit Sec 9.2)");
}

// Audit Section 9.2: Handle AVAudioSession interruptions
void AudioStream_HandleInterruption(AVAudioSessionInterruptionType type)
{
    switch (type)
    {
        case AVAudioSessionInterruptionTypeBegan:
            NSLog(@"[BionicSX2] Audio interrupted — pausing (Audit Sec 9.2)");
            AudioStream_Stop();
            break;
        case AVAudioSessionInterruptionTypeEnded:
            NSLog(@"[BionicSX2] Audio interruption ended — resuming (Audit Sec 9.2)");
            AudioStream_Start();
            break;
    }
}
