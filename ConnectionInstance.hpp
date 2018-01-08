#ifndef IDK_CONNECTIONINSTANCE_HPP
#define IDK_CONNECTIONINSTANCE_HPP


#include <ev++.h>

class ConnectionInstance {
public:
    ConnectionInstance() = delete;

    ConnectionInstance(ev::dynamic_loop& loop, int socketFD);

    ConnectionInstance(ev::default_loop& loop, int socketFD);

    virtual ~ConnectionInstance();

private:
    ev::io watcher;
    int socketFD;

    void dispatcher(ev::io& watcher, int revents);

    void readCB(ev::io& watcher);
};


#endif //IDK_CONNECTIONINSTANCE_HPP
