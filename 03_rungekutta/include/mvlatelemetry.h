#pragma once

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>

#include "abstracttelemetry.h"

class MVlaTelemetry : public AbstractTelemetry
{
    QString m_token;

public:
    MVlaTelemetry(const QString& token = "");
    ~MVlaTelemetry() = default;

    void setToken(const QString& token);
    void sendData(const QJsonObject& data);
};
