#ifndef IVISUALIZER_H
#define IVISUALIZER_H

class IVisualizer
{
public:
    virtual ~IVisualizer() = default;
    virtual void update() = 0;
};

#endif // IVISUALIZER_H
