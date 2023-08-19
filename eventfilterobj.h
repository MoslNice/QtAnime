#ifndef EVENTFILTEROBJ_H
#define EVENTFILTEROBJ_H

#include <QObject>

class eventFilterObj : public QObject
{
    Q_OBJECT
public:
    explicit eventFilterObj(QObject *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:

};

#endif // EVENTFILTEROBJ_H
