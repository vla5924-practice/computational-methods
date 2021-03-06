QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    include

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pointdialog.cpp \
    src/spline.cpp \
    src/splinechart.cpp \
    src/aboutdialog.cpp \
    src/loadingdialog.cpp \
    src/helpdialog.cpp

HEADERS += \
    include/mainwindow.h \
    include/pointdialog.h \
    include/spline.h \
    include/splinechart.h \
    include/aboutdialog.h \
    include/loadingdialog.h \
    include/helpdialog.h

FORMS += \
    ui/aboutdialog.ui \
    ui/helpdialog.ui \
    ui/loadingdialog.ui \
    ui/mainwindow.ui \
    ui/pointdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
