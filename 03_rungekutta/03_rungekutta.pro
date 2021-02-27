QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    include

HEADERS += \
    include/abstractequationsystem.h \
    include/mainwindow.h \
    include/solutiontablemodel.h \
    include/aboutdialog.h \
    include/helpdialog.h

SOURCES += \
    src/abstractequationsystem.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/solutiontablemodel.cpp \
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
