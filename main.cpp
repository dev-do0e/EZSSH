#include <iostream>

#include "JSON_PARSING/JsonParsing.h"
#include "LIBSSH_SCP/Scp.h"
int main(){
   //Start EZSSH

   //Retrieve Lampad-X information to run EZSSH from setting.json
   //1. Get Lampad-X information from setting.json
   JsonParsing jsonParsing;
   JsonParsing::Lampadx lampadx;
   jsonParsing.getLampadxInfo(lampadx);

   //[시작!]
   std::cout << "EZSSH" << std::endl << std::endl;

   //2.EZSSH를 실행시켰으면 setting.json에 있는 Lampad-X의 정보를 보여줘
   std::cout << "lampad-X ID : " << lampadx.lampadxId << std::endl;
   std::cout << "lampad-X IP : " << lampadx.lampadxIp << std::endl;
   std::cout << "lampad-X PW : " << lampadx.lampadxPw << std::endl << std::endl;

   //3. setting.json의 정보로 Lampad-X에 cage와 Faklient 파일 교체 시작
   Scp scp(lampadx.lampadxIp, lampadx.lampadxId, lampadx.lampadxPw);

   if (!scp.connect()) {
         std::cerr << "Failed to connect to SSH server." << std::endl;
         return -1;
   }

   // 파일 교체 전에 faklient.service 정지
   std::string stopFaklientService = "sudo systemctl stop faklient.service";
   if(!scp.execute_remote_command(stopFaklientService)) {
      std::cerr << "Failed to execute remote command: " << stopFaklientService << std::endl;
   } else {
      std::cout << stopFaklientService << " | success" << std::endl;
   }

   //cage part
   std::cout << std::endl;
   std::cout << "cage part" << std::endl;

   // DISSH로 변경할 cage를 LampadX home 경로에 위치
   if (!scp.transfer_file("./files/cage.exe", "/home/linaro", "cage")) {   
      std::cerr << "Failed to transfer file: " << "./files/cage" << std::endl;
   } else {
      std::cout << "scp ./files/cage.exe " << lampadx.lampadxId << "@" << lampadx.lampadxIp << ":/home/linaro/" << " | success" << std::endl;
   }

   // cage 변경
   std::string mvCage = "sudo mv /home/linaro/cage /Paradox/";
   if(!scp.execute_remote_command(mvCage)) {
      std::cerr << "Failed to execute remote command: " << mvCage << std::endl;
   } else {
      std::cout << mvCage << " | success" << std::endl;
   }

   // cage 권한 변경
   std::string chmodCage = "sudo chmod 755 /Paradox/cage";
   if(!scp.execute_remote_command(chmodCage)) {
      std::cerr << "Failed to execute remote command: " << chmodCage << std::endl;
   } else {
      std::cout << chmodCage << " | success" << std::endl;
   }

   // cage 소유권 변경
   std::string chownCage = "sudo chown root:root /Paradox/cage";
   if(!scp.execute_remote_command(chownCage)) {
      std::cerr << "Failed to execute remote command: " << chownCage << std::endl;
   } else {
      std::cout << chownCage << " | success" << std::endl;
   }

   //Faklient part
   std::cout << std::endl;
   std::cout << "Faklient part" << std::endl;

   // DISSH로 변경할 Faklient를 LampadX home 경로에 위치
   if (!scp.transfer_file("./files/Faklient.exe", "/home/linaro", "Faklient")) {
      std::cerr << "Failed to transfer file: " << "./files/Faklient" << std::endl;
   } else {
      std::cout << "scp ./files/Faklient.exe " << lampadx.lampadxId << "@" << lampadx.lampadxIp << ":/home/linaro/" << " | success" << std::endl;
   }

   // Faklient 변경
   std::string mvFaklient = "sudo mv /home/linaro/Faklient /Paradox/";
   if(!scp.execute_remote_command(mvFaklient)) {
      std::cerr << "Failed to execute remote command: " << mvFaklient << std::endl;
   } else {
      std::cout << mvFaklient << " | success" << std::endl;
   }

   // Faklient 권한 변경
   std::string chmodFaklient = "sudo chmod 755 /Paradox/Faklient";
   if(!scp.execute_remote_command(chmodFaklient)) {
      std::cerr << "Failed to execute remote command: " << chmodFaklient << std::endl;
   } else {
      std::cout << chmodFaklient << " | success" << std::endl;
   }

   // Faklient 소유권 변경
   std::string chownFaklient = "sudo chown root:root /Paradox/Faklient";
   if(!scp.execute_remote_command(chownFaklient)) {
      std::cerr << "Failed to execute remote command: " << chownFaklient << std::endl;
   } else {
      std::cout << chownFaklient << " | success" << std::endl;
   }
      
   std::cout << std::endl;

   // 파일 교체 후에 faklient.service 재시작
   std::string restartFaklientService = "sudo systemctl restart faklient.service";
   if(!scp.execute_remote_command(restartFaklientService)) {
      std::cerr << "Failed to execute remote command: " << restartFaklientService << std::endl;
   } else {
      std::cout << restartFaklientService << " | success" << std::endl;
   }

   system("pause");

   return 0;
}