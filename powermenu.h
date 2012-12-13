#ifndef POWERMENU_H
#define POWERMENU_H

#include <MDialog>
#include <MBasicListItem>

#include <QGraphicsLinearLayout>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusInterface>

#include "profileclient.h"

class PowerMenu : public MDialog
{
    Q_OBJECT
public:
    explicit PowerMenu(MWindow *window = 0);
    
public slots:
    void appearOnWindow();
    
private:
    MWindow *m_window;
    ProfileClient *m_profileClient;

private slots:
    void onPowerOffButtonClicked();
    void onRebootButtonClicked();
    void onRestartMeeGoTouchHomeClicked();
};

#endif // POWERMENU_H
