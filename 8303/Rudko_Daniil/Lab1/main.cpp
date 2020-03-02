#include <iostream>

using namespace std;

class Unite {
public:
    int x, y;
    int health;
    int armor;
    int attack;
    string name;
    void move(int x, int y) {
        this->x = x - 1;
        this->y = y - 1;
    }
};

class GField {
private:
    int length, width;
    int numberUnit;
    const int maxnumberUnit = 5;
    Unite*** map;

public:

    GField(const GField &gfield) {}

    GField(int x, int y) {
        this->length = x;
        this->width = y;
        this->numberUnit = 0;

        map = new Unite** [this->length];
        for (int i = 0; i < this->width; i++)
        {
            map[i] = new Unite* [x];
            for (int j = 0; j < this->length; j++)
                map[i][j] = nullptr;
        }


    }
    void addUnit(Unite* unite) {
        if (unite->x < this->length && unite->y < this->width && this->numberUnit < this->maxnumberUnit) {
            map[unite->x][unite->y] = unite;
            this->numberUnit++;
        }
        else
            if(this->numberUnit >= this->maxnumberUnit)
                std::cout << "На поле максимальное количество юнитов" << std::endl;
    }

    void moveUnite(Unite* unite, int newx, int newy) {
        if (map[newx][newy] == nullptr) {
            map[unite->x][unite->y] = nullptr;
            unite->move(newx, newy);
            unite->x = newx;
            unite->y = newy;
            map[unite->x][unite->y] = unite;
        }
        else {
            std::cout << "Клетка игрового поля занята" << std::endl;
        }
    }

    void deleteUnite(Unite* unite) {
        int x = unite->x;
        int y = unite->y;
        delete map[unite->x][unite->y];
        map[x][y] = nullptr;
        this->numberUnit--;
    }

    void printField() {
        for (int i = 0; i < this->length; i++) {
            for (int j = 0; j < this->width; j++)
                if (map[i][j] != nullptr) {
                    cout << map[i][j]->name << " ";
                }
                else {
                    cout << "X ";
                }
            cout << endl;
        }
    }
};

class MeleeWarrior
    :public Unite {
protected:
    int melee_r;
};

class MediumWarrior
    :public Unite {
protected:
    int medium_r;
};

class DistanceWarrior
    :public Unite {
protected:
    int distance_r;
};

class Scorpio
    :public MeleeWarrior { //класс воинов "скорпион", ближний бой
public:
    Scorpio(int x, int y) {
        this->x = x;
        this->y = y;
        this->name = "scorpio";
        this->health = 100;
        this->armor = 50;
        this->attack = 30;
    }
};

class Mammoth
    :public MeleeWarrior { //класс воинов "мамонт", ближний бой
public:
    Mammoth(int x, int y) {
        this->x = x;
        this->y = y;
        this->name = "mammoth";
        this->health = 200;
        this->armor = 70;
        this->attack = 50;
    }
};

class Frog
    :public MediumWarrior { //класс воинов "лягушка", бой на средней дистанции
public:
    Frog(int x, int y) {
        this->x = x;
        this->y = y;
        this->name = "frog";
        this->health = 100;
        this->armor = 50;
        this->attack = 10;
    }
};

class Kangaroo
    :public MediumWarrior { //класс воинов "кенгуру", бой на средней дистанции
public:
    Kangaroo(int x, int y) {
        this->x = x;
        this->y = y;
        this->name = "kangaroo";
        this->health = 100;
        this->armor = 5;
        this->attack = 67;
    }
};

class Swallow
    :public DistanceWarrior { //класс воинов "ласточка", дальний бой
public:
    Swallow(int x, int y) {
        this->x = x;
        this->y = y;
        this->name = "swallow";
        this->health = 100;
        this->armor = 50;
        this->attack = 30;
    }
};

class Hawk
    :public DistanceWarrior { //класс воинов "ястреб", дальний бой
public:
    Hawk(int x, int y) {
        this->x = x;
        this->y = y;
        this->name = "hawk";
        this->health = 100;
        this->armor = 50;
        this->attack = 30;
    }
};



int main()
{

    cout << "Введите размеры поля" << endl;
    int a, b, c, d;
    cin >> a >> b;
    GField* field = new GField(a, b);
    cout << "Введите координаты Scorpio" << endl;
    cin >> c >> d;
    Unite* scorpio = new Scorpio(c-1, d-1);

    cout << "Введите координаты Frog" << endl;
    cin >> c >> d;
    Unite* frog = new Frog(c-1, d-1);

    field->addUnit(scorpio);
    field->addUnit(frog);
    field->printField();
    cout << endl;
    cout << "Введите координаты перемещения scorpio" << endl;
    cin >> a >> b;
    field->moveUnite(scorpio, a-1, b-1);
    field->printField();

    cout << endl;
    GField* field1 = field;
    cout << "Поле скопированно" << endl;
    field1->printField();

    cout << endl;
    cout << "Удаление юнита" << endl;
    field->deleteUnite(scorpio);
    field->printField();
    return 0;
}
