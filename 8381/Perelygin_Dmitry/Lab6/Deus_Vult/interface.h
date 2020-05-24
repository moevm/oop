#ifndef INTERFACE_H
#define INTERFACE_H
#include "unit.h"
#include "base.h"
#include "field.h"

class Interface
{
    protected:
        Unit* unit;
        Base* base;
        Field* field;

    public:
        Interface(
                   Unit* unit = nullptr,
                   Base* base = nullptr,
                   Field* field= nullptr
                   )
        {
            this->unit = unit ?: new Unit;
            this->base = base ?: new Base();
            this->field = field?: new Field(10,10);
        }

        int x,y,type,unit_id,def_unit_id;

        int St_Game(int u_count);




        ~Interface( ){
            delete unit;
            delete base;
        }
};

#endif // INTERFACE_H
