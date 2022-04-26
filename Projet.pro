QT       += core gui sql charts axcontainer serialport

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
    arduino.cpp \
    avis.cpp \
    connection.cpp \
    donateurs.cpp \
    dons.cpp \
    evenement.cpp \
    excelexporthelper.cpp \
    form.cpp \
    form2.cpp \
    historique.cpp \
    login.cpp \
    mahdi.cpp \
    main.cpp \
    mainwindow.cpp \
    maissa.cpp \
    maraaa.cpp \
    membre.cpp \
    sponsor1.cpp

HEADERS += \
    arduino.h \
    avis.h \
    connection.h \
    donateurs.h \
    dons.h \
    evenement.h \
    excelexporthelper.h \
    form.h \
    form2.h \
    historique.h \
    login.h \
    mahdi.h \
    mainwindow.h \
    maissa.h \
    maraaa.h \
    membre.h \
    sponsor1.h

FORMS += \
    form.ui \
    form2.ui \
    login.ui \
    mahdi.ui \
    mainwindow.ui \
    maissa.ui \
    maraaa.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

