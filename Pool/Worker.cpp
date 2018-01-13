#include "Worker.hpp"
#include "../Server/ConnectionInstance.hpp"
#include "../utils/utils.hpp"

using idk::instances::ConnectionInstance;

namespace idk::pool {
    void Worker::workerFunction() {
        notifier.start();
        loop.run(0);
    }

    void Worker::addConnection(int clientSocketFD) {
        new ConnectionInstance(loop, clientSocketFD, connectionGone);
        notifier.send();
    }

    void Worker::join() {
        return thread->join();
    }


    void Worker::run() {
        thread.reset(new std::thread(&Worker::workerFunction, this));
    }

    Worker::Worker() : notifier(loop), connectionGone(loop) {
        notifier.set<Worker, &Worker::notifyCB>(this);
        connectionGone.set<Worker, &Worker::connectionGoneCB>(this);
    }

    void Worker::notifyCB(ev::async& notifier, int revents) {
        UNUSED(notifier);
        UNUSED(revents);
        ++connectionsHandling;
    }

    void Worker::connectionGoneCB(ev::async& notifier, int revents) {
        UNUSED(notifier);
        UNUSED(revents);
        --connectionsHandling;
    }

    size_t Worker::currentConnections() {
        return connectionsHandling;
    }
}