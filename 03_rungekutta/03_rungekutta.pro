QT       += core gui widgets network

CONFIG += c++11

INCLUDEPATH += \
    include

HEADERS += \
    include/abstractequationsystem.h \
    include/mainwindow.h \
    include/myequationsystem.h \
    include/rkmethodsolver.h \
    include/solutiontablemodel.h \
    include/aboutdialog.h \
    include/helpdialog.h \
    include/telemetry/config.h \
    include/telemetry/inc.h \
    include/telemetry/service.h

SOURCES += \
    src/abstractequationsystem.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/myequationsystem.cpp \
    src/rkmethodsolver.cpp \
    src/solutiontablemodel.cpp \
    src/telemetryservice.cpp \
    src/aboutdialog.cpp \
    src/helpdialog.cpp

FORMS += \
    ui/mainwindow.ui \
    ui/aboutdialog.ui \
    ui/helpdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
