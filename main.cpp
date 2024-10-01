#include <iostream>

#include "JSON_PARSING/JsonParsing.h"
#include "REST_API_POST/Post.h"
#include "REST_API_GET/Get.h"

int main() {

   //1. get Lampad inforamation by setting.json
   JsonParsing jsonParsing;
   JsonParsing::Lampad lampad;
   jsonParsing.getLampadInfo(lampad);

   std::cout << "This is information about the lampad server you set up." << std::endl;
   std::cout << "lampad url : " << lampad.lampadUrl << std::endl;
   std::cout << "lampad id : " << lampad.lampadId << std::endl;
   std::cout << "lampad password : " << lampad.lampadPassword << std::endl;
   
   //In setting.json, it checks whether the client has set the settings as desired and shuts down the system if the settings are not done correctly.
   bool answerCheck = true;
   while(answerCheck){

      std::cout << "If you have entered the lampad server information required to use DISSH correctly, enter 'y', otherwise enter 'n'. (without '')" << std::endl;
      std::string answer;
      std::cin >> answer;

      if(answer == "Y" || answer == "y"){
         answerCheck = false;
      }else if (answer == "N" || answer == "n"){
         answerCheck = false;
         std::cout << "Please enter lampad server information correctly in setting.json." << std::endl;
         system("pause");
         return 0;
      }

   }

   //2. get Lampad Civet7Token for lampad login
   //   Civet7Token is required to use the rest API
   std::string postUrl = lampad.lampadUrl + "/q/login/";
   std::string jsonData = "{\"username\":\""+lampad.lampadId+"\",\"password\":\""+lampad.lampadPassword+"\"}";
   Post post(postUrl, jsonData);
   post.postRequest();


   //3. perform get request
   //   Retrieve information about lampad-x connected to lampad
   //std::string getUrl = lampad.lampadUrl + "/q/paradox/";
   //Get get(getUrl);
   //get.getRequest();
   
   return 0;

}