#include "WorkerPool.hpp"

WorkerPool::WorkerPool(const unsigned long workersAmount)
        : _workers(workersAmount), _workersAmount(workersAmount) {}

WorkerPool::~WorkerPool() {
    for (auto& worker: _workers) {
        worker.join();
    }
}

void WorkerPool::addConnection(int clientSocketFD) {
    if (++_balancer == _workersAmount) {
        _balancer = 0;
    }

    return _workers[_balancer].addConnection(clientSocketFD);
}

void WorkerPool::run() {
    for (auto& thr: _workers) {
        thr.run();
    }
}
