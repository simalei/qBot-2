//
// Created by Alex on 12/11/2022.
//

#include "License.h"

namespace License {

    /*
    one means everything is fine
    zero means hwids don't match
    negative one means login data is wrong
    */


    licenseData ldata;
    bool LICENSED = false;

    std::string getID() {
        SYSTEM_INFO siSysInfo;
        GetSystemInfo(&siSysInfo);
        std::string id = std::string(
                std::to_string(siSysInfo.dwNumberOfProcessors) +
                std::to_string(siSysInfo.dwPageSize) +
                std::to_string(siSysInfo.dwProcessorType) +
                std::to_string(siSysInfo.dwActiveProcessorMask));

        return id;
    }

    size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data) {
        data->append((char *) ptr, size * nmemb);
        return size * nmemb;
    }

    int registerUser(std::string username, std::string password, std::string licenseKey) {
        std::string registerLink = "http://adarift.atwebpages.com/qbot/api/api.php?a=reg&n=" + username + "&p=" + password + "&ui=" + getID() + "&k=" + licenseKey;
        CURL *curl;
        CURLcode res;
        std::string response;
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, registerLink.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        if (response == "1") {
            return 1;
        } else {
            return 0;
        }
    }

    int loginUser(std::string username, std::string password) {
        std::string loginLink =
                "http://adarift.atwebpages.com/qbot/api/api.php?a=auth&n=" + username + "&p=" + password;
        CURL *curl;
        CURLcode res;
        std::string response;
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, loginLink.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        if (response == "-1") {
            return -1;
        }

        if (response == getID()) {
            return 1;
        } else {
            return 0;
        }
    }

    void saveLicenseData() {
        auto file = fopen(".qbot\\licenseData.dat", "wb");
        if (file) {
            fwrite(&ldata, sizeof(ldata), 1, file);
            fclose(file);
        }
    }

    void loadLicenseData() {
        auto file = fopen(".qbot\\licenseData.dat", "rb");
        if (file) {
            fseek(file, 0, SEEK_END);
            auto size = ftell(file);
            if (size == sizeof(ldata)) {
                fseek(file, 0, SEEK_SET);
                fread(&ldata, sizeof(ldata), 1, file);
                fclose(file);
            }
        }
    }
}