#include "EditorCommand.hpp"
EditorCommand::EditorCommand(Editor *editor) /* , v8::Isolate *isolate) : Command(isolate) */
{
    this->editor = editor;
}

void EditorCommand::execute(v8::Local<v8::Value> request)
{
    

    v8::Local<v8::Object> objRequest;

    if (request->IsObject())
        objRequest = request->ToObject();
    else
        return;

    /* * * * * */
    unsigned int task;
    v8::Local<v8::Object> params;
    /* * * * * */

    if (!GetObjProperty(objRequest, "task", task))
        return;
    if (!GetObjProperty(objRequest, "params", params))
        return;

    if (task == MOVE)
    {
        

        /* * * * * */
        v8::Local<v8::Object> moveInfo;
        /*  */ v8::Local<v8::Object> moveFrom;
        /*  */ /*  */ unsigned int fromX;
        /*  */ /*  */ unsigned int fromY;
        /*  */ v8::Local<v8::Object> moveTo;
        /*  */ /*  */ unsigned int toX;
        /*  */ /*  */ unsigned int toY;
        /* * * * * */

        if (!GetObjProperty(params, "moveInfo", moveInfo))
            return;
        if (!GetObjProperty(moveInfo, "moveFrom", moveFrom))
            return;
        if (!GetObjProperty(moveFrom, "fromX", fromX))
            return;
        if (!GetObjProperty(moveFrom, "fromY", fromY))
            return;
        if (!GetObjProperty(moveInfo, "moveTo", moveTo))
            return;
        if (!GetObjProperty(moveTo, "toX", toX))
            return;
        if (!GetObjProperty(moveTo, "toY", toY))
            return;
        

        try
        {
            editor->moveObject(fromY, fromX, toY, toX); 
        }
        catch (Except &except)
        {
            fireEvent("except", except.getLog());
            
        }
    }
    else if (task == ADD_OBJ)
    {

        

        /* * * * * */
        v8::Local<v8::Object> neutralObjectInfo;
        /*  */ unsigned int x;
        /*  */ unsigned int y;
        /*  */ unsigned int neutralObjectType;
        /* * * * * */

        if (!GetObjProperty(params, "neutralObjectInfo", neutralObjectInfo))
            return;
        if (!GetObjProperty(neutralObjectInfo, "x", x))
            return;
        if (!GetObjProperty(neutralObjectInfo, "y", y))
            return;
        if (!GetObjProperty(neutralObjectInfo, "neutralObjectType", neutralObjectType))
            return;

        

        editor->createResourceGenerator(y, x, neutralObjectType); 
    }
}
