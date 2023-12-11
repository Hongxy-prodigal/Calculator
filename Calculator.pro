QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    currency.cpp \
    dateapart.cpp \
    datecalculator.cpp \
    dateoperate.cpp \
    main.cpp \
    mainwindow.cpp \
    programmercalculator.cpp \
    scientificcalculator.cpp \
    standardcalculator.cpp

HEADERS += \
    currency.h \
    dateapart.h \
    datecalculator.h \
    dateoperate.h \
    mainwindow.h \
    programmercalculator.h \
    scientificcalculator.h \
    standardcalculator.h

FORMS += \
    currency.ui \
    dateapart.ui \
    datecalculator.ui \
    dateoperate.ui \
    mainwindow.ui \
    programmercalculator.ui \
    scientificcalculator.ui \
    standardcalculator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
