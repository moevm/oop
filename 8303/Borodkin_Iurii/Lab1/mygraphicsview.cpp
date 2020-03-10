#include "mygraphicsview.h"
#include <QDebug>

MyGraphicsView::MyGraphicsView(Field* const field, QWidget* parent) : QGraphicsView(parent), field(field)
{
    if (!field) return;


    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scene = new QGraphicsScene();
    this->setScene(scene);

    double x1 = 0.0, y1 = 0.0;

    for (int i = 0; i < field->height(); i++) {
        squares.push_back(std::vector<MyRect>());
        for (int j = 0; j < field->width(); j++) {
            QRectF rect(x1, y1, 500 / field->width(), 500 / field->height());
            squares[size_t(i)].push_back({rect, QPen(), QBrush()});
            scene->addRect(rect);
            x1 += 500 / field->width();
        }
        y1 += 500 / field->height();
        x1 = 0.0;
    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *e)
{
    if (!field) return;
    static bool isPressed = false;
    static std::pair<size_t, size_t> edge;
    auto coords = e->pos();

    if (isPressed)
    {
        size_t i = edge.first;
        size_t j = edge.second;

        if (int(i + 1) < field->height())
        {
            auto square = squares[i + 1][j].rectf;
            if ((square.x() < coords.x() && coords.x() < square.x() + square.width()) &&
                (square.y() < coords.y() && coords.y() < square.y() + square.height()) &&
                field->get_type(int(i), int(j)) != "Object")
                field->move({int(j), int(i)}, Moves::UP);

        }

        if (int(i - 1) >= 0)
        {
            auto square = squares[i - 1][j].rectf;
            if ((square.x() < coords.x() && coords.x() < square.x() + square.width()) &&
                (square.y() < coords.y() && coords.y() < square.y() + square.height()) &&
                field->get_type(int(i), int(j)) != "Object")
                field->move({int(j), int(i)}, Moves::DOWN);

        }

        if (int(j + 1) < field->width())
        {
            auto square = squares[i][j + 1].rectf;
            if ((square.x() < coords.x() && coords.x() < square.x() + square.width()) &&
                (square.y() < coords.y() && coords.y() < square.y() + square.height()) &&
                field->get_type(int(i), int(j)) != "Object")
                field->move({int(j), int(i)}, Moves::RIGHT);

        }

        if (int(j - 1) >= 0)
        {
            auto square = squares[i][j - 1].rectf;
            if ((square.x() < coords.x() && coords.x() < square.x() + square.width()) &&
                (square.y() < coords.y() && coords.y() < square.y() + square.height()) &&
                field->get_type(int(i), int(j)) != "Object")
                field->move({int(j), int(i)}, Moves::LEFT);

        }

        if (int(i + 1) < field->height()) squares[i+1][j].brush = Qt::white;
        if (int(j + 1) < field->width()) squares[i][j+1].brush = Qt::white;
        if (int(i - 1) >= 0) squares[i-1][j].brush = Qt::white;
        if (int(j - 1) >= 0) squares[i][j-1].brush = Qt::white;
        update();
        isPressed = false;

        return;
    }

    for (size_t i = 0; i < size_t(field->height()); i++)
        for (size_t j = 0; j < size_t(field->height()); j++)
        {
            auto square = squares[i][j].rectf;

            if ((square.x() < coords.x() && coords.x() < square.x() + square.width()) &&
                (square.y() < coords.y() && coords.y() < square.y() + square.height()) &&
                field->get_type(int(i), int(j)) != "Object")
            {
                isPressed = true;
                edge = {i, j};
                if (int(i + 1) < field->height() && field->get_type(int(i+1), int(j)) == "Object") squares[i+1][j].brush = Qt::black;
                if (int(j + 1) < field->width() && field->get_type(int(i), int(j+1)) == "Object") squares[i][j+1].brush = Qt::black;
                if (int(i - 1) >= 0 && field->get_type(int(i-1), int(j)) == "Object") squares[i-1][j].brush = Qt::black;
                if (int(j - 1) >= 0 && field->get_type(int(i), int(j-1)) == "Object") squares[i][j-1].brush = Qt::black;

                update();
                return;
            }
        }
}

void MyGraphicsView::update()
{
    scene->clear();
    double x1 = 0.0, y1 = 0.0;
    for (int i = 0; i < field->height(); i++) {
        for (int j = 0; j < field->width(); j++) {
            if (field->get_type(i, j) != "Object")
            {
                QGraphicsItemGroup group;
                scene->addRect(squares[size_t(i)][size_t(j)].rectf,
                               squares[size_t(i)][size_t(j)].pen,
                               squares[size_t(i)][size_t(j)].brush);
                QGraphicsTextItem* txt = new QGraphicsTextItem(field->get_type(i, j).c_str());
                txt->setX(x1 + 100 / field->width());
                txt->setY(y1 + 100 / field->height());
                scene->addItem(txt);
                x1 += 500 / field->width();
            }
            else
            {
                scene->addRect(squares[size_t(i)][size_t(j)].rectf,
                               squares[size_t(i)][size_t(j)].pen,
                               squares[size_t(i)][size_t(j)].brush);
                x1 += 500 / field->width();
            }
        }
        y1 += 500 / field->height();
        x1 = 0.0;
    }
}
