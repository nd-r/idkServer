#ifndef IDK_CONNECTIONINSTANCE_HPP
#define IDK_CONNECTIONINSTANCE_HPP


#include <ev++.h>

namespace idk::instances {
    class ConnectionInstance {
    public:
        ConnectionInstance() = delete;

        ConnectionInstance(ev::dynamic_loop& loop, int socketFD, ev::async& destroyNotifier);

        virtual ~ConnectionInstance();

    private:
        ev::io watcher;
        ev::async& destroyNotifier;
        int socketFD;

        void dispatcher(ev::io& watcher, int revents);

        void readCB(ev::io& watcher);
    };

}
#endif //IDK_CONNECTIONINSTANCE_HPP
