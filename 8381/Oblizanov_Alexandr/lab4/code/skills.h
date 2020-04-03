#ifndef SKILLS_H
#define SKILLS_H

class Skills
{
public:
    Skills();

    void setAll(int move, int power, int spread, int bonus);

    int getMove() const;
    void setMove(int value);
    void reduceMove(int value);

    int getPower() const;
    void setPower(int value);
    void reducePower(int value);

    int getSpread() const;
    void setSpread(int value);
    void reduceSpread(int value);

    int getBonus() const;
    void setBonus(int value);

private:
    int move;
    int power;
    int spread;
    int bonus;
};

#endif // SKILLS_H
