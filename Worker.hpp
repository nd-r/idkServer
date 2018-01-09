#ifndef IDK_WORKER_HPP
#define IDK_WORKER_HPP


#include <thread>
#include <ev++.h>
#include <iostream>

namespace idk::pool {
    class Worker {
    public:
        explicit Worker();

        explicit Worker(const Worker&) = delete;

        explicit Worker(const Worker&&) = delete;

        Worker& operator=(const Worker&) = delete;

        Worker& operator=(const Worker&&) = delete;

        void run();

        void join();

        void addConnection(int clientSocketFD);

        virtual ~Worker() = default;

        void workerFunction();

        size_t currentConnections();

    private:
        size_t connectionsHandling = 0;

        ev::dynamic_loop loop;
        ev::async notifier;
        ev::async connectionGone;

        std::unique_ptr<std::thread> thread;

        void notifyCB(ev::async& notifier, int revents);

        void connectionGoneCB(ev::async& notifier, int revents);
    };
}

#endif //IDK_WORKER_HPP
