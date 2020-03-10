#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <vector>
#include "Field.h"

struct MyRect {
    QRectF rectf;
    QPen pen;
    QBrush brush;
};

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(Field* const = nullptr, QWidget* = nullptr);
    Field * const field;
    void update();
    void mousePressEvent(QMouseEvent*) override;

private:
    std::vector <std::vector<MyRect>> squares;

    QGraphicsScene *scene;
    QGraphicsItemGroup *group;
    void deleteItemsFromGroup();
};

#endif // MYGRAPHICSVIEW_H
