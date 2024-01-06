QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    capacity.cpp \
    currency.cpp \
    dateapart.cpp \
    datecalculator.cpp \
    dateoperate.cpp \
    main.cpp \
    mainwindow.cpp \
    painting.cpp \
    programmercalculator.cpp \
    qcustomplot.cpp \
    scientificcalculator.cpp \
    standardcalculator.cpp \
    tinyexpr.c

HEADERS += \
    capacity.h \
    currency.h \
    dateapart.h \
    datecalculator.h \
    dateoperate.h \
    mainwindow.h \
    painting.h \
    programmercalculator.h \
    qcustomplot.h \
    scientificcalculator.h \
    standardcalculator.h \
    tinyexpr.h

FORMS += \
    capacity.ui \
    currency.ui \
    dateapart.ui \
    datecalculator.ui \
    dateoperate.ui \
    mainwindow.ui \
    painting.ui \
    programmercalculator.ui \
    scientificcalculator.ui \
    standardcalculator.ui

RC_ICONS = app.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    calculator.qrc


