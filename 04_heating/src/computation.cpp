#include "computation.h"

void Computation::run()
{
    emit progressChanged(0, 3);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    emit progressChanged(1, 3);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    emit progressChanged(2, 3);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    emit progressChanged(3, 3);
    emit resultReady();
}

Computation::Computation(QObject *parent) : QThread(parent)
{

}
