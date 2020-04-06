#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    startNewGameButton(new QPushButton),
    playersCountLabel(new QLabel),
    playersCountSpinBox(new QSpinBox)
{
    setUpUI();
}

void MainWindow::setUpUI()
{
#ifdef QT_DEBUG
    qDebug() << "Debug: UI setup started" << endl;
#endif
    // working zone - main widget
    QWidget *canvas = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    // set main vertical layout
    canvas->setLayout(layout);

    // sets the stretch factor at position index
    // and aligning of main widget
    layout->setStretch(1, 2);
    layout->setAlignment(Qt::AlignCenter);

    // set main widget of window
    canvas->setStyleSheet("QWidget { background: white; }");
    setCentralWidget(canvas);

    // set up buttons
    startNewGameButton->setText("Start new game");

    // set up labels
    playersCountLabel->setAlignment(Qt::AlignCenter);
    playersCountLabel->setText("Number of players:");

    // set up other
    playersCountSpinBox->setRange(1, 3);

    // set up grids
    QHBoxLayout *playersCountLayout = new QHBoxLayout;
    playersCountLayout->addWidget(playersCountLabel);
    playersCountLayout->addWidget(playersCountSpinBox);
    QGridLayout *mainGameSetupLayout = new QGridLayout;
    mainGameSetupLayout->addLayout(playersCountLayout, 1, 0, 1, 1, Qt::AlignCenter);
    mainGameSetupLayout->addWidget(startNewGameButton, 0, 0, 1, 1, Qt::AlignCenter);

    // main layout setup
    layout->addLayout(mainGameSetupLayout);

    /* SIGNALS AND SLOTS CONNECTIONS */
    gameWindow = new GameWindow();
    connect(startNewGameButton, &QPushButton::pressed, this, &MainWindow::on_startNewGameButton_clicked);
    connect(gameWindow, &GameWindow::gameWindowClosed, this, &MainWindow::on_gameWindow_closeEvent);

#ifdef QT_DEBUG
    qDebug() << "Debug: UI setup finished" << endl;
#endif
}

void MainWindow::on_startNewGameButton_clicked()
{
    gameWindow->showMaximized();
    setDisabled(true);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    // TODO: also ask for saving
    gameWindow->destroy();
    event->accept();
}

void MainWindow::on_gameWindow_closeEvent()
{
    // FIXME: function doesn't enter here
    setEnabled(true);
}
