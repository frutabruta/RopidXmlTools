QT       += core gui
QT += sql
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    XmlRopidImportStream/xmlropidimportstream.cpp \
    main.cpp \
    mainwindow.cpp \
    sqldotazymodel.cpp \
    sqlpraceropid.cpp \
    VDV301struktury/spoj.cpp \
    VDV301struktury/linka.cpp \
    VDV301struktury/obeh.cpp \
    VDV301struktury/pasmo.cpp \
    VDV301struktury/zastavka.cpp \
    VDV301struktury/zastavkacil.cpp

HEADERS += \
    XmlRopidImportStream/xmlropidimportstream.h \
    mainwindow.h \
    sqldotazymodel.h \
    sqlpraceropid.h \
    VDV301struktury/spoj.h \
    VDV301struktury/linka.h \
    VDV301struktury/obeh.h \
    VDV301struktury/pasmo.h \
    VDV301struktury/zastavka.h \
    VDV301struktury/zastavkacil.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
