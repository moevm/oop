#ifndef GAMECELL_H
#define GAMECELL_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include "Neuturals/Pack.h"
#include "Objects/Object.h"
#include "Landscapes/Landscape.h"
#include "Landscapes/Lava.h"
#include "Landscapes/Rock.h"
#include "Landscapes/Water.h"
#include "Field.h"

class GameCell
{
public:
    Object* &obj;

    Pack* pack = nullptr;

    QRectF rectf;

    QPen pen;

    QBrush brush;

    Landscape* landscape = nullptr;

    explicit GameCell(Object* &obj, QRectF = QRectF(), QPen = QPen());

    bool canStandUnit() const;

    bool canMove() const;

    bool canPlaceBuild() const;

    bool empty() const;

    ~GameCell();
};

#endif // GAMECELL_H
