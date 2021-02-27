#pragma once

#include "telemetry/config.h"

#ifdef ENABLE_TELEMETRY

#include "telemetry/service.h"
TelemetryService qTelemetryService(TELEMETRY_TOKEN);
#define SEND_TELEMETRY(QJSONOBJECT) qTelemetryService.sendData(QJSONOBJECT)
#define SEND_TELEMETRY_ACTION(ACTION) qTelemetryService.sendData(QJsonObject{{ "action", (ACTION) }})

#else

#define SEND_TELEMETRY(QJSONOBJECT)
#define SEND_TELEMETRY_ACTION(ACTION)

#endif
