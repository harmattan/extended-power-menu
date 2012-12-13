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
