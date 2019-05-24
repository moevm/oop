#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include "coordinate.h"
#include "logwriter.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "unitgraphics.h"
#include "arrowgraphics.h"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::srand(std::time(nullptr));

    connect(ui->btnReplace,SIGNAL(clicked(bool)),this,SLOT(btnReplace_clicked()));
    connect(ui->btnHandle,SIGNAL(clicked(bool)),this,SLOT(btnHandle_clicked()));
    connect(ui->btnUndo,SIGNAL(clicked(bool)),this,SLOT(btnUndo_clicked()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(actionSave_triggered()));
    connect(ui->actionLoad,SIGNAL(triggered(bool)),this,SLOT(actionLoad_triggered()));


    this->scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(this->scene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->scale(qreal(0.8), qreal(0.8));

    for(auto &id : controller.getUnitIds()){
        UnitGraphics *u = new UnitGraphics(id,this);
        units.insert(std::pair<std::size_t, UnitGraphics*>(id,u));
        scene->addItem(u);
    }

    this->loadInfo();

    LogWriter::getInstance().changeMode(LogWriter::BUFFERED_LOG);
    LogWriter::getInstance().log("Program initialization completed");

}

void MainWindow::focusItem(std::size_t id){
    ui->lstHandlers->item(map_row_id[id])->setSelected(true);
    ui->lstHandlers->setFocus();
}
void MainWindow::loadInfo(){
    ui->lstHandlers->clear();
    map_row_id.clear();
    int i = 0;
    for(auto pair : this->controller.getHandlersInfo()){

        ui->lstHandlers->addItem(QString::fromStdString(pair.second)); ;
        map_row_id.insert(std::pair<std::size_t,std::size_t>(pair.first,i));
        i++;
    }
    ui->lblModelState->setText(QString::fromStdString(controller.getModelState()));

    for( auto &item : scene->items()){
        if(dynamic_cast<ArrowGraphics*>(item)!=nullptr) scene->removeItem(item);
    }
//    for (const auto& u : units) {
//        scene->addItem(u.second);
//    }

    for(std::pair<std::size_t,std::size_t> &connection : controller.getConnections()){
        scene->addItem(new ArrowGraphics(units[connection.first],units[connection.second]));
    }


}
void MainWindow::btnUndo_clicked(){
    this->controller.undo();
    this->loadInfo();
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
