//
// Created by Alex on 11/26/2022.
//

#include "Engine.h"


namespace Engine {
    std::vector<Click> replay;
    std::vector<Checkpoint> checkpoints;
    std::vector<std::string> sequence;

    int frame = 0;
    int mode = 0;
    bool inLevel = false;
    bool p1ButtonPushed = false;
    bool p2ButtonPushed = false;
    Settings settings;

    void handleInit(gd::PlayLayer *pl) {
        frame = 0;
        inLevel = true;
        checkpoints.clear();
        /*
        if (Engine::settings.sequenceEnabled) {
            loadReplay(sequence[sequenceIndex]);
        }
         */
    }

    void handleUpdate(gd::PlayLayer *pl) {
        if (pl->m_player1->getPositionX() == 0)
        {
            frame = 0;
        } else if (!pl->m_isDead) {
            frame++;
        }

        if (Engine::mode == 0)
        {

        } else if (Engine::mode == 1)
        {

        } else if (Engine::mode == 2)
        {
            for (size_t i = 0; i <= replay.size(); i++) {
                while (replay[i].frame == frame)
                {
                    if (replay[i].action) {
                        Hooks::PlayLayer::pushButton(pl, 0, replay[i].player);
                        Clickbot::push();
                    } else {
                        Hooks::PlayLayer::releaseButton(pl, 0, replay[i].player);
                        Clickbot::release();
                    }
                    break;
                }
            }
        }
    }

    void handlePush(gd::PlayLayer *pl, bool player) {
        if (Engine::mode == 1 && frame != 0)
        {
            if (player) {
                p1ButtonPushed = true;
            } else {
                p2ButtonPushed = true;
            }
            Click click;
            click.frame = frame;
            click.fps = (int)settings.fps;
            click.action = true;
            click.player = player;
            click.xpos = pl->m_player1->getPositionX();
            replay.push_back(click);
        }
    }

    void handleRelease(gd::PlayLayer *pl, bool player) {
        if (Engine::mode == 1 && frame != 0)
        {
            if (player) {
                p1ButtonPushed = false;
            } else {
                p2ButtonPushed = false;
            }
            Click click;
            click.frame = frame;
            click.fps = (int)settings.fps;
            click.action = false;
            click.player = player;
            click.xpos = pl->m_player1->getPositionX();
            replay.push_back(click);
        }
    }

    void handleReset(gd::PlayLayer *pl) {

        if (Engine::mode == 2)
        {
            Hooks::PlayLayer::releaseButton(pl, 0, true);
            Hooks::PlayLayer::releaseButton(pl, 0, false);
        }

        if (Engine::settings.sequenceEnabled && Engine::mode == 2) {
            if (Engine::settings.randomSequenceEnabled) {
                settings.sequenceIndex = rand() % Engine::sequence.size();
                loadReplay(Engine::sequence[settings.sequenceIndex]);
            } else {
                if (settings.sequenceFirstRun)  {
                    settings.sequenceIndex = 0;
                    settings.sequenceFirstRun = false;
                } else {
                    settings.sequenceIndex++;
                }

                if (Engine::sequence.size() <= (size_t)Engine::settings.sequenceIndex) Engine::settings.sequenceIndex = 0;
                loadReplay(Engine::sequence[settings.sequenceIndex]);
            }
        }

        if (checkpoints.size() != 0 && replay.size() != 0)
        {
            frame = checkpoints.back().frame;

            if (Engine::settings.checkpointFixEnabled)
            {
                pl->m_player1->setPositionX(checkpoints.back().P1.xpos);
                pl->m_player2->setPositionX(checkpoints.back().P2.xpos);
                pl->m_player1->setPositionY(checkpoints.back().P1.ypos);
                pl->m_player2->setPositionY(checkpoints.back().P2.ypos);
                pl->m_player1->setRotation(checkpoints.back().P1.rotation);
                pl->m_player2->setRotation(checkpoints.back().P2.rotation);
                pl->m_player1->m_yAccel = checkpoints.back().P1.yAccel;
                pl->m_player2->m_yAccel = checkpoints.back().P2.yAccel;
                pl->m_player1->m_isHolding = checkpoints.back().P1.isHolding;
                pl->m_player2->m_isHolding = checkpoints.back().P2.isHolding;
                pl->m_player1->m_isSliding = checkpoints.back().P1.isSliding;
                pl->m_player2->m_isSliding = checkpoints.back().P2.isSliding;
                pl->m_player1->m_playerSpeed = checkpoints.back().P1.playerSpeed;
                pl->m_player2->m_playerSpeed = checkpoints.back().P2.playerSpeed;

                if (checkpoints.back().P1.buttonPushed)
                {
                    Hooks::PlayLayer::pushButton(pl, 0, true);
                }
                if (checkpoints.back().P2.buttonPushed)
                {
                    Hooks::PlayLayer::pushButton(pl, 0, false);
                }
            }
            while (replay.back().frame >= frame)
            {
                replay.pop_back();
            }
        }
    }

    void handleQuit(gd::PlayLayer *pl)
    {
        frame = 0;
        inLevel = false;
    }

    void createCheckpoint(gd::PlayLayer *pl) {
        Checkpoint checkpoint;
        checkpoint.frame = frame;
        if (Engine::settings.checkpointFixEnabled)
        {
            checkpoint.P1.xpos = pl->m_player1->getPositionX();
            checkpoint.P1.ypos = pl->m_player1->getPositionY();
            checkpoint.P1.rotation = pl->m_player1->getRotation();
            checkpoint.P1.yAccel = pl->m_player1->m_yAccel;
            checkpoint.P1.isHolding = pl->m_player1->m_isHolding;
            checkpoint.P1.isSliding = pl->m_player1->m_isSliding;
            checkpoint.P1.playerSpeed = pl->m_player1->m_playerSpeed;
            checkpoint.P1.buttonPushed = p1ButtonPushed;

            checkpoint.P2.xpos = pl->m_player2->getPositionX();
            checkpoint.P2.ypos = pl->m_player2->getPositionY();
            checkpoint.P2.rotation = pl->m_player2->getRotation();
            checkpoint.P2.yAccel = pl->m_player2->m_yAccel;
            checkpoint.P2.isHolding = pl->m_player2->m_isHolding;
            checkpoint.P2.isSliding = pl->m_player2->m_isSliding;
            checkpoint.P2.playerSpeed = pl->m_player2->m_playerSpeed;
            checkpoint.P2.buttonPushed = p2ButtonPushed;
        }
        checkpoints.push_back(checkpoint);
    }

    void removeCheckpoint(gd::PlayLayer *pl)
    {
        if (checkpoints.size() > 0)
        {
            checkpoints.pop_back();
        }
    }

    void saveReplay(std::string path) {
        std::ofstream out(".qbot\\replays\\" + path + ".qbf2", std::ios::binary);
        out.write((char*)replay.data(),sizeof(Click)*replay.size());
        Engine::mode = 0;
    }

    void loadReplay(std::string path) {
        std::ifstream in(".qbot\\replays\\" + path + ".qbf2", std::ios::binary);
        size_t count = in.seekg(0, std::ios::end).tellg()/sizeof(Click);
        replay.resize(count);
        in.seekg(0);
        in.read((char*)replay.data(),sizeof(Click)*count);
        Engine::mode = 2;
        setFPS();
    }

    void saveSettings() {
        auto file = fopen(".qbot\\autosave.dat", "wb");
        if (file) {
            fwrite(&Engine::settings, sizeof(Engine::settings), 1, file);
            fclose(file);
        }
    }

    void loadSettings() {
        auto file = fopen(".qbot\\autosave.dat", "rb");
        if (file) {
            fseek(file, 0, SEEK_END);
            auto size = ftell(file);

            if (size == sizeof(Engine::settings)) {
                fseek(file, 0, SEEK_SET);
                fread(&Engine::settings, sizeof(Engine::settings), 1, file);
                fclose(file);
            }
        }
    }
}