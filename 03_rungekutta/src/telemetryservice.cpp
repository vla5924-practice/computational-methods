#include "telemetry/service.h"

#include <QJsonDocument>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QSysInfo>

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
    QJsonObject postData = data;
    postData.insert("token", TELEMETRY_TOKEN);
    QJsonObject sysInfo
    {
        { "host_name", QSysInfo::machineHostName() },
        { "unique_id", QString(QSysInfo::machineUniqueId()) },
        { "product_name", QSysInfo::prettyProductName() }
    };
    postData.insert("system_info", sysInfo);
    manager->post(request, QJsonDocument(postData).toJson());
#endif
}
