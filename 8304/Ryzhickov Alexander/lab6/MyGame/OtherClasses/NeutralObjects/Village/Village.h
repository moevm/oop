//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_VILLAGE_H
#define GAME_VILLAGE_H


#include "../NeutralObject.h"

class Village : public NeutralObject {
private:
    int goldPoints = 50;
    int *addressMoney = nullptr;
public:
    void setAddressMoney(int *addressMoney);

public:
    Village();
    void operator[](int *something) override;
    void makeGameMove() override;
    std::string getInformationAboutNeutralObject(int *adress1, int *adress2) override ;
};


#endif //GAME_VILLAGE_H
