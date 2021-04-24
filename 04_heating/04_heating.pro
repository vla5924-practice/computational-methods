QT     += core gui widgets printsupport

CONFIG += c++11

INCLUDEPATH += \
    include \
    thirdparty/qcustomplot

HEADERS += \
    include/computation.h \
    include/computationresult.h \
    include/mainwindow.h \
    thirdparty/qcustomplot/qcustomplot.h

SOURCES += \
    src/computation.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    thirdparty/qcustomplot/qcustomplot.cpp

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
