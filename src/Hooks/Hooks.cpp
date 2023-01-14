//
// Created by Alex on 11/26/2022.
//

#include "Hooks.h"


namespace Hooks {
    void init()
    {
        size_t base = reinterpret_cast<size_t>(GetModuleHandle(0));

        MH_CreateHook(
                GetProcAddress(GetModuleHandleA("libcocos2d.dll"), "?update@CCScheduler@cocos2d@@UAEXM@Z"),
                hkCCSchedulerUpdate,
                (LPVOID*)&CCScheduler_update);
        MH_CreateHook(
                (PVOID)(base + 0x111500),
                PlayLayer::hkPushButton,
                (LPVOID*)&PlayLayer::pushButton);
        MH_CreateHook(
                (PVOID)(base + 0x111660),
                PlayLayer::hkReleaseButton,
                (LPVOID*)&PlayLayer::releaseButton);
        MH_CreateHook(
                (PVOID)(base + 0x01FB780),
                PlayLayer::hkInit,
                (LPVOID*)&PlayLayer::init);
        MH_CreateHook(
                (PVOID)(base + 0x2029C0),
                PlayLayer::hkUpdate,
                (LPVOID*)&PlayLayer::update);
        MH_CreateHook(
                (PVOID)(base + 0x20B050),
                PlayLayer::hkCreateCheckpoint,
                (LPVOID*)&Hooks::PlayLayer::createCheckpoint);
        MH_CreateHook(
                (PVOID)(base + 0x20B830),
                PlayLayer::hkRemoveCheckpoint,
                (LPVOID*)&PlayLayer::removeCheckpoint);
        MH_CreateHook(
                (PVOID)(base + 0x20BF00),
                PlayLayer::hkResetLevel,
                (LPVOID*)&PlayLayer::resetLevel);
        MH_CreateHook(
                (PVOID)(base + 0x20D810),
                PlayLayer::hkOnQuit,
                (LPVOID*)&PlayLayer::onQuit);
        MH_CreateHook(
                (PVOID)(base + 0x205460),
                hkPlayLayerUpdateVisibility,
                (LPVOID*)&PlayLayer_updateVisibility);

        MH_EnableHook(MH_ALL_HOOKS);
    }
}