#include "splash_messages.h"

#include "GUI/game_info_window.h"
#include <SFML/Graphics/RenderWindow.hpp>


SplashMessages::~SplashMessages(){
    for(auto &s: messages){
        delete s.message;
    }
}


void SplashMessages::splash(GameInfoWindow *message){
    messages.push_front(Splash{message, 3000.f});
    if(messages.size() > 3){
        delete messages.back().message;
        messages.pop_back();
    }
}


void SplashMessages::update(float ms){
    for(auto it = messages.begin();
        it != messages.end(); it++)
    {
        it->timer -= ms;
        if(it->timer <= 0){
            it = messages.erase(it);
        }
    }
}


void SplashMessages::draw(sf::RenderWindow &window){
    size_t i = 0;
    for(auto &s: messages){
        int alpha;
        if(s.timer < 800){
            alpha = s.timer/800*0xFF;
        } else {
            alpha = 0xFF;
        }

        s.message->draw(window.getSize().x/2.f - s.message->getSize().x/2.f,
                        20 + 40*(i), alpha);
        i++;
    }
}
