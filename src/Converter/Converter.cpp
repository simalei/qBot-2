//
// Created by Alex on 12/14/2022.
//

#include "Converter.h"


namespace Converter {

    void tokenize(const std::string &s, const char delim,
                  std::vector<std::string> &out)
    {
        std::string::size_type beg = 0;
        for (auto end = 0; (end = s.find(delim, end)) != std::string::npos; ++end)
        {
            out.push_back(s.substr(beg, end - beg));
            beg = end + 1;
        }

        out.push_back(s.substr(beg));
    }

    std::string convertToPlainText(std::vector<Engine::Click> replay, int frameOffset) {
        if (Engine::replay.size() == 0)
            return "";
        std::stringstream ss;
        ss << Engine::replay[0].fps << "\n";
        for (int i = 0; i < Engine::replay.size(); ++i) {
            ss << Engine::replay[i].frame + frameOffset;
            std::string action;
            if (Engine::replay[i].player) {
                ss << (Engine::replay[i].action ? " 1" : " 0") << " 0\n";
            } else {
                ss << " 0 " << (Engine::replay[i].action ? "1" : "0") << "\n";
            }
        }
        return ss.str();
    }

    void convertFromPlainText(std::string plainText)
    {
        Engine::replay.clear();
        if (plainText.empty())
            return;
        int fps;
        int frame;
        bool action;
        bool player;
        std::vector<std::string> tmp;
        std::vector<std::string> tmp2;
        const char delim1 = '\n';
        const char delim2 = ' ';
        tokenize(plainText, delim1, tmp);
        fps = std::stoi(tmp[0]);
        for (size_t i = 1; i < tmp.size() - 1; i++) {
            tmp2.clear();
            tokenize(tmp[i], delim2, tmp2);

            if (!tmp2.empty())
            {
                frame = std::stoi(tmp2[0]);

                if (tmp2[1] == "1" && tmp2[2] == "0")
                {
                    action = true;
                    player = true;
                } else if (tmp2[1] == "0" && tmp2[2] == "1") {
                    action = true;
                    player = false;
                } else {
                    action = false;
                    player = false;
                }

            }
            Engine::replay.push_back({fps, frame, -1, action, player});
        }
    }
}