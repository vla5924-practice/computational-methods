#include "telemetry/service.h"

#include <QJsonDocument>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

#include "telemetry/config.h"

TelemetryService::TelemetryService(const QString &token)
{
    m_token = token;
}

void TelemetryService::sendData(const QJsonObject &data)
{
#ifdef ENABLE_TELEMETRY
    QNetworkRequest request(QUrl(TELEMETRY_URL));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    manager->post(request, QJsonDocument(data).toJson());
#endif
}
