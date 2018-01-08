#include "Worker.hpp"
#include "ConnectionInstance.hpp"

void Worker::workerFunction() {
    this->timer.set(this->loop);
    this->timer.set<Worker, &Worker::on_timer>(this);
    this->timer.start(0.1, 0.0001);

    loop.run(0);
}

void Worker::addConnection(int clientSocketFD) {
    new ConnectionInstance(loop, clientSocketFD);
}

void Worker::join() {
    return thread->join();
}


void Worker::run() {
    thread.reset(new std::thread(&Worker::workerFunction, this));
}
