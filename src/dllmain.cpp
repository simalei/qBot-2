#include "includes.h"
#include <Hooks/Hooks.h>
#include <Engine/Engine.h>
#include <GUI/GUI.h>
#include <Clickbot/Clickbot.h>
#include <direct.h>

DWORD MainThread(LPVOID lpParam)
{
    _mkdir(".qbot");
    _mkdir(".qbot\\replays");
    _mkdir(".qbot\\videos");
    _mkdir(".qbot\\clicks");
    MH_Initialize();
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);


    Clickbot::init(); // FMod initialization

    ImGuiHook::setInitFunction(GUI::init);
    ImGuiHook::setRenderFunction(GUI::render);

    ImGuiHook::setToggleCallback([]() {
        GUI::visible = !GUI::visible;
        if (GUI::visible)
            GUI::updateReplaysList();
    });

    ImGuiHook::setToggleKey(VK_RCONTROL);

    ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
        MH_CreateHook(target, hook, trampoline);
    });

    Hooks::init(); // All GD-related hooks

    MH_EnableHook(MH_ALL_HOOKS);

    return S_OK;
}


DWORD WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0x1000, reinterpret_cast<LPTHREAD_START_ROUTINE>(&MainThread), NULL, 0, NULL);
            CreateThread(NULL, 0x1000, reinterpret_cast<LPTHREAD_START_ROUTINE>(&fpsThread), NULL, 0, NULL);
            break;

        case DLL_PROCESS_DETACH:
            Engine::saveSettings();
            break;

        default:
            break;
    }

    return TRUE;
}