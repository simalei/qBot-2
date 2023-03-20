//
// Created by Alex on 11/26/2022.
//

#ifndef QBOT_ENGINE_H
#define QBOT_ENGINE_H

#include <includes.h>
#include <Hooks/PlayLayer/PlayLayer.h>
#include <Recorder/Recorder.h>
#include <Hooks/FPS/FPS.h>
namespace Engine {


    struct PlayerStorage {
        float xpos;
        float ypos;
        float rotation;
        double yAccel;
        bool buttonPushed;
        bool isHolding;
        bool isSliding;
        float playerSpeed;
    };

    struct Click {
        int fps;
        int frame;
        float xpos;
        bool action;
        bool player;
    };

    struct Checkpoint {
        int frame;
        PlayerStorage P1;
        PlayerStorage P2;
    };



    struct Settings {
        float fps;
        float speed;
        bool accuracyFixEnabled;
        bool fpsMultiplierEnabled;
        bool checkpointFixEnabled;
        bool ignoreUserInputEnabled;
        bool dualClickEnabled;
        bool lockDeltaEnabled;
        bool frameAdvanceEnabled;

        // clickbot
        bool clickbotEnabled;
        bool softClicksEnabled;
        bool hardClicksEnabled;
        float softClickTime;
        float hardClickTime;
        float volume;

        // Recorder settings
        std::string recName, recCodec, recBitrate, recExtraArgs, recExtraAudioArgs;
        int recWidth, recHeight, recFps;
        bool recIncludeAudio;

        // sequence
        bool sequenceEnabled;
        bool randomSequenceEnabled;
        int sequenceIndex;
        bool sequenceFirstRun;
    };


    extern int frame;
    extern int mode;
    extern bool inLevel;
    extern int actionIndex;

    extern std::vector<Click> replay;
    extern std::vector<Checkpoint> checkpoints;
    extern Settings settings;

    extern std::vector<std::string> sequence;

    extern void handleInit(gd::PlayLayer* pl);
    extern void handleUpdate(gd::PlayLayer* pl);
    extern void handlePush(gd::PlayLayer* pl, bool player);
    extern void handleRelease(gd::PlayLayer* pl, bool player);
    extern void handleReset(gd::PlayLayer* pl);
    extern void handleQuit(gd::PlayLayer* pl);
    extern void createCheckpoint(gd::PlayLayer* pl);
    extern void removeCheckpoint(gd::PlayLayer* pl);

    extern void saveReplay(std::string path);
    extern void loadReplay(std::string path);

    extern void saveSettings();
    extern void loadSettings();

    extern DWORD frameThread(LPVOID lpParam);
}


#endif //QBOT_ENGINE_H
