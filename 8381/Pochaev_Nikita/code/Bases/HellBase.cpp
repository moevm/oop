#include "HellBase.h"
#include "AuxiliaryFunctionality/TextColoring.h"

void HellBase::describeYourself()
{
    std::cout << ANSIColor::coloredString("I'm Hell Base!", ANSIColor::FG_GREEN) << std::endl;
    std::cout << "Current Health is: " << health << std::endl;
    std::cout << unitCount->getTotalInformation();
}
