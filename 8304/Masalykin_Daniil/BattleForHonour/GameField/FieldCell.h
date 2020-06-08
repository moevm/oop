#ifndef BATTLEFORHONOUR_FIELDCELL_H
#define BATTLEFORHONOUR_FIELDCELL_H


#include <ostream>
#include "../Terrains/Terrain.h"
#include "../Objects/GameObject.h"

class FieldCell {

private:

    GameObject *object;
    Terrain *terrain;
    bool ismovable;

public:

    FieldCell():
        object(nullptr),
        terrain(nullptr),
        ismovable(true){}

    FieldCell(const FieldCell& cell);
    FieldCell(FieldCell &&other);
    explicit FieldCell(Terrain *terrain);

    bool isEmpty() {
        return object == nullptr;
    }

    [[nodiscard]] GameObject *getObject() const {
        return object;
    }
    [[nodiscard]] Terrain *getTerrain() const {
        return terrain;
    }
    bool isMovable() const{
        return this->ismovable;
    }
    bool setObject(GameObject *object);
    bool setTerrain(Terrain *terrain);
    void eraseObject();

    void changeMovable(bool flag){
        this->ismovable = flag;
    }

    friend std::ostream& operator<< (std::ostream &stream, const FieldCell &cell);
    FieldCell& operator=(FieldCell &&other);
    FieldCell& operator=(const FieldCell &cell);

};

#endif //BATTLEFORHONOUR_FIELDCELL_H
