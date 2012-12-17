#include "profileclient.h"

ProfileClient::ProfileClient(QObject *parent) : QObject(parent)
{
    qDBusRegisterMetaType<ProfileDataValue>();
    qDBusRegisterMetaType<QList<ProfileDataValue> >();

    QDBusConnection::sessionBus().connect("", "",PROFILED_INTERFACE, PROFILED_PROFILE_CHANGED,
                                          this, SLOT(onProfileChanged(bool, bool, QString, QList<ProfileDataValue>)));
}

void ProfileClient::onProfileChanged(bool changed, bool active, QString profile, QList<ProfileDataValue> values)
{
    if (changed && active) {
        m_activeProfile = profile;
        emit profileChanged(profile);
    }

    foreach (const ProfileDataValue &value, values) {
        emit propertyChanged(profile, value.key, value.val);
    }
}

bool ProfileClient::setProfile(QString profileName)
{
    QDBusInterface dbus_iface(PROFILED_SERVICE, PROFILED_PATH,
                              PROFILED_INTERFACE);

    // Returns true if success
    QDBusReply<bool> reply = dbus_iface.call(PROFILED_SET_PROFILE, profileName);
    return reply.value();
}

bool ProfileClient::setProfileProperty(QString profile, QString property, QString value)
{
    QDBusInterface dbus_iface(PROFILED_SERVICE, PROFILED_PATH,
                              PROFILED_INTERFACE);

    // Returns true if success
    QDBusReply<bool> reply = dbus_iface.call(PROFILED_SET_VALUE, profile, property, value);
    return reply.value();
}

QStringList ProfileClient::profileTypes()
{
    QDBusInterface dbus_iface(PROFILED_SERVICE, PROFILED_PATH,
                              PROFILED_INTERFACE);

    QStringList profileTypes;
    QString profile;
    foreach (profile, profiles())
    {
        QDBusReply<QString> reply = dbus_iface.call(PROFILED_GET_VALUE, profile,
                                                    PROFILED_TYPE_VALUE);
        profileTypes.append(reply.value());
    }

    // In Harmattan at least, profile type Ringing is
    // attached to  "general" and "outdoors" profiles.
    // The "general" profile is the one that's used for
    // "ringing", profile "outdoors" should not be used
    // when setting a profile.
    profileTypes.removeDuplicates();
    return profileTypes;
}

QString ProfileClient::activeProfile()
{
    if (m_activeProfile.isEmpty()) {
        QDBusInterface dbus_iface(PROFILED_SERVICE, PROFILED_PATH,
                                  PROFILED_INTERFACE);

        QDBusReply<QString> reply = dbus_iface.call(PROFILED_GET_PROFILE);
        m_activeProfile = reply.value();
    }

    return m_activeProfile;
}

QString ProfileClient::profileProperty(QString profile, QString property)
{
    QDBusInterface dbus_iface(PROFILED_SERVICE, PROFILED_PATH,
                              PROFILED_INTERFACE);

    // Returns true if success
    QDBusReply<QString> reply = dbus_iface.call(PROFILED_GET_VALUE, profile, property);
    return reply.value();
}

QStringList ProfileClient::profiles()
{
    QDBusInterface dbus_iface(PROFILED_SERVICE, PROFILED_PATH,
                              PROFILED_INTERFACE);

    QDBusReply<QStringList> reply = dbus_iface.call(PROFILED_GET_PROFILES);
    return reply.value();
}

QDBusArgument &operator<<(QDBusArgument &argument, const ProfileDataValue &value)
{
    argument.beginStructure();
    argument << value.key << value.val << value.type;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, ProfileDataValue &value)
{
    argument.beginStructure();
    argument >> value.key >> value.val >> value.type;
    argument.endStructure();
    return argument;
}
