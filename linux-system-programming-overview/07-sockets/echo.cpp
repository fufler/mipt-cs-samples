#include <iostream>
#include <cassert>

#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>

using namespace std;

constexpr int BUF_SIZE = 1024;
constexpr int PORT = 12345;

void server(char* address)
{
    char buffer[BUF_SIZE+1];
    struct sockaddr_in serv_addr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, address, &serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    listen(sockfd, 0);

    while (true)
    {
        int newsockfd = accept(sockfd, nullptr, nullptr);

        int n = read(newsockfd, buffer, BUF_SIZE);
        buffer[n] = 0;

        write(newsockfd, buffer, n);

        close(newsockfd);

        if ((n == 4) && !strcmp("quit", buffer))
            break;
    }

    close(sockfd);
}

void client(char* address)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    char buf[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, address, &serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(PORT);

    connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

    string s;

    cout << ">>> ";
    cin >> s;

    write(sockfd, s.c_str(), strlen(s.c_str()));
    int n = read(sockfd, buf, BUF_SIZE);
    buf[n] = 0;

    cout << buf << endl;

    close(sockfd);
}

int main(int argc, char** argv)
{
    assert(argc == 3);

    bool client_mode, server_mode;

    if (!strcmp("server", argv[1]))
        server_mode = true;
    else
        if (!strcmp("client", argv[1]))
            client_mode = true;

    assert(client_mode || server_mode);

    if (client_mode)
        client(argv[2]);
    else
        server(argv[2]);

    return 0;
}
