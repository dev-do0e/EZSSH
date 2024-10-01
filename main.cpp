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

   std::cout << std::endl;
   //In setting.json, it checks whether the client has set the settings as desired and shuts down the system if the settings are not done correctly.
   bool answerCheck = true;
   while(answerCheck){
      std::cout << "Did you correctly enter the Lampad server information required for DISSH operation? If correct, please enter 'y', if not, enter 'n'. (without '')" << std::endl;
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

   std::cout << std::endl;
   //2. get Lampad Civet7Token for lampad login
   //   Civet7Token is required to use the rest API
   std::string postUrl = lampad.lampadUrl + "/q/login/";
   std::string jsonData = "{\"username\":\""+lampad.lampadId+"\",\"password\":\""+lampad.lampadPassword+"\"}";
   Post post(postUrl, jsonData);
   post.postRequest();

   std::cout << std::endl;
   //3. Retrieve information about lampad-x connected to lampad
   //   The file will be uploaded to lampad-X where responsive is true.
   std::string getUrl = lampad.lampadUrl + "/q/paradox/";
   Get get(getUrl);
   get.getRequest();

   std::cout << std::endl;
   std::vector<std::string> lampadxIpResponsiveTrue;
   std::vector<std::string> lampadxIpResponsiveFalse;
   //4. Assuming that operation 3 has been completed successfully, lampad-X with responsive set to true will be imported from paradox.json.
   jsonParsing.getLampadxIp(lampadxIpResponsiveTrue, lampadxIpResponsiveFalse);
   std::cout << "This is the IP of Lampad-X that is currently connected to the Lampad Server and can communicate with it." << std::endl;
   for(int i = 0; i < lampadxIpResponsiveTrue.size(); i++){
      std::cout << lampadxIpResponsiveTrue[i] << std::endl;
   }
   std::cout << std::endl;
   std::cout << "This is the IP of Lampad-X, which is connected to the Lampad Server but is currently unable to communicate." << std::endl;
   for(int i = 0; i < lampadxIpResponsiveFalse.size(); i++){
      std::cout << lampadxIpResponsiveFalse[i] << std::endl;
   }

   system("pause");

   return 0;

}