#ifndef STATEBUTTON_H
#define STATEBUTTON_H

#include <QGraphicsSceneMouseEvent>

#include <MImageWidget>
#include <MCancelEvent>

class StateButton : public MImageWidget
{
    Q_OBJECT
public:
    explicit StateButton(QGraphicsItem *parent = 0, bool initialState = false);
    bool state() { return m_state; }

signals:
    void stateChanged(bool state);
    void pressed();
    void released();
    void clicked();
    
public slots:
    void setState(bool on);
    void setIcons(QString activeIcon, QString inactiveIcon);

private:
    bool m_state;
    bool m_pressed;
    QString m_activeIcon;
    QString m_inactiveIcon;

    void updateIcons(bool state);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);
    void cancelEvent(MCancelEvent *event);
};

#endif // STATEBUTTON_H
