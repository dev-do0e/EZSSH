#include "Get.h"
#include <fstream>

// Constructor
Get::Get(const std::string &url)
    : url(url) {}

// Destructor
Get::~Get() {}

// Static callback function
size_t Get::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string* buffer = static_cast<std::string*>(userp);
    buffer->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

void Get::saveResponseToFile(const std::string &filename) {
    try {
        // JSON response pasing
        json jsonResponse = json::parse(responseBuffer);

        // save file
        std::ofstream file(filename);
        if (file.is_open()) {
            file << std::setw(4) << jsonResponse << std::endl;
            file.close();
            std::cout << "Response saved to " << filename << std::endl;
        } else {
            std::cerr << "Unable to open file to save response." << std::endl;
        }
    } catch (json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
}

// function to perform the GET request
void Get::getRequest() {
    CURL* curl;
    CURLcode res;

    // Initialize CURL handle
    curl = curl_easy_init();

    if (!curl) {
        std::cerr << "curl_easy_init() failed. Could not initialize CURL object." << std::endl;
        return; // Exit the function on error
    }

    // Enable verbose output for debugging
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    // setting HTTP GET
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    //buffer setting for Response date process
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

    // Set the cookie file
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie.jar");
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie.jar");

    // Perform the HTTP request
    res = curl_easy_perform(curl);
    

    if (res == CURLE_OK) {
        //std::cout << "Request successful. Response:\n" << response_buffer << std::endl;
        std::cout << std::endl << std::endl << "get res is find ^^7" <<  std::endl << std::endl << std::endl;
        saveResponseToFile("json/paradox.json");
    } else {
        std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);

}