//
// Created by Alex on 12/12/2022.
//

#include "Clickbot.h"

namespace Clickbot {

    bool initialized = false;

    std::string pickRandomPush(SoundType type) {
        srand(time(0));
        std::vector<std::string> files;
        std::string path;

        switch (type) {
            case SOFT:
                if (Engine::settings.softClicksEnabled && std::filesystem::exists("\\.qbot\\clicks\\softClicks\\"))
                    path = "\\.qbot\\clicks\\softClicks\\";
                else
                    path = "\\.qbot\\clicks\\clicks\\";
                break;
            case HARD:
                if (Engine::settings.hardClicksEnabled && std::filesystem::exists("\\.qbot\\clicks\\hardClicks\\"))
                    path = "\\.qbot\\clicks\\hardClicks\\";
                else
                    path = "\\.qbot\\clicks\\clicks\\";
                break;
            case NORMAL:
                path = "\\.qbot\\clicks\\clicks\\";
                break;
        }
        for (auto& p : std::filesystem::directory_iterator(std::filesystem::current_path().string() + path))
        {
            files.push_back(p.path().string());
        }
        int index = rand() % files.size();
        return files[index];
    }

    std::string pickRandomRelease(SoundType type) {
        srand(time(0));
        std::vector<std::string> files;
        std::string path;

        switch (type) {
            case SOFT:
                if (Engine::settings.softClicksEnabled && std::filesystem::exists("\\.qbot\\clicks\\softReleases\\"))
                    path = "\\.qbot\\clicks\\softReleases\\";
                else
                    path = "\\.qbot\\clicks\\releases\\";
                break;
            case HARD:
                if (Engine::settings.hardClicksEnabled && std::filesystem::exists("\\.qbot\\clicks\\hardReleases\\"))
                    path = "\\.qbot\\clicks\\hardReleases\\";
                else
                    path = "\\.qbot\\clicks\\releases\\";
                break;
            case NORMAL:
                path = "\\.qbot\\clicks\\releases\\";
                break;
        }
        for (auto& p : std::filesystem::directory_iterator(std::filesystem::current_path().string() + path))
        {
            files.push_back(p.path().string());
        }
        int index = rand() % files.size();
        return files[index];
    }



    void init() {
        if (!initialized) {
            auto GDEngine = gd::FMODAudioEngine::sharedEngine();
            FMOD::System_Create(&Clickbot::system);
            Clickbot::system->init(1024 * 2, FMOD_INIT_NORMAL, GDEngine->m_pExtraDriverData);
            initialized = true;
        }
    }

    void push() {
        if (Engine::settings.clickbotEnabled && initialized && std::filesystem::exists(".qbot\\clicks\\clicks\\")) {
            Clickbot::now = std::chrono::system_clock::now();
            Clickbot::cycleTime = Clickbot::now - Clickbot::start;

            std::string path;
            SoundType type;
            Clickbot::start = std::chrono::system_clock::now();

            if (Clickbot::cycleTime.count() < Engine::settings.softClickTime) {
                type = SOFT;
            } else if (Clickbot::cycleTime.count() > Engine::settings.hardClickTime) {
                type = HARD;
            } else {
                type = NORMAL;
            }

            path = pickRandomPush(type);
            Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::pushSound);

            Clickbot::system->playSound(Clickbot::pushSound, nullptr, true, &Clickbot::pushChannel);
            Clickbot::pushChannel->setVolume(Engine::settings.volume);
            Clickbot::pushChannel->setPaused(false);
            Clickbot::system->update();
        }
    }

    void release() {
        if (Engine::settings.clickbotEnabled && initialized && std::filesystem::exists(".qbot\\clicks\\clicks\\")) {
            std::string path;
            SoundType type;

            if (Clickbot::cycleTime.count() < Engine::settings.softClickTime) {
                type = SOFT;
            } else if (Clickbot::cycleTime.count() > Engine::settings.hardClickTime) {
                type = HARD;
            } else {
                type = NORMAL;
            }

            path = pickRandomRelease(type);
            Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);

            Clickbot::system->playSound(Clickbot::releaseSound, nullptr, true, &Clickbot::releaseChannel);
            Clickbot::releaseChannel->setVolume(Engine::settings.volume);
            Clickbot::releaseChannel->setPaused(false);
            Clickbot::system->update();
        }
    }
}