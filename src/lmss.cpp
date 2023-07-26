#include "lmss.hpp"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

namespace letMeSee
{
    int LmssApp::acceptNewConnection(int port)
    {
        int listenFd = socket(AF_INET, SOCK_STREAM, 0);
        if (listenFd == -1)
        {
            std::cout << "error: open socket" << std::endl;
            return 0;
        }

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(listenFd, (struct sockaddr *)(&addr), sizeof(addr)) == -1)
        {
            std::cout << "error: bind" << std::endl;
            return 0;
        }

        if (listen(listenFd, 5) == -1)
        {
            std::cout << "error: listen" << std::endl;
            return 0;
        }

        int connection;
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        while (1)
        {
            connection = accept(listenFd, (struct sockaddr *)(&clientAddr), &clientAddrLen);
            if (connection < 0)
            {
                std::cout << "error: bad connection" << std::endl;
                continue;
            }
            giveConnection(connection);
        }
    }

    void LmssApp::giveConnection(int fd)
    {
        reactors[currentReactorIndex]->addSocketFdToEpoll(fd);
        currentReactorIndex += 1;
        currentReactorIndex =
            currentReactorIndex == reactors.size()
                ? 0
                : currentReactorIndex;
    }
}