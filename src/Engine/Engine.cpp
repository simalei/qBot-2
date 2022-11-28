//
// Created by Alex on 11/26/2022.
//

#include "Engine.h"


namespace Engine {

    std::vector<Click> replay;
    std::vector<Checkpoint> checkpoints;


    int frame = 0;
    int mode = 0;
    Settings settings;

    void handleInit(gd::PlayLayer *pl) {
        std::cout << "PlayLayer has been initialized. Frame: " << frame << std::endl;

    }

    void handleUpdate(gd::PlayLayer *pl) {
        if (pl->m_player1->getPositionX() != 0 && !pl->m_isDead)
            frame++;
        else
            frame = 0;
    }

    void handlePush(gd::PlayLayer *pl, bool player) {

    }

    void handleRelease(gd::PlayLayer *pl, bool player) {

    }

    void handleReset(gd::PlayLayer *pl) {

    }

    void createCheckpoint(gd::PlayLayer *pl) {
        Checkpoint checkpoint;
        checkpoint.frame = frame;
        checkpoint.P1.xpos = pl->m_player1->getPositionX();
        checkpoint.P1.ypos = pl->m_player1->getPositionY();
        checkpoint.P1.rotation = pl->m_player1->getRotation();
        checkpoint.P1.yAccel = pl->m_player1->m_yAccel;
        checkpoint.P2.xpos = pl->m_player2->getPositionX();
        checkpoint.P2.ypos = pl->m_player2->getPositionY();
        checkpoint.P2.rotation = pl->m_player2->getRotation();
        checkpoint.P2.yAccel = pl->m_player2->m_yAccel;
        checkpoints.push_back(checkpoint);
    }

    void removeCheckpoint(gd::PlayLayer *pl)
    {
        if (checkpoints.size() > 0)
        {
            checkpoints.pop_back();
        }
    }
}