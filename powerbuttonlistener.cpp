#include "powerbuttonlistener.h"

PowerButtonListener::PowerButtonListener(QObject *parent) :
    QObject(parent)
{
    // signal sender=:1.3 -> dest=(null destination) serial=1125 path=/com/nokia/mce/request; interface=com.nokia.mce.request; member=powerkey_long_ind

    QDBusConnection::systemBus().connect("", "/com/nokia/mce/request", "com.nokia.mce.request", "powerkey_long_ind", this, SIGNAL(powerButtonLongPressed()));
    QDBusConnection::systemBus().connect("", "/com/nokia/mce/request", "com.nokia.mce.request", "powerkey_double_ind", this, SIGNAL(powerButtonDoubleClicked()));
}
