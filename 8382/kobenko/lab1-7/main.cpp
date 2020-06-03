#include "game.h"

int main() {
    defaultCeil defC;
    deathCeil deaC;
    AwesomeCeil aweC;
    AwesomeItem aweI;
    DeathItem deaI;
    Heal h;
    BigHeal bh;
    Field field;
    field.CreatingField(defC, deaC, aweC, aweI, deaI, h, bh);
    Game game;
    game.InfiniteCycle(field);

    return 0;
}
