QT       += core gui

QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    qntp/src/qntp/NtpClient.cpp \
    qntp/src/qntp/NtpReply.cpp \
    timesync.cpp \
    trayicon.cpp

HEADERS += \
    qntp/include/qntp/NtpClient.h \
    qntp/include/qntp/NtpReply.h \
    qntp/include/qntp/QNtp.h \
    qntp/src/qntp/NtpClient.h \
    qntp/src/qntp/NtpPacket.h \
    qntp/src/qntp/NtpReply.h \
    qntp/src/qntp/NtpReply_p.h \
    qntp/src/qntp/NtpTimestamp.h \
    qntp/src/qntp/QNtp.h \
    qntp/src/qntp/config.h \
    timesync.h \
    trayicon.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../res/res.qrc
