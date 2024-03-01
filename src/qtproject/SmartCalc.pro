QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/creditcalc.cc \
    ../model/creditdeposerror.cc \
    ../model/deposcalc.cc \
    ../model/maincalc.cc \
    ../model/plotcalc.cc \
    ../controller/creditcalccontroller.cc \
    ../controller/deposcalccontroller.cc \
    ../controller/maincalccontroller.cc \
    ../controller/plotcalccontroller.cc \
    ../view/creditcalcwindow.cc \
    ../view/deposcalcwindow.cc \
    ../view/main.cc \
    ../view/maincalcwindow.cc \
    ../view/plotwindow.cc \
    ../view/replenismentwindow.cc \
    qcustomplot.cc

HEADERS += \
    ../model/creditcalc.h \
    ../model/creditdeposerror.h \
    ../model/deposcalc.h \
    ../model/maincalc.h \
    ../model/plotcalc.h \
    ../controller/creditcalccontroller.h \
    ../controller/deposcalccontroller.h \
    ../controller/maincalccontroller.h \
    ../controller/plotcalccontroller.h \
    ../view/creditcalcwindow.h \
    ../view/deposcalcwindow.h \
    ../view/main.h \
    ../view/maincalcwindow.h \
    ../view/plotwindow.h \
    ../view/replenismentwindow.h \
    qcustomplot.h

FORMS += \
    creditcalcwindow.ui \
    deposcalcwindow.ui \
    maincalcwindow.ui \
    plotwindow.ui \
    replenismentwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
