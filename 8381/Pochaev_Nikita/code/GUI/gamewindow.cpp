#include "gamewindow.h"

GameWindow::GameWindow() :
    addUnitButton(new QPushButton),
    unitTypeLabel(new QLabel),
    unitTypeComboBox(new QComboBox),
    unitSourceBaseLabel(new QLabel),
    unitSourceBaseComboBox(new QComboBox),

    addBaseButton(new QPushButton),
    baseTypeLabel(new QLabel),
    baseTypeComboBox(new QComboBox),
    basePositionLabel(new QLabel),
    xCoordBasePos(new QSpinBox),
    yCoordBasePos(new QSpinBox),
    baseNameLabel(new QLabel),
    baseNameText(new QLineEdit),

    moveUnitButton(new QPushButton),
    attackUnitButton(new QPushButton),
    unitActionLabel(new QLabel),
    unitSourceActionLabel(new QLabel),
    xCoordUnitSourceAction(new QSpinBox),
    yCoordUnitSourceAction(new QSpinBox),
    unitDestActionLabel(new QLabel),
    xCoordUnitDestAction(new QSpinBox),
    yCoordUnitDestAction(new QSpinBox),

    logs(new QTextEdit),
    cellInfromationButton(new QPushButton),
    logCoordsLabel(new QLabel),
    xCoordLogPos(new QSpinBox),
    yCoordLogPos(new QSpinBox),
    cellInfromationWhoLabel(new QLabel),
    cellInfromationWhoComboBox(new QComboBox),

    visualField(new QTextEdit)
{
    setupGameWindow();
}

void GameWindow::closeEvent(QCloseEvent* event)
{
    emit gameWindowClosed();
    event->accept();
}

void GameWindow::setupGameWindow()
{
    // BUTTONS SETUP
    addUnitButton->setText("Add unit");
    addBaseButton->setText("Add base");
    moveUnitButton->setText("Move unit");
    attackUnitButton->setText("Attack unit");
    cellInfromationButton->setText("Inf. about the cell");

    // SETUP LABELS
    unitTypeLabel->setText("Unit type:");
    baseTypeLabel->setText("Base type:");
    unitSourceBaseLabel->setText("From wich base create unit:");
    basePositionLabel->setText("Base porition (x;y):");
    unitActionLabel->setText("Unit actions");
    unitSourceActionLabel->setText("Unit source:");
    unitDestActionLabel->setText("Unit dist:");
    logCoordsLabel->setText("Cell coords:");
    baseNameLabel->setText("Set base name:");
    cellInfromationWhoLabel->setText("What to find out about:");

    // SETUP LISTS
    unitTypeComboBox->addItem("Cannon fodder");
    unitTypeComboBox->addItem("Infantry");
    unitTypeComboBox->addItem("Shooter");
    unitTypeComboBox->addItem("Wizard");
    unitTypeComboBox->addItem("Cavalry");

    baseTypeComboBox->addItem("Hell base");
    baseTypeComboBox->addItem("Human base");

    cellInfromationWhoComboBox->addItem("Game");
    cellInfromationWhoComboBox->addItem("Base");
    cellInfromationWhoComboBox->addItem("Unit");
    cellInfromationWhoComboBox->addItem("Land");
    cellInfromationWhoComboBox->addItem("Item");

    // working zone - main widget
    QGridLayout *layout = new QGridLayout;

    // set main vertical layout
    this->setLayout(layout);

    // sets the stretch factor at position index
    // and aligning of main widget
    layout->setAlignment(Qt::AlignCenter);

    // set main widget of window
    this->setStyleSheet("QWidget { background: white; }");

    // LAYOUTS

    // unit
    QHBoxLayout *unitTypeLayout = new QHBoxLayout;
    unitTypeLayout->addWidget(unitTypeLabel);
    unitTypeLayout->addWidget(unitTypeComboBox);
    QHBoxLayout *unitSourceBaseLayout = new QHBoxLayout;
    unitSourceBaseLayout->addWidget(unitSourceBaseLabel);
    unitSourceBaseLayout->addWidget(unitSourceBaseComboBox);
    QVBoxLayout *unitTotalLayout = new QVBoxLayout;
    unitTotalLayout->addLayout(unitTypeLayout);
    unitTotalLayout->addLayout(unitSourceBaseLayout);
    unitTotalLayout->addWidget(addUnitButton);

    // base
    QHBoxLayout *baseTypeLayout = new QHBoxLayout;
    baseTypeLayout->addWidget(baseTypeLabel);
    baseTypeLayout->addWidget(baseTypeComboBox);
    QHBoxLayout *baseCoordsLayout = new QHBoxLayout;
    baseCoordsLayout->addWidget(basePositionLabel);
    baseCoordsLayout->addWidget(xCoordBasePos);
    baseCoordsLayout->addWidget(yCoordBasePos);
    QHBoxLayout *baseNameLayout = new QHBoxLayout;
    baseNameLayout->addWidget(baseNameLabel);
    baseNameLayout->addWidget(baseNameText);
    QVBoxLayout *baseTotalLayout = new QVBoxLayout;
    baseTotalLayout->addLayout(baseTypeLayout);
    baseTotalLayout->addLayout(baseCoordsLayout);
    baseTotalLayout->addLayout(baseNameLayout);
    baseTotalLayout->addWidget(addBaseButton);

    // unit functions
    QHBoxLayout *unitActionsLayout = new QHBoxLayout;
    unitActionsLayout->addWidget(moveUnitButton);
    unitActionsLayout->addWidget(attackUnitButton);
    QHBoxLayout *unitSourceActionLayout = new QHBoxLayout;
    unitSourceActionLayout->addWidget(unitSourceActionLabel);
    unitSourceActionLayout->addWidget(xCoordUnitSourceAction);
    unitSourceActionLayout->addWidget(yCoordUnitSourceAction);
    QHBoxLayout *unitDestActionLayout = new QHBoxLayout;
    unitDestActionLayout->addWidget(unitDestActionLabel);
    unitDestActionLayout->addWidget(xCoordUnitDestAction);
    unitDestActionLayout->addWidget(yCoordUnitDestAction);
    QVBoxLayout *unitActionTotalLayout = new QVBoxLayout;
    unitActionTotalLayout->addLayout(unitSourceActionLayout);
    unitActionTotalLayout->addLayout(unitDestActionLayout);
    unitActionTotalLayout->addLayout(unitActionsLayout);

    // logs
    QHBoxLayout *cellInfrormationCoordsLayout = new QHBoxLayout;
    cellInfrormationCoordsLayout->addWidget(logCoordsLabel);
    cellInfrormationCoordsLayout->addWidget(xCoordLogPos);
    cellInfrormationCoordsLayout->addWidget(yCoordLogPos);
    QHBoxLayout *cellInfrormationWhoLayout = new QHBoxLayout;
    cellInfrormationWhoLayout->addWidget(cellInfromationWhoLabel);
    cellInfrormationWhoLayout->addWidget(cellInfromationWhoComboBox);
    QVBoxLayout *logTotalLayout = new QVBoxLayout;
    logTotalLayout->addWidget(logs);
    logTotalLayout->addLayout(cellInfrormationCoordsLayout);
    logTotalLayout->addLayout(cellInfrormationWhoLayout);
    logTotalLayout->addWidget(cellInfromationButton);

    // total work bar layout
    QVBoxLayout *workBarLayout = new QVBoxLayout;
    workBarLayout->addLayout(unitTotalLayout);
    workBarLayout->addLayout(baseTotalLayout);
    workBarLayout->addLayout(unitActionTotalLayout);
    workBarLayout->addLayout(logTotalLayout);

    layout->addWidget(visualField, 0, 0, 3, 3, Qt::AlignCenter);
    layout->addLayout(workBarLayout, 0, 4, 3, 4, Qt::AlignLeft);
}

void GameWindow::startNewPlayingWindow(size_t gameFieldSize_, size_t playersCount_)
{
#ifdef QT_DEBUG
    qDebug() << "Debug: was created MainWindow with field: size - " << gameFieldSize_ << " ; players count - " << playersCount_ << endl;
#endif
    gameFieldSize = gameFieldSize_;
    playersCount = playersCount_;

    // SIGNALS AND SLOT CONNECTION
    connect(addBaseButton, &QPushButton::clicked, this, &GameWindow::on_addBaseButton_clicked);
    connect(addUnitButton, &QPushButton::clicked, this, &GameWindow::on_addUnitButton_clicked);
    connect(moveUnitButton, &QPushButton::clicked, this, &GameWindow::on_moveUnitButton_clicked);
    connect(attackUnitButton, &QPushButton::clicked, this, &GameWindow::on_attackUnitButton_clicked);
    connect(cellInfromationButton, &QPushButton::clicked, this, &GameWindow::on_cellInfromationButton_clicked);
    emit createFieldRequest(gameFieldSize_, playersCount_);

    showMaximized();
}

void GameWindow::createLoggerRequest(eLOGGER_TYPE type, eLOGGER_OUTPUT_FORMAT format)
{
    emit createLoggerInFacadeRequest(type, format);
}

void GameWindow::on_addBaseButton_clicked()
{
#ifdef QT_DEBUG
    qDebug() << "Debug: request for " << (baseTypeComboBox->currentIndex() == 0 ? "Hell base" : "Human base") << " on position: (" << xCoordBasePos->value() << ";" << yCoordBasePos->value() << ") with name: " + baseNameText->text() << endl;
#endif
    if(baseNameText->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Empty base name"), tr("Base name can't be empty.\nPlease enter it."), QMessageBox::Ok);
    }
    unitSourceBaseComboBox->addItem(baseNameText->text());
    emit addBaseRequest(baseTypeComboBox->currentIndex() == 0 ? HELL_BASE : HUMAN_BASE, xCoordBasePos->value(), yCoordBasePos->value(), baseNameText->text());
}

void GameWindow::on_addUnitButton_clicked()
{
    if(unitSourceBaseComboBox->currentIndex() == -1)
    {
        throw std::invalid_argument("No existing base for unit creation");
    }

    QString unitTypeStr("NULL");
    eUnitsType unitType;
    switch(unitTypeComboBox->currentIndex())
    {
        case 0:
            unitTypeStr = "Cannon fodder";
            unitType = CANNON_FODDER;
            break;
        case 1:
            unitTypeStr = "Infantry";
            unitType = INFANTRY;
            break;
        case 2:
            unitTypeStr = "Shooter";
            unitType = SHOOTER;
            break;
        case 3:
            unitTypeStr = "Wizard";
            unitType = WIZARD;
            break;
        case 4:
            unitTypeStr = "Cavalry";
            unitType = CAVALRY;
            break;
    }

#ifdef QT_DEBUG
    qDebug() << "Debug: request for unit of type: " << unitTypeStr << (" type with source base: " + unitSourceBaseComboBox->currentText()) << endl;
#endif
    emit addUnitRequest(unitType, unitSourceBaseComboBox->currentText());
}

void GameWindow::on_moveUnitButton_clicked()
{
#ifdef QT_DEBUG
    qDebug() << "Debug:: request for unit move from: (" << xCoordUnitSourceAction->value() << ";" << yCoordUnitSourceAction->value() << ") to (" << xCoordUnitDestAction->value() << ";" << yCoordUnitDestAction->value() << ")" << endl;
#endif
    emit moveUnitRequest(xCoordUnitSourceAction->value(), yCoordUnitSourceAction->value(), xCoordUnitDestAction->value(), yCoordUnitDestAction->value());
}

void GameWindow::on_attackUnitButton_clicked()
{
#ifdef QT_DEBUG
    qDebug() << "Debug:: request for unit attack from: (" << xCoordUnitSourceAction->value() << ";" << yCoordUnitSourceAction->value() << ") to (" << xCoordUnitDestAction->value() << ";" << yCoordUnitDestAction->value() << ")" << endl;
#endif
    emit moveUnitRequest(xCoordUnitSourceAction->value(), yCoordUnitSourceAction->value(), xCoordUnitDestAction->value(), yCoordUnitDestAction->value());
}

void GameWindow::on_cellInfromationButton_clicked()
{
#ifdef QT_DEBUG
    qDebug() << "Debug:: request infrormation about " << cellInfromationWhoComboBox->currentText() << " on (" << xCoordLogPos->value() << ";" << yCoordLogPos->value() << ") coord" << endl;
#endif
    eRequest infRequest;
    switch(cellInfromationWhoComboBox->currentIndex())
    {
        case -1:
            infRequest = NONE;
            break;
        case 0:
            infRequest = GAME_INFO;
            break;
        case 1:
            infRequest = BASE_INFO;
            break;
        case 2:
            infRequest = UNIT_INFO;
            break;
        case 3:
            infRequest = LAND_INFO;
            break;
        case 4:
            infRequest = LAND_INFO;
            break;
        case 5:
            infRequest = ITEM_INFO;
            break;
    }
    emit cellUnfromationRequest(xCoordLogPos->value(), yCoordLogPos->value(), infRequest);
}
