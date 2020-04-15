#include "ModifiedScene.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include <fstream>


ModifiedScene::ModifiedScene(QWidget *parent) : QGraphicsScene(parent),
    attributeWidget(nullptr), baseWidget(nullptr), overButton(nullptr), x(0), y(0), width(0), height(0) {
}

void ModifiedScene::wheelEvent(QGraphicsSceneWheelEvent *event) {
    auto view = *(views().begin());
    if (event->delta() > 0) {
        view->scale(1.2, 1.2);
    }
    if (event->delta() < 0) {
        view->scale(0.8, 0.8);
    }
}

void ModifiedScene::keyPressEvent(QKeyEvent *event) {
    auto view = *(views().begin());
    auto rect = view->sceneRect();

    if (width == 0) {
        x = rect.x();
        y = rect.y();
        width = rect.width();
        height = rect.height();
    }

    auto key = event->key();
    if (key == Qt::Key_Up || key == Qt::Key_W) {
        y -= OFFSET_STEP * height;
        view->setSceneRect(x, y, width, height);
    }
    else if (key == Qt::Key_Left || key == Qt::Key_A) {
        x -= OFFSET_STEP * width;
        view->setSceneRect(x, y, width, height);

    }
    else if (key == Qt::Key_Down || key == Qt::Key_S) {
        y += OFFSET_STEP * height;
        view->setSceneRect(x, y, width, height);
    }
    else if (key == Qt::Key_Right || key == Qt::Key_D) {
        x += OFFSET_STEP * width;
        view->setSceneRect(x, y, width, height);
    }
    update(sceneRect());
}



void ModifiedScene::showAttributes(Object* object) {
    if (object == nullptr) return;

    if (object->getGroupType() == UNIT || object->getGroupType() == BASE) {
        hideAttributes();

        QGraphicsView* view = *(views().begin());

        attributeWidget = new AttributeWidget(view);
        attributeWidget->setValues(object);
        attributeWidget->move(view->width() - attributeWidget->width(), view->height() - attributeWidget->height());
        attributeWidget->show();
    }
}

void ModifiedScene::hideAttributes() {
    delete attributeWidget;
    attributeWidget = nullptr;
}



void ModifiedScene::showBase(Base* base) {
    if (base == nullptr)
        return;

    hideBase();

    QGraphicsView* view = *(views().begin());
    baseWidget = new BaseWidget(view);
    baseWidget->move(view->width() - baseWidget->width(), 0);
    baseWidget->show();
}

void ModifiedScene::hideBase() {
    delete baseWidget;
    baseWidget = nullptr;
}




void ModifiedScene::showTurn() {
    if (overButton != nullptr)
        return;

    QGraphicsView* view = *(views().begin());

    overButton = new TurnButton(view);
    overButton->move(view->width() - overButton->width(), view->height() - overButton->height());
    overButton->show();
}

void ModifiedScene::hideTurn() {
    delete overButton;
    overButton = nullptr;
}
