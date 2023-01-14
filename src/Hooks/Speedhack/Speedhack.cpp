//
// Created by Alex on 12/1/2022.
//

#include "Speedhack.h"

void setSpeed() {
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(Engine::settings.speed);
}
