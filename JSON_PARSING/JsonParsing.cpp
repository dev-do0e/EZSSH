#include "JsonParsing.h"

using json = nlohmann::json;

//parsing lampad infomation for setting.json before starting program
void JsonParsing::getLampadInfo(Lampad &lampad){

    std::string file = "json/setting.json";
    std::ifstream fin(file);

    if(!fin.is_open()){
        std::cout << "JsonParsing error | setting.json does not exist in the path." << std::endl;
        system("pause");
    }

    json j;
    fin >> j;
    
    lampad.lampadUrl = j["lampad"]["url"];
    lampad.lampadId = j["lampad"]["id"];
    lampad.lampadPassword = j["lampad"]["password"];

    fin.close();

}

//parsing lampadx infomation for setting.json before starting program
void JsonParsing::getLampadxInfo(Lampadx &lampadx){

    std::string file = "json/setting.json";
    std::ifstream fin(file);

    if(!fin.is_open()){
        std::cout << "JsonParsing error | setting.json does not exist in the path." << std::endl;
        system("pause");
    }

    json j;
    fin >> j;

    lampadx.lampadxId = j["lampad"]["id"];
    lampadx.lampadxPassword = j["lampad"]["password"];

    fin.close();

}

void JsonParsing::getLampadxIp(std::vector<std::string> &lampadxIpResponsiveTrue, std::vector<std::string> &lampadxIpResponsiveFalse){

    std::string file = "json/paradox.json";
    std::ifstream fin(file);

    if(!fin.is_open()){
        std::cout << "JsonParsing error | paradox.json does not exist in the path." << std::endl;

    }

    json j;
    fin >> j;

    for(const auto& lampadx : j){
        if(lampadx["responsive"]){
            lampadxIpResponsiveTrue.push_back(lampadx["deviceip"]);
        }else if(!lampadx["responsive"]){
            lampadxIpResponsiveFalse.push_back(lampadx["deviceip"]);
        }
    }

    fin.close();

}