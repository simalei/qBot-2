//
// Created by Alex on 11/26/2022.
//

#include "GUI.h"


namespace GUI {

    bool visible = false;

    void init()
    {
        DEVMODE dm;
        EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
        Engine::settings.fps = dm.dmDisplayFrequency;
        Engine::settings.speed = 1;

    }

    void render()
    {
        if (visible)
        {

            ImGui::Begin("General", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

            ImGui::SetWindowSize(ImVec2(230,326));
            ImGui::SetWindowPos(ImVec2(10, 10));

            ImGui::Combo("Mode", &Engine::mode, "Disabled\0Record\0Playback");

            ImGui::End();

            ImGui::Begin("Assist", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

            ImGui::SetWindowSize(ImVec2(230,157.5));
            ImGui::SetWindowPos(ImVec2(250, 10));

            ImGui::InputFloat("FPS", &Engine::settings.fps, 10.f);
            ImGui::Checkbox("FPS Multiplier", &Engine::settings.fpsMultiplierEnabled);
            ImGui::Button("Set FPS");

            ImGui::Separator();

            ImGui::InputFloat("Speed", &Engine::settings.speed, 0.1f);
            ImGui::Button("Set Speed");

            ImGui::End();

            ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

            ImGui::SetWindowSize(ImVec2(230,157.5));
            ImGui::SetWindowPos(ImVec2(250, 179.5));

            ImGui::End();
        }
    }
}