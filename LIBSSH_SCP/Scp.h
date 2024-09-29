#ifndef SCP_H
#define SCP_H

#include <libssh/libssh.h>
#include <string>

class Scp {
public:
    Scp(const std::string &hostname, const std::string &username, const std::string &password);
    ~Scp();

    bool connect();
    bool transfer_file(const std::string &local_file, const std::string &remote_path, const std::string &file_name);
    bool execute_remote_command(const std::string &command);
    void disconnect();

private:
    ssh_session session;
    std::string hostname;
    std::string username;
    std::string password;
};

#endif // SCP_UTILS_H
