#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <memory>

#include "GUI/IVisualizer.h"
#include "GUI/gamewindow.h"
#include "Game/UIFacade.h"

class Visualizer : public IVisualizer
{
public:
    Visualizer(GameWindow *window_, std::shared_ptr<UIFacade> facade_);
    void update() override;

private:
    std::shared_ptr<GameWindow> window;
    std::shared_ptr<UIFacade> facade;
};

#endif // VISUALIZER_H
