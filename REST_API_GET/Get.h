#ifndef GET_H
#define GET_H

#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include "../json.hpp"

using json = nlohmann::json;

class Get {
public:
    // Constructor and destructor
    Get(const std::string& url);
    ~Get();

    // function to perform the GET request
    void getRequest();

private:
    std::string url;
    std::string responseBuffer;

    // Declaration WriteCallback function
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

    void saveResponseToFile(const std::string& filename);
};

#endif // GET_H
