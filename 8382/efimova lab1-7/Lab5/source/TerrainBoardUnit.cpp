#include "TerrainBoardUnit.h"

QJsonObject TerrainBoardUnit::getSnapshot() {
	QJsonObject terrainUnitSnapshot;//он возвращает json-ский объект
	terrainUnitSnapshot.insert("type", "terrain");//который вставляет в поле тип и значение(рельеф)
	terrainUnitSnapshot.insert("subtype", getName().c_str());//и сам тип он берет имя этого юнита(трава)
	return terrainUnitSnapshot;
}