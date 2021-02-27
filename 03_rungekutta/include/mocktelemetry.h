#pragma once

#include "abstracttelemetry.h"

class MockTelemetry : public AbstractTelemetry
{
public:
    MockTelemetry() = default;
    ~MockTelemetry() = default;

    void setToken(const QString&) {};
    void sendData(const QJsonObject&) {};
};
