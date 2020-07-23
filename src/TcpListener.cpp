#include "../include/TcpListener.hpp"


static constexpr size_t MAX_BUFFER_SIZE = 49152;

CTcpListener::CTcpListener(std::string const& ipAddress, int port,
                           MessageReceivedHandler const& handler)
    : m_ipAddress(ipAddress), m_port(port), messageReceived(handler) {}

// create a socket
int CTcpListener::createSocket() {
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
        perror("Can't create a socket ");
        return -1;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

    auto bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));
    if (bindOk == -1) {
        perror("Can't bind to IP / port ");
        close(listening);
        return -1;
    }

    auto listenOk = listen(listening, SOMAXCONN);
    if (listenOk == -1) {
        perror("Can't listen ");
        close(listening);
        return -1;
    }

    return listening;
}

// wait for a connection
int CTcpListener::waitForConnection(int listeningSocket) {
    return accept(listeningSocket, NULL, NULL);
}

// send a message to a specified client
void CTcpListener::sendMsg(int clientSocket, std::string const& msg) {
    send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}

// main processing loop
void CTcpListener::run() {
    char buf[MAX_BUFFER_SIZE];

    while (true) {
        int listening = createSocket();
        if (listening == -1) {
            break;
        }

        int client = waitForConnection(listening);
        close(listening);
        if (client == -1) {
            perror("Problem with connecting to client ");
            break;
        }

        int bytesRecv = 0;
        do {
            memset(buf, 0, MAX_BUFFER_SIZE);

            bytesRecv = recv(client, buf, MAX_BUFFER_SIZE, 0);
            if (bytesRecv > 0 && messageReceived != NULL) {
                messageReceived(this, client, std::string(buf, 0, bytesRecv));
            }
        } while (bytesRecv > 0);

        close(client);
    }
}
