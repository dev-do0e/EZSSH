#ifndef JSONPARSING_H
#define JSONPARSING_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../json.hpp"

class JsonParsing {

    public :
        //get Lampad information
        struct Lampad{
            std::string lampadUrl;
            std::string lampadId;
            std::string lampadPassword;
        };
        void getLampadInfo(Lampad &lampad);

        //get Lampadx information
        struct Lampadx{
            std::string lampadxId;
            std::string lampadxPassword;
        };
        void getLampadxInfo(Lampadx &lampadx);

        //Get the IP of Lampad X where the response is true in parardox.json
        void getLampadxIpResponsiveTrue(std::vector<std::string> &lampadxIpResponsiveTrue);
        void getLampadxIpResponsiveFalse(std::vector<std::string> &lampadxIpResponsiveFalse);

};

#endif