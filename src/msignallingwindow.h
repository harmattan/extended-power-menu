#ifndef MSIGNALLINGWINDOW_H
#define MSIGNALLINGWINDOW_H

#include <MWindow>
#include <MSceneManager>

#include <QTimer>
#include <QX11Info>
#include <QDBusMessage>

#include <X11/Xresource.h>
#include "x11wrapper.h"

class MSignallingWindow : public MWindow
{
    Q_OBJECT
public:
    explicit MSignallingWindow(MSceneManager *sceneManager = 0);
    
signals:
    void shown();
    void hidden();
    
public slots:
    void showHide();
    void onDisplayStateChanged(const QDBusMessage &msg);

protected:
     void showEvent(QShowEvent *event);
     void hideEvent(QHideEvent *event);
};

#endif // MSIGNALLINGWINDOW_H
