#include "field.h"
#include <conio.h>

#ifndef RULES_H
#define RULES_H

#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77


class Rules
{
protected:
    TerminalLog termLog;
    FileLog* fileLog = new FileLog("log.txt");
    int logFlag = 0;
    Field* field;
    int step = 1;
    Command* command;
    string saveFile = "save.txt";
    string loadFile = "load.txt";
    Memento* snap = nullptr;
    Unit* unit11 = nullptr;
    Unit* unit22 = nullptr;
public:
    Rules(){
        field = nullptr;
    }
    virtual Field* createField() = 0;
    virtual int action() = 0;
    Unit* getCurrentUnit(){
        if (step == 1){
            return unit11;
        }
        if (step == 2){
            return unit22;
        }
    }
};

class Rule1: public Rules{
    int key;
public:
    Field* createField() override{
        field = new Field(17, 17, 17*17);
        field->createBase(0, 17/2);
        field->createBase(17-1, 17/2);
        return field;
    }
    bool isLose(Field* field){
        if (field->isDestroyed() == 1){
            return 1;
        }
        if (field->isDestroyed() == 2){
            return 2;
        }
    }
    int action() override{
        key = getch();
        if (key == 'g'){
            return 1;
        }
        if (key == 's'){
            cout << "Would you like to create quick save or write your save in file(1 - quick, 2 - file): ";
            int fl = 0;
            cin >> fl;
            if (fl == 1){
                snap = new Memento(saveFile);
                snap = field->quickSave(snap);
            }
            if (fl == 2){
                cout << "Write file that you want to use to save: ";
                cin >> saveFile;
                snap = new Memento(saveFile);
                snap = field->quickSave(snap);
                snap->fileSave();
            }
        }
        if (key == 'd'){
            cout << "Choose the way to load(1 - from quicksave, 2 - from file): ";
            int fl2 = 0;
            cin >> fl2;
            if (fl2 == 1){
                field->quickLoad(snap);
                unit11 = new Unit;
                unit11 = field->changeUnit1(unit11);
            }
            if (fl2 == 2){
                Memento* snap2 = new Memento();
                snap2->fileLoad();
                field->quickLoad(snap2);
                unit11 = new Unit;
                unit11 = field->changeUnit1(unit11);
            }
        }
        if (key == '+'){
            logFlag++;
            if (logFlag == 1){
                cout << "\nNow its a logging in terminal!\n";
            }
            if (logFlag == 2){
                cout << "\nNow its a logging in file!\n";
            }
            if (logFlag > 2){
                cout << "\nNow its no logging\n";
                logFlag = 0;
            }
        }
        if (step == 1){
          //  key = getch();
            if (key == 'u'){
                cout << "choose the type of unit (from 0 to 5):" << endl;
                int code;
                cin >> code;
                if(code < 0 || code > 5){
                    cout << "Wrong, moron. Can you read at least, are you? I said FROM 0 TO 5. Try again:" << endl;
                    cin >> code;
                }
                if(code < 0 || code > 5){
                    cout << "Okey, I just give up, you are so stupid donkey, that it actually look like harassment from my side.\n I'll write instead of you, don't please me\n" << endl;
                    code = 4;
                }
                Player1Factory factory;
                field->setUnitFromBase(factory, 0, 17/2, code);
                if (logFlag == 1){
                    termLog.log("Unit of Player1 was created");
                }
                if (logFlag == 2){
                    fileLog->log("Unit of Player1 was created");
                }
                if(field->getLastUnit(code)){
                    unit11 = field->getLastUnit(code);
                    return 0;
                }
                else {
                    return 0;
                }
            }
            if (key == 'm'){
                cout << "\nPlayer 1 base gold: " << field->getBaseGold(0, 17/2) << " | Count of units: " << field->getBaseCountOfUnits(0, 17/2);
                if (logFlag == 1){
                    termLog.log("Check info of Player1 base");
                }
                if (logFlag == 2){
                    fileLog->log("Check info of Player1 base");
                }
                return 0;
            }
            if (key == 9){
                unit11 = field->changeUnit1(unit11);
                if (logFlag == 1){
                    termLog.log("Change Player1 current unit");
                }
                if (logFlag == 2){
                    fileLog->log("Change Player1 current unit");
                }
                return 0;
            }
            if (key == 'f'){
                Unit* unit2;
                unit2 = unit11;
                unit11 = field->changeUnit1(unit2);
                field->deleteUnit1(unit2);
                if (logFlag == 1){
                    termLog.log("Deleting Player1 unit");
                }
                if (logFlag == 2){
                    fileLog->log("Deleting Player1 unit");
                }
                return 0;
            }
            if (key == 224){
                key = getch();
                switch(key){
                case UP_ARROW:
                    command = new MoveUpCommand(field);
                    command->execute(unit11, &termLog, fileLog, logFlag, 1);
                    step = 2;
                    if (logFlag == 1){
                        termLog.log("Current unit goes up");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes up");
                    }
                    break;
                case DOWN_ARROW:
                    command = new MoveDownCommand(field);
                    command->execute(unit11, &termLog, fileLog, logFlag, 1);
                    step = 2;
                    if (logFlag == 1){
                        termLog.log("Current unit goes down");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes down");
                    }
                    break;
                case LEFT_ARROW:
                    command = new MoveLeftCommand(field);
                    command->execute(unit11, &termLog, fileLog, logFlag, 1);
                    step = 2;
                    if (logFlag == 1){
                        termLog.log("Current unit goes left");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes left");
                    }
                    break;
                case RIGHT_ARROW:
                    command = new MoveRightCommand(field);
                    command->execute(unit11, &termLog, fileLog, logFlag, 1);
                    step = 2;
                    if (logFlag == 1){
                        termLog.log("Current unit goes right");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes right");
                    }
                    break;
                default:
                    break;
                }
            }
            return 0;
        }
        if (step == 2){
        //    key = getch();
            if (key == 'n'){
                cout << "choose the type of unit (from 0 to 5):" << endl;
                int code;
                cin >> code;
                if(code < 0 || code > 5){
                    cout << "Wrong, moron. Can you read at least, are you? I said FROM 0 TO 5. Try again:" << endl;
                    cin >> code;
                }
                if(code < 0 || code > 5){
                    cout << "Okey, I just give up, you are so stupid donkey, that it actually look like harassment from my side.\n I'll write instead of you, don't please me\n" << endl;
                    code = 11;
                }
                code += 6;
                Player2Factory factory;
                field->setUnitFromBase(factory, 17-1, 17/2, code);
                if (logFlag == 1){
                    termLog.log("Unit of Player2 was created");
                }
                if (logFlag == 2){
                    fileLog->log("Unit of Player2 was created");
                }
                if(field->getLastUnit(code)){
                    unit22 = field->getLastUnit(code);
                    return 0;
                }
                else {
                    return 0;
                }
            }
            if (key == 'l'){
                cout << "\nPlayer 2 base gold: " << field->getBaseGold(17-1, 17/2) << " | Count of units: " << field->getBaseCountOfUnits(17-1, 17/2);
                if (logFlag == 1){
                    termLog.log("Check info of Player2 base");
                }
                if (logFlag == 2){
                    fileLog->log("Check info of Player2 base");
                }
                key = getch();
                return 0;
            }
            if (key == '-'){
                unit22 = field->changeUnit2(unit22);
                if (logFlag == 1){
                    termLog.log("Change Player2 current unit");
                }
                if (logFlag == 2){
                    fileLog->log("Change Player2 current unit");
                }
                return 0;
            }
            if (key == ']'){
                Unit* unit3;
                unit3 = unit22;
                unit22 = field->changeUnit2(unit3);
                field->deleteUnit2(unit3);
                if (logFlag == 1){
                    termLog.log("Deleting Player2 unit");
                }
                if (logFlag == 2){
                    fileLog->log("Deleting Player2 unit");
                }
                return 0;
            }
            if (key == 224){
                key = getch();
                switch(key){
                case UP_ARROW:
                    command = new MoveUpCommand(field);
                    command->execute(unit22, &termLog, fileLog, logFlag, 1);
                    step = 1;
                    if (logFlag == 1){
                        termLog.log("Current unit goes up");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes up");
                    }
                    break;
                case DOWN_ARROW:
                    command = new MoveDownCommand(field);
                    command->execute(unit22, &termLog, fileLog, logFlag, 1);
                    step = 1;
                    if (logFlag == 1){
                        termLog.log("Current unit goes down");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes down");
                    }
                    break;
                case LEFT_ARROW:
                    command = new MoveLeftCommand(field);
                    command->execute(unit22, &termLog, fileLog, logFlag, 1);
                    step = 1;
                    if (logFlag == 1){
                        termLog.log("Current unit goes left");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes left");
                    }
                    break;
                case RIGHT_ARROW:
                    command = new MoveRightCommand(field);
                    command->execute(unit22, &termLog, fileLog, logFlag, 1);
                    step = 1;
                    if (logFlag == 1){
                        termLog.log("Current unit goes right");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes right");
                    }
                    break;
                default:
                    break;
                }
            }
            return 0;
        }
    }
};

class Rule2: public Rules{        // второе правило - режим обогащения. побеждает первый, набивший 1000 голды.
    int key;
public:
    Field* createField() override{
        field = new Field(23, 23, 23*23);
        field->createBase(0, 23/2);
        field->createBase(23-1, 23/2);
        return field;
    }
    bool isLose(Field* field){
        if (field->isRich() == 1){
            cout << "Player 1 wins!!!\n";
            return true;
        }
        if (field->isRich() == 2){
            cout << "Player 2 wins!!!\n";
            return true;
        }
    }
    int action() override{
        key = getch();
        if (key == 'g'){
            return 1;
        }
        if (key == 's'){
            cout << "Would you like to create quick save or write your save in file(1 - quick, 2 - file): ";
            int fl = 0;
            cin >> fl;
            if (fl == 1){
                snap = new Memento(saveFile);
                snap = field->quickSave(snap);
            }
            if (fl == 2){
                cout << "Write file that you want to use to save: ";
                cin >> saveFile;
                snap = new Memento(saveFile);
                snap = field->quickSave(snap);
                snap->fileSave();
            }
        }
        if (key == 'd'){
            cout << "Choose the way to load(1 - from quicksave, 2 - from file): ";
            int fl2 = 0;
            cin >> fl2;
            if (fl2 == 1){
                field->quickLoad(snap);
                unit11 = new Unit;
                unit11 = field->changeUnit1(unit11);
            }
            if (fl2 == 2){
                Memento* snap2 = new Memento();
                snap2->fileLoad();
                field->quickLoad(snap2);
                unit11 = new Unit;
                unit11 = field->changeUnit1(unit11);
            }
        }
        if (key == '+'){
            logFlag++;
            if (logFlag == 1){
                cout << "\nNow its a logging in terminal!\n";
            }
            if (logFlag == 2){
                cout << "\nNow its a logging in file!\n";
            }
            if (logFlag > 2){
                cout << "\nNow its no logging\n";
                logFlag = 0;
            }
        }
        if (step == 1){
       //     key = getch();
            if (key == 'u'){
                cout << "choose the type of unit (from 0 to 5):" << endl;
                int code;
                cin >> code;
                if(code < 0 || code > 5){
                    cout << "Wrong, moron. Can you read at least, are you? I said FROM 0 TO 5. Try again:" << endl;
                    cin >> code;
                }
                if(code < 0 || code > 5){
                    cout << "Okey, I just give up, you are so stupid donkey, that it actually look like harassment from my side.\n I'll write instead of you, don't please me\n" << endl;
                    code = 4;
                }
                Player1Factory factory;
                field->setUnitFromBase(factory, 0, 23/2, code);
                if (logFlag == 1){
                    termLog.log("Unit of Player1 was created");
                }
                if (logFlag == 2){
                    fileLog->log("Unit of Player1 was created");
                }
                if(field->getLastUnit(code)){
                    unit11 = field->getLastUnit(code);
                    return 0;
                }
                else {
                    return 0;
                }
            }
            if (key == 'm'){
                cout << "\nPlayer 1 base gold: " << field->getBaseGold(0, 23/2) << " | Count of units: " << field->getBaseCountOfUnits(0, 23/2);
                if (logFlag == 1){
                    termLog.log("Check info of Player1 base");
                }
                if (logFlag == 2){
                    fileLog->log("Check info of Player1 base");
                }
                return 0;
            }
            if (key == 9){
                unit11 = field->changeUnit1(unit11);
                if (logFlag == 1){
                    termLog.log("Change Player1 current unit");
                }
                if (logFlag == 2){
                    fileLog->log("Change Player1 current unit");
                }
                return 0;
            }
            if (key == 'f'){
                Unit* unit2;
                unit2 = unit11;
                unit11 = field->changeUnit1(unit2);
                field->deleteUnit1(unit2);
                if (logFlag == 1){
                    termLog.log("Deleting Player1 unit");
                }
                if (logFlag == 2){
                    fileLog->log("Deleting Player1 unit");
                }
                return 0;
            }
            if (key == 224){
                key = getch();
                switch(key){
                case UP_ARROW:
                    command = new MoveUpCommand(field);
                    command->execute(unit11, &termLog, fileLog, logFlag, 2);
                    step = 2;
                    if (logFlag == 1){
                        termLog.log("Current unit goes up");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes up");
                    }
                    break;
                case DOWN_ARROW:
                    command = new MoveDownCommand(field);
                    command->execute(unit11, &termLog, fileLog, logFlag, 2);
                    step = 2;
                    if (logFlag == 1){
                        termLog.log("Current unit goes down");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes down");
                    }
                    break;
                case LEFT_ARROW:
                    command = new MoveLeftCommand(field);
                    command->execute(unit11, &termLog, fileLog, logFlag, 2);
                    step = 2;
                    if (logFlag == 1){
                        termLog.log("Current unit goes left");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes left");
                    }
                    break;
                case RIGHT_ARROW:
                    command = new MoveRightCommand(field);
                    command->execute(unit11, &termLog, fileLog, logFlag, 2);
                    step = 2;
                    if (logFlag == 1){
                        termLog.log("Current unit goes right");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes right");
                    }
                    break;
                default:
                    break;
                }
            }
            return 0;
        }
        if (step == 2){
           // key = getch();
            if (key == 'n'){
                cout << "choose the type of unit (from 0 to 5):" << endl;
                int code;
                cin >> code;
                if(code < 0 || code > 5){
                    cout << "Wrong, moron. Can you read at least, are you? I said FROM 0 TO 5. Try again:" << endl;
                    cin >> code;
                }
                if(code < 0 || code > 5){
                    cout << "Okey, I just give up, you are so stupid donkey, that it actually look like harassment from my side.\n I'll write instead of you, don't please me\n" << endl;
                    code = 11;
                }
                code += 6;
                Player2Factory factory;
                field->setUnitFromBase(factory, 23-1, 23/2, code);
                if (logFlag == 1){
                    termLog.log("Unit of Player2 was created");
                }
                if (logFlag == 2){
                    fileLog->log("Unit of Player2 was created");
                }
                if(field->getLastUnit(code)){
                    unit22 = field->getLastUnit(code);
                    return 0;
                }
                else {
                    return 0;
                }
            }
            if (key == 'l'){
                cout << "\nPlayer 2 base gold: " << field->getBaseGold(23-1, 23/2) << " | Count of units: " << field->getBaseCountOfUnits(23-1, 23/2);
                if (logFlag == 1){
                    termLog.log("Check info of Player2 base");
                }
                if (logFlag == 2){
                    fileLog->log("Check info of Player2 base");
                }
                key = getch();
                return 0;
            }
            if (key == '-'){
                unit22 = field->changeUnit2(unit22);
                if (logFlag == 1){
                    termLog.log("Change Player2 current unit");
                }
                if (logFlag == 2){
                    fileLog->log("Change Player2 current unit");
                }
                return 0;
            }
            if (key == ']'){
                Unit* unit3;
                unit3 = unit22;
                unit22 = field->changeUnit2(unit3);
                field->deleteUnit2(unit3);
                if (logFlag == 1){
                    termLog.log("Deleting Player2 unit");
                }
                if (logFlag == 2){
                    fileLog->log("Deleting Player2 unit");
                }
                return 0;
            }
            if (key == 224){
                key = getch();
                switch(key){
                case UP_ARROW:
                    command = new MoveUpCommand(field);
                    command->execute(unit22, &termLog, fileLog, logFlag, 2);
                    step = 1;
                    if (logFlag == 1){
                        termLog.log("Current unit goes up");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes up");
                    }
                    break;
                case DOWN_ARROW:
                    command = new MoveDownCommand(field);
                    command->execute(unit22, &termLog, fileLog, logFlag, 2);
                    step = 1;
                    if (logFlag == 1){
                        termLog.log("Current unit goes down");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes down");
                    }
                    break;
                case LEFT_ARROW:
                    command = new MoveLeftCommand(field);
                    command->execute(unit22, &termLog, fileLog, logFlag, 2);
                    step = 1;
                    if (logFlag == 1){
                        termLog.log("Current unit goes left");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes left");
                    }
                    break;
                case RIGHT_ARROW:
                    command = new MoveRightCommand(field);
                    command->execute(unit22, &termLog, fileLog, logFlag, 2);
                    step = 1;
                    if (logFlag == 1){
                        termLog.log("Current unit goes right");
                    }
                    if (logFlag == 2){
                        fileLog->log("Current unit goes right");
                    }
                    break;
                default:
                    break;
                }
            }
            return 0;
        }
    }
};

#endif // RULES_H
