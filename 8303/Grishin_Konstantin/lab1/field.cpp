#include <SFML/Graphics.hpp>
#include <stack>

#include "field.h"


void Field::findPossibleWay(){
    for(auto entity: entities)
    {
        if(entity->selected_p()){
            std::vector<Point> visited;

            std::vector<Point> in_progress;
            in_progress.push_back(entity->pos());
            for(unsigned int i = 0; i < 1 + entity->remainigSteps(); i++){
                unsigned int j;
                unsigned int in_progress_size = in_progress.size();
                for(j = 0; j < in_progress_size; j++){

                    unsigned int c;
                    for(c = 0; c < visited.size(); c++){
                        if(visited[c] == in_progress[j])
                            break;
                    }

                    if(c == visited.size())
                        visited.push_back(in_progress[j]);

                    in_progress.push_back(in_progress[j] + Point(0,1));
                    in_progress.push_back(in_progress[j] + Point(1,0));
                    in_progress.push_back(in_progress[j] - Point(0,1));
                    in_progress.push_back(in_progress[j] - Point(1,0));
                }
                in_progress.erase(in_progress.begin(), in_progress.begin()+j);
            }
            visited.erase(visited.begin());
            possible_way = visited;
            return;
        }
    }
}


void Field::findAttackArea(){
    for(auto entity: entities){
        if(entity->selected_p()){
            std::vector<Point> visited;

            std::vector<Point> in_progress;
            in_progress.push_back(entity->pos());

            int outer = 0;
            int inner = 0;

            switch (entity->attackType()){
            case Entity::Attack::Melee:
                outer = 2;
                break;

            case Entity::Attack::Range:
                inner = dynamic_cast<Range*>(entity)->blindZone();
                outer = dynamic_cast<Range*>(entity)->attackRange();
                break;

            case Entity::Attack::Absent:
                break;
            }

            for(unsigned int i = 0; i < 1 + outer; i++){
                unsigned int j;
                unsigned int in_progress_size = in_progress.size();
                for(j = 0; j < in_progress_size; j++){

                    Point difference = in_progress[j] - entity->pos();
                    if(abs(difference.x) + abs(difference.y) > inner){
                        unsigned int c;
                        for(c = 0; c < visited.size(); c++){
                            if(visited[c] == in_progress[j])
                                break;
                        }

                        if(c == visited.size())
                            visited.push_back(in_progress[j]);
                    }

                    in_progress.push_back(in_progress[j] + Point(0,1));
                    in_progress.push_back(in_progress[j] + Point(1,0));
                    in_progress.push_back(in_progress[j] - Point(0,1));
                    in_progress.push_back(in_progress[j] - Point(1,0));
                }
                in_progress.erase(in_progress.begin(), in_progress.begin()+j);
            }
            attack_area = visited;
            return;
        }
    }
}


Field::Field(sf::RenderTarget *target, int width, int height){
    if(width <= 0 || height <= 0) exit(1);

    this->target = target;

    iWidth = width;
    iHeight = height;

    iMaxUnits = static_cast<int>((width*height)*0.6f);

    cell_arr = new Cell*[iWidth * iHeight];
    for(int i = 0; i < width*height; i++){
        cell_arr[i] = new Cell;
    }

    unsigned int trg_w = target->getSize().x;
    unsigned int trg_h = target->getSize().y;

    const int outline = 3;
    cell_size = (std::min(trg_h, trg_w) - outline*2)/std::max(iWidth, iHeight) - 3;
}


Field::~Field(){
    delete [] cell_arr;
}


void Field::addUnit(Entity *unit){
    if(int(entities.size()) < iMaxUnits)
        entities.push_back(unit);
}


void Field::draw(){
    for(int y = 0; y < iHeight; y++){
        for(int x = 0; x < iWidth; x++){
            cell_arr[y*iWidth + x]->draw(target, Point{x, y}, cell_size);
        }
    }

    for(auto entity: entities){
        entity->draw(target, cell_size);
    }
}


void Field::spotCell(int x, int y, const sf::Color &color, int units)
{
    int x_pos = x;
    int y_pos = y;

    if(units == PIXELS){
        x_pos = x/(cell_size+3);
        y_pos = y/(cell_size+3);
    }

    sf::RectangleShape spot_light(sf::Vector2f(cell_size+6, cell_size+6));
    spot_light.setFillColor(color);
    spot_light.setPosition(x_pos * (cell_size+3), y_pos * (cell_size+3));

    target->draw(spot_light);
}


void Field::selectUnit(int x, int y, int units)
{
    int x_pos = x;
    int y_pos = y;

    if(units == PIXELS){
        x_pos = x/(cell_size+3);
        y_pos = y/(cell_size+3);
    }

    for(auto entity: entities)
    {
        if (entity->pos().x == x_pos && entity->pos().y == y_pos){
            attack_area.clear();
            possible_way.clear();

            if(entity->selected_p())
                entity->deselect();
            else{

                for(auto to_deselect: entities){
                    to_deselect->deselect();
                }

                entity->select();

                findPossibleWay();
                findAttackArea();
                break;
            }
        }
    }
}


void Field::lighDirections(){
    switch (spotlight){
    case Moving:
        for(auto point: possible_way){
            spotCell(point.x, point.y, sf::Color(0, 200, 0, 100), CELLS);
        }
        break;
    case Attack:
        for(auto point: attack_area){
            spotCell(point.x, point.y, sf::Color(255, 0, 0, 100), CELLS);
        }
        break;
    }
}


void Field::changeSpotlight(){
    spotlight = Field::Show(spotlight + 1);
    if(spotlight > Field::Show::Attack) spotlight = Field::Show::Moving;
}


void Field::moveSelectedUnit(int x, int y, int units){
    int x_pos = x;
    int y_pos = y;

    if(units == PIXELS){
        x_pos = x/(cell_size+3);
        y_pos = y/(cell_size+3);
    }

    Point moveVector(x_pos, y_pos);

    std::cout << moveVector.x << " " << moveVector.y << "\n\n";
    for(auto point: possible_way){
        std::cout << point.x << " " << point.y << std::endl;
    }

    for(auto entity:entities){
        if(entity->selected_p()){
            for(auto point: possible_way){
                if(point == moveVector){
                    entity->deselect();
                    possible_way.clear();
                    attack_area.clear();
                    moveVector -= entity->pos();
                    entity->move(moveVector);
                    break;
                }
            }
        }
    }

}


bool Field::checkSteps() const{
    for(auto entity: entities){
        if(entity->remainigSteps() > 0)
            return 0;
    }
    return 1;
}


void Field::handleKeyboard(const sf::Event &event){
    switch(event.key.code){
    case sf::Keyboard::Space:
        changeSpotlight();
        break;

    case sf::Keyboard::U:
        nextStep();
        break;

    default:
        break;
    }
}


void Field::nextStep(){
    iCurrentStep++;
    for(auto entity: entities){
        entity->nextStep();
        entity->deselect();
    }
}


std::string Field::getData() const{
    std::stringstream out;
    for(auto entity: entities){
        out << "Attack type: " << entity->attackType() << '\n';
        out << "Unit type: " << entity->unitType() << '\n';
        out << "Position: " << entity->pos().x << "; " << entity->pos().y << '\n';
        out << "Move points: " << entity->remainigSteps() << '\n';
        out << "Health: " << entity->health() << '\n';
        out << '\n';
    }
    return out.str();
}
