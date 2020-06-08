#include <cstdlib>
#include <ctime>
class Random{
public:
int percentRoll( int percent )
{
    srand(time(0));
    return (rand() % 100) < percent ? 1 : 0;
}
};
