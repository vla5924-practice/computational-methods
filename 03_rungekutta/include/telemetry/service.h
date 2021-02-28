#pragma once

#include <QString>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>

class TelemetryService
{
    QNetworkAccessManager* m_manager;
    QString m_token;

public:
    TelemetryService(const QString& token = "");
    ~TelemetryService();

    void sendData(const QJsonObject& data);
};
