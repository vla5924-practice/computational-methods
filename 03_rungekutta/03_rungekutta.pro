QT     += core gui widgets printsupport

CONFIG += c++11

INCLUDEPATH += \
    include \
    thirdparty/qcustomplot

HEADERS += \
    include/abstractequationsystem.h \
    include/abstractaccuratesolution.h \
    include/mainwindow.h \
    include/myequationsystem.h \
    include/myaccuratesolution.h \
    include/rkmethodsolver.h \
    include/solutiontablemodel.h \
    include/aboutdialog.h \
    thirdparty/qcustomplot/qcustomplot.h \
    include/plotsdialog.h

SOURCES += \
    src/abstractequationsystem.cpp \
    src/abstractaccuratesolution.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/myequationsystem.cpp \
    src/rkmethodsolver.cpp \
    src/solutiontablemodel.cpp \
    src/aboutdialog.cpp \
    src/myaccuratesolution.cpp \
    thirdparty/qcustomplot/qcustomplot.cpp \
    src/plotsdialog.cpp

FORMS += \
    ui/mainwindow.ui \
    ui/aboutdialog.ui \
    ui/plotsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
