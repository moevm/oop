//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_NEUTRALOBJECT_H
#define MYGAME_NEUTRALOBJECT_H


class NeutralObject {
public:
    bool isActive;
    int countGameMoves;
private:
    virtual void operator[](int *something) = 0;
    virtual void makeGameMove() = 0;
};


#endif //MYGAME_NEUTRALOBJECT_H
