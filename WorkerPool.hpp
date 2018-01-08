#ifndef IDK_WORKERPOOL_HPP
#define IDK_WORKERPOOL_HPP


#include "Worker.hpp"
#include <vector>

class WorkerPool {
public:
    explicit WorkerPool(unsigned long workersAmount);

    virtual ~WorkerPool();

    explicit WorkerPool() = delete;

    WorkerPool(const WorkerPool&) = delete;

    WorkerPool(const WorkerPool&&) = delete;

    WorkerPool& operator=(const WorkerPool&) = delete;

    WorkerPool& operator=(const WorkerPool&&) = delete;

    void addConnection(int clientSocketFD);

    void run();

private:
    std::vector<Worker> _workers;
    size_t _workersAmount;
    size_t _balancer = 0;
};


#endif //IDK_WORKERPOOL_HPP
