//
// Created by Alex on 11/26/2022.
//

#ifndef QBOT_GUI_H
#define QBOT_GUI_H

#include <includes.h>
#include <Engine/Engine.h>
#include <Hooks/FPS/FPS.h>
#include <Hooks/Speedhack/Speedhack.h>
#include <Recorder/Recorder.h>
#include <License/License.h>
#include <Clickbot/Clickbot.h>
#include <Converter/Converter.h>

namespace GUI {
    extern bool visible;
    extern std::string replayName;
    extern void updateReplaysList();
    void init();
    void render();
}

#endif //QBOT_GUI_H
