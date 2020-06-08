#ifndef SPLASHMESSAGES_H
#define SPLASHMESSAGES_H

#include <list>

class GameInfoWindow;
namespace sf {
    class RenderWindow;
}

class SplashMessages
{
    struct Splash{
        GameInfoWindow *message;
        float timer;
    };

    std::list<Splash> messages;

public:
    ~SplashMessages();
    void splash(GameInfoWindow *message);
    void update(float ms);
    void draw(sf::RenderWindow &window);
};

#endif // SPLASHMESSAGES_H
