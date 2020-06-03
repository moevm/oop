#include "Field.hpp"
Field::Field(unsigned int rowsQuantity, unsigned int columnsQuantity, unsigned int maximumObjectsQuantity, Mediator *mediator)
{
    

    this->rowsQuantity = rowsQuantity;
    this->columnsQuantity = columnsQuantity;
    this->currentObjectsQuantity = 0;
    this->maximumObjectsQuantity = maximumObjectsQuantity;
    this->mediator = mediator;

    fieldGrid = new FieldCell *[rowsQuantity];
    for (unsigned int i = 0; i < rowsQuantity; i++)
        fieldGrid[i] = new FieldCell[columnsQuantity];
}

Field::Field(unsigned int rowsQuantity, unsigned int columnsQuantity, Mediator *mediator)
{
    

    this->rowsQuantity = rowsQuantity;
    this->columnsQuantity = columnsQuantity;
    this->currentObjectsQuantity = 0;
    this->maximumObjectsQuantity = rowsQuantity * columnsQuantity * 0.8;
    this->mediator = mediator;

    fieldGrid = new FieldCell *[rowsQuantity];
    for (unsigned int i = 0; i < rowsQuantity; i++)
        fieldGrid[i] = new FieldCell[columnsQuantity];
}

Field::Field(const Field &lastField)
{
    

    this->rowsQuantity = lastField.rowsQuantity;
    this->columnsQuantity = lastField.columnsQuantity;
    this->currentObjectsQuantity = lastField.currentObjectsQuantity;
    this->maximumObjectsQuantity = lastField.maximumObjectsQuantity;
    this->mediator = lastField.mediator;

    fieldGrid = new FieldCell *[lastField.rowsQuantity];
    for (unsigned int i = 0; i < lastField.rowsQuantity; i++)
    {
        fieldGrid[i] = new FieldCell[lastField.columnsQuantity];
        for (unsigned int j = 0; j < lastField.columnsQuantity; j++)
            this->fieldGrid[i][j] = lastField.fieldGrid[i][j];
    }
}

Field::Field(Field &&lastField)
{
    
    this->fieldGrid = lastField.fieldGrid;
    this->rowsQuantity = lastField.rowsQuantity;
    this->columnsQuantity = lastField.columnsQuantity;
    this->currentObjectsQuantity = lastField.currentObjectsQuantity;
    this->maximumObjectsQuantity = lastField.maximumObjectsQuantity;
    this->mediator = lastField.mediator;

    fieldGrid = new FieldCell *[lastField.rowsQuantity];
    for (unsigned int i = 0; i < lastField.rowsQuantity; i++)
    {
        fieldGrid[i] = new FieldCell[lastField.columnsQuantity];
        for (unsigned int j = 0; j < lastField.columnsQuantity; j++)
            this->fieldGrid[i][j] = lastField.fieldGrid[i][j];
    }

    
    
    
    
    
    
}
Field::~Field()
{
    
    for (unsigned int i = 0; i < rowsQuantity; i++)
    {
        for (unsigned int j = 0; j < columnsQuantity; j++)
        {
            delete &fieldGrid[i][j];
            
        }
        delete[] fieldGrid[i];
    }
    delete[] fieldGrid;
    delete mediator;
}
/* 
void Field::setRowsQuantity(unsigned int rowsQuantity)
{
    this->rowsQuantity = rowsQuantity;
}
void Field::setColumnsQuantity(unsigned int columnsQuantity)
{
    this->columnsQuantity = columnsQuantity;
}
void Field::setMaximumObject(unsigned int maximumObjectsQuantity)
{
    this->maximumObjectsQuantity = maximumObjectsQuantity;
}
void Field::setCurrentObject(unsigned int currentObjectsQuantity)
{
    this->currentObjectsQuantity = currentObjectsQuantity;
}
void Field::setMediator(Mediator *mediator)
{
    this->mediator = mediator;
}
*/

unsigned int Field::getRowsQuantity() const
{
    return rowsQuantity;
}
unsigned int Field::getColumnsQuantity() const
{
    return columnsQuantity;
}
unsigned int Field::getMaximumObject() const
{
    return maximumObjectsQuantity;
}
unsigned int Field::getCurrentObject() const
{
    return currentObjectsQuantity;
}

FieldCell &Field::getFieldCell(unsigned int rowNumber, unsigned int columnNumber)
{
    

    
    
    return fieldGrid[rowNumber][columnNumber];
}




















Mediator *Field::getMediator() const
{
    return mediator;
}

void Field::addObject(unsigned int rowNumber, unsigned int columnNumber, Object *object)
{
    if (object == nullptr)
        return;
    if (rowNumber >= rowsQuantity || columnNumber >= columnsQuantity)
    {

        
        return;
    }
    if (currentObjectsQuantity >= maximumObjectsQuantity)
    {
        
        
        
        ;
        return;
    }
    if (fieldGrid[rowNumber][columnNumber].getObject() != nullptr)
    {
        
        
        
        return;
    }

    fieldGrid[rowNumber][columnNumber].setObject(object);

    
    object->attachEvent("object updated", this);
    object->attachEvent("log", this);

    currentObjectsQuantity++;
    
    
    

    fireEvent("object updated", getObjectData(rowNumber, columnNumber));
}

void Field::updateLandscape(unsigned int rowNumber, unsigned int columnNumber, unsigned int landscapeType /* Landscape *landscape */)
{
    fieldGrid[rowNumber][columnNumber].setLandscape(new LandscapeProxy(landscapeType));
}

void Field::removeObject(Object *object)
{
    for (int rowNumber = 0; rowNumber < rowsQuantity; rowNumber++)
        for (int columnNumber = 0; columnNumber < columnsQuantity; columnNumber++)
        {
            if (fieldGrid[rowNumber][columnNumber].getObject() == object)
            {
                
                removeObject(rowNumber, columnNumber);
            }
        }
}
void Field::removeObject(unsigned int rowNumber, unsigned int columnNumber)
{

    if (rowNumber >= rowsQuantity || columnNumber >= columnsQuantity)
    {
        
        return;
    }

    if (fieldGrid[rowNumber][columnNumber].getObject() == nullptr)
    {
        
        
        
        return;
    }
    
    fieldGrid[rowNumber][columnNumber].setObject(nullptr);
    currentObjectsQuantity--;
    
    
    fireEvent("object updated", getObjectData(rowNumber, columnNumber));
}

void Field::moveObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber)
{
    Object *fromObj = fieldGrid[fromRowNumber][fromColumnNumber].getObject();
    Object *toObj = fieldGrid[toRowNumber][toColumnNumber].getObject();

    if (fromObj == nullptr)
    {
        
        
        
        throw(Except("The field cell contains no objects. You cannot move a void", "void Field::moveObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber)", 0));
        return;
    }

    if (!fromObj->isMoveable())
    {
        
        
        
        throw(Except("The Object cannot be moved. You cannot move this Object.", "void Field::moveObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber)", 0));

        return;
    }

    if (toObj == nullptr)
    {
        if (!fieldGrid[toRowNumber][toColumnNumber].getLandscape()->checkAccessMove(fieldGrid[fromRowNumber][fromColumnNumber].getObject()->getObjectType()))
        {

            
            
            
            
            throw(Except("The object cannot be moved to this cell.(landscape)", "void Field::moveObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber)", 0));

            return;
        }
        fieldGrid[toRowNumber][toColumnNumber].setObject(fromObj);
        fieldGrid[fromRowNumber][fromColumnNumber].setObject(nullptr);
        
        
        
        fireEvent("object updated", getObjectData(fromRowNumber, fromColumnNumber));
        fireEvent("object updated", getObjectData(toRowNumber, toColumnNumber));
        return;
    }
    else
    {

        mediator->interactionObjObj(this, fromRowNumber, fromColumnNumber, toRowNumber, toColumnNumber);

        /* 
        if (!fieldGrid[toRowNumber][toColumnNumber].getLandscape()->checkAccessInteraction(fieldGrid[fromRowNumber][fromColumnNumber].getObject()->getObjectType()))
        {

            
                  
                  
            return;
        }

        
              
              
        interactionObjObj(fromObj, toObj);
         */
    }
}
/* 
void Field::battle(CombatObject *object1, CombatObject *object2)
{
    double damage1 = object1->getDamage(),
           damage2 = object2->getDamage(),
           armor1 = object1->getArmor(),
           armor2 = object2->getArmor();

    
    

    object1->underAttack(damage2, armor2);
    object2->underAttack(damage1, armor1);

    
    
}

void Field::interactionObjObj(Object *object1, Object *object2)
{
    if (object1 == nullptr || object2 == nullptr)
        return;
    std::string resGenerators = "Farm GoldMine Sawmill";
    if (resGenerators.find(object2->getObjectType()) != std::string::npos)
    {
        *object2 << object1;
        return;
    }

    

    if (object1->getPlayerID() == object2->getPlayerID())
    {
        
              
              
        return;
    }
    else
        battle((CombatObject *)object1, (CombatObject *)object2);
}
 */

v8::Local<v8::Array> Field::getLandscapesData()
{
    v8::Local<v8::Array> rows = Nan::New<v8::Array>();
    for (unsigned int rowNumber = 0; rowNumber < rowsQuantity; rowNumber++)
    {
        v8::Local<v8::Array> columns = Nan::New<v8::Array>();
        for (unsigned int columnNumber = 0; columnNumber < columnsQuantity; columnNumber++)
        {
            SetArrProperty(columns, columnNumber, getLandscapeData(rowNumber, columnNumber));
        }
        SetArrProperty(rows, rowNumber, columns);
    }
    return rows;
}

v8::Local<v8::Array> Field::getObjectsData()
{
    v8::Local<v8::Array> rows = Nan::New<v8::Array>();
    for (unsigned int rowNumber = 0; rowNumber < rowsQuantity; rowNumber++)
    {
        v8::Local<v8::Array> columns = Nan::New<v8::Array>();
        for (unsigned int columnNumber = 0; columnNumber < columnsQuantity; columnNumber++)
        {
            SetArrProperty(columns, columnNumber, getObjectData(rowNumber, columnNumber));
        }
        SetArrProperty(rows, rowNumber, columns);
    }

    return rows;
}

v8::Local<v8::Object> Field::getObjectData(unsigned int rowNumber, unsigned int columnNumber)
{
    

    
    v8::Local<v8::Object> data = Nan::New<v8::Object>();
    std::string objectType("empty_");
    Object *object = fieldGrid[rowNumber][columnNumber].getObject();

    if (object != nullptr)
        data = object->getFullInfo();
    else
        SetObjProperty(data, "objectType", objectType);
    SetObjProperty(data, "x", columnNumber);
    SetObjProperty(data, "y", rowNumber);

    return data;
}

v8::Local<v8::Object> Field::getObjectData(Object *object)
{
    

    for (unsigned int rowNumber = 0; rowNumber < rowsQuantity; rowNumber++)
        for (unsigned int columnNumber = 0; columnNumber < columnsQuantity; columnNumber++)
        {
            
            
            
            
            
            if (object == fieldGrid[rowNumber][columnNumber].getObject())
            {
                return getObjectData(rowNumber, columnNumber);
            }
        }
    return Nan::New<v8::Object>();
}

v8::Local<v8::Object> Field::getLandscapeData(unsigned int rowNumber, unsigned int columnNumber)
{
    v8::Local<v8::Object> data = Nan::New<v8::Object>();
    SetObjProperty(data, "lanscapeType", fieldGrid[rowNumber][columnNumber].getLandscape()->getLandscapeType());
    return data;
}

void Field::eventHandler(Event *event)
{
    if (event->getSEventId() == "object death")
    {
        
        removeObject((Object *)event->getSource());
    }
    else if (event->getSEventId() == "object updated")
    {
        for (unsigned int rowNumber = 0; rowNumber < rowsQuantity; rowNumber++)
            for (unsigned int columnNumber = 0; columnNumber < columnsQuantity; columnNumber++)
                if (fieldGrid[rowNumber][columnNumber].getObject() == (Object *)event->getSource())
                {
                    fireEvent("object updated", getObjectData(rowNumber, columnNumber));
                }
    }
};


v8::Local<v8::Object> Field::getFullInfo()
{
    v8::Local<v8::Object> info = Nan::New<v8::Object>();
    v8::Isolate *isolate = info->GetIsolate();
    v8::Local<v8::Context> context = v8::Context::New(isolate);

    v8::Local<v8::Array> landscapesArray = Nan::New<v8::Array>();
    v8::Local<v8::Array> unitsArray = Nan::New<v8::Array>();
    v8::Local<v8::Array> resGensArray = Nan::New<v8::Array>();
    for (unsigned int i = 0; i < rowsQuantity; i++)
    {
        for (unsigned int j = 0; j < columnsQuantity; j++)
        {

            SetArrProperty(landscapesArray, i * columnsQuantity + j, fieldGrid[i][j].getLandscape()->getLandscapeType());
            if (fieldGrid[i][j].getObject() != nullptr)
            {
                
                unsigned int objectType = fieldGrid[i][j].getObject()->getObjectType();
                if (objectType > 0 && objectType < 7)
                {
                    
                    SetArrProperty(unitsArray, unitsArray->Length(), getObjectData(i, j));
                }
                else if (objectType >= 7)
                {
                    SetArrProperty(resGensArray, resGensArray->Length(), getObjectData(i, j));
                }
            }
        }
    }
    SetObjProperty(info, "landscapes", landscapesArray);
    SetObjProperty(info, "units", unitsArray);
    SetObjProperty(info, "resGens", resGensArray);
    SetObjProperty(info, "rowsQuantity", rowsQuantity);
    SetObjProperty(info, "columnsQuantity", columnsQuantity);
    SetObjProperty(info, "currentObjectsQuantity", currentObjectsQuantity);
    SetObjProperty(info, "maximumObjectsQuantity", maximumObjectsQuantity);
    

    return info;
}