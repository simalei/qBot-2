//
// Created by Alex on 12/12/2022.
//

#ifndef QBOT_CLICKBOT_H
#define QBOT_CLICKBOT_H

#include <includes.h>
#include <Engine/Engine.h>

namespace Clickbot {
    void init();

    extern bool initialized;

    static inline std::chrono::system_clock::time_point start, now;
    static inline std::chrono::duration<double> cycleTime;

    static inline FMOD::System* system;
    static inline FMOD::Channel* pushChannel;
    static inline FMOD::Sound* pushSound;
    static inline FMOD::Channel* releaseChannel;
    static inline FMOD::Sound* releaseSound;

    enum SoundType {
        SOFT,
        NORMAL,
        HARD
    };

    extern void push();
    extern void release();

    std::string pickRandomPush(SoundType type);
    std::string pickRandomRelease(SoundType type);
}
#endif //QBOT_CLICKBOT_H
