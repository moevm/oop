
#ifndef Memento_h
#define Memento_h
class GameMap;
class GameNeutralObjects;
class EnemiesEntity;
class FriendsEntity;
class Memento;
class GameMaster;
#include <vector>
#include <iostream>
#include <fstream>


class Caretaker{
private:
    std::vector<Memento*> mementos;
    GameMaster* gameMaster;

public:
    Caretaker(GameMaster* gameMaster);
    ~Caretaker();
    void backup();
    void restore();
    void showSaves();
    void loadFromFile();
    void saveToFile();
};


#endif /* Memento_h */
