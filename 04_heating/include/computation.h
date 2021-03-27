#pragma once

#include <QThread>
#include <thread>

class Computation : public QThread
{
    Q_OBJECT

    void run() override;

public:
    Computation(QObject* parent = nullptr);
    ~Computation() = default;

signals:
    void progressChanged(int current, int total);
    void resultReady();
};
