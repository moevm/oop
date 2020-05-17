#include "snapshotbackup.h"
#include "Field.h"

#include "Field.h"
#include "FileRAII.h"
#include "Base.h"

#include "unitfactory.h"

#include "Landscape/Landscape.h"
#include "Landscape/Ground.h"
#include "Landscape/Mountain.h"
#include "Landscape/Water.h"

#include "Neutral/NeutralObject.h"

#include "Neutral/damage.h"
#include "Neutral/restoreArmour.h"
#include "Neutral/restoreFuel.h"
#include "Neutral/restoreHealth.h"
#include "Neutral/none.h"


SnapshotBackup::SnapshotBackup(Field *field, int x, int y, int maxUnit, int curUnit, std::vector<Base*> bases):
    field(field), x(x), y(y), maxUnit(maxUnit), curUnit(curUnit), bases(bases)
{
    std::cout << "SnapshotBackup::SnapshotBackup(save)" << std::endl;
    fileWrie = new FileRAII("saveField.txt", "save");
}

SnapshotBackup::SnapshotBackup(Field *field)
{
    fileRead = new FileRead("saveField.txt");
    this->field = field;
    this->adapter = new Adapter;
}

SnapshotBackup::~SnapshotBackup()
{
    delete fileWrie;
    delete fileRead;
}

void SnapshotBackup::saveGame()
{
    std::cout << "saveGame" << std::endl;
    std::ostringstream str;
    this->adapter = field->getAdapter();

    //field
    str << x << " " << y << " " << maxUnit << std::endl;

    //cells
    for(int i=0;i<field->y;i++)
    {
        for(int j=0;j<field->x;j++)
        {
            Cell* c = field->cell[i][j];
            char tn = c->object->typeNeutral();
            str << c->x << " " << c->y << " " << c->landscape->typeLandscape() << " " << ((tn==' ')? '-' : tn) << std::endl;
        }
    }

    int count_base = 0;
    for(const auto& base : bases) {
        if(base)
            count_base++;
    }
    str << count_base << std::endl; // кол-во баз

    for(const auto& base : bases) {
        if(base) // когда база есть!
        {
            //base
            str << base->id <<" "<< base->x <<" "<<base->y<<" " << base->health<<" " << base->maxCountUnit << " " << base->countUnit << std::endl;

            //units
            Unit *unit;
            str << base->units.size() << std::endl;
            for (size_t i = 0; i < base->units.size(); i++){
                   unit = base->getUnitById(i);
                   str << unit->base_id << " " << unit->x << " " << unit->y << " " << unit->type() << " "
                   << unit->param.fuel << " " << unit->param.armor << " " << unit->param.damage
                   << " " << unit->param.health << std::endl;

            }
        }
    }

    fileWrie->write(str.str());
    adapter->gameSaved();
}

void SnapshotBackup::loadGame()
{

    std::cout << "loadGame" << std::endl;

    std::stringstream stream = fileRead->read();

    stream >> x >> y >> maxUnit;
    Field* field = new Field(x,y,maxUnit, new Adapter);

    // cells
    for(int i=0;i<y;i++)
    {
        for(int j=0;j<x;j++)
        {
            int x, y;
            char lt, ot;

            stream >> x >> y >> lt >> ot;

            Landscape* l = nullptr;
            std::cout << "read: "  << x << " "<< y << " " << lt <<" " << ot << std::endl;
            switch(lt)
            {
            case '.' : l = new Ground; break;
            case '^' : l = new Mountain; break;
            case '~' : l = new Water;
            }

            NeutralObject *obj = nullptr;
            switch(ot)
            {
            case '0': obj = new restoreFuelAction(new restoreFuelNight); break;
            case '1': obj = new RestoreArmourAction(new RestoreArmourNight); break;
            case '2': obj = new RestoreHealthAction(new RestoreHealthDay); break;
            case '4': obj = new incDamageAction(new incDamageDay); break;
            default: obj = new NoneObj;
            }
            field->cell[i][j] = new Cell(j,i,nullptr, l, obj);
        }
    }

    int count_base;
    stream >> count_base;

    for(int i=0;i<count_base;i++)
    {
        int id, baseX, baseY, maxCountUnitBase, health, countUnitBase;
        stream >> id >> baseX >> baseY >> maxCountUnitBase >> health >> countUnitBase ;

        field->createBase(id, baseX, baseY, maxCountUnitBase, health);

        int unitsSize;
        stream >> unitsSize;

        std::cout << "unitsSize: " << unitsSize << std::endl;

        for(int i=0;i<unitsSize;i++)
        {
            int base_id, x, y, f, a, d, h;
            char type;
            stream >> base_id >> x >> y >> type;
            stream >> f >> a >> d >> h;

            std::cout << base_id << " " << x<<" " << y << " " << type << " " << f <<" " << a  << " " << d << " " << h << std::endl;

            Unit *u;
            Base *base = field->getBase(base_id);
            if(base->x == x && base->y == y)
            {
                u = base->createUnit(type);
            }
            else {
                u = base->unitFactory.createUnit(type, x, y);
                base->units.addUnit(u);
                field->cell[y][x]->unit = u;
            }
            u->param.fuel = f;
            u->param.armor = a;
            u->param.damage = d;
            u->param.health = h;
        }
    }

    this->field->x = field->x;
    this->field->y = field->y;
    this->field->bases = field->bases;
    this->field->adapter = field->adapter;
    this->field->cell = field->cell;

    adapter->gameLoaded();
}
