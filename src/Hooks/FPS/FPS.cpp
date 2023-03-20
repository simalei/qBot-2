#include <includes.h>
#include "FPS.h"

float g_target_fps = 60.f;
bool g_disable_render = false;
float g_left_over = 0.f;
static float g_interval;

typedef void*   (__cdecl *fSharedApplication)();
typedef void    (__thiscall *fSetAnimationInterval)(void *instance, double delay);
fSharedApplication sharedApplication;
fSetAnimationInterval setAnimInterval;

void __fastcall hkCCSchedulerUpdate(CCScheduler* self, int, float dt) {
    if (!Engine::settings.fpsMultiplierEnabled)
        return CCScheduler_update(self, dt);
    auto speedhack = self->getTimeScale();



    const float newdt = 1.f / Engine::settings.fps / speedhack;
    g_disable_render = true;

    const int times = min(static_cast<int>((dt + g_left_over) / newdt), 100); // limit it to 100x just in case
    for (int i = 0; i < times; ++i) {
        if (i == times - 1)
            g_disable_render = false;
        CCScheduler_update(self, newdt);
    }
    g_left_over += dt - newdt * times;
}


void __fastcall hkPlayLayerUpdateVisibility(void* self) {
    if (!g_disable_render)
        PlayLayer_updateVisibility(self);
}

void setFPS() {
    g_interval = 1.0f / Engine::settings.fps;
    g_target_fps = Engine::settings.fps;
}

DWORD fpsThread(LPVOID lpParam) {
    while (true) {
        HMODULE hMod = LoadLibrary(LPCSTR("libcocos2d.dll"));
        sharedApplication = (fSharedApplication)GetProcAddress(hMod, "?sharedApplication@CCApplication@cocos2d@@SAPAV12@XZ");
        setAnimInterval = (fSetAnimationInterval)GetProcAddress(hMod, "?setAnimationInterval@CCApplication@cocos2d@@UAEXN@Z");
        void *application = sharedApplication();
        setAnimInterval(application, g_interval);
    }
}