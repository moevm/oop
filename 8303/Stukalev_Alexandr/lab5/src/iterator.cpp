#include "iterator.h"
#include "QtCore"
#include <iostream>

Iterator::Iterator(Field* field):field(field), currUnit(nullptr), x(0), y(0),isFirstIter(true)
{

}

Iterator& Iterator::operator++(int)
{
    for (int i = currUnit->getX() + 1; i < field->getX(); i++)
    {
        qDebug() << "i: "<< i;
        Unit * newcurrUnit = field->getUnit(i,currUnit->getY());
        if(newcurrUnit != nullptr)
        {

            this->x = i;
            qDebug() << this->x;
            qDebug() << this->y;
            this->currUnit = newcurrUnit;
            return *this;
        }
    }
    for (int j = currUnit->getY() + 1; j < field->getY(); j++)
    {
        for (int i = 0; i < field->getX(); i++)
        {
            qDebug() << "i: "<< i;
            qDebug() << "j: "<< j;
            Unit* newcurrUnit = field->getUnit(i,j);
            if(newcurrUnit != nullptr)
            {
                this->x = i;
                this->y = j;
                qDebug() << this->x;
                qDebug() << this->y;
                return *this;
            }
            if(j == field->getY() - 1 && i == field->getX() - 1)
            {
                i = 0;
                j = 0;
            }
        }
    }

}

Unit*& Iterator::operator*()
{
    return currUnit;
}
void ::Iterator::Next()
{
    for (int i = currUnit->getX() + 1; i < field->getX(); i++)
    {
        //qDebug() << "i: "<< i;
        Unit * newcurrUnit = field->getUnit(i,currUnit->getY());
        if(newcurrUnit != nullptr)
        {

            this->x = i;
            //qDebug() << this->x;
            //qDebug() << this->y;
            this->currUnit = newcurrUnit;
            return;
        }
    }
    for (int j = currUnit->getY() + 1; j < field->getY(); j++)
    {
        for (int i = 0; i < field->getX(); i++)
        {
            //qDebug() << "i: "<< i;
            //qDebug() << "j: "<< j;
            Unit* newcurrUnit = field->getUnit(i,j);
            if(newcurrUnit != nullptr)
            {
                this->x = i;
                this->y = j;
                //qDebug() << this->x;
                //qDebug() << this->y;
                currUnit = newcurrUnit;
                return;
            }
            if(j == field->getY() - 1 && i == field->getX() - 1)
            {
                i = 0;
                j = 0;
            }
        }
    }
}
bool Iterator::canFindNext()
{

    int x = this->x;
    int y = this->y;
    //qDebug() << this->x;
    //qDebug() << this->y;
    for (int i = x + 1; i < field->getX(); i++)
    {
        if (field->checkUnit(i,y))
        {
            if (isFirstIter)
            {
                this->y = y;
                this->x = i;
                //qDebug() << this->x;
                //qDebug() << this->y;
                currUnit = this->field->getUnit(i,y);
                isFirstIter = false;
            }
            return true;
        }
    }
    for (int j = y + 1; j < field->getY(); j++)
    {
        for (int i = 0; i < field->getX(); i++)
        {
            if (field->checkUnit(i,j))
            {
                if (isFirstIter)
                {
                    this->y = j;
                    this->x = i;
                    //qDebug() << this->x;
                    //qDebug() << this->y;
                    currUnit = this->field->getUnit(i,j);
                    isFirstIter = false;
                }
                return true;
            }
        }
    }
    return false;
}

void Iterator::getXY()
{
    cout << this->x << "\n";
    cout << this->y;
}

