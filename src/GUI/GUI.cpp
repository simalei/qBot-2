//
// Created by Alex on 11/26/2022.
//

#include "GUI.h"

namespace GUI {


    bool _login;
    bool _register;
    bool visible = false;
    float tempFps;
    ImVec2 buttonSize = {230.f - 18.f, 24.f};
    std::string replayName;
    std::string sequenceReplayName;
    std::string copyName;

    std::vector<std::string> autocomplete;
    auto& rec = Recorder::get();

    int frameOffset = 0;
    std::string convertedMacro;
    bool sortWindows = true;
    bool sortWindows2 = true;

    std::filesystem::path path;


    std::string getFilenameFromFullPath(std::string s)
    {
        std::string fileName;
        int i;
        for(i = s.length(); (s[i] != '\\') && (s[i] != '/') && i >= 0; --i)
            ;
        while (s[++i] != '\0')
            fileName += s[i];
        return fileName;
    }

    std::string eraseExtension(std::string s)
    {
        std::string hello = s;
        const std::string tail = ".qbf2";
        size_t offset = hello.find_last_of(tail);
        if(offset != std::string::npos && offset == hello.length()-1)
            hello.erase(offset-tail.length()+1, tail.length());
        return hello;
    }

    std::string getFileExt(const std::string& s) {
        size_t i = s.rfind('.', s.length());
        if (i != std::string::npos) {
            return(s.substr(i+1, s.length() - i));
        }
        return("");
    }

    void embraceTheDarkness()
    {
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding                     = ImVec2(8.00f, 8.00f);
        style.FramePadding                      = ImVec2(5.00f, 2.00f);
        style.CellPadding                       = ImVec2(6.00f, 6.00f);
        style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
        style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
        style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
        style.IndentSpacing                     = 25;
        style.ScrollbarSize                     = 15;
        style.GrabMinSize                       = 10;
        style.WindowBorderSize                  = 1;
        style.ChildBorderSize                   = 1;
        style.PopupBorderSize                   = 1;
        style.FrameBorderSize                   = 1;
        style.TabBorderSize                     = 1;
        style.WindowRounding                    = 7;
        style.ChildRounding                     = 4;
        style.FrameRounding                     = 3;
        style.PopupRounding                     = 4;
        style.ScrollbarRounding                 = 9;
        style.GrabRounding                      = 3;
        style.LogSliderDeadzone                 = 4;
        style.TabRounding                       = 4;
        style.WindowTitleAlign                  = ImVec2(0.5f,0.5f);
    }
    void helpMarker(const char* desc)
    {
        ImGui::SameLine();
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
    void updateReplaysList()
    {
        std::filesystem::current_path(path);
        autocomplete.clear();
        for (auto& p : std::filesystem::directory_iterator(std::filesystem::current_path().string() + "\\.qbot\\replays\\"))
        {
            if (getFileExt(p.path().string()) == "qbf2")
                autocomplete.push_back(eraseExtension(getFilenameFromFullPath(p.path().string())));
        }
    }

    void init()
    {
        embraceTheDarkness();
        ImGuiIO* io = &ImGui::GetIO();

        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16.f);
        ImGui::MergeIconsWithLatestFont(16.f, false);
        DEVMODE dm;
        EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);


        // default settings
        Engine::settings.fps = 60;
        tempFps = Engine::settings.fps;
        Engine::settings.speed = 1;
        Engine::settings.fpsMultiplierEnabled = true;

        Engine::settings.recWidth = 1280;
        Engine::settings.recHeight = 720;
        Engine::settings.recFps = 60;
        Engine::settings.recBitrate = "30M";
        Engine::settings.recExtraArgs = "-crf 0";

        Engine::settings.softClicksEnabled = true;
        Engine::settings.hardClicksEnabled = true;

        Engine::settings.softClickTime = 0.3f;
        Engine::settings.hardClickTime = 1.5f;

        Engine::settings.volume = 1.f;


        License::loadLicenseData();
        if (License::loginUser(License::ldata.username, License::ldata.password) == 1)
        {
            License::LICENSED = true;
        }
        Engine::loadSettings();

        Engine::settings.sequenceEnabled = false;

        tempFps = Engine::settings.fps;
        setFPS();

        path = std::filesystem::current_path();

        if (!std::filesystem::exists(".qbot\\clicks\\clicks") || !std::filesystem::exists(".qbot\\clicks\\releases"))
            ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Clicks not found. Clickbot is disabled"});
    }


    void renderMain()
    {
        ImGui::Begin("General", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowSize(ImVec2(230,350));
        if (sortWindows || sortWindows2)
            ImGui::SetWindowPos(ImVec2(10, 10));

        ImGui::Combo("Mode", &Engine::mode, "Disabled\0Record\0Playback");
        ImGui::Checkbox("Ignore input on playback", &Engine::settings.ignoreUserInputEnabled);

        ImGui::Separator();

        ImGui::Text("Frame:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%d", Engine::frame);

        ImGui::Text("Loaded actions:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%d", Engine::replay.size());

        if (Engine::settings.sequenceEnabled) {
            ImGui::Text("Sequence:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%d/%d", Engine::settings.sequenceIndex + 1, Engine::sequence.size());
        }


        ImGui::Separator();

        ImGui::PushItemWidth(buttonSize.x);
        const bool is_input_text_enter_pressed = ImGui::InputText("##input", &replayName, ImGuiInputTextFlags_EnterReturnsTrue);
        const bool is_input_text_active = ImGui::IsItemActive();
        const bool is_input_text_activated = ImGui::IsItemActivated();

        if (is_input_text_activated)
            ImGui::OpenPopup("##popup");

        {
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y));
            ImGui::SetNextWindowSize({ ImGui::GetItemRectSize().x, 0 });
            if (ImGui::BeginPopup("##popup", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ChildWindow))
            {
                for (int i = 0; i < autocomplete.size(); i++)
                {
                    if (strstr(autocomplete[i].c_str(), replayName.c_str()) == NULL)
                        continue;
                    if (ImGui::Selectable(autocomplete[i].c_str()))
                    {
                        ImGui::ClearActiveID();
                        replayName = autocomplete[i];
                    }
                }

                if (is_input_text_enter_pressed || (!is_input_text_active && !ImGui::IsWindowFocused()))
                    ImGui::CloseCurrentPopup();

                ImGui::EndPopup();
            }
        }

        if (ImGui::Button("Save", {buttonSize.x / 2, buttonSize.y})) {
            if (replayName != "")
            {
                Engine::saveReplay(replayName);
                updateReplaysList();
                ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Replay successfully saved"});
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Load", {buttonSize.x / 2 - 5, buttonSize.y})) {
            Engine::replay.clear();
            if (replayName != "")
            {
                Engine::loadReplay(replayName);
                Engine::settings.fps = Engine::replay[0].fps;
                tempFps = Engine::replay[0].fps;
                setFPS();
                updateReplaysList();
                ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Replay successfully loaded"});
            }
        }

        if (ImGui::Button("Clear", buttonSize))
        {
            Engine::replay.clear();
        }

        if (ImGui::Button("Copy", buttonSize))
        {
            if (replayName != "")
            {
                copyName.clear();
                copyName = replayName + "_Copy";
                ImGui::OpenPopup("Copy");
            }

        }

        if (ImGui::Button("Delete", buttonSize))
        {
            remove((".qbot\\replays\\" + replayName + ".qbf2").c_str());
            updateReplaysList();
            replayName.clear();
        }

        ImGui::Separator();

        if (ImGui::Button("Import", {buttonSize.x / 2, buttonSize.y}))
        {
            ImGui::OpenPopup("ImportPopup");
        }

        ImGui::SameLine();

        if (ImGui::Button("Export", {buttonSize.x / 2 - 5, buttonSize.y}))
        {
            ImGui::OpenPopup("ExportPopup");
        }

        if (ImGui::BeginPopup("ImportPopup")) {
            if (ImGui::Button("Plain text")) {
                OPENFILENAME ofn;
                char fileName[MAX_PATH] = "";
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lpstrFilter = "Plain Text (*.txt)\0*.txt";
                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.lpstrFile = fileName;
                ofn.nMaxFile = MAX_PATH;
                if (GetOpenFileName(&ofn)) {
                    std::stringstream ss;
                    std::string line;
                    std::ifstream in((std::string(fileName)).c_str());
                    if (in.is_open()) {
                        while (getline(in, line)) {
                            ss << line << std::endl;
                        }
                    }
                    in.close();
                    Converter::convertFromPlainText(ss.str());
                }
            }

            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("ExportPopup")) {
            if (ImGui::Button("Plain text")) {
                OPENFILENAME ofn;
                char fileName[MAX_PATH] = "";
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lpstrFilter = "Plain Text (*.txt)\0*.txt";
                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.lpstrFile = fileName;
                ofn.nMaxFile = MAX_PATH;
                if (GetSaveFileName(&ofn)) {
                    std::ofstream out;
                    out.open((std::string(fileName) + ".txt").c_str());
                    if (out.is_open()) {
                        out << Converter::convertToPlainText(Engine::replay);
                    }
                    out.close();
                }
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopupModal("Copy", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::PushItemWidth(buttonSize.x + 5);
            ImGui::InputText("##CopyInput", &copyName);
            if (ImGui::Button("Copy", {buttonSize.x / 2, 0})) {
                std::filesystem::copy_file(".qbot\\replays\\" + replayName + ".qbf2", ".qbot\\replays\\" + copyName + ".qbf2");
                updateReplaysList();
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", {buttonSize.x / 2, 0}))
                ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
        }

        ImGui::End();


        ImGui::Begin("Assist", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowSize(ImVec2(230,185));
        if (sortWindows || sortWindows2)
            ImGui::SetWindowPos(ImVec2(250, 10));

        ImGui::InputFloat("FPS", &tempFps, 10.f);
        ImGui::Checkbox("FPS Multiplier", &Engine::settings.fpsMultiplierEnabled);
        if (ImGui::Button("Set FPS", buttonSize))
        {
            Engine::settings.fps = tempFps;
            setFPS();
        }

        ImGui::Separator();

        ImGui::InputFloat("Speed", &Engine::settings.speed, 0.1f);
        if (ImGui::Button("Set speed", buttonSize))
        {
            setSpeed();
        }


        ImGui::End();

        ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowSize(ImVec2(230,155));
        if (sortWindows || sortWindows2)
        {
            ImGui::SetWindowPos(ImVec2(250, 205));
            sortWindows2 = false;
        }

        ImGui::Checkbox("Dual click", &Engine::settings.dualClickEnabled);
        helpMarker("Clicks both players at the same time");

        ImGui::Checkbox("Checkpoint fix", &Engine::settings.checkpointFixEnabled);
        helpMarker("Saves more data (y acceleration, etc.) every checkpoint and restores that data after respawn");

        if (ImGui::Button("Reset layout", buttonSize))
        {
            sortWindows = true;
            sortWindows2 = true;
        }

        ImGui::End();

        ImGui::Begin("Recorder", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowSize(ImVec2(230,350));
        if (sortWindows)
            ImGui::SetWindowPos(ImVec2(490, 10));

        ImGui::InputText("Name", &Engine::settings.recName);
        ImGui::InputInt("Width", &Engine::settings.recWidth);
        ImGui::InputInt("Height", &Engine::settings.recHeight);
        ImGui::InputInt("FPS", &Engine::settings.recFps);
        ImGui::InputText("Codec", &Engine::settings.recCodec);
        ImGui::InputText("Bitrate", &Engine::settings.recBitrate);
        ImGui::InputText("Extra args", &Engine::settings.recExtraArgs);
        ImGui::Checkbox("Include audio", &Engine::settings.recIncludeAudio);

        if (ImGui::Button("Presets", buttonSize))
        {
            ImGui::OpenPopup("PresetsPopup");
        }

        if (ImGui::BeginPopup("PresetsPopup"))
        {
            float popupX;
            if (ImGui::Button("HD (720p)"))
            {
                Engine::settings.recWidth = 1280;
                Engine::settings.recHeight = 720;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("Full HD (1080p)"))
            {
                Engine::settings.recWidth = 1920;
                Engine::settings.recHeight = 1080;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("Quad HD (1440p)"))
            {
                Engine::settings.recWidth = 2560;
                Engine::settings.recHeight = 1440;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("4K (2160p)"))
            {
                Engine::settings.recWidth = 3840;
                Engine::settings.recHeight = 2160;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("8K (4320p)"))
            {
                Engine::settings.recWidth = 7680;
                Engine::settings.recHeight = 4320;
                ImGui::CloseCurrentPopup();
            }
            ImGui::Separator();
            if (ImGui::Button("NVIDIA GPU codec"))
            {
                Engine::settings.recCodec = "h264_nvenc";
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("AMD GPU codec"))
            {
                Engine::settings.recCodec = "h264_amf";
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("Intel GPU codec"))
            {
                Engine::settings.recCodec = "h264_qsv";
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        if (!rec.recording)
        {
            if (ImGui::Button("Start recording", buttonSize))
            {
                if (Engine::inLevel)
                {
                    rec.lastFrameTime = 0;
                    rec.start((".qbot\\videos\\" + Engine::settings.recName + ".mp4").c_str());
                } else {
                    ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Enter a level to start recording"});
                }
            }
        } else {
            if (ImGui::Button("Stop recording", buttonSize))
            {
                rec.stop();
            }
        }

        ImGui::End();

        ImGui::Begin("Clicks", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowSize(ImVec2(230,185));
        if (sortWindows)
            ImGui::SetWindowPos(ImVec2(730, 10));

        ImGui::Checkbox("Enabled", &Engine::settings.clickbotEnabled);

        ImGui::Separator();

        ImGui::BeginDisabled(!Engine::settings.clickbotEnabled);


        ImGui::BeginDisabled(!std::filesystem::exists(".qbot\\clicks\\softClicks") && !std::filesystem::exists(".qbot\\clicks\\softReleases"));
        ImGui::Checkbox("Soft clicks", &Engine::settings.softClicksEnabled);
        ImGui::EndDisabled();

        ImGui::SameLine();

        ImGui::BeginDisabled(!std::filesystem::exists(".qbot\\clicks\\hardClicks") && !std::filesystem::exists(".qbot\\clicks\\hardReleases"));
        ImGui::Checkbox("Hard clicks", &Engine::settings.hardClicksEnabled);
        ImGui::EndDisabled();

        ImGui::BeginDisabled(!std::filesystem::exists(".qbot\\clicks\\clicks") && !std::filesystem::exists(".qbot\\clicks\\releases"));

        ImGui::InputFloat("Soft time", &Engine::settings.softClickTime, 0.1f);
        ImGui::InputFloat("Hard time", &Engine::settings.hardClickTime, 0.1f);

        ImGui::SliderFloat("Volume", &Engine::settings.volume, 0.f, 1.5f, "%.1f");

        ImGui::EndDisabled();

        ImGui::EndDisabled();

        ImGui::End();

        ImGui::Begin("Replay editor", nullptr,  ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowSize(ImVec2(300, 350));
        if (sortWindows)
            ImGui::SetWindowPos(ImVec2(970, 10));

        ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 310), false);

        ImGui::InputTextMultiline("##editor", &convertedMacro, ImVec2(140, 310));
        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginChild("ChildR", ImVec2(0, 285), false);

        ImGui::Text("Frame offset");

        ImGui::InputInt("##1", &frameOffset);
        if (ImGui::Button("Apply", {135.f, 24.f}))
        {
            convertedMacro = Converter::convertToPlainText(Engine::replay, frameOffset);
        }

        ImGui::Separator();

        if (ImGui::Button("Load", {135.f, 24.f}))
        {
            convertedMacro = Converter::convertToPlainText(Engine::replay);
        }

        if (ImGui::Button("Save", {135.f, 24.f}))
        {
            Converter::convertFromPlainText(convertedMacro);
            frameOffset = 0;
        }

        ImGui::EndChild();
        ImGui::End();

        ImGui::Begin("Sequence", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowSize(ImVec2(230,155));
        if (sortWindows) {
            ImGui::SetWindowPos(ImVec2(730, 205));
        }


        if (ImGui::BeginChild("##sequenceChild", ImVec2(NULL, 60), true))
        {
            for (size_t n = 0; n < Engine::sequence.size(); n++)
            {
                bool is_selected = (Engine::settings.sequenceIndex == n);
                std::string anticonflict = Engine::sequence[n] + "##" + std::to_string(n);
                if (ImGui::Selectable(anticonflict.c_str(), is_selected)) Engine::settings.sequenceIndex = n;
            }
            ImGui::EndChild();
        }


        ImGui::PushItemWidth(buttonSize.x - 50);
        const bool is_input_text_enter_pressed2 = ImGui::InputText("##sequenceInput", &sequenceReplayName, ImGuiInputTextFlags_EnterReturnsTrue);
        const bool is_input_text_active2 = ImGui::IsItemActive();
        const bool is_input_text_activated2 = ImGui::IsItemActivated();

        if (is_input_text_activated2)
            ImGui::OpenPopup("##popup");

        {
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y));
            ImGui::SetNextWindowSize({ ImGui::GetItemRectSize().x, 0 });
            if (ImGui::BeginPopup("##popup", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ChildWindow))
            {
                for (int i = 0; i < autocomplete.size(); i++)
                {
                    if (strstr(autocomplete[i].c_str(), sequenceReplayName.c_str()) == NULL)
                        continue;
                    if (ImGui::Selectable(autocomplete[i].c_str()))
                    {
                        ImGui::ClearActiveID();
                        sequenceReplayName = autocomplete[i];
                    }
                }

                if (is_input_text_enter_pressed2 || (!is_input_text_active2 && !ImGui::IsWindowFocused()))
                    ImGui::CloseCurrentPopup();

                ImGui::EndPopup();
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("+", {20.f, 0})) {
            Engine::sequence.push_back(sequenceReplayName);
            Engine::settings.sequenceFirstRun = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("-", {20.f, 0})) {
            if (Engine::sequence.size() > (size_t)Engine::settings.sequenceIndex) {
                Engine::sequence.erase(Engine::sequence.begin()+Engine::settings.sequenceIndex);
                Engine::settings.sequenceFirstRun = true;
            }
        }


        ImGui::Checkbox("Enabled", &Engine::settings.sequenceEnabled);
        ImGui::SameLine();
        ImGui::BeginDisabled(!Engine::settings.sequenceEnabled);
        ImGui::Checkbox("Random sequence", &Engine::settings.randomSequenceEnabled);
        ImGui::EndDisabled();

        ImGui::End();

        ImGui::Begin("About", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowSize(ImVec2(230,155));
        if (sortWindows) {
            ImGui::SetWindowPos(ImVec2(1280, 10));
            sortWindows = false;
        }


        ImGui::Text("qBot by");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "adarift");

        ImGui::Text("qBot version:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "v2.0");

        ImGui::Text("Build date:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "20 Mar 2022");

        ImGui::Text("ImGui version:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", ImGui::GetVersion());

        ImGui::Separator();

        if (ImGui::Button("Special thanks", buttonSize))
        {
            ShellExecute(0, 0, LPCSTR("https://pastebin.com/raw/PKpxRaM6"), 0, 0 , SW_SHOW );
        }

        ImGui::End();
    }


    void renderLogin()
    {

        ImGui::Begin("qBot login", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        auto windowSize = ImGui::GetWindowSize();
        ImVec2 btnSize = {windowSize.x - 18, 24.f};

        if (_login)
        {
            ImGui::InputText("Username", &License::ldata.username);
            ImGui::InputText("Password", &License::ldata.password, ImGuiInputTextFlags_Password);
            ImGui::Checkbox("Remember credentials", &License::ldata.remember);
            if (ImGui::Button("Login", btnSize))
            {
                if (License::loginUser(License::ldata.username, License::ldata.password) == 1)
                {
                    if (License::ldata.remember)
                    {
                        License::saveLicenseData();
                    }
                    License::LICENSED = true;
                    ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Successfully logged in"});
                } else {
                    ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Failed to login"});
                }
            }
            if (ImGui::Button("Go back", btnSize))
            {
                _login = false;
            }
        } else if (_register)
        {
            ImGui::InputText("Username", &License::ldata.username);
            ImGui::InputText("Password", &License::ldata.password, ImGuiInputTextFlags_Password);
            ImGui::InputText("Confirm password", &License::ldata.password2, ImGuiInputTextFlags_Password);
            ImGui::InputText("License key", &License::ldata.licenseKey);
            if (ImGui::Button("Register", btnSize))
            {
                if (License::ldata.password == License::ldata.password2)
                {
                    if (License::registerUser(License::ldata.username, License::ldata.password, License::ldata.licenseKey) == 1)
                    {
                        ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Registered successfully! Thanks for purchasing qBot"});
                    } else {
                        ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Failed to register. Check your details and internet connection"});
                    }
                } else {
                    ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Passwords do not match"});
                }
            }
            if (ImGui::Button("Go back", btnSize))
            {
                _register = false;
            }

        } else {
            if (ImGui::Button("Login", buttonSize))
            {
                _login = true;
                _register = false;
            }
            if (ImGui::Button("Register", buttonSize))
            {
                _register = true;
                _login = false;
            }
        }
        ImGui::End();


    }

    void render()
    {
        if (IsDebuggerPresent())
        {
            exit(-1);
        }
        if (visible)
        {
            if (!License::LICENSED)
            {
                renderLogin();
            } else {
                renderMain();
            }
            //ImGui::ShowDemoWindow();
        }
        ImGui::RenderNotifications(); // <-- Here we render all notifications
    }
}