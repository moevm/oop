#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include "coordinate.h"
#include "logwriter.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->loadInfo();
    connect(ui->btnReplace,SIGNAL(clicked(bool)),this,SLOT(btnReplace_clicked()));
    connect(ui->btnHandle,SIGNAL(clicked(bool)),this,SLOT(btnHandle_clicked()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(actionSave_triggered()));
    connect(ui->actionLoad,SIGNAL(triggered(bool)),this,SLOT(actionLoad_triggered()));

    LogWriter::getInstance().changeMode(LogWriter::BUFFERED_LOG);
    LogWriter::getInstance().log("Program initialization completed");

}

void MainWindow::loadInfo(){
    ui->lstHandlers->clear();
    for(std::string s : this->controller.getHandlersInfo()){
        ui->lstHandlers->addItem(QString::fromStdString(s)); ;
    }
    ui->lblModelState->setText(QString::fromStdString(controller.getModelState()));
}
void MainWindow::btnReplace_clicked(){
    try{
        controller.replace(ui->txtRepId1->text().toUInt(),ui->txtRepId2->text().toUInt());
        this->loadInfo();
        LogWriter::getInstance().log("Replaced handler ("+ui->txtRepId1->text().toStdString()
                                     +") with ("+ui->txtRepId2->text().toStdString()+")");
    }catch(const std::exception& e){
        LogWriter::getInstance().log(" Error: "+std::string(e.what()));
        QMessageBox::critical(this,QString("Error"),QString(e.what()));
    }
}
void MainWindow::btnHandle_clicked(){
    try{
        //Coordinate c = Coordinate::fromString(ui->txtValue0->text().toStdString());
        double c1 = ui->txtValue0->text().toDouble();
        double c2 = ui->txtValue1->text().toDouble();

        controller.handle(c1,c2);
        this->loadInfo();

        LogWriter::getInstance().log("Handled input: "+ui->txtValue0->text().toStdString()
                                     +" "+ui->txtValue1->text().toStdString());
    }catch(const std::exception& e){
        LogWriter::getInstance().log(" Error: "+std::string(e.what()));
        QMessageBox::critical(this,QString("Error"),QString(e.what()));
    }
}

void MainWindow::actionSave_triggered(){
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save state"), "",
        tr("Binary File (*.bin);;Text File (*.txt)"));

    if((fileName.toStdString().compare("")!=0))
    {
        QFileInfo fi(fileName);
        QString ext = fi.suffix();
        if(ext.toStdString().compare("bin")==0){
            controller.saveToBinFile(fileName.toStdString());
        }else if(ext.toStdString().compare("txt")==0){
            controller.saveToTextFile(fileName.toStdString());
        }
    }

}
void MainWindow::actionLoad_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load state"), "",
        tr("Binary File (*.bin);;Text File (*.txt)"));
    if((fileName.toStdString().compare("")!=0))
    {
        QFileInfo fi(fileName);
        QString ext = fi.suffix();
        if(ext.toStdString().compare("bin")==0){
            controller.loadFromBinFile(fileName.toStdString());
        }else if(ext.toStdString().compare("txt")==0){
            controller.loadFromTextFile(fileName.toStdString());
        }
        loadInfo();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
