#ifndef POST_H
#define POST_H

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <fstream>

#include "../json.hpp"

using json = nlohmann::json;

class Post {
public:
    // Constructor and destructor
    Post(const std::string& url, const std::string& json_data);
    ~Post();

    // function to perform the GET request
    void postRequest();

private:
    std::string url;
    std::string jsonData;
    std::string responseBuffer;

    // Declaration WriteCallback function
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

    void saveResponseToFile(const std::string& filename);
};

#endif // POST_H
