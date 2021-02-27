#pragma once

#include <QString>
#include <QJsonObject>

class AbstractTelemetry
{
public:
    AbstractTelemetry() = default;
    virtual ~AbstractTelemetry() = default;

    virtual void setToken(const QString& token) = 0;
    virtual void sendData(const QJsonObject& data) = 0;
};
