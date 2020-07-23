#pragma once

#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <functional>
#include <string>


class CTcpListener {
public:
    using MessageReceivedHandler =
        std::function<void(CTcpListener*, int, std::string const&)>;

public:
    CTcpListener(std::string const& ipAddress, int port,
                 MessageReceivedHandler const& handler);

    // send a message to a specified client
    static void sendMsg(int clientSocket, std::string const& msg);

    // main processing loop
    void run();

private:
    // create a socket
    int createSocket();

    // wait for a connection
    static int waitForConnection(int listeningSocket);

    // data members
    std::string m_ipAddress;
    int m_port;
    MessageReceivedHandler messageReceived;
};