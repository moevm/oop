#pragma once
#include "PlayableBoardUnit.h"
class PongoBaseBoardUnit;
class PongoBoardUnit : public PlayableBoardUnit
{
public:
	PongoBoardUnit(PongoBaseBoardUnit* base);
	PongoBoardUnit(QJsonObject snapshot, PongoBaseBoardUnit* base);
	virtual ~PongoBoardUnit();
	static int getUnitCount();
	static void resetUnitCount() { unit_count = 0; };
	QJsonObject getSnapshot() override;
	virtual std::string getClassName() = 0;
protected:
	PongoBaseBoardUnit* _base;
private:
	static int unit_count;
};

