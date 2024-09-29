cmake_minimum_required(VERSION 3.30.3)

project(DISSH)

include_directories("curl_x64-windows/include")
link_directories("curl_x64-windows/lib")


include_directories("libssh_x64_windows/include")
link_directories("libssh_x64_windows/lib")

set(JSON_PARSING
JSON_PARSING/JsonParsing.h
JSON_PARSING/JsonParsing.cpp
)

set(REST_API_POST
REST_API_POST/Post.h
REST_API_POST/Post.cpp
)

set(REST_API_GET
REST_API_GET/Get.h
REST_API_GET/Get.cpp
)

MESSAGE ( "\nproject name : " ${CMAKE_PROJECT_NAME} "\n")

add_executable(DISSH

main.cpp
json.hpp

${JSON_PARSING}
${REST_API_POST}
${REST_API_GET}

)

target_link_libraries(DISSH libcurl ssh)
