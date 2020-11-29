QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    include

SOURCES += \
    src/gaussmethodsolver.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/systemtablemodel.cpp \
    src/solutiontablemodel.cpp

HEADERS += \
    include/gaussmethodsolver.h \
    include/lesystemsolver.h \
    include/mainwindow.h \
    include/matrix.h \
    include/systemtablemodel.h \
    include/solutiontablemodel.h

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
