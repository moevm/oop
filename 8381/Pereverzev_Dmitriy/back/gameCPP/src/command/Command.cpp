#include "Command.hpp"

void Command::eventHandler(Event *event)
{
    fireEvent(event->getSEventId(), event->getData());
}