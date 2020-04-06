#include "HumanBase.h"
#include "AuxiliaryFunctionality/TextColoring.h"

void HumanBase::describeYourself()
{
    std::cout << ANSIColor::coloredString("I'm Human Base!", ANSIColor::FG_GREEN) << std::endl;
    std::cout << "Current Health is: " << health << std::endl;
    std::cout << unitCount->getTotalInformation();
}
