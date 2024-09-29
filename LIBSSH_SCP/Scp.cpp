#include "Scp.h"
#include <libssh/sftp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#define S_IRUSR _S_IREAD
#define S_IWUSR _S_IWRITE
#endif

Scp::Scp(const std::string &hostname, const std::string &username, const std::string &password)
    : hostname(hostname), username(username), password(password), session(ssh_new()) {
    if (session == NULL) {
        std::cerr << "Error creating ssh session." << std::endl;
    }
}

Scp::~Scp() {
    if (session != NULL) {
        ssh_free(session);
    }
}

bool Scp::connect() {
    if (session == NULL) {
        return false;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, hostname.c_str());
    ssh_options_set(session, SSH_OPTIONS_USER, username.c_str());

    int rc = ssh_connect(session);
    if (rc != SSH_OK) {
        std::cerr << "Error connecting to " << hostname << ": " << ssh_get_error(session) << std::endl;
        return false;
    }

    rc = ssh_userauth_password(session, NULL, password.c_str());
    if (rc != SSH_AUTH_SUCCESS) {
        std::cerr << "Error authenticating with password: " << ssh_get_error(session) << std::endl;
        ssh_disconnect(session);
        return false;
    }

    return true;
}

bool Scp::transfer_file(const std::string &local_file, const std::string &remote_path, const std::string &file_name) {
    ssh_scp scp = ssh_scp_new(session, SSH_SCP_WRITE | SSH_SCP_RECURSIVE, remote_path.c_str());
    if (scp == NULL) {
        std::cerr << "Error allocating scp session: " << ssh_get_error(session) << std::endl;
        return false;
    }

    if (ssh_scp_init(scp) != SSH_OK) {
        std::cerr << "Error initializing scp session: " << ssh_get_error(session) << std::endl;
        ssh_scp_free(scp);
        return false;
    }

    std::ifstream file(local_file, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << local_file << std::endl;
        ssh_scp_free(scp);
        return false;
    }

    std::streamsize size = file.tellg();
    if (size <= 0) {
        std::cerr << "Error: file is empty or could not get the file size: " << local_file << std::endl;
        ssh_scp_free(scp);
        return false;
    }

    file.seekg(0, std::ios::beg);

    if (ssh_scp_push_file(scp, file_name.c_str(), size, S_IRUSR | S_IWUSR) != SSH_OK) {
        std::cerr << "Error pushing file: " << ssh_get_error(session) << std::endl;
        ssh_scp_free(scp);
        return false;
    }

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        std::cerr << "Error reading file: " << local_file << std::endl;
        ssh_scp_free(scp);
        return false;
    }

    if (ssh_scp_write(scp, buffer.data(), size) != SSH_OK) {
        std::cerr << "Error writing to scp: " << ssh_get_error(session) << std::endl;
        ssh_scp_free(scp);
        return false;
    }

    ssh_scp_close(scp);
    ssh_scp_free(scp);
    return true;
}

bool Scp::execute_remote_command(const std::string &command) {
    ssh_channel channel = ssh_channel_new(session);
    if (channel == NULL) {
        std::cerr << "Error creating ssh channel." << std::endl;
        return false;
    }

    if (ssh_channel_open_session(channel) != SSH_OK) {
        std::cerr << "Error opening ssh channel." << std::endl;
        ssh_channel_free(channel);
        return false;
    }

    if (ssh_channel_request_exec(channel, command.c_str()) != SSH_OK) {
        std::cerr << "Error executing remote command: " << ssh_get_error(session) << std::endl;
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return false;
    }

    ssh_channel_close(channel);
    ssh_channel_free(channel);
    return true;
}

void Scp::disconnect() {
    if (session != NULL) {
        ssh_disconnect(session);
    }
}
