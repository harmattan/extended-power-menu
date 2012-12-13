#ifndef POWERBUTTONLISTENER_H
#define POWERBUTTONLISTENER_H

#include <QObject>
#include <QDBusConnection>

class PowerButtonListener : public QObject
{
    Q_OBJECT
public:
    explicit PowerButtonListener(QObject *parent = 0);
    
signals:
    void powerButtonLongPressed();
    void powerButtonDoubleClicked();
};

#endif // POWERBUTTONLISTENER_H
