#ifndef JSONPARSING_H
#define JSONPARSING_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../json.hpp"

class JsonParsing {

    public :
        //get Lampadx information
        struct Lampadx{
            std::string lampadxId;
            std::string lampadxIp;
            std::string lampadxPw;
        };
        void getLampadxInfo(Lampadx &lampadx);

};

#endif