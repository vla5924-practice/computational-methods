#include "mvlatelemetry.h"


MVlaTelemetry::MVlaTelemetry(const QString &token)
{
    m_token = token;
}

void MVlaTelemetry::setToken(const QString &token)
{
    m_token = token;
}

void MVlaTelemetry::sendData(const QJsonObject &data)
{
    QNetworkRequest request(QUrl("https://mvla.ru/experiments/egamov-telemetry/?token=" + m_token));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    manager->post(request, QJsonDocument(data).toJson());
}
