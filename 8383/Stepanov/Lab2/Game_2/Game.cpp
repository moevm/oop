//
//  Game.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Game.hpp"

void Game::startGame() {
    
    std::cout << "Start" << std::endl;
    
    height = 10;
    width = 10;
    
    field = new Field();
    
    field->createField(height, width);
    
    first = new Base (1, width-1, 0, field);
    second = new Base (2, 0, height-1, field);
    
    first->setFirstUnits(field);                        /// расстановка юнитов на позиции
    second->setFirstUnits(field);
    
    first->setNeutralObjects(field);                    /// расстановка нейтральных объктов на позиции
    second->setNeutralObjects(field);

    bool endGame = true;
    
    do{
        printField();                           /// печать поля
        
        printPoints();                          /// печать характеристик юнитов
                
        std::cout << choseUnitToMove(endGame) << std::endl;     /// ввод команд
        printf("\033c");
                
                  
    }while(endGame);
}

void Game::printPoints () {
    for (int i = 0; i < 9; i++){
                
        Unit *firstUnit = first->getUnit(i);
        Unit *secondUnit = second->getUnit(i);

        if (!(firstUnit || secondUnit)) continue;

        if (firstUnit) { std::cout <<firstUnit->getName() <<
            "\th = " << firstUnit->health.getPoint() <<
            "\ta = " << firstUnit->armor.getPoint() <<
            "\tp = " << firstUnit->attack.getPoint() << "\t";

        } else {
            std::cout << "\t\t\t\t\t\t\t";
        }

        if (secondUnit) { std::cout <<secondUnit->getName() <<
            "\th = " << secondUnit->health.getPoint() <<
            "\ta = " << secondUnit->armor.getPoint() <<
            "\tp = " << secondUnit->attack.getPoint() << std::endl;

        } else {
            std::cout << std::endl;
        }
    }
}

void Game::printField () {

    for (int i = -1; i <= height; i++){
        
        for (int j = -1; j <= width; j++){

            if ((i == -1 && j == -1) || (i == -1 && j == width) ||
                (i == height && j == -1) || (i == height && j == width)){

                std::cout << " ";

            } else if (i == -1 || i == height) {

                std::cout << "--";

            } else if (j == -1 || j == width) {

                std::cout << "|";

            } else {
                
                
                switch (field->whatInCell(j, i)) {
                        case 1:
                        std::cout << field->getBase(j, i);
                            break;
                    case 2:
                        std::cout << field->getNeutralObject(j, i)->getName();
                        break;
                        
                        case 3:
                        std::cout << field->getUnit(j, i)->getName();
                            break;
                        
                        case 4:
                        std::cout << field->getLandscape(j, i)->getName();
                        std::cout << field->getLandscape(j, i)->getName();
                            break;

                            
                        default:
                            std::cout << "  ";
                            break;
                    
                    
                
                    

                }
            }
        }
        
        std::cout << std::endl;
    }
}




bool Game::choseUnitToMove (bool &endGame){
           
       char stroc[3];
       bool isHit = false;
       char n;
       
       std::cout << "Введить имя персонажа и в какую сторону переместить или взаимодействовать (!5 w1)" << std::endl;
       
       
       stroc[0] = std::cin.get();
       stroc[1] = std::cin.get();
       stroc[2] = std::cin.get();
       
       if (stroc[0] == 'e' && stroc[1] == 'x' && stroc[2] == 'i' && std::cin.get() == 't') {
           
           std::cout << "Конец ввода" << std::endl;
           endGame = false;
           return true;
       }
         
       if (stroc[2] != ' ') {
           
           std::cin.ignore(32767,'\n');
           return false;
       }
           
           
       stroc[2] = std::cin.get();
       
       n = std::cin.get();
     
       if (n == 'h'){
           isHit = true;
           
           if (std::cin.get() != '\n'){
               
               std::cin.ignore(32767,'\n');
               return false;
           }
       } else if (n == 'm'){
           if (std::cin.get() != '\n'){
               
               std::cin.ignore(32767,'\n');
               return false;
           }
           
       } else if (n != '\n'){
           
           std::cin.ignore(32767,'\n');
           return false;
       }
           
       
    Base *base;
       
       if ('1' <= stroc[0] &&  stroc[0] <='9') {
           base = second;
       } else {
           base = first;
       }
         
    
       int toX, toY;
        int x, y;
          
          Unit* chosenUnit  = base->findUnit(stroc);
          
          if (chosenUnit == nullptr){
              std::cout << "Юнит не найден"<< std::endl;
              return false;
          }
          
                     
          x = chosenUnit->getX();
          y = chosenUnit->getY();
          
          toX = x;
          toY = y;
                     
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
                     
       
          if (isHit){
              
              if (chosenUnit->uid != 0 && field->whatInCell(toX, toY) == 2) {   // if uid == 0 -> chosenUnit is Smoker
                                                                                // whatInCell == 2 -> in cell neutralObject
                  NeutralObject *n = field->getNeutralObject(toX, toY);
                  
                  if (n) {
                      *n += chosenUnit;
                  }
                  
                  
              }
            
              
              
          } else {
              
              if (field->whatInCell(toX, toY) == 4){ // if whatInCell == 4 -> in Cell only landscape
                  
                  Proxy p (field->getLandscape(toX, toY));
                  
                  if (p.doSomething(chosenUnit) && field->replaceUnit(x, y, toX, toY))
                      
                      chosenUnit->setXY(toX, toY);
             
              } else {return false;}
              
          }
          return true;
   }
       

