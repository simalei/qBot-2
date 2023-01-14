//
// Created by Alex on 12/11/2022.
//

#ifndef QBOT_LICENSE_H
#define QBOT_LICENSE_H

#include <includes.h>

namespace License {

    struct licenseData {
        std::string username, password, password2, licenseKey;
        bool remember;
    };

    extern licenseData ldata;
    extern bool LICENSED;
    extern int registerUser(std::string username, std::string password, std::string licenseKey);
    extern int loginUser(std::string username, std::string password);
    extern void saveLicenseData();
    extern void loadLicenseData();
}

#endif //QBOT_LICENSE_H
