#pragma once
#include "units_interfaces.h"
#include "fieldcomponent.h"

#include <stdexcept>

class Field
{
private:

    FieldComponent*** fieldModel;

    friend class FieldIteator;

    unsigned int rowsAmount;
    unsigned int columnsAmount;
    unsigned int maximumEntitiesAmount;
    unsigned int currentEntitiesAmount;
public:
    Field(unsigned int rowsAmount, unsigned int columnsAmount, unsigned int maximumEntitiesAmount);
    Field(const Field& field);
    Field(Field&& field);
    ~Field();

    unsigned int getRowsAmount() const;
    unsigned int getColumnsAmount() const;
    unsigned int getMaximumEntitiesAmount() const;

    void setMaximumEntitiesAmount(unsigned int newMaximumEntitiesAmount);

    void placeCreature(unsigned int row, unsigned int columnn, ICreature* creature);

    void moveUnit(unsigned int rowNumberFrom, unsigned int columnNumberFrom,
                    unsigned int rowNumberTo, unsigned int columnNumberTo);

    FieldComponent* getCell(unsigned int rowNumber, unsigned int columnNumber);

    void commitFight(unsigned int rowFrom, unsigned int columnFrom,
                     unsigned int rowTo, unsigned int columnTo);

    QString getAsString();
};

class FieldIteator{
private:
    Field* field;

    unsigned int currentRow;
    unsigned int currentColumn;
public:
    FieldIteator(Field* fieldAttachedTo)
    {
        this->field = fieldAttachedTo;
        currentRow = 0;
        currentColumn = 0;
    }

    void reset() {
        currentRow = 0;
        currentColumn = 0;
    }

    bool hasNext() {
        if(currentRow < field->rowsAmount && currentColumn < field->columnsAmount)
            return true;
        else return false;
    }

    FieldComponent* getNext()
    {
        FieldComponent* cell = field->fieldModel[currentRow][currentColumn];
        currentRow++;
        if(currentRow == field->rowsAmount)
        {
            currentRow = 0;
            currentColumn++;
        }
        return cell;
    }
};
