#include "Post.h"

// Constructor
Post::Post(const std::string &url, const std::string &jsonData)
    : url(url), jsonData(jsonData) {}

// Destructor
Post::~Post() {};

// Static callback function
size_t Post::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string* buffer = static_cast<std::string*>(userp);
    buffer->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

// function to perform the POST request
void Post::postRequest() {
    CURL* curl;
    CURLcode res;

    // Initialize CURL handle
    curl = curl_easy_init();
    
    if (!curl) {
        std::cerr << "curl_easy_init() failed. Could not initialize CURL object. (Post.cpp 26)" << std::endl;
        return;
    }

    //debugging
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    //Set url and jsonData to send HTTP POST.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)jsonData.length());

    //Setting headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    //buffer setting for Response date process
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie.jar");  // Read cookie from existing file (created if file does not exist)
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie.jar");   // Save cookie to file

    // Perform the HTTP request
    res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        //Now, when the response arrives, save the response here in the login.json file using the saveResponseToFile function.
        std::cout << "Post Request to retrieve Civet7Token was successful."<< std::endl;
        saveResponseToFile("json/login.json");
    } else {
        std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
    }

    //clear header list memory
    curl_slist_free_all(headers);

    curl_easy_cleanup(curl);
}

void Post::saveResponseToFile(const std::string &filename) {
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