#ifndef IDK_WORKER_HPP
#define IDK_WORKER_HPP


#include <thread>
#include <ev++.h>
#include <iostream>


class Worker {
public:
    explicit Worker() = default;

    explicit Worker(const Worker&) = delete;

    explicit Worker(const Worker&&) = delete;

    Worker& operator=(const Worker&) = delete;

    Worker& operator=(const Worker&&) = delete;

    void run();

    void join();

    void addConnection(int clientSocketFD);

    virtual ~Worker() = default;

    void workerFunction();

private:
    ev::dynamic_loop loop;

    std::unique_ptr<std::thread> thread;

    ev::timer timer;

    void on_timer()
    {
        return;
    }
};


#endif //IDK_WORKER_HPP
