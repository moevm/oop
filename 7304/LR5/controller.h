#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
class Controller{
public:
    Model<double,int> myModel;

    Controller();

    void init();

    void replace(std::size_t id1, std::size_t id2);

    void backup();

    void handle(double c1,double c2);

    void undo();

    std::string getModelState();

    std::vector<std::string> getHandlersInfo();

    void loadFromTextFile(std::string path);

    void loadFromBinFile(std::string path);

    void saveToTextFile(std::string path);

    void saveToBinFile(std::string path);
};
#endif // CONTROLLER_H
