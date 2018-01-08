#include "Server.hpp"
#include "utils.hpp"
#include <unistd.h>
#include <netinet/in.h>


Server::Server() : watcher(loop), _workerPool(2), socketFD(socket(PF_INET, SOCK_STREAM, 0)) {
    if (socketFD < 0) {
#if(LOGGING_LEVEL > 0)
        perror("Failed to open file descriptor");
#endif
        return;
    }

    struct sockaddr_in addr{};
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketFD, (struct sockaddr*) &addr, sizeof(addr)) != 0) {
#if(LOGGING_LEVEL > 0)
        perror("Falied to bind");
#endif
        return;
    }

    setNonblocking(socketFD);

    listen(socketFD, SOMAXCONN);

    watcher.set<Server, &Server::acceptCb>(this);
    watcher.start(socketFD, ev::READ);

    signalSIGINT.set<&Server::signalCb>();
    signalSIGINT.start(SIGINT);
}

Server::~Server() {
    shutdown(socketFD, SHUT_RDWR);
    close(socketFD);
}

void Server::run() {
    _workerPool.run();
    loop.run(0);
}

void Server::acceptCb(ev::io& watcher, int revents) {
    if (revents & EV_ERROR) {
#if(LOGGING_LEVEL > 1)
        perror("Wrong event");
#endif
        return;
    }

    struct sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    int clientSocketFD = accept(watcher.fd, (struct sockaddr*) &clientAddr, &clientLen);
    setNonblocking(clientSocketFD);

    _workerPool.addConnection(clientSocketFD);
}

void Server::signalCb(ev::sig& signal, int revents) {
    UNUSED(revents);
    signal.loop.break_loop();
}
