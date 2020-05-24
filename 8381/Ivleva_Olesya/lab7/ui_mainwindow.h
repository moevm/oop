/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_8;
    QAction *action_9;
    QAction *action_10;
    QAction *action_11;
    QAction *action_12;
    QWidget *centralWidget;
    QPushButton *add_green_dr;
    QPushButton *add_red_dr;
    QTextEdit *print;
    QSpinBox *set_y;
    QSpinBox *set_x;
    QLabel *label;
    QPushButton *delete_item;
    QPushButton *move_unit;
    QSpinBox *set_x1;
    QSpinBox *set_y1;
    QLabel *move_2;
    QTextEdit *print_item;
    QPushButton *add_war_fight;
    QPushButton *add_war_ronin;
    QPushButton *add_sen_fire;
    QPushButton *add_sen_lion;
    QPushButton *bonus;
    QPushButton *attack;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1500, 1000);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/base.png"), QSize(), QIcon::Normal, QIcon::Off);
        action->setIcon(icon);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        action_8 = new QAction(MainWindow);
        action_8->setObjectName(QString::fromUtf8("action_8"));
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QString::fromUtf8("action_9"));
        action_10 = new QAction(MainWindow);
        action_10->setObjectName(QString::fromUtf8("action_10"));
        action_11 = new QAction(MainWindow);
        action_11->setObjectName(QString::fromUtf8("action_11"));
        action_12 = new QAction(MainWindow);
        action_12->setObjectName(QString::fromUtf8("action_12"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        add_green_dr = new QPushButton(centralWidget);
        add_green_dr->setObjectName(QString::fromUtf8("add_green_dr"));
        add_green_dr->setGeometry(QRect(20, 10, 80, 71));
        add_green_dr->setCursor(QCursor(Qt::PointingHandCursor));
        add_green_dr->setStyleSheet(QString::fromUtf8("border-image:url(:/icons/1108_s.png)"));
        add_red_dr = new QPushButton(centralWidget);
        add_red_dr->setObjectName(QString::fromUtf8("add_red_dr"));
        add_red_dr->setGeometry(QRect(140, 10, 80, 71));
        add_red_dr->setCursor(QCursor(Qt::PointingHandCursor));
        add_red_dr->setStyleSheet(QString::fromUtf8("border-image:url(:/icons/1118_s.png)"));
        print = new QTextEdit(centralWidget);
        print->setObjectName(QString::fromUtf8("print"));
        print->setGeometry(QRect(10, 320, 231, 481));
        print->setStyleSheet(QString::fromUtf8("border-radius: 10%;\n"
"border: 3px solid #545454;\n"
"background-color: #f8fbea;"));
        set_y = new QSpinBox(centralWidget);
        set_y->setObjectName(QString::fromUtf8("set_y"));
        set_y->setGeometry(QRect(110, 150, 51, 31));
        set_x = new QSpinBox(centralWidget);
        set_x->setObjectName(QString::fromUtf8("set_x"));
        set_x->setGeometry(QRect(30, 150, 51, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 105, 241, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Georgia Pro Cond Light"));
        font.setPointSize(11);
        font.setItalic(true);
        label->setFont(font);
        delete_item = new QPushButton(centralWidget);
        delete_item->setObjectName(QString::fromUtf8("delete_item"));
        delete_item->setGeometry(QRect(220, 130, 80, 61));
        delete_item->setCursor(QCursor(Qt::PointingHandCursor));
        delete_item->setStyleSheet(QString::fromUtf8("border-image:url(:/icons/delete.png)"));
        move_unit = new QPushButton(centralWidget);
        move_unit->setObjectName(QString::fromUtf8("move_unit"));
        move_unit->setGeometry(QRect(220, 230, 80, 71));
        move_unit->setCursor(QCursor(Qt::PointingHandCursor));
        move_unit->setStyleSheet(QString::fromUtf8("border-image:url(:/icons/move.png)"));
        set_x1 = new QSpinBox(centralWidget);
        set_x1->setObjectName(QString::fromUtf8("set_x1"));
        set_x1->setGeometry(QRect(30, 260, 51, 31));
        set_y1 = new QSpinBox(centralWidget);
        set_y1->setObjectName(QString::fromUtf8("set_y1"));
        set_y1->setGeometry(QRect(110, 260, 51, 31));
        move_2 = new QLabel(centralWidget);
        move_2->setObjectName(QString::fromUtf8("move_2"));
        move_2->setGeometry(QRect(30, 220, 191, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Georgia Pro Cond Light"));
        font1.setPointSize(12);
        font1.setItalic(true);
        move_2->setFont(font1);
        print_item = new QTextEdit(centralWidget);
        print_item->setObjectName(QString::fromUtf8("print_item"));
        print_item->setGeometry(QRect(280, 320, 541, 481));
        print_item->setStyleSheet(QString::fromUtf8("border-radius: 10%;\n"
"border: 3px solid #545454;\n"
"background-color: #f8fbea;"));
        add_war_fight = new QPushButton(centralWidget);
        add_war_fight->setObjectName(QString::fromUtf8("add_war_fight"));
        add_war_fight->setGeometry(QRect(250, 10, 80, 71));
        add_war_fight->setCursor(QCursor(Qt::PointingHandCursor));
        add_war_fight->setStyleSheet(QString::fromUtf8("border-image:url(:/icons/1095_s.png)"));
        add_war_ronin = new QPushButton(centralWidget);
        add_war_ronin->setObjectName(QString::fromUtf8("add_war_ronin"));
        add_war_ronin->setGeometry(QRect(360, 20, 80, 61));
        add_war_ronin->setCursor(QCursor(Qt::PointingHandCursor));
        add_war_ronin->setStyleSheet(QString::fromUtf8("border-image:url(:/icons/1104_s.png)"));
        add_sen_fire = new QPushButton(centralWidget);
        add_sen_fire->setObjectName(QString::fromUtf8("add_sen_fire"));
        add_sen_fire->setGeometry(QRect(470, 20, 80, 61));
        add_sen_fire->setCursor(QCursor(Qt::PointingHandCursor));
        add_sen_fire->setStyleSheet(QString::fromUtf8("border-image:url(:/icons/578_s.png)"));
        add_sen_lion = new QPushButton(centralWidget);
        add_sen_lion->setObjectName(QString::fromUtf8("add_sen_lion"));
        add_sen_lion->setGeometry(QRect(590, 10, 80, 71));
        add_sen_lion->setCursor(QCursor(Qt::PointingHandCursor));
        add_sen_lion->setStyleSheet(QString::fromUtf8("border-image:url(:/icons/575_s.png)"));
        bonus = new QPushButton(centralWidget);
        bonus->setObjectName(QString::fromUtf8("bonus"));
        bonus->setGeometry(QRect(340, 130, 80, 61));
        bonus->setCursor(QCursor(Qt::PointingHandCursor));
        bonus->setStyleSheet(QString::fromUtf8("border-image: url(:/icons/bonus.png)"));
        attack = new QPushButton(centralWidget);
        attack->setObjectName(QString::fromUtf8("attack"));
        attack->setGeometry(QRect(340, 230, 80, 61));
        attack->setCursor(QCursor(Qt::PointingHandCursor));
        attack->setStyleSheet(QString::fromUtf8("border-image:url(:/icons/attack.png)"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1500, 17));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menu->addSeparator();
        menu->addSeparator();
        menu->addAction(action);
        menu_2->addAction(action_2);
        menu_2->addAction(action_3);
        menu_3->addAction(action_4);
        menu_3->addAction(action_5);
        menu_4->addAction(action_6);
        menu_4->addAction(action_7);
        menu_5->addAction(action_8);
        menu_5->addAction(action_9);
        menu_5->addAction(action_10);
        menu_5->addAction(action_11);
        menu_5->addAction(action_12);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\261\320\260\320\267\321\213", nullptr));
        action_2->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\321\214 \320\262 \321\204\320\260\320\271\320\273", nullptr));
        action_3->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\321\214 \320\262 \320\272\320\276\320\275\321\201\320\276\320\273\321\214", nullptr));
        action_4->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273\320\275\320\260\321\217", nullptr));
        action_5->setText(QApplication::translate("MainWindow", "\320\232\321\200\320\260\321\202\320\272\320\260\321\217", nullptr));
        action_6->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        action_7->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        action_8->setText(QApplication::translate("MainWindow", "\320\233\320\265\320\263\320\272\320\276 2\320\270\320\263\321\200", nullptr));
        action_9->setText(QApplication::translate("MainWindow", "\320\233\320\265\320\263\320\272\320\276 3\320\270\320\263\321\200", nullptr));
        action_10->setText(QApplication::translate("MainWindow", "\320\241\320\273\320\276\320\266\320\275\320\276 2\320\270\320\263\321\200", nullptr));
        action_11->setText(QApplication::translate("MainWindow", "\320\241\320\273\320\276\320\266\320\275\320\276 3\320\270\320\263\321\200", nullptr));
        action_12->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\262\320\260\321\217 \320\270\320\263\321\200\320\260", nullptr));
#ifndef QT_NO_TOOLTIP
        add_green_dr->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Georgia Pro Cond Light'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#e9e8e4;\"><span style=\" background-color:#e9e8e4;\">\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\265\320\273\320\265\320\275\320\276\320\263\320\276 \320\264\321\200\320\260\320\272\320\276\320\275\320\260</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        add_green_dr->setText(QString());
#ifndef QT_NO_TOOLTIP
        add_red_dr->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Georgia Pro Cond Light'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#e9e8e4;\"><span style=\" background-color:#e9e8e4;\">\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\272\321\200\320\260\321\201\320\275\320\276\320\263\320\276 \320\264\321\200\320\260\320\272\320\276\320\275\320\260</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        add_red_dr->setText(QString());
        label->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213:", nullptr));
#ifndef QT_NO_TOOLTIP
        delete_item->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Georgia Pro Cond Light'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#e9e8e4;\"><span style=\" background-color:#e9e8e4;\">\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\216\320\275\320\270\321\202\320\260</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        delete_item->setText(QString());
#ifndef QT_NO_TOOLTIP
        move_unit->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Georgia Pro Cond Light'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#e9e8e4;\"><span style=\" background-color:#e9e8e4;\">\320\237\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214 \321\216\320\275\320\270\321\202\320\260</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        move_unit->setText(QString());
        move_2->setText(QApplication::translate("MainWindow", "\320\232\321\203\320\264\320\260:", nullptr));
        add_war_fight->setText(QString());
        add_war_ronin->setText(QString());
        add_sen_fire->setText(QString());
        add_sen_lion->setText(QString());
#ifndef QT_NO_TOOLTIP
        bonus->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Georgia Pro Cond Light'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#e9e8e4;\"><span style=\" background-color:#e9e8e4;\">\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\261\320\276\320\275\321\203\321\201</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        bonus->setText(QString());
#ifndef QT_NO_TOOLTIP
        attack->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Georgia Pro Cond Light'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#e9e8e4;\"><span style=\" background-color:#e9e8e4;\">\320\220\321\202\320\260\320\272\320\276\320\262\320\260\321\202\321\214</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        attack->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\320\221\320\260\320\267\320\260", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\233\320\276\320\263\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        menu_3->setTitle(QApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260 \320\262\321\213\320\262\320\276\320\264\320\260", nullptr));
        menu_4->setTitle(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\320\265", nullptr));
        menu_5->setTitle(QApplication::translate("MainWindow", "\320\230\320\263\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
