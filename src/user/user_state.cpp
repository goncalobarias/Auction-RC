#include "user_state.hpp"
#include "../lib/messages.hpp"
#include "user.hpp"

#include <cstring>
#include <iostream>
#include <netdb.h>
#include <unistd.h>

void UserState::readOpts(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "n:p:h")) != -1) {
        switch (opt) {
        case 'n':
            this->host = std::string(optarg);
            break;
        case 'p':
            this->port = std::string(optarg);
            break;
        case 'h':
            printHelp(std::cout, argv[0]);
            exit(EXIT_SUCCESS);
        default:
            printHelp(std::cerr, argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}

void UserState::getServerAddresses() {
    struct addrinfo hints;
    int res;
    const char *host_str = host.c_str();
    const char *port_str = port.c_str();

    // Get UDP address
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;      // IPv4
    hints.ai_socktype = SOCK_DGRAM; // UDP socket
    if ((res = getaddrinfo(host_str, port_str, &hints, &this->addrUDP)) != 0) {
        std::cerr << GETADDRINFO_UDP_ERR << gai_strerror(res) << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get TCP address
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    if ((res = getaddrinfo(host_str, port_str, &hints, &this->addrTCP)) != 0) {
        std::cerr << GETADDRINFO_TCP_ERR << gai_strerror(res) << std::endl;
        exit(EXIT_FAILURE);
    }
}

void UserState::openTCPSocket() {
    if ((this->socketTCP = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << SOCKET_CREATE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    struct timeval timeout;
    timeout.tv_sec = TCP_READ_TIMEOUT_SECS;
    timeout.tv_usec = 0;
    if (setsockopt(this->socketTCP, SOL_SOCKET, SO_RCVTIMEO, &timeout,
                   sizeof(timeout)) < 0) {
        std::cerr << SOCKET_TIMEOUT_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = TCP_WRITE_TIMEOUT_SECS;
    if (setsockopt(this->socketTCP, SOL_SOCKET, SO_SNDTIMEO, &timeout,
                   sizeof(timeout)) < 0) {
        std::cerr << SOCKET_TIMEOUT_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
}

void UserState::closeTCPSocket() {
    if (this->socketTCP == -1) {
        return; // socket was already closed
    }
    if (close(this->socketTCP) != 0) {
        std::cerr << SOCKET_CLOSE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    this->socketTCP = -1;
}

void UserState::sendAndReceiveUDPPacket(UDPPacket &packetOut,
                                        UDPPacket &packetIn) {
    (void)packetOut;
    (void)packetIn;
    // TODO: implement
}

void UserState::sendAndReceiveTCPPacket(TCPPacket &packetOut,
                                        TCPPacket &packetIn) {
    (void)packetOut;
    (void)packetIn;
    // TODO: implement
}

UserState::~UserState() {
    if (this->socketUDP != -1) {
        close(this->socketUDP);
    }
    if (this->socketTCP != -1) {
        close(this->socketTCP);
    }
    if (this->addrUDP != NULL) {
        freeaddrinfo(this->addrUDP);
    }
    if (this->addrTCP != NULL) {
        freeaddrinfo(this->addrTCP);
    }
}