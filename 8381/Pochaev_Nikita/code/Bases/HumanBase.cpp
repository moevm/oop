#include "HumanBase.h"
#include "AuxiliaryFunctionality/TextColoring.h"

void HumanBase::describeYourself()
{
    std::cout << ANSIColor::coloredString("I'm Human Base!", ANSIColor::FG_GREEN) << std::endl;
    std::cout << "Current Health is: " << health << std::endl;
    std::cout << unitCount->getTotalInformation();
}

std::string HumanBase::getInformationAbout()
{
    return "I'm Human Base!\nCurrent Health is: " + std::to_string(health) + "\n" + unitCount->getTotalInformation();
}

eBaseType HumanBase::getBaseType()
{
    return HUMAN_BASE;
}
