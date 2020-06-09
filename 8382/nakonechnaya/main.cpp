#include <iostream>
#include "Game.h"
using std::cout;
using std::endl;
using std::cin;

int main() {

    cout << "Rules:" << endl;
    cout << "1: Kill units\n2: Damage bases\nother: auto(Kill units)" << endl;
    int rule;
    cin >> rule;
    Rules *rules;
    switch (rule){
        case 1:{
            rules = new KillUnits;
            break;
        }
        case 2:{
            rules = new DamageBase;
            break;
        }
        default:
            rules = new KillUnits;
    }
    auto *game = new Game<Rules>(rules);
    game->startGame();

    return 0;
}