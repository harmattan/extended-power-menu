#include "msignallingwindow.h"

MSignallingWindow::MSignallingWindow(MSceneManager *sceneManager) :
    MWindow(sceneManager)
{
}

void MSignallingWindow::showEvent(QShowEvent *event)
{
    MWindow::showEvent(event);

    QTimer::singleShot(200, this, SIGNAL(shown()));

    // Set the stacking layer
    Display *display = QX11Info::display();
    Atom stackingLayerAtom = X11Wrapper::XInternAtom(display, "_MEEGO_STACKING_LAYER", False);
    if (stackingLayerAtom != None) {
        long layer = 6;
        X11Wrapper::XChangeProperty(display, internalWinId(), stackingLayerAtom, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&layer, 1);
    }
}

void MSignallingWindow::hideEvent(QHideEvent *event)
{
    emit hidden();
    MWindow::hideEvent(event);
}

void MSignallingWindow::showHide()
{
    if (isOnDisplay())
        hide();
    else
        show();
}

void MSignallingWindow::onDisplayStateChanged(const QDBusMessage &msg)
{
    if (msg.arguments().first().toString() == "off")
        hide();
}
