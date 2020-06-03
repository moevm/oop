#include "Editor.hpp"

Editor::Editor(std::string editorID, Field *field, UUID *uuidGen, NeutralObjectFactory *neutralObjectFactory)
{
    this->editorID = editorID;
    this->field = field;
    this->uuidGen = uuidGen;
    this->neutralObjectFactory = neutralObjectFactory;
}

std::string Editor::getEditorID() { return editorID; }

void Editor::createResourceGenerator(unsigned int rowNumber, unsigned int columnNumber, unsigned int type)
{
    field->addObject(rowNumber, columnNumber, neutralObjectFactory->createResourceGenerator(type, uuidGen->generateUUID()));
}

void Editor::updateLandscape(unsigned int rowNumber, unsigned int columnNumber, unsigned int type)
{
    field->updateLandscape(rowNumber, columnNumber, type);
}

void Editor::moveObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber)
{
    field->moveObject(fromRowNumber, fromColumnNumber, toRowNumber, toColumnNumber);
}

void Editor::removeObject(unsigned int rowNumber, unsigned int columnNumber)
{
    removeObject(rowNumber, columnNumber);
}

