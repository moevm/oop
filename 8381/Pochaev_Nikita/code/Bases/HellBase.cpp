#include "HellBase.h"
#include "AuxiliaryFunctionality/TextColoring.h"

void HellBase::describeYourself()
{
    std::cout << ANSIColor::coloredString("I'm Hell Base!", ANSIColor::FG_GREEN) << std::endl;
    std::cout << "Current Health is: " << health << std::endl;
    std::cout << unitCount->getTotalInformation();
}

std::string HellBase::getInformationAbout()
{
    return "I'm Hell Base!\n Current Health is: " + std::to_string(health) + "\n" + unitCount->getTotalInformation();
}

eBaseType HellBase::getBaseType()
{
    return HELL_BASE;
}
