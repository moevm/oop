#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->cell->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_create_cell_clicked()
{
    int n = ui->size_n->value();
    int m = ui->size_m->value();

    if (cell) {

        QMessageBox::warning(this, "Warning", "Поле уже создано!");
        return;
    }

    cell = new Cell(n, m);

    double x1 = 0.0, y1 = 0.0;


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            QRectF rect(x1, y1, 500 / m, 500 / n);
            scene->addRect(rect);
            x1 += 500 / m;
        }
        y1 += 500 / n;
        x1 = 0.0;
    }
}

void MainWindow::update()
{
    scene->clear();
    double x1 = 0.0, y1 = 0.0;
    for (int i = 1; i <= cell->n(); i++) {
        for (int j = 1; j <= cell->m(); j++) {
            if (cell->get_type(i, j) != "Object")
            {
                QGraphicsItemGroup group;
                QRectF rect(x1, y1, 500 / cell->m(), 500 / cell->n());
                scene->addRect(rect);
                QGraphicsTextItem* txt = new QGraphicsTextItem(cell->get_type(i, j).c_str());
                txt->setX(x1 + 100 / cell->m());
                txt->setY(y1 + 100 / cell->n());
                scene->addItem(txt);
                x1 += 500 / cell->m();
            }
            else
            {
                QRectF rect(x1, y1, 500 / cell->m(), 500 / cell->n());
                scene->addRect(rect);
                x1 += 500 / cell->m();
            }
        }
        y1 += 500 / cell->n();
        x1 = 0.0;
    }
}

void MainWindow::on_add_unit_clicked()
{
    if (!cell) {
        QMessageBox::warning(this, "Warning", "Создайте поле!");
        return;
    }

    if (ui->archer->isChecked()) {
        cell->add_unit
                (new Archer({ui->x->value(), ui->y->value()}));
    } else if (ui->wizard->isChecked()) {
        cell->add_unit
                (new Wizard({ui->x->value(), ui->y->value()}));
    } else if (ui->swordsman->isChecked()) {
        cell->add_unit
                (new SwordsMan({ui->x->value(), ui->y->value()}));
    } else if (ui->spearman->isChecked()) {
        cell->add_unit
                (new SpearMan({ui->x->value(), ui->y->value()}));
    } else if (ui->panzer->isChecked()) {
        cell->add_unit
                (new Panzer({ui->x->value(), ui->y->value()}));
    } else if (ui->centaur->isChecked()) {
        cell->add_unit
                (new Centaur({ui->x->value(), ui->y->value()}));
    }

    update();
}

void MainWindow::on_move_unit_clicked()
{
    int x = ui->diff_x->value();
    int y = ui->diff_y->value();

    if (ui->left->isChecked()) {
        cell->move({x, y}, Object::BACK, true);
    } else if (ui->right->isChecked()) {
        cell->move({x, y}, Object::FORWARD, true);
    } else if (ui->up->isChecked()) {
        cell->move({x, y}, Object::FORWARD, false);
    } else
        cell->move({x, y}, Object::BACK, false);

    update();
}
