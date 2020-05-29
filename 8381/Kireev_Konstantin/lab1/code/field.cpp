#include "field.h"

Field::~Field()
{
    for(unsigned int i = 0; i < NmRows; ++i)
    {
        for(unsigned int j = 0; j < NmColumns; ++j)
            delete fieldModel[i][j];
        delete[] fieldModel[i];
    }
    delete[] fieldModel;
}

Field::Field(unsigned int NmRows, unsigned int NmColumns, unsigned int MaxObjects)
    : NmRows(NmRows)
    , NmColumns(NmColumns)
    , MaxObjects(MaxObjects)
{
    fieldModel = new cellInterface** [NmRows];
    for(unsigned int i = 0; i < NmRows; ++i)
    {
        fieldModel[i] = new cellInterface* [NmColumns];
        for(unsigned int j = 0; j < NmColumns; ++j)
            fieldModel[i][j] = nullptr;
    }
    CurrObjects = 0;
}

Field::Field(const Field& field)
    : NmRows(field.NmRows)
    , NmColumns(field.NmColumns)
    , MaxObjects(field.MaxObjects)
    , CurrObjects(field.CurrObjects)
{
    fieldModel = new cellInterface** [NmRows];
    for(unsigned int i = 0; i < NmRows; i++)
    {
        fieldModel[i] = new cellInterface*[NmColumns];
        for(unsigned int j = 0; j < NmColumns; j++)
        {
            fieldModel[i][j] = nullptr;
            if(field.fieldModel[i][j] != nullptr)
            {
                fieldModel[i][j] = field.fieldModel[i][j]->copy();
            }
        }
    }
}

Field::Field(Field&& field)
    : fieldModel(field.fieldModel)
    , NmRows(field.NmRows)
    , NmColumns(field.NmColumns)
    , MaxObjects(field.MaxObjects)
    , CurrObjects(field.CurrObjects)
{
    field.fieldModel = nullptr;
    field.NmRows = 0;
    field.NmColumns = 0;
}

unsigned int Field::getNmRows() const
{
    return NmRows;
}

unsigned int Field::getNmColumns() const
{
    return NmColumns;
}

void Field::setMaxObjects(unsigned int maxObjectsNewValue)
{
    MaxObjects = maxObjectsNewValue;
}

void Field::addObject(unsigned int Nrows, unsigned int Ncols, cellInterface *object)
{
    if (CurrObjects == MaxObjects)
        throw std::length_error ("Error:\nThere are max objects on the field");

    if (Nrows >= NmRows || Ncols >= NmColumns)
        throw std::out_of_range ("Error:\nOut of a field size");

    if (fieldModel[Nrows][Ncols] != nullptr)
        throw std::invalid_argument ("Error:\nThis cell is reserved");

    fieldModel[Nrows][Ncols] = object;
    CurrObjects++;
}

void Field::removeObject(unsigned int Nrows, unsigned int Ncols)
{
    if (Nrows >= NmRows || Ncols >= NmColumns)
        throw std::out_of_range ("Error:\nOut of a field size");

    if (fieldModel[Nrows][Ncols] == nullptr)
        throw std::invalid_argument ("Error:\nThis cell is empty");

    delete fieldModel[Nrows][Ncols];
    fieldModel[Nrows][Ncols] = nullptr;
    CurrObjects--;
}

void Field::moveObject(unsigned int NrowFrom, unsigned int NcolFrom, unsigned int NrowTo, unsigned int NcolTo)
{
    if (NrowFrom >= NmRows || NcolFrom >= NmColumns || NrowTo >= NmRows || NcolTo >= NmColumns)
        throw std::out_of_range ("Error:\nOut of a field size");

    cellInterface* object = fieldModel[NrowFrom][NcolFrom];
    if (object == nullptr)
        throw std::invalid_argument ("Error:\nThis cell is empty");

    if (object->isMove() == true)
    {
        cellInterface* newCell = fieldModel[NrowTo][NcolTo];
        if (newCell != nullptr)
            throw std::invalid_argument ("Error:\nNew cell is not empty");
        else
        {
            fieldModel[NrowTo][NcolTo] = object;
            fieldModel[NrowFrom][NcolFrom] = nullptr;
        }
    }
    else
        throw std::invalid_argument ("Error:\nObject is not mobile");
}

cellInterface* Field::getObject(unsigned int Nrow, unsigned int Ncol)
{
    if(Nrow >= NmRows || Ncol >= NmColumns)
        throw std::out_of_range("Error:\nOut of a field size");
    else
        return fieldModel[Nrow][Ncol];
}

QString Field::getStringInfo()
{
    QString output = nullptr;
    for(unsigned int i = 0; i < NmRows; i++)
    {
        for(unsigned int j = 0; j < NmColumns; j++)
        {
            cellInterface* obj = getObject(i,j);
            if(obj == nullptr)
                output.append("-------");
            else
                output.append(obj->getClass().leftRef(7));
            output.append("  ");
        }
        output.append("\n");
    }
    return output;
}
