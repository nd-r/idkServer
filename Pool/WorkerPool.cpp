#include "WorkerPool.hpp"

namespace idk::pool {
    WorkerPool::WorkerPool(const unsigned long workersAmount)
            : _workers(workersAmount), _workersAmount(workersAmount) {}

    WorkerPool::~WorkerPool() {
        for (auto& worker: _workers) {
            worker.join();
        }
    }

    void WorkerPool::addConnection(int clientSocketFD) {
        size_t minConnections = _workers[0].currentConnections();
        unsigned long workerIdx = 0;

        for (unsigned long i = 1; i < _workersAmount; ++i) {
            auto workerConns = _workers[i].currentConnections();
            if (minConnections > workerConns) {
                minConnections = workerConns;
                workerIdx = i;
            }
        }

        return _workers[workerIdx].addConnection(clientSocketFD);
    }

    void WorkerPool::run() {
        for (auto& thr: _workers) {
            thr.run();
        }
    }
}