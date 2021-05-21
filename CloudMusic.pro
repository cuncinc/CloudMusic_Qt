QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    detailwindow.cpp \
    eventwindow.cpp \
    findwindow.cpp \
    httpclient.cpp \
    logindialog.cpp \
    loginwindow.cpp \
    main.cpp \
    main2window.cpp \
    mainwindow.cpp \
    mewindow.cpp \
    player.cpp \
    searchwindow.cpp \
    songlistwindow.cpp

HEADERS += \
    detailwindow.h \
    eventwindow.h \
    findwindow.h \
    httpclient.h \
    logindialog.h \
    loginwindow.h \
    main2window.h \
    mainwindow.h \
    mewindow.h \
    player.h \
    searchwindow.h \
    songlistwindow.h

FORMS += \
    detailwindow.ui \
    eventwindow.ui \
    findwindow.ui \
    logindialog.ui \
    loginwindow.ui \
    main2window.ui \
    mainwindow.ui \
    mewindow.ui \
    searchwindow.ui \
    songlistwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#�次�引入自定义控件的所有头文件 懒得�个个拷贝
INCLUDEPATH += $$PWD/quc/include

#不同的构建套�debug release 依赖不同的链接库
CONFIG(debug, debug|release){
LIBS += -L$$PWD/quc/ -lqucd
} else {
LIBS += -L$$PWD/quc/ -lquc
}

RESOURCES += \
    res.qrc
