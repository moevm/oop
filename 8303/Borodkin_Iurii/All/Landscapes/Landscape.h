#ifndef LANDSCAPE_H
#define LANDSCAPE_H
#include <QBrush>
#include "Proxy/Proxy.h"

class Landscape : public IProxy
{
protected:
    QBrush _brush;
public:
    Landscape(QBrush = Qt::green);
    void kill(Object *&) override;
    virtual QBrush brush() const;
    virtual bool canStandUnit() const;
    virtual bool canPlaceBuild() const;
    virtual bool deathCell() const;
    virtual bool canMove() const;
};

#endif // LANDSCAPE_H
