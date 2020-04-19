#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    startNewGameButton(new QPushButton),
    playersCountLabel(new QLabel),
    playersCountSpinBox(new QSpinBox),
    fieldSizeLabel(new QLabel),
    fieldSizeSpinBox(new QSpinBox),
    logModeLabel(new QLabel),
    logModeComboBox(new QComboBox),
    logAdvancedModeCheckBox(new QCheckBox)
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
    fieldSizeLabel->setText("Field size:");
    logModeLabel->setText("Log mode:");

    // set up other
    playersCountSpinBox->setRange(1, 3);
    fieldSizeSpinBox->setRange(3, 15);
    // log stuff setup
    logModeComboBox->addItem("no log");
    logModeComboBox->addItem("to file");
    logModeComboBox->addItem("to terminal");
    logAdvancedModeCheckBox->setText("Enable advanced logging:");
    logAdvancedModeCheckBox->setLayoutDirection(Qt::RightToLeft);

    // set up grids
    QHBoxLayout *playersCountLayout = new QHBoxLayout;
    playersCountLayout->addWidget(playersCountLabel);
    playersCountLayout->addWidget(playersCountSpinBox);
    QHBoxLayout *fieldSizeLayout = new QHBoxLayout;
    fieldSizeLayout->addWidget(fieldSizeLabel);
    fieldSizeLayout->addWidget(fieldSizeSpinBox);
    QHBoxLayout *logModeLayout = new QHBoxLayout;
    logModeLayout->addWidget(logModeLabel);
    logModeLayout->addWidget(logModeComboBox);
    QGridLayout *mainGameSetupLayout = new QGridLayout;
    mainGameSetupLayout->addWidget(startNewGameButton, 0, 0, 1, 1, Qt::AlignCenter);
    mainGameSetupLayout->addLayout(playersCountLayout, 1, 0, 1, 1, Qt::AlignCenter);
    mainGameSetupLayout->addLayout(fieldSizeLayout, 2, 0, 2, 1, Qt::AlignCenter);
    mainGameSetupLayout->addLayout(logModeLayout, 4, 0, 4, 1, Qt::AlignCenter);
    mainGameSetupLayout->addWidget(logAdvancedModeCheckBox, 7, 0, 7, 1, Qt::AlignCenter);

    // main layout setup
    layout->addLayout(mainGameSetupLayout);

    /* SIGNALS AND SLOTS CONNECTIONS */
    gameWindow = new GameWindow();
    connect(startNewGameButton, &QPushButton::pressed, this, &MainWindow::on_startNewGameButton_clicked);
    connect(gameWindow, &GameWindow::gameWindowClosed, this, &MainWindow::on_gameWindow_closeEvent);
    connect(this, &MainWindow::startNewGameWindow, gameWindow, &GameWindow::startNewPlayingWindow);

#ifdef QT_DEBUG
    qDebug() << "Debug: UI setup finished" << endl;
#endif
}

void MainWindow::on_startNewGameButton_clicked()
{
    gameFieldSize = fieldSizeSpinBox->value();
    playersCount = playersCountSpinBox->value();
    emit startNewGameWindow(gameFieldSize, playersCount);
    setDisabled(true);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    // TODO: also ask for saving (next lr)
    gameWindow->close();
    event->accept();
}

void MainWindow::on_gameWindow_closeEvent()
{
    setEnabled(true);
}

GameWindow* MainWindow::getGameWindow() const
{
    return gameWindow;
}
