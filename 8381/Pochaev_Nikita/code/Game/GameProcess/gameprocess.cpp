#include "Game/GameProcess/gameprocess.h"

void SignalSlotGameProcess::on_passMove_button_clicked()
{
    currentState = currentState->passTheMove();
    emit setCurrentPlayerNumber(currentState->getPlayerNumb());
    updateResults();
}
