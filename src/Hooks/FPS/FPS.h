//
// Created by Alex on 12/1/2022.
//

#ifndef QBOT_FPS_H
#define QBOT_FPS_H

#include <Engine/Engine.h>

inline void (__thiscall* CCScheduler_update)(CCScheduler*, float);
void __fastcall hkCCSchedulerUpdate(CCScheduler* self, int, float dt);

inline void (__thiscall* PlayLayer_updateVisibility)(void*);
void __fastcall hkPlayLayerUpdateVisibility(void* self);

extern void setFPS();
extern DWORD fpsThread(LPVOID lpParam);
#endif //QBOT_FPS_H
