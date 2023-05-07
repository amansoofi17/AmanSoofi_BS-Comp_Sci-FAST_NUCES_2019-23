QT       += core gui sql

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
    add_items.cpp \
    admin.cpp \
    business_account.cpp \
    categories_items.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    ratings.cpp \
    shop.cpp \
    show_acc_info.cpp \
    show_items.cpp \
    signup.cpp

HEADERS += \
    add_items.h \
    admin.h \
    business_account.h \
    categories_items.h \
    global.h \
    mainwindow.h \
    ratings.h \
    shop.h \
    show_acc_info.h \
    show_items.h \
    signup.h

FORMS += \
    add_items.ui \
    admin.ui \
    business_account.ui \
    categories_items.ui \
    global.ui \
    mainwindow.ui \
    ratings.ui \
    shop.ui \
    show_acc_info.ui \
    show_items.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \
    databaseform.qrc \
    imageresource.qrc \
    signup.qrc
