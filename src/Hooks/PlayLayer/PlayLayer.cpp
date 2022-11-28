//
// Created by Alex on 11/26/2022.
//

#include "PlayLayer.h"

namespace Hooks::PlayLayer
{
    bool __fastcall hkInit(gd::PlayLayer* self, int edx, void* GJGameLevel)
    {
        Engine::handleInit(self);
        return init(self, GJGameLevel);
    }

    void __fastcall hkUpdate(gd::PlayLayer* self, void*, float delta)
    {
        Engine::handleUpdate(self);
        update(self, delta);
    }

    void __fastcall hkOnQuit(gd::PlayLayer* self)
    {
        onQuit(self);
    }

    int __fastcall hkResetLevel(gd::PlayLayer* self)
    {
        Engine::handleReset(self);
        resetLevel(self);
        return 0;
    }

    bool __fastcall hkPushButton(gd::PlayLayer* self, uintptr_t, int state, bool player)
    {
        if (Engine::settings.ignoreUserInputEnabled)
            return false;
        Engine::handlePush(self, player);
        return pushButton(self, state, player);
    }

    bool __fastcall hkReleaseButton(gd::PlayLayer* self, uintptr_t, int state, bool player)
    {
        if (Engine::settings.ignoreUserInputEnabled)
            return false;
        Engine::handleRelease(self, player);
        return releaseButton(self, state, player);
    }

    void __fastcall hkTogglePractice(void* self, int edx, bool practice)
    {
        togglePractice(self, practice);
    }

    int __fastcall hkCreateCheckpoint(gd::PlayLayer* self)
    {
        Engine::createCheckpoint(self);
        return createCheckpoint(self);
    }

    int __fastcall hkRemoveCheckpoint(gd::PlayLayer* self)
    {
        Engine::removeCheckpoint(self);
        return removeCheckpoint(self);
    }
} // namespace Hooks::PlayLayer