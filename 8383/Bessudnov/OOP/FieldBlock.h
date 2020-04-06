#pragma once
#include "Interfaces.h"
#include <iostream>

enum BlockTypes {Grass, Boulder, Water, Bush, Base};

class FieldBlock : public IBlocks {
public:
	BlockTypes blockType;
	bool isWalkable;
	FieldBlock() : blockType(BlockTypes::Grass){}
	FieldBlock(BlockTypes type);
	~FieldBlock();

	virtual void onMove(GameUnits &units) {};
	virtual void onAttack() {};
	virtual void onConversion() {};
};

class GrassBlock : public FieldBlock {
public:
	GrassBlock() {
		blockType = BlockTypes::Grass;
		isWalkable = true;
	}
};

class BoulderBlock : public FieldBlock {
public:
	BoulderBlock() {
		blockType = BlockTypes::Boulder;
		isWalkable = false;
	}
};

class WaterBlock : public FieldBlock {
public:
	WaterBlock() {
		blockType = BlockTypes::Water;
		isWalkable = true;
	}
};

class BushBlock : public FieldBlock {
public:
	BushBlock() {
		blockType = BlockTypes::Bush;
		isWalkable = true;
	}
};

class BaseBlock : public FieldBlock {
public:
	BaseBlock() {
		blockType = BlockTypes::Base;
		isWalkable = false;
	}
};
