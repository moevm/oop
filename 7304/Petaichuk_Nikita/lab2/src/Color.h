#pragma once

//Класс цвета
class Color
{
public:
    explicit Color(unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0);
    Color(const Color &other);
    Color& operator=(const Color &other);

    void setRedComponet(unsigned int red);
    void setGreenComponet(unsigned int green);
    void setBlueComponet(unsigned int blue);

    unsigned int getRedComponent() const;
    unsigned int getGreenComponent() const;
    unsigned int getBlueComponent() const;

private:
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};
