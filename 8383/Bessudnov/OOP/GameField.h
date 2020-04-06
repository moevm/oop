#pragma once
#include "FieldBlock.h"
#include "GameUtilities.h"
#include <string>
#include <fstream>

class GameUnits;

class FieldProperties {
public:
	Vector2D dimensions;
	FieldBlock ***blocks;

	~FieldProperties() {
		for (int i = 0; i < dimensions.x; i++) {
			delete[] blocks[i];
		}

		delete blocks;
	}

	FieldProperties() {}
	FieldProperties(Vector2D dims) : dimensions(dims) {
		*blocks = new FieldBlock*[dimensions.x];
		for (int i = 0; i < dimensions.x; i++) {
			*blocks[i] = new FieldBlock[dimensions.y];
		}
	}

	FieldProperties(const FieldProperties &props) : dimensions(props.dimensions){
		*blocks = new FieldBlock*[dimensions.x];
		for (int i = 0; i < dimensions.x; i++) {
			*blocks[i] = new FieldBlock[dimensions.y];
		}
	}

	FieldProperties &operator=(const FieldProperties &props) {
		if (&props == this) return *this;

		for (int i = 0; i < dimensions.x; i++) delete[] blocks[i];
		delete[] blocks;

		dimensions = props.dimensions;
		*blocks = new FieldBlock*[dimensions.x];
		for (int i = 0; i < dimensions.x; i++) {
			*blocks[i] = new FieldBlock[dimensions.y];
		}

		for (int i = 0; i < dimensions.x; i++) {
			for (int j = 0; j < dimensions.y; j++) {
				blocks[i][j]->blockType = props.blocks[i][j]->blockType;
			}
		}

		return *this;

	}
};

class GameField : IBlocks{
public:
	FieldProperties fieldProps;

	Vector2D getFieldBorders();
	FieldBlock *getBlockAtLocation(Vector2D loc);
	void resizeMap(Vector2D newDimensions);

	void onMove(GameUnits &units);
	void onAttack();
	void onConversion();

	GameField(Vector2D dimensions, BlockTypes type);
	GameField(const GameField &field);
	GameField(std::string mapName);
	~GameField();
private:
	void createBlock(Vector2D location, int type);
};

