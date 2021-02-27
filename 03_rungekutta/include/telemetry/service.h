#pragma once

#include <QString>
#include <QJsonObject>

class TelemetryService
{
    QString m_token;

public:
    TelemetryService(const QString& token = "");
    ~TelemetryService() = default;

    void sendData(const QJsonObject& data);
};
