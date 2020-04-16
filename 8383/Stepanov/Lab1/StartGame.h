
#include "Field.h"
#include "Units.h"
#include <memory>

#ifndef StartGame_h
#define StartGame_h



class Game {
    
    
    Unit* firstPlayer[9];
    Unit* secondPlayer[9];
    Iterator::Field f;
    int x, y;
    
    char numberSUnitsFirstPlayer[3] = {'/', '/', '/'};  // '/' == 47
    char numberSUnitsSecondPlayer[3] = {'0', '0', '0'}; // '0' == 48
    int countUnitsFirstPlauer;
    int countUnitsSecondPlauer;


public:
    
    void startGame(){
        
        int chosenGame;
        
        
        do{
            std::cout << "Выберите игру : 1 - стандартная, 2 - пользовательская, 3 - завершение" << std::endl;
            std::cin >> chosenGame;
        
        
            if (std::cin.fail() || chosenGame > 3 || chosenGame < 1 ) // если предыдущее извлечение оказалось неудачным,
            {
                std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
                std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
                std::cout << "Неверный ввод!" << std::endl;
                continue;
            }
        
            break;
        }while(true);
        
        

        if (chosenGame == 1){
            x = 15;
            y = 15;
            standartGame();
            
        } else if (chosenGame == 2){
            modifiedGame();
        }
        

        
    }
    
private:
    

    void setUnitsToStart(){
        
        firstPlayer[0] = doUnits(0, numberSUnitsFirstPlayer[0], false);
        firstPlayer[1] = doUnits(1, numberSUnitsFirstPlayer[1], false);
        firstPlayer[2] = doUnits(1, numberSUnitsFirstPlayer[1], false);
        firstPlayer[3] = doUnits(2, numberSUnitsFirstPlayer[2], false);
        firstPlayer[4] = doUnits(2, numberSUnitsFirstPlayer[2], false);
        firstPlayer[5] = doUnits(2, numberSUnitsFirstPlayer[2], false);
        countUnitsFirstPlauer = 6;

        secondPlayer[0] = doUnits(0, numberSUnitsSecondPlayer[0], false);
        secondPlayer[1] = doUnits(1, numberSUnitsSecondPlayer[1], false);
        secondPlayer[2] = doUnits(1, numberSUnitsSecondPlayer[1], false);
        secondPlayer[3] = doUnits(2, numberSUnitsSecondPlayer[2], false);
        secondPlayer[4] = doUnits(2, numberSUnitsSecondPlayer[2], false);
        secondPlayer[5] = doUnits(2, numberSUnitsSecondPlayer[2], false);
        countUnitsSecondPlauer = 6;
        
        f.takeUnit(firstPlayer[0]->getName(), x-1, 0);
        firstPlayer[0]->setXY(x-1, 0);
        f.takeUnit(firstPlayer[1]->getName(), x-2, 0);
        firstPlayer[1]->setXY(x-2, 0);
        f.takeUnit(firstPlayer[2]->getName(), x-1, 1);
        firstPlayer[2]->setXY(x-1, 1);
        f.takeUnit(firstPlayer[3]->getName(), x-1, 2);
        firstPlayer[3]->setXY(x-1, 2);
        f.takeUnit(firstPlayer[4]->getName(), x-2, 1);
        firstPlayer[4]->setXY(x-2, 1);
        f.takeUnit(firstPlayer[5]->getName(), x-3, 0);
        firstPlayer[5]->setXY(x-3, 0);
        
        f.takeUnit(secondPlayer[0]->getName(), 0, y-1);
        secondPlayer[0]->setXY(0, y-1);
        f.takeUnit(secondPlayer[1]->getName(), 0, y-2);
        secondPlayer[1]->setXY(0, y-2);
        f.takeUnit(secondPlayer[2]->getName(), 1, y-1);
        secondPlayer[2]->setXY(1, y-1);
        f.takeUnit(secondPlayer[3]->getName(), 2, y-1);
        secondPlayer[3]->setXY(2, y-1);
        f.takeUnit(secondPlayer[4]->getName(), 1, y-2);
        secondPlayer[4]->setXY(1, y-2);
        f.takeUnit(secondPlayer[5]->getName(), 0, y-3);
        secondPlayer[5]->setXY(0, y-3);
        
    }
    
    Unit* doUnits(int whatUnit, char &unitNumber, bool isProtected){ // 2 - runner, 1 - shooter, 0 - smoker
        
        ConcreteUnitShooter sho;
        ConcreteUnitRunner run;
        ConcreteUnitSmoker smo;
        
        unitNumber += 2;
        
        if (whatUnit == 0 ) return smo.CreateUnit(unitNumber, isProtected);
        
        else if (whatUnit == 1) return sho.CreateUnit(unitNumber, isProtected);
        
        else return run.CreateUnit(unitNumber, isProtected);
        
    }
    
    
    bool choseUnitToMove (bool &endGame){
        
        char stroc[3];
      
        std::cout << "Введить имя персонажа и в какую сторону переместить (!5 w1)" << std::endl;
        std::cin.ignore(32767,'\n');
        stroc[0] = std::cin.get();
        stroc[1] = std::cin.get();
        stroc[2] = std::cin.get();
        if (stroc[0] == 'e' && stroc[1] == 'x' && stroc[2] == 'i' && std::cin.get() == 't'){
            std::cout << "Конец ввода" << std::endl;
            endGame = false;
            return true;
        }
        if (stroc[2] != ' ') return false;
        
        
        stroc[2] = std::cin.get();
        
        if ('1' <= stroc[0] &&  stroc[0] <='9'){
            
            return replaceUnit (stroc,secondPlayer , countUnitsSecondPlauer);
            
        } else {
            return replaceUnit (stroc,firstPlayer , countUnitsFirstPlauer);
        }
        
        return true;
    }
   
    
    bool replaceUnit (char stroc[3], Unit** units, int &countUnits){
    
    Unit* chosenUnit;
    int toX, toY;
        
        for (int i = 0; i < countUnits; i++){
   
    if (units[i]->name[0] == stroc[0] && units[i]->name[1] == stroc[1]){
                       chosenUnit = units[i];
                       break;
                   }
                   
                   if (i == countUnits-1) return false;
               }
               
               toX = chosenUnit->getX();
               toY = chosenUnit->getY();
               
               switch (stroc[2]) {
                   case 'w':
                       toY--;
                   break;
                   case 'a':
                       toX--;
                   break;
                   case 's':
                       toY++;
                   break;
                   case 'd':
                       toX++;
                   break;
                   
                   default:
                       return false;
                   break;
               }
               
        
        if (toX > x || toX < 0 || toY > y || toY < 0) return false;
        if (f.cellIsUsed(toX, toY)) return false;
               
        f.replaceUnit(chosenUnit->getX(), chosenUnit->getY(), toX, toY);
        chosenUnit->setXY(toX, toY);
        return true;
}
    
    
    
    
    void modifiedGame (){
        
        bool endGame = true;
            
        do{
            std::cout << "Введите размер поля (не менее 6х6)" << std::endl << "Пример: 12 13 (поле 12х13)" <<std::endl;
            std::cin >> x >> y;
               
               
            if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
            {
                std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
                std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
                std::cout << "Неверный ввод!" << std::endl;
                continue;
            }
            
            if (!(f.createField(x, y))){
                continue;
            }
               
            f.printField();
            break;
        }while(true);
        
        
        setUnitsToStart();
        f.printField();
        
        while (endGame) {
        
        
            std::cout << choseUnitToMove (endGame) << std::endl;
        
        
            f.printField();
        }
        
    }
    
    void standartGame() {
        
        
        bool endGame = true;
       
        f.createField(x, y);
        setUnitsToStart();
        f.printField();
        
        while (endGame) {


            std::cout << choseUnitToMove (endGame) << std::endl;


            f.printField();
        }

        
    }
    
};



#endif
