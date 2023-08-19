#include "eventfilterobj.h"
#include <QMouseEvent>
#include <QWidget>
#include <QDebug>
eventFilterObj::eventFilterObj(QObject *parent) : QObject(parent)
{

}

bool eventFilterObj::eventFilter(QObject *watched, QEvent *event)
{
    auto* Mouseev = static_cast<QMouseEvent*>(event);
    static QPoint pos;
    if(event->type() == QEvent::MouseButtonPress){
        pos = Mouseev->pos();
        qDebug()<<pos;

    }
    else if(event->type() == QEvent::MouseMove && Mouseev->buttons()&Qt::LeftButton){
        auto* pthis = static_cast<QWidget*>(watched);
        pthis->move(Mouseev->globalPos()-pos);
    }
    return false;
}
