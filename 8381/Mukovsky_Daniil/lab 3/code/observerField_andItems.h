#pragma once



class FieldObject;

class IField {
public:
	virtual ~IField() = default;
	virtual void onObjectDestroyed(FieldObject* destroyedUnit) = 0;
};

class IObject {
protected:
	IField* field;
public:
	virtual ~IObject() = default;
	virtual void  attachField(IField* field) = 0;


};
