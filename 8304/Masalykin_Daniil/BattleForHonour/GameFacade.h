#ifndef BATTLEFORHONOUR_GAMEFACADE_H
#define BATTLEFORHONOUR_GAMEFACADE_H


#include <sstream>
#include "GameState.h"
#include "User/CommandInterpreter.h"


template<typename Rule, int playersCount>
class GameFacade: public GameState {

private:

    CommandInterpreter actCommand;
    Rule rule;
    GameFacade(int fieldWidth, int fieldHeight):
        GameState(playersCount, fieldWidth, fieldWidth, new Rule){}

public:

    static GameFacade& single(){
        Rule rule;
        static GameFacade subSystem(rule.fieldWidth, rule.fieldHeight);
        return subSystem;
    }

    friend std::ostream &operator<<(std::ostream &stream, const GameFacade &game){
        stream << "Current user: " << game.currentUser << std::endl;
        stream << game.gameField << std::endl;
        return stream;
    }

    bool isOver(){
        return rule.isOver(*this);
    }

    void nextTurn(){

        std::string commandString;
        std::getline(std::cin, commandString);

        std::cout << "---------------------------------------------" << std::endl;

        std::unique_ptr<Command> command = actCommand.handle(commandString);
        try {
            command->execute(*this);
        } catch(DoubleBasePlacingExc &exception) {
            std::cout << "Player " << exception.playerIndex << " trying to place second base." << std::endl;
        } catch (DoublePlacingExc &exception){
            std::cout << "This cell is full by another object." << std::endl;
        } catch (OutOfRangeExc &exception){
            std::cout << "Out of range. Cell point " << exception.x << " " << exception.y << " is not exist." << std::endl;
        } catch (ImpossibleMoveExc &exception){
            std::cout << "Can't move to this cell. They busy by other object." << std::endl;
        } catch (InvalidFileLoadExc &exception){
            std::cout << "Wrong file." << std::endl;
        } catch (...){
            std::cout << "Unknown error." << std::endl;
        }
        gameActions.push_back(command->getSnapshot());
        nextUser();
    }

};


#endif //BATTLEFORHONOUR_GAMEFACADE_H
