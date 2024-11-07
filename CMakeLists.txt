cmake_minimum_required(VERSION 3.30.3)

project(EZSSH)

include_directories("curl_x64-windows/include")
link_directories("curl_x64-windows/lib")

include_directories("libssh_x64_windows/include")
link_directories("libssh_x64_windows/lib")

MESSAGE ( "\nproject name : " ${CMAKE_PROJECT_NAME} "\n")

set(JSON_PARSING
JSON_PARSING/JsonParsing.h
JSON_PARSING/JsonParsing.cpp
)

set(LIBSSH_SCP
LIBSSH_SCP/Scp.h
LIBSSH_SCP/Scp.cpp
)

add_executable(EZSSH

${JSON_PARSING}
${LIBSSH_SCP}

main.cpp
json.hpp

)

target_link_libraries(EZSSH ssh)