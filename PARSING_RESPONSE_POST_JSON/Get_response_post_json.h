#ifndef __GET_RESPONSE_POST_JSON_H_
#define __GET_RESPONSE_POST_JSON_H_

#include <iostream>
#include <vector>

#include "../json.hpp"

class Get_response_post_json {
    public :
        void get_lampadx_ip_responsive_true(std::vector<std::string> &lampadx_ip_responsive_true);

        void get_lampadx_ip_responsive_false(std::vector<std::string> &lampadx_ip_responsive_false);
        
};
#endif