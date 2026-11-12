QT       += core gui widgets
CONFIG   += c++17

TARGET = COMP3000Project
TEMPLATE = app

SOURCES += \
    ingredient.cpp \
    main.cpp \
    mainwindow.cpp \
    loginwidget.cpp \
    placeordercontrol.cpp \
    rolehomewidget.cpp \
    useridentificationcontrol.cpp \
    systemdata.cpp \
    defaultdata.cpp \
    user.cpp \
    customer.cpp \
    menu.cpp \
    menuitem.cpp \
    order.cpp \
    orderhistory.cpp \
    orderqueue.cpp \
    viewmenu.cpp \
    featurepage.cpp \
    dashboardcontrol.cpp \
    viewdashboard.cpp \
    viewqueuecontrol.cpp \
    viewqueue.cpp

HEADERS += \
    ingredient.h \
    mainwindow.h \
    loginwidget.h \
    placeordercontrol.h \
    rolehomewidget.h \
    useridentificationcontrol.h \
    systemdata.h \
    defaultdata.h \
    user.h \
    staff.h \
    customer.h \
    menu.h \
    menuitem.h \
    order.h \
    orderhistory.h \
    orderqueue.h \
    viewmenu.h \
    featurepage.h \
    dashboardcontrol.h \
    viewdashboard.h \
    viewqueuecontrol.h \
    viewqueue.h

FORMS += \
    PlaceOrder.ui \
    ViewMenu.ui
