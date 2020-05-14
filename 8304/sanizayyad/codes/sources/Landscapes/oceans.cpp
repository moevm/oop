#include "oceans.hpp"

void OceansLandscape::hurtUnit(std::shared_ptr<Unit> unit) const
{
    if (unit) {
        unit->makeDamage(5);
    }
}


bool OceansLandscape::canMove(std::shared_ptr<Unit> unit) const
{
//    not used
    return true;
}


std::shared_ptr<Landscape> OceansLandscape::clone() const
{
    std::shared_ptr<Landscape> landscape(new OceansLandscape);
    return landscape;
}


char OceansLandscape::draw() const
{
    return 'O';
}
