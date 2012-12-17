#include "powermenu.h"

PowerMenu::PowerMenu(MWindow *window) :
    MDialog(tr("Power Menu"), M::NoStandardButton),
    m_window(window),
    m_profileClient(new ProfileClient(this))
{
    if (centralWidget() == NULL) {
        MWidget *newCentralWidget = new MWidget(this);
        setCentralWidget(newCentralWidget);
    }
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical, centralWidget());

    QGraphicsLinearLayout *profileLayout = new QGraphicsLinearLayout(Qt::Horizontal);

    QString currentProfile = m_profileClient->activeProfile();
    QString vibrateProperty = m_profileClient->profileProperty(currentProfile, PROFILED_VIBRATE_VALUE);

    m_vibrateButton = new StateButton(this, (vibrateProperty == "On"));
    m_vibrateButton->setIcons(VIBRATE_ON_ICON, VIBRATE_OFF_ICON);

    m_profileButton = new StateButton(this, ((currentProfile == "general") || currentProfile == "meeting"));
    m_profileButton->setIcons(GENERAL_ICON, SILENT_ICON);

    connect(m_profileButton, SIGNAL(clicked()), this, SLOT(onProfileButtonClicked()));
    connect(m_vibrateButton, SIGNAL(clicked()), this, SLOT(onVibrateButtonClicked()));

    connect(m_profileClient, SIGNAL(profileChanged(QString)), this, SLOT(onProfileChanged(QString)));
    connect(m_profileClient, SIGNAL(propertyChanged(QString,QString,QString)), this, SLOT(onProfilePropertyChanged(QString,QString,QString)));

    profileLayout->addItem(m_vibrateButton);
    profileLayout->addItem(m_profileButton);
    layout->addItem(profileLayout);

    MBasicListItem *powerOffButton = new MBasicListItem(MBasicListItem::SingleTitle);
    powerOffButton->setStyleName("CommonSmallPanelInverted");
    connect(powerOffButton, SIGNAL(clicked()), this, SLOT(onPowerOffButtonClicked()));
    powerOffButton->setTitle(tr("Power off"));
    layout->addItem(powerOffButton);

    MBasicListItem *rebootButton = new MBasicListItem(MBasicListItem::SingleTitle);
    rebootButton->setStyleName("CommonSmallPanelInverted");
    connect(rebootButton, SIGNAL(clicked()), this, SLOT(onRebootButtonClicked()));
    rebootButton->setTitle(tr("Reboot"));
    layout->addItem(rebootButton);

    MBasicListItem *restartMeeGoTouch = new MBasicListItem(MBasicListItem::SingleTitle);
    restartMeeGoTouch->setStyleName("CommonSmallPanelInverted");
    connect(restartMeeGoTouch, SIGNAL(clicked()), this, SLOT(onRestartMeeGoTouchHomeClicked()));
    restartMeeGoTouch->setTitle(tr("Restart MeeGo Touch Home"));
    layout->addItem(restartMeeGoTouch);
}

void PowerMenu::onPowerOffButtonClicked()
{
    disappear();
    QDBusInterface interface("com.nokia.dsme", "/com/nokia/dsme/request", "com.nokia.dsme.request", QDBusConnection::systemBus(), this);
    interface.call("req_shutdown");
}

void PowerMenu::onRebootButtonClicked()
{
    disappear();
    QDBusInterface interface("com.nokia.dsme", "/com/nokia/dsme/request", "com.nokia.dsme.request", QDBusConnection::systemBus(), this);
    interface.call("req_reboot");
}

void PowerMenu::onRestartMeeGoTouchHomeClicked()
{
    disappear();
    system("killall meegotouchhome");
}

void PowerMenu::appearOnWindow()
{
    appear(m_window, MSceneWindow::KeepWhenDone);
}

void PowerMenu::onProfileChanged(QString profile)
{
    if (profile == "general" || profile == "meeting")
        m_profileButton->setState(true);
    else if (profile == "silent")
        m_profileButton->setState(false);
}

void PowerMenu::onProfilePropertyChanged(QString profile, QString property, QString value)
{
    if (property != PROFILED_VIBRATE_VALUE)
        return;

    if (profile != m_profileClient->activeProfile())
        return;

    if (value == "On")
        m_vibrateButton->setState(true);
    else if (value == "Off")
        m_vibrateButton->setState(false);
}

void PowerMenu::onProfileButtonClicked()
{
    if (m_profileButton->state())
        m_profileClient->setProfile("silent");
    else
        m_profileClient->setProfile("general");
}

void PowerMenu::onVibrateButtonClicked()
{
    QString newValue;
    if (m_vibrateButton->state())
        newValue = "Off";
    else
        newValue = "On";
    m_profileClient->setProfileProperty(m_profileClient->activeProfile(), PROFILED_VIBRATE_VALUE, newValue);
}
