#include <fstream>
#include <iostream>

#include "Get_response_post_json.h"

using json = nlohmann::json;

void Get_response_post_json::get_lampadx_ip_responsive_true(std::vector<std::string> &lampadx_ip_responsive_true) {

    std::string file = "response_get.json";
    std::ifstream fin(file);

    if(!fin.is_open()){
        std::cout << "responsive_true_lampadx can't open file" << std::endl;
    }

    json j;
    fin >> j;

    for(const auto& lampadx : j){
        if(lampadx["responsive"]){
            lampadx_ip_responsive_true.push_back(lampadx["deviceip"]);
        }
    }

    fin.close();

}

void Get_response_post_json::get_lampadx_ip_responsive_false(std::vector<std::string> &lampadx_ip_responsive_false) {

    std::string file = "response_get.json";
    std::ifstream fin(file);

    if(!fin.is_open()){
        std::cout << "responsive_true_lampadx can't open file" << std::endl;
    }

    json j;
    fin >> j;

    for(const auto& lampadx : j){
        if(!lampadx["responsive"]){
            lampadx_ip_responsive_false.push_back(lampadx["deviceip"]);
        }
    }

    fin.close();

}