#include "telemetry/service.h"

#include <memory>

#include <QJsonDocument>
#include <QtNetwork/QNetworkRequest>
#include <QSysInfo>

#include "telemetry/config.h"

TelemetryService::TelemetryService(const QString &token)
{
    m_token = token;
    m_manager = nullptr;
}

TelemetryService::~TelemetryService()
{
    if (m_manager != nullptr)
        delete m_manager;
}

void TelemetryService::sendData(const QJsonObject &data)
{
#ifdef ENABLE_TELEMETRY
    QNetworkRequest request(QUrl(TELEMETRY_URL));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    if (m_manager == nullptr)
        m_manager = new QNetworkAccessManager;
    QJsonObject postData = data;
    postData.insert("token", TELEMETRY_TOKEN);
    QJsonObject sysInfo
    {
        { "host_name", QSysInfo::machineHostName() },
        { "unique_id", QString(QSysInfo::machineUniqueId()) },
        { "product_name", QSysInfo::prettyProductName() }
    };
    postData.insert("system_info", sysInfo);
    m_manager->post(request, QJsonDocument(postData).toJson());
#endif
}
