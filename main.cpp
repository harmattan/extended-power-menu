#include <MApplication>
#include <MComponentCache>
#include <MExport>
#include <MDialog>
#include <MApplicationWindow>

#include "powermenu.h"
#include "powerbuttonlistener.h"
#include "msignallingwindow.h"

M_EXPORT int main(int argc, char *argv[])
{
    MApplication *application = MComponentCache::mApplication(argc, argv);
    MSignallingWindow *window = new MSignallingWindow(new MSceneManager);
    window->setTranslucentBackground(true);
    window->setAttribute(Qt::WA_X11NetWmWindowTypeDialog, true);
    window->setWindowModality(Qt::WindowModal);

    PowerButtonListener listener;
    PowerMenu powerMenu(window);

    QObject::connect(&listener, SIGNAL(powerButtonDoubleClicked()), window, SLOT(showHide()));
    QObject::connect(window, SIGNAL(shown()), &powerMenu, SLOT(appearOnWindow()));
    QObject::connect(window, SIGNAL(hidden()), &powerMenu, SLOT(dismiss()));
    QObject::connect(&powerMenu, SIGNAL(disappeared()), window, SLOT(hide()));

    QDBusConnection::systemBus().connect("", "/com/nokia/mce/signal", "com.nokia.mce.signal",
                                         "display_status_ind", window, SLOT(onDisplayStateChanged(const QDBusMessage &)));

    return application->exec();
}
