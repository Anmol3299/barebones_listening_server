#include <iostream>

#include "../include/CQuoteDay.hpp"
#include "../include/TcpListener.hpp"


void listenerMessageReceived(CTcpListener* listener, int client,
                             std::string const& msg);

static CQuoteDay quote(
    "/mnt/c/Users/mitta/coding_stuff/listener_server/"
    "wisdom.txt");

int main() {
    std::string ip = "127.0.0.1";
    int port = 54000;
    CTcpListener server(ip, port, listenerMessageReceived);

    server.run();


    return 0;
}

void listenerMessageReceived(CTcpListener* listener, int client,
                             std::string const& msg) {
    std::cout << msg << '\n';

    listener->sendMsg(client, quote.getRandomQuote());
}