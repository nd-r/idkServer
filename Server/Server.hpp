#ifndef IDK_SERVER_HPP
#define IDK_SERVER_HPP

#include "Config.hpp"
#include "../Pool/WorkerPool.hpp"
#include <ev++.h>

namespace idk {
    class Server {
    public:
        explicit Server();

        Server(const Server&) = delete;

        Server(const Server&&) = delete;

        Server& operator=(const Server&) = delete;

        Server& operator=(const Server&&) = delete;

        virtual ~Server();

        void run();

        static void signalCb(ev::sig& signal, int revents);

    private:
        idk::server::Config cfg;

        ev::default_loop loop;
        ev::io watcher;
        ev::sig signalSIGINT;

        idk::pool::WorkerPool _workerPool;

        int socketFD;

        void acceptCb(ev::io& watcher, int revents);
    };
}

#endif //IDK_SERVER_HPP
