#ifndef PROFILECLIENT_H
#define PROFILECLIENT_H

// Class to handle profiles, credits go to
// http://meegoharmattandev.blogspot.co.il/2011/07/changing-and-accessing-profiles.html
// The code is mostly copy-pasted except for some code style changes, and some code from Nokia's
// qt-mobility Gitorious repo https://qt.gitorious.org/qt-mobility/qt-mobility/blobs/master/src/systeminfo/qsysteminfo_maemo.cpp

#define PROFILED_SERVICE "com.nokia.profiled"
#define PROFILED_PATH "/com/nokia/profiled"
#define PROFILED_INTERFACE "com.nokia.profiled"
#define PROFILED_GET_PROFILES "get_profiles"
#define PROFILED_SET_PROFILE "set_profile"
#define PROFILED_GET_VALUE "get_value"
#define PROFILED_SET_VALUE "set_value"
#define PROFILED_PROFILE_CHANGED "profile_changed"
// The key for accessing Harmattan's profile type under profile
#define PROFILED_TYPE_VALUE "ringing.alert.type"
#define PROFILED_VIBRATE_VALUE "vibrating.alert.enabled"

#include <QObject>
#include <QDebug>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusArgument>
#include <QDBusMetaType>

struct ProfileDataValue {
    QString key;
    QString val;
    QString type;
};

Q_DECLARE_METATYPE(ProfileDataValue)
Q_DECLARE_METATYPE(QList<ProfileDataValue>)

class ProfileClient : public QObject
{
    Q_OBJECT
public:
    explicit ProfileClient(QObject *parent = 0);
    static QStringList profiles();
    static QStringList profileTypes();
    static bool setProfile(QString profileName);
    static bool setProfileProperty(QString profile, QString property, QString value);
    
signals:
    void profileChanged(QString profile);
    void propertyChanged(QString profile, QString property, QString value);
    
private slots:
    void onProfileChanged(bool changed, bool active, QString profile, QList<ProfileDataValue> values);
};

#endif // PROFILECLIENT_H
