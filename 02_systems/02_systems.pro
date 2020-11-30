QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    include

HEADERS += \
    include/firstapproximationtablemodel.h \
    include/gaussmethodsolver.h \
    include/jacobimethodsolver.h \
    include/kramermethodsolver.h \
    include/lesystemsolver.h \
    include/mainwindow.h \
    include/matrix.h \
    include/method.h \
    include/seidelmethodsolver.h \
    include/simpleiterationmethodsolver.h \
    include/solution.h \
    include/systemtablemodel.h \
    include/solutiontablemodel.h \
    include/upperrelaxationmethodsolver.h \
    include/datarequestdialog.h

SOURCES += \
    src/firstapproximationtablemodel.cpp \
    src/gaussmethodsolver.cpp \
    src/jacobimethodsolver.cpp \
    src/kramermethodsolver.cpp \
    src/lesystemsolver.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/matrix.cpp \
    src/seidelmethodsolver.cpp \
    src/simpleiterationmethodsolver.cpp \
    src/systemtablemodel.cpp \
    src/solutiontablemodel.cpp \
    src/upperrelaxationmethodsolver.cpp \
    src/datarequestdialog.cpp

FORMS += \
    ui/datarequestdialog.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
