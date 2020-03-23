#include "mainwindow.h"

#include <QApplication>

#include <Units/Factory/abstractArmy.h>
#include <Units/Factory/creaturesArmy.h>
#include <Units/Factory/humanityArmy.h>


void example1(){
    PlayingField playingField(4, 4, 2);
    AbstractArmy* humanityArmy = new HumanityArmy();
    AbstractArmy* creaturesArmy = new CreaturesArmy();
    Arrow* archer = humanityArmy->createArrow();
    Cavelry* rider = creaturesArmy->createCavelry();
    Base *base1 = new Base(3, 100, 4, 4, 1);
    Base *base2 = new Base(3, 100, 4, 4, 2);
    playingField.setBase(base1);
    playingField.setBase(base2);
    playingField.addUnit(archer, 2, 2, 1);
    playingField.addUnit(rider, 1, 1, 2);


    cout<<playingField.getCell(1,1)->characteristic(1,1)<<endl;
    cout<<playingField.getCell(2,2)->characteristic(2,2)<<endl;

    cout << playingField.printBase(playingField.getBase1())<<endl;
    playingField.deleteUnit(archer);
    cout << playingField.printBase(playingField.getBase1())<<endl;

}

void example2(){
    PlayingField playingField(4, 4, 2);
    AbstractArmy* humanityArmy = new HumanityArmy();
    AbstractArmy* creaturesArmy = new CreaturesArmy();
    Arrow* archer = humanityArmy->createArrow();
    Cavelry* rider = creaturesArmy->createCavelry();
    Base *base1 = new Base(3, 100, 4, 4, 1);
    Base *base2 = new Base(3, 100, 4, 4, 2);
    playingField.setBase(base1);
    playingField.setBase(base2);
    playingField.addUnit(archer, 2, 2, 1);
    playingField.addUnit(rider, 1, 1, 2);

    playingField.moveUnit(archer, 1, 1);

}
void exp1(){
    PlayingField playingField(10, 10, 2);
    AbstractArmy* humanityArmy = new HumanityArmy();
    AbstractArmy* creaturesArmy = new CreaturesArmy();
    Arrow* archer = humanityArmy->createArrow();
    Cavelry* rider = creaturesArmy->createCavelry();
    Base *base1 = new Base(3, 100, 10, 10, 1);
    Base *base2 = new Base(3, 100, 10, 10, 2);
    playingField.setBase(base1);
    playingField.setBase(base2);
    playingField.addUnit(archer, 7, 7, 1);
    playingField.addUnit(rider, 1, 1, 2);
    cout<<playingField.getCell(8,8)->characteristic(8,8)<<endl;
    playingField.addNeutral(new DrinkPoison(new Covid19()), 8, 8);
    cout<<playingField.getCell(8,8)->characteristic(8,8)<<endl;
    playingField.moveUnit(archer, 1, 1);
    cout<<playingField.getCell(8,8)->characteristic(8,8)<<endl;
}
int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
    QCoreApplication a(argc, argv);
    exp1();
    //example2();
    //example3();
    return a.exec();


}
