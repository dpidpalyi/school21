QT       += core gui

win32 {
    LIBS += -lopengl32
}

include(QtGifImage/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets openglwidgets gui

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../lib/s21_helpers.c \
    ../lib/s21_parse_file.c \
    ../lib/s21_transformations.c \
    main.cpp \
    mainwindow.cpp \
    oglwidget.cpp

HEADERS += \
    ../lib/s21_3DViewer.h \
    ../lib/s21_helpers.h \
    ../lib/s21_model.h \
    ../lib/s21_parse_file.h \
    ../lib/s21_transformations.h \
    mainwindow.h \
    oglwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
