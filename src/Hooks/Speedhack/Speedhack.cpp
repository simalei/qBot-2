//
// Created by Alex on 12/1/2022.
//

#include "Speedhack.h"

void setSpeed() {
    Speedhack::SetSpeed(Engine::settings.speed);
    //CCDirector::sharedDirector()->getScheduler()->setTimeScale(Engine::settings.speed);
}
