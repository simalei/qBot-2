//
// Created by Alex on 12/14/2022.
//

#ifndef QBOT_CONVERTER_H
#define QBOT_CONVERTER_H

#include <includes.h>
#include <Engine/Engine.h>

namespace Converter {
    extern std::string convertToPlainText(std::vector<Engine::Click> macro, int frameOffset = 0);
    extern void convertFromPlainText(std::string plainText);
}

#endif //QBOT_CONVERTER_H
