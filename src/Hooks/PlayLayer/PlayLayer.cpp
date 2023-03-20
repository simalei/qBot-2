//
// Created by Alex on 11/26/2022.
//

#include "PlayLayer.h"

auto& rec = Recorder::get();

namespace Hooks::PlayLayer
{
    bool __fastcall hkInit(gd::PlayLayer* self, int edx, void* GJGameLevel)
    {
        auto res = init(self, GJGameLevel);
        Engine::handleInit(self);
        rec.updateSongOffset(self);
        return res;
    }

    void __fastcall hkUpdate(gd::PlayLayer* self, void*, float delta)
    {
        if (self->m_player1->getPositionX() == 0)
        {
            Engine::frame = 0;
        } else if (!self->m_isDead) {
            Engine::frame++;
        }

        if (rec.recording)
        {
            rec.handleRecording(self, delta);
        }
        if (Engine::mode == 2)
        {
            update(self, 1 / Engine::settings.fps);
        } else {
            update(self, delta);
        }
        Engine::handleUpdate(self);
    }

    void __fastcall hkOnQuit(gd::PlayLayer* self)
    {
        Engine::handleQuit(self);
        onQuit(self);
    }

    int __fastcall hkResetLevel(gd::PlayLayer* self)
    {
        auto rs = resetLevel(self);
        Engine::frame = 0;
        Engine::handleReset(self);
        if (rec.recording) {
            rec.updateSongOffset(self);
        }
        return rs;
    }

    bool __fastcall hkPushButton(gd::PlayLayer* self, uintptr_t, int state, bool player)
    {
        Engine::handlePush(self, player);
        if (Engine::settings.ignoreUserInputEnabled && Engine::mode == 2)
            return false;
        if (Engine::settings.dualClickEnabled)
        {
            Engine::handlePush(self, !player);
            pushButton(self, 0, !player);
        }
        return pushButton(self, state, player);
    }

    bool __fastcall hkReleaseButton(gd::PlayLayer* self, uintptr_t, int state, bool player)
    {
        Engine::handleRelease(self, player);
        if (Engine::settings.ignoreUserInputEnabled && Engine::mode == 2)
        {
            return false;
        }
        if (Engine::settings.dualClickEnabled)
        {
            Engine::handleRelease(self, !player);
            releaseButton(self, 0, !player);
        }
        return releaseButton(self, state, player);
    }

    void __fastcall hkTogglePractice(void* self, int edx, bool practice)
    {
        togglePractice(self, practice);
    }

    int __fastcall hkCreateCheckpoint(gd::PlayLayer* self)
    {
        auto rs = createCheckpoint(self);
        Engine::createCheckpoint(self);
        return rs;
    }

    int __fastcall hkRemoveCheckpoint(gd::PlayLayer* self)
    {
        auto rs = removeCheckpoint(self);
        Engine::removeCheckpoint(self);
        return rs;
    }
} // namespace Hooks::PlayLayer