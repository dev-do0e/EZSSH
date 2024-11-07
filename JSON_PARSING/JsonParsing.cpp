#include "JsonParsing.h"

using json = nlohmann::json;

//parsing lampadx infomation for setting.json before starting program
void JsonParsing::getLampadxInfo(Lampadx &lampadx){

    std::string file = "./setting.json";
    std::ifstream fin(file);

    if(!fin.is_open()){
        std::cout << "JsonParsing error | setting.json does not exist in the path." << std::endl;
        system("pause");
    }

    json j;
    fin >> j;

    lampadx.lampadxId = j["lampadx"]["id"]; 
    lampadx.lampadxIp = j["lampadx"]["ip"]; 
    lampadx.lampadxPw = j["lampadx"]["pw"];

    fin.close();

}
