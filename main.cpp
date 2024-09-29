#include <iostream>

#include "JSON_PARSING/JsonParsing.h"
#include "REST_API_POST/Post.h"
#include "REST_API_GET/Get.h"

int main() {

   //get Lampad inforamation by setting.json
   JsonParsing jsonParsing;
   JsonParsing::Lampad lampad;
   jsonParsing.getLampadInfo(lampad);

   std::cout << "json parsing is succed" << std::endl;

   //get Lampad Civet7Token for lampad login
   std::string postUrl = lampad.lampadUrl + "/q/login/";
   std::string jsonData = "{\"username\":\""+lampad.lampadId+"\",\"password\":\""+lampad.lampadPassword+"\"}";
   Post post(postUrl, jsonData);
   post.postRequest();

   //perform get request
    std::string getUrl = lampad.lampadUrl + "/q/paradox/";
    Get get(getUrl);
    get.getRequest();
   
   return 0;

}