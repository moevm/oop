#include "oceans.hpp"

void OceansLandscape::hurtUnit(std::shared_ptr<Unit> unit) const
{
//    not used
}


bool OceansLandscape::canMove(std::shared_ptr<Unit> unit) const
{
//    not used
    return false;
}


std::shared_ptr<Landscape> OceansLandscape::clone() const
{
    std::shared_ptr<Landscape> landscape(new OceansLandscape);
    return landscape;
}


char OceansLandscape::draw() const
{
    return '~';
}
