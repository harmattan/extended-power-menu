TEMPLATE = app
TARGET = harmattan-power-menu
QT += dbus

target.path = /usr/bin
INSTALLS += target

CONFIG += link_pkgconfig
PKGCONFIG += meegotouch meegotouch-boostable
INCLUDEPATH += /usr/include/meegotouch

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    extended-power-menu.conf \
    qtc_packaging/debian_harmattan/postinst \
    qtc_packaging/debian_harmattan/prerm

SOURCES += \
    main.cpp \
    powermenu.cpp \
    powerbuttonlistener.cpp \
    msignallingwindow.cpp \
    x11wrapper.cpp \
    profileclient.cpp

HEADERS += \
    powermenu.h \
    powerbuttonlistener.h \
    msignallingwindow.h \
    x11wrapper.h \
    profileclient.h

autostart.path = /etc/init/apps
autostart.files = extended-power-menu.conf

INSTALLS += autostart
