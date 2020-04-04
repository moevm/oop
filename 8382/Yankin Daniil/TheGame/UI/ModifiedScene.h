#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QGraphicsSceneWheelEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QGraphicsProxyWidget>

#include "AttributeWidget.h"
#include "BaseWidget.h"
#include "TurnButton.h"

#define OFFSET_STEP 0.01

class Object;
class Base;


class ModifiedScene : public QGraphicsScene
{
public:
    ModifiedScene(QWidget *parent = nullptr);

    void showAttributes(Object* object);
    void hideAttributes();

    void showBase(Base* base);
    void hideBase();

    void showTurn();
    void hideTurn();

private slots:
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    AttributeWidget* attributeWidget;
    BaseWidget* baseWidget;
    TurnButton* overButton;

    qreal x;
    qreal y;
    qreal width;
    qreal height;
};
