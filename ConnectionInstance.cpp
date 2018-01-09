#include "ConnectionInstance.hpp"
#include <unistd.h>

#define bufferSize 1024

namespace idk::instances {
    ConnectionInstance::ConnectionInstance(ev::dynamic_loop& loop, int socketFD, ev::async& destroyNotifier)
            : watcher(loop), destroyNotifier(destroyNotifier), socketFD(socketFD) {
        watcher.set<ConnectionInstance, &ConnectionInstance::dispatcher>(this);
        watcher.start(socketFD, ev::READ);
    }

    ConnectionInstance::~ConnectionInstance() {
        destroyNotifier.send();
        watcher.stop();
        close(socketFD);
    }

    void ConnectionInstance::dispatcher(ev::io& watcher, int revents) {
        if (revents & EV_ERROR) {
#if(LOGGING_LEVEL > 0)
            perror("Invalid event in connection instances");
#endif
            return;
        }

        if (revents & EV_READ) {
            readCB(watcher);
        }

        watcher.set(ev::READ);
    }

    void ConnectionInstance::readCB(ev::io& watcher) {
        char buffer[bufferSize];

        volatile int i = 1;

        for (int j = 0; j < 380000; j++) {
            ++i;
            i = i << 2 >> 2;
        }

        ssize_t nRead = read(watcher.fd, buffer, bufferSize);

        if (nRead > 0) {
            write(watcher.fd, "HTTP/1.1 200 OK\r\nContent-length: 0\r\n\r\n", 38);
        } else if (nRead == 0) {
            delete this;
        } else {
#if (LOGGING_LEVEL > 1)
            perror("Error while reading");
#endif
        }

        watcher.set(EV_READ);
    }
}