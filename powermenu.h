#ifndef POWERMENU_H
#define POWERMENU_H

#include <MDialog>
#include <MBasicListItem>

#include <QGraphicsLinearLayout>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusInterface>

#include "profileclient.h"
#include "statebutton.h"

#define ICON_PATH "/usr/share/extended-power-menu/icons/"
#define VIBRATE_ON_ICON ICON_PATH "vibrate_on.png"
#define VIBRATE_OFF_ICON ICON_PATH "vibrate_off.png"
#define GENERAL_ICON ICON_PATH "general.png"
#define SILENT_ICON ICON_PATH "silent.png"

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
    StateButton *m_profileButton;
    StateButton *m_vibrateButton;

private slots:
    void onPowerOffButtonClicked();
    void onRebootButtonClicked();
    void onRestartMeeGoTouchHomeClicked();

    void onProfileButtonClicked();
    void onVibrateButtonClicked();
    void onProfileChanged(QString profile);
    void onProfilePropertyChanged(QString profile, QString property, QString value);
};

#endif // POWERMENU_H
