//
// Created by Alex on 11/26/2022.
//

#include "Hooks.h"


namespace Hooks {
    void init()
    {
        MH_CreateHook(
                (PVOID)(gd::base + 0x01FB780),
                PlayLayer::hkInit,
                (LPVOID*)&PlayLayer::init);
        MH_CreateHook(
                (PVOID)(gd::base + 0x2029C0),
                PlayLayer::hkUpdate,
                (LPVOID*)&PlayLayer::update);
        MH_CreateHook(
                (PVOID)(gd::base + 0x111500),
                PlayLayer::hkPushButton,
                (LPVOID*)&PlayLayer::pushButton);
        MH_CreateHook(
                (PVOID)(gd::base + 0x20B050),
                PlayLayer::hkCreateCheckpoint,
                (LPVOID*)&Hooks::PlayLayer::createCheckpoint);
        MH_CreateHook(
                (PVOID)(gd::base + 0x20B830),
                PlayLayer::hkRemoveCheckpoint,
                (LPVOID*)&PlayLayer::removeCheckpoint);
        MH_CreateHook(
                (PVOID)(gd::base + 0x20BF00),
                PlayLayer::hkResetLevel,
                (LPVOID*)&PlayLayer::resetLevel);


    }
}