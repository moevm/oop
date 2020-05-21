#include "visualizer.h"

Visualizer::Visualizer(GameWindow *window_, std::shared_ptr<UIFacade> facade_) :
    window(std::move(window_)), facade(std::move(facade_)) { }

void Visualizer::update()
{
    std::shared_ptr<Game> game = facade->game.lock()->getCurrGameInstance();
    std::shared_ptr<GameFieldProxy> field = game->field;

    std::shared_ptr<Unit> unit;
    std::shared_ptr<GameBase> base;

    window->visualField->clear();
    window->RoadMap->clear();

    for(size_t i = 0; i < field->getWidth(); ++i)
    {
        for(size_t j = 0; j < field->getHeight(); ++j)
        {
            unit = field->getUnitByCoords(i, j);
            if(unit == nullptr)
            {
                window->visualField->insertPlainText("- ");
            }
            else
            {
                if(unit->getType() == CANNON_FODDER)
                {
                    window->visualField->insertPlainText("f ");
                }
                else if(unit->getType() == INFANTRY)
                {
                    window->visualField->insertPlainText("i ");
                }
                else if(unit->getType() == SHOOTER)
                {
                    window->visualField->insertPlainText("s ");
                }
                else if(unit->getType() == WIZARD)
                {
                    window->visualField->insertPlainText("w ");
                }
                else if(unit->getType() == CAVALRY)
                {
                    window->visualField->insertPlainText("c ");
                }
            }
        }
        window->visualField->insertPlainText("\n");
    }

    for(size_t i = 0; i < field->getWidth(); ++i)
    {
        for(size_t j = 0; j < field->getHeight(); ++j)
        {
            base = field->getBaseByCoords(i, j);
            if(base != nullptr)
            {
                window->RoadMap->insertPlainText("* ");
            }
            else if(field->artifactMap.find(Coords(i,j)) != field->artifactMap.end())
            {
                window->RoadMap->insertPlainText("? ");
            }
        }
        window->RoadMap->insertPlainText("\n");
    }
}
