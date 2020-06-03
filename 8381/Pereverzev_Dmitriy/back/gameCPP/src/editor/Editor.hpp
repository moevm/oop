#ifndef Editor_hpp
#define Editor_hpp

#include "../field/Field.hpp"

#include "../uuid/UUID.hpp"
#include "../objects/neutralObject/NeutralObjectFactory.hpp"

class Editor
{
private:
    Field *field;
    NeutralObjectFactory *neutralObjectFactory;
    UUID *uuidGen;
    std::string editorID;

public:
    Editor(std::string editorID, Field *field, UUID *uuidGen, NeutralObjectFactory *neutralObjectFactory);
    std::string getEditorID();
    void createResourceGenerator(unsigned int rowNumber, unsigned int columnNumber, unsigned int type);
    void updateLandscape(unsigned int rowNumber, unsigned int columnNumber, unsigned int type);
    void moveObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber);
    void removeObject(unsigned int rowNumber, unsigned int columnNumber);

};

#endif /* Editor_hpp */
