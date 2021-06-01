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
    dialog/commentdialog.cpp \
    dialog/logindialog.cpp \
    dialog/settingdialog.cpp \
    dialog/trackdialog.cpp \
    main.cpp \
    utils/QrCode.cpp \
    utils/global.cpp \
    utils/httpclient.cpp \
    utils/player.cpp \
    utils/toast.cpp \
    window/detailwindow.cpp \
    window/eventwindow.cpp \
    window/findwindow.cpp \
    window/main2window.cpp \
    window/mainwindow.cpp \
    window/searchwindow.cpp \
    window/songlistwindow.cpp \
    window/userinfowindow.cpp

HEADERS += \
    dialog/commentdialog.h \
    dialog/logindialog.h \
    dialog/settingdialog.h \
    dialog/trackdialog.h \
    utils/QrCode.h \
    utils/QrCode.h \
    utils/global.h \
    utils/httpclient.h \
    utils/player.h \
    utils/song.h \
    utils/toast.h \
    window/detailwindow.h \
    window/eventwindow.h \
    window/findwindow.h \
    window/main2window.h \
    window/mainwindow.h \
    window/searchwindow.h \
    window/songlistwindow.h \
    window/userinfowindow.h

FORMS += \
    dialog/commentdialog.ui \
    dialog/logindialog.ui \
    dialog/settingdialog.ui \
    dialog/trackdialog.ui \
    utils/toast.ui \
    window/detailwindow.ui \
    window/eventwindow.ui \
    window/findwindow.ui \
    window/main2window.ui \
    window/mainwindow.ui \
    window/searchwindow.ui \
    window/songlistwindow.ui \
    window/userinfowindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#一次引入自定义控件的所有头文件 懒得个个拷贝
INCLUDEPATH += $$PWD/quc/include

#不同的构建套debug release 依赖不同的链接库
CONFIG(debug, debug|release){
LIBS += -L$$PWD/quc/ -lqucd
} else {
LIBS += -L$$PWD/quc/ -lquc
}

RESOURCES += \
    res.qrc
