#include "statebutton.h"

StateButton::StateButton(QGraphicsItem *parent, bool initialState) :
    MImageWidget(parent),
    m_state(initialState),
    m_pressed(false)
{
}

void StateButton::setState(bool on)
{
    if (m_state == on)
        return;

    m_state = on;
    emit stateChanged(on);
    updateIcons(on);
}

void StateButton::setIcons(QString activeIcon, QString inactiveIcon)
{
    m_activeIcon = activeIcon;
    m_inactiveIcon = inactiveIcon;

    updateIcons(m_state);
}

void StateButton::updateIcons(bool state)
{
    if (state) {
        setImage(QImage(m_activeIcon));
    } else {
        setImage(QImage(m_inactiveIcon));
    }
}

void StateButton::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        m_pressed = true;
        emit pressed();
    }
}

void StateButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        m_pressed = false;
        emit released();
        if (rect().contains(ev->pos())) {
            emit clicked();
        }
    }
}

void StateButton::cancelEvent(MCancelEvent *event)
{
    Q_UNUSED(event);
    m_pressed = false;
}
