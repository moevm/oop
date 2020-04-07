#include "gamewindow.h"

GameWindow::GameWindow() :
    addUnitButton(new QPushButton),
    unitTypeLabel(new QLabel),
    unitTypeComboBox(new QComboBox),
    unitPositionLabel(new QLabel),
    xCoordUnitPos(new QSpinBox),
    yCoordUnitPos(new QSpinBox),

    addBaseButton(new QPushButton),
    baseTypeLabel(new QLabel),
    baseTypeComboBox(new QComboBox),
    basePositionLabel(new QLabel),
    xCoordBasePos(new QSpinBox),
    yCoordBasePos(new QSpinBox),

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
    unitTypeLabel->setText("Unit types:");
    baseTypeLabel->setText("Base types");
    unitPositionLabel->setText("Unit position (x;y):");
    basePositionLabel->setText("Base porition (x;y):");
    unitActionLabel->setText("Unit actions");
    unitSourceActionLabel->setText("Unit source:");
    unitDestActionLabel->setText("Unit dist:");
    logCoordsLabel->setText("Cell coords:");

    // SETUP LISTS
    unitTypeComboBox->addItem("Cannon fodder");
    unitTypeComboBox->addItem("Infantry");
    unitTypeComboBox->addItem("Shooter");
    unitTypeComboBox->addItem("Wizard");
    unitTypeComboBox->addItem("Cavalry");

    baseTypeComboBox->addItem("Hell base");
    baseTypeComboBox->addItem("Human base");

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
    QHBoxLayout *unitCoordsLayout = new QHBoxLayout;
    unitCoordsLayout->addWidget(unitPositionLabel);
    unitCoordsLayout->addWidget(xCoordUnitPos);
    unitCoordsLayout->addWidget(yCoordUnitPos);
    QVBoxLayout *unitTotalLayout = new QVBoxLayout;
    unitTotalLayout->addLayout(unitTypeLayout);
    unitTotalLayout->addLayout(unitCoordsLayout);
    unitTotalLayout->addWidget(addUnitButton);

    // base
    QHBoxLayout *baseTypeLayout = new QHBoxLayout;
    baseTypeLayout->addWidget(baseTypeLabel);
    baseTypeLayout->addWidget(baseTypeComboBox);
    QHBoxLayout *baseCoordsLayout = new QHBoxLayout;
    baseCoordsLayout->addWidget(basePositionLabel);
    baseCoordsLayout->addWidget(xCoordBasePos);
    baseCoordsLayout->addWidget(yCoordBasePos);
    QVBoxLayout *baseTotalLayout = new QVBoxLayout;
    baseTotalLayout->addLayout(baseTypeLayout);
    baseTotalLayout->addLayout(baseCoordsLayout);
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
    QVBoxLayout *logTotalLayout = new QVBoxLayout;
    logTotalLayout->addWidget(logs);
    logTotalLayout->addLayout(cellInfrormationCoordsLayout);
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
    gameFieldSize = gameFieldSize_;
    playersCount = playersCount_;
    showMaximized();
}
