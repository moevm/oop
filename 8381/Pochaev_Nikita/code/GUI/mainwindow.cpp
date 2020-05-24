#include "mainwindow.h"

/*
 * QFont standartFont("Arial", 8, QFont::Normal);
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    startNewGameButton(new QPushButton),
    gameSetupLabel(new QLabel),
    playersCountLabel(new QLabel),
    playersCountSpinBox(new QSpinBox),
    fieldSizeLabel(new QLabel),
    fieldSizeSpinBox(new QSpinBox),
    gameRulesLabel(new QLabel),
    gameRulesComboBox(new QComboBox),
    rulesInformationText(new QTextEdit),
    logModeLabel(new QLabel),
    logModeComboBox(new QComboBox),
    logAdvancedModeCheckBox(new QCheckBox)
{
    setUpUI();
}

void MainWindow::setUpUI()
{
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
    QFont headerFont("Arial", 10, QFont::Bold);
    playersCountLabel->setAlignment(Qt::AlignCenter);
    playersCountLabel->setText("Number of players:");
    fieldSizeLabel->setText("Field size:");
    logModeLabel->setText("Log mode:");
    gameSetupLabel->setText("Game setup");
    gameSetupLabel->setAlignment(Qt::AlignCenter);
    gameSetupLabel->setFont(headerFont);
    gameRulesLabel->setText("Game rules:");

    // set up other
    playersCountSpinBox->setRange(1, 4);
    fieldSizeSpinBox->setRange(3, 15);
    // log stuff setup
    logModeComboBox->addItem("no log");
    logModeComboBox->addItem("to file");
    logModeComboBox->addItem("to terminal");
    logAdvancedModeCheckBox->setText("Enable advanced logging:");
    logAdvancedModeCheckBox->setLayoutDirection(Qt::RightToLeft);

    // game rulse stuff setup
    gameRulesComboBox->addItem("no rules");
    gameRulesComboBox->addItem("1 vs 1 (battle)");
    gameRulesComboBox->addItem("2 vs 2 (confrontation)");
    rulesInformationText->setReadOnly(true);
    rulesInformationText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rulesInformationText->viewport()->setCursor(Qt::ArrowCursor);

    // set up grids
    QHBoxLayout *mainGameSetupLayout = new QHBoxLayout;

    QHBoxLayout *playersCountLayout = new QHBoxLayout;
    playersCountLayout->addWidget(playersCountLabel);
    playersCountLayout->addWidget(playersCountSpinBox);

    QHBoxLayout *fieldSizeLayout = new QHBoxLayout;
    fieldSizeLayout->addWidget(fieldSizeLabel);
    fieldSizeLayout->addWidget(fieldSizeSpinBox);

    QHBoxLayout *logModeLayout = new QHBoxLayout;
    logModeLayout->addWidget(logModeLabel);
    logModeLayout->addWidget(logModeComboBox);

    QVBoxLayout *totalLogLayout = new QVBoxLayout;
    totalLogLayout->addLayout(logModeLayout);
    totalLogLayout->addWidget(logAdvancedModeCheckBox);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(startNewGameButton);
    leftLayout->addLayout(totalLogLayout);

    QHBoxLayout *rulesChooseLayout = new QHBoxLayout;
    rulesChooseLayout->addWidget(gameRulesLabel);
    rulesChooseLayout->addWidget(gameRulesComboBox);

    QVBoxLayout *rulesLayout = new QVBoxLayout;
    rulesLayout->addLayout(rulesChooseLayout);
    rulesLayout->addWidget(rulesInformationText);

    QVBoxLayout *gameSetupLayout = new QVBoxLayout;
    gameSetupLayout->addLayout(playersCountLayout);
    gameSetupLayout->addLayout(fieldSizeLayout);
    gameSetupLayout->setAlignment(Qt::AlignLeft);

    QHBoxLayout *totalRulesLayout = new QHBoxLayout;
    totalRulesLayout->addLayout(gameSetupLayout);
    totalRulesLayout->addLayout(rulesLayout);

    QVBoxLayout *gameModLayout = new QVBoxLayout;
    gameModLayout->setAlignment(Qt::AlignCenter);
    gameModLayout->addWidget(gameSetupLabel);
    gameModLayout->addLayout(totalRulesLayout);

    mainGameSetupLayout->addLayout(leftLayout);
    mainGameSetupLayout->addLayout(gameModLayout);

    // main layout setup
    layout->addLayout(mainGameSetupLayout);

    /* SIGNALS AND SLOTS CONNECTIONS */
    gameWindow = new GameWindow();
    connect(startNewGameButton, &QPushButton::pressed, this, &MainWindow::on_startNewGameButton_clicked);
    connect(gameWindow, &GameWindow::gameWindowClosed, this, &MainWindow::on_gameWindow_closeEvent);
    connect(this, &MainWindow::startNewGameWindow, gameWindow, &GameWindow::startNewPlayingWindow);
    connect(this, &MainWindow::startLogging, gameWindow, &GameWindow::createLoggerRequest);
    connect(gameRulesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_RuleValue_changed);
}

void MainWindow::on_startNewGameButton_clicked()
{
    std::unique_ptr<AbstractGameRule> rules{};

    if(gameRulesComboBox->currentIndex() == 0)
    {
        // game field and players info
        gameFieldSize = fieldSizeSpinBox->value();
        playersCount = playersCountSpinBox->value();
    }
    else if(gameRulesComboBox->currentIndex() == 1)
    {
        rules = std::make_unique<oneToOneRule>();
        gameFieldSize = rules->getFieldSize();
        playersCount = rules->getPlayersCount();
    }
    else if(gameRulesComboBox->currentIndex() == 2)
    {
        rules = std::make_unique<twoByTwoRule>();
        gameFieldSize = rules->getFieldSize();
        playersCount = rules->getPlayersCount();
    }

    // logger info
    eLOGGER_TYPE loggerType = NO_LOG;
    if(logModeComboBox->currentIndex() == 0)
    {
        loggerType = NO_LOG;
    }
    else if(logModeComboBox->currentIndex() == 1)
    {
        loggerType = FILE_LOG;
    }
    else if(logModeComboBox->currentIndex() == 2)
    {
        loggerType = TERMINAL_LOG;
    }
    eLOGGER_OUTPUT_FORMAT loggerFormat = logAdvancedModeCheckBox->isChecked() ? ADVANCED : STANDART;

    emit startNewGameWindow(gameFieldSize, playersCount, this->width(), this->height(), (rules) ? rules->getType() : NO_TYPE);
    emit startLogging(loggerType, loggerFormat);
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

void MainWindow::on_RuleValue_changed(int index)
{
    if(index == 0)
    {
        rulesInformationText->clear();
    }
    else if(index == 1)
    {
        rulesInformationText->setText("- 1 player VS 1 player;\n- Field size: 8*8;\n- Time for step: 40 sec.;\n- Victory condition: superiority in bases.");
    }
    else if(index == 2)
    {
        rulesInformationText->setText("- 2 players VS 2 players;\n- Field size: 15*15;\nTime for step: 20 sec.;\n- Victory condition: destruction of enemy bases.");
    }
}
