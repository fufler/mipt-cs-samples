#include <iostream>
#include <cassert>
#include <string>

#include <boost/program_options.hpp>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;
namespace bpo = boost::program_options;

constexpr unsigned BUFF_SIZE = 1000;

in_addr_t resolve_address(const string& address) {
    addrinfo hints;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;


    addrinfo *res;

    getaddrinfo(address.c_str(), nullptr, &hints, &res);
    auto s_addr = (reinterpret_cast<sockaddr_in*>(res->ai_addr))->sin_addr.s_addr;

    freeaddrinfo(res);

    return s_addr;
}

int connect_to_server(const string& address, short port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    assert(sockfd != -1);

    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = resolve_address(address);
    serv_addr.sin_port = htons(port);

    int rc = connect(sockfd, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr));

    assert(rc == 0);

    return sockfd;
}

void handle_socks5_handshake(int sockfd, const string &server_address, short server_port) {
    unsigned char b1[] = {5, 1, 0};

    write(sockfd, b1, 3);
    read(sockfd, b1, 2);

    assert(b1[0] == 5);
    assert(b1[1] == 0);

    auto addr = resolve_address(server_address);

    auto paddr = reinterpret_cast<unsigned char*>(&addr);
    auto port = htons(server_port);
    auto pport = reinterpret_cast<unsigned char*>(&port);

    unsigned char b2[] = {5, 1, 0, 1, paddr[0], paddr[1], paddr[2], paddr[3], pport[0], pport[1]};

    write(sockfd, b2, 10);
    read(sockfd, b2, 10);

    assert(b2[0] == 5);
    assert(b2[1] == 0);
}

int main(int argc, char** argv) {

    string proxy_address;
    short proxy_port;

    string server_address;
    short server_port;

    bpo::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("proxy-address", bpo::value<string>(&proxy_address)->default_value(""), "proxy server address")
            ("proxy-port", bpo::value<short>(&proxy_port)->default_value(1080), "proxy server port")
            ("server-address", bpo::value<string>(&server_address)->required(), "HTTP server address")
            ("server-port", bpo::value<short>(&server_port)->default_value(80), "HTTP server port");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }

    int sockfd;

    if (proxy_address.empty()) {
        sockfd = connect_to_server(server_address, server_port);
    } else {
        sockfd = connect_to_server(proxy_address, proxy_port);
        handle_socks5_handshake(sockfd, server_address, server_port);
    }

    string msg = "GET / HTTP/1.1\nHost: " + server_address + "\nConnection: close\n\n";

    write(sockfd, msg.c_str(), strlen(msg.c_str()));

    char buff[BUFF_SIZE+1];

    int sz;
    while ((sz = read(sockfd, buff, BUFF_SIZE)) > 0) {
        buff[sz] = 0;
        cout << buff;
    }

    close(sockfd);
}